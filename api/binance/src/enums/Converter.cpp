#pragma once

#include <QHash>
#include <QString>

#include "enums/Converter.h"

namespace Binance::Enum
{
    QString toString(SymbolStatus status)
    {
        static const QHash<SymbolStatus, QString> map = {
            {SymbolStatus::TRADING, "TRADING"},
            {SymbolStatus::END_OF_DAY, "END_OF_DAY"},
            {SymbolStatus::HALT, "HALT"},
            {SymbolStatus::BREAK, "BREAK"}};
        return map.value(status);
    }

    std::optional<SymbolStatus> toSymbolStatus(const QString &status)
    {
        static const QHash<QString, SymbolStatus> map = {
            {"TRADING", SymbolStatus::TRADING},
            {"END_OF_DAY", SymbolStatus::END_OF_DAY},
            {"HALT", SymbolStatus::HALT},
            {"BREAK", SymbolStatus::BREAK}};
        return map.value(status, {});
    }

    QString toString(AccountAndSymbolPermissions permission)
    {
        static const QHash<AccountAndSymbolPermissions, QString> map = {
            {AccountAndSymbolPermissions::SPOT, "SPOT"},
            {AccountAndSymbolPermissions::MARGIN, "MARGIN"}};
        return map.value(permission, {});
    }

    std::optional<AccountAndSymbolPermissions> toAccountAndSymbolPermissions(const QString &permission)
    {
        static const QHash<QString, AccountAndSymbolPermissions> map = {
            {"SPOT", AccountAndSymbolPermissions::SPOT},
            {"MARGIN", AccountAndSymbolPermissions::MARGIN}};
        return map.value(permission);
    }

    QString toString(OrderStatus status)
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

