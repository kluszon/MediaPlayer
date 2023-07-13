#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "model/medialistmodel.h"

class MediaPlayer : public QMediaPlayer
{
    Q_OBJECT

public:
    Q_PROPERTY(int currentVolume READ currentVolume WRITE setCurrentVolume NOTIFY currentVolumeChanged)
    Q_PROPERTY(bool currentState READ currentState WRITE setCurrentState NOTIFY currentStateChanged)
    Q_PROPERTY(bool currentMediaLoop READ currentMediaLoop WRITE setCurrentMediaLoop NOTIFY currentMediaLoopChanged)
    Q_PROPERTY(qint64 currentMediaTimePosition READ currentMediaTimePosition WRITE setCurrentMediaTimePosition NOTIFY currentMediaTimePositionChanged)
    Q_PROPERTY(bool autoStartPlayNext READ autoStartPlayNext WRITE setAutoStartPlayNext NOTIFY autoStartPlayNextChanged)

    MediaPlayer();

    void createPlayList();

    void setMediaPath(QString mediaFilePath);
    int currentVolume() const;
    bool currentState() const;
    bool currentMediaLoop() const;

    QMediaPlaylist *playList() const;

    bool isMediaExistOnPlaylist(QMediaContent mediaContent);
    qint64 currentMediaTimePosition() const;
    bool autoStartPlayNext() const;

    int mediaPlayListIndex(const QMediaContent &currentMediaContent);

    double volumeFactor() const;

#ifdef QT_DEBUG
    inline static const int default_volume = 10;
#else
    inline static const int default_volume = 80;
#endif

    double volumeFadeOutFactor() const;

public slots:
    void setCurrentVolume(int currentVolume);
    void setCurrentState(bool currentState);
    void setCurrentMediaLoop(bool currentMediaLoop);
    void setCurrentMediaTimePosition(qint64 currentMediaTimePosition);
    void setAutoStartPlayNext(bool autoStartPlayNext);
    void updatePlayList(MediaListModel *mediaListModel);
    void setVolumeFactor(double volumeFactor);

private slots:
    void updateCurrentState(QMediaPlayer::State state);
    void updatePlaybackMode();
    void updateCurrentMediaTimePosition(qint64 timePosition);
    void updateAutoplayAndRepeat(int start, int end);
    void updateVolume();

signals:
    void currentVolumeChanged(int currentVolume);
    void currentStateChanged(bool currentState);
    void currentMediaLoopChanged(bool currentMediaLoop);
    void currentMediaTimePositionChanged(int currentMediaTimePosition);
    void autoStartPlayNextChanged(bool autoStartPlayNext);
    void volumeFactorChanged(double volumeFactor);

private:
    QMediaPlaylist *m_playList;
    bool m_currentState;                            ///< True media playing; false media pause or stop
    bool m_currentMediaLoop;
    qint64 m_currentMediaTimePosition;
    bool m_autoStartPlayNext;
    int m_currentVolume;
    double m_volumeFactor;                          ///< 0.0 - 1.0
};

#endif // MEDIAPLAYER_H
