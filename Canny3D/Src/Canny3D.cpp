#include "Canny3D.h"
#include <QFileDialog>
#include <QDialog>
#include <QImageReader>
#include <QImageWriter>
#include "DataSetReader.h"
#include <qmessagebox.h>
#include <QAction>
#include "Utility.h"

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
		reader.loadData(fileName.toStdWString());
	}
	catch (std::exception& e)
	{
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
			tr("Cannot load %1: %2")
			.arg(QDir::toNativeSeparators(fileName),
				QString::fromStdString(e.what())));
		return false;
	}

	updateImage();

	setWindowFilePath(fileName);

	const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
		.arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(
			image.depth());
	//statusBar()->showMessage(message);
	return true;
}


void Canny3D::updateImage()
{
	image = reader.cur();
	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->adjustSize();
}

void Canny3D::open()
{
	QFileDialog dialog(this, QString::fromWCharArray(L"Открыть файл"));

	static bool firstDialog = true;
	if (firstDialog)
	{
		firstDialog = false;
		dialog.setDirectory(QDir::currentPath());
	}

	while (dialog.exec() == QDialog::Accepted && !loadFiles(dialog.selectedFiles().first()))
	{
	}
}

void Canny3D::openFolder()
{
	QFileDialog dialog(this, QString::fromWCharArray(L"Открыть папку"));

	static bool firstDialog = true;
	if (firstDialog)
	{
		firstDialog = false;
		dialog.setDirectory(tr("d:/DICOM/Latishev-after1operation/DICOM"));
	}

	dialog.setFileMode(QFileDialog::Directory);

	while (dialog.exec() == QDialog::Accepted && !loadFiles(dialog.selectedFiles().first()))
	{
	}
}
