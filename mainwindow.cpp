#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_app_dirs();
    init_main_menu();
    init_tray_icon();
    init_table();
    m_config.load_config();
    gen_sync_server_data();
    start_selected_v2ary_process();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_app_dirs()
{
    QDir qd;
    qd.mkpath(translate_environment_path(DEFAULT_CONFIG_TEMPLATE_DIR));
    qd.mkpath(translate_environment_path(DEFAULT_CONFIG_SUBSCRIPTION_DIR));
    qd.mkpath(translate_environment_path(DEFAULT_V2RAY_DIR));
    //QDir::mkpath(DEFAULT_CONFIG_TEMPLATE_DIR);
}

void MainWindow::init_main_menu()
{
    connect(ui->action_add_server, SIGNAL(triggered()), this, SLOT(custom_menu_add_slot()));
    connect(ui->action_add_files, SIGNAL(triggered()), this, SLOT(custom_menu_add_files_slot()));

    connect(ui->action_modify_server, SIGNAL(triggered()), this, SLOT(custom_menu_modeify_slot()));
    connect(ui->action_remove_server, SIGNAL(triggered()), this, SLOT(custom_menu_delete_slot()));
    connect(ui->action_import_vmess_link, SIGNAL(triggered()), this, SLOT(custom_menu_import_link_slot()));
    connect(ui->action_export_vmess_link, SIGNAL(triggered()), this, SLOT(custom_menu_export_link_slot()));

    connect(ui->action_update_subscription, SIGNAL(triggered()), this, SLOT(custom_menu_update_subscription_slot()));
    connect(ui->action_clear_subscription, SIGNAL(triggered()), this, SLOT(custom_menu_clear_subscription_slot()));

    //setting
    connect(ui->action_select_template, SIGNAL(triggered()), this, SLOT(custom_menu_set_config_template_window_slot()));

    //process
    connect(ui->action_restart_process, SIGNAL(triggered()), this, SLOT(custom_menu_restart_process_slot()));
    connect(ui->action_terminate_process, SIGNAL(triggered()), this, SLOT(custom_menu_terminate_process_slot()));


}

void MainWindow::init_tray_icon()
{
    //创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    QMenu *tray_icon_menu = new QMenu(this);
    QAction *quit_action = new QAction(QObject::tr("Exit"), this);
    tray_icon_menu->addAction(quit_action);


    //托盘初始化
    QIcon icon = QIcon(":/MAIN_LOGO");
    m_tray_icon = new QSystemTrayIcon(this);
    m_tray_icon->setIcon(icon);
    m_tray_icon->setToolTip("V2RAYQT");
    m_tray_icon->setContextMenu(tray_icon_menu);
    m_tray_icon->show();
    //连接托盘槽
    connect(m_tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(tray_icon_activated_slot(QSystemTrayIcon::ActivationReason)));

    //连接菜单的槽
    connect(quit_action, SIGNAL(triggered()), this, SLOT(tray_exit_slot()));


}

QString MainWindow::return_select_symbol(bool b_flag)
{
    if(b_flag == true)
    {
        return "*";
    }
    else
    {
        return "";
    }
}

