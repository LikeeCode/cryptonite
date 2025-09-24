#pragma once

#include <QHash>
#include <QString>

#include "EnumConverter.h"

namespace Binance
{
    QString EnumConverter::symbolStatusToString(SymbolStatus status)
    {
        static const QHash<SymbolStatus, QString> map = {
            {SymbolStatus::TRADING, "TRADING"},
            {SymbolStatus::END_OF_DAY, "END_OF_DAY"},
            {SymbolStatus::HALT, "HALT"},
            {SymbolStatus::BREAK, "BREAK"}};
        return map.value(status);
    }

    SymbolStatus EnumConverter::stringToSymbolStatus(const QString& statusStr)
    {
        static const QHash<QString, SymbolStatus> map = {
            {"TRADING", SymbolStatus::TRADING},
            {"END_OF_DAY", SymbolStatus::END_OF_DAY},
            {"HALT", SymbolStatus::HALT},
            {"BREAK", SymbolStatus::BREAK}};
        return map.value(statusStr, SymbolStatus::BREAK); // Default to BREAK if not found
    }

    QString EnumConverter::accountAndSymbolPermissionsToString(AccountAndSymbolPermissions permission)
    {
        if (permission == AccountAndSymbolPermissions::SPOT) return "SPOT";
        return QString();
    }

    AccountAndSymbolPermissions EnumConverter::stringToAccountAndSymbolPermissions(const QString& permissionStr)
    {
        if (permissionStr == "SPOT") return AccountAndSymbolPermissions::SPOT;
        return AccountAndSymbolPermissions::SPOT; // Only one value
    }

    QString EnumConverter::orderStatusToString(OrderStatus status)
    {
        static const QHash<OrderStatus, QString> map = {
            {OrderStatus::NEW, "NEW"},
            {OrderStatus::PENDING_NEW, "PENDING_NEW"},
            {OrderStatus::PARTIALLY_FILLED, "PARTIALLY_FILLED"},
            {OrderStatus::FILLED, "FILLED"},
            {OrderStatus::CANCELED, "CANCELED"},
            {OrderStatus::PENDING_CANCEL, "PENDING_CANCEL"},
            {OrderStatus::REJECTED, "REJECTED"},
            {OrderStatus::EXPIRED, "EXPIRED"},
            {OrderStatus::EXPIRED_IN_MATCH, "EXPIRED_IN_MATCH"}};
        return map.value(status);
    }

    OrderStatus EnumConverter::stringToOrderStatus(const QString& statusStr)
    {
        static const QHash<QString, OrderStatus> map = {
            {"NEW", OrderStatus::NEW},
            {"PENDING_NEW", OrderStatus::PENDING_NEW},
            {"PARTIALLY_FILLED", OrderStatus::PARTIALLY_FILLED},
            {"FILLED", OrderStatus::FILLED},
            {"CANCELED", OrderStatus::CANCELED},
            {"PENDING_CANCEL", OrderStatus::PENDING_CANCEL},
            {"REJECTED", OrderStatus::REJECTED},
            {"EXPIRED", OrderStatus::EXPIRED},
            {"EXPIRED_IN_MATCH", OrderStatus::EXPIRED_IN_MATCH}};
        return map.value(statusStr, OrderStatus::REJECTED); // Default to REJECTED if not found
    }

    QString EnumConverter::orderListStatusToString(OrderListStatus status)
    {
        static const QHash<OrderListStatus, QString> map = {
            {OrderListStatus::RESPONSE, "RESPONSE"},
            {OrderListStatus::EXEC_STARTED, "EXEC_STARTED"},
            {OrderListStatus::UPDATED, "UPDATED"},
            {OrderListStatus::ALL_DONE, "ALL_DONE"}};
        return map.value(status);
    }

    OrderListStatus EnumConverter::stringToOrderListStatus(const QString& statusStr)
    {
        static const QHash<QString, OrderListStatus> map = {
            {"RESPONSE", OrderListStatus::RESPONSE},
            {"EXEC_STARTED", OrderListStatus::EXEC_STARTED},
            {"UPDATED", OrderListStatus::UPDATED},
            {"ALL_DONE", OrderListStatus::ALL_DONE}};
        return map.value(statusStr, OrderListStatus::RESPONSE); // Default to RESPONSE if not found
    }

