#include "v2ray_json_config.h"

v2ray_json_config::v2ray_json_config()
{

}

bool v2ray_json_config::load_template_file(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QObject::tr("Can't open the file!") << endl;
        return false;
    }
    QByteArray qbytedata = file.readAll();
    QJsonDocument json_doc;
    json_doc = QJsonDocument::fromJson(qbytedata);
    if(json_doc.isNull() == true)
    {
        qDebug() << QObject::tr("Can't parse json!") << endl;
        return false;
    }
    if(json_doc.isObject() != true)
    {
        qDebug() << QObject::tr("json error.") << endl;
        return false;
    }
    m_root_object = json_doc.object();
    return true;
}

bool v2ray_json_config::write_to_file(const QString &path)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << QObject::tr("Can't open the file!") << endl;
        return false;
    }
    QJsonDocument json_doc;
    json_doc.setObject(m_root_object);

    QByteArray qbytedata = json_doc.toJson(QJsonDocument::Indented);
    file.write(qbytedata);
    return true;
}

bool v2ray_json_config::copy_file(const QString &old_path, const QString &new_path)
{
    QFile old_file(old_path);
    if(!old_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << QObject::tr("Can't open the file!") << endl;
        return false;
    }
    QFile new_file(new_path);
    if(!new_file.open(QIODevice::WriteOnly))
    {
        qDebug() << QObject::tr("Can't open the file!") << endl;
        return false;
    }
    while(true)
    {
        QByteArray qbytedata = old_file.read(4096);
        if(qbytedata.isEmpty() == true)
        {
            break;
        }
        new_file.write(qbytedata);
    }
    return true;
}

void v2ray_json_config::create_config_file_from_server_data(const QString &save_path,
        const v2ray_core_server_data &server_data,
        const QString &template_path)
{
    if(server_data.is_file() == true)
    {
        copy_file(server_data.filepath, save_path);
    }
    else
    {
        load_template_file(template_path);
        set_client_outbounds(server_data);
        write_to_file(save_path);
    }
}

void v2ray_json_config::set_client_outbounds(const v2ray_core_server_data &server_data)
{

    QJsonArray outbounds_array;
    outbounds_array.append(set_client_outbound_direct());
    outbounds_array.append(set_client_outbound_blocked());
    outbounds_array.append(set_client_outbound_vmess_final_node(server_data));
    m_root_object["outbounds"] = outbounds_array;
}

QJsonObject v2ray_json_config::set_client_outbound_direct()
{
    QJsonObject outbound_direct;
    outbound_direct.insert("tag", "direct");
    outbound_direct.insert("protocol", "freedom");
    QJsonObject tcpsettings_obj;
    outbound_direct.insert("tcpSettings", tcpsettings_obj);
    return outbound_direct;
}

QJsonObject v2ray_json_config::set_client_outbound_blocked()
{
    QJsonObject outbound_blocked;
    outbound_blocked.insert("tag", "blocked");
    outbound_blocked.insert("protocol", "blackhole");
    QJsonObject tcpsettings_obj;
    outbound_blocked.insert("tcpSettings", tcpsettings_obj);
    return outbound_blocked;
}

QJsonObject v2ray_json_config::set_client_outbound_vmess_final_node_tcp_settings(const v2ray_core_server_data &server_data)
{
    QJsonObject tcpsettings_obj;
    QJsonObject header_obj;

    if(server_data.is_have_header() == true)
    {
        QJsonObject request_obj;
        header_obj["type"] = server_data.stream_type;
        QJsonObject host_object;
        QJsonArray host_array;
        QStringList host_list = server_data.get_host_list();
        for (auto &it : host_list)
        {
            host_array.append(it);
        }
        host_object["Host"] = host_array;
        request_obj["headers"] = host_object;
        QStringList path_list = server_data.get_path_list();
        QJsonArray path_array;
        for (auto &it : path_list)
        {
            host_array.append(it);
        }
        request_obj["Path"] = path_array;
        header_obj["request"] = request_obj;
    }
    else
    {
        header_obj["type"] = "none";
    }
    tcpsettings_obj["header"] = header_obj;
    return tcpsettings_obj;
}

QJsonObject v2ray_json_config::set_client_outbound_vmess_final_node_kcp_settings(const v2ray_core_server_data &server_data)
{
    QJsonObject kcpsettings_obj;
    QJsonObject header_obj;
    if(server_data.is_have_header() == true)
    {
        header_obj["type"] = server_data.stream_type;

    }
    else
    {
        header_obj["type"] = "none";
    }
    kcpsettings_obj["header"] = header_obj;
    return kcpsettings_obj;
}

