#include "MusicLrcLabel.h"

MusicLrcLabel::MusicLrcLabel(QWidget *parent):QLabel(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::SubWindow);
    this->setAttribute(Qt::WA_TranslucentBackground);     //背景透明
    this->setFocusPolicy(Qt::NoFocus);
    this->resize(800,60);
    this->setText(tr("音乐播放器"));

    double width = QApplication::desktop() ->width();   //移动位置
    double height = QApplication::desktop() ->height();
    this ->move(QPoint(width / 2 - 800 / 2, height - 90));


    LineGradient.setStart(0,10);            //线条
    LineGradient.setFinalStop(0,60);
    LineGradient.setColorAt(0.1,QColor(14,179,255) );
    LineGradient.setColorAt(0.5,QColor(114,32,255) );
    LineGradient.setColorAt(0.9,QColor(176,196,222) );//  14,179,255

    CoverGraditent.setStart(0,10);          //罩子
    CoverGraditent.setFinalStop(0,60);
    CoverGraditent.setColorAt(0.1,QColor(186,85,211) );//222,54,4
    CoverGraditent.setColorAt(0.5,QColor(147,112,219) );//255,72,16
    CoverGraditent.setColorAt(0.9,QColor(230,230,250) );//222,54,4

    LabelFont.setFamily("Times New Roman"); // 字体
    LabelFont.setBold(true);
    LabelFont.setPointSize(30);

    Timer = new QTimer(this);
    connect(Timer,SIGNAL(timeout()),this,SLOT(TimeOut()) );
    LrcCoverWidth = 0;
    LrcCoverIntervalWidth = 0;

    Menu = new QMenu(this);
    Hiden = new QAction(tr("隐藏"),this);
    connect(Hiden,SIGNAL(triggered()),this,SLOT(hide()) );
}
void MusicLrcLabel::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.setFont(LabelFont);

    painter.setPen(QColor(0,0,200));
    painter.drawText(0,0,800,60,Qt::AlignLeft,text());

    painter.setPen(QPen(LineGradient,0));
    painter.drawText(0,0,800,60,Qt::AlignLeft,text());

    painter.setPen(QPen(CoverGraditent,0));
    painter.drawText(0,0,LrcCoverWidth,60,Qt::AlignLeft,text());


}
void MusicLrcLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        PressPositon = event->globalPos();
        Is_LeftPress = true;
    }
}
void MusicLrcLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(Is_LeftPress)
    {
        setCursor(Qt::PointingHandCursor);
        move(this->pos() + (event->globalPos() - PressPositon));
        PressPositon = event->globalPos();
    }
}

void MusicLrcLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        Is_LeftPress = false;
    }
}
void MusicLrcLabel::StartCoverLrc(qint64 IntervalTime)
{
    qreal count = IntervalTime / 30;        //每隔30毫秒更新一次
    LrcCoverIntervalWidth = 800/count;
    LrcCoverWidth = 0;
    Timer->start(30);
}
void MusicLrcLabel::StopCoverLrc()
{
    Timer->stop();
    LrcCoverWidth = 0;
    update();
    this->setText(tr("音乐播放器"));
}

void MusicLrcLabel::contextMenuEvent(QContextMenuEvent *event)
{
    Menu->clear();
    Menu->addAction(Hiden);
    Menu->exec(event->globalPos());
}

void MusicLrcLabel::TimeOut()
{
    LrcCoverWidth += LrcCoverIntervalWidth;
    update();
}

MusicLrcLabel::~MusicLrcLabel()
{

}

