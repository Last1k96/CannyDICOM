#include "DicomViewer.h"
#include <QWidget>
#include <utility>
#include "Utility.h"

DicomViewer::DicomViewer(QWidget* parent, std::vector<ImebraImage> const& data)
	: QLabel(parent)
	  , images(data)
{
	this->setBackgroundRole(QPalette::Base);
	this->setMinimumSize(1, 1);
	this->setScaledContents(true);
	this->installEventFilter(this);
	updateImage();
}

void DicomViewer::updateImage()
{
	if (images.empty()) return;
	currentImage = computeImage();
	setPixmap(QPixmap::fromImage(matToQImage(currentImage)));
}

size_t DicomViewer::imageCount() const
{
	return images.size();
}

size_t DicomViewer::index() const
{
	return idx;
}

bool DicomViewer::selectImage(int index)
{
	if (index < 0 || index >= images.size())
		return false;
	idx = index;
	updateImage();
	emit imageChanged(index);
	return true;
}

cv::Mat DicomViewer::computeImage()
{
	return imebraToMat(images[idx]);
}

void DicomViewer::setPixmap(const QPixmap& pm)
{
	pixmapWidth = pm.width();
	pixmapHeight = pm.height();

	updateMargins();
	QLabel::setPixmap(pm);
}

void DicomViewer::resizeEvent(QResizeEvent* event)
{
	updateMargins();
	QLabel::resizeEvent(event);
}

void DicomViewer::updateMargins()
{
	if (pixmapWidth <= 0 || pixmapHeight <= 0)
		return;

	int w = this->width();
	int h = this->height();

	if (w <= 0 || h <= 0)
		return;

	if (w * pixmapHeight > h * pixmapWidth)
	{
		int m = (w - (pixmapWidth * h / pixmapHeight)) / 2;
		setContentsMargins(m, 0, m, 0);
	}
	else
	{
		int m = (h - (pixmapHeight * w / pixmapWidth)) / 2;
		setContentsMargins(0, m, 0, m);
	}
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
		selectImage(index() - 1);
	}
	else
	{
		selectImage(index() + 1);
	}
}
