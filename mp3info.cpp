#include "mp3info.h"

QString MP3INFO::getTag() const { return tag; }

void MP3INFO::setTag(const QString &value) { tag = value; }

QString MP3INFO::getMusicname() const { return musicname; }

void MP3INFO::setMusicname(const QString &value) { musicname = value; }

QString MP3INFO::getArtist() const { return artist; }

void MP3INFO::setArtist(const QString &value) { artist = value; }

QString MP3INFO::getAlbum() const { return album; }

void MP3INFO::setAlbum(const QString &value) { album = value; }

QString MP3INFO::getYear() const { return year; }

void MP3INFO::setYear(const QString &value) { year = value; }

QString MP3INFO::getGeneric() const { return generic; }

void MP3INFO::setGeneric(const QString &value) { generic = value; }

QString MP3INFO::getMusictype() const { return musictype; }

void MP3INFO::setMusictype(const QString &value) { musictype = value; }

MP3INFO::MP3INFO(QString tag, QString musicname, QString artist, QString album,
                 QString year, QString generic, QString musictype) {
  this->tag = tag;
  this->musicname = musicname;
  this->musictype = musictype;
  this->artist = artist;
  this->album = album;
  this->year = year;
  this->generic = generic;
}

QString MP3INFO::toString() {

  return "\ntag : " + getTag() + "\nmusicname : " + getMusicname() +
         "\nmusictype : " + getMusictype() + "\nartist : " + getArtist() +
         "\nalbum : " + getAlbum() + "\nyear : " + getYear() +
         "\ngeneric : " + getGeneric() + "\n";
}

MP3INFO::MP3INFO() {}
