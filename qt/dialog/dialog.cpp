/**
 * @file Test eval display
 *
 * @author sfzhang
 * @date 2016-11-9
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.showMaximized();

    return app.exec();
}
