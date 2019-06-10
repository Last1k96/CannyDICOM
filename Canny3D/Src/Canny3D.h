#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Canny3D.h"
#include <qfiledialog.h>
#include <QLabel>
#include "Utility.h"
#include "DicomTreeItem.h"

struct MillimetersPerPixel;

class Canny3D : public QMainWindow
{
Q_OBJECT

public:
	Canny3D(QWidget* parent = Q_NULLPTR);
	std::vector<ImebraImage> loadFiles(const QString&);

	void addNewTab(QTreeWidgetItem* item, int column) const;

	void addNewTab3D(std::vector<cv::Mat> images, std::tuple<double, double, double> xyzInMillimeters,
	                 QString const& tabName) const;
	void updateTree(std::vector<ImebraImage>&& images);
	void adjustColumns(QModelIndex const& index);
	std::optional<std::vector<ImebraImage>> initiateOpenDialog(QString const& name, QFileDialog::FileMode type);

private slots:
	void open();
	void openFolder();

private:
	Ui::Canny3DClass ui;
};
