#pragma once
#include <imebra/imebra.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <QImage>
#include <string>
#include <optional>
namespace fs = std::experimental::filesystem;

static void remove_gray_threshold(cv::Mat img, int threshold = 220)
{
	return;
	for (auto row = 0; row < img.rows; ++row)
	{
		for (auto col = 0; col < img.cols; ++col)
		{
			auto& x = img.at<uint8_t>(row, col);
			if (x < threshold) x = 0;
		}
	}
}

static void removeUnwantedEdges(cv::Mat canny, cv::Mat original, int threshold = 170)
{
	auto const radius = 2;
	for (auto row = radius; row < canny.rows - radius; ++row)
	{
		for (auto col = radius; col < canny.cols - radius; ++col)
		{
			auto& edgePixel = canny.at<uint8_t>(row, col);
			if (edgePixel == 0) continue;
			auto const to_remove = [&]
			{
				auto count = 0;
				for (auto mask_row = -radius; mask_row <= radius; ++mask_row)
				{
					for (auto mask_col = -radius; mask_col <= radius; ++mask_col)
					{
						auto const r = row + mask_row;
						auto const c = col + mask_col;
						if (original.at<uint8_t>(r, c) >= threshold)
							count++;
					}
				}
				// ���� ���������� ���� ��������� �������� ��������
				auto const area = (2 * radius + 1) * (2 * radius + 1);
				return count < 2 * radius;
			}();
			if (to_remove)
			{
				edgePixel = 0;
			}
		}
	}
}

static cv::Mat canny(cv::Mat img)
{
	cv::Mat blured;
	GaussianBlur(img, blured, cv::Size(3, 3), 1, 1);
	auto const thld = 100;
	Canny(blured, blured, thld, 180, 3, true);
	return blured;
}

static cv::Mat bytesToMat(std::vector<char>& bytes, const int width, const int height)
{
	auto mat = cv::Mat(height, width, CV_8UC4, &bytes[0]).clone();
	cv::Mat gray;
	cvtColor(mat, gray, cv::COLOR_RGBA2GRAY);
	return gray; // make a copy
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

	const auto bufferSize = draw.getBitmap(*data.image, 
		imebra::drawBitmapType_t::drawBitmapRGBA, 4, nullptr, 0);

	std::vector<char> buffer(bufferSize, 0);
	draw.getBitmap(*data.image, imebra::drawBitmapType_t::drawBitmapRGBA, 4,
	               reinterpret_cast<char*>(&buffer.at(0)), bufferSize);

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
