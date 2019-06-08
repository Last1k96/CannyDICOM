#include "DicomTreeItem.h"
#include <QTreeWidget>
#include <QObject>
#include "DicomViewer.h"
#include "Canny3D.h"
#include "QGLMeshViewer.h"

DicomTreeItem::DicomTreeItem(QTreeWidgetItem* parent, It begin, It end)
	: QTreeWidgetItem(parent)
	  , images(begin, end)
{
}

