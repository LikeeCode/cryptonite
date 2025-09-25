#pragma once

#include <QMap>
#include <QString>
#include <QVariant>

namespace Binance::Filter
{
    // See: https://github.com/binance/binance-spot-api-docs/blob/master/testnet/filters.md

    enum class Type
    {
        // Symbol filters
        PRICE_FILTER,
        PERCENT_PRICE,
        PERCENT_PRICE_BY_SIDE,
        LOT_SIZE,
        MIN_NOTIONAL,
        NOTIONAL,
        ICEBERG_PARTS,
        MARKET_LOT_SIZE,
        // Exchange filters
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
        EXCHANGE_MAX_NUM_ORDER_LISTS
    };

    struct BinanceFilter
    {
        Type filterType{};
    };

    // Symbol Filters
    struct PriceFilter : BinanceFilter
    {
        double minPrice{};
        double maxPrice{};
        double tickSize{};
    };

    struct PercentPriceFilter : BinanceFilter
    {
        double multiplierUp{};
        double multiplierDown{};
        int avgPriceMins{};
    };

    struct PercentPriceBySideFilter : BinanceFilter
    {
        double bidMultiplierUp{};
        double bidMultiplierDown{};
        int askMultiplierUp{};
        double askMultiplierDown{};
        int avgPriceMins{};
    };

    struct LotSize : BinanceFilter
    {
        double minQty{};
        double maxQty{};
        double stepSize{};
    };

    struct MinNotional : BinanceFilter
    {
        double minNotional{};
        bool applyToMarket{};
        int avgPriceMins{};
    };

    struct Notional : BinanceFilter
    {
        double minNotional{};
        bool applyMinToMarket{};
        double maxNotional{};
        bool applyMaxToMarket{};
        int avgPriceMins{};
    };

    struct IcebergParts : BinanceFilter
    {
        int limit{};
    };

    struct MarketLotSize : BinanceFilter
    {
        double minQty{};
        double maxQty{};
        double stepSize{};
    };

    // Exchange Filters

    struct MaxNumOrders : BinanceFilter
    {
        int maxNumOrders{};
    };

    struct MaxNumAlgoOrders : BinanceFilter
    {
        int maxNumAlgoOrders{};
    };

    struct MaxNumIcebergOrders : BinanceFilter
    {
        int maxNumIcebergOrders{};
    };

    struct MaxPosition : BinanceFilter
    {
        double maxPosition{};
    };

    struct TrailingDelta : BinanceFilter
    {
        int minTrailingAboveDelta{};
        int maxTrailingAboveDelta{};
        int minTrailingBelowDelta{};
        int maxTrailingBelowDelta{};
    };

    struct MaxNumOrderAmends : BinanceFilter
    {
        int maxNumOrderAmends{};
    };

    struct MaxNumOrderLists : BinanceFilter
    {
        int maxNumOrderLists{};
    };

    struct ExchangeMaxNumOrders : BinanceFilter
    {
        int maxNumOrders{};
    };

    struct ExchangeMaxNumAlgoOrders : BinanceFilter
    {
        int maxNumAlgoOrders{};
    };

    struct ExchangeMaxNumIcebergOrders : BinanceFilter
    {
        int maxNumIcebergOrders{};
    };

    struct ExchangeMaxNumOrderLists : BinanceFilter
    {
        int maxNumOrderLists{};
    };
} // namespace Binance::Filter
