#pragma once

#include <optional>

#include <QString>

#include "Enums.h"

namespace Binance
{
    class EnumConverter
    {
    public:
        // SymbolStatus
        inline static QString toString(SymbolStatus status);
        inline static std::optional<SymbolStatus> toSymbolStatus(const QString &status);

        // AccountAndSymbolPermissions
        inline static QString toString(AccountAndSymbolPermissions permission);
        inline static std::optional<AccountAndSymbolPermissions> toAccountAndSymbolPermissions(const QString &permission);

        // OrderStatus
        inline static QString toString(OrderStatus status);
        inline static std::optional<OrderStatus> toOrderStatus(const QString &status);

        // OrderListStatus
        inline static QString toString(OrderListStatus status);
        inline static std::optional < OrderListStatus> toOrderListStatus(const QString &status);

        // OrderListOrderStatus
        inline static QString toString(OrderListOrderStatus status);
        inline static std::optional<OrderListOrderStatus> toOrderListOrderStatus(const QString &status);

        // ContingencyType
        inline static QString toString(ContingencyType type);
        inline static std::optional<ContingencyType> toContingencyType(const QString &type);

        // AllocationType
        inline static QString toString(AllocationType type);
        inline static std::optional<AllocationType> toAllocationType(const QString &type);

        // OrderType
        inline static QString toString(OrderType type);
        inline static std::optional<OrderType> toOrderType(const QString &type);

        // OrderResponseType
        inline static QString toString(OrderResponseType type);
        inline static std::optional<OrderResponseType> toOrderResponseType(const QString &type);

        // WorkingFloor
        inline static QString toString(WorkingFloor floor);
        inline static std::optional<WorkingFloor> toWorkingFloor(const QString &floor);

        // OrderSide
        inline static QString toString(OrderSide side);
        inline static std::optional<OrderSide> toOrderSide(const QString &side);

        // TimeInForce
        inline static QString toString(TimeInForce tif);
        inline static std::optional<TimeInForce> toTimeInForce(const QString &tif);

        // RateLimitInterval
        inline static QString toString(RateLimitInterval interval);
        inline static std::optional<RateLimitInterval> toRateLimitInterval(const QString &interval);

        // RateLimitType
        inline static QString toString(RateLimitType type);
        inline static std::optional<RateLimitType> toRateLimitType(const QString &type);

        // SelfTradePreventionMode
        inline static QString toString(SelfTradePreventionMode mode);
        inline static std::optional<SelfTradePreventionMode> toSelfTradePreventionMode(const QString &mode);
    };
} //namespace Binance
