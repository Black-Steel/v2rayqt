#include "os_clipboard.h"

void SetClipboard(const QString &input_str)
{
    QClipboard *board = QApplication::clipboard();
    board->setText(input_str);
}

QString GetClipboard()
{
    QClipboard *board = QApplication::clipboard();
    QString qstr_out = board->text();
    //QMessageBox::information(NULL, "From clipboard", str);
    return qstr_out;
}
