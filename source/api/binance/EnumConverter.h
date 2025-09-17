#pragma once

#include <QString>

#include "Enums.h"

namespace Api::Binance
{
    class EnumConverter
    {
    public:
        // SymbolStatus
        inline static QString symbolStatusToString(SymbolStatus status);
        inline static SymbolStatus stringToSymbolStatus(const QString& statusStr);

        // AccountAndSymbolPermissions
        inline static QString accountAndSymbolPermissionsToString(AccountAndSymbolPermissions permission);
        inline static AccountAndSymbolPermissions stringToAccountAndSymbolPermissions(const QString& permissionStr);

        // OrderStatus
        inline static QString orderStatusToString(OrderStatus status);
        inline static OrderStatus stringToOrderStatus(const QString& statusStr);

        // OrderListStatus
        inline static QString orderListStatusToString(OrderListStatus status);
        inline static OrderListStatus stringToOrderListStatus(const QString& statusStr);

        // OrderListOrderStatus
        inline static QString orderListOrderStatusToString(OrderListOrderStatus status);
        inline static OrderListOrderStatus stringToOrderListOrderStatus(const QString& statusStr);

        // ContingencyType
        inline static QString contingencyTypeToString(ContingencyType type);
        inline static ContingencyType stringToContingencyType(const QString& typeStr);

        // AllocationType
        inline static QString allocationTypeToString(AllocationType type);
        inline static AllocationType stringToAllocationType(const QString& typeStr);

        // OrderType
        inline static QString orderTypeToString(OrderType type);
        inline static OrderType stringToOrderType(const QString& typeStr);

        // OrderResponseType
        inline static QString orderResponseTypeToString(OrderResponseType type);
        inline static OrderResponseType stringToOrderResponseType(const QString& typeStr);

        // WorkingFloor
        inline static QString workingFloorToString(WorkingFloor floor);
        inline static WorkingFloor stringToWorkingFloor(const QString& floorStr);

        // OrderSide
        inline static QString orderSideToString(OrderSide side);
        inline static OrderSide stringToOrderSide(const QString& sideStr);

        // TimeInForce
        inline static QString timeInForceToString(TimeInForce tif);
        inline static TimeInForce stringToTimeInForce(const QString& tifStr);

        // RateLimitInterval
        inline static QString rateLimitIntervalToString(RateLimitInterval interval);
        inline static RateLimitInterval stringToRateLimitInterval(const QString& intervalStr);

        // RateLimitType
        inline static QString rateLimitTypeToString(RateLimitType type);
        inline static RateLimitType stringToRateLimitType(const QString& typeStr);

        // SelfTradePreventionMode
        inline static QString selfTradePreventionModeToString(SelfTradePreventionMode mode);
        inline static SelfTradePreventionMode stringToSelfTradePreventionMode(const QString& modeStr);
    };
}
//namespace Api::Binance
