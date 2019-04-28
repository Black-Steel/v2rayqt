#include "qt_os_filesystem.h"

void qt_os_filesystem::listdir(const QString &path, QList<QString> &out_list)
{
    QDir qdir(path);
    QFileInfoList qfile_list = qdir.entryInfoList();
    for (auto &fi : qfile_list)
    {
        if(fi.isFile())
        {
            out_list.push_back(fi.filePath());
        }
        else
        {
            if(fi.fileName() == "." || fi.fileName() == "..")
            {
                continue;
            }
            listdir(fi.absoluteFilePath(), out_list);
        }
    }
}
