#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QDir>
#include "v2ray_json_config.h"

void SetAppWorkDir(QApplication *app)
{
    //设置工作目录为程序目录
    QString app_dir = app->applicationDirPath();
    qDebug() << app_dir << endl;
    QDir::setCurrent(app_dir);
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    SetAppWorkDir(&app);

    MainWindow w;
    w.show();

    return app.exec();
}
