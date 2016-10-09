#include "SkinWidget.h"

SkinWidget::SkinWidget(QWidget *parent):QDialog(parent)
{
    CreateListWidget();

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAutoFillBackground(true);

    mainlayout = new QVBoxLayout;
    mainlayout->addWidget(ListWidget);
    setLayout(mainlayout);
    setFixedSize(460,600);
    setObjectName(tr("skinDialog"));

    QBitmap bmp(this->size());                      //设置窗体遮罩圆角
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);                                //白色
    p.setBrush(Qt::black);                              //黑色
    p.drawRoundedRect(bmp.rect(),10,10);                //画出来之后椭圆矩形的内部为黑，则可以显示，其他地方为透明
    setMask(bmp);

    Is_LeftPress = false;
}

SkinWidget::~SkinWidget()
{

}

QListWidget *SkinWidget::getList()
{
    return ListWidget;
}

void SkinWidget::CreateListWidget()
{
    ListWidget = new QListWidget(this);
    ListWidget->setObjectName(tr("skinList"));
    ListWidget->setIconSize(QSize(96, 96));
    ListWidget->setResizeMode(QListView::Adjust);
    ListWidget->setViewMode(QListView::IconMode);   //设置QListWidget的显示模式
    ListWidget->setMovement(QListView::Static);  //设置QListWidget中的单元项不可被拖动
    ListWidget->setSpacing(5);                 //设置QListWidget中的单元项的间距

    for(int nIndex = 0; nIndex < 20; ++nIndex)    //依次创建19个单元项
    {
        QString strPath = QString(":/skin/BKImage/%1.jpg").arg(nIndex + 1);   //获得图片路径
        QPixmap objPixmap(strPath);
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(96,96))),tr(" "));
        pItem->setSizeHint(QSize(96,96));
        ListWidget->insertItem(nIndex, pItem);
    }
}

void SkinWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(Is_LeftPress)
    {
        this->move(this->pos() + (event->globalPos() - PressPositon));
        PressPositon = event->globalPos();
    }
}

void SkinWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        PressPositon = event->globalPos();
        Is_LeftPress = true;
    }
}

void SkinWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        Is_LeftPress = false;
}



