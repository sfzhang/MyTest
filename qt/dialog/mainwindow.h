/**
 * @file Main window
 *
 * @author sfzhang
 * @date 2016-11-9
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "imagedialog.h"

class QAction;
class QComboBox;
class QToolBar;

/**
 * @class Mainwindow
 */
class MainWindow: public QMainWindow {

    Q_OBJECT

public:

    MainWindow();

protected:

    void createToolBar();

protected slots:

    void on_new_action_triggered();

protected:

    QToolBar *m_main_tool_bar;
    QAction *m_new_action;

    ImageDialog *m_dlg;

};

#endif