void MainWindow::init_table()
{
    //隐藏列表头
    ui->server_table_view->verticalHeader()->setVisible(false);
    ui->server_table_view->horizontalHeader()->setVisible(true);
    //整行选中的方式
    ui->server_table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    //禁止修改表格内容
    ui->server_table_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置为可以选中多个目标;
    ui->server_table_view->setSelectionMode(QAbstractItemView::ExtendedSelection);


    /*设置列字段名

    model->setHeaderData(0,Qt::Horizontal, "1");
    model->setHeaderData(1,Qt::Horizontal, "2");
    model->setHeaderData(2,Qt::Horizontal, "3");
    ?   */
    /*设置行字段名*/


    QStandardItemModel *model = new QStandardItemModel(this);
    //设置列数量
    //qDebug() << sizeof(SERVER_TABLE_COLUMN_ID) <<endl;
    int n_header_count = SERVER_TABLE_COLUMN_ID::ENUM_SIZE;
    model->setColumnCount(n_header_count);
    //设置行数量
    model->setRowCount(0);

    model->setHeaderData(SERVER_TABLE_COLUMN_ID::CHECKED, Qt::Horizontal, "CHECKED");
    model->setHeaderData(SERVER_TABLE_COLUMN_ID::REMARKS, Qt::Horizontal, "REMARKS");
    model->setHeaderData(SERVER_TABLE_COLUMN_ID::ADDRESS, Qt::Horizontal, "ADDRESS");
    model->setHeaderData(SERVER_TABLE_COLUMN_ID::PORT, Qt::Horizontal, "PORT");
    ui->server_table_view->setModel(model);
    //自适应列宽

    ui->server_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->server_table_view->horizontalHeader()->setSectionResizeMode(SERVER_TABLE_COLUMN_ID::CHECKED, QHeaderView::ResizeToContents);
    ui->server_table_view->horizontalHeader()->setSectionResizeMode(SERVER_TABLE_COLUMN_ID::PORT, QHeaderView::Fixed);
    ui->server_table_view->setColumnWidth(SERVER_TABLE_COLUMN_ID::PORT, 100);
    /*
    //允许用户手动调整部分列
    ui->server_table_view->horizontalHeader()->setSectionResizeMode(SERVER_TABLE_COLUMN_ID::REMARKS,QHeaderView::Interactive);
    ui->server_table_view->horizontalHeader()->setSectionResizeMode(SERVER_TABLE_COLUMN_ID::ADDRESS,QHeaderView::Interactive);
    ui->server_table_view->setColumnWidth(SERVER_TABLE_COLUMN_ID::REMARKS,300);
    ui->server_table_view->setColumnWidth(SERVER_TABLE_COLUMN_ID::ADDRESS,300);
    */
    //ui->server_table_view->horizontalHeader()->setSectionResizeMode(SERVER_TABLE_COLUMN_ID::REMARKS,QHeaderView::Interactive);
    //ui->server_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //自适应行高
    //ui->server_table_view->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // custom menu
    ui->server_table_view->setContextMenuPolicy(Qt::CustomContextMenu);
    // right click connection
    connect(ui->server_table_view, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(table_custom_right_menu_slot(QPoint)));

    ui->server_table_view->show();

    //add
    //get_subscription_url("http://127.0.0.1/dspi.txt","dspi");

    //table_set_item(1,td);
}

void MainWindow::clear_table()
{
    QStandardItemModel *p_model = dynamic_cast<QStandardItemModel *>(ui->server_table_view->model());
    int n_row = p_model->rowCount();
    p_model->removeRows(0, n_row);
}

void MainWindow::table_add_item(const v2ray_core_server_data &server_data_object)
{
    QStandardItemModel *p_model = dynamic_cast<QStandardItemModel *>(ui->server_table_view->model());

    //add new row
    QList<QStandardItem *> list;
    //SERVER_TABLE_COLUMN_ID::CHECKED
    list << new QStandardItem(return_select_symbol(server_data_object.selected));
    //SERVER_TABLE_COLUMN_ID::REMARKS
    list << new QStandardItem(server_data_object.remarks);
    //SERVER_TABLE_COLUMN_ID::ADDRESS
    list << new QStandardItem(server_data_object.address);
    //SERVER_TABLE_COLUMN_ID::PORT
    list << new QStandardItem(QString::number(server_data_object.port));
    //在第next_row行插入一条记录
    //int now_row = p_model->rowCount();
    //int next_row = now_row + 1;
    //p_model->insertRow(next_row, list);
    p_model->appendRow(list);
}

void MainWindow::table_remove_item(const int row)
{
    QStandardItemModel *p_model = dynamic_cast<QStandardItemModel *>(ui->server_table_view->model());
    if(row < 0)
    {
        return;
    }
    if(row > p_model->rowCount())
    {
        return;
    }
    p_model->removeRow(row);
}

