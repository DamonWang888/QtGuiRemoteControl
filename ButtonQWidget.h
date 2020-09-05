#pragma once
#include<QWidget>
#include<QDebug>
#include<QVBoxLayout>
#include<QLabel>
//#include"terminal.h"
/// <summary>
/// 实现点击某一QWidget对象时的动作
/// </summary>

class ButtonQWidget : public QWidget
{
	Q_OBJECT

public:
    explicit ButtonQWidget(QWidget* parent = 0);
    
protected:
    void mousePressEvent(QMouseEvent*event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent*event) Q_DECL_OVERRIDE;
    //void paintEvent(QPaintEvent*event);

private:
    QVBoxLayout* pGlobalLayOut;
    bool state;
    //terminal* pWifiSpeedTerminal;
    QWidget* pTotalQWidget;
    QLabel* pTitle;
    QLabel* pFill1;
    QLabel* pFill2;
    QWidget* pTerminalWidget;
    QVBoxLayout* pTerminalLayOut;
    //terminal* pTerminal;
signals:
    void clicked();
    void released();
    void pressed();
private slots:
    void initFormWifiSpeed();
    void init();
    void initForm();
};