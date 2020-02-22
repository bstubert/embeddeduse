// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef CUSTOMERMANAGER_H
#define CUSTOMERMANAGER_H

#include <QObject>
#include <QVector>
#include "Customer.h"

class CustomerManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject *randomCustomer READ randomCustomer CONSTANT)

public:
    CustomerManager(QObject *parent = nullptr)
        : QObject(parent)
    {
        m_customers.append(new Customer("Joe", "Smith"));
        m_customers.append(new Customer("Jack", "Miller"));
        m_customers.append(new Customer("Harold", "Beck"));
    }

    ~CustomerManager()
    {
        qDeleteAll(m_customers);
    }

    Q_INVOKABLE Customer *randomCustomer() const
    {
        return m_customers[qrand() % 3];
    }

private:
    QVector<Customer *> m_customers;
};

#endif // CUSTOMERMANAGER_H

