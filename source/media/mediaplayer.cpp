#include "mediaplayer.h"
#include "mediamanager.h"
#include <QProcess>
#include <QAudio>
#include <QQmlEngine>

MediaPlayer::MediaPlayer() :
    m_currentState(0),
    m_currentMediaLoop(0),
    m_currentMediaTimePosition(0),
    m_autoStartPlayNext(false),
    m_volumeFactor(1.0)
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    connect(this, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(updateCurrentState(QMediaPlayer::State)));
    connect(this, SIGNAL(positionChanged(qint64)), this, SLOT(updateCurrentMediaTimePosition(qint64)));
    connect(this, &MediaPlayer::currentVolumeChanged, this, [this](int){updateVolume();});
    connect(this, &MediaPlayer::volumeFactorChanged, this, [this](double){updateVolume();});
    connect(this, &MediaPlayer::currentMediaLoopChanged, this, &MediaPlayer::updatePlaybackMode);
    connect(this, &MediaPlayer::autoStartPlayNextChanged, this, &MediaPlayer::updatePlaybackMode);

    createPlayList();
    setCurrentVolume(default_volume);
}

void MediaPlayer::createPlayList()
{
    m_playList = new QMediaPlaylist;
    m_playList->setPlaybackMode(QMediaPlaylist::Sequential);
    setPlaylist(m_playList);

    connect(m_playList, SIGNAL(mediaInserted(int, int)), this , SLOT(updateAutoplayAndRepeat(int, int)));
    connect(m_playList, SIGNAL(mediaRemoved(int, int)), this , SLOT(updateAutoplayAndRepeat(int, int)));
}

void MediaPlayer::setMediaPath(QString mediaFilePath)
{
    this->setMedia(QUrl::fromLocalFile(mediaFilePath));
}

int MediaPlayer::currentVolume() const
{
    return m_currentVolume;
}

bool MediaPlayer::currentState() const
{
    return m_currentState;
}

bool MediaPlayer::currentMediaLoop() const
{
    return m_currentMediaLoop;
}

void MediaPlayer::setCurrentVolume(int currentVolume)
{
    if (m_currentVolume == currentVolume)
        return;

    m_currentVolume = currentVolume;
    emit currentVolumeChanged(m_currentVolume);
}

void MediaPlayer::setCurrentState(bool currentState)
{
    if (m_currentState == currentState)
        return;

    m_currentState = currentState;
    emit currentStateChanged(m_currentState);
}

void MediaPlayer::setCurrentMediaLoop(bool currentMediaLoop)
{
    if (m_currentMediaLoop == currentMediaLoop)
        return;

    m_currentMediaLoop = currentMediaLoop;
    emit currentMediaLoopChanged(m_currentMediaLoop);
}


void MediaPlayer::setCurrentMediaTimePosition(qint64 currentMediaTimePosition)
{
    if (m_currentMediaTimePosition == currentMediaTimePosition)
        return;

    m_currentMediaTimePosition = currentMediaTimePosition;
    emit currentMediaTimePositionChanged(m_currentMediaTimePosition);
}

void MediaPlayer::setAutoStartPlayNext(bool autoStartPlayNext)
{
    if (m_autoStartPlayNext == autoStartPlayNext)
        return;

    m_autoStartPlayNext = autoStartPlayNext;
    emit autoStartPlayNextChanged(m_autoStartPlayNext);
}

void MediaPlayer::updatePlayList(MediaListModel *mediaListModel)
{
    QMediaPlaylist *oldPlayList = m_playList;

    createPlayList();

    foreach(auto media, mediaListModel->mediaListModel()){
        QUrl fileUrl = media->path();
        m_playList->addMedia(fileUrl);
    }

    oldPlayList->disconnect();
    oldPlayList->deleteLater();

    connect(m_playList, SIGNAL(currentMediaChanged(const QMediaContent&)), MediaManager::getInstance(), SLOT(updateCurrentIndex(const QMediaContent&)));
    connect(m_playList, SIGNAL(playbackModeChanged(QMediaPlaylist::PlaybackMode)), MediaManager::getInstance(), SLOT(updateNextIndex(QMediaPlaylist::PlaybackMode)));
}

void MediaPlayer::updateCurrentState(QMediaPlayer::State state)
{
    switch(state) {
    case PlayingState:{
        setCurrentState(true);
    }
        break;
    case StoppedState:
    case PausedState:
    default:
        setCurrentState(false);
        break;
    }
}

void MediaPlayer::updatePlaybackMode()
{
    if(currentMediaLoop() && autoStartPlayNext()){
        m_playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }else if(!currentMediaLoop() && autoStartPlayNext()){
        m_playList->setPlaybackMode(QMediaPlaylist::Sequential);
    }else if(currentMediaLoop() && !autoStartPlayNext()){
        m_playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }else{
        m_playList->setPlaybackMode(QMediaPlaylist::Sequential);
    }
}

void MediaPlayer::updateCurrentMediaTimePosition(qint64 timePosition)
{
    setCurrentMediaTimePosition(timePosition);
}

/*!
 * \brief MediaPlayer::updateAutoplayAndRepeat
 *
 * Update autoplay (hollow button) state and repeat (repeat button).
 *
 * \param start - int start position
 * \param end - int end possition
 */

void MediaPlayer::updateAutoplayAndRepeat(int start, int end)
{
    if(m_playList->mediaCount() == 0 ){
        setAutoStartPlayNext(false);
        setCurrentMediaLoop(false);
    }
}

void MediaPlayer::updateVolume()
{
    qreal linearVolume = QAudio::convertVolume(m_currentVolume / qreal(100.0),
                                                   QAudio::LogarithmicVolumeScale,
                                                   QAudio::LinearVolumeScale) * 100;

    int volume = qRound(linearVolume * m_volumeFactor);

    setVolume(volume);
}

double MediaPlayer::volumeFactor() const
{
    return m_volumeFactor;
}

void MediaPlayer::setVolumeFactor(double volumeFactor)
{
    if(volumeFactor == m_volumeFactor) {
        return;
    }

    m_volumeFactor = volumeFactor;
    emit volumeFactorChanged(volumeFactor);
}

QMediaPlaylist *MediaPlayer::playList() const
{
    return m_playList;
}

bool MediaPlayer::isMediaExistOnPlaylist(QMediaContent mediaContent)
{
    for (auto i = 0; i < m_playList->mediaCount(); i++)
    {
        if(m_playList->media(i) == mediaContent){
            return true;
        }
    }

    return false;
}

qint64 MediaPlayer::currentMediaTimePosition() const
{
    return m_currentMediaTimePosition;
}

bool MediaPlayer::autoStartPlayNext() const
{
    return m_autoStartPlayNext;
}

int MediaPlayer::mediaPlayListIndex(const QMediaContent &currentMediaContent)
{
    auto playListCount = m_playList->mediaCount();

    for(auto mediaIndex = 0; mediaIndex < playListCount; mediaIndex++){
        QMediaContent mediaFromPlaylist = m_playList->media(mediaIndex);

        if(currentMediaContent == mediaFromPlaylist){

            return mediaIndex;
        }
    }
    return -1;
}

