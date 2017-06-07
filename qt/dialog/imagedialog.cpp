/**
 * @file Image dialog
 *
 * @author sfzhang
 * @date 2016-11-14
 */

#include "imagedialog.h"
#include <QPainter>
#include <QRectF>

ImageDialog::ImageDialog(QWidget *parent):
    QDialog(parent, Qt::Window | Qt::WindowCloseButtonHint)
{
    setMinimumSize(512, 512);
    setModal(false);
}

void ImageDialog::setImage(const QImage &image)
{
    m_image = image;
    update();
}

void ImageDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QRect r = rect();
    QRectF target;
    if ((m_image.width() > 0) && (m_image.height() > 0)) {
        double w_s = 1.0 * r.width() / m_image.width();
        double h_s = 1.0 * r.height() / m_image.height();
        if (w_s > h_s) {
            double w = h_s * m_image.width();
            double h = r.height();
            target = QRectF(((r.width() - w) / 2.0), 0, w, h);
        }
        else {
            double h = w_s * m_image.height();
            double w = r.width();
            target = QRectF(0, ((r.height() - h) / 2.0), w, h);
        }

        painter.drawImage(target, m_image);
    }
}
