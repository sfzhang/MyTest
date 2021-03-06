#include "dial.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPixmap>
#include <cmath>
//#include <pub/point3d.h>

using namespace std;

const double Dial::K_INIT_ANGLE_DEG = 150;
const double Dial::K_RANGE_ANGLE_DEG = 240;
const double Dial::K_INIT_ANGLE = (M_PI * K_INIT_ANGLE_DEG / 180);
const double Dial::K_RANGE_ANGLE = (M_PI * K_RANGE_ANGLE_DEG / 180);

const QColor Dial::K_DARK_COLOR = QColor(204, 204, 204);
const QColor Dial::K_BRIGHT_COLOR = QColor(71, 222, 229);

Dial::Dial(int min, int max, int dft, QWidget *parent):
    QAbstractSlider(parent),
    m_add_btn(nullptr),
    m_sub_btn(nullptr),
    m_dft_btn(nullptr),
    m_dft_value(dft),
    m_adjust(false)
{
    //setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setMinimum(min);
    setMaximum(max);

    initialize();

    setMouseTracking(true);
    setStyleSheet("background-color:#2A2A2A;");
    setFocusPolicy(Qt::StrongFocus);
}

Dial::Dial(int min, int max, QWidget *parent):
    Dial(min, max, (min + max) / 2, parent)
{
}

Dial::~Dial()
{
}

QSize Dial::sizeHint() const
{
    return QSize(m_panel_icon.getRadius() * 2, m_panel_icon.getRadius() * 2);
}

void Dial::initialize()
{
    /* Panel */
    QIcon *panel = new QIcon(":res/dial_panel.png");

    m_panel_icon.setIcon(panel);
    m_panel_icon.setSize(QSizeF(480, 480));
    m_panel_icon.setRadius(157.5);

    /* Switch */
    QIcon *dial_switch = new QIcon(":res/dial_switch.png");

    m_switch_icon.setIcon(dial_switch);
    m_switch_icon.setSize(QSizeF(480, 480));
    m_switch_icon.setInnerRadius(45);
    m_switch_icon.setOuterRadius(82.5);

    /* Indicator */
    QIcon *indicator = new QIcon();
    indicator->addFile(":res/dial_indicator_normal.png");
    indicator->addFile(":res/dial_indicator_disabled.png", QSize(), QIcon::Disabled);

    m_indicator_icon.setIcon(indicator);
    m_indicator_icon.setSize(QSizeF(12, 12));

    /* Add button */
    QIcon add_icon;
    add_icon.addFile(":res/dial_add_normal.png");
    add_icon.addFile(":res/dial_add_disabled.png", QSize(), QIcon::Disabled);
    add_icon.addFile(":res/dial_add_active.png", QSize(), QIcon::Active);
    add_icon.addFile(":res/dial_add_selected.png", QSize(), QIcon::Selected);
    m_add_btn = new CircularButton(32, 72, add_icon, "", this);
    m_add_btn->setAutoRepeat(true);
    m_add_btn->setAutoRepeatInterval(80);
    connect(m_add_btn, &QPushButton::clicked, this, &Dial::increase);

    /* Sub button */
    QIcon sub_icon;
    sub_icon.addFile(":res/dial_sub_normal.png");
    sub_icon.addFile(":res/dial_sub_disabled.png", QSize(), QIcon::Disabled);
    sub_icon.addFile(":res/dial_sub_active.png", QSize(), QIcon::Active);
    sub_icon.addFile(":res/dial_sub_selected.png", QSize(), QIcon::Selected);
    m_sub_btn = new CircularButton(32, 72, sub_icon, "", this);
    m_sub_btn->setAutoRepeat(true);
    m_sub_btn->setAutoRepeatInterval(80);
    connect(m_sub_btn, &QPushButton::clicked, this, &Dial::descrease);

    /* Default button */
    QIcon dft_icon;
    dft_icon.addFile(":res/dial_dft_normal.png");
    dft_icon.addFile(":res/dial_dft_disabled.png", QSize(), QIcon::Disabled);
    dft_icon.addFile(":res/dial_dft_active.png", QSize(), QIcon::Active);
    dft_icon.addFile(":res/dial_dft_selected.png", QSize(), QIcon::Selected);
    m_dft_btn = new CircularButton(32, 72, dft_icon, "", this);
    connect(m_dft_btn, &QPushButton::clicked, this, &Dial::setDefault);

    /* Other radius */
    m_indicator_radius = 54;
    m_tracking_radius = 87.75;
    m_notch_radius = 114;
    m_notch_value_radius = 135;

    setMaximumSize(m_panel_icon.getSize().toSize());
    setMinimumSize((m_panel_icon.getSize() / 3).toSize());

    connect(this, &QAbstractSlider::valueChanged, this, &Dial::updateButtonState);
    updateButtonState(value());
}

double Dial::getFontSize(const QString &text, double scale) const
{
    return scale * 24 - 4 * text.length() + 14;
}

