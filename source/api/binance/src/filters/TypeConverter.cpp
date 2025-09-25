#pragma once

#include <QHash>
#include <QJsonObject>
#include <QString>

#include "filters/TypeConverter.h"

namespace Binance::Filter
{
    QString toString(Type type)
    {
        static const QMap<Type, QString> filterTypeMap = {
            {Type::PRICE_FILTER, "PRICE_FILTER"},
            {Type::PERCENT_PRICE, "PERCENT_PRICE"},
            {Type::PERCENT_PRICE_BY_SIDE, "PERCENT_PRICE_BY_SIDE"},
            {Type::LOT_SIZE, "LOT_SIZE"},
            {Type::MIN_NOTIONAL, "MIN_NOTIONAL"},
            {Type::NOTIONAL, "NOTIONAL"},
            {Type::ICEBERG_PARTS, "ICEBERG_PARTS"},
            {Type::MARKET_LOT_SIZE, "MARKET_LOT_SIZE"},
            {Type::MAX_NUM_ORDERS, "MAX_NUM_ORDERS"},
            {Type::MAX_NUM_ALGO_ORDERS, "MAX_NUM_ALGO_ORDERS"},
            {Type::MAX_NUM_ICEBERG_ORDERS, "MAX_NUM_ICEBERG_ORDERS"},
            {Type::MAX_POSITION, "MAX_POSITION"},
            {Type::TRAILING_DELTA, "TRAILING_DELTA"},
            {Type::MAX_NUM_ORDER_AMENDS, "MAX_NUM_ORDER_AMENDS"},
            {Type::MAX_NUM_ORDER_LISTS, "MAX_NUM_ORDER_LISTS"},
            {Type::EXCHANGE_MAX_NUM_ORDERS, "EXCHANGE_MAX_NUM_ORDERS"},
            {Type::EXCHANGE_MAX_NUM_ALGO_ORDERS, "EXCHANGE_MAX_NUM_ALGO_ORDERS"},
            {Type::EXCHANGE_MAX_NUM_ICEBERG_ORDERS, "EXCHANGE_MAX_NUM_ICEBERG_ORDERS"},
            {Type::EXCHANGE_MAX_NUM_ORDER_LISTS, "EXCHANGE_MAX_NUM_ORDER_LISTS"}};

        return filterTypeMap.value(type);
    }

    std::optional<Type> toFilterType(const QString &type)
    {
        static const QMap<QString, Type> filterTypeMap = {
            {"PRICE_FILTER", Type::PRICE_FILTER},
            {"PERCENT_PRICE", Type::PERCENT_PRICE},
            {"PERCENT_PRICE_BY_SIDE", Type::PERCENT_PRICE_BY_SIDE},
            {"LOT_SIZE", Type::LOT_SIZE},
            {"MIN_NOTIONAL", Type::MIN_NOTIONAL},
            {"NOTIONAL", Type::NOTIONAL},
            {"ICEBERG_PARTS", Type::ICEBERG_PARTS},
            {"MARKET_LOT_SIZE", Type::MARKET_LOT_SIZE},
            {"MAX_NUM_ORDERS", Type::MAX_NUM_ORDERS},
            {"MAX_NUM_ALGO_ORDERS", Type::MAX_NUM_ALGO_ORDERS},
            {"MAX_NUM_ICEBERG_ORDERS", Type::MAX_NUM_ICEBERG_ORDERS},
            {"MAX_POSITION", Type::MAX_POSITION},
            {"TRAILING_DELTA", Type::TRAILING_DELTA},
            {"MAX_NUM_ORDER_AMENDS", Type::MAX_NUM_ORDER_AMENDS},
            {"MAX_NUM_ORDER_LISTS", Type::MAX_NUM_ORDER_LISTS},
            {"EXCHANGE_MAX_NUM_ORDERS", Type::EXCHANGE_MAX_NUM_ORDERS},
            {"EXCHANGE_MAX_NUM_ALGO_ORDERS", Type::EXCHANGE_MAX_NUM_ALGO_ORDERS},
            {"EXCHANGE_MAX_NUM_ICEBERG_ORDERS", Type::EXCHANGE_MAX_NUM_ICEBERG_ORDERS},
            {"EXCHANGE_MAX_NUM_ORDER_LISTS", Type::EXCHANGE_MAX_NUM_ORDER_LISTS}};

        return filterTypeMap.value(type, {});
    }

