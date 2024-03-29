#include "DataSetReader.h"
#include <opencv2/opencv.hpp>
#include "DisplayImage.h"

QImage DataSetReader::matToQImage(cv::Mat img)
{
	return QImage((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
}


void DataSetReader::advance(int const count)
{
	index = (index + images.size() + count) % images.size();
}

void DataSetReader::update()
{
	advance(0);
}

DataSetReader::DataSetReader(std::filesystem::path path)
{
	images.clear();
	try
	{
		if (is_regular_file(path))
		{
			images.push_back(getImage(readFile(path).get()));
		}
		else if (is_directory(path))
		{
			images = datasetToImages(readFolder(path));
		}

		if (images.empty())
		{
			throw std::runtime_error("�� ������� ��������� ����.");
		}
		update();
	}
	catch (std::exception& e)
	{
		error = e.what();
	}
}

void DataSetReader::next(int const count = 1)
{
	advance(count);
}

void DataSetReader::prev(int const count = 1)
{
	advance(-count);
}

QImage DataSetReader::cur() const
{
	auto const original = applyVoilutTransform(images[index]);
	auto const edges = canny(original);
	removeUnwantedEdges(edges, original);
	auto result = cv::Mat{};
	hconcat(original, edges, result);
	return matToQImage(result);
}

bool DataSetReader::empty() const
{
	return images.empty();
}

std::string DataSetReader::errorString() const
{
	return error;
}
