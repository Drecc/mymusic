#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QImage>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFont>

class ItemWidget : public QWidget
{
    Q_OBJECT
public:
    ItemWidget(QString picPath,QString tittle,QString tip,QWidget *parent = 0);
    ~ItemWidget();
protected:
    void enterEvent(QEvent*);
private:
    void init();
    QImage *image;
    QLabel *pic;
    QLabel *label_1;
    QLabel *label_2;

    QFont font_1;
    QFont font_2;
    QVBoxLayout *leftLayout;
    QHBoxLayout *mainLayout;
};

#endif // ITEMWIDGET_H
