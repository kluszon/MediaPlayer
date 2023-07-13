#include "mediamanager.h"
#include <QDir>

MediaManager *MediaManager::m_instance = nullptr;

MediaManager::MediaManager(QObject *parent) :
    m_mediaListModel(new MediaListModel()),
    m_mediaPlayer(new MediaPlayer()),
    m_currentSelectedMediaIndex(-1),
    m_currentPlayingMediaIndex(-1),
    m_currentTitle(""),
    m_currentArtist(""),
    m_currentMediaDuration(0),
    QObject(parent)
{
    connect(this, SIGNAL(currentPlayingMediaIndexChanged(int)), this, SLOT(updateCurrentMediaDetails(int)));
    connect(m_mediaListModel, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(addMediaToPlaylist(QModelIndex,int,int)));
}

MediaManager *MediaManager::getInstance()
{
    if(m_instance == nullptr){
        m_instance = new MediaManager();
    }

    return m_instance;
}

bool MediaManager::addMedia(QString path)
{
#ifdef Q_OS_LINUX
    path.prepend(QDir::separator());
#endif

    QSharedPointer<MediaFile> mediaFile = QSharedPointer<MediaFile>(new MediaFile(path));

    m_mediaListModel->addMedia(mediaFile);
}

bool MediaManager::removeMedia(const int mediaIndex)
{
    m_mediaListModel->removeMedia(mediaIndex);
}

void MediaManager::playMedia(int newPosition)
{
    setCurrentPlayingMediaIndex(currentSelectedMediaIndex());

    if(m_mediaPlayer->state() == QMediaPlayer::PlayingState){
        stopMedia();
    }

    if(currentPlayingMediaIndex() >= 0)
    {
        if(m_mediaPlayer->playList()->currentIndex() != currentPlayingMediaIndex()){
            m_mediaPlayer->playList()->setCurrentIndex(currentPlayingMediaIndex());
        }

        m_mediaPlayer->play();

        if(newPosition != 0 &&
                newPosition != m_mediaPlayer->currentMediaTimePosition())
        {
            QMetaObject::invokeMethod(m_mediaPlayer, "setPosition", Qt::QueuedConnection, Q_ARG(qint64, newPosition));
        }
    }
}

void MediaManager::pauseMedia()
{
    m_mediaPlayer->pause();
}

void MediaManager::stopMedia()
{
    m_mediaPlayer->stop();
}

void MediaManager::previoseMedia()
{
}

void MediaManager::nextMedia()
{

}

void MediaManager::setNewPosition(int newTimePosition)
{
    m_mediaPlayer->setPosition(newTimePosition);
}

MediaListModel *MediaManager::mediaListModel() const
{
    return m_mediaListModel;
}

int MediaManager::currentSelectedMediaIndex() const
{
    return m_currentSelectedMediaIndex;
}

void MediaManager::setCurrentSelectedMediaIndex(int newCurrentMediaIndex)
{
    if (m_currentSelectedMediaIndex == newCurrentMediaIndex)
        return;
    m_currentSelectedMediaIndex = newCurrentMediaIndex;
    emit currentSelectedMediaIndexChanged(newCurrentMediaIndex);
}

MediaPlayer *MediaManager::mediaPlayer() const
{
    return m_mediaPlayer;
}

void MediaManager::setMediaPlayer(MediaPlayer *newMediaPlayer)
{
    if (m_mediaPlayer == newMediaPlayer)
        return;
    m_mediaPlayer = newMediaPlayer;
    emit mediaPlayerChanged();
}

const QString &MediaManager::currentTitle() const
{
    return m_currentTitle;
}

void MediaManager::setCurrentTitle(const QString &newCurrentTitle)
{
    if (m_currentTitle == newCurrentTitle)
        return;
    m_currentTitle = newCurrentTitle;
    emit currentTitleChanged();
}

const QString &MediaManager::currentArtist() const
{
    return m_currentArtist;
}

void MediaManager::setCurrentArtist(const QString &newCurrentArtist)
{
    if (m_currentArtist == newCurrentArtist)
        return;
    m_currentArtist = newCurrentArtist;
    emit currentArtistChanged();
}

int MediaManager::currentMediaDuration() const
{
    return m_currentMediaDuration;
}

void MediaManager::setCurrentMediaDuration(int newCurrentMediaDuration)
{
    if (m_currentMediaDuration == newCurrentMediaDuration)
        return;
    m_currentMediaDuration = newCurrentMediaDuration;
    emit currentMediaDurationChanged();
}

void MediaManager::addMediaToPlaylist(const QModelIndex &parent, int first, int last)
{
    for(auto i = first; i <= last; i++){
        QModelIndex index = m_mediaListModel->index(i, 0);
        QUrl fileUrl = m_mediaListModel->data(index, MediaListModel::MEDIA_FILE_URL).toUrl();

        m_mediaPlayer->playList()->addMedia(fileUrl);
    }
}

void MediaManager::updateCurrentMediaDetails(int currentMediaIndex)
{
    auto mediaModelIndex = m_mediaListModel->index(currentMediaIndex, 0);

    setCurrentTitle(m_mediaListModel->data(mediaModelIndex, MediaListModel::MEDIA_TITLE).toString());
    setCurrentArtist(m_mediaListModel->data(mediaModelIndex, MediaListModel::MEDIA_ARTIST).toString());
    setCurrentMediaDuration(m_mediaListModel->data(mediaModelIndex, MediaListModel::MEDIA_DURATION).toInt());
}

int MediaManager::currentPlayingMediaIndex() const
{
    return m_currentPlayingMediaIndex;
}

void MediaManager::setCurrentPlayingMediaIndex(int newCurrentPlayingMediaIndex)
{
    if (m_currentPlayingMediaIndex == newCurrentPlayingMediaIndex)
        return;
    m_currentPlayingMediaIndex = newCurrentPlayingMediaIndex;
    emit currentPlayingMediaIndexChanged(newCurrentPlayingMediaIndex);
}
