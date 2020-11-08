#ifndef QJSONTABLEMODEL_H
#define QJSONTABLEMODEL_H

#include <QDebug>
#include <QObject>
#include <QVector>
#include <QMap>
#include <QAbstractTableModel>
#include <QJsonDocument>
#include <QJsonArray>

class QJsonTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    typedef QMap<QString,QString> Heading;
    typedef QVector<Heading> Header;
    QJsonTableModel( const Header& header, QObject * parent = 0);

    bool setJson( const QJsonDocument& json );
    bool setJson( const QJsonArray& array );

    virtual QJsonObject getJsonObject( const QModelIndex &index ) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const ;


signals:
    void rowEdit(QList<QVariant>);

private:
    Header m_header;
    QJsonArray m_json;
};

#endif // QJSONTABLEMODEL_H
