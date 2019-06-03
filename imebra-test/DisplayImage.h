#pragma once
#include <imebra/imebra.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
namespace fs = std::filesystem;

static cv::Mat bytes_to_mat(std::vector<char> bytes, const int width, const int height)
{
	return cv::Mat(height, width, CV_8UC4, &bytes[0]).clone(); // make a copy
}

template <typename T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
std::wstring int_to_hex(const T& i)
{
	std::wstringstream stream;
	stream << std::setfill(L'0') << std::setw(sizeof(T) * 2)
		<< std::hex << i;
	return stream.str();
}

std::wstring tag_to_wstring(const imebra::TagId& tag)
{
	return L"(" + int_to_hex(tag.getGroupId()) + L", " + int_to_hex(tag.getTagId()) + L")";
}

static std::wstring read_tag(const imebra::DataSet& dataset, const imebra::TagId& tagId)
{
	try { return imebra::DicomDictionary::getUnicodeTagName(tagId) + L" : " + dataset.getUnicodeString(tagId, 0); }
	catch (...)
	{
	}
	return {};
}

static std::wstring read_tag(const imebra::DataSet& dataset, const imebra::tagId_t& tag)
{
	try { return read_tag(dataset, imebra::TagId(tag)); }
	catch (...)
	{
	}
	return {};
}

static cv::Mat get_image(imebra::DataSet* loadedDataSet)
{
	// Retrieve the first qimage (index = 0)
	std::unique_ptr<imebra::Image> image(loadedDataSet->getImageApplyModalityTransform(0));

	// Get the color space
	std::string colorSpace = image->getColorSpace();

	// Get the size in pixels

	const auto width = image->getWidth();
	const auto height = image->getHeight();

	// The transforms chain will contain all the transform that we want to
	// apply to the qimage before displaying it
	imebra::TransformsChain chain;

	if (imebra::ColorTransformsFactory::isMonochrome(colorSpace))
	{
		// Allocate a VOILUT transform. If the DataSet does not contain any pre-defined
		//  settings then we will find the optimal ones.
		imebra::VOILUT voilutTransform;

		// Retrieve the VOIs (center/width pairs)
		imebra::vois_t vois = loadedDataSet->getVOIs();

		// Retrieve the LUTs
		std::vector<std::unique_ptr<imebra::LUT>> luts;
		for (size_t scanLUTs(0); ; ++scanLUTs)
		{
			try
			{
				luts.emplace_back(
					loadedDataSet->getLUT(imebra::TagId(imebra::tagId_t::VOILUTSequence_0028_3010), scanLUTs));
			}
			catch (const imebra::MissingDataElementError&)
			{
				break;
			}
		}

		if (!vois.empty())
		{
			voilutTransform.setCenterWidth(vois[0].center, vois[0].width);
		}
		else if (!luts.empty())
		{
			voilutTransform.setLUT(*(luts.front().get()));
		}
		else
		{
			voilutTransform.applyOptimalVOI(*image, 0, 0, width, height);
		}

		chain.addTransform(voilutTransform);
	}

	// If the qimage is monochromatic then now chain contains the VOILUT transform
	// We create a DrawBitmap that always apply the chain transform before getting the RGB qimage
	imebra::DrawBitmap draw{chain};

	// Ask for the size of the buffer (in bytes)
	const size_t requestedBufferSize = draw.getBitmap(*image, imebra::drawBitmapType_t::drawBitmapRGBA, 4, nullptr, 0);

	// Now we allocate the buffer and then ask DrawBitmap to fill it
	std::vector<char> buffer(requestedBufferSize, 0);
	draw.getBitmap(*image, imebra::drawBitmapType_t::drawBitmapRGBA, 4, reinterpret_cast<char*>(&(buffer.at(0))),
	               requestedBufferSize);
	auto mat = bytes_to_mat(buffer, width, height);
	if (mat.empty())
	{
		std::cout << "Can't open an qimage\n";
		std::cin.get();
		return {};
	}
	return mat;
}

static void sort_by_instance_number(std::vector<std::unique_ptr<imebra::DataSet>>& v)
{
	auto sorted = std::vector<std::pair<std::wstring, imebra::DataSet*>>{};
	std::transform(v.begin(), v.end(), std::back_inserter(sorted), [&](auto& data)
	{
		auto tag = read_tag(*data, imebra::tagId_t::InstanceNumber_0020_0013);
		return std::make_pair(tag, data.release());
	});
	std::stable_sort(sorted.begin(), sorted.end(), [](const auto& l, const auto& r)
	{
		return l.first < r.first;
	});
	v.clear();
	for (auto& p : sorted)
	{
		v.emplace_back(p.second);
	}
}


static std::vector<std::unique_ptr<imebra::DataSet>> read_folder(const std::wstring& path)
{
	std::vector<std::unique_ptr<imebra::DataSet>> dicom_dataset{};

	for (const auto& entry : fs::directory_iterator(path))
	{
		try
		{
			dicom_dataset.emplace_back(imebra::CodecFactory::load(entry.path()));
		}
		catch (...)
		{
		}
	}
	sort_by_instance_number(dicom_dataset);

	return dicom_dataset;
}

