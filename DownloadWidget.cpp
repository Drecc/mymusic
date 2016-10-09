#include "DownloadWidget.h"

DownloadWidget::DownloadWidget(QWidget *parent) : QWidget(parent)
{
    Is_LeftPress = false;
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    init();
}

DownloadWidget::~DownloadWidget()
{

}

QString DownloadWidget::getMusicName()
{
    return musicName->text();
}

QString DownloadWidget::getArtistName()
{
    return artistName->text();
}

void DownloadWidget::setMusicName(QString name)
{
    musicName->setText(name);
}

void DownloadWidget::setArtistName(QString name)
{
    artistName->setText(name);
}

void DownloadWidget::setBarVisible(bool bo)
{
    bar->setVisible(bo);
}

void DownloadWidget::setBtnVisible(bool bo)
{
    dafaultBtn->setVisible(bo);
}

void DownloadWidget::init()
{
    title = new QLabel(tr("下载歌曲"));

    closeBtn = new QPushButton;
    closeBtn->setObjectName(tr("closeBtn"));
    closeBtn->setFixedSize(18,18);
    closeBtn->setCursor(Qt::PointingHandCursor);
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(hide()));

    minBtn = new QPushButton;
    minBtn->setObjectName(tr("minBtn"));
    minBtn->setFixedSize(18,18);
    minBtn->setCursor(Qt::PointingHandCursor);
    connect(minBtn,SIGNAL(clicked()),this,SLOT(showMinimized()));

    tipLabel = new QLabel(tr("输入歌曲名"));
    tip2Label = new QLabel(tr("输入歌手名"));
    musicName = new QLineEdit;
    artistName = new QLineEdit;

    bar = new QProgressBar;
    bar->setValue(0);

    dafaultBtn = new QPushButton(tr("确定"));
    connect(dafaultBtn,SIGNAL(clicked()),this,SIGNAL(clickedDafaultBtn()));
    dafaultBtn->setFixedSize(35,25);

    upLayout = new QHBoxLayout;
    upLayout->addWidget(title);
    upLayout->addStretch(1);
    upLayout->addWidget(minBtn);
    upLayout->addWidget(closeBtn);

    midLayout = new QGridLayout;

    midLayout->addWidget(tipLabel, 0, 0);
    midLayout->addWidget(musicName, 0, 1);
    midLayout->addWidget(tip2Label, 1, 0);
    midLayout->addWidget(artistName, 1, 1);
    midLayout->setColumnStretch(0, 1);
    midLayout->setColumnStretch(1, 2);

    downLayout = new QHBoxLayout;
    downLayout->addWidget(bar);
    downLayout->addWidget(dafaultBtn);


    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(midLayout);
    mainLayout->addLayout(downLayout);

    setLayout(mainLayout);

    setFixedSize(260,150);

    QBitmap bmp(this->size());                      //设置窗体遮罩圆角
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);                                //白色
    p.setBrush(Qt::black);                              //黑色
    p.drawRoundedRect(bmp.rect(),10,10);                //画出来之后椭圆矩形的内部为黑，则可以显示，其他地方为透明
    setMask(bmp);
}

void DownloadWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(Is_LeftPress)
    {
        this->move(this->pos() + (event->globalPos() - PressPositon));
        PressPositon = event->globalPos();
    }
}

void DownloadWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        PressPositon = event->globalPos();
        Is_LeftPress = true;
    }
}

void DownloadWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        Is_LeftPress = false;
}

void DownloadWidget::downloadProgress(qint64 progress, qint64 total)
{
    bar->setMaximum(total);
    bar->setValue(progress);
}

