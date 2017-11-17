/**
 * @file Test eval display
 *
 * @author sfzhang
 * @date 2016-11-9
 */

#include <QApplication>
#include "dial.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Dial dial;
    dial.show();

    return app.exec();
}
