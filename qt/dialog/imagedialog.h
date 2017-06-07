/**
 * @file Image dialog
 *
 * @author sfzhang
 * @date 2016-11-14
 */

#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include <QImage>

class ImageDialog: public QDialog {

    Q_OBJECT

public:

    /**
     * @brief Constructor
     * @param[in] parent The parent widget
     */
    ImageDialog(QWidget *parent = nullptr);

    /**
     * @brief Set image
     * @param[in] image The image
     */
    void setImage(const QImage &image);

protected:

    /**
     * @brief paintEvent
     */
    virtual void paintEvent(QPaintEvent *);

protected:

    QImage m_image;

};

#endif
