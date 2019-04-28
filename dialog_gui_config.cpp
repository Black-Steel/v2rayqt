#include "dialog_gui_config.h"
#include "ui_dialog_gui_config.h"

dialog_gui_config::dialog_gui_config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_gui_config)
{
    ui->setupUi(this);
    find_config_template();
    sync_combobox();
}

void dialog_gui_config::find_config_template()
{
    QString abs_path = translate_environment_path(DEFAULT_CONFIG_TEMPLATE_DIR);

    qt_os_filesystem::listdir(abs_path, m_template_path);
}

void dialog_gui_config::sync_combobox()
{
    ui->comboBox_template->clear();
    for (auto &it : m_template_path)
    {
        QFileInfo fileinfo(it);
        QString basename = fileinfo.fileName();
        ui->comboBox_template->addItem(basename);
    }
    //ui->comboBox_template->addItems(m_template_path);
    ui->comboBox_template->setCurrentIndex(0);
}

dialog_gui_config::~dialog_gui_config()
{
    delete ui;
}

void dialog_gui_config::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok))
    {
        int current_index = ui->comboBox_template->currentIndex();
        QString send_path = m_template_path[current_index];
        emit signal_selected_template_path(send_path);
    }
    this->close();
}

