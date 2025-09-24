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
        static std::optional<GeneralData::Ping> parsePing(const QJsonDocument &doc);

        // Check server time
        static std::optional<GeneralData::ServerTime> parseServerTime(const QJsonDocument &doc);
    };
} // namespace Binance
