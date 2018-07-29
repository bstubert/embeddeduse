// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QString>
#include <QtDebug>
#include <QTimer>

// #define SINGLE_SHOT_WITH_SLOT
// #define SINGLE_SHOT_WITH_LAMBDA
// #define SINGLE_SHOT_WITH_LAMBDA_AND_CONTEXT
// #define SINGLE_SHOT_WITH_LAMBDA_AND_VALUES

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

#ifdef SINGLE_SHOT_WITH_SLOT
        // Single-shot with slot: No crash
        QTimer::singleShot(5000, this, &Customer::printWithSlot);
#endif

#ifdef SINGLE_SHOT_WITH_LAMBDA_AND_CONTEXT
        // Single-shot with lambda and context: No crash
        QTimer::singleShot(5000, this, [this]() {
            qDebug() << "*** Single-shot with lambda and context";
            qDebug() << "Customer: " << firstName() << lastName();
        });
#endif

#ifdef SINGLE_SHOT_WITH_LAMBDA_AND_VALUES
        // Single-shot with lambda and values: No crash
        auto first = firstName();
        auto last = lastName();
        QTimer::singleShot(5000, [first, last]() {
            qDebug() << "*** Single-shot with lambda and values";
            qDebug() << "Customer: " << first << last;
        });
#endif
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

#ifdef SINGLE_SHOT_WITH_SLOT
private slots:
    void printWithSlot()
    {
        qDebug() << "*** Single-shot with slot";
        qDebug() << "Customer: " << firstName() << lastName();
    }

#endif

signals:
    void firstNameChanged();
    void lastNameChanged();

private:
    QString m_firstName;
    QString m_lastName;
};

#endif // CUSTOMER_H
