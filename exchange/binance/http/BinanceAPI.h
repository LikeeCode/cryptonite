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

        // Market Data endpoints
        void orderBook(const Binance::MarketData::OrderBookRequest &request);
        void recentTrades(const Binance::MarketData::RecentTradesRequest &request);
        void historicalTrades(const Binance::MarketData::OldTradesRequest &request);
        void aggregatedTrades(const Binance::MarketData::AggregatedTradeRequest &request);
        void klines(const Binance::MarketData::KlineRequest &request);
        void uiKlines(const Binance::MarketData::UIKlineRequest &request);
        void currentAveragePrice(const Binance::MarketData::CurrentAveragePriceRequest &request);
        void tickerPrice24hr(const Binance::MarketData::Ticker24hrRequest &request);
        void tradingDay(const Binance::MarketData::TradingDayRequest &request);
        void symbolPriceTicker(const Binance::MarketData::SymbolPriceTickerRequest &request);
        void symbolOrderBookTicker(const Binance::MarketData::SymbolOrderBookTickerRequest &request);
        void rollingWindowTicker(const Binance::MarketData::TickerRequest &request);

    private:
        void getApiKeys();
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
        void apiKeysFileError();
        void apiError(const QString &error);

        void pingResponse(const QJsonDocument &data);
        void timeResponse(const QJsonDocument &data);
        void exchangeInfoResponse(const QJsonDocument &data);

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
