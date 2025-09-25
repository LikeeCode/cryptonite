#pragma once

#include <optional>

#include <QJsonDocument>

#include "GeneralData.h"

namespace Binance
{
    class GeneralDataParser
    {
    public:
        // Test connectivity
        static std::optional<GeneralData::Ping> parsePing(const QJsonDocument &jsonDoc);

        // Check server time
        static std::optional<GeneralData::ServerTime> parseServerTime(const QJsonDocument &jsonDoc);

        // Exchange information
        static std::optional<GeneralData::ExchangeInfo> parseExchangeInfo(const QJsonDocument &jsonDoc);
    };
} // namespace Binance
