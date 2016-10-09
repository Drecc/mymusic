#include "SearchWidget.h"

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{ 
    SearchBtn = new QPushButton;
    SearchBtn->setFixedSize(25,25);
    SearchBtn->setCursor(Qt::OpenHandCursor);
    SearchBtn->setObjectName(tr("searchBtn"));

    SearchEdit = new QLineEdit;

    MainLayout = new QHBoxLayout;
    MainLayout->addWidget(SearchEdit);
    MainLayout->addWidget(SearchBtn);
    MainLayout->setContentsMargins(2,2,2,2);

    this->setLayout(MainLayout);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
    this->setFixedSize(250,30);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setObjectName(tr("searchWidget"));

    connect(SearchBtn,SIGNAL(clicked()),this,SIGNAL(clicked()));      //转发信号
    connect(SearchEdit,SIGNAL(returnPressed()),this,SIGNAL(returnPressed()));

}

SearchWidget::~SearchWidget()
{

}

void SearchWidget::setText(QString text)
{
    SearchEdit->setText(text);
}

QString SearchWidget::text()
{
    return SearchEdit->text();
}


