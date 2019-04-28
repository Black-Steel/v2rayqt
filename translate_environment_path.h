#ifndef TRANSLATE_ENVIRONMENT_PATH_H
#define TRANSLATE_ENVIRONMENT_PATH_H

#include <string>
#include <QString>
#include <QtGlobal>
#include <QFileInfo>
//#include <QProcess>

#include "os_system_environment.h"
QString replace_environment(const QString &input_path, const QString &env_key);
QString translate_environment_path(const QString &input_path);

#endif // TRANSLATE_ENVIRONMENT_PATH_H
