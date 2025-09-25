#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "GeneralDataParser.h"
#include "filters/TypeConverter.h"

namespace Binance
{
    std::optional<GeneralData::Ping> GeneralDataParser::parsePing(const QJsonDocument &jsonDoc)
    {
        // 1. Check if the document is a valid JSON object
        if (!jsonDoc.isObject())
        {
            return {}; // Invalid format
        }

        return GeneralData::Ping{};
    }

    std::optional<GeneralData::ServerTime> GeneralDataParser::parseServerTime(const QJsonDocument &jsonDoc)
    {
        // 1. Check if the document is a valid JSON object
        if (!jsonDoc.isObject())
        {
            return {}; // Invalid format
        }

        QJsonObject json = jsonDoc.object();
        const QJsonValue serverTimeValue = json.value("serverTime");

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

    std::optional<GeneralData::ExchangeInfo> GeneralDataParser::parseExchangeInfo(const QJsonDocument &jsonDoc)
    {
        GeneralData::ExchangeInfo exchangeInfo{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // Invalid format
        }
        const QJsonObject json = jsonDoc.object();

        // timezone
        if (!json.contains("timezone") || !json["timezone"].isString())
        {
            return {}; // timezone is required
        }
        exchangeInfo.timezone = json["timezone"].toString();

        // serverTime
        if (!json.contains("serverTime") || !json["serverTime"].isDouble())
        {
            return {}; // timezone is required
        }
        exchangeInfo.serverTime = json["serverTime"].toDouble();

        // rateLimits
        // const QJsonValue rateLimits = json.value("rateLimits");
        // if (rateLimits.isUndefined() || !rateLimits.isArray())
        // {
        //     return {}; // rateLimits are required
        // }
        // QJsonArray rateLimits = json["rateLimits"].toArray();

        // exchangeFilters
        if (json.contains("exchangeFilters") && json["exchangeFilters"].isArray())
        {
            QJsonArray exchangeFilters = json["exchangeFilters"].toArray();
            for (int i = 0; i < exchangeFilters.size(); i++)
            {
                if (exchangeFilters[i].isString())
                {
                    auto exchangeFilter = exchangeFilters[i].toString();
                    auto exchangeFilterType = Filter::toFilterType(exchangeFilter);
                    if(exchangeFilterType.has_value())
                    {
                        exchangeInfo.exchangeFilters.append(exchangeFilterType.value());
                    }
                }
            }
        }

        return exchangeInfo;
    }
} // namespace Binance