    QString EnumConverter::orderListOrderStatusToString(OrderListOrderStatus status)
    {
        static const QHash<OrderListOrderStatus, QString> map = {
            {OrderListOrderStatus::EXECUTING, "EXECUTING"},
            {OrderListOrderStatus::ALL_DONE, "ALL_DONE"},
            {OrderListOrderStatus::REJECT, "REJECT"}};
        return map.value(status);
    }

    OrderListOrderStatus EnumConverter::stringToOrderListOrderStatus(const QString& statusStr)
    {
        static const QHash<QString, OrderListOrderStatus> map = {
            {"EXECUTING", OrderListOrderStatus::EXECUTING},
            {"ALL_DONE", OrderListOrderStatus::ALL_DONE},
            {"REJECT", OrderListOrderStatus::REJECT}};
        return map.value(statusStr, OrderListOrderStatus::REJECT); // Default to REJECT if not found
    }

    QString EnumConverter::contingencyTypeToString(ContingencyType type)
    {
        static const QHash<ContingencyType, QString> map = {
            {ContingencyType::OCO, "OCO"},
            {ContingencyType::OTO, "OTO"}};
        return map.value(type);
    }

    ContingencyType EnumConverter::stringToContingencyType(const QString& typeStr)
    {
        static const QHash<QString, ContingencyType> map = {
            {"OCO", ContingencyType::OCO},
            {"OTO", ContingencyType::OTO}};
        return map.value(typeStr, ContingencyType::OCO); // Default to OCO if not found
    }

    QString EnumConverter::allocationTypeToString(AllocationType type)
    {
        if (type == AllocationType::SOR) return "SOR";
        return QString();
    }

    AllocationType EnumConverter::stringToAllocationType(const QString& typeStr)
    {
        if (typeStr == "SOR") return AllocationType::SOR;
        return AllocationType::SOR; // Only one value
    }

    QString EnumConverter::orderTypeToString(OrderType type)
    {
        static const QHash<OrderType, QString> map = {
            {OrderType::LIMIT, "LIMIT"},
            {OrderType::MARKET, "MARKET"},
            {OrderType::STOP_LOSS, "STOP_LOSS"},
            {OrderType::STOP_LOSS_LIMIT, "STOP_LOSS_LIMIT"},
            {OrderType::TAKE_PROFIT, "TAKE_PROFIT"},
            {OrderType::TAKE_PROFIT_LIMIT, "TAKE_PROFIT_LIMIT"},
            {OrderType::LIMIT_MAKER, "LIMIT_MAKER"}};
        return map.value(type);
    }

    OrderType EnumConverter::stringToOrderType(const QString& typeStr)
    {
        static const QHash<QString, OrderType> map = {
            {"LIMIT", OrderType::LIMIT},
            {"MARKET", OrderType::MARKET},
            {"STOP_LOSS", OrderType::STOP_LOSS},
            {"STOP_LOSS_LIMIT", OrderType::STOP_LOSS_LIMIT},
            {"TAKE_PROFIT", OrderType::TAKE_PROFIT},
            {"TAKE_PROFIT_LIMIT", OrderType::TAKE_PROFIT_LIMIT},
            {"LIMIT_MAKER", OrderType::LIMIT_MAKER}};
        return map.value(typeStr, OrderType::LIMIT); // Default to LIMIT if not found
    }

    QString EnumConverter::orderResponseTypeToString(OrderResponseType type)
    {
        static const QHash<OrderResponseType, QString> map = {
            {OrderResponseType::ACK, "ACK"},
            {OrderResponseType::RESULT, "RESULT"},
            {OrderResponseType::FULL, "FULL"}};
        return map.value(type);
    }

    OrderResponseType EnumConverter::stringToOrderResponseType(const QString& typeStr)
    {
        static const QHash<QString, OrderResponseType> map = {
            {"ACK", OrderResponseType::ACK},
            {"RESULT", OrderResponseType::RESULT},
            {"FULL", OrderResponseType::FULL}};
        return map.value(typeStr, OrderResponseType::FULL); // Default to FULL if not found
    }

    QString EnumConverter::workingFloorToString(WorkingFloor floor)
    {
        static const QHash<WorkingFloor, QString> map = {
            {WorkingFloor::EXCHANGE, "EXCHANGE"},
            {WorkingFloor::SOR, "SOR"}};
        return map.value(floor);
    }

    WorkingFloor EnumConverter::stringToWorkingFloor(const QString& floorStr)
    {
        static const QHash<QString, WorkingFloor> map = {
            {"EXCHANGE", WorkingFloor::EXCHANGE},
            {"SOR", WorkingFloor::SOR}};
        return map.value(floorStr, WorkingFloor::EXCHANGE); // Default to EXCHANGE if not found
    }

