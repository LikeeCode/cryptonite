#pragma once

#include <QObject>

#include "../http/BinanceHttpClient.h"
#include "../data/MarketData.h"

namespace Binance
{
    class BinanceMarketDataRepository : public QObject
    {
        Q_OBJECT
    public:
        explicit BinanceMarketDataRepository(BinanceHttpClient *client, QObject *parent = nullptr);

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

    signals:
        void orderBookReady(const MarketData::OrderBook &data);
        void recentTradesReady(const QList<MarketData::Trade> &data);
        void historicalTradesReady(const QList<MarketData::Trade> &data);
        void aggregatedTradesReady(const QList<MarketData::AggregatedTrade> &data);
        void klinesReady(const QList<MarketData::Kline> &data);
        void uiKlinesReady(const QList<MarketData::UIKline> &data);
        void currentAveragePriceReady(const MarketData::CurrentAveragePrice &data);
        void tickerPrice24hrFullReady(const QList<MarketData::Ticker24hrFull> &data);
        void tickerPrice24hrMiniReady(const QList<MarketData::Ticker24hrMini> &data);
        void tradingDayFullReady(const QList<MarketData::TradingDayFull> &data);
        void tradingDayMiniReady(const QList<MarketData::TradingDayMini> &data);
        void symbolPriceTickerReady(const QList<MarketData::SymbolPriceTicker> &data);
        void symbolOrderBookTickerReady(const QList<MarketData::SymbolOrderBookTicker> &data);
        void rollingWindowTickerFullReady(const QList<MarketData::TickerFull> &data);
        void rollingWindowTickerMiniReady(const QList<MarketData::TickerMini> &data);
        void error(const QString &message);

    private:
        BinanceHttpClient *m_client;
    };
} // namespace Binance
