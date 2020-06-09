#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  showLayout();
}

void MainWindow::showLayout() {
  init();
  QWidget *widget = new QWidget();

  mediaPlay->setPlaylist(mediaPlayList);
  mediaPlay->setVideoOutput(videoWidget);
  videoSlider->setOrientation(Qt::Horizontal);
  videoSlider->setMinimum(0);
  qtimer->setInterval(1000);
  qtimer->start();
  musicLable->setAlignment(Qt::AlignCenter);
  timeLable->setAlignment(Qt::AlignLeft);
  timeEndLabel->setAlignment(Qt::AlignRight);
  voiceSlider->setWindowFlags(Qt::FramelessWindowHint);
  voiceSlider->setMaximum(100);
  voiceSlider->setValue(100);
  vbox->addWidget(musicLable, 1);
  vbox->addWidget(videoWidget, 1);

  hbox->addWidget(timeLable);
  hbox->addWidget(timeEndLabel);
  vbox->addLayout(hbox);
  hbox = new QHBoxLayout();
  vbox->addWidget(videoSlider);
  hbox->addWidget(preMusic);
  hbox->addWidget(play);
  hbox->addWidget(nextMusic);
  hbox->addWidget(voiceChange);
  hbox->addWidget(selectFiles);
  hbox->addWidget(fullScreen);
  hbox->addWidget(showPlayList);
  vbox->addLayout(hbox);
  widget->setLayout(vbox);
  setCentralWidget(widget);
}

void MainWindow::checkPlay() {

  if (mediaPlay->currentMedia().canonicalUrl().fileName().indexOf("mp4") !=
          -1 ||
      mediaPlay->currentMedia().canonicalUrl().fileName().indexOf("avi") !=
          -1 ||
      mediaPlay->currentMedia().canonicalUrl().fileName().indexOf("wav") !=
          -1 ||
      mediaPlay->currentMedia().canonicalUrl().fileName().indexOf("ts") != -1 ||
      mediaPlay->currentMedia().canonicalUrl().fileName().indexOf("flv") !=
          -1) {
    musicLable->setHidden(true);
    videoWidget->setHidden(false);
  } else {
    musicLable->setText(windowTitle());
    musicLable->setHidden(false);
    videoWidget->setHidden(true);
  }
}

void MainWindow::addTreeView() {
  treeView->setModel(model);
  treeView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
  model->setHorizontalHeaderLabels({"音乐播放列表"});
}

