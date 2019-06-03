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
	//auto const dataset_vector = read_folder(L"d:\\DICOM\\Kalinin-before\\DICOM");

	std::vector<std::wstring> paths = { 
		L"d:/DICOM/Panasenko/DICOM",
		L"d:/DICOM/Prohorov-after/DICOM/D201504/DD2409",
		L"d:/DICOM/Kalinin-before/DICOM",
		//L"d:/DICOM/korotkov/DICOM/17020708/29510000",
		//L"d:/DICOM/korotkov/DICOM/17020708/29510001",
		L"d:/DICOM/Krupin-before/DICOM/D201508/DD1014",
		L"d:/DICOM/Latishev-after1operation/DICOM",
		L"d:/DICOM/Latishev-after2operation-CBCT/Data",
		L"d:/DICOM/Lukin-after1operation/DICOM/D201111/DD1111",
		L"d:/DICOM/Lukin-after2operation/DICOM/D201211/DD1512" 
	};

	auto previous_set = std::set<std::wstring>{};
	auto union_difference = std::set<std::wstring>{};
	for (auto const& path : paths) {
		std::wcout << path << '\n';
		auto cur_sets = read_folder(path);
		auto current_union_diffference = std::set<std::wstring>{};
		for (auto const& dataset : cur_sets)
		{
			auto current_set = std::set<std::wstring>{};
			for (auto const& tag : dataset->getTags())
			{
				try {
					auto const tag_string = tag_to_wstring(tag);
					auto const tag_name = imebra::DicomDictionary::getUnicodeTagName(tag);
					//auto const tag_value = [&]
					//{
					//	return dataset->getUnicodeString(tag, 0, L"");
					//}();
					current_set.insert(tag_string + L"\t" + tag_name);
				} catch (...) {}
			}
			auto current_difference = std::set<std::wstring>{};
			
			std::set_intersection(previous_set.begin(), previous_set.end(),
				current_set.begin(), current_set.end(),
				std::inserter(current_difference, current_difference.end()));
			std::set_union(current_difference.begin(), current_difference.end(),
				union_difference.begin(), union_difference.end(),
				std::inserter(current_union_diffference, current_union_diffference.end()));

			previous_set = std::move(current_set);
		}
	}
	for (auto const& tag : union_difference)
	{
		std::wcout << tag << '\n';
	}
	std::wcout << "end" << "\n\n";

	return 0;
	auto const loadedDataSet = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path));

	auto tags = loadedDataSet->getTags();

	auto count = 0;
	auto buf = std::wstring{};
	for (auto const& tag : tags)
	{
		buf.clear();
		try
		{
			auto const key = L"(" + int_to_hex(tag.getGroupId())
				+ L", " + int_to_hex(tag.getTagId()) + L")";
			buf += imebra::DicomDictionary::getUnicodeTagName(tag) + L" : "
				+ loadedDataSet->getUnicodeString(tag, 0, L"");
			std::wcout << key << L"\t" << buf << L'\n';
		}
		catch (...)
		{
		}
	}

	std::wstring patientNameCharacter = loadedDataSet->getUnicodeString(imebra::TagId(0x10, 0x10), 0);
	std::wstring patientName = loadedDataSet->
		getUnicodeString(imebra::TagId(imebra::tagId_t::PatientName_0010_0010), 0);

	std::wcout << read_tag(*loadedDataSet, imebra::tagId_t::PatientName_0010_0010) << L'\n'
		<< read_tag(*loadedDataSet, imebra::tagId_t::PatientID_0010_0020) << L'\n'
		<< read_tag(*loadedDataSet, imebra::tagId_t::PatientBirthDate_0010_0030) << L'\n'
		<< read_tag(*loadedDataSet, imebra::tagId_t::PatientSex_0010_0040) << L'\n'
		<< read_tag(*loadedDataSet, imebra::tagId_t::PatientAge_0010_1010) << L'\n'
		<< read_tag(*loadedDataSet, imebra::tagId_t::PatientWeight_0010_1030) << L'\n'
		<< read_tag(*loadedDataSet, imebra::tagId_t::PatientAddress_0010_1040) << L'\n';


	auto const image = std::unique_ptr<imebra::Image>(loadedDataSet->getImage(0));
	auto depth = image->getDepth();

	std::cout << "getChannelsNumber " << image->getChannelsNumber() << '\n'
		<< "getColorSpace " << image->getColorSpace() << '\n'
		//<< "getDepth " << qimage->getDepth() << '\n'
		<< "getHeight " << image->getHeight() << '\n'
		<< "getHeightMm " << image->getHeightMm() << '\n'
		<< "getWidth " << image->getWidth() << '\n'
		<< "getWidthMm " << image->getWidthMm() << '\n'
		<< "getHighBit " << image->getHighBit() << '\n';
	imshow("dcm", get_image(loadedDataSet.get()));
	cv::waitKey();
}
