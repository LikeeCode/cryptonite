#pragma once

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QVariantMap>

#include "rest-api/APIEndpoints.h"
#include "rest-api/GeneralData.h"
#include "rest-api/MarketData.h"
#include "../../../RequestType.h"

namespace Binance
{
    class BinanceAPI : public QObject
    {
        Q_OBJECT
    public:
        explicit BinanceAPI(QObject *parent = nullptr, bool useTestNetwork = true);
        ~BinanceAPI();

        void setApiKeys(const QString &key, const QString &secret);

        // General endpoints
        void ping();
        void time();
        void exchangeInfo();
        void exchangeInfo(const Binance::GeneralData::ExchangeInfoRequest &request);

        void orderBook(const Binance::MarketData::OrderBookRequest &request);
        void recentTrades(const Binance::MarketData::RecentTradesRequest &request);
        void historicalTrades(const Binance::MarketData::OldTradesRequest &request);
        void aggregatedTrades(const Binance::MarketData::AggregatedTradeRequest &request);

        void klines(const Binance::MarketData::KlineRequest &request);
        void currentAveragePrice(const Binance::MarketData::CurrentAveragePriceRequest &request);

    private:
        void getApiKeys();
        void sendPublicRequest(const QString &endpoint, const QVariantMap &params = {}, RequestType type = RequestType::Get);
        void sendSignedRequest(const QString &endpoint, const QVariantMap &params, RequestType type);
        
        bool m_useTestNetwork;
        QString m_baseUrl;
        QString m_apiKey;
        QString m_apiSecret;
        QNetworkAccessManager* m_networkManager;

    private slots:
        void onReplyFinished(QNetworkReply *reply);

    signals:
        void apiKeysFileError();
        void apiError(const QString &error);

        void pingResponse(const QJsonDocument &data);
        void timeResponse(const QJsonDocument &data);
        void exchangeInfoResponse(const QJsonDocument &data);

        void orderBookResponse(const QJsonDocument &data);
        void tradesResponse(const QJsonDocument &data);
        void aggTradesResponse(const QJsonDocument &data);

        void klinesResponse(const QJsonDocument &data);
        void currentAveragePriceResponse(const QJsonDocument &data);
    };
} // namespace Binance
