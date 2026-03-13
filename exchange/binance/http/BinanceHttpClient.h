#pragma once

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QVariantMap>

#include "../data/APIEndpoints.h"
#include "../data/GeneralData.h"
#include "../data/MarketData.h"
#include "../data/Enums.h"

namespace Binance
{
    class BinanceHttpClient : public QObject
    {
        Q_OBJECT
    public:
        explicit BinanceHttpClient(QObject *parent = nullptr, const QString& apiKey = "", const QString& apiSecret = "", bool useTestNetwork = true);
        ~BinanceHttpClient();

        // General data endpoints
        void ping();
        void time();
        void exchangeInfo();
        void exchangeInfo(const GeneralData::ExchangeInfoRequest &request);

        // Market data endpoints
        void orderBook(const MarketData::OrderBookRequest &request);
        void recentTrades(const MarketData::RecentTradesRequest &request);
        void historicalTrades(const MarketData::OldTradesRequest &request);
        void aggregatedTrades(const MarketData::AggregatedTradeRequest &request);
        void klines(const MarketData::KlineRequest &request);
        void uiKlines(const MarketData::UIKlineRequest &request);
        void currentAveragePrice(const MarketData::CurrentAveragePriceRequest &request);
        void tickerPrice24hr(const MarketData::Ticker24hrRequest &request);
        void tradingDay(const MarketData::TradingDayRequest &request);
        void symbolPriceTicker(const MarketData::SymbolPriceTickerRequest &request);
        void symbolOrderBookTicker(const MarketData::SymbolOrderBookTickerRequest &request);
        void rollingWindowTicker(const MarketData::TickerRequest &request);

    private:
        QNetworkReply* sendPublicRequest(const QString &endpoint, const QVariantMap &params = {}, RequestType type = RequestType::Get);
        QNetworkReply* sendSignedRequest(const QString &endpoint, const QVariantMap &params, RequestType type);

        bool m_useTestNetwork;
        QString m_baseUrl;
        QString m_apiKey;
        QString m_apiSecret;
        std::unique_ptr<QNetworkAccessManager> m_networkManager;

    private slots:
        void onReplyFinished(QNetworkReply *reply);

    signals:
        void apiError(const QString &error);

        // General signals — raw JSON, no parsing
        void pingResponse(const QJsonDocument &data);
        void timeResponse(const QJsonDocument &data);
        void exchangeInfoResponse(const QJsonDocument &data);

        // Market data signals — raw JSON, no parsing
        void orderBookResponse(const QJsonDocument &data);
        void recentTradesResponse(const QJsonDocument &data);
        void historicalTradesResponse(const QJsonDocument &data);
        void aggTradesResponse(const QJsonDocument &data);
        void klinesResponse(const QJsonDocument &data);
        void uiKlinesResponse(const QJsonDocument &data);
        void currentAveragePriceResponse(const QJsonDocument &data);
        void tickerPrice24hrResponseFull(const QJsonDocument &data);
        void tickerPrice24hrResponseMini(const QJsonDocument &data);
        void tradingDayResponseFull(const QJsonDocument &data);
        void tradingDayResponseMini(const QJsonDocument &data);
        void symbolPriceTickerResponse(const QJsonDocument &data);
        void symbolOrderBookTickerResponse(const QJsonDocument &data);
        void rollingWindowTickerResponseFull(const QJsonDocument &data);
        void rollingWindowTickerResponseMini(const QJsonDocument &data);
    };
} // namespace Binance
