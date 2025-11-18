#pragma once

#include <optional>

#include <QJsonDocument>

#include "MarketData.h"

namespace Binance
{
    class MarketDataParser
    {
    public:
        // Order Book
        static std::optional<MarketData::OrderBook> parseOrderBook(const QJsonDocument &jsonDoc);
    };
} // namespace Binance
