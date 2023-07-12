#ifndef MEDIALISTMODEL_H
#define MEDIALISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QSharedPointer>

#include "mediafile.h"

class MediaListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /*!
     * \enum Roles
     * \brief Roles name enum
    */

    enum Roles {
        MEDIA_TITLE = Qt::UserRole + 1,     ///< title
        MEDIA_ARTIST,                       ///< artist
        MEDIA_ALBUM,                        ///< album
        MEDIA_DURATION,                     ///< duration
        MEDIA_FILE_NAME,                    ///< file name
        MEDIA_FILE_PATH,                    ///< file path
        MEDIA_OBJECT,                       ///< media object
        MEDIA_SELECTED,
        MEDIA_EXTENSION,
        MEDIA_EXISTS,
        MEDIA_FILE_SIZE
    };
    Q_ENUM(Roles)

    MediaListModel();

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QHash<int, QByteArray> roleNames() const;

    // Add data:
    void addMedia(QSharedPointer<MediaFile> media);

private:
    QList<QSharedPointer<MediaFile>> m_mediaListModel;
};

Q_DECLARE_METATYPE(MediaListModel*)

#endif // MEDIALISTMODEL_H
