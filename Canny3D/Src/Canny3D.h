#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_Canny3D.h"
#include <qfiledialog.h>
#include <QLabel>
#include "Utility.h"

class Canny3D : public QMainWindow
{
	Q_OBJECT

public:
	Canny3D(QWidget* parent = Q_NULLPTR);
	bool loadFiles(const QString&);
		
	void addNewTab() const;
	void addNewTab3D() const;

	bool initiateOpenDialog(QString const& dialogName, QFileDialog::FileMode dialogType);

private slots:
	void open();
	void openFolder();

private:
	Ui::Canny3DClass ui;
	std::vector<ImebraImage> images{};

};
