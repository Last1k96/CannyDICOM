#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QHBoxLayout>
#include <QWheelEvent>
#include <opencv2/core/mat.hpp>
#include "DataSetReader.h"

class DicomViewer : public QLabel
{
	Q_OBJECT

public:
	DicomViewer(QWidget* parent = Q_NULLPTR);

private:
	bool eventFilter(QObject* obj, QEvent* event) override;
	void handleWheelEvent(QWheelEvent*);
	void updateImage();

	QLabel* imageLabel;
	QImage image;
};
