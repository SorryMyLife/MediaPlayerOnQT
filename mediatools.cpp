#include "mediatools.h"
#include <iostream>

MP3INFO MediaTools::toMp3Info(QString path) {
  int part = 128;
  QString tag, musicname, artist, album, year, generic, musictype;
  QFile f(path);
  f.open(QFile::ReadOnly);
  f.seek(f.size() - part);
  part = part - 3;
  tag = QString::fromLocal8Bit(f.readLine(4));
  f.seek(f.size() - part);
  part = part - 30;
  musicname = QString::fromLocal8Bit(f.readLine(31));
  f.seek(f.size() - part);
  part = part - 30;
  artist = QString::fromLocal8Bit(f.readLine(31));
  f.seek(f.size() - part);
  part = part - 30;
  album = QString::fromLocal8Bit(f.readLine(31));
  f.seek(f.size() - part);
  part = part - 4;
  year = QString::fromLocal8Bit(f.readLine(5));
  f.seek(f.size() - part);
  part = part - 30;
  generic = QString::fromLocal8Bit(f.readLine());
  f.seek(f.size() - 1);
  musictype = QString::fromLocal8Bit(f.readLine(1));
  f.close();
  return MP3INFO(tag, musicname, artist, album, year, generic, musictype);
}

void MediaTools::seekFiles(int &len, QFile &f) {
  QByteArray by;
  f.seek(len);
  qDebug() << "seekFiles  0 ::" << QString::fromLocal8Bit(f.readLine(5));
  f.seek(len + 4);
  by = f.read(4);
  qDebug() << "seekFiles  1 ::" << by;
  f.seek(len + 4 + 4);
  qDebug() << "seekFiles  2 ::" << QString::fromLocal8Bit(f.readLine(3));
  int FSize;
  FSize = by[0] * 0x100000000 + by[1] * 0x10000 + by[2] * 0x100 + by[3];
  qDebug() << "seekFiles  fsize ::" << FSize;
  f.seek(len + 11);
  qDebug() << "seekFiles  data ::" << QString::fromLocal8Bit(f.readLine());
  len = len + 10 + FSize;
  qDebug() << "next positi ::: " << len << "\n";
}

void MediaTools::Mp3ID3V2_3(QString path) {
  QFile f(path);
  f.open(QFile::ReadOnly);
  QByteArray by;
  qDebug() << "0 ::" << QString::fromLocal8Bit(f.readLine(4));
  f.seek(3);
  qDebug() << "1 ::" << QString::fromLocal8Bit(f.readLine(2));
  f.seek(4);
  qDebug() << "2 ::" << QString::fromLocal8Bit(f.readLine(2));
  f.seek(5);
  qDebug() << "3 ::" << QString::fromLocal8Bit(f.readLine(2));
  f.seek(6);
  by = f.read(4);
  qDebug() << "4 ::" << by;
  int len = 10;
  int total_size;

  total_size = (by[0] & 0x7F) * 0x200000 + (by[1] & 0x7F) * 0x400 +
               (by[2] & 0x7F) * 0x80 + (by[3] & 0x7F);
  qDebug() << total_size;
  seekFiles(len, f);
  seekFiles(len, f);
  seekFiles(len, f);
  seekFiles(len, f);
  seekFiles(len, f);
  seekFiles(len, f);
  seekFiles(len, f);
  seekFiles(len, f);

  f.close();
}

void MediaTools::test() {
  QString path = "E:/test/files/uu.mp3";
  Mp3ID3V2_3(path);
}

MediaTools::MediaTools() {}
