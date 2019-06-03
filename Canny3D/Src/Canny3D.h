#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Canny3D.h"
#include <qfiledialog.h>
#include <QLabel>
#include "DataSetReaderCanny.h"

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
	static void initializeImageFileDialog(QFileDialog& dialog, QFileDialog::AcceptMode acceptMode);
	Ui::Canny3DClass ui;

	void createActions();
	void updateImage();
	DataSetReader reader;
	QImage image;
	QLabel* imageLabel;
};
