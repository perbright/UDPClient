#include "querytest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QUERYTEST w;
    w.show();
    return a.exec();
}
