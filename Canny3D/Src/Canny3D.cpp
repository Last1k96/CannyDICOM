#include "Canny3D.h"

Canny3D::Canny3D(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

bool Canny3D::loadFiles(const QString& fileName)
{
	////QImageReader reader(fileName);
	////reader.setAutoTransform(true);
	//reader = DataSetReader(fileName.toStdWString());

	//if (reader.empty())
	//{
	//	QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
	//		tr("Cannot load %1: %2")
	//		.arg(QDir::toNativeSeparators(fileName),
	//			QString::fromStdString(reader.errorString())));
	//	return false;
	//}

	//updateImage();

	//setWindowFilePath(fileName);

	//const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
	//	.arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(
	//		image.depth());
	//statusBar()->showMessage(message);
	return true;
}
