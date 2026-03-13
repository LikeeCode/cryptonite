#pragma once

#include <optional>

#include <QString>

#include "../data/Enums.h"

namespace Binance::Enum
{
    // SymbolStatus
    QString toString(SymbolStatus status);
    std::optional<SymbolStatus> toSymbolStatus(const QString &status);

    // AccountAndSymbolPermissions
    QString toString(AccountAndSymbolPermissions permission);
    std::optional<AccountAndSymbolPermissions> toAccountAndSymbolPermissions(const QString &permission);

    // OrderStatus
    QString toString(OrderStatus status);
    std::optional<OrderStatus> toOrderStatus(const QString &status);

    // OrderListStatus
    QString toString(OrderListStatus status);
    std::optional<OrderListStatus> toOrderListStatus(const QString &status);

    // OrderListOrderStatus
    QString toString(OrderListOrderStatus status);
    std::optional<OrderListOrderStatus> toOrderListOrderStatus(const QString &status);

    // ContingencyType
    QString toString(ContingencyType type);
    std::optional<ContingencyType> toContingencyType(const QString &type);

    // AllocationType
    QString toString(AllocationType type);
    std::optional<AllocationType> toAllocationType(const QString &type);

    // OrderType
    QString toString(OrderType type);
    std::optional<OrderType> toOrderType(const QString &type);

    // ResponseType
    QString toString(ResponseType type);
    std::optional<ResponseType> toResponseType(const QString &type);

    // OrderResponseType
    QString toString(OrderResponseType type);
    std::optional<OrderResponseType> toOrderResponseType(const QString &type);

    // WorkingFloor
    QString toString(WorkingFloor floor);
    std::optional<WorkingFloor> toWorkingFloor(const QString &floor);

    // OrderSide
    QString toString(OrderSide side);
    std::optional<OrderSide> toOrderSide(const QString &side);

    // TimeInForce
    QString toString(TimeInForce tif);
    std::optional<TimeInForce> toTimeInForce(const QString &tif);

    // RateLimitInterval
    QString toString(RateLimitInterval interval);
    std::optional<RateLimitInterval> toRateLimitInterval(const QString &interval);

    // Interval
    QString toString(Interval interval);
    std::optional<Interval> toInterval(const QString &interval);
    
    // RateLimitType
    QString toString(RateLimitType type);
    std::optional<RateLimitType> toRateLimitType(const QString &type);

    // SelfTradePreventionMode
    QString toString(SelfTradePreventionMode mode);
    std::optional<SelfTradePreventionMode> toSelfTradePreventionMode(const QString &mode);

    // PegPriceType
    QString toString(PegPriceType type);
    std::optional<PegPriceType> toPegPriceType(const QString &type);

    // PegOffsetType
    QString toString(PegOffsetType type);
    std::optional<PegOffsetType> toPegOffsetType(const QString &type);
    
} // namespace Binance::Enum
