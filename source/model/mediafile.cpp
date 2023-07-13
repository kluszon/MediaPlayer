#include <QDir>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>
#include "mediafile.h"

MediaFile::MediaFile(QString path, int duration, QString title, QString artist, QString album, QObject *parent) :
    m_path(path),
    m_duration(duration),
    m_title(title),
    m_artist(artist),
    m_album(album),
    QObject(parent)
{

}

MediaFile::MediaFile(QString path)
{
    QFileInfo mediaFileInfo(path);

    m_path = path;

    QString filePath = mediaFileInfo.path() + QDir::separator() + mediaFileInfo.fileName();
    QUrl mediaUrl = QUrl("file://" + filePath);

    m_url = mediaUrl;

    TagLib::FileRef fileRef(mediaUrl.path().toStdString().c_str());

    if(!fileRef.isNull() && fileRef.tag())
    {
        TagLib::Tag *tag = fileRef.tag();

        m_title = tag->title().toCString();
        m_artist = tag->artist().toCString();
        m_album = tag->album().toCString();
    }

    if(!fileRef.isNull() && fileRef.audioProperties())
    {
        TagLib::AudioProperties *properties = fileRef.audioProperties();

        m_duration = properties->length() * 1000;       ///< Convert duration to miliseconds
    }

    if(m_title.isEmpty()){
        m_title = "Unknown";
    }
    if(m_artist.isEmpty()){
        m_artist = "Unknown";
    }
    if(m_album.isEmpty()){
        m_album = "--";
   }
}

MediaFile::MediaFile(const MediaFile &other) :
    QObject(other.parent()),
    m_path(other.path()),
    m_duration(other.duration()),
    m_title(other.title()),
    m_artist(other.artist()),
    m_album(other.album())
{

}

const QString &MediaFile::fileName() const
{
    return m_fileName;
}

void MediaFile::setFileName(const QString &newFileName)
{
    if (m_fileName == newFileName)
        return;
    m_fileName = newFileName;
    emit fileNameChanged();
}

const QString &MediaFile::fileExtension() const
{
    return m_fileExtension;
}

void MediaFile::setFileExtension(const QString &newFileExtension)
{
    if (m_fileExtension == newFileExtension)
        return;
    m_fileExtension = newFileExtension;
    emit fileExtensionChanged();
}

const QString &MediaFile::title() const
{
    return m_title;
}

void MediaFile::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

const QString &MediaFile::artist() const
{
    return m_artist;
}

void MediaFile::setArtist(const QString &newArtist)
{
    if (m_artist == newArtist)
        return;
    m_artist = newArtist;
    emit artistChanged();
}

const QString &MediaFile::album() const
{
    return m_album;
}

void MediaFile::setAlbum(const QString &newAlbum)
{
    if (m_album == newAlbum)
        return;
    m_album = newAlbum;
    emit albumChanged();
}

int MediaFile::duration() const
{
    return m_duration;
}

void MediaFile::setDuration(int newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

bool MediaFile::selected() const
{
    return m_selected;
}

void MediaFile::setSelected(bool newSelected)
{
    if (m_selected == newSelected)
        return;
    m_selected = newSelected;
    emit selectedChanged();
}

bool MediaFile::fileExists() const
{
    return m_fileExists;
}

void MediaFile::setFileExists(bool newFileExists)
{
    if (m_fileExists == newFileExists)
        return;
    m_fileExists = newFileExists;
    emit fileExistsChanged();
}

float MediaFile::fileSize() const
{
    return m_fileSize;
}

void MediaFile::setFileSize(float newFileSize)
{
    if (qFuzzyCompare(m_fileSize, newFileSize))
        return;
    m_fileSize = newFileSize;
    emit fileSizeChanged();
}

const QString &MediaFile::path() const
{
    return m_path;
}

const QUrl &MediaFile::url() const
{
    return m_url;
}

void MediaFile::setUrl(const QUrl &newUrl)
{
    m_url = newUrl;
}
