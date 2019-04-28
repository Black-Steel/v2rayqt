#include "v2ray_core_data.h"

v2ray_core_server_data::v2ray_core_server_data()
{
    port = 0;
    alter_id = 0;
    selected = false;
}

v2ray_core_server_data::v2ray_core_server_data(const v2ray_core_server_data &src)
{
    self_deep_copy(src);
}

v2ray_core_server_data::~v2ray_core_server_data()
{

}

v2ray_core_server_data  &v2ray_core_server_data::operator=(const v2ray_core_server_data &src)
{
    self_deep_copy(src);
    return *this;
}

void v2ray_core_server_data::load_from_json_object(const QJsonObject &json_object)
{
    filepath = json_object["filepath"].toString();
    remarks = json_object["remarks"].toString();
    address = json_object["address"].toString();
    port = json_object["port"].toInt();
    user_id = json_object["user_id"].toString();
    alter_id = json_object["alter_id"].toInt();
    user_security = json_object["user_security"].toString();
    network = json_object["network"].toString();
    stream_type = json_object["stream_type"].toString();
    stream_security = json_object["stream_security"].toString();
    stream_host = json_object["stream_host"].toString();
    stream_path = json_object["stream_path"].toString();
    subscription_id = json_object["subscription_id"].toString();
    selected = json_object["is_default"].toBool();
}

QJsonObject v2ray_core_server_data::save_to_json_object() const
{
    QJsonObject json_object;
    json_object["filepath"] = filepath ;
    json_object["remarks"] = remarks;
    json_object["address"] = address;
    json_object["port"] = port;
    json_object["user_id"] = user_id;
    json_object["alter_id"] = alter_id;
    json_object["user_security"] = user_security;
    json_object["network"] = network;
    json_object["stream_type"] = stream_type;
    json_object["stream_security"] = stream_security;
    json_object["stream_host"] = stream_host;
    json_object["stream_path"] = stream_path;
    json_object["subscription_id"] = subscription_id;
    json_object["is_default"] = selected;
    return json_object;
}

void v2ray_core_server_data::set_custom_file(const QString &path)
{
    QFileInfo finfo(path);
    filepath = path;
    remarks = finfo.fileName();
}

QStringList v2ray_core_server_data::get_host_list() const
{
    QStringList host_list = stream_host.split(",", QString::SplitBehavior::SkipEmptyParts);
    return host_list;
}

QStringList v2ray_core_server_data::get_path_list() const
{
    QStringList path_list = stream_host.split(",", QString::SplitBehavior::SkipEmptyParts);
    return path_list;
}

bool v2ray_core_server_data::is_empty() const
{
    if(filepath.isEmpty() && remarks.isEmpty())
    {
        return true;
    }
    return false;
}

bool v2ray_core_server_data::is_file() const
{
    if(filepath.isEmpty() == true)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool v2ray_core_server_data::is_have_header() const
{
    if(stream_type.isEmpty() || stream_type == "none")
    {
        return false;
    }
    return true;
}

void v2ray_core_server_data::self_deep_copy(const v2ray_core_server_data &src)
{
    filepath = src.filepath;
    remarks = src.remarks;
    address = src.address;
    port = src.port;
    user_id = src.user_id;
    alter_id = src.alter_id;
    user_security = src.user_security;
    network = src.network;
    stream_type = src.stream_type;
    stream_security = src.stream_security;
    stream_host = src.stream_host;
    stream_path = src.stream_path;
    subscription_id = src.subscription_id;
    selected = src.selected;
}
