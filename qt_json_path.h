#ifndef QJSONPATH_H
#define QJSONPATH_H

#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QStringList>


class QJsonPath
{
public:
    QJsonPath();
    static void setPathValue(QJsonObject &node, const QString &node_path, const QJsonValue &new_value);
    static QJsonValue getPathValue(const QJsonObject &node, const QString &path);

};

#endif // QJSONPATH_H
