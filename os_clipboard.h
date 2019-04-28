#ifndef OS_CLIPBOARD_H
#define OS_CLIPBOARD_H

#include <QApplication>
#include <QClipboard>
#include <QString>


void SetClipboard(const QString &input_str);
QString GetClipboard();

#endif // OS_CLIPBOARD_H
