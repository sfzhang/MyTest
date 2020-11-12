#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomAttr>
#include <QFile>
#include <QtDebug>
#include <QString>
#include <QStringList>
#include <QColor>

#define CHECK_NODE(node, str) \
    do { \
        if (node.isNull()) { \
            qDebug() << str << " is null" << endl; \
        } \
        else { \
            qDebug() << str << " is not null" << endl; \
        } \
    } while (0)

QDomDocument g_doc;

QDomElement find(const QStringList &tag_list)
{
    QDomNode ele = g_doc;
    for (const auto &tag: tag_list) {
        if (!ele.isNull()) {
            ele = ele.firstChildElement(tag);
        }
        else {
            break;
        }
    }

    return ele.toElement();
}

template<typename T>
bool getValue(const QString &path, T &value)
{
    auto node = find(path.split('.')).firstChild();
    if (node.isText() && !node.nodeValue().isEmpty()) {
        auto var = QVariant(node.nodeValue());
        if (var.canConvert<T>()) {
            value = var.value<T>();
            return true;
        }
    }

    return false;
}

template<typename T>
bool getAttribute(const QString &path, const QString &attribute, T &value)
{
    auto text = find(path.split('.')).attribute(attribute);
    if (!text.isEmpty()) {
        auto var = QVariant(text);
        if (var.canConvert<T>()) {
            value = var.value<T>();
            return true;
        }
    }
    return false;
}

template<typename T>
bool replaceValue(const QString &path, const T &value)
{
    auto node = find(path.split('.')).firstChild();
    if (node.isText()) {
        node.setNodeValue(QVariant(value).toString());
        return true;
    }
    return false;
}

template <typename T>
bool replaceAttribute(const QString &path, const QString &attribute, const T &value)
{
    auto node = find(path.split('.')).attributeNode(attribute);
    if (!node.isNull()) {
        node.setValue(QVariant(value).toString());
        return true;
    }
    return false;
}

bool save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        return false;
    }

    QTextStream stream;
    stream.setDevice(&file);
    stream.setCodec("UTF-8");

    g_doc.save(stream, 4);
    file.close();
    return true;
}

