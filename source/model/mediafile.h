#ifndef MEDIAFILE_H
#define MEDIAFILE_H

#include <QObject>
#include <QUrl>

#include "tag.h"
#include "fileref.h"
#include "tpropertymap.h"

using namespace TagLib;

class MediaFile : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString fileExtension READ fileExtension WRITE setFileExtension NOTIFY fileExtensionChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString album READ album WRITE setAlbum NOTIFY albumChanged)
    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(bool fileExists READ fileExists WRITE setFileExists NOTIFY fileExistsChanged)
    Q_PROPERTY(float fileSize READ fileSize WRITE setFileSize NOTIFY fileSizeChanged)

    MediaFile(QString path, int duration, QString title = "Unknown", QString artist = "Unknown",
                       QString album = "---", QObject *parent = nullptr);
    MediaFile(QString path);
    explicit MediaFile(const MediaFile &other);

    const QString &fileName() const;
    void setFileName(const QString &newFileName);

    const QString &fileExtension() const;
    void setFileExtension(const QString &newFileExtension);

    const QString &title() const;
    void setTitle(const QString &newTitle);

    const QString &artist() const;
    void setArtist(const QString &newArtist);

    const QString &album() const;
    void setAlbum(const QString &newAlbum);

    int duration() const;
    void setDuration(int newDuration);

    bool selected() const;
    void setSelected(bool newSelected);

    bool fileExists() const;
    void setFileExists(bool newFileExists);

    float fileSize() const;
    void setFileSize(float newFileSize);

    const QString &path() const;

    const QUrl &url() const;
    void setUrl(const QUrl &newUrl);

signals:

    void fileNameChanged();
    void fileExtensionChanged();
    void titleChanged();
    void artistChanged();
    void albumChanged();
    void durationChanged();
    void selectedChanged();
    void fileExistsChanged();
    void fileSizeChanged();

private:
    QString m_fileName;
    QString m_fileExtension;
    QString m_path;
    QUrl m_url;
    QString m_title;
    QString m_artist;
    QString m_album;
    int m_duration;
    bool m_selected;
    bool m_fileExists;
    float m_fileSize;
};

#endif // MEDIAFILE_H
