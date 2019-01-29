#include <QtCore/QCoreApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QVariant>
#include <iostream>
#include <QSslSocket>

using namespace std;

int main(int argc, char *argv[]){
	QCoreApplication a(argc, argv);

    qDebug()<<"SSL version use for build: "<<QSslSocket::sslLibraryBuildVersionString();
    qDebug()<<"SSL version use for run-time: "<<QSslSocket::sslLibraryVersionNumber();
    qDebug()<<QCoreApplication::libraryPaths();

	QString message=R"RR({"ID":259189459021535250265000001110000000,"IDs":"635913899220803700"})RR";
	QJsonParseError err;

	QJsonDocument Doc=QJsonDocument::fromJson(message.toUtf8(),&err);

    cout << err.errorString().toStdString().c_str() << endl;

	unsigned long long ia=Doc.object()["ID"].toDouble();
    cout << "ia: " << ia << endl;

	unsigned long long ib=Doc.object()["ID"].toVariant().toLongLong();
    cout << "ib"<< ib << endl;

    cout << Doc.object()["ID"].toString().toStdString().c_str() << endl;

    cout << Doc.object()["ID"].toVariant().toString().toStdString().c_str() << endl;
    cout << Doc.object()["ID"].toVariant().toDouble() << endl;

	return a.exec();
}
