#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>


#include "enums/Converter.h"
#include "filters/TypeConverter.h"
#include "GeneralDataParser.h"

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
        if (json.contains("rateLimits") && json["rateLimits"].isArray())
        {
            QJsonArray rateLimits = json["rateLimits"].toArray();
            for (int i = 0; i < rateLimits.size(); i++)
            {
                if (!rateLimits[i].isObject())
                {
                    return {}; // Invalid format
                }
                const QJsonObject rateLimit = rateLimits[i].toObject();

                // rateLimitType
                if (!rateLimit.contains("rateLimitType") || !rateLimit["rateLimitType"].isString())
                {
                    return {}; // rateLimitType is required
                }
                GeneralData::RateLimit limit{};
                limit.rateLimitType = Enum::toRateLimitType(rateLimit["rateLimitType"].toString()).value();

                // interval
                if (!rateLimit.contains("interval") || !rateLimit["interval"].isString())
                {
                    return {}; // interval is required
                }
                limit.interval = rateLimit["interval"].toString();

                // intervalNum
                if (!rateLimit.contains("intervalNum") || !rateLimit["intervalNum"].isDouble())
                {
                    return {}; // intervalNum is required
                }
                limit.intervalNum = rateLimit["intervalNum"].toDouble();

                // limit
                if (!rateLimit.contains("limit") || !rateLimit["limit"].isDouble())
                {
                    return {}; // limit is required
                }
                limit.limit = rateLimit["limit"].toDouble();

                exchangeInfo.rateLimits.append(limit);
            }
        }
        else{
            return {}; // rateLimits are required
        }

        // exchangeFilters
        if (!json.contains("exchangeFilters") || !json["exchangeFilters"].isArray())
        {
            return {}; // exchangeFilters are required
        }

        return exchangeInfo;
    }
} // namespace Binance
