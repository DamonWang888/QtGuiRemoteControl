#pragma once
#ifndef SWITCH_CONTROL
#define SWITCH_CONTROL

#include <QWidget>
#include <QTimer>
#include<QDebug>

class SwitchControl : public QWidget
{
    Q_OBJECT

public:
    explicit SwitchControl(QWidget* parent = 0);
    //explicit SwitchControl(int type,int num,QWidget* parent = 0);
    explicit SwitchControl(int type, int num, QWidget* sigparent,QWidget* parent = 0);
    // ���ؿ���״̬ - �򿪣�true �رգ�false
    bool isToggled() const;

    // ���ÿ���״̬
    void setToggle(bool checked);

    // ���ñ�����ɫ
    void setBackgroundColor(QColor color);

    // ����ѡ����ɫ
    void setCheckedColor(QColor color);

    // ���ò�������ɫ
    void setDisbaledColor(QColor color);

    

protected:
    // ���ƿ���
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

    // ��갴���¼�
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    // ����ͷ��¼� - �л�����״̬������toggled()�ź�
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    // ��С�ı��¼�
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

    // ȱʡ��С
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

 signals:
    // ״̬�ı�ʱ�������ź�
    void toggled(bool checked);
    void toggled(int type,int num);

private slots:
    // ״̬�л�ʱ�����ڲ�������Ч��
    void onTimeout();

    //���Ժ���
    void TestFunction();

private:
    bool m_bChecked;         // �Ƿ�ѡ��
    QColor m_background;     // ������ɫ
    QColor m_checkedColor;   // ѡ����ɫ
    QColor m_disabledColor;  // ��������ɫ
    QColor m_thumbColor;     // Ĵָ��ɫ
    qreal m_radius;          // Բ��
    qreal m_nX;              // x������
    qreal m_nY;              // y������
    qint16 m_nHeight;        // �߶�
    qint16 m_nMargin;        // ��߾�
    QTimer m_timer;          // ��ʱ��
    int type;                // �������� 0���ܿ��أ�1���ֲ��ܿ��أ�2����ͨ����
    int num;                 // ���ر��
    QWidget* sigparent;      // ͨ�Ŷ���
   
};

#endif // SWITCH_CONTROL