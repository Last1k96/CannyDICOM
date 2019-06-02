#include "QtGuiDicomViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtGuiDicomViewer w;
	w.show();
	return a.exec();
}