static void display_folder(std::wstring const& path)
{
	auto const sets = read_folder(path);
	for (auto const& set : sets)
	{
	}
}

//static std::vector<cv::Mat> read_folder(const std::wstirng& path)
//{
//	std::vector<std::unique_ptr<imebra::DataSet>> dicom_dataset{};
//	for (const auto& entry : fs::directory_iterator(path))
//	{
//		try
//		{
//			dicom_dataset.emplace_back(imebra::CodecFactory::load(entry.path()));
//		}
//		catch (...)
//		{
//		}
//	}
//
//
//	std::vector<cv::Mat> result{};
//	std::transform(dicom_dataset.begin(), dicom_dataset.end(), std::back_inserter(result), [&](auto& data)
//	{
//		return get_image(data.get());;
//	});
//	return result;
//}

static std::vector<cv::Mat> dataset_to_images(const std::vector<std::unique_ptr<imebra::DataSet>>& set)
{
	auto result = std::vector<cv::Mat>{};
	result.reserve(set.size());

	std::transform(set.begin(), set.end(), std::back_inserter(result), [&](const auto& dataset)
	{
		return get_image(dataset.get());
	});

	return result;
}

namespace std
{
	template <>
	struct less<imebra::TagId>
	{
		bool operator()(const imebra::TagId& lhs, const imebra::TagId& rhs) const
		{
			return lhs.getGroupId() < rhs.getGroupId() &&
				lhs.getGroupOrder() < rhs.getGroupOrder() &&
				lhs.getTagId() < rhs.getTagId();
		}
	};
}

[[nodiscard]]
static std::set<std::wstring> get_tags_union(const std::vector<imebra::DataSet*>& datasets)
{
	auto previous_set = std::set<std::wstring>{};
	auto union_difference = std::set<std::wstring>{};
	for (const auto& dataset : datasets)
	{
		auto current_set = std::set<std::wstring>{};
		for (const auto& tag : dataset->getTags())
		{
			const auto tag_string = tag_to_wstring(tag);
			const auto tag_value = [&]
			{
				return dataset->getUnicodeString(tag, 0, L"");
			}();
			current_set.insert(tag_string + L"\t" + tag_value);
		}
		auto current_difference = std::set<std::wstring>{};

		std::set_symmetric_difference(previous_set.begin(), previous_set.end(),
		                              current_set.begin(), current_set.end(),
		                              std::inserter(current_difference, current_difference.end()));
		std::set_union(current_difference.begin(), current_difference.end(),
		               union_difference.begin(), union_difference.end(),
		               std::inserter(union_difference, union_difference.end()));
	}
	return union_difference;
}

std::vector<std::wstring> get_tags(const imebra::DataSet& dataset)
{
	const auto tags = dataset.getTags();
	auto tag_names = std::vector<std::wstring>{};
	tag_names.reserve(tags.size());
	std::transform(tags.begin(), tags.end(), std::back_inserter(tag_names), [&](const imebra::TagId& tag)
	{
		return tag_to_wstring(tag) + L" " + read_tag(dataset, tag);
	});
	return tag_names;
}

std::set<std::wstring> different_tag_values(const imebra::DataSet& set1, const imebra::DataSet& set2)
{
	auto different_values = std::set<std::wstring>{};
	const auto tags1 = get_tags(set1);
	const auto tags2 = get_tags(set2);
	std::set_symmetric_difference(tags1.begin(), tags1.end(), tags2.begin(), tags2.end(),
	                              std::inserter(different_values, different_values.end()));
	return different_values;
}

static void print_series_tag_difference()
{
	std::wstring const path1 = L"d:\\DICOM\\Kalinin-before\\DICOM\\00000";
	std::wstring const path2 = L"d:\\DICOM\\Kalinin-before\\DICOM\\00617";
	//	std::wstring const path1 = L"d:\\korotkov\\DICOM\\17020708\\29510000\\80520630.dcm";
	//	std::wstring const path2 = L"d:\\korotkov\\DICOM\\17020708\\29510000\\80529459.dcm";
	auto const set1 = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path1));
	auto const set2 = std::unique_ptr<imebra::DataSet>(imebra::CodecFactory::load(path2));
	auto const diff = different_tag_values(*set1, *set2);
	for (auto const& tag : diff)
	{
		std::wcout << tag << '\n';
	}
}

static void print_series_tag_union()
{
	std::wstring const path1 = L"d:\\DICOM\\Kalinin-before\\DICOM\\00000";
	std::wstring const path2 = L"d:\\DICOM\\Kalinin-before\\DICOM\\00617";
	//	std::wstring const path1 = L"d:\\korotkov\\DICOM\\17020708\\29510000\\80520630.dcm";
	//	std::wstring const path2 = L"d:\\korotkov\\DICOM\\17020708\\29510000\\80529459.dcm";
	auto set1 = imebra::CodecFactory::load(path1);
	auto set2 = imebra::CodecFactory::load(path2);

	auto const diff = get_tags_union({set1, set2});
	for (auto const& tag : diff)
	{
		std::wcout << tag << '\n';
	}
}
