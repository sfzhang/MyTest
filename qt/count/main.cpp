#include <QCoreApplication>
#include "counter.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Counter a, b;
    QObject::connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));

    a.setValue(12);

    return app.exec();
}