double Dial::value2Angle(double value) const
{
    double max = maximum();
    double min = minimum();

    if (value > max) {
        value = max;
    }
    else if (value < min) {
        value = min;
    }

    return (K_INIT_ANGLE + (value - min) / (max - min) * K_RANGE_ANGLE);

}

void Dial::resetIconRegion(const QSize &size)
{
    double scale = 1;

    double w_scale = size.width() / m_panel_icon.getSize().width();
    double h_scale = size.height() / m_panel_icon.getSize().height();

    if (w_scale > h_scale) {
        scale = h_scale;
    }
    else {
        scale = w_scale;
    }

    m_panel_icon.setScale(scale);
    m_panel_icon.setCenter(size.width() / 2.0, size.height() / 2.0);

    m_switch_icon.setScale(scale);
    m_switch_icon.setCenter(size.width() / 2.0, size.height() / 2.0);

    m_indicator_icon.setScale(scale);

    /* Add button */
    int length = m_add_btn->length() * scale;
    m_add_btn->resize(length, length);

    double r = m_panel_icon.getRadius() * scale;
    m_add_btn->move((size.width() / 2.0 + r - length / 2.0),
                    (size.height() / 2.0 + r - length / 2.0));

    /* Sub button */
    length = m_sub_btn->length() * scale;
    m_sub_btn->resize(length, length);

    m_sub_btn->move((size.width() / 2.0 - r - length / 2.0),
                    (size.height() / 2.0 + r - length / 2.0));

    /* Default button */
    length = m_dft_btn->length() * scale;
    m_dft_btn->resize(length, length);

    m_dft_btn->move((size.width() / 2.0 + r - length / 2.0),
                    (size.height() / 2.0 - r - length / 2.0));
}

void Dial::updateValue(const QPointF &point)
{
    QPointF center = m_panel_icon.getCenter();
    auto p = point - center;

    double angle = atan2(p.y(), p.x());
    if (angle < M_PI / 2) {
        angle += 2 * M_PI;
    }

    double min = minimum();
    double max = maximum();
    double old_value = value();

    double new_value = min + (angle - K_INIT_ANGLE) / K_RANGE_ANGLE * (max - min);

    if (((max == old_value) || (min == old_value)) &&
        ((new_value > max) || (new_value < min))) {
        return;
    }

    new_value = qBound(min, new_value, max);
    setSliderPosition(new_value + 0.5);
}

void Dial::increase()
{
    int new_value = value() + singleStep();
    new_value = qBound(minimum(), new_value, maximum());
    setSliderPosition(new_value);
}

void Dial::descrease()
{
    int new_value = value() - singleStep();
    new_value = qBound(minimum(), new_value, maximum());
    setSliderPosition(new_value);
}

void Dial::setDefault()
{
    int new_value = qBound(minimum(), m_dft_value, maximum());
    setSliderPosition(new_value);
}

void Dial::drawPanel(QPainter &painter)
{
    painter.drawPixmap(m_panel_icon.getPosition(), m_panel_icon.getPixmap());
}

void Dial::drawTracking(QPainter &painter)
{
    double angle = value2Angle(value());
    double angle_deg = angle * 180 / M_PI;

    painter.save();

    QPen pen(K_BRIGHT_COLOR);
    if (!isEnabled()) {
        pen.setColor(K_DARK_COLOR);
    }
    pen.setWidth(m_panel_icon.getScale() / 0.2);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    double r = m_tracking_radius * m_panel_icon.getScale();
    QRectF rect(m_panel_icon.getCenter().x() - r,
                m_panel_icon.getCenter().y() - r, r * 2, r * 2);
    painter.drawArc(rect, -(K_INIT_ANGLE_DEG - 1) * 16,
                          -(angle_deg - K_INIT_ANGLE_DEG + 1) * 16);

    painter.restore();
}

void Dial::drawNotch(QPainter &painter)
{
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(K_DARK_COLOR);
    pen.setWidth(2);
    painter.setPen(pen);

    QBrush brush(K_DARK_COLOR);
    painter.setBrush(brush);

    double x = 0;
    double y = 0;
    double r = m_notch_radius * m_panel_icon.getScale();
    QPointF center = m_panel_icon.getCenter();

    double d = m_panel_icon.getScale() / 0.4;
    for (int i = 0; i <= K_RANGE_ANGLE_DEG; i += 30) {
        x = center.x() + r * cos((K_INIT_ANGLE_DEG + i) * M_PI / 180);
        y = center.y() + r * sin((K_INIT_ANGLE_DEG + i) * M_PI / 180);
        painter.drawPie(QRectF(x - d, y - d, 2 * d, 2 * d), 0, 360 * 16);
    }

    painter.restore();
}

void Dial::drawSwitch(QPainter &painter)
{
    painter.drawPixmap(m_switch_icon.getPosition(), m_switch_icon.getPixmap());
}

