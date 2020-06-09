#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "mediatools.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QStandardItemModel>
#include <QThread>
#include <QTimer>
#include <QTreeView>
#include <QVBoxLayout>
#include <QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  /*
  voiceSlider : 音量调节控件
  videoSlider : 视频进度条
*/
  QSlider *voiceSlider, *videoSlider;

  /*
    play : 开始播放按键
    selectFiles : 选择需要进行播放的文件
    fullScreen : 全屏按键
    showPlayList : 显示播放列表
    voiceChange : 用于显示与关闭音量条
    preMusic : 返回到上一首歌曲/视频进行播放
    nextMusic : 切换到下一首歌曲/视频进行播放
*/

  QPushButton *play, *selectFiles, *fullScreen, *showPlayList, *voiceChange,
      *preMusic, *nextMusic;
  // playList : 用于存储播放媒体信息
  QStringList playList;
  /*
    timeLable : 用于显示当前时间进度
    musicLable : 用于显示当前播放的视频文件名称
    timeEndLabel : 用于显示歌曲/视频总长度
*/
  QLabel *timeLable, *musicLable, *timeEndLabel;
  //横向布局控件
  QHBoxLayout *hbox;
  //竖向布局控件
  QVBoxLayout *vbox;
  /*
    如果你对QMediaPlayer不熟悉的话，可以将此项目导入进qtcreator
    双击QMediaPlayer按f1即可查阅文档
    或者你可以去qt官方查询在线文档
*/
  QMediaPlayer *mediaPlay;
  QMediaPlaylist *mediaPlayList;
  //用于保存当前进度位置(进度条核心)
  qint64 positi = 0;
  //用于判断当前播放状态，详情可参考官方文档
  QMediaPlayer::State mediaState;
  //走进度条用的
  QTimer *qtimer;
  //以树状图显示播放文件信息
  QTreeView *treeView;
  //保存播放文件
  QStandardItemModel *model;
  //显示视频控件
  QVideoWidget *videoWidget;
  //  QMediaPlayer::State playState;
  int playState = 0, fullflag = 0, showPlayListState = 0, voiceChangeState = 0,
      musicLen = 0;
  MediaTools m;

public:
  //判断播放文件类型
  void checkPlay();
  //信号槽链接
  void connectFun();
  //添加播放文件到列表并显示
  void addTreeView();
  //显示核心布局控件
  void showLayout();
  //测试函数
  void test();
  //初始化函数
  void init();

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
