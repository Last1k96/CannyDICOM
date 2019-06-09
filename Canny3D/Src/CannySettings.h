#pragma once

#include <QWidget>
#include "ui_CannySettings.h"

class CannySettings : public QWidget
{
	Q_OBJECT

public:
	CannySettings(QWidget *parent = Q_NULLPTR);
	~CannySettings();

private:
	Ui::CannySettings ui;
};
