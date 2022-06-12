#include "xStudio.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xStudio w;
    w.show();
    return a.exec();
}
