#include "DicomViewer.h"
#include <QWidget>
#include <utility>
#include "Utility.h"

DicomViewer::DicomViewer(QWidget* parent, std::vector<ImebraImage>&& data)
	: QLabel(parent)
	  , images(std::forward<std::vector<ImebraImage>>(data))
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
	currentImage = computeCurrentImage();
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

void DicomViewer::setSettings(Settings const& s)
{
	settings = s;
	updateImage();
}

cv::Mat DicomViewer::computeImage(int index) const
{
	cv::Mat result;

	auto const imebraImage = images[index];

	auto const voilut = applyVoilutTransform(imebraImage, VOI{ settings.voiCenter, settings.voiWidth });
	if (settings.step == Steps::VOI)
	{
		auto const original = cv::Mat(applyVoilutTransform(imebraImage));
		hconcat(original, voilut, result);
		return result;
	}

	auto const blured = gauss(voilut, settings.gaussKernel, settings.gaussSigma);
	if (settings.step == Steps::Gauss)
	{
		hconcat(voilut, blured, result);
		return result;
	}
	//auto const thld = toZeroThreshold(blured);
	auto const edges = canny(blured, Threshold{ settings.cannyLow, settings.cannyHigh });
	//removeUnwantedEdges(edges, original);
	hconcat(blured, edges, result);
	return result;
}

cv::Mat DicomViewer::computeCurrentImage() const
{
	return computeImage(idx);
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
