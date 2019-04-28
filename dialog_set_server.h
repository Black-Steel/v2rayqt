#ifndef DIALOG_SET_SERVER_H
#define DIALOG_SET_SERVER_H

#include <QDialog>
#include <QString>
//#include "gui_config_object.h"
#include "v2ray_core_data.h"
namespace Ui
{
    class dialog_set_server;
}

class dialog_set_server : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_set_server(QWidget *parent = nullptr);
    ~dialog_set_server();

    void set_ui_limit();
    void set_server_data(const int index, const v2ray_core_server_data &input);
    void sync_data_to_ui();
    void sync_ui_to_data();

signals:
    void signal_send_server_data(const int index, const v2ray_core_server_data &data);

private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

private:
    int m_server_data_index;
    v2ray_core_server_data m_server_data;
    Ui::dialog_set_server *ui;
};

#endif // DIALOG_SET_SERVER_H
