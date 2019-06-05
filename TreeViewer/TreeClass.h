#pragma once

#include <QWidget>
#include "ui_TreeClass.h"

class TreeClass : public QWidget
{
	Q_OBJECT

public:
	TreeClass(QWidget *parent = Q_NULLPTR);
	~TreeClass();


private:
	Ui::TreeClass ui;
};
