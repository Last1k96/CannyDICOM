#pragma once
#include <imebra/imebra.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <QImage>
#include <string>
#include <optional>
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
	cv::threshold(img, result, 180, 255, cv::THRESH_TOZERO);
	return result;
}

static std::pair<int, int> otsuThreshold(cv::Mat img)
{
	cv::Mat out;
	double threshold = cv::threshold(
		img, out, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU
	);

	return { 0.5 * threshold, threshold };
}

static cv::Mat canny(cv::Mat img, std::optional<std::pair<int, int>> threshold = {})
{
	cv::Mat edges;
	auto const thld = 100;
	cv::Canny(img, edges, thld, 180, 3, true);
	return edges;
}

static cv::Mat bytesToMat(std::vector<char>& bytes, const int width, const int height)
{
	const auto mat = cv::Mat(height, width, CV_8UC4, &bytes[0]).clone();
	cv::Mat gray;
	cvtColor(mat, gray, cv::COLOR_RGBA2GRAY);
	return gray;
}

static int32_t readTag(const imebra::DataSet* dataset, const imebra::tagId_t& tag)
{
	try
	{
		auto const tagId = imebra::TagId(tag);
		return dataset->getSignedLong(tagId, 0);
	}
	catch (...)
	{
	}
	return {};
}

struct VOI
{
	double center;
	double width;
};

struct ImebraImage
{
	std::shared_ptr<imebra::Image const> image{};
	std::optional<VOI> voi;
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

	return bytesToMat(buffer, width, height);;
}

static ImebraImage getImage(imebra::DataSet* loadedDataSet)
{
	ImebraImage result;
	result.image = std::shared_ptr<imebra::Image>(loadedDataSet->getImage(0));
	if (!imebra::ColorTransformsFactory::isMonochrome(result.image->getColorSpace()))
	{
		throw std::runtime_error("Image must be monochrome.");
	}

	auto vois = loadedDataSet->getVOIs();
	if (!vois.empty())
	{
		result.voi = VOI{vois[0].center, vois[0].width};
	}

	return result;
}

static std::unique_ptr<imebra::DataSet> readFile(const std::wstring& path)
{
	return std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path));
}

static std::wstring sv(const QString& s)
{
	return s.toStdWString();
}

static void sortDatasetsByTagid(std::vector<std::unique_ptr<imebra::DataSet>>& v, const imebra::tagId_t& tagId)
{
	std::vector<std::pair<int32_t, imebra::DataSet*>> sorted{};
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

static std::vector<std::unique_ptr<imebra::DataSet>> readFolder(const std::wstring& path)
{
	std::vector<std::unique_ptr<imebra::DataSet>> dicom_dataset{};

	for (auto const& entry : fs::directory_iterator(path))
	{
		try
		{
			dicom_dataset.emplace_back(imebra::CodecFactory::load(entry.path()));
		}
		catch (...)
		{
		}
	}
	sortDatasetsByTagid(dicom_dataset, imebra::tagId_t::SeriesNumber_0020_0011);
	//sortDatasetsByTagid(dicom_dataset, imebra::tagId_t::ConvolutionKernel_0018_1210);
	//sortDatasetsByTagid(dicom_dataset, imebra::tagId_t::SliceLocation_0020_1041);
	//sortDatasetsByTagid(dicom_dataset, imebra::tagId_t::SeriesTime_0008_0031);
	//sortDatasetsByTagid(dicom_dataset, imebra::tagId_t::SeriesDate_0008_0021);


	return dicom_dataset;
}

static std::vector<ImebraImage> datasetToImages(const std::vector<std::unique_ptr<imebra::DataSet>>& set)
{
	auto result = std::vector<ImebraImage>{};
	result.reserve(set.size());

	std::transform(set.begin(), set.end(), std::back_inserter(result),
	               [&](auto const& dataset)
	               {
		               return getImage(dataset.get());
	               });

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
	auto images = std::vector<ImebraImage>{};

	if (is_regular_file(path))
	{
		images.push_back(getImage(readFile(path).get()));
	}
	else if (is_directory(path))
	{
		images = datasetToImages(readFolder(path));
	}

	return images;
}