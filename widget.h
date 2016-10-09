#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QStringList>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>
#include <QAction>
#include <QFileDialog>
#include <QFileInfo>
#include "MusicListWidget.h"
#include "MusicLrcLabel.h"
#include "SearchWidget.h"
#include "SkinWidget.h"
#include "connection.h"
#include "Thread.h"
#include <QDebug>
#include <QMap>
#include <QTextCodec>
#include <QTime>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QToolButton>
#include <QMediaMetaData>
#include <QTabWidget>
#include <QBitmap>
#include <QPixmap>
#include <QPicture>
#include "MiniWidget.h"
#include "DownloadWidget.h"
#include <QUrl>
#include "LrcThread.h"
#include "MusicThread.h"
#include "PicThread.h"
#include "SearchThread.h"
#include "ExtensionWidget.h"
#include "MusicDownThread.h"
#include <QMimeData>


class Thread;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    enum Request{LRC_DATA, PIC_DATA, MUSIC_DATA, PIC_DOWNLOAD, LRC_DOWNLOAD};//下载应答的类型

private:
    QLabel          *WelcomeLabel;                      //装B标签
    QLabel          *MusicInformation;                  //歌曲相关信息
    QHBoxLayout     *UpLayout;                          //顶层水平布局1
    QHBoxLayout     *UpLayout2;                         //顶层水平布局2
    QVBoxLayout     *UpLayout3;                         //顶层水平布局3
    QHBoxLayout     *MidLayout;                         //中层水平布局
    QHBoxLayout     *DownLayout;                        //底层水平布局
    QVBoxLayout     *MainLayoutL;                       //总体垂直布局左
    QHBoxLayout     *MainLayoutR;                       //总体垂直布局右
    QSlider         *SeekSlider;                        //进度条
    QLabel          *CurrentMusicTime;                  //歌曲当前时间
    QLabel          *TotallMusicTime;                   //歌曲总时间

    QTabWidget      *MusicWidget;                     //管理两个列表
    MusicListWidget *CollectListWidget;               //收藏列表
    MusicListWidget *DafaultListWidget;               //默认列表


    QPushButton     *extensionBtn;                      //拓展按钮

    MusicLrcLabel   *LrcLabel;                        //歌词

    QMediaPlayer    *MediaPlayer;                       //媒体播放器
    QMediaPlaylist  *DafaultMediaPlayList;              //默认
    QMediaPlaylist  *CollectMediaPlayList;              //收藏
    QStringList     DafaultMediaPathList;               //默认列表的路径
    QStringList     CollectMediaPathList;               //收藏列表的路径

    QPushButton     *miniBtn;                //迷你模式按钮
    QPushButton     *closeBtn;               //关闭按钮
    QPushButton     *minBtn;                 //最小化按钮
    QPushButton     *skinBtn;                //皮肤按钮

    QPushButton     *modelBtn;               //模式按钮
    QPushButton     *playOrPauseBtn;         //播放按钮
    QPushButton     *previousBtn;            //上一首按钮
    QPushButton     *nextBtn;                //下一首按钮
    QPushButton     *lrcBtn;                 //歌词按钮
    QPushButton     *volumeBtn;              //音量按钮
    QSlider         *volumeSlider;           //音量条

    SearchWidget    *Search;                //查找框
    SkinWidget      *skinWidget;            //皮肤框
    DownloadWidget  *downWidget;            //下载框
    MiniWidget      *mini;                  //迷你框
    ExtensionWidget *extensionWidget;       //拓展框

    QPushButton     *openFileBtn;           //打开文件
    QPushButton     *addFileBtn;            //添加文件
    QPushButton     *locationBtn;           //定位歌曲
    QPushButton     *searchBtn;             //查找歌曲
    QPushButton     *downloadBtn;           //下载歌曲按钮

    QMap<qint64, QString> LrcMap;            //储存歌曲歌词

    QSystemTrayIcon *TrayIcon;              //系统托盘图标
    QMenu *TrayIconMenu;                    //最小化系统菜单
    QAction *PlayOrPause;                   //播放or暂停
    QAction *Next;                          //下一首
    QAction *Previous;                      //上一首
    QAction *MusicLrc;                      //歌词
    QAction *Exit;                          //退出

    Thread *thread;                         //线程

    QMenu *MenuModel;                       //模式菜单
    QAction *CurrentItemInLoop;             //单曲循环
    QAction *Sequential;                    //顺序播放
    QAction *Random;                        //随机播放
    QAction *Loop;                          //列表循环
    void Init();                                        //初始化
    void CreateMenuModel();                             //创建播放模式菜单
    void CreateUpLayout();                              //创建顶层布局
    void CreateMidLayout();                             //创建中层布局
    void CreateListWidget();                            //创建中间列表TabWidget
    void CreateDownLayout();                            //创建下层布局
    void CreateMediaPlay();                             //创建媒体播放mediaplay和mediaplaylist
    void CreateTrayIcon();                              //创建最小化系统菜单
    void CreateThread();                                //创建线程
    void CreateMini();                                  //创建迷你模式
    void CreateSkin();                                  //创建换肤框
    void CreateDown();                                  //创建下载框
    void CreateFolder();                                //创建文件夹
    void CreateExtension();                             //创建拓展框
    void ResolveLrc(QString &FileName);                 //解析歌词

    bool Is_DafaultList;                                //true为默认列表，false为收藏列表
    bool Is_networkMusic;
    bool Is_LeftPress;                                  //左键是否被按下
    bool Is_picChanged;
    QPoint PressPositon;                                //左键按下的位置
    qint64 totall;                                      //歌曲总长度
    QString currentMusicName;
    QString currentArtist;
    QString currentPath;
    int currentIndex;
    QString downFolderPath;                             //下载文件夹的路径
    QString skinTemp;

