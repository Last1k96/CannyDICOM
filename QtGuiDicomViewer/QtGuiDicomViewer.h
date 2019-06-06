#pragma once

#include <QWheelEvent>
#include "ui_DicomViewer.h"
#include "DataSetReader.h"

class QGraphicsSceneWheelEvent;

class DicomViewer : public QMainWindow
{
Q_OBJECT

public:
	DicomViewer(QWidget* parent = Q_NULLPTR);
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
