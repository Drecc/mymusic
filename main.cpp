#include "widget.h"
#include <QApplication>
#include <QListWidget>
#include <QWidget>
#include <QListWidgetItem>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
