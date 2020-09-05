#ifndef LIGHTBUTTON_H
#define LIGHTBUTTON_H

/**
 * �������ⰴť�ؼ� ����:feiyangqingyun(QQ:517216493) 2016-10-16
 * 1:�������ı�,������ʾ
 * 2:�������ı���ɫ
 * 3:��������߿򽥱���ɫ
 * 4:��������߿򽥱���ɫ
 * 5:�����ñ���ɫ
 * 6:��ֱ�ӵ������õ����� ��ɫ/��ɫ/��ɫ/��ɫ/��ɫ �ȹ��вۺ���
 * 7:�������Ƿ��������п��ƶ�,����һ������ʹ��
 * 8:�������Ƿ���ʾ����
 * 9:�����ñ�����ɫ+�Ǳ�����ɫ
 * 10:�ɿ�������������ֹͣ����,����ʱ��˸
 */

#include <QWidget>

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,7,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT LightButton : public QWidget
#else
class LightButton : public QWidget
#endif

{
    Q_OBJECT
        Q_PROPERTY(QString text READ getText WRITE setText)
        Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
        Q_PROPERTY(QColor alarmColor READ getAlarmColor WRITE setAlarmColor)
        Q_PROPERTY(QColor normalColor READ getNormalColor WRITE setNormalColor)

        Q_PROPERTY(QColor borderOutColorStart READ getBorderOutColorStart WRITE setBorderOutColorStart)
        Q_PROPERTY(QColor borderOutColorEnd READ getBorderOutColorEnd WRITE setBorderOutColorEnd)
        Q_PROPERTY(QColor borderInColorStart READ getBorderInColorStart WRITE setBorderInColorStart)
        Q_PROPERTY(QColor borderInColorEnd READ getBorderInColorEnd WRITE setBorderInColorEnd)
        Q_PROPERTY(QColor bgColor READ getBgColor WRITE setBgColor)

        Q_PROPERTY(bool canMove READ getCanMove WRITE setCanMove)
        Q_PROPERTY(bool showRect READ getShowRect WRITE setShowRect)
        Q_PROPERTY(bool showOverlay READ getShowOverlay WRITE setShowOverlay)
        Q_PROPERTY(QColor overlayColor READ getOverlayColor WRITE setOverlayColor)

public:
    explicit LightButton(QWidget* parent = 0);

protected:
    bool eventFilter(QObject* watched, QEvent* event);
    void paintEvent(QPaintEvent*);
    void drawBorderOut(QPainter* painter);
    void drawBorderIn(QPainter* painter);
    void drawBg(QPainter* painter);
    void drawText(QPainter* painter);
    void drawOverlay(QPainter* painter);

private:
    QString text;                   //�ı�
    QColor textColor;               //������ɫ
    QColor alarmColor;              //������ɫ
    QColor normalColor;             //������ɫ

    QColor borderOutColorStart;     //��߿򽥱俪ʼ��ɫ
    QColor borderOutColorEnd;       //��߿򽥱������ɫ
    QColor borderInColorStart;      //��߿򽥱俪ʼ��ɫ
    QColor borderInColorEnd;        //��߿򽥱������ɫ
    QColor bgColor;                 //������ɫ

    bool showRect;                  //��ʾ�ɾ���
    bool canMove;                   //�Ƿ��ܹ��ƶ�
    bool showOverlay;               //�Ƿ���ʾ���ֲ�
    QColor overlayColor;            //���ֲ���ɫ

    bool isAlarm;                   //�Ƿ񱨾�
    QTimer* timerAlarm;             //��ʱ���л���ɫ

public:
    QString getText()               const;
    QColor getTextColor()           const;
    QColor getAlarmColor()          const;
    QColor getNormalColor()         const;

    QColor getBorderOutColorStart() const;
    QColor getBorderOutColorEnd()   const;
    QColor getBorderInColorStart()  const;
    QColor getBorderInColorEnd()    const;
    QColor getBgColor()             const;

    bool getCanMove()               const;
    bool getShowRect()              const;
    bool getShowOverlay()           const;
    QColor getOverlayColor()        const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //�����ı�
    void setText(const QString& text);
    //�����ı���ɫ
    void setTextColor(const QColor& textColor);

    //���ñ�����ɫ+������ɫ
    void setAlarmColor(const QColor& alarmColor);
    void setNormalColor(const QColor& normalColor);

    //������߿򽥱���ɫ
    void setBorderOutColorStart(const QColor& borderOutColorStart);
    void setBorderOutColorEnd(const QColor& borderOutColorEnd);

    //������߿򽥱���ɫ
    void setBorderInColorStart(const QColor& borderInColorStart);
    void setBorderInColorEnd(const QColor& borderInColorEnd);

    //���ñ���ɫ
    void setBgColor(const QColor& bgColor);

    //�����Ƿ���ƶ�
    void setCanMove(bool canMove);
    //�����Ƿ���ʾ����
    void setShowRect(bool showRect);
    //�����Ƿ���ʾ���ֲ�
    void setShowOverlay(bool showOverlay);
    //�������ֲ���ɫ
    void setOverlayColor(const QColor& overlayColor);

    //����Ϊ��ɫ
    void setGreen();
    //����Ϊ��ɫ
    void setRed();
    //����Ϊ��ɫ
    void setYellow();
    //����Ϊ��ɫ
    void setBlack();
    //����Ϊ��ɫ
    void setGray();
    //����Ϊ��ɫ
    void setBlue();
    //����Ϊ����ɫ
    void setLightBlue();
    //����Ϊ����ɫ
    void setLightRed();
    //����Ϊ����ɫ
    void setLightGreen();

    //���ñ�����˸
    void startAlarm();
    void stopAlarm();
    void alarm();

    //���ֳ���
    void HoldAram();

};

#endif // LIGHTBUTTON_H
