#pragma once

#include <QString>
#include <QMap>

namespace Binance
{
    // See: https://github.com/binance/binance-spot-api-docs/blob/master/testnet/filters.md

    enum class FilterType
    {
        PRICE_FILTER,
        PERCENT_PRICE,
        PERCENT_PRICE_BY_SIDE,
        LOT_SIZE,
        MIN_NOTIONAL,
        NOTIONAL,
        ICEBERG_PARTS,
        MARKET_LOT_SIZE,
        MAX_NUM_ORDERS,
        MAX_NUM_ALGO_ORDERS,
        MAX_NUM_ICEBERG_ORDERS,
        MAX_POSITION,
        TRAILING_DELTA,
        MAX_NUM_ORDER_AMENDS,
        MAX_NUM_ORDER_LISTS,
        EXCHANGE_MAX_NUM_ORDERS,
        EXCHANGE_MAX_NUM_ALGO_ORDERS,
        EXCHANGE_MAX_NUM_ICEBERG_ORDERS,
        EXCHANGE_MAX_NUM_ORDER_LISTS,
        UNKNOWN
    };

    // Symbol Filters
    struct PriceFilter
    {
        double minPrice{};
        double maxPrice{};
        double tickSize{};
    };

    struct PercentPriceFilter
    {
        double multiplierUp{};
        double multiplierDown{};
        int avgPriceMins{};
    };

    struct PercentPriceBySideFilter
    {
        double bidMultiplierUp{};
        double bidMultiplierDown{};
        int askMultiplierUp{};
        double askMultiplierDown{};
        int avgPriceMins{};
    };

    struct LotSize
    {
        double minQty{};
        double maxQty{};
        double stepSize{};
    };

    struct MinNotional
    {
        double minNotional{};
        int applyToMarket{};
        int avgPriceMins{};
    };

    struct Notional
    {
        double minNotional{};
        double applyMinToMarket{};
        double maxNotional{};
        double applyMaxToMarket{};
        int avgPriceMins{};
    };

    struct IcebergParts
    {
        int limit{};
    };

    struct MarketLotSize
    {
        double minQty{};
        double maxQty{};
        double stepSize{};
    };

    struct MaxNumOrders
    {
        int maxNumOrders{};
    };



    struct MaxNumAlgoOrders
    {
        int maxNumAlgoOrders{};
    };

    struct MaxNumIcebergOrders
    {
        int maxNumIcebergOrders{};
    };

    struct MaxPosition
    {
        double maxPosition{};
    };

    struct TrailingDelta
    {
        int minTrailingAboveDelta{};
        int maxTrailingAboveDelta{};
        int minTrailingBelowDelta{};
        int maxTrailingBelowDelta{};
    };

    struct MaxNumOrderAmends
    {
        int maxNumOrderAmends{};
    };

    struct MaxNumOrderLists
    {
        int maxNumOrderLists{};
    };

    // Exchange Filters
    struct ExchangeMaxNumOrders
    {
        int maxNumOrders{};
    };

    struct ExchangeMaxNumAlgoOrders
    {
        int maxNumAlgoOrders{};
    };

    struct ExchangeMaxNumIcebergOrders
    {
        int maxNumIcebergOrders{};
    };

    struct ExchangeMaxNumOrderLists
    {
        int maxNumOrderLists{};
    };
} // namespace Binance
