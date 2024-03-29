#pragma once
#include <vector>
#include <QImage>
#include <opencv2/core/mat.hpp>
#include <filesystem>
#include "DisplayImage.h"


class DataSetReader
{
	std::vector<ImebraImage> images{};
	int index{0};
	cv::Mat mimage{};
	QImage qimage{};
	std::string error{};

	void advance(int count);
	void update();

	static QImage matToQImage(cv::Mat img);

public:
	DataSetReader() = default;
	DataSetReader(std::filesystem::path path);
	void next(int count);
	void prev(int count);

	size_t size() const
	{
		return images.size();
	}

	QImage cur() const;
	bool empty() const;
	[[nodiscard]] std::string errorString() const;
};
