#pragma once
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

static std::wstring sv(const QString& s)
{
	return s.toStdWString();
}