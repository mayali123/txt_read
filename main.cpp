#include "file1.h"
#include <QtWidgets/QApplication>
#include<QDebug>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	file1 w;
	w.show();
	return a.exec();
}
