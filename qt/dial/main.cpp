/**
 * @file Test eval display
 *
 * @author sfzhang
 * @date 2016-11-9
 */

#include <QApplication>
#include "dial.h"
#include "simpledial.h"
#include <QDial>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dial dial(200, 1000, 480);
    dial.resize(640 / 3, 640 / 3);
    dial.setValue(500);
    //QDial dial;
    dial.show();

    return app.exec();
}
