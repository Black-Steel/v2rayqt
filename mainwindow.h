#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QObject>
#include <QObjectUserData>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItem>
#include <QMutex>
#include <QMutexLocker>
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
//#include <QRadioButton>
//#include <QButtonGroup>
#include <QPoint>
#include <QVector>

#include "gui_config_object.h"
#include "dialog_gui_config.h"
#include "dialog_set_server.h"
#include "qt_os_filesystem.h"
#include "v2ray_core_data.h"
#include "vmess_link.h"
#include "vmess_subscription.h"
#include "os_clipboard.h"
#include "translate_environment_path.h"
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //init app dirs
    void init_app_dirs();
    //初始化菜单
    void init_main_menu();
    void init_tray_icon();
    QString return_select_symbol(bool b_flag);
    //初始化table
    void init_table();
    void clear_table();
    //设置tableview的函数
    void table_add_item(const v2ray_core_server_data &server_data_object);
    void table_remove_item(const int row);
    void table_set_item(const int row, const v2ray_core_server_data &server_data_object);
    void table_set_item_checked(const int row);
    //设置server_object的函数
    void server_object_add(const v2ray_core_server_data &server_data_object);
    void server_object_remove(const int pos);
    void server_object_set(const int pos, const v2ray_core_server_data &server_data_object);
    void server_object_set_selected(const int pos);
    //通用设置函数
    void gen_sync_server_data();
    void gen_add_server(const v2ray_core_server_data &server_data_object);
    void gen_remove_server(const int pos);
    void gen_set_server(const int pos, const v2ray_core_server_data &server_data_object);
    void gen_set_server_selected(const int pos);

    //download url
    void get_subscription_url(const QString &string_url, const QString &string_subscription_id);
    void gen_add_vmess_subscription_group(const QStringList &vmess_list, const QString &subscription_id);

    //log
    void print_text_to_window(const QString &log);

    //save config
    void save_config_to_file();

    //start v2ary process
    int find_selected_server_index();
    void start_selected_v2ary_process();
    void close_v2ary_process();
    void start_v2ary_process();

    //重写事件
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);

public slots:
    void table_custom_right_menu_slot(QPoint pos);
    void custom_menu_select_server_slot();
    void custom_menu_add_slot();
    void custom_menu_add_files_slot();
    void custom_menu_modeify_slot();
    void custom_menu_delete_slot();

    void custom_menu_import_link_slot();
    void custom_menu_export_link_slot();
    void custom_menu_update_subscription_slot();
    void custom_menu_clear_subscription_slot();

    void add_server_slot(const int index, const v2ray_core_server_data &data);
    void change_server_slot(const int index, const v2ray_core_server_data &data);

    void subscription_download_finish_slot(QNetworkReply *p_reply);

    //setting
    void custom_menu_set_config_template_window_slot();
    void set_config_template_path_slot(const QString &path);

    //process
    void output_process_log_slot();
    void custom_menu_restart_process_slot();
    void custom_menu_terminate_process_slot();
    //tray
    void tray_icon_activated_slot(QSystemTrayIcon::ActivationReason reason);
    void tray_exit_slot();

signals:

private:
    enum SERVER_TABLE_COLUMN_ID
    {
        CHECKED = 0,
        REMARKS,
        ADDRESS,
        PORT,
        ENUM_SIZE
    };

    //QVector<v2ray_server_data> m_config.server_data;
    QMutex m_window_mutex;
    QProcess m_process;
    gui_config_object m_config;
    QSystemTrayIcon *m_tray_icon;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
