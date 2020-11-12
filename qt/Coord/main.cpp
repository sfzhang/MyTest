//#include "widget.h"
#include "phasewidget.h"
#include "ampplot.h"
#include <QApplication>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //PhaseWidget w;
    AmpPlot w;
    w.show();

    QString s;
    bool valid = true;

    auto d = s.toDouble(&valid);
    d = d + 0;

    qDebug() << valid;

    return a.exec();
}
