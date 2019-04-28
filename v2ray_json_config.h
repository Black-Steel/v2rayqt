#ifndef V2RAY_JSON_CONFIG_CLASS_H
#define V2RAY_JSON_CONFIG_CLASS_H

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QString>
#include <QList>
#include <QFile>

#include "qt_json_path.h"
#include "v2ray_core_data.h"

class v2ray_json_config
{
public:

    QJsonObject m_root_object;
    v2ray_json_config();
    bool load_template_file(const QString &path);
    bool write_to_file(const QString &path);
    bool copy_file(const QString &old_path, const QString &new_path);

    void create_config_file_from_server_data(const QString &save_path,
            const v2ray_core_server_data &server_data,
            const QString &template_path);

    void set_client_outbounds(const v2ray_core_server_data &server_data);
protected:
    QJsonObject set_client_outbound_direct();
    QJsonObject set_client_outbound_blocked();
    QJsonObject set_client_outbound_vmess_final_node_tcp_settings(const v2ray_core_server_data &server_data);
    QJsonObject set_client_outbound_vmess_final_node_kcp_settings(const v2ray_core_server_data &server_data);
    QJsonObject set_client_outbound_vmess_final_node_ws_settings(const v2ray_core_server_data &server_data);
    QJsonObject set_client_outbound_vmess_final_node_http_settings(const v2ray_core_server_data &server_data);
    QJsonObject set_client_outbound_vmess_final_node_domainsocket_settings(const v2ray_core_server_data &server_data);
    QJsonObject set_client_outbound_vmess_final_node_tls_settings(const v2ray_core_server_data &server_data);
    QJsonObject set_client_outbound_vmess_final_node(const v2ray_core_server_data &server_data);

};

#endif // V2RAY_JSON_CONFIG_CLASS_H
