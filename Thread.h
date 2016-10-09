#ifndef THREAD_H
#define THREAD_H

#include <widget.h>
#include <QThread>
#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


class Thread : public QThread
{
    Q_OBJECT
public:
    enum Type{INIT_LIST, SAVE_LIST, DELETE_MUSIC, DELETE_MUSIC_ALL};
    Thread(QObject *parent = 0);
    ~Thread();
    void setTyle(Type ty);
    void setPaths(QStringList &pa);
    void setIsDafault(bool bo);
    void setPath(QString pa);
signals:
    void MusicPath(QString);
    void CloseThread();
    void addMusic(QFileInfo, bool);
protected:
    void run();
private:
    void initList();
    void saveList();
    void deleteMusic();
    void deleteMusicAll();
    QString path;               //要删除的歌曲路径
    QStringList paths;          //要删除的歌曲路径s
    Type type;                  //执行哪种类型
    bool Is_dafault;            //是否为默认列表

};

#endif // THREAD_H
