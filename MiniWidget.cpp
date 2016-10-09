#include "MiniWidget.h"

MiniWidget::MiniWidget(QWidget *parent) : QWidget(parent)
{


}

MiniWidget::MiniWidget(QWidget *parent, QMediaPlayer *play): QWidget(parent)
{
    this->player = play;
    createBtn();
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setFixedSize(300,80);

    QBitmap bmp(this->size());                      //设置窗体遮罩圆角
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);                                //白色
    p.setBrush(Qt::black);                              //黑色
    p.drawRoundedRect(bmp.rect(),10,10);                //画出来之后椭圆矩形的内部为黑，则可以显示，其他地方为透明
    setMask(bmp);

    connect(previousBtn,SIGNAL(clicked()),this,SIGNAL(ClickedPreviousBtn()));
    connect(playOrpauseBtn,SIGNAL(clicked()),this,SIGNAL(ClickedPlayBtn()));
    connect(nextBtn,SIGNAL(clicked()),this,SIGNAL(ClickedNextBtn()));
    connect(hideBtn,SIGNAL(clicked()),this,SIGNAL(ClickedHideBtn()));

    Is_LeftPress = false;
}

MiniWidget::~MiniWidget()
{

}

void MiniWidget::setText(QString text)
{
    MusicInformation->setText(text);
}

QPushButton *MiniWidget::getPlayBtn()
{
    return playOrpauseBtn;
}

void MiniWidget::setPicPath(QString pictureName)
{
    image->load(pictureName);
    picture->setPixmap(QPixmap::fromImage(*image));
}

void MiniWidget::createBtn()
{
    image = new QImage(tr(":/skin/BKImage/4.jpg"));

    picture = new QLabel(this);
    picture->setScaledContents(true);
    picture->setFixedSize(80,60);
    picture->setPixmap(QPixmap::fromImage(*image));

    MusicInformation = new QLabel(this);
    MusicInformation->setText(tr("音乐播放器"));

    previousBtn = new QPushButton(this);
    previousBtn->setCursor(Qt::PointingHandCursor);
    previousBtn->setFixedSize(25,25);
    previousBtn->setObjectName(tr("miniPreviousBtn"));

    playOrpauseBtn = new QPushButton(this);
    playOrpauseBtn->setCursor(Qt::PointingHandCursor);
    playOrpauseBtn->setFixedSize(25,25);
    playOrpauseBtn->setObjectName(tr("miniPlayorpauseBtn"));

    nextBtn = new QPushButton(this);
    nextBtn->setCursor(Qt::PointingHandCursor);
    nextBtn->setFixedSize(25,25);
    nextBtn->setObjectName(tr("miniNextBtn"));

    hideBtn = new QPushButton(this);
    hideBtn->setCursor(Qt::PointingHandCursor);
    hideBtn->setFixedSize(18,18);
    hideBtn->setObjectName(tr("mainBtn"));
    //hideBtn->setText(tr("主"));

    upLayout = new QHBoxLayout;

    upLayout->addWidget(MusicInformation);
    upLayout->addWidget(previousBtn);
    upLayout->addWidget(playOrpauseBtn);
    upLayout->addWidget(nextBtn);
    upLayout->addWidget(hideBtn);

    seekSlider = new QSlider(Qt::Horizontal,this);
    seekSlider->setCursor(Qt::PointingHandCursor);
    connect(seekSlider,SIGNAL(sliderReleased()),this,SLOT(ValueChanged()));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(DurationChanged(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(PositionChanged(qint64)));

    leftLayout = new QVBoxLayout;
    leftLayout->addLayout(upLayout);
    leftLayout->addWidget(seekSlider);

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(picture);
    mainLayout->addLayout(leftLayout);
    this->setLayout(mainLayout);



}

void MiniWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(Is_LeftPress)
    {
        this->move(this->pos() + (event->globalPos() - PressPositon));
        PressPositon = event->globalPos();
    }
}

void MiniWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        PressPositon = event->globalPos();
        Is_LeftPress = true;
    }
}

void MiniWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        Is_LeftPress = false;
}

void MiniWidget::DurationChanged(qint64 max)
{
    seekSlider->setRange(0,max);
}

void MiniWidget::ValueChanged()
{
    player->setPosition(seekSlider->value());
}

void MiniWidget::PositionChanged(qint64 position)
{
    seekSlider->setValue(position);
}

