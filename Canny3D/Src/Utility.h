#pragma once
#include <imebra/imebra.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <QImage>
#include <string>
#include <optional>
#include <variant>
class CannySettings;
namespace fs = std::experimental::filesystem;

static void removeUnwantedEdges(cv::Mat canny, cv::Mat original, int threshold = 170)
{
	auto const radius = 2;
	for (auto row = radius; row < canny.rows - radius; ++row)
	{
		for (auto col = radius; col < canny.cols - radius; ++col)
		{
			auto& edgePixel = canny.at<uint8_t>(row, col);
			if (edgePixel == 0) continue;
			auto const toRemove = [&]
			{
				auto count = 0;
				for (auto maskRow = -radius; maskRow <= radius; ++maskRow)
				{
					for (auto maskCol = -radius; maskCol <= radius; ++maskCol)
					{
						auto const r = row + maskRow;
						auto const c = col + maskCol;
						if (original.at<uint8_t>(r, c) >= threshold)
							count++;
					}
				}
				// если поблизости есть несколько полезных пикселей
				auto const area = (2 * radius + 1) * (2 * radius + 1);
				return count < 2 * radius;
			}();
			if (toRemove)
			{
				edgePixel = 0;
			}
		}
	}
}

static cv::Mat gauss(cv::Mat img, int gaussMaskDiameter = 5, double gaussSigma = 1)
{
	cv::Mat blured;
	auto maskSize = cv::Size(gaussMaskDiameter, gaussMaskDiameter);
	GaussianBlur(img, blured, maskSize, gaussSigma, gaussSigma);
	return blured;
}

static cv::Mat toZeroThreshold(cv::Mat img)
{
	cv::Mat result;
	threshold(img, result, 180, 255, cv::THRESH_TOZERO);
	return result;
}

static std::pair<int, int> otsuThreshold(cv::Mat img)
{
	cv::Mat out;
	double threshold = cv::threshold(
		img, out, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU
	);

	return {0.5 * threshold, threshold};
}

struct Threshold
{
	int low;
	int high;
};

static cv::Mat canny(cv::Mat img, Threshold threshold = {100, 200})
{
	cv::Mat edges;
	Canny(img, edges, threshold.low, threshold.high, 3, true);
	return edges;
}

static cv::Mat bytesToMat(std::vector<char>& bytes, const int width, const int height)
{
	const auto mat = cv::Mat(height, width, CV_8UC4, &bytes[0]).clone();
	cv::Mat gray;
	cvtColor(mat, gray, cv::COLOR_RGBA2GRAY);
	return gray;
}

static std::wstring readTag(imebra::DataSet* const dataset, const imebra::TagId& tagId)
{
	try { return dataset->getUnicodeString(tagId, 0); }
	catch (...)
	{
	}
	return {};
}

static std::wstring readTag(imebra::DataSet* const dataset, const imebra::tagId_t& tag)
{
	try { return readTag(dataset, imebra::TagId(tag)); }
	catch (...)
	{
	}
	return {};
}

struct VOI
{
	int center;
	int width;
};


struct treeTags
{
	std::vector<std::wstring> groupBy{};
	float sliceLocation{};

	std::vector<std::wstring> groupName{};

	treeTags(imebra::DataSet* const dataset)
		: groupBy
		  {
			  readTag(dataset, imebra::tagId_t::PatientID_0010_0020),
			  readTag(dataset, imebra::tagId_t::StudyInstanceUID_0020_000D),
			  readTag(dataset, imebra::tagId_t::SeriesNumber_0020_0011),
		  }
		  , sliceLocation{std::stof(readTag(dataset, imebra::tagId_t::SliceLocation_0020_1041))}
		  , groupName
		  {
			  readTag(dataset, imebra::tagId_t::PatientName_0010_0010),
			  readTag(dataset, imebra::tagId_t::StudyDescription_0008_1030),
			  readTag(dataset, imebra::tagId_t::SeriesDescription_0008_103E),
		  }
	{
	}

	treeTags() = default;
	treeTags(treeTags const&) = default;
	treeTags& operator=(treeTags const&) = default;
	treeTags(treeTags&&) = default;
	treeTags& operator=(treeTags&&) = default;
	~treeTags() = default;
};

struct ImebraImage
{
	std::shared_ptr<imebra::Image const> image{};
	std::optional<VOI> voi{};
	treeTags tags{};

