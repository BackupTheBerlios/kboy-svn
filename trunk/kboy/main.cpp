#include <QtGui/QApplication>
#include "kboy.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    kboy foo;
    foo.show();
    return app.exec();
}
