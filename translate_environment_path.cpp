#include "translate_environment_path.h"

QString replace_environment(const QString &input_path, const QString &env_key)
{
    std::string std_env_value = os_system_environment::get_env(env_key.toStdString());
    QString env_value = QString::fromStdString(std_env_value);
    QString env_name("$");
    env_name.append(env_key);
    QString return_path = input_path;
    return return_path.replace(env_name, env_value);
}

QString translate_environment_path(const QString &input_path)
{
    QString return_path = input_path;
    #if defined(Q_OS_WIN32)
    return_path.replace("$HOME", ".");
    #elif defined(Q_OS_LINUX)
    return_path = replace_environment(return_path, "HOME");
    #endif
    //转换相对路径到绝对路径
    QFileInfo path_info(return_path);
    return_path = path_info.absoluteFilePath();
    return return_path;
}

