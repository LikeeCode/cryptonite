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

    std::optional<GeneralData::ExchangeInfo> GeneralDataParser::parseExchangeInfo(const QJsonDocument &doc)
    {
        // 1. Check if the document is a valid JSON object
        if (!doc.isObject())
        {
            return {}; // Invalid format
        }

        QJsonObject jsonObj = doc.object();
        const QJsonValue timezoneValue = jsonObj.value("timezone");
        const QJsonValue serverTimeValue = jsonObj.value("serverTime");
        const QJsonValue rateLimitsValue = jsonObj.value("rateLimits");
        const QJsonValue exchangeFiltersValue = jsonObj.value("exchangeFilters");
        const QJsonValue symbolsValue = jsonObj.value("symbols");

        // 2. Check if the required keys exist and are the correct types
        if (timezoneValue.isUndefined() || !timezoneValue.isString() ||
            serverTimeValue.isUndefined() || !serverTimeValue.isDouble() ||
            rateLimitsValue.isUndefined() || !rateLimitsValue.isArray() ||
            exchangeFiltersValue.isUndefined() || !exchangeFiltersValue.isArray() ||
            symbolsValue.isUndefined() || !symbolsValue.isArray())
        {
            return {}; // One or more keys are missing or have the wrong type
        }

        // Parse rate limits
        // QJsonArray rateLimitsArray = rateLimitsValue.toArray();
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

        // // Parse exchange filters
        // QJsonArray exchangeFiltersArray = exchangeFiltersValue.toArray();
        // for (const QJsonValue &filterVal : exchangeFiltersArray)
        // {
        //     if (!filterVal.isObject()) continue;
        //     QJsonObject filterObj = filterVal.toObject();

        //     GeneralData::Filter filter{};
        //     filter.filterType = filterObj.value("filterType").toString();
        // }

        // 3. If all checks pass, construct and return the object
        GeneralData::ExchangeInfo exchangeInfoData{};
        exchangeInfoData.timezone = timezoneValue.toString();
        exchangeInfoData.serverTime = serverTimeValue.toVariant().toLongLong();

        return exchangeInfoData;
    }
} // namespace Binance
