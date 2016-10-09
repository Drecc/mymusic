#include "LrcWidget.h"

LrcWidget::LrcWidget(QMediaPlayer *player, QMap<qint64, QString> *map, QWidget *parent)
    : player(player), map(map),QLabel(parent),lineHeight(32)
{
    initMenu();
    curRow = -1;
    connect(player,SIGNAL(mediaChanged(QMediaContent)),this,SLOT(mediaChanged(QMediaContent)));
    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(timeOut()) );

    /// 用于检测并设置当前行
    checkCurRowTimer = new QTimer(this);
    connect( checkCurRowTimer, SIGNAL(timeout()), this, SLOT(checkCurRow()) );

    widdlyTimer = new QTimer(this);
    connect( widdlyTimer, SIGNAL(timeout()), this, SLOT(widdlyTimeOut()) );

    lrcFont.setFamily("Times New Roman"); // 字体
    lrcFont.setBold(true);
    lrcFont.setPointSize(lineHeight - 13);
    fontColor.setRgb(255,255,255);
}

LrcWidget::~LrcWidget()
{

}

void LrcWidget::seekLrc()
{
    if ( !map || map->isEmpty() )
        return ;

    qint64 pos = player->position();
    QList<qint64> tList = map->keys();

    for ( int i = 0; i < tList.size() - 1; i++ )
    {
        if ( pos > tList.at(i) && pos < tList.at(i + 1) )
        {
            curRow = i;
            y = height() / 2 - curRow * lineHeight + 0;
            update();
            break;
        }
    }
    timer->setInterval( 600 );  // 防止残余上次的速度！！歌词走得过快
}

void LrcWidget::init()
{
    if ( !map || map->isEmpty() )
        return ;

    y = this->height() / 2 + 0;
    curRow = -1;

    step = 0;
}

void LrcWidget::initMenu()
{
    menu = new QMenu(this);

    pic = new QAction(tr("封面写真"),this);
    pic->setIcon(QIcon(tr(":/images/picCover.png")));

    connect(pic,SIGNAL(triggered()),this,SIGNAL(picChanged()));
}

void LrcWidget::play()
{
    checkCurRowTimer->start(20);
    timer->start(1000);
    widdlyTimer->start(40);
}

void LrcWidget::pause()
{
    if ( timer->isActive() )
        timer->stop();

    if ( widdlyTimer->isActive() )
        widdlyTimer->stop();

    if ( checkCurRowTimer->isActive() )
        checkCurRowTimer->stop();
}

void LrcWidget::timeOut()
{
    scroll(0, -1);
    y--;
}

void LrcWidget::checkCurRow()
{
    if ( !map || map->isEmpty() )
        return ;

    qint64 pos = player->position();
    QList<qint64> tList = map->keys();

    for ( int i = 0; i < tList.size(); i++ )
    {
        if ( pos > tList.at(i) - 70 && pos < tList.at(i) && curRow != i )
        {
            curRow = i;

            if ( i + 1 < tList.size() )
            {
                int dt = tList.at(i + 1) - tList.at(i);
                if ( dt <= 0 )
                    dt = 1000;
                /// 落后、过快修补
                int ddt = dt / lineHeight;
                if ( y + curRow * lineHeight > height() / 2 + 30 )
                    ddt = ( ddt - 40 > 0 ) ? ddt - 40 : 30;
                else if ( y + curRow * lineHeight < height() / 2 - 20 )
                    ddt += 50;
                timer->setInterval( ddt );

                //////////////////////////////////////
                /// 归零该行歌词启动计时器
                widdlyTimer->stop();
                wid.clear();
                step = 0;
                QFontMetrics metrics(font());

                for ( int index = 0; index < map->value(tList.at(curRow)).size(); index++ )
                    wid.insert( index, 0 );

                // 保证唱完这一行，刚好滚动完
                if ( !map->value(tList.at(curRow)).isEmpty() )
                {
                    int speed = dt / metrics.width(map->value(tList.at(curRow)));
                    speed = ( speed < 50 && speed > 0 ) ? speed : 40;
                    widdlyTimer->start(speed);
                }
            }
            break;
        }
    }
}

void LrcWidget::widdlyTimeOut()
{
    if ( wid.size() == 0 || map->isEmpty() || !map )
        return ;

    step++;
    int i = 0;

    foreach( QString str, *map )
    {
        if ( i++ == curRow )
        {
            for( int s = step, n = 0; s > 0 && n < str.size(); s--, n++ )
            {
                if ( wid.value(n) <= 15 )
                    wid.insert( n, s );
            }
        }
    }
}

void LrcWidget::mediaChanged(QMediaContent)
{
    pause();
    play();
    seekLrc();
}

void LrcWidget::enterEvent(QEvent *)
{
    setCursor( Qt::PointingHandCursor );
}

void LrcWidget::paintEvent(QPaintEvent *event)
{
    if ( map->isEmpty() || !map )
    {
        QLabel::paintEvent(event);
        return ;
    }
    QPainter paint(this);
    paint.setFont( lrcFont );
    int i = 0, a = 255;
    foreach( QString str, *map )
    {

        // 只输出窗口内部的歌词
        if ( y + lineHeight * i >= -20 && y + lineHeight * i < height() && curRow != i)
        {
            // 上下渐隐
            a = 255 - abs(curRow - i) * 250 * 2 * lineHeight / height();
            a = ( a > 0 ) ? a : 30;
            a = ( a < 255 ) ? a : 255;

            // 更改成员数据颜色的透明度
            fontColor.setAlpha( a );
            paint.setPen( fontColor );
            paint.drawText( 0, y + lineHeight * i, width(),
                             lineHeight, Qt::AlignCenter, str );

        }
        else if ( curRow == i )
        {
            QColor color;
            QFontMetrics metrics(lrcFont);
            int x = ( width() - metrics.width(str) ) / 2;
            int top = y + lineHeight * i + 16;
            color.setHsv(240,255,255);
            paint.setPen( color );
            paint.drawText( x, top -metrics.height() + lineHeight + 8,str);
        }
        i++;

    }
}

void LrcWidget::resizeEvent(QResizeEvent *)
{
    y = height() / 2 - curRow * lineHeight + 0;
}

void LrcWidget::contextMenuEvent(QContextMenuEvent *event)
{
    menu->addAction(pic);
    menu->exec(event->globalPos());
}

void LrcWidget::hideEvent(QHideEvent *)
{
    pause();
}

void LrcWidget::showEvent(QShowEvent *)
{
    if ( player->state() == QMediaPlayer::PlayingState )
    {
        play();
        seekLrc();
    }
}
