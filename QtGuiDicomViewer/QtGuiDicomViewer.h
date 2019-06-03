#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QHBoxLayout>
#include <QWheelEvent>
#include <opencv2/core/mat.hpp>
#include "ui_QtGuiDicomViewer.h"
#include "DataSetReader.h"

class QGraphicsSceneWheelEvent;

class QtGuiDicomViewer : public QMainWindow
{
Q_OBJECT

public:
	QtGuiDicomViewer(QWidget* parent = Q_NULLPTR);
	bool loadFiles(const QString&);

private slots:
	void open();
	void openFolder();
	void saveAs();
	void about();

private:
	bool eventFilter(QObject* obj, QEvent* event) override;
	void handleWheelEvent(QWheelEvent*);
	void createActions();
	bool saveFile(const QString& fileName);
	void updateImage();
	DataSetReader reader;

	QLabel* imageLabel;
	QImage image;
};
