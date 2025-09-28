#pragma once

#include <QList>
#include <QString>
#include <QVariant>

#include "enums/Enums.h"
#include "filters/Filters.h"

namespace Binance::GeneralData
{
    struct Ping
    {
    };
    
    struct ServerTime
    {
        qint64 serverTime{};
    };

    struct RateLimit
    {
        RateLimitType rateLimitType{};
        QString interval;
        int intervalNum{};
        int limit{};
    };

    struct Symbol{
        QString symbol;
        SymbolStatus status{};
        QString baseAsset;
        int baseAssetPrecision{};
        QString quoteAsset;
        int quotePrecision{};
        int quoteAssetPrecision{};
        int baseCommissionPrecision{};
        int quoteCommissionPrecision{};
        QList<OrderType> orderTypes;
        bool icebergAllowed{};
        bool ocoAllowed{};
        bool otoAllowed{};
        bool quoteOrderQtyMarketAllowed{};
        bool allowTrailingStop{};
        bool cancelReplaceAllowed{};
        bool amendAllowed{};
        bool pegInstructionsAllowed{};
        bool isSpotTradingAllowed{};
        bool isMarginTradingAllowed{};
        QList<std::shared_ptr<Filter::BinanceFilter>> filters;
        QList<AccountAndSymbolPermissions> permissions;
        QList<AccountAndSymbolPermissions> permissionSets;
        QString defaultSelfTradePreventionMode;
        QList<SelfTradePreventionMode> allowedSelfTradePreventionModes;
    };
    
    struct ExchangeInfo
    {
        QString timezone;
        qint64 serverTime{};
        QList<RateLimit> rateLimits;
        QList<Binance::Filter::Type> exchangeFilters;
        QList<Symbol> symbols;
        QList<Symbol> sors;
    };
}