void Dial::drawIndicator(QPainter &painter)
{
    double angle = value2Angle(value());
    double angle_deg = angle * 180 / M_PI;

    painter.save();

    double r = m_indicator_radius * m_panel_icon.getScale();
    double x = m_panel_icon.getCenter().x() + r * cos(angle);
    double y = m_panel_icon.getCenter().y() + r * sin(angle);

    painter.translate(x, y);
    painter.rotate(90 + angle_deg);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    if (!isEnabled()) {
        painter.drawPixmap(m_indicator_icon.getPosition(),
                           m_indicator_icon.getPixmap(QIcon::Disabled));
    }
    else {
        painter.drawPixmap(m_indicator_icon.getPosition(),
                           m_indicator_icon.getPixmap(QIcon::Selected));
    }
    painter.rotate(-(90 + angle_deg));
    painter.translate(-x, -y);

    painter.restore();
}

void Dial::drawValue(QPainter &painter)
{
    painter.save();

    QString text = QString("%1").arg(value());
    double size = getFontSize(text, m_panel_icon.getScale());
    QFont font("Square721 BT", size, QFont::Bold);
    painter.setFont(font);

    if (!isEnabled()) {
        painter.setPen(K_DARK_COLOR);
    }
    else {
        painter.setPen(K_BRIGHT_COLOR);
    }

    QPointF center = m_panel_icon.getCenter();
    QRectF text_rect = QRectF(center.x() - 1, center.y() - 1, 2, 2);
    painter.drawText(text_rect, Qt::AlignCenter | Qt::TextSingleLine | Qt::TextDontClip,
                     text);

    painter.restore();
}

void Dial::drawNotchValue(QPainter &painter)
{
    painter.save();

    double min = minimum();
    double max = maximum();

    double v = 0;
    QPen pen(K_DARK_COLOR);
    pen.setWidth(2);
    painter.setPen(pen);

    QFont font("Square721 BT", (m_panel_icon.getScale() * 16), QFont::Normal);
    painter.setFont(font);

    double r = m_notch_value_radius * m_panel_icon.getScale();
    double x = 0;
    double y = 0;
    QPointF center = m_panel_icon.getCenter();
    for (int i = 0; i <= K_RANGE_ANGLE_DEG; i += 30) {
        if (!(i / 30 % 2)) {
            x = center.x() + r * cos((i + K_INIT_ANGLE_DEG) * M_PI / 180);
            y = center.y() + r * sin((i + K_INIT_ANGLE_DEG) * M_PI / 180);
            v = min + (max - min) / (K_RANGE_ANGLE_DEG / 30) * i / 30;

            painter.translate(x, y);
            painter.rotate(K_INIT_ANGLE_DEG + i + 90);
            painter.drawText(QRectF(- 1, - 1, 2, 2), Qt::AlignCenter | Qt::TextSingleLine | Qt::TextDontClip,
                             QString("%1").arg(v));
            painter.rotate(-(K_INIT_ANGLE_DEG + i + 90));
            painter.translate(-x, -y);
        }
    }

    painter.restore();
}

void Dial::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    /* Draw panel */
    drawPanel(painter);

    /* Draw tracking */
    drawTracking(painter);

    /* Draw notch */
    drawNotch(painter);

    /* Draw switch */
    drawSwitch(painter);

    /* Draw indicator */
    drawIndicator(painter);

    /* Draw value */
    drawValue(painter);

    /* Draw notch value */
    drawNotchValue(painter);
}

void Dial::resizeEvent(QResizeEvent *event)
{
    resetIconRegion(event->size());
    QAbstractSlider::resizeEvent(event);
}

void Dial::mousePressEvent(QMouseEvent *event)
{
    if ((minimum() == maximum()) || (event->button() != Qt::LeftButton) ||
        (!isEnabled())) {
        event->ignore();
        return;
    }
    else if (m_switch_icon.contains(event->localPos())) {
        event->accept();
        m_adjust = true;
        updateValue(event->localPos());
    }
    else {
        QAbstractSlider::mousePressEvent(event);
    }
}

void Dial::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_adjust) {
        event->accept();
        updateValue(event->localPos());
        m_adjust = false;
    }
    else {
        QAbstractSlider::mousePressEvent(event);
    }
}

void Dial::mouseMoveEvent(QMouseEvent *event)
{
    if (m_adjust) {
        event->accept();
        updateValue(event->localPos());
        update();
    }
    else if (isEnabled() && m_switch_icon.contains(event->localPos())) {
        if (!m_hover_switch) {
            m_hover_switch = true;
            update();
        }
    }
    else {
        if (m_hover_switch) {
            m_hover_switch = false;
            update();
        }
        QAbstractSlider::mouseMoveEvent(event);
    }
}

void Dial::setDefaultValue(int value)
{
    m_dft_value = qBound(minimum(), value, maximum());
    update();
}

void Dial::updateButtonState(int value)
{
    m_add_btn->setEnabled(value != maximum());
    m_sub_btn->setEnabled(value != minimum());
    update();
}
