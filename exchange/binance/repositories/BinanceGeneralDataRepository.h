#pragma once

#include <QObject>

#include "../http/BinanceHttpClient.h"
#include "../data/GeneralData.h"

namespace Binance
{
    class BinanceGeneralDataRepository : public QObject
    {
        Q_OBJECT
    public:
        explicit BinanceGeneralDataRepository(BinanceHttpClient *client, QObject *parent = nullptr);

        void ping();
        void time();
        void exchangeInfo();
        void exchangeInfo(const GeneralData::ExchangeInfoRequest &request);

    signals:
        void pingReady(const GeneralData::Ping &data);
        void serverTimeReady(const GeneralData::ServerTime &data);
        void exchangeInfoReady(const GeneralData::ExchangeInfo &data);
        void error(const QString &message);

    private:
        BinanceHttpClient *m_client;
    };
} // namespace Binance
