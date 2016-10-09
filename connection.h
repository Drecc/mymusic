#ifndef CONNECTION
#define CONNECTION
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
static bool createConnection()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE","MusicData");//数据库连接名为MusicData 默认列表
    QSqlDatabase database2 = QSqlDatabase::addDatabase("QSQLITE","MusicData2");//收藏列表
    database.setDatabaseName("Music.db");//设置数据库的名字
    database2.setDatabaseName("MusicCollect.db");
    if(!database.open() || !database2.open())
    {
        return false;
    }
    QSqlQuery query(database),query2(database2);
    query.exec("CREATE TABLE Music(id INTEGER primary key AUTOINCREMENT, "
               "musicName varchar, musicPath verchar)");
                                    //AUTOINCREMENT自动添加键值
    query2.exec("CREATE TABLE MusicCollect(id INTEGER primary key AUTOINCREMENT,"
                " musicName varchar, musicPath verchar)");
                                    //AUTOINCREMENT自动添加键值
    return true;

}

#endif // CONNECTION