void MainWindow::table_set_item(const int row, const v2ray_core_server_data &server_data_object)
{
    QStandardItemModel *p_model = dynamic_cast<QStandardItemModel *>(ui->server_table_view->model());
    /*
    p_model->setItem(row, SERVER_TABLE_COLUMN_ID::CHECKED,new QStandardItem(return_select_symbol(server_data_object.selected)));
    p_model->setItem(row, SERVER_TABLE_COLUMN_ID::REMARKS,new QStandardItem(server_data_object.remarks));
    p_model->setItem(row, SERVER_TABLE_COLUMN_ID::ADDRESS,new QStandardItem(server_data_object.address));
    p_model->setItem(row, SERVER_TABLE_COLUMN_ID::PORT,new QStandardItem(server_data_object.port));
    */
    QStandardItem *p_item = nullptr;

    p_item = p_model->item(row, SERVER_TABLE_COLUMN_ID::CHECKED);
    p_item->setText(return_select_symbol(server_data_object.selected));

    p_item = p_model->item(row, SERVER_TABLE_COLUMN_ID::REMARKS);
    p_item->setText(server_data_object.remarks);

    p_item = p_model->item(row, SERVER_TABLE_COLUMN_ID::ADDRESS);
    p_item->setText(server_data_object.address);

    p_item = p_model->item(row, SERVER_TABLE_COLUMN_ID::PORT);
    p_item->setText(QString::number(server_data_object.port));
}

void MainWindow::table_set_item_checked(const int row)
{
    QStandardItemModel *p_model = dynamic_cast<QStandardItemModel *>(ui->server_table_view->model());
    int all_row = p_model->rowCount();
    for (int i = 0; i < all_row; i++)
    {
        QStandardItem *p_item = nullptr;
        if(i == row)
        {
            //p_model->setItem(row, SERVER_TABLE_COLUMN_ID::CHECKED, new QStandardItem(return_select_symbol(true)));
            p_item = p_model->item(i, SERVER_TABLE_COLUMN_ID::CHECKED);
            p_item->setText(return_select_symbol(true));
        }
        else
        {
            p_item = p_model->item(i, SERVER_TABLE_COLUMN_ID::CHECKED);
            p_item->setText(return_select_symbol(false));
        }
    }

}

void MainWindow::server_object_add(const v2ray_core_server_data &server_data_object)
{
    m_config.server_data_vector.push_back(server_data_object);
}

void MainWindow::server_object_remove(const int pos)
{
    m_config.server_data_vector.removeAt(pos);
}

void MainWindow::server_object_set(const int pos, const v2ray_core_server_data &server_data_object)
{
    m_config.server_data_vector.replace(pos, server_data_object);
}

void MainWindow::server_object_set_selected(const int pos)
{
    for(int i = 0; i < m_config.server_data_vector.size(); i++)
    {
        if(i == pos)
        {
            m_config.server_data_vector[i].selected = true;
        }
        else
        {
            m_config.server_data_vector[i].selected = false;
        }
    }
}

void MainWindow::gen_sync_server_data()
{
    clear_table();
    for (auto &it : m_config.server_data_vector)
    {
        table_add_item(it);
    }
}

void MainWindow::gen_add_server(const v2ray_core_server_data &server_data_object)
{
    server_object_add(server_data_object);
    table_add_item(server_data_object);
}

void MainWindow::gen_remove_server(const int pos)
{
    table_remove_item(pos);
    server_object_remove(pos);
}

void MainWindow::gen_set_server(const int pos, const v2ray_core_server_data &server_data_object)
{
    table_set_item(pos, server_data_object);
    server_object_set(pos, server_data_object);
}

void MainWindow::gen_set_server_selected(const int pos)
{
    table_set_item_checked(pos);
    server_object_set_selected(pos);
}

void MainWindow::get_subscription_url(const QString &string_url, const QString &string_subscription_id)
{
    QUrl qurl(string_url);
    QNetworkAccessManager *p_manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(qurl);
    QNetworkReply *p_reply = p_manager->get(request);
    //传递subscription_id参数
    p_reply->setProperty("subscription_id", string_subscription_id);
    QObject::connect(p_manager, &QNetworkAccessManager::finished, this, &MainWindow::subscription_download_finish_slot);
}

