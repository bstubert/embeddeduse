// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QString>
#include <QtDebug>
#include <QTimer>

class Customer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName
               NOTIFY firstNameChanged)

    Q_PROPERTY(QString lastName READ lastName WRITE setLastName
               NOTIFY lastNameChanged)

public:
    Customer(QObject *parent = nullptr) :
        QObject{parent},
        m_firstName{"Jane"},
        m_lastName{"Doe"}
    {
        qDebug() << "@@@ Creating Customer";
        QTimer::singleShot(5000, this, &Customer::printBySlot);
    }

    ~Customer()
    {
        qDebug() << "### Destroying Customer";
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

private slots:
    void printBySlot()
    {
        qDebug() << "*** printCustomer";
        qDebug() << "Customer: " << firstName() << lastName();
    }

signals:
    void firstNameChanged();
    void lastNameChanged();

private:
    QString m_firstName;
    QString m_lastName;
};

#endif // CUSTOMER_H
