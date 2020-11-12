#include "widget.h"
#include "dialog.h"
#include "messagebox.h"
#include <QPainter>
#include <QRadialGradient>
#include <QImage>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>

using namespace cv;

bool convertMat2QImage(const Mat &mat, QImage &image)
{
    Mat m;
    QImage conv_image;
    switch (mat.type()) {
    case CV_8UC4:
        conv_image = QImage(mat.data, mat.cols, mat.rows,
                            static_cast<int>(mat.step),
                            QImage::Format_ARGB32);
        break;
    case CV_8UC3:
        cvtColor(mat, m, COLOR_BGR2RGB);
        conv_image = QImage(m.data, m.cols, m.rows,
                            m.step[0],
                            QImage::Format_RGB888);
        break;
    case CV_8UC1: {
        static QVector<QRgb> s_color_table;
        if (s_color_table.empty()) {
            for (size_t i = 0; i < 256; i++) {
                s_color_table.push_back(qRgb(i, i, i));
            }
        }

        conv_image = QImage(mat.data, mat.cols, mat.rows,
                            static_cast<int>(mat.step),
                       QImage::Format_Indexed8);
        conv_image.setColorTable(s_color_table);
        break;
    }
    default:
        return false;
    }

    /* Make sure deep copy */
    image = conv_image.copy();
    return true;
}

bool convertQImage2Mat(const QImage &image, Mat &mat)
{
    switch (image.format()) {
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = Mat(image.height(), image.width(), CV_8UC4,
                  const_cast<uchar*>(image.bits()),
                  static_cast<size_t>(image.bytesPerLine())).clone();
        break;
    case QImage::Format_RGB888: {
        QImage swap_image = image.rgbSwapped();
        mat = Mat(swap_image.height(), swap_image.width(), CV_8UC3,
                  const_cast<uchar*>(swap_image.bits()),
                  static_cast<size_t>(swap_image.bytesPerLine())).clone();
        break;
    }
    case QImage::Format_Indexed8:
        mat = Mat(image.height(), image.width(), CV_8UC1,
                  const_cast<uchar*>(image.bits()),
                  static_cast<size_t>(image.bytesPerLine())).clone();
        break;
    default:
        return false;
    }

    return true;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_image = QImage(140, 140, QImage::Format_ARGB32);

    m_sonic_icon = new QImage(":/res/sonicIcon.png");
    m_cool_icon = new QImage(":/res/coolIcon.png");

    m_current_angle = 0;

    connect(&m_timer, &QTimer::timeout, this, &Widget::render);
    //connect(&m_timer, &QTimer::timeout, this, &Widget::updateProcess);
    //calcStep(120);
    m_timer.start(1000 / 24);
    m_i = 0;
    m_r = false;

    generate(30);
    /*
    auto dialog = new Dialog(this);
    dialog->setWindowTitle("Test");
    dialog->show();
    */

    m_msg_box = new MessageBox(QMessageBox::Warning, "Confirm",
                                  "Copyright (C) 2015-2019 by Shanghai Shende Healthcare Co.Ltd.",
                                  //QMessageBox::Ok);
                                  QMessageBox::Yes | QMessageBox::No);
                                  //QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll);
                                  //QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    m_msg_box->setCheckBox("Apply all");
    m_msg_box->disableClose(true);

    connect(m_msg_box, &MessageBox::finished, this, &Widget::on_close);

    /*
    qDebug() << m_msg_box->exec();
    qDebug() << m_msg_box->standarClickedButton();

    qDebug() << MessageBox::information("info", "a b c d e f g asdfas asfasdjfqwioeejrfqw");
    qDebug() << MessageBox::question("quest", "a b c d e f g asdfas asfasdjfqwioeejrfqw");
    qDebug() << MessageBox::warning("warn", "a b c d e f g asdfas asfasdjfqwioeejrfqw");
    qDebug() << MessageBox::critical("critical", "a b c d e f g asdfas asfasdjfqwioeejrfqw");

    //m_msg_box->show();

    auto i = QMessageBox::question(nullptr, "a", "b", QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::Ok);
    qDebug() << i;
    */
}

Widget::~Widget()
{

}

void Widget::on_close(int r)
{
    qDebug() << "finished: " << r;
    qDebug() << "buttons: " << m_msg_box->standarClickedButton();
}

void Widget::calcStep(int t)
{
    double n_fps = 5760.0 / (abs(t) * 24);
    int itv = 0;
    if (n_fps >= 1) {
        itv = 1000 / 24;
    }
    else {
        itv = abs(t) * 1000 / 5760;
    }

    m_timer.start(itv);
    m_step_angle = n_fps * abs(t) / t;
}

void Widget::updateProcess()
{
    m_current_angle += m_step_angle;

    if (m_current_angle < 0) {
        m_current_angle = 0;
    }
    else if (m_current_angle > 5760) {
        m_current_angle = 5760;

        calcStep(-30);
    }

    update();
}

void Widget::generate(double angle)
{
    cv::Mat m(256, 256, CV_8UC3);

    cv::ellipse(m, Point(128, 128), Size(100, 100), 270, (360 - angle), 360, Scalar(0x00, 0x4c, 0xff), 7);
    cv::ellipse(m, Point(128, 128), Size(100, 100), 270, 0, (360 - angle), Scalar(0xeb, 0x80, 0x26), 7);

    cv::Mat blur_m;
    GaussianBlur(m, blur_m, Size(31, 31), 0, 0);
    convertMat2QImage(blur_m, m_image);
    update();
}

