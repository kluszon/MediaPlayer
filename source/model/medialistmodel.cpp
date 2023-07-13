#include "medialistmodel.h"
#include <QDebug>

MediaListModel::MediaListModel()
{
    connect(this, &QAbstractListModel::rowsInserted, this, &MediaListModel::rowCountChanged);
    connect(this, &QAbstractListModel::rowsRemoved, this, &MediaListModel::rowCountChanged);
    connect(this, &QAbstractListModel::modelReset, this, &MediaListModel::rowCountChanged);
}

int MediaListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_mediaListModel.size();
}

QVariant MediaListModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= 0 && rowCount() > index.row())
    {
        switch(role)
        {
            case MEDIA_TITLE:
                return m_mediaListModel[index.row()]->title();
            case MEDIA_ARTIST:
                return m_mediaListModel[index.row()]->artist();
            case MEDIA_ALBUM:
                return m_mediaListModel[index.row()]->album();
            case MEDIA_DURATION:
                return m_mediaListModel[index.row()]->duration();
            case MEDIA_FILE_NAME:
                return m_mediaListModel[index.row()]->fileName();
            case MEDIA_FILE_URL:
                return m_mediaListModel[index.row()]->url();
            case MEDIA_OBJECT:
                return QVariant::fromValue(m_mediaListModel[index.row()]);
            case MEDIA_SELECTED:
                return m_mediaListModel[index.row()]->selected();
            case MEDIA_EXTENSION:
                return m_mediaListModel[index.row()]->fileExtension();
            case MEDIA_EXISTS:
                return m_mediaListModel[index.row()]->fileExists();
            case MEDIA_FILE_SIZE:
                return m_mediaListModel[index.row()]->fileSize();
            default:
                qDebug() << "Not supposed";
                return QVariant();
        }
    }else{
        qDebug() << "Warning: " << index.row();
        return QVariant();
    }
}

bool MediaListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.row() >= 0 && rowCount() > index.row())
    {
        switch(role)
        {
        case MEDIA_TITLE:{
            m_mediaListModel[index.row()]->setTitle(value.toString());
        }
        break;
        case MEDIA_ARTIST:{
            m_mediaListModel[index.row()]->setArtist(value.toString());
        }
        break;
        case MEDIA_ALBUM:{
            m_mediaListModel[index.row()]->setAlbum(value.toString());
        }
        break;
        case MEDIA_DURATION:{
            m_mediaListModel[index.row()]->setDuration(value.toUInt());
        }
        break;
        case MEDIA_SELECTED:{
            m_mediaListModel[index.row()]->setSelected(value.toBool());

//            if(value.toBool()){
//                emit rowSelected(index.row(), true);
//            }else{
//                emit rowSelected(index.row(), false);
//            }
        }
        break;
        case MEDIA_EXISTS:{
            m_mediaListModel[index.row()]->setFileExists(value.toBool());
        }
        break;
        default:{
            return false;
        }
        }
        emit dataChanged(index, index);

        return true;
    }else{
        return false;
    }
}

QHash<int, QByteArray> MediaListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[MEDIA_TITLE] = "mediaTitle";
    roles[MEDIA_ARTIST] = "mediaArtist";
    roles[MEDIA_ALBUM] = "mediaAlbum";
    roles[MEDIA_DURATION] = "mediaDuration";
    roles[MEDIA_FILE_NAME] = "mediaFileName";
    roles[MEDIA_FILE_URL] = "mediaFileUrl";
    roles[MEDIA_SELECTED] = "mediaSelected";
    roles[MEDIA_EXTENSION] = "mediaExtension";
    roles[MEDIA_EXISTS] = "mediaExists";
    roles[MEDIA_FILE_SIZE] = "mediaFileSize";
    return roles;
}

void MediaListModel::addMedia(QSharedPointer<MediaFile> media)
{
    beginInsertRows(QModelIndex(), m_mediaListModel.size(), m_mediaListModel.size());

    m_mediaListModel << media;

    endInsertRows();
}

void MediaListModel::removeMedia(const int mediaIndex)
{
    beginRemoveRows(QModelIndex(), mediaIndex, mediaIndex);

    m_mediaListModel.removeAt(mediaIndex);

    endRemoveRows();
}

QList<QSharedPointer<MediaFile> > MediaListModel::mediaListModel()
{
    return m_mediaListModel;

}
