#ifndef GUI_CONFIG_H
#define GUI_CONFIG_H

#include <cstdlib>

#include <QApplication>
#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QStringList>
//QJSON
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
//FILE
#include <QFile>
#include <QFileInfo>

#include <QMessageBox>
#include "qt_os_filesystem.h"
#include "translate_environment_path.h"
#include "config_constexpr.h"
#include "v2ray_core_data.h"
#include "v2ray_json_config.h"


class gui_config_object
{
public:

    QJsonObject m_root_object;
    QVector<v2ray_core_server_data> server_data_vector;
    QString current_template_path;


    gui_config_object();
    void load_config();
    void save_config();

private:
    bool load_json_config(const QString &path);
    bool save_json_config(const QString &path);
    bool load_config_from_json_object();
    bool save_config_to_json_object();
    void first_create_config_file();

};

#endif // GUI_CONFIG_H
