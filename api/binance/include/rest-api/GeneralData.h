#pragma once

#include <optional>

#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include <QString>
#include <QVariant>

#include "../enums/Enums.h"
#include "../filters/Filters.h"

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

    struct ExchangeInfoRequest
    {
        std::optional<QString> symbol{};
        std::optional<QList<QString>> symbols{};

        QVariantMap toVariantMap() const {
            QVariantMap params;
            if (symbol.has_value()) {
                params.insert("symbol", symbol.value());
            } else if (symbols.has_value()) {
                QJsonArray jsonArray;
                for (const auto& sym : symbols.value()) {
                    jsonArray.append(sym);
                }
                params.insert("symbols", QJsonDocument(jsonArray).toJson(QJsonDocument::Compact));
            }
            return params;
        }
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
