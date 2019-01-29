#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QString>
#include <QDebug>

class Message : public QObject {

	Q_OBJECT

	Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)

public:

	void setAuthor(const QString &a)
	{
        qDebug() << "setAuthor()";
    	if (a != m_author) {
        	m_author = a;
          	emit authorChanged();
      	}
  	}

  	QString author() const
 	{
        qDebug() << "author(): " << m_author;
		return m_author;
  	}

	Q_INVOKABLE bool postMessage(const QString &msg)
	{
        qDebug() << "Called the C++ method with" << msg;
        return true;
    }

signals:

    void authorChanged();

public slots:

    void refresh()
    {
        qDebug() << "Called the C++ slot";
    }

private:

  QString m_author;
};

#endif
