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

        QJsonObject jsonObj = jsonDoc.object();
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

    std::optional<GeneralData::ExchangeInfo> GeneralDataParser::parseExchangeInfo(const QJsonDocument &jsonDoc)
    {
        std::optional<GeneralData::ExchangeInfo> exchangeInfo{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // Invalid format
        }
        const QJsonObject json = jsonDoc.object();

        // timezone
        if (json.contains("timezone") && json["timezone"].isString())
        {
            exchangeInfo.value().timezone = json["timezone"].toString();
        }
        else{
            return {}; // timezone is required
        }

        // serverTime
        if (json.contains("serverTime") && json["serverTime"].isDouble())
        {
            exchangeInfo.value().serverTime = json["serverTime"].toDouble();
        }
        else{
            return {}; // serverTime is required
        }

        // rateLimits
        if (json.contains("rateLimits") && json["rateLimits"].isArray())
        {
            QJsonArray rateLimits = json["rateLimits"].toArray();

            for (int i = 0; i < rateLimits.size(); i++){
                QJsonObject rateLimitJson = rateLimits[i].toObject();
                // auto rateLimitType = Binance::toRateLimitType(rateLimitJson.value("rateLimitType").toString()).value();
                // exchangeInfo.value().rateLimits.append(rateLimitType);
            }
        }

        // filters
        if (json.contains("exchangeFilters") && json["exchangeFilters"].isArray())
        {
            QJsonArray exchangeFilters = json["exchangeFilters"].toArray();

            for (int i = 0; i < exchangeFilters.size(); i++)
            {
                QJsonObject exchangeFilterJson = exchangeFilters[i].toObject();
                auto filterType = Binance::Filter::toFilterType(exchangeFilterJson.value("filterType").toString()).value();
                exchangeInfo.value().exchangeFilters.append(filterType);
            }
        }

        // rateLimits
        // if (json.contains("rateLimits") && json["rateLimits"].isArray())
        // {
        //     QJsonArray rateLimits = json["rateLimits"].toArray();
        //     for (int i = 0; i < rateLimits.size(); i++)
        //     {
        //         QJsonObject rateLimit = rateLimits[i].toObject();

        //         RateLimitType rateLimit;
        //         rateLimit.read(rateLimitJson);

        //         rateLimits.append(rateLimit);
        //     }
        // }

        // // Parse rate limits
        // if (json.contains("rateLimits") && json["rateLimits"].isArray()){

        // }
        //     QJsonArray rateLimitsArray = rateLimitsValue.toArray();
        // for (const QJsonValue &rateLimitVal : rateLimitsArray)
        // {
        //     if (!rateLimitVal.isObject()) continue;
        //     QJsonObject rateLimitObj = rateLimitVal.toObject();

        //     GeneralData::RateLimit rateLimit{};
        //     rateLimit.rateLimitType = rateLimitObj.value("rateLimitType").toString();
        //     rateLimit.interval = rateLimitObj.value("interval").toString();
        //     rateLimit.intervalNum = rateLimitObj.value("intervalNum").toInt();
        //     rateLimit.limit = rateLimitObj.value("limit").toInt();

        //     exchangeInfoData.rateLimits.push_back(rateLimit);
        // }

        

        return exchangeInfo;
    }
} // namespace Binance
