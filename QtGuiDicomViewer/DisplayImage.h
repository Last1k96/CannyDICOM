#pragma once
#include <imebra/imebra.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <QImage>
#include <string>
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

static void remove_unwanted_edges(cv::Mat canny, cv::Mat original, int threshold = 170)
{
	auto const radius = 2;
	for (auto row = radius; row < canny.rows - radius; ++row)
	{
		for (auto col = radius; col < canny.cols - radius; ++col)
		{
			auto& edge_pixel = canny.at<uint8_t>(row, col);
			if (edge_pixel == 0) continue;
			auto const to_remove = [&] {
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
				// если поблизости есть несколько полезных пикселей
				auto const area = (2 * radius + 1) * (2 * radius + 1);
				return count < 2 * radius;
			}();
			if (to_remove)
			{
				edge_pixel = 0;
			}
		}
	}
}

static cv::Mat canny(cv::Mat img)
{
	cv::Mat blured;
	GaussianBlur(img, blured, cv::Size(3, 3), 1, 1);
	const auto thld = 100;
	Canny(blured, blured, thld, 180, 3, true);
	return blured;
}

static cv::Mat bytes_to_mat(std::vector<char>& bytes, const int width, const int height)
{
	auto mat = cv::Mat(height, width, CV_8UC4, &bytes[0]).clone();
	cv::Mat gray;
	cvtColor(mat, gray, cv::COLOR_RGBA2GRAY);
	return gray; // make a copy
}

static int32_t read_tag(const imebra::DataSet* dataset, const imebra::tagId_t& tag)
{
	try
	{
		const auto tagId = imebra::TagId(tag);
		return dataset->getSignedLong(tagId, 0);
	}
	catch (...)
	{
	}
	return {};
}

static cv::Mat get_image(imebra::DataSet* loadedDataSet)
{
	std::unique_ptr<imebra::Image> image(loadedDataSet->getImageApplyModalityTransform(0));
	std::string colorSpace = image->getColorSpace();
	const auto width = image->getWidth();
	const auto height = image->getHeight();
	imebra::TransformsChain chain;

	if (imebra::ColorTransformsFactory::isMonochrome(colorSpace))
	{
		imebra::VOILUT voilutTransform;
		imebra::vois_t vois = loadedDataSet->getVOIs();
		std::vector<std::unique_ptr<imebra::LUT>> luts;
		//for (size_t scanLUTs(0); ; ++scanLUTs)
		//{
		//	try
		//	{
		//		luts.emplace_back(
		//			loadedDataSet->getLUT(imebra::TagId(imebra::tagId_t::VOILUTSequence_0028_3010), scanLUTs));
		//	}
		//	catch (const imebra::MissingDataElementError&)
		//	{
		//		break;
		//	}
		//}

		if (!vois.empty())
		{
			voilutTransform.setCenterWidth(vois[0].center, vois[0].width);
		}
			//else if (!luts.empty())
			//{
			//	voilutTransform.setLUT(*(luts.front().get()));
			//}
		else
		{
			voilutTransform.applyOptimalVOI(*image, 0, 0, width, height);
		}
		//voilutTransform.setCenterWidth(300, 1500);
		chain.addTransform(voilutTransform);
	}

	imebra::DrawBitmap draw{chain};
	
	// Ask for the size of the buffer (in bytes)
	const size_t requestedBufferSize = draw.getBitmap(*image, imebra::drawBitmapType_t::drawBitmapRGBA, 4, nullptr, 0);
	
	// Now we allocate the buffer and then ask DrawBitmap to fill it
	std::vector<char> buffer(requestedBufferSize, 0);
	draw.getBitmap(*image, imebra::drawBitmapType_t::drawBitmapRGBA, 4,
	               reinterpret_cast<char*>(&buffer.at(0)), requestedBufferSize);
	auto mat = bytes_to_mat(buffer, width, height);
	if (mat.empty())
	{
		std::cout << "Can't open an qimage\n";
		std::cin.get();
		return {};
	}
	//remove_gray_threshold(mat);
	return mat;
}

static cv::Mat read_file(const std::wstring& path)
{
	const auto loaded_dataset = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path));
	return get_image(loaded_dataset.get());
}

static std::wstring sv(const QString& s)
{
	return s.toStdWString();
}

static void sort_datasets_by_tagid(std::vector<std::unique_ptr<imebra::DataSet>>& v, const imebra::tagId_t& tagId)
{
	std::vector<std::pair<int32_t, imebra::DataSet*>> sorted{};
	std::transform(v.begin(), v.end(), std::back_inserter(sorted), [&](auto& data)
	{
		auto tag = read_tag(data.get(), tagId);
		return std::make_pair(tag, data.release());
	});
	std::stable_sort(sorted.begin(), sorted.end(), [](const auto& l, const auto& r)
	{
		return l.first < r.first;
	});
	v.clear();
	for (auto& p : sorted)
	{
		v.emplace_back(p.second);
	}
}


//static std::vector<cv::Mat> read_folder(std::wstring_view path)
//{
//	std::vector<std::unique_ptr<imebra::DataSet>> dicom_dataset{};
//	for (const auto& entry : fs::directory_iterator(path))
//	{
//		try
//		{
//			dicom_dataset.emplace_back(imebra::CodecFactory::load(entry.path()));
//		}
//		catch (...)
//		{
//		}
//	}
//
//	//sort_datasets_by_tagid(dicom_dataset);
//	//sort_by_series_number(dicom_dataset);
//
//
//	std::vector<cv::Mat> result{};
//	std::transform(dicom_dataset.begin(), dicom_dataset.end(), std::back_inserter(result), [&](auto& data)
//	{
//		return get_image(data.get());;
//	});
//	return result;
//}

//(0008, 1030)    Study Description : Thorax^Thorax_STANDART (Adult)
//(0008, 0060)    Modality : CT
//Thorax^Thorax_STANDART (Adult)(CT: 4 series)	

//(0008, 103e)    Series Description : ThorCombi  0.75  B41s
struct image_serie
{
	std::wstring description{};
	std::vector<imebra::DataSet> images{};
};

static std::vector<std::unique_ptr<imebra::DataSet>> read_folder(const std::wstring& path)
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
	//sort_datasets_by_tagid(dicom_dataset, imebra::tagId_t::SeriesNumber_0020_0011);
	//sort_datasets_by_tagid(dicom_dataset, imebra::tagId_t::ConvolutionKernel_0018_1210);
	//sort_datasets_by_tagid(dicom_dataset, imebra::tagId_t::SliceLocation_0020_1041);
	//sort_datasets_by_tagid(dicom_dataset, imebra::tagId_t::SeriesTime_0008_0031);
	//sort_datasets_by_tagid(dicom_dataset, imebra::tagId_t::SeriesDate_0008_0021);
	sort_datasets_by_tagid(dicom_dataset, imebra::tagId_t::SeriesInstanceUID_0020_000E);


	return dicom_dataset;
}

static std::vector<cv::Mat> dataset_to_images(const std::vector<std::unique_ptr<imebra::DataSet>>& set)
{
	auto result = std::vector<cv::Mat>{};
	result.reserve(set.size());

	std::transform(set.begin(), set.end(), std::back_inserter(result),
	               [&](const auto& dataset)
	               {
		               return get_image(dataset.get());
	               });

	return result;
}