    std::shared_ptr<BinanceFilter> fromJsonObject(const QJsonObject &jsonObj)
    {
        if (!jsonObj.contains("filterType") || !jsonObj["filterType"].isString())
        {
            return {}; // filterType is required
        }

        auto filterType = Filter::toFilterType(jsonObj["filterType"].toString());
        if (!filterType.has_value())
        {
            return {}; // Invalid filterType
        }

        switch (filterType.value())
        {
        // Symbol filters
        case Type::PRICE_FILTER:
        {
            auto filter = std::make_shared<PriceFilter>();
            if (!jsonObj.contains("minPrice") || !jsonObj["minPrice"].isString())
            {
                return {}; // minPrice is required
            }
            filter->minPrice = jsonObj["minPrice"].toString().toDouble();
            if (!jsonObj.contains("maxPrice") || !jsonObj["maxPrice"].isString())
            {
                return {}; // maxPrice is required
            }
            filter->maxPrice = jsonObj["maxPrice"].toString().toDouble();
            if (!jsonObj.contains("tickSize") || !jsonObj["tickSize"].isString())
            {
                return {}; // tickSize is required
            }
            filter->tickSize = jsonObj["tickSize"].toString().toDouble();
            return filter;
        }
        case Type::PERCENT_PRICE:
        {
            auto filter = std::make_shared<PercentPriceFilter>();
            if (!jsonObj.contains("multiplierUp") || !jsonObj["multiplierUp"].isString())
            {
                return {}; // multiplierUp is required
            }
            filter->multiplierUp = jsonObj["multiplierUp"].toString().toDouble();
            if (!jsonObj.contains("multiplierDown") || !jsonObj["multiplierDown"].isString())
            {
                return {}; // multiplierDown is required
            }
            filter->multiplierDown = jsonObj["multiplierDown"].toString().toDouble();
            if (!jsonObj.contains("avgPriceMins") || !jsonObj["avgPriceMins"].isDouble())
            {
                return {}; // avgPriceMins is required
            }
            filter->avgPriceMins = jsonObj["avgPriceMins"].toInt();
            return filter;
        }
        case Type::PERCENT_PRICE_BY_SIDE:
        {
            auto filter = std::make_shared<PercentPriceBySideFilter>();
            if (!jsonObj.contains("bidMultiplierUp") || !jsonObj["bidMultiplierUp"].isString())
            {
                return {}; // bidMultiplierUp is required
            }
            filter->bidMultiplierUp = jsonObj["bidMultiplierUp"].toString().toDouble();
            if (!jsonObj.contains("bidMultiplierDown") || !jsonObj["bidMultiplierDown"].isString())
            {
                return {}; // bidMultiplierDown is required
            }
            filter->bidMultiplierDown = jsonObj["bidMultiplierDown"].toString().toDouble();
            if (!jsonObj.contains("askMultiplierUp") || !jsonObj["askMultiplierUp"].isString())
            {
                return {}; // askMultiplierUp is required
            }
            filter->askMultiplierUp = jsonObj["askMultiplierUp"].toString().toDouble();
            if (!jsonObj.contains("askMultiplierDown") || !jsonObj["askMultiplierDown"].isString())
            {
                return {}; // askMultiplierDown is required
            }
            filter->askMultiplierDown = jsonObj["askMultiplierDown"].toString().toDouble();
            if (!jsonObj.contains("avgPriceMins") || !jsonObj["avgPriceMins"].isDouble())
            {
                return {}; // avgPriceMins is required
            }
            filter->avgPriceMins = jsonObj["avgPriceMins"].toInt();
            return filter;
        }
        case Type::LOT_SIZE:
        {
            auto filter = std::make_shared<LotSize>();
            if (!jsonObj.contains("minQty") || !jsonObj["minQty"].isString())
            {
                return {}; // minQty is required
            }
            filter->minQty = jsonObj["minQty"].toString().toDouble();
            if (!jsonObj.contains("maxQty") || !jsonObj["maxQty"].isString())
            {
                return {}; // maxQty is required
            }
            filter->maxQty = jsonObj["maxQty"].toString().toDouble();
            if (!jsonObj.contains("stepSize") || !jsonObj["stepSize"].isString())
            {
                return {}; // stepSize is required
            }
            filter->stepSize = jsonObj["stepSize"].toString().toDouble();
            return filter;
        }
        case Type::MIN_NOTIONAL:
        {
            auto filter = std::make_shared<MinNotional>();
            if (!jsonObj.contains("minNotional") || !jsonObj["minNotional"].isString())
            {
                return {}; // minNotional is required
            }
            filter->minNotional = jsonObj["minNotional"].toString().toDouble();
            if (!jsonObj.contains("applyToMarket") || !jsonObj["applyToMarket"].isBool())
            {
                return {}; // applyToMarket is required
            }
            filter->applyToMarket = jsonObj["applyToMarket"].toBool();
            if (!jsonObj.contains("avgPriceMins") || !jsonObj["avgPriceMins"].isDouble())
            {
                return {}; // avgPriceMins is required
            }
            filter->avgPriceMins = jsonObj["avgPriceMins"].toInt();
            return filter;
        }
        case Type::NOTIONAL:
        {
            auto filter = std::make_shared<Notional>();
            if (!jsonObj.contains("minNotional") || !jsonObj["minNotional"].isString())
            {
                return {}; // minNotional is required
            }
            filter->minNotional = jsonObj["minNotional"].toString().toDouble();
            if (!jsonObj.contains("applyMinToMarket") || !jsonObj["applyMinToMarket"].isBool())
            {
                return {}; // applyMinToMarket is required
            }
            filter->applyMinToMarket = jsonObj["applyMinToMarket"].toBool();
            if (!jsonObj.contains("maxNotional") || !jsonObj["maxNotional"].isString())
            {
                return {}; // maxNotional is required
            }
            filter->maxNotional = jsonObj["maxNotional"].toString().toDouble();
            if (!jsonObj.contains("applyMaxToMarket") || !jsonObj["applyMaxToMarket"].isBool())
            {
                return {}; // applyMaxToMarket is required
            }
            filter->applyMaxToMarket = jsonObj["applyMaxToMarket"].toBool();
            if (!jsonObj.contains("avgPriceMins") || !jsonObj["avgPriceMins"].isDouble())
            {
                return {}; // avgPriceMins is required
            }
            filter->avgPriceMins = jsonObj["avgPriceMins"].toInt();
            return filter;
        }
        case Type::ICEBERG_PARTS:
        {
            auto filter = std::make_shared<IcebergParts>();
            if (!jsonObj.contains("limit") || !jsonObj["limit"].isDouble())
            {
                return {}; // limit is required
            }
            filter->limit = jsonObj["limit"].toInt();
            return filter;
        }
        case Type::MARKET_LOT_SIZE:
        {
            auto filter = std::make_shared<MarketLotSize>();
            if (!jsonObj.contains("minQty") || !jsonObj["minQty"].isString())
            {
                return {}; // minQty is required
            }
            filter->minQty = jsonObj["minQty"].toString().toDouble();
            if (!jsonObj.contains("maxQty") || !jsonObj["maxQty"].isString())
            {
                return {}; // maxQty is required
            }
            filter->maxQty = jsonObj["maxQty"].toString().toDouble();
            if (!jsonObj.contains("stepSize") || !jsonObj["stepSize"].isString())
            {
                return {}; // stepSize is required
            }
            filter->stepSize = jsonObj["stepSize"].toString().toDouble();
            return filter;
        }
        // Exchange filters
        case Type::MAX_NUM_ORDERS:
        {
            auto filter = std::make_shared<MaxNumOrders>();
            if (!jsonObj.contains("maxNumOrders") || !jsonObj["maxNumOrders"].isDouble())
            {
                return {}; // maxNumOrders is required
            }
            filter->maxNumOrders = jsonObj["maxNumOrders"].toInt();
            return filter;
        }
        case Type::MAX_NUM_ALGO_ORDERS:
        {
            auto filter = std::make_shared<MaxNumAlgoOrders>();
            if (!jsonObj.contains("maxNumAlgoOrders") || !jsonObj["maxNumAlgoOrders"].isDouble())
            {
                return {}; // maxNumAlgoOrders is required
            }
            filter->maxNumAlgoOrders = jsonObj["maxNumAlgoOrders"].toInt();
            return filter;
        }
        case Type::MAX_NUM_ICEBERG_ORDERS:
        {
            auto filter = std::make_shared<MaxNumIcebergOrders>();
            if (!jsonObj.contains("maxNumIcebergOrders") || !jsonObj["maxNumIcebergOrders"].isDouble())
            {
                return {}; // maxNumIcebergOrders is required
            }
            filter->maxNumIcebergOrders = jsonObj["maxNumIcebergOrders"].toInt();
            return filter;
        }
        case Type::MAX_POSITION:
        {
            auto filter = std::make_shared<MaxPosition>();
            if (!jsonObj.contains("maxPosition") || !jsonObj["maxPosition"].isString())
            {
                return {}; // maxPosition is required
            }
            filter->maxPosition = jsonObj["maxPosition"].toString().toDouble();
            return filter;
        }
        case Type::TRAILING_DELTA:
        {
            auto filter = std::make_shared<TrailingDelta>();
            if (!jsonObj.contains("minTrailingAboveDelta") || !jsonObj["minTrailingAboveDelta"].isDouble())
            {
                return {}; // minTrailingAboveDelta is required
            }
            filter->minTrailingAboveDelta = jsonObj["minTrailingAboveDelta"].toInt();
            if (!jsonObj.contains("maxTrailingAboveDelta") || !jsonObj["maxTrailingAboveDelta"].isDouble())
            {
                return {}; // maxTrailingAboveDelta is required
            }
            filter->maxTrailingAboveDelta = jsonObj["maxTrailingAboveDelta"].toInt();
            if (!jsonObj.contains("minTrailingBelowDelta") || !jsonObj["minTrailingBelowDelta"].isDouble())
            {
                return {}; // minTrailingBelowDelta is required
            }
            filter->minTrailingBelowDelta = jsonObj["minTrailingBelowDelta"].toInt();
            if (!jsonObj.contains("maxTrailingBelowDelta") || !jsonObj["maxTrailingBelowDelta"].isDouble())
            {
                return {}; // maxTrailingBelowDelta is required
            }
            filter->maxTrailingBelowDelta = jsonObj["maxTrailingBelowDelta"].toInt();
            return filter;
        }
        case Type::MAX_NUM_ORDER_AMENDS:
        {
            auto filter = std::make_shared<MaxNumOrderAmends>();
            if (!jsonObj.contains("maxNumOrderAmends") || !jsonObj["maxNumOrderAmends"].isDouble())
            {
                return {}; // maxNumOrderAmends is required
            }
            filter->maxNumOrderAmends = jsonObj["maxNumOrderAmends"].toInt();
            return filter;
        }
        case Type::MAX_NUM_ORDER_LISTS:
        {
            auto filter = std::make_shared<MaxNumOrderLists>();
            if (!jsonObj.contains("maxNumOrderLists") || !jsonObj["maxNumOrderLists"].isDouble())
            {
                return {}; // maxNumOrderLists is required
            }
            filter->maxNumOrderLists = jsonObj["maxNumOrderLists"].toInt();
            return filter;
        }
        case Type::EXCHANGE_MAX_NUM_ORDERS:
        {
            auto filter = std::make_shared<ExchangeMaxNumOrders>();
            if (!jsonObj.contains("maxNumOrders") || !jsonObj["maxNumOrders"].isDouble())
            {
                return {}; // maxNumOrders is required
            }
            filter->maxNumOrders = jsonObj["maxNumOrders"].toInt();
            return filter;
        }
        case Type::EXCHANGE_MAX_NUM_ALGO_ORDERS:
        {
            auto filter = std::make_shared<ExchangeMaxNumAlgoOrders>();
            if (!jsonObj.contains("maxNumAlgoOrders") || !jsonObj["maxNumAlgoOrders"].isDouble())
            {
                return {}; // maxNumAlgoOrders is required
            }
            filter->maxNumAlgoOrders = jsonObj["maxNumAlgoOrders"].toInt();
            return filter;
        }
        case Type::EXCHANGE_MAX_NUM_ICEBERG_ORDERS:
        {
            auto filter = std::make_shared<ExchangeMaxNumIcebergOrders>();
            if (!jsonObj.contains("maxNumIcebergOrders") || !jsonObj["maxNumIcebergOrders"].isDouble())
            {
                return {}; // maxNumIcebergOrders is required
            }
            filter->maxNumIcebergOrders = jsonObj["maxNumIcebergOrders"].toInt();
            return filter;
        }
        case Type::EXCHANGE_MAX_NUM_ORDER_LISTS:
        {
            auto filter = std::make_shared<ExchangeMaxNumOrderLists>();
            if (!jsonObj.contains("maxNumOrderLists") || !jsonObj["maxNumOrderLists"].isDouble())
            {
                return {}; // maxNumOrderLists is required
            }
            filter->maxNumOrderLists = jsonObj["maxNumOrderLists"].toInt();
            return filter;
        }
        default:
            return {}; // Unsupported filter type for SymbolFilter
        }
    }
} // namespace Binance::Filter
