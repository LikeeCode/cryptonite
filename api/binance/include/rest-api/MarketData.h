#pragma once

#include <QList>
#include <QString>
#include <QVariant>

#include "enums/Enums.h"
#include "enums/Converter.h"
#include "filters/Filters.h"

namespace Binance::MarketData{
    struct OrderBookRequest{
        QString symbol;
        int limit{100}; // Optional, default 100; max 5000
        SymbolStatus status{ SymbolStatus::TRADING };

        QVariantMap toVariantMap() const {
            QVariantMap params;

            params.insert("symbol", symbol);
            if(limit != 100 && limit > 0 && limit <= 5000){
                params.insert("limit", limit);
            }
            if(status != SymbolStatus::TRADING){
                params.insert("status", Binance::Enum::toString(status));
            }
            
            return params;
        }
    };

    struct OrderBook{
        qint64 lastUpdateId{};
        QList<QPair<double, double>> bids; // price, quantity
        QList<QPair<double, double>> asks; // price, quantity
    };

    struct RecentTradesRequest{
        QString symbol;
        int limit{}; // Optional, default 500; max 1000
    };

    struct Trade{
        qint64 id{};
        double price{};
        double qty{};
        double quoteQty{};
        qint64 time{};
        bool isBuyerMaker{};
        bool isBestMatch{};
    };

    struct OldTradesRequest{
        QString symbol;
        int limit{}; // Optional, default 500; max 1000
        qint64 fromId{}; // Trade id to fetch from. Default gets most recent trades.
    };

    struct AggregatedTradeRequest{
        QString symbol;
        qint64 fromId{}; // Optional, id to get aggregate trades from INCLUSIVE.
        qint64 startTime{}; // Optional, timestamp in ms to get aggregate trades from INCLUSIVE.
        qint64 endTime{}; // Optional, timestamp in ms to get aggregate trades until INCLUSIVE.
        int limit{}; // Optional, default 500; max 1000
    };

    struct AggregatedTrade{
        qint64 a{}; // Aggregate tradeId
        double p{}; // Price
        double q{}; // Quantity
        qint64 f{}; // First tradeId
        qint64 l{}; // Last tradeId
        qint64 T{}; // Timestamp
        bool m{}; // Was the buyer the maker?
        bool M{}; // Was the trade the best price match?
    };

    struct KlineRequest{
        QString symbol;
        Interval interval;
        qint64 startTime{}; // Optional, timestamp in ms to get candlesticks from INCLUSIVE.
        qint64 endTime{}; // Optional, timestamp in ms to get candlesticks until INCLUSIVE.
        QString timeZone; // Optional, default 0 UTC
        int limit{}; // Optional, default 500; max 1000
    };

    struct Kline{
        qint64 openTime{};
        double open{};
        double high{};
        double low{};
        double close{};
        double volume{};
        qint64 closeTime{};
        double quoteAssetVolume{};
        int numberOfTrades{};
        double takerBuyBaseAssetVolume{};
        double takerBuyQuoteAssetVolume{};
        double ignore{};
    };

    struct UIKlineRequest{
        QString symbol;
        Interval interval;
        qint64 startTime{}; // Optional, timestamp in ms to get candlesticks from INCLUSIVE.
        qint64 endTime{}; // Optional, timestamp in ms to get candlesticks until INCLUSIVE.
        QString timeZone; // Optional, default 0 UTC
        int limit{}; // Optional, default 500; max 1000
    };

    struct UIKline{
        qint64 openTime{};
        double open{};
        double high{};
        double low{};
        double close{};
        double volume{};
        qint64 closeTime{};
        double quoteAssetVolume{};
        int numberOfTrades{};
        double takerBuyBaseAssetVolume{};
        double takerBuyQuoteAssetVolume{};
        double ignore{};
    };

    struct CurrentAveragePriceRequest{
        QString symbol;
    };

    struct CurrentAveragePrice{
        int interval{};
        double price{};
        qint64 mins{};
    };

    struct ticker24hrRequest{
        QString symbol;
        QList<QString> symbols;
        ResponseType type{ ResponseType::FULL };
        SymbolStatus status{ SymbolStatus::TRADING };
    };

    struct ticker24hr{
        QString symbol;
        double priceChange{};
        double priceChangePercent{};
        double weightedAvgPrice{};
        double prevClosePrice{};
        double lastPrice{};
        double lastQty{};
        double bidPrice{};
        double bidQty{};
        double askPrice{};
        double askQty{};
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        int firstId{};   // First tradeId
        int lastId{};    // Last tradeId
        int count{};     // Trade count
    };

    struct ticker24hrMini{
        QString symbol;
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        int firstId{};   // First tradeId
        int lastId{};    // Last tradeId
        int count{};     // Trade count
    };

    struct TradingDayRequest{
        QString symbol;
        qint64 startTime{}; // Optional, timestamp in ms to get data from INCLUSIVE.
        ResponseType type{ ResponseType::FULL };
        SymbolStatus status{ SymbolStatus::TRADING };
    };

    struct TradingDay{
        QString symbol;
        double priceChange{};
        double priceChangePercent{};
        double weightedAvgPrice{};
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        int firstId{};   // First tradeId
        int lastId{};    // Last tradeId
        int count{};     // Trade count
    };

    struct TradingDayMini{
        QString symbol;
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        int firstId{};   // First tradeId
        int lastId{};    // Last tradeId
        int count{};     // Trade count
    };

    struct SymbolPriceTickerRequest{
        QString symbol;
        SymbolStatus status{ SymbolStatus::TRADING };
    };

    struct SymbolPriceTicker{
        QString symbol;
        double price{};
    };

    struct SymbolOrderBookTickerRequest{
        QString symbol;
        SymbolStatus status{ SymbolStatus::TRADING };
    };

    struct SymbolOrderBookTicker{
        QString symbol;
        double bidPrice{};
        double bidQty{};
        double askPrice{};
        double askQty{};
    };

    struct TickerRequest{
        QString symbol;
        QString windowSize; // e.g., "1m", "5m", "1h", "1d"
        ResponseType type{ ResponseType::FULL };
        SymbolStatus status{ SymbolStatus::TRADING };
    };

    struct Ticker{
        QString symbol;
        double priceChange{};
        double priceChangePercent{};
        double weightedAvgPrice{};
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        int firstId{};
        int lastId{};
        int count{};
    };

    struct TickerMini{
        QString symbol;
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        int firstId{};
        int lastId{};
        int count{};
    };
}