    QString EnumConverter::orderSideToString(OrderSide side)
    {
        static const QHash<OrderSide, QString> map = {
            {OrderSide::BUY, "BUY"},
            {OrderSide::SELL, "SELL"}};
        return map.value(side);
    }

    OrderSide EnumConverter::stringToOrderSide(const QString& sideStr)
    {
        static const QHash<QString, OrderSide> map = {
            {"BUY", OrderSide::BUY},
            {"SELL", OrderSide::SELL}};
        return map.value(sideStr, OrderSide::BUY); // Default to BUY if not found
    }

    QString EnumConverter::timeInForceToString(TimeInForce tif)
    {
        static const QHash<TimeInForce, QString> map = {
            {TimeInForce::GTC, "GTC"},
            {TimeInForce::IOC, "IOC"},
            {TimeInForce::FOK, "FOK"}};
        return map.value(tif);
    }

    TimeInForce EnumConverter::stringToTimeInForce(const QString& tifStr)
    {
        static const QHash<QString, TimeInForce> map = {
            {"GTC", TimeInForce::GTC},
            {"IOC", TimeInForce::IOC},
            {"FOK", TimeInForce::FOK}};
        return map.value(tifStr, TimeInForce::GTC); // Default to GTC if not found
    }

    QString EnumConverter::rateLimitIntervalToString(RateLimitInterval interval)
    {
        static const QHash<RateLimitInterval, QString> map = {
            {RateLimitInterval::SECOND, "SECOND"},
            {RateLimitInterval::MINUTE, "MINUTE"},
            {RateLimitInterval::DAY, "DAY"}};
        return map.value(interval);
    }

    RateLimitInterval EnumConverter::stringToRateLimitInterval(const QString& intervalStr)
    {
        static const QHash<QString, RateLimitInterval> map = {
            {"SECOND", RateLimitInterval::SECOND},
            {"MINUTE", RateLimitInterval::MINUTE},
            {"DAY", RateLimitInterval::DAY}};
        return map.value(intervalStr, RateLimitInterval::SECOND); // Default to SECOND if not found
    }

    QString EnumConverter::rateLimitTypeToString(RateLimitType type)
    {
        static const QHash<RateLimitType, QString> map = {
            {RateLimitType::REQUEST_WEIGHT, "REQUEST_WEIGHT"},
            {RateLimitType::ORDERS, "ORDERS"},
            {RateLimitType::RAW_REQUESTS, "RAW_REQUESTS"}};
        return map.value(type);
    }

    RateLimitType EnumConverter::stringToRateLimitType(const QString& typeStr)
    {
        static const QHash<QString, RateLimitType> map = {
            {"REQUEST_WEIGHT", RateLimitType::REQUEST_WEIGHT},
            {"ORDERS", RateLimitType::ORDERS},
            {"RAW_REQUESTS", RateLimitType::RAW_REQUESTS}};
        return map.value(typeStr, RateLimitType::REQUEST_WEIGHT); // Default to REQUEST_WEIGHT if not found
    }

    QString EnumConverter::selfTradePreventionModeToString(SelfTradePreventionMode mode)
    {
        static const QHash<SelfTradePreventionMode, QString> map = {
            {SelfTradePreventionMode::NONE, "NONE"},
            {SelfTradePreventionMode::EXPIRE_MAKER, "EXPIRE_MAKER"},
            {SelfTradePreventionMode::EXPIRE_TAKER, "EXPIRE_TAKER"},
            {SelfTradePreventionMode::EXPIRE_BOTH, "EXPIRE_BOTH"},
            {SelfTradePreventionMode::DECREMENT, "DECREMENT"}};
        return map.value(mode);
    }

    SelfTradePreventionMode EnumConverter::stringToSelfTradePreventionMode(const QString& modeStr)
    {
        static const QHash<QString, SelfTradePreventionMode> map = {
            {"NONE", SelfTradePreventionMode::NONE},
            {"EXPIRE_MAKER", SelfTradePreventionMode::EXPIRE_MAKER},
            {"EXPIRE_TAKER", SelfTradePreventionMode::EXPIRE_TAKER},
            {"EXPIRE_BOTH", SelfTradePreventionMode::EXPIRE_BOTH},
            {"DECREMENT", SelfTradePreventionMode::DECREMENT}};
        return map.value(modeStr, SelfTradePreventionMode::NONE); // Default to NONE if not found
    }

} // namespace Binance
