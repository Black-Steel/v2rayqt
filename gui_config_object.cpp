#include "gui_config_object.h"

gui_config_object::gui_config_object()
{

}

void gui_config_object::load_config()
{
    QString default_config_name = translate_environment_path(DEFAULT_GUI_CONFIG_FILENAME);
    QFileInfo gui_config_file(default_config_name);

    if(gui_config_file.exists() == false)
    {
        first_create_config_file();
        return;
    }

    load_json_config(default_config_name);
    load_config_from_json_object();

}

void gui_config_object::save_config()
{
    QString default_config_name = translate_environment_path(DEFAULT_GUI_CONFIG_FILENAME);
    save_config_to_json_object();
    save_json_config(default_config_name);
}

bool gui_config_object::load_json_config(const QString &path)
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

bool gui_config_object::save_json_config(const QString &path)
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

bool gui_config_object::load_config_from_json_object()
{
    if(m_root_object.isEmpty() == true)
    {
        return false;
    }
    current_template_path = m_root_object["current_template_path"].toString();
    QJsonArray array_object = m_root_object["server_data"].toArray();
    for (auto item : array_object)
    {
        if(item.isObject() == false)
        {
            continue;
        }
        QJsonObject server_json_object = item.toObject();
        v2ray_core_server_data server_object;
        server_object.load_from_json_object(server_json_object);
        if(server_object.is_file() == true)
        {
            //检查文件是否有效
            QFileInfo qfile(server_object.filepath);
            if(qfile.exists() == false)
            {
                continue;
            }

        }
        server_data_vector.push_back(server_object);
    }
    return true;
}

bool gui_config_object::save_config_to_json_object()
{
    m_root_object["current_template_path"] = current_template_path;

    QJsonArray array_object;
    for (auto &it : server_data_vector)
    {
        QJsonObject server_object = it.save_to_json_object();
        array_object.push_back(server_object);
    }
    m_root_object["server_data"] = array_object;
    return true;
}

void gui_config_object::first_create_config_file()
{
    QString abs_path = translate_environment_path(DEFAULT_CONFIG_TEMPLATE_DIR);
    QList<QString> template_path_list;

    qt_os_filesystem::listdir(abs_path, template_path_list);
    if(template_path_list.isEmpty() == true)
    {
        QMessageBox::warning(nullptr,
                             QObject::tr("warning"),
                             QObject::tr("Can't found template file."),
                             QMessageBox::Ok);
        //QApplication::exit(0);
        std::exit(0);
        //return;
    }
    current_template_path = template_path_list.first();
}

