#pragma once

#include <QList>
#include <QString>
#include <QVariant>

#include "enums/Enums.h"
#include "filters/Filters.h"

namespace Binance::GeneralData
{
    // Test connectivity
    // GET /api/v3/ping
    // Response
    struct Ping
    {
    };

    // Check server time
    // GET /api/v3/time
    // Response
    struct ServerTime
    {
        qint64 serverTime{};
    };

    // Exchange information
    // GET /api/v3/exchangeInfo
    // Request
    struct ExchangeInfoRequest{
        QString symbol; // Optional
        QList<QString> symbols; // Optional
        AccountAndSymbolPermissions permissions{}; // Optional
        bool showPermissionSets{}; // Optional
        SymbolStatus status{}; // Optional
    };

    // Response
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
        QList<FilterType> filters; // This uses the Filter variant from your Filters.h
        QList<AccountAndSymbolPermissions> permissions;
        QList<AccountAndSymbolPermissions> permissionSets;
        QString defaultSelfTradePreventionMode;
        QList<SelfTradePreventionMode> allowedSelfTradePreventionModes;
    };

    struct SOR
    {
        QString baseAsset;
        QList<QString> symbols;
    };
    struct ExchangeInfo
    {
        QString timezone;
        qint64 serverTime{};
        QList<RateLimitType> rateLimits;
        QList<FilterType> exchangeFilters;
        QList<Symbol> symbols;
        QList<Symbol> sors;
    };
}
