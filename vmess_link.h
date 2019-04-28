#ifndef VMESS_LINK_H
#define VMESS_LINK_H


#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QVariant>
#include <QString>
#include <QByteArray>
#include <v2ray_core_data.h>

class vmess_link
{
public:
    vmess_link();
    static bool load_form_link(const QString &string_link, v2ray_core_server_data &server_object);
    static bool save_to_link(const v2ray_core_server_data &server_object, QString &string_link);
protected:

private:
    static bool server_object_to_link_json_bytes(const v2ray_core_server_data &server_object, QByteArray &json_bytes);
    static bool link_json_bytes_to_server_object(const QByteArray &json_bytes, v2ray_core_server_data &server_object);
};

#endif // VMESS_LINK_H
