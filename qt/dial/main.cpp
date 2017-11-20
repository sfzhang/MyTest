/**
 * @file Test eval display
 *
 * @author sfzhang
 * @date 2016-11-9
 */

#include <QApplication>
#include "dial.h"
#include <QDial>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dial dial(200, 1000, 480);
    //QDial dial;
    dial.show();

    return app.exec();
}
