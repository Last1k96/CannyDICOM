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

// ageId = 4112

template <typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
std::wstring intToHex(const T& i)
{
	std::wstringstream stream;
	stream << std::setfill(L'0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}

std::wstring readTag(const imebra::DataSet* dataset, const imebra::tagId_t& tag)
{
	try
	{
		const auto tagId = imebra::TagId(tag);
		return imebra::DicomDictionary::getUnicodeTagName(tagId) + L" : " + dataset->getUnicodeString(tagId, 0);
	} catch (...)
	{
	}
	return {};
}



int main(int argc, const char* argv[])
{
	const std::wstring path = L"d:\\korotkov\\DICOM\\17020708\\29510000\\80509514.dcm";
	auto body = read_folder(L"d:\\korotkov\\DICOM\\17020708\\29510000");
	auto count = 0;
	const auto loadedDataSet = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path));

	auto tags = loadedDataSet->getTags();

	//auto count = 0;
	for (const auto& tag : tags)
	{
		auto buf = std::wstringstream{};
		try
		{
			const auto key = L"(" + intToHex(tag.getGroupId())
					+ L", " + intToHex(tag.getTagId()) + L")";
			buf << imebra::DicomDictionary::getUnicodeTagName(tag) << " : "
				<< loadedDataSet->getUnicodeString(tag, 0, L"");
			const auto val = buf.str();
			std::wcout << key << L"\t" << buf.str() << L'\n';
		}
		catch (...)
		{
		}
		count++;
	}
	std::wcout << L"size = " << count << L"\n";

	std::wstring patientNameCharacter = loadedDataSet->getUnicodeString(imebra::TagId(0x10, 0x10), 0);
	std::wstring patientName = loadedDataSet->getUnicodeString(imebra::TagId(imebra::tagId_t::PatientName_0010_0010), 0);

	std::wcout << readTag(loadedDataSet.get(), imebra::tagId_t::PatientName_0010_0010) << L'\n'
			   << readTag(loadedDataSet.get(), imebra::tagId_t::PatientID_0010_0020) << L'\n'
			   << readTag(loadedDataSet.get(), imebra::tagId_t::PatientBirthDate_0010_0030) << L'\n'
			   << readTag(loadedDataSet.get(), imebra::tagId_t::PatientSex_0010_0040) << L'\n'
			   << readTag(loadedDataSet.get(), imebra::tagId_t::PatientAge_0010_1010) << L'\n'
			   << readTag(loadedDataSet.get(), imebra::tagId_t::PatientWeight_0010_1030) << L'\n'
			   << readTag(loadedDataSet.get(), imebra::tagId_t::PatientAddress_0010_1040) << L'\n';
	
	
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
	//imebra::DataSet::setUnsignedLong(imebra::TagId(imebra::))
	cv::imshow("dcm", get_image(loadedDataSet.get()));
	cv::waitKey();
}
