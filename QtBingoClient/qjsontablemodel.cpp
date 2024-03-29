#include "qjsontablemodel.h"
#include <QJsonObject>

QJsonTableModel::QJsonTableModel( const QJsonTableModel::Header& header, QObject * parent )
    : QAbstractTableModel( parent )
    , m_header( header )
{

}

bool QJsonTableModel::setJson(const QJsonDocument &json)
{
    return setJson( json.array() );
}

bool QJsonTableModel::setJson( const QJsonArray& array )
{
    beginResetModel();
    m_json = array;
    endResetModel();
    return true;
}

QVariant QJsonTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    switch( orientation )
    {
    case Qt::Horizontal:
        return m_header[section]["title"];
    case Qt::Vertical:
        //return section + 1;
        return QVariant();
    default:
        return QVariant();
    }

}

int QJsonTableModel::rowCount(const QModelIndex &parent ) const
{
    return m_json.size();
}

int QJsonTableModel::columnCount(const QModelIndex &parent ) const
{
    return m_header.size();
}


QJsonObject QJsonTableModel::getJsonObject( const QModelIndex &index ) const
{
    const QJsonValue& value = m_json[index.row() ];
    return value.toObject();
}

QVariant QJsonTableModel::data( const QModelIndex &index, int role ) const
{
    switch( role )
    {
    case Qt::DisplayRole:
    {
        QJsonObject obj = getJsonObject( index );
        const QString& key = m_header[index.column()]["index"];
        if( obj.contains( key ))
        {
            QJsonValue v = obj[ key ];

            if( v.isString() )
            {
                return v.toString();
            }
            else if( v.isDouble() )
            {
                return QString::number( v.toDouble() );
            }
            else if (v.isArray())
            {
                QJsonArray a = v.toArray();
                QString num;
                for (int i = 0; i < a.count(); i++)
                {
                    num.append(QString::number(a.at(i).toInt()));
                    num.append(" ");
                }
                return num;
            }
            else
            {
                return QVariant();
            }
        }
        else
        {
            return QVariant();
        }
    }
    case Qt::ToolTipRole:
        return QVariant();
    default:
        return QVariant();
    }
}




bool QJsonTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int col = index.column();

    QList<QVariant> list;
    for (int i = 0; i < this->columnCount(); i++)
    {
        if (i == col)
            list.append(value);
        else
            list.append(this->index(row,i).data());
    }

    emit rowEdit(list);
    return true;
}

Qt::ItemFlags QJsonTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index);// | Qt::ItemIsEditable;
}
