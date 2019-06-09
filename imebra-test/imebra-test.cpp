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

	auto v = std::vector<int>{ 1, 2, 3, 4, 5 };
	auto it = v.begin() + 1;
	std::reverse(begin(v), end(v));
	std::cout << *it;
	return 0;

	std::vector<std::wstring> paths = {
		//L"d:/DICOM/Panasenko/DICOM",
		//L"d:/DICOM/Prohorov-after/DICOM/D201504/DD2409",
		//L"d:/DICOM/Kalinin-before/DICOM",
		L"d:/DICOM/korotkov/DICOM/17020708/29510000",
		//L"d:/DICOM/korotkov/DICOM/17020708/29510001",
		//L"d:/DICOM/Krupin-before/DICOM/D201508/DD1014",
		//L"d:/DICOM/Latishev-after1operation/DICOM",
		//L"d:/DICOM/Latishev-after2operation-CBCT/Data",
		//L"d:/DICOM/Lukin-after1operation/DICOM/D201111/DD1111",
		//L"d:/DICOM/Lukin-after2operation/DICOM/D201211/DD1512"
	};
	auto tag = imebra::tagId_t::StudyID_0020_0010;
	auto sets = readFolder(L"d:/DICOM/korotkov/DICOM/17020708/29510000");
	for (auto& set : sets)
	{
		static auto count = 0;
		std::wcout << count++ << " " << readTag(*set, tag) << '\n';
	}
	std::cout << std::endl;
	sets = readFolder(L"d:/DICOM/Panasenko/DICOM");
	for (auto& set : sets)
	{
		static auto count = 0;
		std::wcout << count++ << " " << readTag(*set, tag) << '\n';
	}
	std::cout << std::endl;
	sets = readFolder(L"d:/DICOM/Lukin-after1operation/DICOM/D201111/DD1111");
	for (auto& set : sets)
	{
		static auto count = 0;
		std::wcout << count++ << " " << readTag(*set, tag) << '\n';
	}

	//auto sets = readFolder(path);
}
