#pragma once

#include <optional>

#include <QJsonDocument>

#include "MarketData.h"

namespace Binance
{
    class MarketDataParser
    {
    public:
        static std::optional<MarketData::OrderBook> parseOrderBook(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::Trade>> parseTrades(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::AggregatedTrade>> parseAggregatedTrades(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::Kline>> parseKlines(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::UIKline>> parseUIKlines(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::CurrentAveragePrice> parseCurrentAveragePrice(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::Ticker24hrFull> parseTicker24hrFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::Ticker24hrMini> parseTicker24hrMini(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TradingDayFull> parseTradingDayFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TradingDayMini> parseTradingDayMini(const QJsonDocument &jsonDoc);
    };
} // namespace Binance
