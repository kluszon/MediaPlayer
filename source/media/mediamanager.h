#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <QFileInfo>
#include <QObject>

#include "model/medialistmodel.h"
#include "mediaplayer.h"

class MediaManager : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(MediaListModel* mediaListModel READ mediaListModel NOTIFY mediaListModelChanged)
    Q_PROPERTY(int currentPlayingMediaIndex READ currentPlayingMediaIndex WRITE setCurrentPlayingMediaIndex NOTIFY currentPlayingMediaIndexChanged)
    Q_PROPERTY(int currentSelectedMediaIndex READ currentSelectedMediaIndex WRITE setCurrentSelectedMediaIndex NOTIFY currentSelectedMediaIndexChanged)
    Q_PROPERTY(MediaPlayer* mediaPlayer READ mediaPlayer WRITE setMediaPlayer NOTIFY mediaPlayerChanged)
    Q_PROPERTY(QString currentTitle READ currentTitle WRITE setCurrentTitle NOTIFY currentTitleChanged)
    Q_PROPERTY(QString currentArtist READ currentArtist WRITE setCurrentArtist NOTIFY currentArtistChanged)
    Q_PROPERTY(int currentMediaDuration READ currentMediaDuration WRITE setCurrentMediaDuration NOTIFY currentMediaDurationChanged)

    static MediaManager *getInstance();

    Q_INVOKABLE bool addMedia(QString path);
    Q_INVOKABLE bool removeMedia(const int mediaIndex);
    Q_INVOKABLE bool playCurrentMedia(int newPosition = 0);
    Q_INVOKABLE void playMedia(int newPosition = 0);
    Q_INVOKABLE void pauseMedia();
    Q_INVOKABLE void stopMedia();
    Q_INVOKABLE void previoseMedia();
    Q_INVOKABLE void nextMedia();

    Q_INVOKABLE void setNewPosition(int newTimePosition);

    MediaListModel* mediaListModel() const;

    int currentSelectedMediaIndex() const;

    MediaPlayer *mediaPlayer() const;
    void setMediaPlayer(MediaPlayer *newMediaPlayer);
    const QString &currentTitle() const;
    const QString &currentArtist() const;
    int currentMediaDuration() const;
    int currentPlayingMediaIndex() const;

public slots:
    void setCurrentSelectedMediaIndex(int newCurrentMediaIndex);
    void setCurrentPlayingMediaIndex(int newCurrentPlayingMediaIndex);
    void setCurrentTitle(const QString &newCurrentTitle);
    void setCurrentArtist(const QString &newCurrentArtist);
    void setCurrentMediaDuration(int newCurrentMediaDuration);
    void addMediaToPlaylist(const QModelIndex &parent, int first, int last);
    void updateCurrentMediaDetails(int currentMediaIndex);

signals:
    void mediaListModelChanged();
    void currentSelectedMediaIndexChanged(int);
    void currentPlayingMediaIndexChanged(int);
    void mediaPlayerChanged();
    void currentTitleChanged();
    void currentArtistChanged();
    void currentMediaDurationChanged();

private:
    MediaManager(QObject *parent = nullptr);
    static MediaManager *m_instance;
    static MediaFile* createMediaFile(QFileInfo mediaFileInfo);
    MediaListModel *m_mediaListModel;
    MediaPlayer *m_mediaPlayer;
    int m_currentSelectedMediaIndex;
    int m_currentPlayingMediaIndex;
    QString m_currentTitle;
    QString m_currentArtist;
    int m_currentMediaDuration;
};

#endif // MEDIAMANAGER_H
