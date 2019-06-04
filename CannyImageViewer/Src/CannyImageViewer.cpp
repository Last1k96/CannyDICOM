#include "CannyImageViewer.h"
#include <QPainter>

CannyImageViewer::CannyImageViewer(QWidget *parent)
	: QWidget(parent)
{
}

void CannyImageViewer::paintEvent(QPaintEvent* event)
{
	QPainter painter{this};
	auto size = QRectF(10, 10, this->width() - 10, this->width() - 10);

	painter.setBrush(Qt::red);
	painter.drawPie(size, 0, 90 * 16);
	painter.setBrush(Qt::blue);
	painter.drawPie(size, 90 * 16, 270 * 16);
}
