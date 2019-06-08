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

void print(std::vector<std::wstring> const& v)
{
	for (auto const& s : v)
	{
		std::wcout << s << '\n';
	}
	std::cout << '\n';
}

int main(int argc, const char* argv[])
{
	std::vector<std::wstring> paths = {
		L"d:/DICOM/Panasenko/DICOM",
		L"d:/DICOM/Prohorov-after/DICOM/D201504/DD2409",
		L"d:/DICOM/Kalinin-before/DICOM",
		L"d:/DICOM/korotkov/DICOM/17020708/29510000",
		L"d:/DICOM/korotkov/DICOM/17020708/29510001",
		L"d:/DICOM/Krupin-before/DICOM/D201508/DD1014",
		L"d:/DICOM/Latishev-after1operation/DICOM",
		L"d:/DICOM/Latishev-after2operation-CBCT/Data",
		L"d:/DICOM/Lukin-after1operation/DICOM/D201111/DD1111",
		L"d:/DICOM/Lukin-after2operation/DICOM/D201211/DD1512"
	};

	//L"d:\\DICOM\\Kalinin-before\\DICOM\\00000";
	//union_tags_in_all_datasets();
	for (auto& path : paths)
	{
		auto vals = readFolder(path);
		print(different_values_of_tag(vals, imebra::tagId_t::StudyID_0020_0010));
	}


	//auto sets = readFolder(path);
}
