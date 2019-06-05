#include "TreeViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TreeViewer w;
	w.show();
	return a.exec();
}
