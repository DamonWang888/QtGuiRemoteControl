#pragma once
#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

/**
 * ���ذ�ť�ؼ� ����:feiyangqingyun(QQ:517216493) 2016-11-6
 * 1:�����ÿ��ذ�ť����ʽ Բ�Ǿ���/��Բ��/��Բ��
 * 2:������ѡ�к�δѡ��ʱ�ı�����ɫ
 * 3:������ѡ�к�δѡ��ʱ�Ļ�����ɫ
 * 4:��������ʾ���ı�
 * 5:�����û����뱳���ļ��
 * 6:������Բ�ǽǶ�
 * 7:�������Ƿ���ʾ��������Ч��
 */

#include <QWidget>
#include<Qpainter>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT SwitchButton : public QWidget
#else
class SwitchButton : public QWidget
#endif

{
    Q_OBJECT
        Q_ENUMS(ButtonStyle)

        Q_PROPERTY(int space READ getSpace WRITE setSpace)
        Q_PROPERTY(int rectRadius READ getRectRadius WRITE setRectRadius)
        Q_PROPERTY(bool checked READ getChecked WRITE setChecked)
        Q_PROPERTY(bool showText READ getShowText WRITE setShowText)
        Q_PROPERTY(bool showCircle READ getShowCircle WRITE setShowCircle)
        Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation)
        Q_PROPERTY(ButtonStyle buttonStyle READ getButtonStyle WRITE setButtonStyle)

        Q_PROPERTY(QColor bgColorOff READ getBgColorOff WRITE setBgColorOff)
        Q_PROPERTY(QColor bgColorOn READ getBgColorOn WRITE setBgColorOn)
        Q_PROPERTY(QColor sliderColorOff READ getSliderColorOff WRITE setSliderColorOff)
        Q_PROPERTY(QColor sliderColorOn READ getSliderColorOn WRITE setSliderColorOn)
        Q_PROPERTY(QColor textColorOff READ getTextColorOff WRITE setTextColorOff)
        Q_PROPERTY(QColor textColorOn READ getTextColorOn WRITE setTextColorOn)

        Q_PROPERTY(QString textOff READ getTextOff WRITE setTextOff)
        Q_PROPERTY(QString textOn READ getTextOn WRITE setTextOn)

public:
    enum ButtonStyle {
        ButtonStyle_Rect = 0,       //Բ�Ǿ���
        ButtonStyle_CircleIn = 1,   //��Բ��
        ButtonStyle_CircleOut = 2   //��Բ��
    };

    SwitchButton(QWidget* parent = 0);
    ~SwitchButton();

protected:
    void mousePressEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent*);
    void drawBg(QPainter* painter);
    void drawSlider(QPainter* painter);

private:
    int space;                      //�����뱳�����
    int rectRadius;                 //Բ�ǽǶ�
    bool checked;                   //�Ƿ�ѡ��
    bool showText;                  //��ʾ����
    bool showCircle;                //��ʾСԲ
    bool animation;                 //��������

    ButtonStyle buttonStyle;        //���ذ�ť��ʽ

    QColor bgColorOff;              //�ر�ʱ������ɫ
    QColor bgColorOn;               //��ʱ������ɫ
    QColor sliderColorOff;          //�ر�ʱ������ɫ
    QColor sliderColorOn;           //��ʱ������ɫ
    QColor textColorOff;            //�ر�ʱ������ɫ
    QColor textColorOn;             //��ʱ������ɫ

    QString textOff;                //�ر�ʱ��ʾ������
    QString textOn;                 //��ʱ��ʾ������

    int step;                       //ÿ���ƶ��Ĳ���
    int startX;                     //���鿪ʼX������
    int endX;                       //�������X������
    QTimer* timer;                  //��ʱ������

private slots:
    void change();
    void updateValue();

public:
    int getSpace()                  const;
    int getRectRadius()             const;
    bool getChecked()               const;
    bool getShowText()              const;
    bool getShowCircle()            const;
    bool getAnimation()             const;

    ButtonStyle getButtonStyle()    const;

    QColor getBgColorOff()          const;
    QColor getBgColorOn()           const;
    QColor getSliderColorOff()      const;
    QColor getSliderColorOn()       const;
    QColor getTextColorOff()        const;
    QColor getTextColorOn()         const;

    QString getTextOff()            const;
    QString getTextOn()             const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //���ü��
    void setSpace(int space);
    //����Բ�ǽǶ�
    void setRectRadius(int rectRadius);
    //�����Ƿ�ѡ��
    void setChecked(bool checked);
    //�����Ƿ���ʾ����
    void setShowText(bool showText);
    //�����Ƿ���ʾСԲ
    void setShowCircle(bool showCircle);
    //�����Ƿ񶯻�����
    void setAnimation(bool animation);

    //���÷����ʽ
    void setButtonStyle(const ButtonStyle& buttonStyle);

    //���ñ�����ɫ
    void setBgColorOff(const QColor& bgColorOff);
    void setBgColorOn(const QColor& bgColorOn);

    //���û�����ɫ
    void setSliderColorOff(const QColor& sliderColorOff);
    void setSliderColorOn(const QColor& sliderColorOn);

    //����������ɫ
    void setTextColorOff(const QColor& textColorOff);
    void setTextColorOn(const QColor& textColorOn);

    //��������
    void setTextOff(const QString& textOff);
    void setTextOn(const QString& textOn);

Q_SIGNALS:
    void checkedChanged(bool checked);
};

#endif // SWITCHBUTTON_H