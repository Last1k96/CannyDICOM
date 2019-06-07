// imebra-test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <imebra/imebra.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include "DisplayImage.h"
#include <filesystem>

int main(int argc, const char* argv[])
{
	const std::wstring path = L"d:\\korotkov\\DICOM\\17020708\\29510000\\80509054.dcm";
	//L"d:\\DICOM\\Kalinin-before\\DICOM\\00000";

	auto diff = different_tag_values(*readFolder(L"d:/DICOM/Lukin-after2operation/DICOM/D201211/DD1512").front(),
	                                 *readFolder(L"d:/DICOM/Lukin-after1operation/DICOM/D201111/DD1111").front());

	for (auto const& tag : diff)
	{
		std::wcout << tag << '\n';
	}
}
