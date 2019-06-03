#include "DataSetReader.h"
#include <opencv2/opencv.hpp>
#include "DisplayImage.h"

QImage DataSetReader::mat_to_qimage(cv::Mat img)
{
	return QImage((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
}


void DataSetReader::advance(int const count)
{
	cur_image_index = (cur_image_index + image_vec.size() + count) % image_vec.size();
	auto const original = image_vec[cur_image_index];
	auto const edges = canny(original);
	remove_unwanted_edges(edges, original);
	cv::hconcat(original, edges, mimage);
	qimage = mat_to_qimage(mimage);
}

void DataSetReader::update()
{
	advance(0);
}

DataSetReader::DataSetReader(std::filesystem::path path)
{
	image_vec.clear();
	try
	{
		if (is_regular_file(path))
		{
			image_vec.push_back(read_file(path));
		}
		else if (is_directory(path))
		{
			image_vec = dataset_to_images(read_folder(path));
		}

		if (image_vec.empty())
		{
			throw std::runtime_error("Не удалось прочитать файл.");
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
	return qimage;
}

bool DataSetReader::empty() const
{
	return image_vec.empty();
}

std::string DataSetReader::errorString() const
{
	return error;
}
