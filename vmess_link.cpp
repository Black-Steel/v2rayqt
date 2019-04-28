#include "vmess_link.h"

vmess_link::vmess_link()
{

}

bool vmess_link::load_form_link(const QString &string_link, v2ray_core_server_data &server_object)
{
    QStringList link_list = string_link.split("://");
    if(link_list.size() < 2)
    {
        return false;
    }
    QString &protocl_name = link_list[0];
    if(protocl_name != "vmess")
    {
        return false;
    }
    QString &link_base64 = link_list[1];

    QByteArray link_json_bytes = QByteArray::fromBase64(link_base64.toUtf8());
    return link_json_bytes_to_server_object(link_json_bytes, server_object);
}

bool vmess_link::save_to_link(const v2ray_core_server_data &server_object, QString &string_link)
{
    QByteArray qbyte_json;
    server_object_to_link_json_bytes(server_object, qbyte_json);
    string_link = "vmess://" + qbyte_json.toBase64();
    return true;
}

bool vmess_link::server_object_to_link_json_bytes(const v2ray_core_server_data &server_object, QByteArray &json_bytes)
{
    QJsonDocument json_doc;
    QJsonObject json_root;
    json_root["ps"] = server_object.remarks;
    json_root["add"] = server_object.address;
    json_root["port"] = QString::number(server_object.port);
    json_root["id"] = server_object.user_id;
    json_root["aid"] = QString::number(server_object.alter_id);
    json_root["security"] = server_object.user_security;
    json_root["net"] = server_object.network;
    json_root["type"] = server_object.stream_type;
    json_root["tls"] = server_object.stream_security;
    json_root["host"] = server_object.stream_host;
    json_root["path"] = server_object.stream_path;

    json_doc.setObject(json_root);
    json_bytes = json_doc.toJson(QJsonDocument::Compact);
    return true;
}

bool vmess_link::link_json_bytes_to_server_object(const QByteArray &json_bytes, v2ray_core_server_data &server_object)
{
    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);
    if(json_doc.isNull() == true)
    {
        return false;
    }
    if(json_doc.isObject() != true)
    {
        return false;
    }
    QJsonObject json_root = json_doc.object();
    server_object.remarks = json_root.value("ps").toString();
    server_object.address = json_root.value("add").toString();
    server_object.port = json_root.value("port").toString().toInt();
    server_object.user_id = json_root.value("id").toString();
    server_object.alter_id = json_root.value("aid").toString().toInt();
    server_object.user_security = json_root.value("security").toString();
    if(server_object.user_security.isEmpty())
    {
        server_object.user_security = "auto";
    }
    server_object.network = json_root.value("net").toString();
    server_object.stream_type = json_root.value("type").toString();
    server_object.stream_security = json_root.value("tls").toString();
    server_object.stream_host = json_root.value("host").toString();
    server_object.stream_path = json_root.value("path").toString();
    return true;
}
