// Copyright (C) 2019, Burkhard Stubert (DBA Embedded Use)

#include <algorithm>
#include <memory>
#include <utility>

#include <QByteArray>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>
#include <QCoreApplication>
#include <QList>
#include <QObject>
#include <QRandomGenerator>
#include <QSignalSpy>
#include <QString>
#include <QStringList>
#include <QtDebug>
#include <QtTest>
#include <QVector>

#include "canbusext.h"
#include "j1939_broadcast_frames.h"
#include "mockcanbusrouter.h"
#include "mockcanutils.h"

class TestWriteBufferOverflow : public QObject
{
    Q_OBJECT

    MockCanBusRouter *m_router{nullptr};

    static const int c_writeErrorInterval{4};

    QByteArray encodedReadParameter(int pid, int value = 0) const
    {
        QByteArray payload(8, 0x00);
        qToLittleEndian(static_cast<quint8>(1), payload.data());
        qToLittleEndian(static_cast<quint16>(pid), payload.data() + 1);
        qToLittleEndian(static_cast<qint32>(value), payload.data() + 3);
        return payload;
    }

    std::pair<QVector<J1939Frame>, QVector<J1939Frame>>
    createReadParameterRequests(quint16 count, quint16 startPid)
    {
        auto requestColl = QVector<J1939Frame>{};
        auto responseColl = QVector<J1939Frame>{};
        for (quint16 i = 0; i < count; ++i)
        {
            auto pid{quint16(startPid + i)};
            requestColl.append(ReadParameterRequest{0x02U, 0x01U, pid, 0U});
            auto value = static_cast<quint32>(QRandomGenerator::global()->generate());
            responseColl.append(ReadParameterResponse{0x01U, 0x02U, pid, value});
        }
        return std::make_pair(requestColl, responseColl);
    }

private slots:
    void initTestCase()
    {
        // The loader for the CAN bus plugins adds /canbus to each library path and looks for
        // plugins in /library/path/canbus. Hence, the directory containing the mockcan plugin
        // is called "canbus".
        QCoreApplication::addLibraryPath("../../");
    }

    void init()
    {
        m_router = new MockCanBusRouter{};
        m_router->setWriteErrorInterval(c_writeErrorInterval);
        m_router->setReceiveOwnFrameEnabled(true);
    }

    void cleanup()
    {
        delete m_router;
    }

    void testWriteBufferOverflow()
    {
        m_router->setReceiveOwnFrameEnabled(false);

        auto requestColl = QVector<J1939Frame>{};
        auto responseColl = QVector<J1939Frame>{};
        std::tie(requestColl, responseColl) = createReadParameterRequests(2 * c_writeErrorInterval, 32);
        m_router->expectWriteFrames(requestColl);

        for (const auto &request : requestColl)
        {
            m_router->writeFrame(request);
        }

        const auto &actualFrameColl = m_router->actualCanFrames();
        QCOMPARE(actualFrameColl.size(), 2 * c_writeErrorInterval);
        QCOMPARE(actualFrameColl[2 * c_writeErrorInterval - 1].deviceError(),
                QCanBusDevice::WriteError);
    }

    void testAvoidWriteBufferOverflow()
    {
        auto requestColl = QVector<J1939Frame>{};
        auto responseColl = QVector<J1939Frame>{};
        std::tie(requestColl, responseColl) = createReadParameterRequests(c_writeErrorInterval, 32);
        for (int i = 0; i < requestColl.count(); ++i)
        {
            m_router->expectWriteFrame(requestColl[i]);
            m_router->expectReadOwnFrame(requestColl[i]);
            m_router->expectReadFrame(responseColl[i]);
        }

        for (const auto &request : requestColl)
        {
            m_router->writeFrame(request);
        }

        QTRY_COMPARE_WITH_TIMEOUT(m_router->actualCanFrames(), m_router->expectedCanFrames(), 200);
        const auto &actualFrameColl = m_router->actualCanFrames();
        QCOMPARE(actualFrameColl[c_writeErrorInterval - 1].deviceError(), QCanBusDevice::NoError);
    }

    void testRecoverFromLostOwnFrame()
    {
        auto requestColl = QVector<J1939Frame>{};
        auto responseColl = QVector<J1939Frame>{};
        std::tie(requestColl, responseColl) = createReadParameterRequests(3, 32);
        for (int i = 0; i < requestColl.count(); ++i)
        {
            m_router->expectWriteFrame(requestColl[i]);
            if (i != 1)
            {
                m_router->expectReadOwnFrame(requestColl[i]);
                m_router->expectReadFrame(responseColl[i]);
            }
        }

        for (const auto &request : requestColl)
        {
            m_router->writeFrame(request);
        }

        QTRY_COMPARE_WITH_TIMEOUT(m_router->actualCanFrames(), m_router->expectedCanFrames(), 400);
    }
};

QTEST_GUILESS_MAIN(TestWriteBufferOverflow)

#include "test_write_buffer_overflow.moc"