void MainWindow::gen_add_vmess_subscription_group(const QStringList &vmess_list, const QString &subscription_id)
{
    for (const QString &link : vmess_list)
    {
        v2ray_core_server_data server_data_object;
        server_data_object.subscription_id = subscription_id;
        //server_data_object.user_security = "auto";
        bool b_valid = vmess_link::load_form_link(link, server_data_object);
        if(b_valid == true)
        {
            gen_add_server(server_data_object);
        }
    }
}

void MainWindow::print_text_to_window(const QString &log)
{
    QString append_log = log;
    if(append_log.endsWith('\n') == true)
    {
        append_log.resize(append_log.size() - 1);
    }
    ui->textBrowser_log->append(log);
}

void MainWindow::save_config_to_file()
{
    m_config.save_config();
}

int MainWindow::find_selected_server_index()
{
    const int server_data_size = m_config.server_data_vector.size();
    int i;
    for(i = 0; i < server_data_size; i++)
    {
        if(m_config.server_data_vector[i].selected == true)
        {
            return i;
        }
    }
    return -1;
}

void MainWindow::start_selected_v2ary_process()
{
    int index = find_selected_server_index();
    if(index < 0)
    {
        //没有任何选中
        return;
    }
    //创建config文件
    QString exec_config_path = translate_environment_path(DEFAULT_V2RAY_EXEC_CONFIG_FILENAME);
    const v2ray_core_server_data &server_data = m_config.server_data_vector[index];
    v2ray_json_config json_conf;
    json_conf.create_config_file_from_server_data(exec_config_path, server_data, m_config.current_template_path);
    start_v2ary_process();
}

void MainWindow::close_v2ary_process()
{
    int n_process_state = m_process.state();
    if(n_process_state != QProcess::NotRunning)
    {
        //m_process.kill();
        m_process.close();
    }
    m_process.disconnect();
}

void MainWindow::start_v2ary_process()
{
    close_v2ary_process();

    m_process.setProcessChannelMode(QProcess::MergedChannels);
    m_process.setProgram(translate_environment_path(DEFAULT_V2RAY_EXEC));
    QStringList argvs;
    argvs.append("-config");
    argvs.append(translate_environment_path(DEFAULT_V2RAY_EXEC_CONFIG_FILENAME));
    m_process.setArguments(argvs);
    m_process.start();
    if(m_process.waitForStarted() == false)
    {
        //启动失败
        print_text_to_window(QObject::tr("Start process faild."));
        return;
    }
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(output_process_log_slot()));
    //connect(&m_process,SIGNAL(readyReadStandardError()),this,SLOT(output_process_log()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_tray_icon->isVisible() == true)
    {
        hide(); //隐藏窗口
        event->ignore(); //忽略事件
    }
}

void MainWindow::hideEvent(QHideEvent *event)
{
    if(m_tray_icon->isVisible() == true)
    {
        //隐藏窗口
        hide();
        //忽略事件
        event->ignore();
    }
}

void MainWindow::table_custom_right_menu_slot(QPoint pos)
{
    //define menu
    QMenu *pop_menu = new QMenu(this);
    QAction *action_select = new QAction(QObject::tr("&Select server"), this);
    QAction *action_add = new QAction(QObject::tr("&Add"), this);
    QAction *action_modify = new QAction(QObject::tr("&Modify"), this);
    QAction *action_delete = new QAction(QObject::tr("&Delete"), this);
    QAction *action_import_link = new QAction(QObject::tr("&Import link from clipboard"), this);
    QAction *action_export_link = new QAction(QObject::tr("&Export link to clipboard"), this);

    pop_menu->addAction(action_select);
    //添加分隔符
    pop_menu->addSeparator();
    pop_menu->addAction(action_add);
    pop_menu->addAction(action_modify);
    pop_menu->addAction(action_delete);

    //添加分隔符
    pop_menu->addSeparator();
    pop_menu->addAction(action_import_link);
    pop_menu->addAction(action_export_link);

    connect(action_select, SIGNAL(triggered()), this, SLOT(custom_menu_select_server_slot()));
    connect(action_add, SIGNAL(triggered()), this, SLOT(custom_menu_add_slot()));
    connect(action_modify, SIGNAL(triggered()), this, SLOT(custom_menu_modeify_slot()));
    connect(action_delete, SIGNAL(triggered()), this, SLOT(custom_menu_delete_slot()));
    connect(action_import_link, SIGNAL(triggered()), this, SLOT(custom_menu_import_link_slot()));
    connect(action_export_link, SIGNAL(triggered()), this, SLOT(custom_menu_export_link_slot()));
    //
    QModelIndex index = ui->server_table_view->indexAt(pos);
    if (index.isValid())
    {
        pop_menu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
    }
    pop_menu->disconnect();
    pop_menu->close();
    pop_menu->deleteLater();
}

