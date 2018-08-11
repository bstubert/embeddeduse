// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#include <QtDebug>
#include "Model.h"

#define EMIT_IN_CONSTRUCTOR
#define EMIT_IN_DESTRUCTOR

class Model::Impl : public QObject
{
    Q_OBJECT

public:
    Impl(Model *parent);
    ~Impl();
    QString infoText() const;
    void setInfoText(const QString &text);
    Model *m_iface;
    QString m_infoText;
};

Model::Impl::Impl(Model *parent) :
    QObject(parent),
    m_iface(parent),
    m_infoText{QStringLiteral("Waiting...")}
{
    qDebug() << __PRETTY_FUNCTION__;
#ifdef EMIT_IN_CONSTRUCTOR
    setInfoText("Constructor: Oooops!!!");
#endif
}

Model::Impl::~Impl()
{
    qDebug() << __PRETTY_FUNCTION__;
#ifdef EMIT_IN_DESTRUCTOR
    setInfoText("Destructor: Oooops!!!");
#endif
}

QString Model::Impl::infoText() const
{
    return m_infoText;
}

void Model::Impl::setInfoText(const QString &text)
{
    if (m_infoText != text) {
        qDebug() << __PRETTY_FUNCTION__;
        m_infoText = text;
        emit m_iface->infoTextChanged();
    }
}

Model::Model(QObject *parent) :
    QObject{parent},
    m_impl{new Impl{this}}
{
    qDebug() << __PRETTY_FUNCTION__;
}

Model::~Model()
{
    qDebug() << __PRETTY_FUNCTION__;
}

QString Model::infoText() const
{
    return m_impl->infoText();
}

void Model::setInfoText(const QString &text)
{
    m_impl->setInfoText(text);
}

void Model::connectNotify(const QMetaMethod &signal)
{
    if (signal == QMetaMethod::fromSignal(&Model::infoTextChanged)) {
        qDebug() << __PRETTY_FUNCTION__ << ": Connected to signal infoTextChanged!";
    }
}

void Model::disconnectNotify(const QMetaMethod &signal)
{
    if (signal == QMetaMethod::fromSignal(&Model::infoTextChanged)) {
        qDebug() << __PRETTY_FUNCTION__ << ": Disconnected from signal infoTextChanged!";
    }
}

#include "Model.moc"