protected:
    void closeEvent(QCloseEvent *event);            //重写关闭事件
    void mouseMoveEvent(QMouseEvent *event);         //重写鼠标移动事件
    void mousePressEvent(QMouseEvent *event);        //重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event);     //重写鼠标松开事件
    void paintEvent(QPaintEvent */*event*/);        //重绘
    void dragEnterEvent(QDragEnterEvent *event);    //拖放事件
    void dropEvent(QDropEvent *event);              //拖放事件

private slots:
    void ClickedExtension();                        //扩展框
    void ClickedOpenFile();                         //导入音乐文件夹
    void ClickedAddFile();                          //添加音乐文件
    void ClickedPlayOrPause();                      //播放or暂停
    void ClickedPrevious();                         //上一首
    void ClickedNext();                             //下一首
    void ClickedMusicLrc();                         //歌词
    void ClickedLocation();                         //当前播放歌曲定位
    void ClickedSearch();                           //查找歌曲
    void ClickedSkin();                             //皮肤
    void ClickedClose();                            //关闭按钮
    void ClickedMin();                              //最小化按钮
    void ClickedMini();                             //迷你模式按钮
    void ClickedDownload();                         //下载按钮
    void showMainWidget();                          //显示主窗口
    void ChangeSkin(int index);                     //更换皮肤
    void DurationChanged(qint64 max);               //歌曲总时间
    void ValueChanged();                            //设置歌曲进度
    void PositionChanged(qint64 position);          //歌曲当前时间
    void StateChanged(QMediaPlayer::State state);   //状态的变化
    void WidgetClearList();                         //清空播放列表
    void WidgetPlayOn(int index);                   //播放
    void WidgetRemoveOn(int start,int end);         //移除
    void WidgetDoubleClicked(int index);            //双击播放
    void WidgetCollectOn(int start,int end);        //收藏
    void TrayIconActivated(QSystemTrayIcon::ActivationReason activationReason);
    void SetVolume(int vol);                        //设置音量
    void setMute();                                 //设置静音
    void OnCurrentItemInLoop();                     //单曲循环模式
    void OnSequential();                            //顺序播放模式
    void OnRandom();                                //随机播放模式
    void OnLoop();                                  //列表循环模式
    void UpdateLrc(qint64 time);                    //在播放时间改变时，更新每一句歌词
    void ShowSearch();                              //是否显示查找框
    void SearchMusic();                             //查找列表歌曲
    void addMusic(QFileInfo name,bool is_dafault);  //从数据库导出到播放列表
    void downloadPic(QString name);                 //下载歌手图片
    void downloadMusic();                           //下载歌曲
    void downloadLrcOk(QString lrcPath);            //下载歌词完毕
    void downMusicOk(bool bo, QString musicFilePath);//下载歌曲完毕
    void downPicOk(bool bo, QString picPath);       //下载图片完毕
    void extenMusic(int rol, QString musicName, QString artist, QString urlPic, QString url);
    void downMusicFromEx(QString url,QString musicName,QString artists);
    void picChanged();                              //歌词写真



};

#endif // WIDGET_H
