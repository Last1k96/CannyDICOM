#include "QtGuiDicomViewer.h"

#include "QtGuiDicomViewer.h"

#include <QtWidgets>
#include "DisplayImage.h"
#include "DataSetReader.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QtPrintSupport/QPrintDialog>
#endif
#endif

QtGuiDicomViewer::QtGuiDicomViewer(QWidget* parent)
	: QMainWindow(parent)
	  , cannyImage(new QLabel)
{
	cannyImage->setBackgroundRole(QPalette::Base);
	cannyImage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	cannyImage->setScaledContents(false);
	cannyImage->installEventFilter(this);

	setCentralWidget(cannyImage);

	createActions();

	resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

bool QtGuiDicomViewer::loadFiles(const QString& fileName)
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

void QtGuiDicomViewer::updateImage()
{
	image = reader.cur();
	cannyImage->setPixmap(QPixmap::fromImage(image));

	updateActions();

	cannyImage->adjustSize();
}

bool QtGuiDicomViewer::saveFile(const QString& fileName)
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
	//dialog.selectMimeTypeFilter("image/jpeg");
	if (acceptMode == QFileDialog::AcceptSave)
		dialog.setDefaultSuffix("jpg");
}

void QtGuiDicomViewer::open()
{
	QFileDialog dialog(this, tr("Open File"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

	while (dialog.exec() == QDialog::Accepted && !loadFiles(dialog.selectedFiles().first()))
	{
	}
}

void QtGuiDicomViewer::openFolder()
{
	// TODO change to c:/
	QString dir = QFileDialog::getExistingDirectory(nullptr, QObject::tr("Open Directory"),
	                                                "d:/DICOM/Lukin-after1operation/DICOM/D201111/DD1111",
	                                                QFileDialog::ShowDirsOnly
	                                                | QFileDialog::DontResolveSymlinks);
	if (dir.size() == 0) return;
	loadFiles(dir);
}

void QtGuiDicomViewer::saveAs()
{
	QFileDialog dialog(this, tr("Save File As"));
	initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

	while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first()))
	{
	}
}

void QtGuiDicomViewer::print()
{
	//
	//    Q_ASSERT(cannyImage->pixmap());
	//#if QT_CONFIG(printdialog)
	////! [6] //! [7]
	//    QPrintDialog dialog(&printer, this);
	////! [7] //! [8]
	//    if (dialog.exec()) {
	//        QPainter painter(&printer);
	//        QRect rect = painter.viewport();
	//        QSize size = cannyImage->pixmap()->size();
	//        size.scale(rect.size(), Qt::KeepAspectRatio);
	//        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
	//        painter.setWindow(cannyImage->pixmap()->rect());
	//        painter.drawPixmap(0, 0, *cannyImage->pixmap());
	//    }
	//#endif
}

void QtGuiDicomViewer::about()
{
	QMessageBox::about(this, tr("About Image Viewer"),
	                   tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
		                   "and QScrollArea to display an image-> QLabel is typically used "
		                   "for displaying a text, but it can also display an image-> "
		                   "QScrollArea provides a scrolling view around another widget. "
		                   "If the child widget exceeds the size of the frame, QScrollArea "
		                   "automatically provides scroll bars. </p><p>The example "
		                   "demonstrates how QLabel's ability to scale its contents "
		                   "(QLabel::scaledContents), and QScrollArea's ability to "
		                   "automatically resize its contents "
		                   "(QScrollArea::widgetResizable), can be used to implement "
		                   "zooming and scaling features. </p><p>In addition the example "
		                   "shows how to use QPainter to print an image-></p>"));
}

bool QtGuiDicomViewer::eventFilter(QObject* obj, QEvent* event)
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

void QtGuiDicomViewer::handleWheelEvent(QWheelEvent* e)
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
	//updateImage(mat_to_qimage(image_vec[cur_image_index]));
}

void QtGuiDicomViewer::createActions()
{
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

	QAction* openAct = fileMenu->addAction(tr("&Open..."), this, &QtGuiDicomViewer::open);
	openAct->setShortcut(QKeySequence::Open);

	QAction* openFolderAct = fileMenu->addAction(tr("Open &folder..."), this, &QtGuiDicomViewer::openFolder);

	//printAct = fileMenu->addAction(tr("&Print..."), this, &QtGuiDicomViewer::print);
	//printAct->setShortcut(QKeySequence::Print);
	//printAct->setEnabled(false);

	fileMenu->addSeparator();

	QAction* exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
	exitAct->setShortcut(tr("Ctrl+Q"));

	QMenu* viewMenu = menuBar()->addMenu(tr("&View"));

	//normalSizeAct = viewMenu->addAction(tr("&Normal Size"), this, &QtGuiDicomViewer::normalSize);
	//normalSizeAct->setShortcut(tr("Ctrl+S"));
	//normalSizeAct->setEnabled(false);

	viewMenu->addSeparator();

	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(tr("&About"), this, &QtGuiDicomViewer::about);
	helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

void QtGuiDicomViewer::updateActions() const
{
}
