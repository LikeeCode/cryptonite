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
    };
} // namespace Binance
