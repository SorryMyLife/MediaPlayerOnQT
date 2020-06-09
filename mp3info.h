#ifndef MP3INFO_H
#define MP3INFO_H
#include <QString>
class MP3INFO {

  /**
主要用于解析mp3文件

*/

public:
  QString tag, musicname, artist, album, year, generic, musictype;
  QString toString();

public:
  MP3INFO();

  /**
保存解析后的数据
*/

  MP3INFO(QString tag, QString musicname, QString artist, QString album,
          QString year, QString generic, QString musictype);

  QString getTag() const;
  void setTag(const QString &value);
  QString getMusicname() const;
  void setMusicname(const QString &value);
  QString getArtist() const;
  void setArtist(const QString &value);
  QString getAlbum() const;
  void setAlbum(const QString &value);
  QString getYear() const;
  void setYear(const QString &value);
  QString getGeneric() const;
  void setGeneric(const QString &value);
  QString getMusictype() const;
  void setMusictype(const QString &value);
};

#endif // MP3INFO_H