QJsonObject v2ray_json_config::set_client_outbound_vmess_final_node_ws_settings(const v2ray_core_server_data &server_data)
{
    QJsonObject ws_settings_obj;

    if(server_data.is_have_header() == true)
    {
        ws_settings_obj["path"] = server_data.stream_path;
        QJsonObject headers_obj;
        headers_obj["Host"] = server_data.stream_host;
        ws_settings_obj["headers"] = headers_obj;
    }
    return ws_settings_obj;
}

QJsonObject v2ray_json_config::set_client_outbound_vmess_final_node_http_settings(const v2ray_core_server_data &server_data)
{
    QJsonObject http_settings_obj;

    if(server_data.is_have_header() == true)
    {
        QJsonArray host_array;
        QStringList host_list = server_data.get_host_list();
        for (auto &it : host_list)
        {
            host_array.append(it);
        }
        http_settings_obj["host"] = host_array;
        http_settings_obj["path"] = server_data.stream_path;
    }
    return http_settings_obj;
}

QJsonObject v2ray_json_config::set_client_outbound_vmess_final_node_domainsocket_settings(const v2ray_core_server_data &server_data)
{
    QJsonObject ds_settings_obj;

    if(server_data.is_have_header() == true)
    {
        ds_settings_obj["path"] = server_data.stream_path;
    }
    return ds_settings_obj;
}

QJsonObject v2ray_json_config::set_client_outbound_vmess_final_node_tls_settings(const v2ray_core_server_data &server_data)
{
    QJsonObject tls_settings_obj;
    tls_settings_obj.insert("serverName", server_data.stream_host);
    tls_settings_obj.insert("allowInsecure", true);
    return tls_settings_obj;
}

QJsonObject v2ray_json_config::set_client_outbound_vmess_final_node(const v2ray_core_server_data &server_data)
{
    QJsonObject outbound_final_node;
    outbound_final_node.insert("tag", "final_node");
    outbound_final_node.insert("protocol", "vmess");
    //settings object
    QJsonObject settings_obj;
    QJsonArray vnext_array;
    QJsonObject vnext_item_obj;
    vnext_item_obj.insert("address", server_data.address);
    vnext_item_obj.insert("port", server_data.port);
    QJsonArray users_array;
    QJsonObject user_obj;
    user_obj.insert("id", server_data.user_id);
    user_obj.insert("security", server_data.user_security);
    user_obj.insert("alterId", server_data.alter_id);
    users_array.append(user_obj);
    vnext_item_obj.insert("users", users_array);
    vnext_array.append(vnext_item_obj);
    settings_obj.insert("vnext", vnext_array);
    outbound_final_node.insert("settings", settings_obj);

    //stream_settings_object
    QJsonObject stream_settings_object;
    stream_settings_object.insert("network", server_data.network);
    stream_settings_object.insert("security", server_data.stream_security);

    if(server_data.network == "tcp")
    {
        QJsonObject tcpsettings_obj = set_client_outbound_vmess_final_node_tcp_settings(server_data);
        stream_settings_object.insert("tcpSettings", tcpsettings_obj);
    }
    else if(server_data.network == "kcp")
    {
        QJsonObject kcpsettings_obj = set_client_outbound_vmess_final_node_kcp_settings(server_data);
        stream_settings_object.insert("kcpSettings", kcpsettings_obj);
    }
    else if(server_data.network == "ws")
    {
        QJsonObject ws_settings_obj = set_client_outbound_vmess_final_node_ws_settings(server_data);
        stream_settings_object.insert("wsSettings", ws_settings_obj);
    }
    else if(server_data.network == "http")
    {
        QJsonObject http_settings_obj = set_client_outbound_vmess_final_node_http_settings(server_data);
        stream_settings_object.insert("httpSettings", http_settings_obj);
    }
    else if(server_data.network == "domainsocket")
    {
        QJsonObject http_settings_obj = set_client_outbound_vmess_final_node_domainsocket_settings(server_data);
        stream_settings_object.insert("httpSettings", http_settings_obj);
    }
    else
    {
        //unknow;
    }

    if(server_data.stream_security == "tls")
    {
        QJsonObject tls_settings_obj = set_client_outbound_vmess_final_node_tls_settings(server_data);
        stream_settings_object.insert("tlsSettings", tls_settings_obj);
    }
    outbound_final_node.insert("streamSettings", stream_settings_object);
    return outbound_final_node;
}
