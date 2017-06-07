#include <QApplication>  
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <QImage>
#include <iostream>

#include "cvt.h"

using namespace cv;  
using namespace std;

void q2cv()
{  
    QImage qimage = QImage("./cvt.png");

    /* QImage convert to Mat */
    Mat image(qimage.height(),
              qimage.width(),
              CV_8UC4,
              const_cast<uchar*>(qimage.bits()),
              static_cast<size_t>(qimage.bytesPerLine()));

    imshow("li",image);  
    waitKey();  
}

int cv2q(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Mat image = imread("./cvt.png");  
    
    cout << image.type() << endl;
    if (image.type() == CV_8UC3) {
        cout << "CV_8UC3" << endl;
    }

    QImage qimage(image.data, image.cols, image.rows,
                  static_cast<int>(image.step),
                  QImage::Format_RGB888);

    Widget widget;
    widget.setImage(qimage.rgbSwapped());
    widget.show();

    return app.exec();
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        q2cv();
        return 0;
    }

    return cv2q(argc, argv);
}
