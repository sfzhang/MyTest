#include "messagebox.h"
#include "ui_messagebox.h"
#include <QMouseEvent>
#include <QPushButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QStyle>

QMap<QMessageBox::StandardButton, QString> MessageBox::s_std_btn_text = {
    { QMessageBox::Ok, 				"Ok" },
    { QMessageBox::Save, 		    "Save" },
    { QMessageBox::SaveAll,			"Save all" },
    { QMessageBox::Open,			"Open" },
    { QMessageBox::Yes,				"Yes" },
    { QMessageBox::YesToAll,		"Yes to all" },
    { QMessageBox::No,				"No" },
    { QMessageBox::NoToAll,			"No to all" },
    { QMessageBox::Abort,			"Abort" },
    { QMessageBox::Retry,			"Retry" },
    { QMessageBox::Ignore,			"Ignore" },
    { QMessageBox::Close,			"Close" },
    { QMessageBox::Cancel,			"Cancel" },
    { QMessageBox::Discard,			"Discard" },
    { QMessageBox::Help,			"Help" },
    { QMessageBox::Apply,			"Apply" },
    { QMessageBox::Reset,			"Reset" },
    { QMessageBox::RestoreDefaults, "Restore defaults" }
};

MessageBox::MessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                       QMessageBox::StandardButtons buttons, QWidget *parent):
    QDialog(parent),
    ui(new Ui::MessageBox),
    m_display_ratio(1),
    m_move_widget(false)
{
    ui->setupUi(this);
    ui->m_check_box->hide();
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    connect(ui->m_close_btn, &QPushButton::clicked, this, &MessageBox::on_close_btn_clicked);

    setIcon(icon);
    setTitle(title);
    setText(text);
    addStdButtons(buttons);
    relayout();
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::on_close_btn_clicked()
{
    if (isModal()) {
        done(QDialog::Rejected);
    }
    else {
        reject();
    }
}

void MessageBox::on_btn_clicked()
{
    auto btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        m_clicked_btn_text = btn->text();

        if (isModal()) {
            done(QDialog::Accepted);
        }
        else {
            accept();
        }
    }
}

void MessageBox::relayout()
{
    auto hbox_layout = dynamic_cast<QHBoxLayout*>(ui->m_btns_widget->layout());
    if (!hbox_layout) {
        hbox_layout = new QHBoxLayout();
    }
    else {
        while (!hbox_layout->isEmpty()) {
            hbox_layout->removeItem(hbox_layout->itemAt(0));
        }
    }

    auto space = new QSpacerItem(1, 1, QSizePolicy::Expanding);
    hbox_layout->addSpacerItem(space);

    int space_size = m_btns_text.size() > 3 ? 36 : 48;
    for (int i = 0; i < m_btns_text.size(); i++) {
        hbox_layout->addWidget(m_btns_map[m_btns_text[i]].first);

        if (i < (m_btns_text.size() - 1)) {
            space = new QSpacerItem(static_cast<int>(space_size / m_display_ratio), 1);
            hbox_layout->addSpacerItem(space);
        }
    }

    ui->m_btns_widget->setLayout(hbox_layout);

    update();
}

void MessageBox::addStdButtons(QMessageBox::StandardButtons buttons)
{
    auto i = QMessageBox::FirstButton;
    while (i <= QMessageBox::LastButton) {
        if (buttons & i) {
            addButton(i);
        }
        i = static_cast<QMessageBox::StandardButton>(static_cast<uint32_t>(i) << 1);
    }
    m_std_btns = buttons;
}

