#pragma once
#include <QTreeWidgetItem>
#include "Utility.h"

class DicomTreeItem : public QTreeWidgetItem
{
	using It = std::vector<ImebraImage>::iterator;
public:
	std::vector<ImebraImage> const images;

	DicomTreeItem(QTreeWidgetItem* parent, It begin, It end);

};
