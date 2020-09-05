#include <QPainter>
#include <QMouseEvent>
#include "SwitchControl.h"
#include"NewIphoneControl.h"

SwitchControl::SwitchControl(QWidget* parent)
    : QWidget(parent),
    m_nHeight(16),
    m_bChecked(false),
    m_radius(8.0),
    m_nMargin(3),
    m_checkedColor(0, 176, 80),
    m_thumbColor(Qt::white),
    m_disabledColor(190, 190, 190),
    m_background(Qt::gray)
{
    // ��껬�������״ - ����
    setCursor(Qt::PointingHandCursor);

    // �����źŲ�
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(this,SIGNAL(toggled(int)),this,SLOT(TestFunction()));
}

SwitchControl::SwitchControl(int type,int num, QWidget* sigparent,QWidget* parent)
    : QWidget(parent),
    m_nHeight(16),
    m_bChecked(false),
    m_radius(8.0),
    m_nMargin(3),
    m_checkedColor(0, 176, 80),
    m_thumbColor(Qt::white),
    m_disabledColor(190, 190, 190),
    m_background(Qt::gray),
    type(type),
    num(num),
    sigparent(sigparent)
{
    // ��껬�������״ - ����
    setCursor(Qt::PointingHandCursor);

    // �����źŲ�
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect(this, SIGNAL(toggled(bool)), this, SLOT(TestFunction()));
    connect(this, SIGNAL(toggled(int,int)), sigparent, SLOT(SwitchSlot(int,int)));
}

// ���ƿ���
void SwitchControl::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    QColor background;
    QColor thumbColor;
    qreal dOpacity;
    if (isEnabled()) { // ����״̬
        if (m_bChecked) { // ��״̬
            background = m_checkedColor;
            //thumbColor = m_checkedColor;
            thumbColor = m_thumbColor;
            dOpacity = 0.600;
        }
        else { //�ر�״̬
            background = m_background;
            thumbColor = m_thumbColor;
            dOpacity = 0.800;
        }
    }
    else {  // ������״̬
        background = m_background;
        dOpacity = 0.260;
        thumbColor = m_disabledColor;
    }
    // ���ƴ���Բ
    painter.setBrush(background);
    painter.setOpacity(dOpacity);//��͸����
    //path.addRoundedRect(QRectF(m_nMargin, m_nMargin, width () - 2 * m_nMargin, height() - 2 * m_nMargin), m_radius, m_radius);
    //path.addRect(QRectF(0, 0, width(), height()));
    if(type==0)
        path.addRect(QRectF(0, 0, 50, 20));
    else
        path.addRect(QRectF(0, 0, 30 , 15));
    painter.drawPath(path.simplified());

    // ����С��Բ
    painter.setBrush(thumbColor);
    painter.setOpacity(1.0);
    //painter.drawEllipse(QRectF(m_nX - (m_nHeight / 2), m_nY - (m_nHeight / 2), height(), height()));
    //painter.drawRect(QRectF(m_nX - (m_nHeight / 2), m_nY - (m_nHeight / 2), height() * 2, height()));
    if (type == 0)
        painter.drawRect(QRectF(m_nX, m_nY,30, 20));
    else
        painter.drawRect(QRectF(m_nX, m_nY, 20, 15));
}

// ��갴���¼�
void SwitchControl::mousePressEvent(QMouseEvent* event)
{
    if (isEnabled()) {
        if (event->buttons() & Qt::LeftButton) {
            event->accept();
        }
        else {
            event->ignore();
        }
    }
}

// ����ͷ��¼� - �л�����״̬������toggled()�ź�
void SwitchControl::mouseReleaseEvent(QMouseEvent* event)
{
    if (isEnabled()) {
        if ((event->type() == QMouseEvent::MouseButtonRelease) && (event->button() == Qt::LeftButton)) {
            event->accept();
            m_bChecked = !m_bChecked;
            //emit toggled(m_bChecked);
            emit toggled(type,num);
            m_timer.start(10);//10ms
        }
        else {
            event->ignore();
        }
    }
}

// ��С�ı��¼�
void SwitchControl::resizeEvent(QResizeEvent* event)
{
    //m_nX = m_nHeight / 2;
    m_nX = 0;
    //m_nY = m_nHeight / 2;
    m_nY = 0;
    QWidget::resizeEvent(event);
}

// Ĭ�ϴ�С
QSize SwitchControl::sizeHint() const
{
    return minimumSizeHint();
}

// ��С��С
QSize SwitchControl::minimumSizeHint() const
{
    return QSize(2 * (m_nHeight + m_nMargin), m_nHeight + 2 * m_nMargin);
}

// �л�״̬ - ����
void SwitchControl::onTimeout()
{
    if (m_bChecked) {
        m_nX += 1;
        //if (m_nX >= width() - height() * 2)
        if (type == 0)
        {
            if(m_nX >= 20)
            m_timer.stop();
        }
        else if (m_nX >= 10 )
            m_timer.stop();
    }
    else {
        m_nX -= 1;
        //if (m_nX <= m_nHeight / 2)
        if (m_nX <= 0)
            m_timer.stop();
    }
    update();
}

// ���ؿ���״̬ - �򿪣�true �رգ�false
bool SwitchControl::isToggled() const
{
    return m_bChecked;
}

// ���ÿ���״̬
void SwitchControl::setToggle(bool checked)
{
    m_bChecked = checked;
    m_timer.start(10);
}

// ���ñ�����ɫ
void SwitchControl::setBackgroundColor(QColor color)
{
    m_background = color;
}

// ����ѡ����ɫ
void SwitchControl::setCheckedColor(QColor color)
{
    m_checkedColor = color;
}

// ���ò�������ɫ
void SwitchControl::setDisbaledColor(QColor color)
{
    m_disabledColor = color;
}
void SwitchControl::TestFunction()
{
    qDebug() << "TestFunction";
}
//void SwitchControl::sendToggle(int num)
//{
//    emit toggled(num);
//}