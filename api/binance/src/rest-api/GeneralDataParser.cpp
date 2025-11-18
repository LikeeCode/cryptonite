#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "enums/Converter.h"
#include "filters/Converter.h"
#include "rest-api/GeneralDataParser.h"

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
        GeneralData::ServerTime serverTimeData{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // Invalid format
        }
        const QJsonObject json = jsonDoc.object();

        // serverTime
        if (!json.contains("serverTime") || !json["serverTime"].isDouble())
        {
            return {}; // serverTime is required
        }
        serverTimeData.serverTime = json["serverTime"].toDouble();
        
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
                const QJsonObject rateLimitObj = rateLimits[i].toObject();
                GeneralData::RateLimit rateLimit{};

                // rateLimitType
                if (!rateLimitObj.contains("rateLimitType") || !rateLimitObj["rateLimitType"].isString())
                {
                    return {}; // rateLimitType is required
                }
                if(!Enum::toRateLimitType(rateLimitObj["rateLimitType"].toString()).has_value())
                {
                    return {}; // Invalid rateLimitType
                }
                rateLimit.rateLimitType = Enum::toRateLimitType(rateLimitObj["rateLimitType"].toString()).value();

                // interval
                if (!rateLimitObj.contains("interval") || !rateLimitObj["interval"].isString())
                {
                    return {}; // interval is required
                }
                rateLimit.interval = rateLimitObj["interval"].toString();

                // intervalNum
                if (!rateLimitObj.contains("intervalNum") || !rateLimitObj["intervalNum"].isDouble())
                {
                    return {}; // intervalNum is required
                }
                rateLimit.intervalNum = rateLimitObj["intervalNum"].toDouble();

                // limit
                if (!rateLimitObj.contains("limit") || !rateLimitObj["limit"].isDouble())
                {
                    return {}; // limit is required
                }
                rateLimit.limit = rateLimitObj["limit"].toDouble();

                exchangeInfo.rateLimits.append(rateLimit);
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

        // symbols
        if (json.contains("symbols") && json["symbols"].isArray())
        {
            QJsonArray symbols = json["symbols"].toArray();
            for (int i = 0; i < symbols.size(); i++)
            {
                if (!symbols[i].isObject())
                {
                    return {}; // Invalid format
                }
                const QJsonObject symbolObj = symbols[i].toObject();
                GeneralData::Symbol symbol{};

                // symbol
                if (!symbolObj.contains("symbol") || !symbolObj["symbol"].isString())
                {
                    return {}; // symbol is required
                }
                symbol.symbol = symbolObj["symbol"].toString();

                // status
                if (!symbolObj.contains("status") || !symbolObj["status"].isString())
                {
                    return {}; // status is required
                }
                if(!Enum::toSymbolStatus(symbolObj["status"].toString()).has_value())
                {
                    return {}; // Invalid status
                }
                symbol.status = Enum::toSymbolStatus(symbolObj["status"].toString()).value();

                // baseAsset
                if (!symbolObj.contains("baseAsset") || !symbolObj["baseAsset"].isString())
                {
                    return {}; // baseAsset is required
                }
                symbol.baseAsset = symbolObj["baseAsset"].toString();

                // baseAssetPrecision
                if (!symbolObj.contains("baseAssetPrecision") || !symbolObj["baseAssetPrecision"].isDouble())
                {
                    return {}; // baseAssetPrecision is required
                }
                symbol.baseAssetPrecision = symbolObj["baseAssetPrecision"].toDouble();

                // quoteAsset
                if (!symbolObj.contains("quoteAsset") || !symbolObj["quoteAsset"].isString())
                {
                    return {}; // quoteAsset is required
                }
                symbol.quoteAsset = symbolObj["quoteAsset"].toString();

                // quotePrecision
                if (!symbolObj.contains("quotePrecision") || !symbolObj["quotePrecision"].isDouble())
                {
                    return {}; // quotePrecision is required
                }
                symbol.quotePrecision = symbolObj["quotePrecision"].toDouble();

                // quoteAssetPrecision
                if (!symbolObj.contains("quoteAssetPrecision") || !symbolObj["quoteAssetPrecision"].isDouble())
                {
                    return {}; // quoteAssetPrecision is required
                }
                symbol.quoteAssetPrecision = symbolObj["quoteAssetPrecision"].toDouble();

                // baseCommissionPrecision
                if (!symbolObj.contains("baseCommissionPrecision") || !symbolObj["baseCommissionPrecision"].isDouble())
                {
                    return {}; // baseCommissionPrecision is required
                }
                symbol.baseCommissionPrecision = symbolObj["baseCommissionPrecision"].toDouble();

                // quoteCommissionPrecision
                if (!symbolObj.contains("quoteCommissionPrecision") || !symbolObj["quoteCommissionPrecision"].isDouble())
                {
                    return {}; // quoteCommissionPrecision is required
                }
                symbol.quoteCommissionPrecision = symbolObj["quoteCommissionPrecision"].toDouble();

                // orderTypes
                if (!symbolObj.contains("orderTypes") || !symbolObj["orderTypes"].isArray())
                {
                    return {}; // orderTypes is required
                }

                QJsonArray orderTypesArray = symbolObj["orderTypes"].toArray();
                QList<OrderType> orderTypes;
                for (int i = 0; i < orderTypesArray.size(); i++)
                {
                    if (!orderTypesArray[i].isString())
                    {
                        return {}; // Invalid format
                    }
                    if(!Enum::toOrderType(orderTypesArray[i].toString()).has_value())
                    {
                        return {}; // Invalid orderType
                    }
                    symbol.orderTypes.append(Enum::toOrderType(orderTypesArray[i].toString()).value());
                }

                // icebergAllowed
                if (!symbolObj.contains("icebergAllowed") || !symbolObj["icebergAllowed"].isBool())
                {
                    return {}; // icebergAllowed is required
                }
                symbol.icebergAllowed = symbolObj["icebergAllowed"].toBool();

                // ocoAllowed
                if (!symbolObj.contains("ocoAllowed") || !symbolObj["ocoAllowed"].isBool())
                {
                    return {}; // ocoAllowed is required
                }
                symbol.ocoAllowed = symbolObj["ocoAllowed"].toBool();

                // otoAllowed
                if (!symbolObj.contains("otoAllowed") || !symbolObj["otoAllowed"].isBool())
                {
                    return {}; // otoAllowed is required
                }
                symbol.otoAllowed = symbolObj["otoAllowed"].toBool();

                // quoteOrderQtyMarketAllowed
                if (!symbolObj.contains("quoteOrderQtyMarketAllowed") || !symbolObj["quoteOrderQtyMarketAllowed"].isBool())
                {
                    return {}; // quoteOrderQtyMarketAllowed is required
                }
                symbol.quoteOrderQtyMarketAllowed = symbolObj["quoteOrderQtyMarketAllowed"].toBool();

                // allowTrailingStop
                if (!symbolObj.contains("allowTrailingStop") || !symbolObj["allowTrailingStop"].isBool())
                {
                    return {}; // allowTrailingStop is required
                }
                symbol.allowTrailingStop = symbolObj["allowTrailingStop"].toBool();

                // cancelReplaceAllowed
                if (!symbolObj.contains("cancelReplaceAllowed") || !symbolObj["cancelReplaceAllowed"].isBool())
                {
                    return {}; // cancelReplaceAllowed is required
                }
                symbol.cancelReplaceAllowed = symbolObj["cancelReplaceAllowed"].toBool();

                // amendAllowed
                if (!symbolObj.contains("amendAllowed") || !symbolObj["amendAllowed"].isBool())
                {
                    return {}; // amendAllowed is required
                }
                symbol.amendAllowed = symbolObj["amendAllowed"].toBool();

                // pegInstructionsAllowed
                if (!symbolObj.contains("pegInstructionsAllowed") || !symbolObj["pegInstructionsAllowed"].isBool())
                {
                    return {}; // pegInstructionsAllowed is required
                }
                symbol.pegInstructionsAllowed = symbolObj["pegInstructionsAllowed"].toBool();

                // isSpotTradingAllowed
                if (!symbolObj.contains("isSpotTradingAllowed") || !symbolObj["isSpotTradingAllowed"].isBool())
                {
                    return {}; // isSpotTradingAllowed is required
                }
                symbol.isSpotTradingAllowed = symbolObj["isSpotTradingAllowed"].toBool();

                // isMarginTradingAllowed
                if (!symbolObj.contains("isMarginTradingAllowed") || !symbolObj["isMarginTradingAllowed"].isBool())
                {
                    return {}; // isMarginTradingAllowed is required
                }
                symbol.isMarginTradingAllowed = symbolObj["isMarginTradingAllowed"].toBool();

                // filters
                if (!symbolObj.contains("filters") || !symbolObj["filters"].isArray())
                {
                    return {}; // filters is required
                }

                QJsonArray filtersArray = symbolObj["filters"].toArray();
                for (int i = 0; i < filtersArray.size(); i++)
                {
                    if (!filtersArray[i].isObject())
                    {
                        return {}; // Invalid format
                    }
                    const QJsonObject filterObj = filtersArray[i].toObject();
                    auto symbolFilter = Filter::fromJsonObject(filterObj);
                    if (symbolFilter->filterType.isEmpty())
                    {
                        return {}; // Invalid filter
                    }
                    symbol.filters.append(symbolFilter);
                }

                // permissions
                if (!symbolObj.contains("permissions") || !symbolObj["permissions"].isArray())
                {
                    return {}; // permissions is required
                }

                QJsonArray permissionsArray = symbolObj["permissions"].toArray();
                QList<AccountAndSymbolPermissions> permissions;
                for (int i = 0; i < permissionsArray.size(); i++)
                {
                    if (!permissionsArray[i].isString())
                    {
                        return {}; // Invalid format
                    }
                    if (!Enum::toAccountAndSymbolPermissions(permissionsArray[i].toString()).has_value())
                    {
                        return {}; // Invalid orderType
                    }
                    symbol.permissions.append(Enum::toAccountAndSymbolPermissions(permissionsArray[i].toString()).value());
                }

                // permissionSets
                if (!symbolObj.contains("permissionSets") || !symbolObj["permissionSets"].isArray())
                {
                    return {}; // permissionSets are required
                }

                QJsonArray permissionSets = symbolObj["permissionSets"].toArray();
                for (int i = 0; i < permissionSets.size(); i++)
                {
                    if (!permissionSets[i].isArray())
                    {
                        return {}; // Invalid format
                    }

                    QJsonArray permissionSetsArray = permissionSets[i].toArray();
                    for (int j = 0; j < permissionSetsArray.size(); j++)
                    {
                        if (!permissionSetsArray[j].isString())
                        {
                            return {}; // Invalid format
                        }
                        if (!Enum::toAccountAndSymbolPermissions(permissionSetsArray[j].toString()).has_value())
                        {
                            return {}; // Invalid orderType
                        }
                        symbol.permissionSets.append(Enum::toAccountAndSymbolPermissions(permissionSetsArray[j].toString()).value());
                    }
                }

                // defaultSelfTradePreventionMode
                if (!symbolObj.contains("defaultSelfTradePreventionMode") || !symbolObj["defaultSelfTradePreventionMode"].isString())
                {
                    return {}; // defaultSelfTradePreventionMode is required
                }
                symbol.defaultSelfTradePreventionMode = symbolObj["defaultSelfTradePreventionMode"].toString();

                // permissionSets
                if (!symbolObj.contains("permissionSets") || !symbolObj["permissionSets"].isArray())
                {
                    return {}; // permissionSets are required
                }

                // allowedSelfTradePreventionModes
                QJsonArray allowedSelfTradePreventionModesArray = symbolObj["allowedSelfTradePreventionModes"].toArray();
                QList<AccountAndSymbolPermissions> allowedSelfTradePreventionModes;
                for (int i = 0; i < allowedSelfTradePreventionModesArray.size(); i++)
                {
                    if (!allowedSelfTradePreventionModesArray[i].isString())
                    {
                        return {}; // Invalid format
                    }
                    if (!Enum::toAccountAndSymbolPermissions(allowedSelfTradePreventionModesArray[i].toString()).has_value())
                    {
                        return {}; // Invalid orderType
                    }
                    symbol.allowedSelfTradePreventionModes.append(Enum::toSelfTradePreventionMode(allowedSelfTradePreventionModesArray[i].toString()).value());
                }

                exchangeInfo.symbols.append(symbol);
            }
        }
        else
        {
            return {}; // symbols are required
        }

        return exchangeInfo;
    }
} // namespace Binance
