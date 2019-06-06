#include "DicomViewer.h"

#include "DicomViewer.h"

#include <QtWidgets>
#include "Utility.h"
#include "DataSetReader.h"
#include "Utility.h"

DicomViewer::DicomViewer(QWidget* parent)
	: QLabel(parent)
	 , imageLabel(new QLabel)
{
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(false);
	imageLabel->installEventFilter(this);
}

void DicomViewer::updateImage(ImebraImage const& img)
{
	image = matToQImage(img.image);
	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->adjustSize();
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