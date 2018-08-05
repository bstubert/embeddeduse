// Copyright (C) 2018 Burkhard Stubert (DBA EmbeddedUse)

#include <QtDebug>
#include "Model.h"

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

Model::Impl::Impl(Model *parent)
    : QObject(parent)
    , m_iface(parent)
    , m_infoText{QStringLiteral("Waiting...")}
{
    qDebug() << "@@@ Model::Impl ctor";
}

Model::Impl::~Impl()
{
    qDebug() << "### Model::Impl dtor";
    setInfoText("Crashed!!!");
}

QString Model::Impl::infoText() const
{
    qDebug() << "*** Model::Impl::infoText = " << m_infoText;
    return m_infoText;
}

void Model::Impl::setInfoText(const QString &text)
{
    if (m_infoText != text) {
        qDebug() << "*** Model::Impl::setInfoText = " << text;
        m_infoText = text;
        emit m_iface->infoTextChanged();
    }
}

Model::Model(QObject *parent)
    : QObject{parent}
    , m_impl{new Impl{this}}
{
    qDebug() << "@@@ Model ctor";
}

Model::~Model()
{
    qDebug() << "### Model dtor";
}

QString Model::infoText() const
{
    qDebug() << "*** Model::infoText()";
    return m_impl->infoText();
}

void Model::setInfoText(const QString &text)
{
    m_impl->setInfoText(text);
}

#include "Model.moc"
