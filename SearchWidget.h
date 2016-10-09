#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>


class SearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchWidget(QWidget *parent = 0);
    ~SearchWidget();
    void setText(QString text);
    QString text();
private:
    QLineEdit *SearchEdit;
    QPushButton *SearchBtn;
    QHBoxLayout *MainLayout;
signals:
    void clicked();
    void returnPressed();

public slots:
};

#endif // SEARCHWIDGET_H
