#ifndef QT_OS_FILESYSTEM_H
#define QT_OS_FILESYSTEM_H

#include <QString>
#include <QDir>
#include <QList>
#include <QFileInfoList>

namespace qt_os_filesystem
{
    void listdir(const QString &path, QList<QString> &out_list);
};

#endif // QT_OS_FILESYSTEM_H