void MainWindow::custom_menu_select_server_slot()
{
    QModelIndexList selected = ui->server_table_view->selectionModel()->selectedRows();
    int n_index = 0;
    if(selected.size() > 0)
    {
        n_index = selected.first().row();
        gen_set_server_selected(n_index);
    }
    else
    {
        return;
    }
    save_config_to_file();
    start_selected_v2ary_process();
    /*
    for(const QModelIndex &index:selected)
    {
        gen_set_server_selected(index.row());
        break;
    }
    */
}

void MainWindow::custom_menu_add_slot()
{

    dialog_set_server *dlg = new dialog_set_server(this);

    connect(dlg, &dialog_set_server::signal_send_server_data, this, &MainWindow::add_server_slot);

    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::custom_menu_add_files_slot()
{
    //QFileDialog
    QFileDialog qfd(this);
    //设置模式
    qfd.setAcceptMode(QFileDialog::AcceptOpen);
    //返回文件名，无论文件是否存在
    qfd.setFileMode(QFileDialog::AnyFile);
    //设置标题
    qfd.setWindowTitle(QObject::tr("Open File"));
    //设置起始目录
    qfd.setDirectory(".");
    //设置显示过滤列表
    QStringList name_filter_list;
    name_filter_list << QObject::tr("Any files (*)");
    //设置显示过滤
    qfd.setNameFilters(name_filter_list);
    //显示对话框
    qfd.exec();
    //获取选择路径
    QStringList qlist_filepath = qfd.selectedFiles();
    if(qlist_filepath.size() == 0)
    {
        return;
    }
    for(auto &filepath : qlist_filepath)
    {
        v2ray_core_server_data server_data_object;
        server_data_object.set_custom_file(filepath);
        gen_add_server(server_data_object);
    }
    save_config_to_file();
}

void MainWindow::custom_menu_modeify_slot()
{
    int item_count = ui->server_table_view->model()->rowCount();
    if(item_count == 0)
    {
        return;
    }
    int index_selected = ui->server_table_view->selectionModel()->currentIndex().row();
    dialog_set_server *dlg = new dialog_set_server(this);

    connect(dlg, &dialog_set_server::signal_send_server_data, this, &MainWindow::change_server_slot);

    dlg->set_server_data(index_selected, m_config.server_data_vector[index_selected]);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::custom_menu_delete_slot()
{
    while (true)
    {
        QModelIndexList selected = ui->server_table_view->selectionModel()->selectedRows();
        if(selected.size() > 0)
        {
            gen_remove_server(selected.first().row());
        }
        else
        {
            break;
        }
    }
    save_config_to_file();
}

void MainWindow::custom_menu_import_link_slot()
{
    QString string_link = GetClipboard();
    v2ray_core_server_data server_data_object;
    bool b_valid = vmess_link::load_form_link(string_link, server_data_object);
    if(b_valid == true)
    {
        gen_add_server(server_data_object);
    }
    save_config_to_file();
}

void MainWindow::custom_menu_export_link_slot()
{

    int n_selected_row = 0;
    QModelIndexList selected = ui->server_table_view->selectionModel()->selectedRows();
    if(selected.size() > 0)
    {
        selected.first().row();
    }
    else
    {
        return;
    }
    QString string_link;
    const v2ray_core_server_data &server_data_object = m_config.server_data_vector[n_selected_row];
    vmess_link::save_to_link(server_data_object, string_link);
    SetClipboard(string_link);
}

void MainWindow::add_server_slot(const int index, const v2ray_core_server_data &data)
{
    Q_UNUSED(index)
    gen_add_server(data);
    save_config_to_file();
}

void MainWindow::change_server_slot(const int index, const v2ray_core_server_data &data)
{
    gen_set_server(index, data);
    save_config_to_file();
}

void MainWindow::subscription_download_finish_slot(QNetworkReply *p_reply)
{
    QMutexLocker subscription_locker(&m_window_mutex);
    QString subscription_id = p_reply->property("subscription_id").toString();
    QVariant variant = p_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    /*
    if (variant.isValid() == false)
    {
        qDebug() << "http status code : " << variant.toInt();
    }
    */
    if (p_reply->error() == QNetworkReply::NoError)
    {
        //call
        QByteArray bytes = p_reply->readAll();
        //QString string(bytes); // string
        QString string = QString::fromUtf8(bytes);
        QStringList vmess_list = vmess_subscription::subscription_raw_data_to_list(bytes);
        gen_add_vmess_subscription_group(vmess_list, subscription_id);
    }
    else
    {
        print_text_to_window(QObject::tr("download config %1 error.").arg(subscription_id));
        //print_text_to_window(QObject::tr("network error"));
    }
    save_config_to_file();
    p_reply->close();
    p_reply->deleteLater();
}

void MainWindow::custom_menu_update_subscription_slot()
{
    custom_menu_clear_subscription_slot();
    QString abs_path = translate_environment_path(DEFAULT_CONFIG_SUBSCRIPTION_DIR);
    QList<QString> subscription_list;
    qt_os_filesystem::listdir(abs_path, subscription_list);
    for (auto &it : subscription_list)
    {
        QFile file(it);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << QObject::tr("Can't open the file!") << endl;
            return;
        }
        QByteArray qbytedata = file.readAll();
        QString url = QString::fromUtf8(qbytedata);
        QFileInfo finfo(it);
        QString filename = finfo.fileName();
        print_text_to_window(QObject::tr("Found subscription config %1").arg(filename));
        get_subscription_url(url, filename);
    }
}

void MainWindow::custom_menu_clear_subscription_slot()
{
    for (auto it = m_config.server_data_vector.begin(); it != m_config.server_data_vector.end(); )
    {
        if(it->subscription_id.isEmpty() == false)
        {
            it = m_config.server_data_vector.erase(it);
        }
        else
        {
            it++;
        }
    }
    gen_sync_server_data();
    save_config_to_file();
}

void MainWindow::custom_menu_set_config_template_window_slot()
{
    dialog_gui_config *dlg = new dialog_gui_config(this);

    connect(dlg, &dialog_gui_config::signal_selected_template_path, this, &MainWindow::set_config_template_path_slot);

    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
    //dlg->exec();
    //dlg->deleteLater();
}

void MainWindow::set_config_template_path_slot(const QString &path)
{
    m_config.current_template_path = path;
    save_config_to_file();
}

void MainWindow::output_process_log_slot()
{
    //int n_process_state = m_process.state();
    QString output_data = m_process.readAll();
    print_text_to_window(output_data);
}

void MainWindow::custom_menu_restart_process_slot()
{
    ui->textBrowser_log->clear();
    start_v2ary_process();
}

void MainWindow::custom_menu_terminate_process_slot()
{
    close_v2ary_process();
}

void MainWindow::tray_icon_activated_slot(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        //单击
        if(this->isHidden() == true)
        {
            //this->show();
            this->showNormal();
            this->activateWindow();
        }
        else
        {
            this->hide();
        }
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击
        this->hide();
        break;
    case QSystemTrayIcon::MiddleClick:
        //中键
        //m_tray_icon->showMessage("title","MiddleClick");
        break;
    default:
        break;
    }
}

void MainWindow::tray_exit_slot()
{
    close_v2ary_process();
    QApplication::exit(0);
}