	explicit ImebraImage(imebra::DataSet* const loadedDataSet)
		: image{std::shared_ptr<imebra::Image>(loadedDataSet->getImageApplyModalityTransform(0))}
		  , tags{loadedDataSet}
	{
		if (!imebra::ColorTransformsFactory::isMonochrome(image->getColorSpace()))
		{
			throw std::runtime_error("Image must be monochrome.");
		}

		if (auto const vois = loadedDataSet->getVOIs(); !vois.empty())
		{
			voi = VOI{static_cast<int>(vois[0].center), static_cast<int>(vois[0].width)};
		}
	}

	ImebraImage() = default;
	ImebraImage(ImebraImage const&) = default;
	ImebraImage& operator=(ImebraImage const&) = default;
	ImebraImage(ImebraImage&&) = default;
	ImebraImage& operator=(ImebraImage&&) = default;
	~ImebraImage() = default;
};

static cv::Mat applyVoilutTransform(ImebraImage const& data, std::optional<VOI> voi = {})
{
	auto const width = data.image->getWidth();
	auto const height = data.image->getHeight();

	imebra::TransformsChain chain;
	imebra::VOILUT voilutTransform;

	if (voi)
	{
		voilutTransform.setCenterWidth(voi->center, voi->width);
	}
	else if (data.voi)
	{
		voilutTransform.setCenterWidth(data.voi->center, data.voi->width);
	}
	else
	{
		voilutTransform.applyOptimalVOI(*data.image, 0, 0, width, height);
	}
	chain.addTransform(voilutTransform);

	imebra::DrawBitmap draw{chain};

	const auto buffer_size = draw.getBitmap(*data.image,
	                                        imebra::drawBitmapType_t::drawBitmapRGBA, 4, nullptr, 0);

	std::vector<char> buffer(buffer_size, 0);
	draw.getBitmap(*data.image, imebra::drawBitmapType_t::drawBitmapRGBA, 4,
	               reinterpret_cast<char*>(&buffer.at(0)), buffer_size);

	return bytesToMat(buffer, width, height);
}


static ImebraImage readFile(const std::wstring& path)
{
	auto dataset = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path));
	return ImebraImage{dataset.get()};
}

static std::wstring sv(const QString& s)
{
	return s.toStdWString();
}

static void sortDatasetsByTagid(std::vector<std::unique_ptr<imebra::DataSet>>& v, const imebra::tagId_t& tagId)
{
	std::vector<std::pair<std::wstring, imebra::DataSet*>> sorted{};
	std::transform(v.begin(), v.end(), std::back_inserter(sorted), [&](auto& data)
	{
		auto tag = readTag(data.get(), tagId);
		return std::make_pair(tag, data.release());
	});
	std::stable_sort(sorted.begin(), sorted.end(), [](auto const& l, auto const& r)
	{
		return l.first < r.first;
	});
	v.clear();
	for (auto& p : sorted)
	{
		v.emplace_back(p.second);
	}
}

static std::vector<ImebraImage> readFolder(const std::wstring& path)
{
	std::vector<std::wstring> files;
	for (auto const& entry : fs::recursive_directory_iterator(path))
		files.push_back(entry.path());

	std::vector<ImebraImage> result(files.size());
#pragma omp parallel for
	for (int i = 0; i < files.size(); i++)
	{
		try
		{
			result[i] = ImebraImage(std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(files[i])).get());
		}
		catch (...)
		{
		}
	}
	const auto it = std::remove_if(begin(result), end(result), [](ImebraImage const& img)
	{
		return !img.image;
	});
	result.resize(std::distance(begin(result), it));
	return result;
}

static QImage matToQImage(cv::Mat img)
{
	return QImage((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
}

static cv::Mat imebraToMat(ImebraImage const& input)
{
	auto const original = applyVoilutTransform(input);
	auto const blured = gauss(original);
	auto const thld = toZeroThreshold(blured);
	auto const edges = canny(thld);
	//removeUnwantedEdges(edges, original);
	auto result = cv::Mat{};
	hconcat(original, edges, result);
	return result;
}

static std::vector<ImebraImage> loadData(std::filesystem::path const& path)
{
	return [&]() -> std::vector<ImebraImage>
	{
		if (is_regular_file(path))
		{
			return {readFile(path)};
		}
		if (is_directory(path))
		{
			return readFolder(path);
		}
		return {};
	}();
}



static cv::Mat buildImage(cv::Mat original, CannySettings const& settings)
{
	
}