void Widget::drawProcess(QPainter *painter)
{
    double length = m_sonic_icon->width();
    double half_length = length / 2;

    double angle = (m_current_angle / 5760.0) * 2 * M_PI;
    double h = half_length * (1 - cos(angle));

    painter->save();
    painter->translate(width() / 2.0, height() / 2.0);
    if (m_current_angle <= 5760 / 2) {
        painter->drawImage(QRectF(0, -half_length, half_length, length), *m_cool_icon,
                           QRectF(half_length, 0, half_length, length));
        painter->drawImage(QRectF(-half_length, -half_length, half_length, h), *m_sonic_icon,
                           QRectF(0, 0, half_length, h));

        if (m_current_angle != 5760 / 2) {
            painter->drawImage(QRectF(-half_length, (-half_length + h), half_length, (length - h)), *m_cool_icon,
                               QRectF(0, h, half_length, (length - h)));
        }
    }
    else {
        painter->drawImage(QRectF(-half_length, -half_length, half_length, length), *m_sonic_icon,
                           QRectF(0, 0, half_length, length));

        painter->drawImage(QRectF(0, (-half_length + h), half_length, (length - h)), *m_sonic_icon,
                           QRectF(half_length, h, half_length, (length - h)));

        painter->drawImage(QRectF(0, -half_length, half_length, h), *m_cool_icon,
                           QRectF(half_length, 0, half_length, h));
    }

    painter->restore();
}


void Widget::render()
{
    static int angle = 0;
    angle += 10;
    angle %= 360;

    generate(angle);
    return;

    QImage image(140, 140, QImage::Format_RGB888);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    //QPainter painter(&m_image);

    painter.translate(image.width() / 2, image.height() / 2);
    painter.setPen(QColor(0x1c, 0x1d, 0x22));
    painter.setBrush(QColor(0x1c, 0x1d, 0x22));
    painter.drawRect(-128, -128, 256, 256);

    if (m_r) {
        m_i -= 16;
    }
    else {
        m_i += 16;
    }

    if (m_i >= 5760) {
        m_r = true;
        m_i = 5760;
    }
    else if (m_i <= 0) {
        m_r = false;
        m_i = 0;
    }

    QPen pen_r(QColor(0xff, 0x4c, 0x00));
    pen_r.setCapStyle(Qt::RoundCap);
    pen_r.setWidth(7);
    painter.setPen(pen_r);
    painter.drawArc(-64, -64, 128, 128, 0, m_i);

    QPen pen_b(QColor(0x26, 0x80, 0xeb));
    pen_b.setWidth(7);
    pen_b.setCapStyle(Qt::RoundCap);
    painter.setPen(pen_b);
    painter.drawArc(-64, -64, 128, 128, 0, -(5760 - m_i));

    Mat src, dst;
    if (convertQImage2Mat(image, src)) {
        GaussianBlur(src, dst, Size(31, 31), 0, 0);
        convertMat2QImage(dst, m_image);
    }

    QPainter p2(&m_image);
    p2.setRenderHint(QPainter::HighQualityAntialiasing);
    pen_r.setWidth(3);
    p2.setPen(pen_r);
    p2.translate(m_image.width() / 2, m_image.height() / 2);
    p2.drawArc(-64, -64, 128, 128, 0, m_i);

    pen_b.setWidth(3);
    p2.setPen(pen_b);
    p2.drawArc(-64, -64, 128, 128, 0, -(5760 - m_i));

    update();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    /*
    cv::Mat m(256, 256, CV_8UC4);

    cv::ellipse(m, Point(128, 128), Size(100, 100), 0, 0, 360, Scalar(0xff, 0x00, 0x00, 0xff), 2);
    cvtColor(m, m, CV_BGR2RGBA);
    convertMat2QImage(m, m_image);

    int w = m_image.width();
    int h = m_image.height();

//    drawProcess(&painter);

    //painter.translate(width() / 2.0, height() / 2.0);
    */
    painter.drawImage(QRectF(width() / 2 - m_image.width() / 2, height() / 2 - m_image.height() / 2,
                             m_image.width(), m_image.height()), m_image);

    QPen pen(QColor(0xff, 0x4c, 0x00));
    pen.setWidth(2);
    painter.setPen(pen);
    //painter.drawArc(-64, -64, 128, 128, 0, m_i);

#if 0
    painter.drawImage()

    QImage image(256, 256, QImage::Format_RGB888);

    QPainter img_painter(&image);



    painter.translate(width() / 2.0, height() / 2.0);

    painter.setBrush(QColor(0x1c, 0x1d, 0x22));
    painter.drawRect(-width() / 2, -height() / 2, width(), height());

    QRadialGradient rg(0, 0, 120, 0, 0);

    rg.setColorAt(0, QColor(0x00, 0x00, 0x00, 0x00));
    rg.setColorAt(0.69, QColor(0x00, 0x00, 0x00, 0x00));
    rg.setColorAt(0.7, QColor(0xff, 0x4c, 0x00, 0x00));
    rg.setColorAt(0.82, QColor(0xff, 0x4c, 0x00, 0x4f));
    rg.setColorAt(0.85, QColor(0xff, 0x4c, 0x00, 0x5f));
    rg.setColorAt(0.88, QColor(0xff, 0x4c, 0x00, 0x4f));
    rg.setColorAt(1, QColor(0xff, 0x4c, 0x00, 0x00));

    painter.setPen(Qt::transparent);
    painter.setBrush(rg);

    painter.drawPie(QRectF(-120, -120, 240, 240), 30 * 16, 120 * 16);
#endif
}
