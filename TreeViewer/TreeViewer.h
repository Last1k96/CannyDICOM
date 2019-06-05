#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TreeViewer.h"

class TreeViewer : public QMainWindow
{
	Q_OBJECT

public:
	TreeViewer(QWidget *parent = Q_NULLPTR);

private:
	Ui::TreeViewerClass ui;
};