void MessageBox::setIcon(QMessageBox::Icon icon)
{
    switch (icon) {
    case QMessageBox::Question:
        ui->m_icon_label->setProperty("icon_type", "question");
        break;
    case QMessageBox::Critical:
        ui->m_icon_label->setProperty("icon_type", "critical");
        break;
    case QMessageBox::Warning:
        ui->m_icon_label->setProperty("icon_type", "warning");
        break;
    case QMessageBox::Information:
        ui->m_icon_label->setProperty("icon_type", "information");
        break;
    case QMessageBox::NoIcon:
    default:
        ui->m_icon_label->setProperty("icon_type", "none");
        break;
    }
    m_icon = icon;

    ui->m_icon_label->style()->unpolish(ui->m_icon_label);
    ui->m_icon_label->style()->polish(ui->m_icon_label);
    ui->m_icon_label->update();

    update();
}

QMessageBox::Icon MessageBox::icon() const
{
    return m_icon;
}

void MessageBox::setTitle(const QString &title)
{
    ui->m_title_label->setText(title);
}

QString MessageBox::title() const
{
    return ui->m_title_label->text();
}

void MessageBox::setText(const QString &text)
{
    ui->m_text_label->setText(text);
}

QString MessageBox::text() const
{
    return ui->m_text_label->text();
}

QPushButton *MessageBox::addButton(QMessageBox::StandardButton button)
{
    if (m_std_btns & button) {
        return nullptr;
    }

    auto it = s_std_btn_text.find(button);
    if (it == s_std_btn_text.end()) {
        return nullptr;
    }

    auto btn = addBtnImpl(it.value(), button);
    if (btn) {
        m_std_btns |= button;
    }

    return btn;
}

QPushButton *MessageBox::addButton(const QString &text)
{
    return addBtnImpl(text, QMessageBox::NoButton);
}

QPushButton *MessageBox::addBtnImpl(const QString &text, QMessageBox::StandardButton button)
{
    if (m_btns_map.find(text) != m_btns_map.end()) {
        return nullptr;
    }

    auto btn = new QPushButton(text);
    connect(btn, &QPushButton::clicked, this, &MessageBox::on_btn_clicked);
    btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_btns_map.insert(text, qMakePair(btn, button));
    m_btns_text.push_back(text);
    relayout();

    return btn;
}

QCheckBox *MessageBox::setCheckBox(const QString &text)
{
    if (text.isEmpty()) {
        ui->m_text_label->hide();
    }
    else {
        ui->m_check_box->show();
    }
    ui->m_check_box->setText(text);
    return ui->m_check_box;
}

QCheckBox *MessageBox::checkBox() const
{
    return ui->m_check_box;
}

bool MessageBox::isChecked() const
{
    return ui->m_check_box->isChecked();
}

QPushButton *MessageBox::clickedButton() const
{
    if (m_clicked_btn_text.isEmpty()) {
        return nullptr;
    }
    else {
        return m_btns_map[m_clicked_btn_text].first;
    }
}

QMessageBox::StandardButton MessageBox::standarClickedButton() const
{
    if (m_clicked_btn_text.isEmpty()) {
        return QMessageBox::NoButton;
    }
    else {
        return m_btns_map[m_clicked_btn_text].second;
    }
}

void MessageBox::mousePressEvent(QMouseEvent *event)
{
    const auto close_btn_length = static_cast<int>(48 / m_display_ratio);
    auto title_bar = QRect(0, 0, width(), close_btn_length);
    if (ui->m_close_btn->isVisible()) {
        title_bar.setWidth(title_bar.width() - close_btn_length);
    }

    if (title_bar.contains(event->pos())) {
        m_orig_pos = pos();
        m_prev_point = event->globalPos();
        m_move_widget = true;
        grabMouse(Qt::ClosedHandCursor);
    }
    else {
        QDialog::mousePressEvent(event);
    }
}

void MessageBox::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move_widget) {
        move(m_orig_pos + event->globalPos() - m_prev_point);
    }
    else {
        QDialog::mouseMoveEvent(event);
    }
}

void MessageBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_move_widget) {
        m_move_widget = false;
        releaseMouse();
    }
    else {
        QDialog::mouseReleaseEvent(event);
    }
}
