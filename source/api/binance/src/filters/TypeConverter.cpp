#pragma once

#include <QString>
#include <QHash>

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
} // namespace Binance::Filter
