#pragma once

#include <QList>
#include <QString>
#include <QVariant>

#include "enums/Enums.h"
#include "filters/Filters.h"

namespace Binance::TradingData{
    struct OrderRequest{
        QString symbol;
        OrderSide side{};
        OrderType type{};
        TimeInForce timeInForce{};
        double quantity{};
        double quoteOrderQuantity{};
        double price{};
        QString newClientOrderId;
        qint64 strategyId{};
        int strategyType{};
        double stopPrice{};
        qint64 trailingDelta{};
        double icebergQty{};
        OrderResponseType newOrderRespType{};
        SelfTradePreventionMode selfTradePreventionMode{};
        // pegPriceType
        int pegOffsetValue{};
        // pegOffsetType
        double recvWindow{};
        qint64 timestamp{};
    };
}
