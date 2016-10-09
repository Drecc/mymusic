#include "ItemWidget.h"

ItemWidget::ItemWidget(QString picPath, QString tittle, QString tip, QWidget *parent) : QWidget(parent)
{
    init();
    image->load(picPath);
    label_1->setText(tittle);
    label_2->setText(tip);
    pic->setPixmap(QPixmap::fromImage(*image).scaled(40,40));
}

ItemWidget::~ItemWidget()
{

}

void ItemWidget::enterEvent(QEvent *)
{
    setCursor(Qt::PointingHandCursor);
}

void ItemWidget::init()
{
    image = new QImage;

    pic = new QLabel(this);
    pic->setFixedSize(40,40);

    font_1.setPointSize(10);

    label_1 = new QLabel(this);
    label_1->setFont(font_1);
    font_2.setPointSize(8);

    label_2 = new QLabel(this);
    label_2->setFont(font_2);

    leftLayout = new QVBoxLayout;
    leftLayout->addSpacing(5);
    leftLayout->addWidget(label_1);
    leftLayout->addWidget(label_2);

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(pic);
    mainLayout->addLayout(leftLayout);
    setLayout(mainLayout);

    setFixedHeight(55);
}

