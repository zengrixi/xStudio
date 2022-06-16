#include <QtWidgets/QApplication>
#include "MainWindow.h"

using namespace xStudio;

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow   w;
    w.show();
    return a.exec();
}