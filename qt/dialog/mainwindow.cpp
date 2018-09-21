/**
 * @file Implement main window
 *
 * @author sfzhang
 * @date 2016-11-9
 */

#include "mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <string>
#include <iterator>
#include <QComboBox>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow()
{
    createToolBar();
    m_dlg = new ImageDialog;
}

void MainWindow::createToolBar()
{
    m_new_action = new QAction("new", this);
    connect(m_new_action, SIGNAL(triggered()),
            this, SLOT(on_new_action_triggered()));

    m_main_tool_bar = new QToolBar(this);
    m_main_tool_bar->addAction(m_new_action);
    addToolBar(m_main_tool_bar);
}

void MainWindow::on_new_action_triggered()
{
    QFileDialog dlg(this);
    dlg.exec();

    QRect rect = QApplication::desktop()->screenGeometry();
    QImage image("/home/fus/Pictures/test.png");
    m_dlg->setImage(image);
    m_dlg->show();
    m_dlg->raise();
    m_dlg->activateWindow();
    m_dlg->move(rect.center() - m_dlg->rect().center());
}
