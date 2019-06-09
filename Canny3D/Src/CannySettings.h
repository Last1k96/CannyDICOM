#pragma once

#include <QWidget>
#include "ui_CannySettings.h"

class CannySettings : public QWidget
{
	Q_OBJECT

public:
	CannySettings(QWidget *parent = Q_NULLPTR);

public slots:
	void setVOICenterMinimum(int value);
	void setVOICenterMaximum(int value);
	void setVOIWidthMinimum(int value);
	void setVOIWidthMaximum(int value);

private:
	Ui::CannySettings ui;
};
