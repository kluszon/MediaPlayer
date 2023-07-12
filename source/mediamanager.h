#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <QFileInfo>
#include <QObject>

#include "model/medialistmodel.h"

class MediaManager : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(MediaListModel* mediaListModel READ mediaListModel NOTIFY mediaListModelChanged)

    static MediaManager *getInstance();

    Q_INVOKABLE bool addMedia(QString path);

    MediaListModel* mediaListModel() const;

signals:
    void mediaListModelChanged();

private:
    MediaManager(QObject *parent = nullptr);
    static MediaManager *m_instance;
    static MediaFile* createMediaFile(QFileInfo mediaFileInfo);
    MediaListModel *m_mediaListModel;
};

#endif // MEDIAMANAGER_H
