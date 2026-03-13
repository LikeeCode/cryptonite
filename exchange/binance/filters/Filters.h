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
        explicit BinanceFilter(const QString &type) : filterType(type) {}
        QString filterType;
    };

    // Symbol Filters
    struct PriceFilter : BinanceFilter
    {
        PriceFilter() : BinanceFilter("PRICE_FILTER") {};
        double minPrice{};
        double maxPrice{};
        double tickSize{};
    };

    struct PercentPriceFilter : BinanceFilter
    {
        PercentPriceFilter() : BinanceFilter("PERCENT_PRICE") {};
        double multiplierUp{};
        double multiplierDown{};
        int avgPriceMins{};
    };

    struct PercentPriceBySideFilter : BinanceFilter
    {
        PercentPriceBySideFilter() : BinanceFilter("PERCENT_PRICE_BY_SIDE") {};
        double bidMultiplierUp{};
        double bidMultiplierDown{};
        int askMultiplierUp{};
        double askMultiplierDown{};
        int avgPriceMins{};
    };

    struct LotSize : BinanceFilter
    {
        LotSize() : BinanceFilter("LOT_SIZE") {};
        double minQty{};
        double maxQty{};
        double stepSize{};
    };

    struct MinNotional : BinanceFilter
    {
        MinNotional() : BinanceFilter("MIN_NOTIONAL") {};
        double minNotional{};
        bool applyToMarket{};
        int avgPriceMins{};
    };

    struct Notional : BinanceFilter
    {
        Notional() : BinanceFilter("NOTIONAL") {};
        double minNotional{};
        bool applyMinToMarket{};
        double maxNotional{};
        bool applyMaxToMarket{};
        int avgPriceMins{};
    };

    struct IcebergParts : BinanceFilter
    {
        IcebergParts() : BinanceFilter("ICEBERG_PARTS") {};
        int limit{};
    };

    struct MarketLotSize : BinanceFilter
    {
        MarketLotSize() : BinanceFilter("MARKET_LOT_SIZE") {};
        double minQty{};
        double maxQty{};
        double stepSize{};
    };

    // Exchange Filters

    struct MaxNumOrders : BinanceFilter
    {
        MaxNumOrders() : BinanceFilter("MAX_NUM_ORDERS") {};
        int maxNumOrders{};
    };

    struct MaxNumAlgoOrders : BinanceFilter
    {
        MaxNumAlgoOrders() : BinanceFilter("MAX_NUM_ALGO_ORDERS") {};
        int maxNumAlgoOrders{};
    };

    struct MaxNumIcebergOrders : BinanceFilter
    {
        MaxNumIcebergOrders() : BinanceFilter("MAX_NUM_ICEBERG_ORDERS") {};
        int maxNumIcebergOrders{};
    };

    struct MaxPosition : BinanceFilter
    {
        MaxPosition() : BinanceFilter("MAX_POSITION") {};
        double maxPosition{};
    };

    struct TrailingDelta : BinanceFilter
    {
        TrailingDelta() : BinanceFilter("TRAILING_DELTA") {};
        int minTrailingAboveDelta{};
        int maxTrailingAboveDelta{};
        int minTrailingBelowDelta{};
        int maxTrailingBelowDelta{};
    };

    struct MaxNumOrderAmends : BinanceFilter
    {
        MaxNumOrderAmends() : BinanceFilter("MAX_NUM_ORDER_AMENDS") {};
        int maxNumOrderAmends{};
    };

    struct MaxNumOrderLists : BinanceFilter
    {
        MaxNumOrderLists() : BinanceFilter("MAX_NUM_ORDER_LISTS") {};
        int maxNumOrderLists{};
    };

    struct ExchangeMaxNumOrders : BinanceFilter
    {
        ExchangeMaxNumOrders() : BinanceFilter("EXCHANGE_MAX_NUM_ORDERS") {};
        int maxNumOrders{};
    };

    struct ExchangeMaxNumAlgoOrders : BinanceFilter
    {
        ExchangeMaxNumAlgoOrders() : BinanceFilter("EXCHANGE_MAX_NUM_ALGO_ORDERS") {};
        int maxNumAlgoOrders{};
    };

    struct ExchangeMaxNumIcebergOrders : BinanceFilter
    {
        ExchangeMaxNumIcebergOrders() : BinanceFilter("EXCHANGE_MAX_NUM_ICEBERG_ORDERS") {};
        int maxNumIcebergOrders{};
    };

    struct ExchangeMaxNumOrderLists : BinanceFilter
    {
        ExchangeMaxNumOrderLists() : BinanceFilter("EXCHANGE_MAX_NUM_ORDER_LISTS") {};
        int maxNumOrderLists{};
    };
} // namespace Binance::Filter