void MainWindow::connectFun() {

  connect(videoSlider, &QSlider::sliderMoved, [=]() {
    checkPlay();
    mediaPlay->stop();
    timeLable->setText("当前时间: " + QString::number(videoSlider->value()));
    positi = videoSlider->value();
    mediaPlay->setPosition(positi);
    mediaPlay->play();
  });

  connect(mediaPlay, &QMediaPlayer::currentMediaChanged, [=]() {
    checkPlay();
    QString playNAME = mediaPlay->currentMedia().canonicalUrl().fileName();
    setWindowTitle("正在播放: " + playNAME);
    qDebug() << playNAME;
  });

  connect(play, &QPushButton::clicked, [=]() {
    checkPlay();
    videoSlider->setMaximum(mediaPlay->duration());
    timeEndLabel->setText("总时长: " + QString::number(mediaPlay->duration()));
    timeLable->setText("当前时间: " + QString::number(positi));
    test();
  });

  connect(qtimer, &QTimer::timeout, [=]() {
    if (mediaState != QMediaPlayer::StoppedState) {
      videoSlider->setValue(mediaPlay->position());
      timeLable->setText("当前时间: " + QString::number(videoSlider->value()));
      qDebug() << mediaPlay->volume();
    }
    if (mediaPlay->position() == mediaPlay->duration()) {
      play->setText("播放");
    }
  });

  connect(fullScreen, &QPushButton::clicked, [=]() {
    if (fullflag == 0) {
      fullScreen->setText("恢复");
      showFullScreen();
      fullflag++;
    } else {
      fullScreen->setText("全屏");
      showNormal();
      fullflag = 0;
    }
  });

  connect(selectFiles, &QPushButton::clicked, [=]() {
    musicLen = 0;
    if (!mediaPlayList->isEmpty()) {
      mediaPlayList->clear();
      model->clear();
    }
    mediaPlay->stop();
    QStringList files = QFileDialog::getOpenFileNames(
        this, "选择媒体文件", QDir::currentPath(),
        "Media (*.mp3 *.mp4 *.m4a *.aac *.acc *.avi)");

    foreach (QString s, files) {
      QFileInfo info(s);
      if (info.isFile() && info.size() > 0) {
        mediaPlayList->addMedia(QUrl(info.absoluteFilePath()));
        model->appendRow(new QStandardItem(info.fileName()));
        musicLen++;
      } else {
        QMessageBox::critical(this, "错误", "请确认此文件是正确的媒体文件",
                              QMessageBox::Yes);
      }
    }
  });

  connect(showPlayList, &QPushButton::clicked, [=]() {
    addTreeView();
    if (showPlayListState == 0) {
      treeView->setCurrentIndex(model->index(mediaPlayList->currentIndex(), 0));
      showPlayList->setText("关闭播放列表");
      treeView->show();
      showPlayListState++;
    } else {
      showPlayList->setText("显示播放列表");
      treeView->close();
      showPlayListState = 0;
    }
  });

  connect(treeView, &QTreeView::doubleClicked, [=]() {
    QString nowMusic = treeView->currentIndex().data().toString();
    int index = treeView->currentIndex().row();
    mediaPlayList->setCurrentIndex(index);
    mediaPlay->setPosition(mediaPlay->position());
    videoSlider->setValue(mediaPlay->position());
    test();
  });

  connect(voiceSlider, &QSlider::sliderMoved,
          [=]() { mediaPlay->setVolume(voiceSlider->value()); });

  connect(voiceChange, &QPushButton::clicked, [=]() {
    if (voiceChangeState == 0) {
      voiceChange->setText("关闭音量调节");
      voiceSlider->show();
      voiceChangeState++;
    } else {
      voiceChange->setText("音量");
      voiceSlider->close();
      voiceChangeState = 0;
    }
  });

  connect(preMusic, &QPushButton::clicked, [=]() {
    if (mediaPlayList->currentIndex() == 0) {
      mediaPlayList->setCurrentIndex(musicLen);
    } else {
      mediaPlayList->setCurrentIndex(mediaPlayList->currentIndex() - 1);
    }
    test();
  });

  connect(nextMusic, &QPushButton::clicked, [=]() {
    if (mediaPlayList->currentIndex() < (musicLen - 1)) {
      mediaPlayList->setCurrentIndex(mediaPlayList->currentIndex() + 1);
    } else if (mediaPlayList->currentIndex() == (musicLen - 1)) {
      mediaPlayList->setCurrentIndex(0);
    }
    test();
  });
}

void MainWindow::test() {
  if (mediaState != QMediaPlayer::PlayingState) {
    mediaState = QMediaPlayer::PlayingState;
    mediaPlay->setPosition(positi);
    videoSlider->setValue(positi);
    //    positi = 0;
    play->setText("停止");
    mediaPlay->play();
  } else {
    mediaState = QMediaPlayer::StoppedState;
    positi = mediaPlay->position();
    play->setText("播放");
    mediaPlay->stop();
  }
}

void MainWindow::init() {
  timeLable = new QLabel("时间");
  musicLable = new QLabel("音乐");
  timeEndLabel = new QLabel("总时长");
  play = new QPushButton("开始播放");

  fullScreen = new QPushButton("全屏");
  selectFiles = new QPushButton("选择播放文件");
  showPlayList = new QPushButton("显示播放列表");
  voiceChange = new QPushButton("音量调节");
  preMusic = new QPushButton("上一首");
  nextMusic = new QPushButton("下一首");

  vbox = new QVBoxLayout();
  hbox = new QHBoxLayout();

  mediaPlay = new QMediaPlayer();
  mediaPlayList = new QMediaPlaylist();
  voiceSlider = new QSlider();
  videoSlider = new QSlider();
  qtimer = new QTimer();

  treeView = new QTreeView();
  model = new QStandardItemModel(treeView);
  videoWidget = new QVideoWidget();
  connectFun();
}

MainWindow::~MainWindow() { delete ui; }
