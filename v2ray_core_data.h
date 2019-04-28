#ifndef V2RAY_CONFIG_CORE_SERVER_DATA_OBJECT_H
#define V2RAY_CONFIG_CORE_SERVER_DATA_OBJECT_H

//QJSON
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
//FILE
#include <QFile>
#include <QFileInfo>
//CONTIANER
#include <QString>
#include <QStringList>


class v2ray_core_server_data
{
public:
    QString filepath;
    QString remarks;
    QString address;
    int port;
    QString user_id;
    int alter_id;
    QString user_security;
    QString network;
    QString stream_type;
    QString stream_security;
    QString stream_host;
    QString stream_path;
    QString subscription_id;
    bool selected;

    v2ray_core_server_data();
    v2ray_core_server_data(const v2ray_core_server_data &src);
    ~v2ray_core_server_data();

    v2ray_core_server_data  &operator=(const v2ray_core_server_data &src);
    void load_from_json_object(const QJsonObject &json_object);
    QJsonObject save_to_json_object() const;
    void set_custom_file(const QString &path);

    QStringList get_host_list() const;
    QStringList get_path_list() const;

    bool is_empty() const;
    bool is_file() const;
    bool is_have_header() const;
private:
    void self_deep_copy(const v2ray_core_server_data &src);
};

#endif // V2RAY_CONFIG_CORE_SERVER_DATA_OBJECT_H
