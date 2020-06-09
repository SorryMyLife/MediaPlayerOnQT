#ifndef MEDIATOOLS_H
#define MEDIATOOLS_H
/*
如果你需要进行mp3文件信息解析
可以采用MP3INFO toMp3Info(QString path);函数
你只需要输入媒体文件路径即可获取到相应信息

*/
#include "mp3info.h"
#include <QDebug>
#include <QFile>
#include <QFileDevice>
#include <QFileInfo>
#include <QIODevice>
#include <QString>
class MediaTools {

public:
  /**
MP3INFO toMp3Info(QString path)采用ID3V1结构进行mp3文件解析
数据可能不是很准确，但的确是最简单快捷

void Mp3ID3V2_3(QString path)采用ID3V2结构进行mp3文件解析
目前v2版本并没有有效正确解析，等待后来版本更新与维护

*/
  MP3INFO toMp3Info(QString path);
  void seekFiles(int &len, QFile &f);
  void Mp3ID3V2_3(QString path);
  void test();

public:
  MediaTools();
};

#endif // MEDIATOOLS_H
