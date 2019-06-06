#include "Canny3D.h"
#include <QFileDialog>
#include <QDialog>
#include <QImageReader>
#include <QImageWriter>
#include <qmessagebox.h>
#include <QAction>
#include "Utility.h"
#include "DicomViewer.h"

Canny3D::Canny3D(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.openAction, &QAction::triggered, this, &Canny3D::open);
	connect(ui.openFolderAction, &QAction::triggered, this, &Canny3D::openFolder);
}

bool Canny3D::loadFiles(const QString& fileName)
{
	try {
		images = loadData(fileName.toStdWString());
	}
	catch (std::exception& e)
	{
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load %1: %2")
			.arg(QDir::toNativeSeparators(fileName),
				QString::fromStdString(e.what())));
		return false;
	}

	setWindowFilePath(fileName);

	return true;
}

void Canny3D::addNewTab() const
{
	auto tab = new QWidget();
	tab->setObjectName(QString::fromUtf8("tab"));
	auto layout = new QVBoxLayout(tab);
	layout->setSpacing(6);
	layout->setContentsMargins(11, 11, 11, 11);
	layout->setObjectName(QString::fromUtf8("verticalLayout"));
	auto viewer = new DicomViewer(tab, images);
	viewer->setObjectName(QString::fromUtf8("widget"));

	layout->addWidget(viewer);

	auto slider = new QSlider(tab);
	slider->setObjectName(QString::fromUtf8("horizontalSlider"));
	slider->setOrientation(Qt::Horizontal);

	layout->addWidget(slider);

	slider->setRange(0, images.size());
	connect(slider, &QSlider::valueChanged, viewer, &DicomViewer::selectImage);
	connect(viewer, &DicomViewer::imageChanged, slider, &QSlider::setValue);
	ui.tabWidget->addTab(tab, "Name");
}


bool Canny3D::initiateOpenDialog(QString const& dialogName, QFileDialog::FileMode dialogType)
{
	QFileDialog dialog(this, dialogName);

	static bool firstDialog = true;
	if (firstDialog)
	{
		firstDialog = false;
		//dialog.setDirectory(QDir::currentPath());
		dialog.setDirectory(tr("d:/DICOM/Latishev-after1operation/DICOM"));
	}

	dialog.setFileMode(dialogType);

	return (dialog.exec() == QDialog::Accepted) && loadFiles(dialog.selectedFiles().first());
}

void Canny3D::open()
{
	auto const success = initiateOpenDialog(QString::fromWCharArray(L"Открыть файл"), QFileDialog::AnyFile);
	if (!success) return;
	addNewTab();
}

void Canny3D::openFolder()
{
	auto const success = initiateOpenDialog(QString::fromWCharArray(L"Открыть папку"), QFileDialog::Directory);
	if (!success) return;
	addNewTab();
}
