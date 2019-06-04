#pragma once

#include <QtWidgets/QWidget>

class CannyImageViewer : public QWidget
{
	Q_OBJECT

public:
	explicit CannyImageViewer(QWidget *parent = Q_NULLPTR);
	void paintEvent(QPaintEvent* event) override;
};
