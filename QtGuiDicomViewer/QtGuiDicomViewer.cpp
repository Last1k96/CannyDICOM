#include "DicomViewer.h"

#include "DicomViewer.h"

#include <QtWidgets>
#include "DisplayImage.h"
#include "DataSetReader.h"

DicomViewer::DicomViewer(QWidget* parent)
	: QMainWindow(parent)
	  , imageLabel(new QLabel)
{
	QWidget w{};
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(false);
	imageLabel->installEventFilter(this);

	setCentralWidget(imageLabel);

	createActions();

	resize(QGuiApplication::primaryScreen()->availableSize() * 4 / 5);
}

bool DicomViewer::loadFiles(const QString& fileName)
{
	//QImageReader reader(fileName);
	//reader.setAutoTransform(true);
	reader = DataSetReader(fileName.toStdWString());

	if (reader.empty())
	{
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
		                         tr("Cannot load %1: %2")
		                         .arg(QDir::toNativeSeparators(fileName),
		                              QString::fromStdString(reader.errorString())));
		return false;
	}

	updateImage();

	setWindowFilePath(fileName);

	const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
	                        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(
		                        image.depth());
	statusBar()->showMessage(message);
	return true;
}

void DicomViewer::updateImage()
{
	image = reader.cur();
	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->adjustSize();
}

bool DicomViewer::saveFile(const QString& fileName)
{
	QImageWriter writer(fileName);

	if (!writer.write(image))
	{
		QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
		                         tr("Cannot write %1: %2")
		                         .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
		return false;
	}
	const QString message = tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName));
	statusBar()->showMessage(message);
	return true;
}

static void initializeImageFileDialog(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode)
{
	/*QString dir = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Open Directory"),
		"c:\\",
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);*/


	static bool firstDialog = true;

	if (firstDialog)
	{
		firstDialog = false;
		dialog.setDirectory(QDir::currentPath());
	}

	QStringList mimeTypeFilters;
	const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
		                                          ? QImageReader::supportedMimeTypes()
		                                          : QImageWriter::supportedMimeTypes();
	foreach(const QByteArray &mimeTypeName, supportedMimeTypes)
		mimeTypeFilters.append(mimeTypeName);
	mimeTypeFilters.sort();
	//dialog.setMimeTypeFilters(mimeTypeFilters);
	//dialog.selectMimeTypeFilter("qimage/jpeg");
	if (acceptMode == QFileDialog::AcceptSave)
		dialog.setDefaultSuffix("jpg");
}

void DicomViewer::open()
{
	QFileDialog dialog(this, tr("Open File"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

	while (dialog.exec() == QDialog::Accepted && !loadFiles(dialog.selectedFiles().first()))
	{
	}
}

void DicomViewer::openFolder()
{
	// TODO change to c:/
	QString dir = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Open Directory"),
	                                                "d:/DICOM/Latishev-after1operation/DICOM",
	                                                QFileDialog::ShowDirsOnly
	                                                | QFileDialog::DontResolveSymlinks);
	if (dir.size() == 0) return;
	loadFiles(dir);
}

void DicomViewer::saveAs()
{
	QFileDialog dialog(this, tr("Save File As"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

	while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first()))
	{
	}
}

void DicomViewer::about()
{
	QMessageBox::about(this, tr("About Image Viewer"),
	                   tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
		                   "and QScrollArea to display an qimage-> QLabel is typically used "
		                   "for displaying a text, but it can also display an qimage-> "
		                   "QScrollArea provides a scrolling view around another widget. "
		                   "If the child widget exceeds the size of the frame, QScrollArea "
		                   "automatically provides scroll bars. </p><p>The example "
		                   "demonstrates how QLabel's ability to scale its contents "
		                   "(QLabel::scaledContents), and QScrollArea's ability to "
		                   "automatically resize its contents "
		                   "(QScrollArea::widgetResizable), can be used to implement "
		                   "zooming and scaling features. </p><p>In addition the example "
		                   "shows how to use QPainter to print an qimage-></p>"));
}

bool DicomViewer::eventFilter(QObject* obj, QEvent* event)
{
	if (event->type() == QEvent::Wheel)
	{
		handleWheelEvent(dynamic_cast<QWheelEvent*>(event));

		// Don't propagate
		event->accept();
		return true;
	}
	return false;
}

void DicomViewer::handleWheelEvent(QWheelEvent* e)
{
	const int k = ceil(abs(e->delta()) / 120);
	if (e->delta() > 0)
	{
		reader.prev(k);
	}
	else
	{
		reader.next(k);
	}
	updateImage();
	//updateImage(matToQImage(images[index]));
}

void DicomViewer::createActions()
{
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

	QAction* openAct = fileMenu->addAction(tr("&Open..."), this, &DicomViewer::open);
	openAct->setShortcut(QKeySequence::Open);

	QAction* openFolderAct = fileMenu->addAction(tr("Open &folder..."), this, &DicomViewer::openFolder);

	//printAct = fileMenu->addAction(tr("&Print..."), this, &DicomViewer::print);
	//printAct->setShortcut(QKeySequence::Print);
	//printAct->setEnabled(false);

	fileMenu->addSeparator();

	QAction* exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
	exitAct->setShortcut(tr("Ctrl+Q"));

	QMenu* viewMenu = menuBar()->addMenu(tr("&View"));

	//normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &DicomViewer::normalSize);
	//normalSizeAct->setShortcut(tr("Ctrl+S"));
	//normalSizeAct->setEnabled(false);

	viewMenu->addSeparator();

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(tr("&About"), this, &DicomViewer::about);
	helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}
