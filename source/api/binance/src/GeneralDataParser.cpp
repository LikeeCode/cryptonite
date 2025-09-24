#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "GeneralDataParser.h"

namespace Binance
{
    std::optional<GeneralData::Ping> GeneralDataParser::parsePing(const QJsonDocument& doc)
    {
        // 1. Check if the document is a valid JSON object
        if (!doc.isObject())
        {
            return {}; // Invalid format
        }

        return GeneralData::Ping{};
    }

    std::optional<GeneralData::ServerTime> GeneralDataParser::parseServerTime(const QJsonDocument& doc)
    {
        // 1. Check if the document is a valid JSON object
        if (!doc.isObject())
        {
            return {}; // Invalid format
        }

        QJsonObject jsonObj = doc.object();
        const QJsonValue serverTimeValue = jsonObj.value("serverTime");

        // 2. Check if the required key exists and is the correct type (a number)
        if (serverTimeValue.isUndefined() || !serverTimeValue.isDouble())
        {
            return {}; // Key is missing or has the wrong type
        }

        // 3. If all checks pass, construct and return the object
        GeneralData::ServerTime serverTimeData{};
        serverTimeData.serverTime = serverTimeValue.toVariant().toLongLong();
        
        return serverTimeData;
    }
} // namespace Binance
