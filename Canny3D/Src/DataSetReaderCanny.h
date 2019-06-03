#pragma once
#include <vector>
#include <QImage>
#include <opencv2/core/mat.hpp>
#include <filesystem>

class DataSetReader
{
	std::vector<cv::Mat> image_vec{};
	int cur_image_index{0};
	cv::Mat mimage{};
	QImage qimage{};
	std::string error{};

	void advance(int count);
	void update();

	static QImage mat_to_qimage(cv::Mat img);

public:
	DataSetReader() = default;
	DataSetReader(std::filesystem::path path);
	void next(int count);
	void prev(int count);
	QImage cur() const;
	bool empty() const;
	[[nodiscard]] std::string errorString() const;
};
