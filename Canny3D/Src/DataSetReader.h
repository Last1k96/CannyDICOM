#pragma once
#include <vector>
#include <QImage>
#include <QWidget>
#include <opencv2/core/mat.hpp>
#include <filesystem>
#include "DisplayImage.h"

class DataSetReader : public QObject
{
	Q_OBJECT

	std::vector<ImebraImage> images{};
	int index{0};

	void advance(int count);
	void update();

	static QImage matToQImage(cv::Mat img);

public:
	void loadData(std::filesystem::path const& path);
	void next(int count);
	void prev(int count);
	[[nodiscard]] QImage cur() const;
	[[nodiscard]] bool empty() const;
};