int main()
{
    QFile file("/home/fus/Git/MyTest/qt/xml/a.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open file failed" << endl;
        return -1;
    }

    if (!g_doc.setContent(&file)) {
        qDebug() << "setContent() failed" << endl;
        return -1;
    }

    QDomElement root = g_doc.documentElement();
    qDebug() << root.tagName() << " " << root.text() << endl;

    auto text_node = root.toText();
    CHECK_NODE(text_node, "root");

    auto node = g_doc.firstChildElement("h");
    CHECK_NODE(node, "h");

    node = g_doc.firstChildElement("hifu");
    CHECK_NODE(node, "hifu");
    qDebug() << "hifu node value: " << node.text() << endl;
    node = node.firstChildElement("stats");
    CHECK_NODE(node, "stats");
    auto attr = node.attributeNode("b");
    qDebug() << "hifu.stats<b> is specified: " << attr.specified() << endl;
    attr.setValue("f");
    qDebug() << "hifu.stats<b> is specified: " << attr.specified() << endl;
    qDebug() << "stats node value: " << node.text() << endl;
    node = node.firstChildElement("ledr_threshold_temp");
    CHECK_NODE(node, "ledr_");
    qDebug() << "node value: " << node.nodeValue() << endl;
    qDebug() << "node text value: " << node.text() << endl;
    qDebug() << "isText: " << node.isText() << endl;
    qDebug() << "isElement: " << node.isElement() << endl;

    auto child_node = node.firstChild();
    CHECK_NODE(child_node, "ledr");
    qDebug() << "isText: " << child_node.isText() << ":" << child_node.nodeValue() << endl;

    double d;
    if (getValue("hifu.stats.ledr_threshold_temp", d)) {
        qDebug() << "hifu.stats.ledr_threshold_temp" << ": " << d << endl;
    }

    auto ele = g_doc.toElement();
    CHECK_NODE(ele, "doc -> ele");

    QString s;
    if (getValue("hifu", s)) {
        qDebug() << "hifu" << ": " << s << endl;
    }
    else {
        qDebug() << "get hifu failed" << endl;
    }

    if (getValue("hifu.stats", s)) {
        qDebug() << "hifu.stats" << ": " << s << endl;
    }
    else {
        qDebug() << "get hifu.stats failed" << endl;
    }

    qDebug() << "------------" << endl;

    if (getAttribute("hifu", "a", s)) {
        qDebug() << "hifu<a>" << ": " << s << endl;
    }
    else {
        qDebug() << "get hifu<a> failed" << endl;
    }

    if (getAttribute("hifu.stats", "a", s)) {
        qDebug() << "hifu.stats<a>" << ": " << s << endl;
    }
    else {
        qDebug() << "get hifu.stats<a> failed" << endl;
    }

    bool b;
    if (getAttribute("hifu.stats", "b", b)) {
        qDebug() << "hifu.stats<b>" << ": " << b << endl;
    }
    else {
        qDebug() << "get hifu.stats<b> failed" << endl;
    }

    if (getAttribute("hifu.stats.ledr_threshold_temp", "b", s)) {
        qDebug() << "hifu.stats.ledr_threshold_temp<b>" << ": " << s << endl;
    }
    else {
        qDebug() << "get hifu.stats.ledr_threshold_temp<b> failed" << endl;
    }

    qDebug() << "Test replace ------------" << endl;
    if (replaceValue("hifu", "a")) {
        getValue("hifu", s);
        qDebug() << "replaceValue() hifu to a success: " << s << endl;
    }
    else {
        qDebug() << "replaceValue hifu to a failed" << endl;

    }

    if (replaceValue("hifu.stats", "a")) {
        getValue("hifu.stats", s);
        qDebug() << "replaceValue() hifu.stats to a success: " << s << endl;
    }
    else {
        qDebug() << "replaceValue hifu.stats to a failed" << endl;

    }

    if (replaceValue("hifu.stats.ledr_threshold_temp", "test")) {
        getValue("hifu.stats.ledr_threshold_temp", s);
        qDebug() << "replaceValue() hifu.stats.ledr_threshold_temp to test success: " << s << endl;
    }
    else {
        qDebug() << "replaceValue hifu.stats.ledr_threshold_temp to test failed" << endl;

    }

    qDebug() << "Test replace attribute ----" << endl;

    if (replaceAttribute("hifu", "a", "asdfa")) {
        getAttribute("hifu", "a", s);
        qDebug() << "replaceAttribute hifu<a> to asdfa success: " << s << endl;
    }
    else {
        qDebug() << "replaceAttribute hifu<a> to asdfa failed";
    }

    if (replaceAttribute("hifu.stats", "b", 10.5)) {
        getAttribute("hifu.stats", "b", s);
        qDebug() << "replaceAttribute hifu.stats<b> to 10.5 success: " << s << endl;
    }
    else {
        qDebug() << "replaceAttribute hifu.stats<b> to 10.5 failed";
    }

    if (replaceAttribute("hifu.stats.ledr_threshold_temp", "b", 100)) {
        getAttribute("hifu.stats.ledr_threshold_temp", "b", s);
        qDebug() << "replaceAttribute hifu.stats.ledr_threshold_temp<b> to 100 success: " << s << endl;
    }
    else {
        qDebug() << "replaceAttribute hifu.stats.ledr_threshold_temp<b> to 100 failed";
    }

    if (save("/home/fus/Git/MyTest/qt/xml/new_a.xml")) {
        qDebug() << "save() success" << endl;
    }
    else {
        qDebug() << "save() failed" << endl;
    }

    QColor c(125, 125, 125);
    qDebug() << c.alpha() << endl;

    return 0;
}