    std::optional<OrderStatus> toOrderStatus(const QString &status)
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
        return map.value(status, {});
    }

    QString toString(OrderListStatus status)
    {
        static const QHash<OrderListStatus, QString> map = {
            {OrderListStatus::RESPONSE, "RESPONSE"},
            {OrderListStatus::EXEC_STARTED, "EXEC_STARTED"},
            {OrderListStatus::UPDATED, "UPDATED"},
            {OrderListStatus::ALL_DONE, "ALL_DONE"}};
        return map.value(status);
    }

    std::optional<OrderListStatus> toOrderListStatus(const QString &status)
    {
        static const QHash<QString, OrderListStatus> map = {
            {"RESPONSE", OrderListStatus::RESPONSE},
            {"EXEC_STARTED", OrderListStatus::EXEC_STARTED},
            {"UPDATED", OrderListStatus::UPDATED},
            {"ALL_DONE", OrderListStatus::ALL_DONE}};
        return map.value(status, {});
    }

    QString toString(OrderListOrderStatus status)
    {
        static const QHash<OrderListOrderStatus, QString> map = {
            {OrderListOrderStatus::EXECUTING, "EXECUTING"},
            {OrderListOrderStatus::ALL_DONE, "ALL_DONE"},
            {OrderListOrderStatus::REJECT, "REJECT"}};
        return map.value(status);
    }

    std::optional<OrderListOrderStatus> toOrderListOrderStatus(const QString &status)
    {
        static const QHash<QString, OrderListOrderStatus> map = {
            {"EXECUTING", OrderListOrderStatus::EXECUTING},
            {"ALL_DONE", OrderListOrderStatus::ALL_DONE},
            {"REJECT", OrderListOrderStatus::REJECT}};
        return map.value(status, {});
    }

    QString toString(ContingencyType type)
    {
        static const QHash<ContingencyType, QString> map = {
            {ContingencyType::OCO, "OCO"},
            {ContingencyType::OTO, "OTO"}};
        return map.value(type);
    }

    std::optional<ContingencyType> toContingencyType(const QString &type)
    {
        static const QHash<QString, ContingencyType> map = {
            {"OCO", ContingencyType::OCO},
            {"OTO", ContingencyType::OTO}};
        return map.value(type, {});
    }

    QString toString(AllocationType type)
    {
        if (type == AllocationType::SOR) return "SOR";
        return QString();
    }

    std::optional<AllocationType> toAllocationType(const QString &type)
    {
        static const QHash<QString, AllocationType> map = {
            {"SOR", AllocationType::SOR}};
        return map.value(type, {});
    }

    QString toString(OrderType type)
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

    std::optional<OrderType> toOrderType(const QString &type)
    {
        static const QHash<QString, OrderType> map = {
            {"LIMIT", OrderType::LIMIT},
            {"MARKET", OrderType::MARKET},
            {"STOP_LOSS", OrderType::STOP_LOSS},
            {"STOP_LOSS_LIMIT", OrderType::STOP_LOSS_LIMIT},
            {"TAKE_PROFIT", OrderType::TAKE_PROFIT},
            {"TAKE_PROFIT_LIMIT", OrderType::TAKE_PROFIT_LIMIT},
            {"LIMIT_MAKER", OrderType::LIMIT_MAKER}};
        return map.value(type, {});
    }

    QString toString(OrderResponseType type)
    {
        static const QHash<OrderResponseType, QString> map = {
            {OrderResponseType::ACK, "ACK"},
            {OrderResponseType::RESULT, "RESULT"},
            {OrderResponseType::FULL, "FULL"}};
        return map.value(type);
    }

    std::optional<OrderResponseType> toOrderResponseType(const QString &type)
    {
        static const QHash<QString, OrderResponseType> map = {
            {"ACK", OrderResponseType::ACK},
            {"RESULT", OrderResponseType::RESULT},
            {"FULL", OrderResponseType::FULL}};
        return map.value(type, {});
    }

    QString toString(WorkingFloor floor)
    {
        static const QHash<WorkingFloor, QString> map = {
            {WorkingFloor::EXCHANGE, "EXCHANGE"},
            {WorkingFloor::SOR, "SOR"}};
        return map.value(floor);
    }

    std::optional<WorkingFloor> toWorkingFloor(const QString &floor)
    {
        static const QHash<QString, WorkingFloor> map = {
            {"EXCHANGE", WorkingFloor::EXCHANGE},
            {"SOR", WorkingFloor::SOR}};
        return map.value(floor, {});
    }

    QString toString(OrderSide side)
    {
        static const QHash<OrderSide, QString> map = {
            {OrderSide::BUY, "BUY"},
            {OrderSide::SELL, "SELL"}};
        return map.value(side);
    }

    std::optional<OrderSide> toOrderSide(const QString &side)
    {
        static const QHash<QString, OrderSide> map = {
            {"BUY", OrderSide::BUY},
            {"SELL", OrderSide::SELL}};
        return map.value(side, {});
    }

    QString toString(TimeInForce tif)
    {
        static const QHash<TimeInForce, QString> map = {
            {TimeInForce::GTC, "GTC"},
            {TimeInForce::IOC, "IOC"},
            {TimeInForce::FOK, "FOK"}};
        return map.value(tif);
    }

    std::optional<TimeInForce> toTimeInForce(const QString &tif)
    {
        static const QHash<QString, TimeInForce> map = {
            {"GTC", TimeInForce::GTC},
            {"IOC", TimeInForce::IOC},
            {"FOK", TimeInForce::FOK}};
        return map.value(tif, {});
    }

    QString toString(RateLimitInterval interval)
    {
        static const QHash<RateLimitInterval, QString> map = {
            {RateLimitInterval::SECOND, "SECOND"},
            {RateLimitInterval::MINUTE, "MINUTE"},
            {RateLimitInterval::DAY, "DAY"}};
        return map.value(interval);
    }

    std::optional<RateLimitInterval> toRateLimitInterval(const QString &interval)
    {
        static const QHash<QString, RateLimitInterval> map = {
            {"SECOND", RateLimitInterval::SECOND},
            {"MINUTE", RateLimitInterval::MINUTE},
            {"DAY", RateLimitInterval::DAY}};
        return map.value(interval, {});
    }

    QString toString(RateLimitType type)
    {
        static const QHash<RateLimitType, QString> map = {
            {RateLimitType::REQUEST_WEIGHT, "REQUEST_WEIGHT"},
            {RateLimitType::ORDERS, "ORDERS"},
            {RateLimitType::RAW_REQUESTS, "RAW_REQUESTS"}};
        return map.value(type);
    }

    std::optional<RateLimitType> toRateLimitType(const QString &type)
    {
        static const QHash<QString, RateLimitType> map = {
            {"REQUEST_WEIGHT", RateLimitType::REQUEST_WEIGHT},
            {"ORDERS", RateLimitType::ORDERS},
            {"RAW_REQUESTS", RateLimitType::RAW_REQUESTS}};
        return map.value(type, {});
    }

    QString toString(SelfTradePreventionMode mode)
    {
        static const QHash<SelfTradePreventionMode, QString> map = {
            {SelfTradePreventionMode::NONE, "NONE"},
            {SelfTradePreventionMode::EXPIRE_MAKER, "EXPIRE_MAKER"},
            {SelfTradePreventionMode::EXPIRE_TAKER, "EXPIRE_TAKER"},
            {SelfTradePreventionMode::EXPIRE_BOTH, "EXPIRE_BOTH"},
            {SelfTradePreventionMode::DECREMENT, "DECREMENT"}};
        return map.value(mode);
    }

    std::optional<SelfTradePreventionMode> toSelfTradePreventionMode(const QString &mode)
    {
        static const QHash<QString, SelfTradePreventionMode> map = {
            {"NONE", SelfTradePreventionMode::NONE},
            {"EXPIRE_MAKER", SelfTradePreventionMode::EXPIRE_MAKER},
            {"EXPIRE_TAKER", SelfTradePreventionMode::EXPIRE_TAKER},
            {"EXPIRE_BOTH", SelfTradePreventionMode::EXPIRE_BOTH},
            {"DECREMENT", SelfTradePreventionMode::DECREMENT}};
        return map.value(mode, {});
    }
    
    QString toString(PegPriceType type)
    {
        static const QHash<PegPriceType, QString> map = {
            {PegPriceType::PRIMARY_PEG, "PRIMARY_PEG"},
            {PegPriceType::MARKET_PEG, "MARKET_PEG"}};
        return map.value(type);
    }

    std::optional<PegPriceType> toPegPriceType(const QString &type)
    {
        static const QHash<QString, PegPriceType> map = {
            {"PRIMARY_PEG", PegPriceType::PRIMARY_PEG},
            {"MARKET_PEG", PegPriceType::MARKET_PEG}};
        return map.value(type, {});
    }
    
    QString toString(PegOffsetType type)
    {
        static const QHash<PegOffsetType, QString> map = {
            {PegOffsetType::PRICE_LEVEL, "PRICE_LEVEL"}};
        return map.value(type);
    }

    std::optional<PegOffsetType> toPegOffsetType(const QString &type)
    {
        static const QHash<QString, PegOffsetType> map = {
            {"PRICE_LEVEL", PegOffsetType::PRICE_LEVEL}};
        return map.value(type, {});
    }
} // namespace Binance::Enum
