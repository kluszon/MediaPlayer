#include "mediamanager.h"
#include <QDir>
#include <QDebug>

MediaManager *MediaManager::m_instance = nullptr;

MediaManager::MediaManager(QObject *parent) :
    m_mediaListModel(new MediaListModel()),
    QObject(parent)
{
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

MediaListModel *MediaManager::mediaListModel() const
{
    return m_mediaListModel;
}
