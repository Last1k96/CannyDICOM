#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Canny3D.h"

class Canny3D : public QMainWindow
{
Q_OBJECT

public:
	Canny3D(QWidget* parent = Q_NULLPTR);

private:
	Ui::Canny3DClass ui;
};
