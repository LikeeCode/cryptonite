#pragma once

#include <QString>
#include <QHash>

#include "FilterConverter.h"

namespace Binance
{
    QString FilterConverter::filterTypeToString(FilterType type)
    {
        static const QMap<FilterType, QString> filterTypeMap = {
            {FilterType::PRICE_FILTER, "PRICE_FILTER"},
            {FilterType::PERCENT_PRICE, "PERCENT_PRICE"},
            {FilterType::PERCENT_PRICE_BY_SIDE, "PERCENT_PRICE_BY_SIDE"},
            {FilterType::LOT_SIZE, "LOT_SIZE"},
            {FilterType::MIN_NOTIONAL, "MIN_NOTIONAL"},
            {FilterType::NOTIONAL, "NOTIONAL"},
            {FilterType::ICEBERG_PARTS, "ICEBERG_PARTS"},
            {FilterType::MARKET_LOT_SIZE, "MARKET_LOT_SIZE"},
            {FilterType::MAX_NUM_ORDERS, "MAX_NUM_ORDERS"},
            {FilterType::MAX_NUM_ALGO_ORDERS, "MAX_NUM_ALGO_ORDERS"},
            {FilterType::MAX_NUM_ICEBERG_ORDERS, "MAX_NUM_ICEBERG_ORDERS"},
            {FilterType::MAX_POSITION, "MAX_POSITION"},
            {FilterType::TRAILING_DELTA, "TRAILING_DELTA"},
            {FilterType::MAX_NUM_ORDER_AMENDS, "MAX_NUM_ORDER_AMENDS"},
            {FilterType::MAX_NUM_ORDER_LISTS, "MAX_NUM_ORDER_LISTS"},
            {FilterType::EXCHANGE_MAX_NUM_ORDERS, "EXCHANGE_MAX_NUM_ORDERS"},
            {FilterType::EXCHANGE_MAX_NUM_ALGO_ORDERS, "EXCHANGE_MAX_NUM_ALGO_ORDERS"},
            {FilterType::EXCHANGE_MAX_NUM_ICEBERG_ORDERS, "EXCHANGE_MAX_NUM_ICEBERG_ORDERS"},
            {FilterType::EXCHANGE_MAX_NUM_ORDER_LISTS, "EXCHANGE_MAX_NUM_ORDER_LISTS"},
            {FilterType::UNKNOWN, "UNKNOWN"}};

        return filterTypeMap.value(type, "UNKNOWN");
    }

    FilterType FilterConverter::stringToFilterType(const QString& type)
    {
        static const QMap<QString, FilterType> filterTypeMap = {
            {"PRICE_FILTER", FilterType::PRICE_FILTER},
            {"PERCENT_PRICE", FilterType::PERCENT_PRICE},
            {"PERCENT_PRICE_BY_SIDE", FilterType::PERCENT_PRICE_BY_SIDE},
            {"LOT_SIZE", FilterType::LOT_SIZE},
            {"MIN_NOTIONAL", FilterType::MIN_NOTIONAL},
            {"NOTIONAL", FilterType::NOTIONAL},
            {"ICEBERG_PARTS", FilterType::ICEBERG_PARTS},
            {"MARKET_LOT_SIZE", FilterType::MARKET_LOT_SIZE},
            {"MAX_NUM_ORDERS", FilterType::MAX_NUM_ORDERS},
            {"MAX_NUM_ALGO_ORDERS", FilterType::MAX_NUM_ALGO_ORDERS},
            {"MAX_NUM_ICEBERG_ORDERS", FilterType::MAX_NUM_ICEBERG_ORDERS},
            {"MAX_POSITION", FilterType::MAX_POSITION},
            {"TRAILING_DELTA", FilterType::TRAILING_DELTA},
            {"MAX_NUM_ORDER_AMENDS", FilterType::MAX_NUM_ORDER_AMENDS},
            {"MAX_NUM_ORDER_LISTS", FilterType::MAX_NUM_ORDER_LISTS},
            {"EXCHANGE_MAX_NUM_ORDERS", FilterType::EXCHANGE_MAX_NUM_ORDERS},
            {"EXCHANGE_MAX_NUM_ALGO_ORDERS", FilterType::EXCHANGE_MAX_NUM_ALGO_ORDERS},
            {"EXCHANGE_MAX_NUM_ICEBERG_ORDERS", FilterType::EXCHANGE_MAX_NUM_ICEBERG_ORDERS},
            {"EXCHANGE_MAX_NUM_ORDER_LISTS", FilterType::EXCHANGE_MAX_NUM_ORDER_LISTS}};

        return filterTypeMap.value(type, FilterType::UNKNOWN);
    }
} // namespace Binance
