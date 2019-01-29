#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include "message.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQuickView view;
  	Message msg;
  	view.engine()->rootContext()->setContextProperty("msg", &msg);
  	view.setSource(QUrl::fromLocalFile("MyItem.qml"));
  	view.show();

  	return app.exec();
}
