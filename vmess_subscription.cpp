#include "vmess_subscription.h"


QStringList vmess_subscription::subscription_raw_data_to_list(const QByteArray &raw_bytes)
{
    QByteArray list_bytes = QByteArray::fromBase64(raw_bytes);
    QString string_list = QString::fromUtf8(list_bytes);
    QStringList vmess_link_list = string_list.split('\n', QString::SkipEmptyParts);
    return vmess_link_list;
}
