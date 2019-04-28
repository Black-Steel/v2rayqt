#ifndef DIALOG_GUI_CONFIG_H
#define DIALOG_GUI_CONFIG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QFileInfo>
#include "qt_os_filesystem.h"
#include "config_constexpr.h"
#include "translate_environment_path.h"
namespace Ui
{
    class dialog_gui_config;
}

class dialog_gui_config : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_gui_config(QWidget *parent = nullptr);
    void find_config_template();
    void sync_combobox();
    ~dialog_gui_config();

signals:
    void signal_selected_template_path(const QString &path);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    QStringList m_template_path;
    Ui::dialog_gui_config *ui;
};

#endif // DIALOG_GUI_CONFIG_H
