// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include <QObject>
#include <QVector>
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
        auto customer = new Customer();
        customer->setFirstName("Joe");
        customer->setLastName("Smith");
        m_customers.append(customer);
        setCurrentCustomer(customer);
    }

    ~CustomerManager()
    {
        qDeleteAll(m_customers);
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
    QVector<Customer *> m_customers;
    Customer *m_currentCustomer{};
};

#endif // CUSTOMERMANAGER_H

