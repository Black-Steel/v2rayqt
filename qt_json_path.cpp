#include "qt_json_path.h"

QJsonPath::QJsonPath()
{

}

void QJsonPath::setPathValue(QJsonObject &node, const QString &node_path, const QJsonValue &new_value)
{
    // 查找第一个 . 的位置
    const int n_dot_pos = node_path.indexOf('.');
    // current_key为第一个 . 之前的内容。如果 n_dot_pos 是 -1 则返回整个字符串
    const QString current_key = node_path.left(n_dot_pos);
    QString next_path;
    // n_dot_pos > 0 时说明 . 后面有内容
    if(n_dot_pos > 0)
    {
        next_path = node_path.mid(n_dot_pos + 1);
    }

    //QJsonValue curren_value = node[current_key];

    if(next_path.isEmpty() == true)
    {
        // next_path 为空, 说明 current_key 就是 node_path 中最后一个 . 右边的部分
        // 也就是要设置的属性
        // 如果不存在则会创建
        node[current_key] = new_value;
    }
    else
    {
        // 路径中间的属性，递归访问它的子属性
        QJsonObject child_node = node[current_key].toObject();
        setPathValue(child_node, next_path, new_value);
        // 归结束后需要保存起来再次设置回 current_key
        node[current_key] = child_node;
    }
}

QJsonValue QJsonPath::getPathValue(const QJsonObject &node, const QString &path)
{
    QJsonValue return_value;
    if(node.isEmpty() == true)
    {
        return return_value;
    }

    QStringList node_list  = path.split('.');
    QJsonObject current_node = node;
    // 查找到倒数第二个属性名字对应的 QJsonObject
    const int n_list_size = node_list.size();
    const int n_key_count = n_list_size - 1;
    for (int i = 0; i < n_key_count; ++i)
    {
        if (current_node.isEmpty())
        {
            return QJsonValue();
        }

        current_node = current_node.value(node_list.at(i)).toObject();
    }

    // 返回value
    return current_node.value(node_list.last());
}
