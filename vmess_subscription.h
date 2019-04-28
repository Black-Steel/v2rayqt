#ifndef VMESS_SUBSCRIPTION_H
#define VMESS_SUBSCRIPTION_H

#include <QString>
#include <QStringList>
#include <QRegExp>
namespace vmess_subscription
{
    QStringList subscription_raw_data_to_list(const QByteArray &raw_bytes);
};

#endif // VMESS_SUBSCRIPTION_H
