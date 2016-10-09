#include "Thread.h"

Thread::Thread(QObject *parent):QThread(parent)
{
    Is_dafault = true;
}

void Thread::run()
{
    switch (type)
    {
    case INIT_LIST:
        initList();
        break;
    case SAVE_LIST:
        deleteMusicAll();
        saveList();
        break;
    case DELETE_MUSIC:
        deleteMusic();
        break;
    case DELETE_MUSIC_ALL:
        deleteMusicAll();
        break;
    }
}

Thread::~Thread()
{

}
void Thread::initList()
{
    QSqlDatabase database = QSqlDatabase::database("MusicData");
    QSqlDatabase database2 = QSqlDatabase::database("MusicData2");
    QSqlQuery query(database),query2(database2);
    query.exec("select * from Music");//查询默认列表的数据库中所有的音乐文件信息
    qDebug() << "open dafaultData";
    while(query.next())
    {
        QString path = query.value(2).toString();           //取出音乐的路径,检查存不存在该音乐
        QFile file(path);
        if (!file.exists())
        {
            if (query.exec("delete from Music where id = " + query.value(0).toString()))//音乐不存在则将其从数据库中删除
                qDebug() << path << "不存在, 无法添加到列表中, 已经从数据库中删除.";
        }
        else
        {
            QFileInfo pathName(path);           //如果存在则添加到播放列表和播放路径中
            //qDebug () <<pathName.absoluteFilePath();
            qRegisterMetaType<QFileInfo>("QFileInfo");
            emit addMusic(pathName, true);       //true为默认数据库
        }
    }
    query2.exec("select * from MusicCollect");     //查询收藏列表的数据库
    qDebug() << "open CollectData";
    while(query2.next())
    {
        QString path = query2.value(2).toString();           //取出音乐的路径,检查存不存在该音乐
        QFile file(path);
        if (!file.exists())
        {
            if (query2.exec("delete from MusicCollect where id = " + query2.value(0).toString()))//音乐不存在则将其从数据库中删除
                qDebug() << path << "不存在, 无法添加到列表中, 已经从数据库中删除.";
        }
        else
        {
            QFileInfo pathName(path);           //如果存在则添加到播放列表和播放路径中
            //qDebug () <<pathName.absoluteFilePath();
            qRegisterMetaType<QFileInfo>("QFileInfo");
            emit addMusic(pathName, false);      //false为收藏数据库
        }
    }

}

void Thread::saveList()
{
    if(Is_dafault)              //存储默认列表
    {
        QSqlDatabase database = QSqlDatabase::database("MusicData");
        QSqlQuery query(database);  //查询数据库中是否有和要添加的名字相同的音乐， 有的话取消添加
        qDebug() << "导入默认数据库";
        foreach(QString temp, paths) //从路径列表中取出每一条路径
        {
            QFileInfo info(temp);
            query.exec(QString("select * from Music where musicName = '%1'").arg(info.baseName()));
            if (query.next())
            {
                qDebug() << "已存在";
                continue;
            }
            query.prepare("insert into Music(musicName, musicPath) values(?, ?)");
            QString musicPath = info.absoluteFilePath();
            QString musicName = info.baseName();
            query.addBindValue(musicName);
            query.addBindValue(musicPath);
            query.exec();
        }
     }
    else
    {
        QSqlDatabase database2 = QSqlDatabase::database("MusicData2");
        QSqlQuery query(database2);  //查询数据库中是否有和要添加的名字相同的音乐， 有的话取消添加
        qDebug() << "导入收藏数据库";
        foreach(QString temp, paths) //从路径列表中取出每一条路径
        {
            QFileInfo info(temp);
            query.exec(QString("select * from MusicCollect where musicName = '%1'").arg(info.baseName()));
            if (query.next())
            {
                qDebug() << "已存在";
                continue;
            }
            query.prepare("insert into MusicCollect(musicName, musicPath) values(?, ?)");
            QString musicPath = info.absoluteFilePath();
            QString musicName = info.baseName();
            query.addBindValue(musicName);
            query.addBindValue(musicPath);
            query.exec();
        }
        qDebug() <<"ok";
    }
}

void Thread::setTyle(Thread::Type ty)
{
    type = ty;
}

void Thread::setPaths(QStringList &pa)
{
    this->paths = pa;
}

void Thread::setIsDafault(bool bo)
{
    this->Is_dafault = bo;
}

void Thread::setPath(QString pa)
{
    this->path = pa;
}

void Thread::deleteMusic()
{
    if(Is_dafault)              //存储默认列表
    {
        QSqlDatabase database = QSqlDatabase::database("MusicData");
        QSqlQuery query(database);
        qDebug() << "进入默认数据库";
        QFileInfo info(path);
        query.exec(QString("select * from Music where musicName = '%1'").arg(info.baseName()));
        if (query.next())
        {
            qDebug() << "已找到";
            int id = query.value(0).toInt();    //获取id
            query.exec(QString("delete from Music where id = %1").arg(id));
            qDebug() << "删除成功" << path;
        }

     }
    else
    {
        QSqlDatabase database2 = QSqlDatabase::database("MusicData2");
        QSqlQuery query(database2);
        qDebug() << "进入收藏数据库";
        QFileInfo info(path);
        query.exec(QString("select * from MusicCollect where musicName = '%1'").arg(info.baseName()));
        if (query.next())
        {
            qDebug() << "已找到";
            int id = query.value(0).toInt();    //获取id
            query.exec(QString("delete from MusicCollect where id = %1").arg(id));
            qDebug() << "删除成功" << path;
        }


    }
}

void Thread::deleteMusicAll()
{
    if(Is_dafault)              //存储默认列表
    {
        QSqlDatabase database = QSqlDatabase::database("MusicData");
        QSqlQuery query(database);
        qDebug() << "进入默认数据库";
        query.exec(QString("delete from Music"));
        qDebug() << "清空";

     }
    else
    {
        QSqlDatabase database2 = QSqlDatabase::database("MusicData2");
        QSqlQuery query(database2);
        qDebug() << "进入收藏数据库";
        query.exec(QString("delete from MusicCollect"));
        qDebug() << "清空";
    }
}







