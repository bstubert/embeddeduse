// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include <QObject>
#include "Customer.h"

class CustomerManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Customer *currentCustomer READ currentCustomer
               WRITE setCurrentCustomer NOTIFY currentCustomerChanged)

public:
    CustomerManager(QObject *parent = nullptr)
        : QObject(parent)
    {
        m_currentCustomer = new Customer();
        m_currentCustomer->setFirstName("Joe");
        m_currentCustomer->setLastName("Smith");
    }

    ~CustomerManager()
    {
        delete m_currentCustomer;
    }

    Customer *currentCustomer() const
    {
        return m_currentCustomer;
    }

    void setCurrentCustomer(Customer *customer)
    {
        if (m_currentCustomer != customer) {
            m_currentCustomer = customer;
            emit currentCustomerChanged();
        }
    }

signals:
    void currentCustomerChanged();

private:
    Customer *m_currentCustomer{};
};

#endif // CUSTOMERMANAGER_H

