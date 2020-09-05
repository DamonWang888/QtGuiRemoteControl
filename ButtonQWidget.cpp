#include"ButtonQWidget.h"
ButtonQWidget::ButtonQWidget(QWidget* parent):QWidget(parent)
{
    state = 0;
    setCursor(Qt::PointingHandCursor);
	connect(this,SIGNAL(pressed()),this,SLOT(initFormWifiSpeed()));
	//this->init();
	//this->initForm();
}

void ButtonQWidget::mousePressEvent(QMouseEvent*event)
{
    qDebug() << "mousePressEvent";
    state = 1;
    //repaint();
    emit pressed();
}

void ButtonQWidget::mouseReleaseEvent(QMouseEvent*event)
{
    qDebug() << "mouseReleaseEvent";
    state = 0;
    //repaint();
    emit released();
    emit clicked();
}

//void ButtonQWidget::paintEvent(QPaintEvent*)
//{
//    /*if (state)
//        ...............
//    else
//        .............;*/
//}
void ButtonQWidget::init()
{
    pGlobalLayOut = new QVBoxLayout;
    pGlobalLayOut->setSpacing(6);//栅格之间的空白
    pGlobalLayOut->setMargin(0);//边缘
    pGlobalLayOut->setObjectName("gridLayout");
    this->setLayout(pGlobalLayOut);
}
void ButtonQWidget::initForm()
{
	pTitle = new QLabel(this);
	pTitle->setObjectName(QString("GlobalTitle"));
	pTitle->setText(QString("系统自检"));
	pFill1 = new QLabel(this);
	pFill1->setObjectName(QString("FillLabel1"));
	pFill2 = new QLabel(this);
	pFill2->setObjectName(QString("FillLabel2"));
	//pFill->setText(QString("系统自检"));
	QFont font1;
	font1.setPointSize(27);
	pTitle->setFont(font1);
	pTitle->setTextFormat(Qt::AutoText);
	pTitle->setGeometry(395, 0, 150, 36);
	pFill1->setGeometry(20, 0, 375, 36);
	pFill2->setGeometry(545, 0, 375, 36);
	//pFill->setText(QString("系统自检"));
	QColor col1 = QColor(255, 211, 155);
	if (col1.isValid()) {
		QString qss = QString("background-color: %1").arg(col1.name());
		pFill1->setStyleSheet(qss);
		pFill2->setStyleSheet(qss);
		pTitle->setStyleSheet(qss);
	}

	pTerminalWidget = new QWidget(this);
	pTerminalWidget->setObjectName(QStringLiteral("layoutWidget"));
	pTerminalWidget->setGeometry(QRect(20, 40, 900, 900));

	pTerminalLayOut = new QVBoxLayout;
	pTerminalLayOut->setSpacing(6);//栅格之间的空白
	pTerminalLayOut->setMargin(0);//边缘
	pTerminalLayOut->setObjectName("TerminalLayout");
	pTerminalWidget->setLayout(pTerminalLayOut);

	//pTerminal = new terminal(pTerminalWidget);
	//pTerminal->setGeometry();
	//pTerminalLayOut->addWidget(pTerminal);
}
void ButtonQWidget::initFormWifiSpeed()
{
	qDebug() << "ButtonQWidget::initFormWifiSpeed";
	QWidget* pNewWidget = new QWidget();
	pNewWidget->show();
}