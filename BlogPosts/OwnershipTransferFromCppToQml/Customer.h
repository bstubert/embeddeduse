// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QString>
#include <QtDebug>

class Customer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName
               NOTIFY firstNameChanged)

    Q_PROPERTY(QString lastName READ lastName WRITE setLastName
               NOTIFY lastNameChanged)

public:
    Customer(QObject *parent = nullptr)
        : QObject(parent)
    {}

    ~Customer()
    {
        qDebug() << "### Deleting C++ customer object";
    }

    QString firstName() const
    {
        return m_firstName;
    }

    void setFirstName(QString firstName)
    {
        if (m_firstName != firstName) {
            m_firstName = firstName;
            emit firstNameChanged();
        }
    }

    QString lastName() const
    {
        return m_lastName;
    }

    void setLastName(QString lastName)
    {
        if (m_lastName != lastName) {
            m_lastName = lastName;
            emit lastNameChanged();
        }
    }

signals:
    void firstNameChanged();
    void lastNameChanged();

private:
    QString m_firstName;
    QString m_lastName;
};

#endif // CUSTOMER_H
