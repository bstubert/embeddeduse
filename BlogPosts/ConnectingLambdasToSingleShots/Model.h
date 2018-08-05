// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QString>
#include <QtDebug>
#include <QTimer>

 #define SINGLE_SHOT_WITH_SLOT
// #define SINGLE_SHOT_WITH_LAMBDA
// #define SINGLE_SHOT_WITH_LAMBDA_AND_CONTEXT

class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString infoText READ infoText WRITE setInfoText NOTIFY infoTextChanged)

public:
    Model(QObject *parent = nullptr) :
        QObject{parent},
        m_infoText{"Waiting..."}
    {
        qDebug() << "@@@ Creating Customer";

#ifdef SINGLE_SHOT_WITH_SLOT
        // Single-shot with slot: No crash
        QTimer::singleShot(500, this, &Model::updateInfoText);
#endif

#ifdef SINGLE_SHOT_WITH_LAMBDA
        // Single-shot with lambda: Crash
        QTimer::singleShot(500, [this]() {
            this->setInfoText("INFO: Lambda");
        });
#endif

#ifdef SINGLE_SHOT_WITH_LAMBDA_AND_CONTEXT
        // Single-shot with lambda and context: No crash
        QTimer::singleShot(500, this, [this]() {
            this->setInfoText("INFO: Context");
        });
#endif
    }

    ~Model()
    {
        qDebug() << "### Destroying Customer";
    }

    QString infoText() const
    {
        return m_infoText;
    }

    void setInfoText(QString text)
    {
        if (m_infoText != text) {
            m_infoText = text;
            emit infoTextChanged();
        }
    }

#ifdef SINGLE_SHOT_WITH_SLOT
private slots:
    void updateInfoText()
    {
        this->setInfoText("INFO: Slot");
    }

#endif

signals:
    void infoTextChanged();

private:
    QString m_infoText;
};

#endif // CUSTOMER_H
