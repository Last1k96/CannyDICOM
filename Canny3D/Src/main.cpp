#include "Canny3D.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Canny3D w;
	w.showMaximized();
	return a.exec();
}
