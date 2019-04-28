#include "dialog_set_server.h"
#include "ui_dialog_set_server.h"

dialog_set_server::dialog_set_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_set_server)
{
    ui->setupUi(this);
    m_server_data_index = 0;

    set_ui_limit();

    sync_data_to_ui();
}

dialog_set_server::~dialog_set_server()
{
    delete ui;
}

void dialog_set_server::set_ui_limit()
{
    QIntValidator *pIntValidator = new QIntValidator;
    pIntValidator->setRange(1, 65535);
    ui->lineEdit_port->setValidator(pIntValidator);
    ui->lineEdit_alter_id->setValidator(pIntValidator);
}

void dialog_set_server::set_server_data(const int index, const v2ray_core_server_data &input)
{
    m_server_data_index = index;
    m_server_data = input;
    sync_data_to_ui();
}

void dialog_set_server::sync_data_to_ui()
{
    ui->lineEdit_remarks->setText(m_server_data.remarks);
    ui->lineEdit_address->setText(m_server_data.address);
    ui->lineEdit_port->setText(QString::number(m_server_data.port));
    ui->lineEdit_user_id->setText(m_server_data.user_id);
    ui->lineEdit_alter_id->setText(QString::number(m_server_data.alter_id));
    ui->lineEdit_stream_host->setText(m_server_data.stream_host);
    ui->lineEdit_stream_path->setText(m_server_data.stream_path);
    ui->comboBox_network->setCurrentText(m_server_data.network);
    ui->comboBox_pertend_type->setCurrentText(m_server_data.stream_type);
    ui->comboBox_user_security->setCurrentText(m_server_data.user_security);
    ui->comboBox_stream_security->setCurrentText(m_server_data.stream_security);
}

void dialog_set_server::sync_ui_to_data()
{
    m_server_data.remarks = ui->lineEdit_remarks->text();
    m_server_data.address = ui->lineEdit_address->text();
    m_server_data.port = ui->lineEdit_port->text().toInt();
    m_server_data.user_id = ui->lineEdit_user_id->text();
    m_server_data.alter_id = ui->lineEdit_alter_id->text().toInt();
    m_server_data.stream_host = ui->lineEdit_stream_host->text();
    m_server_data.stream_path = ui->lineEdit_stream_path->text();
    m_server_data.stream_type = ui->comboBox_pertend_type->currentText();
    m_server_data.network = ui->comboBox_network->currentText();
    m_server_data.user_security = ui->comboBox_user_security->currentText();
    m_server_data.stream_security = ui->comboBox_stream_security->currentText();
}

void dialog_set_server::on_pushButton_ok_clicked()
{
    sync_ui_to_data();
    if(m_server_data.stream_type == "none")
    {

    }
    else if(m_server_data.stream_type == "http")
    {
        if(m_server_data.network != "tcp")
        {
            return;
        }
    }
    else
    {
        if(m_server_data.network != "kcp")
        {
            return;
        }
    }
    emit signal_send_server_data(m_server_data_index, m_server_data);
    this->close();
}

void dialog_set_server::on_pushButton_cancel_clicked()
{
    this->close();
}
