#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Canny3D.h"
#include <qfiledialog.h>
#include <QLabel>
#include "DataSetReader.h"

class Canny3D : public QMainWindow
{
Q_OBJECT

public:
	Canny3D(QWidget* parent = Q_NULLPTR);
	bool loadFiles(const QString&);

private slots:
	void open();
	void openFolder();

private:
	Ui::Canny3DClass ui;

	void updateImage();
	DataSetReader reader;
	QImage image;
	QLabel* imageLabel;
};
