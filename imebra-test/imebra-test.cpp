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
	//const auto dataset_vector = read_folder(L"d:\\DICOM\\Kalinin-before\\DICOM");

	//std::wstring const path1 = L"d:/DICOM/Kalinin-before/DICOM/01234";

	//auto const set1 = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path1));
	//auto const diff = get_tags(*set1);
	//for (auto const& tag : diff)
	//{
	//	std::wcout << tag << '\n';
	//}
	//std::wcout << "end" << '\n';
	print_series_tag_union();

	return 0;
	const auto loadedDataSet = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path));

	auto tags = loadedDataSet->getTags();

	auto count = 0;
	auto buf = std::wstring{};
	for (const auto& tag : tags)
	{
		buf.clear();
		try
		{
			const auto key = L"(" + int_to_hex(tag.getGroupId())
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


	const auto image = std::unique_ptr<imebra::Image>(loadedDataSet->getImage(0));
	auto depth = image->getDepth();

	std::cout << "getChannelsNumber " << image->getChannelsNumber() << '\n'
		<< "getColorSpace " << image->getColorSpace() << '\n'
		//<< "getDepth " << image->getDepth() << '\n'
		<< "getHeight " << image->getHeight() << '\n'
		<< "getHeightMm " << image->getHeightMm() << '\n'
		<< "getWidth " << image->getWidth() << '\n'
		<< "getWidthMm " << image->getWidthMm() << '\n'
		<< "getHighBit " << image->getHighBit() << '\n';
	imshow("dcm", get_image(loadedDataSet.get()));
	cv::waitKey();
}
