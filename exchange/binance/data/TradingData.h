#pragma once

#include <optional>

#include <QList>
#include <QString>
#include <QVariant>

#include "../enums/Enums.h"
#include "../parsers/EnumConverter.h"
#include "../filters/Filters.h"

namespace Binance::TradingData
{
    struct OrderRequest
    {
        std::optional<QString> symbol;
        std::optional<OrderSide> side{};
        std::optional<OrderType> type{};
        std::optional<TimeInForce> timeInForce{};
        std::optional<double> quantity{};
        std::optional<double> quoteOrderQuantity{};
        std::optional<double> price{};
        std::optional<QString> newClientOrderId;
        std::optional<qint64> strategyId{};
        std::optional<int> strategyType{};
        std::optional<double> stopPrice{};
        std::optional<qint64> trailingDelta{};
        std::optional<double> icebergQty{};
        std::optional<OrderResponseType> newOrderRespType{};
        std::optional<SelfTradePreventionMode> selfTradePreventionMode{};
        std::optional<PegPriceType> pegPriceType{ PegPriceType::PRIMARY_PEG};
        std::optional<int> pegOffsetValue{};
        std::optional<PegOffsetType> pegOffsetType{ PegOffsetType::PRICE_LEVEL };
        std::optional<double> recvWindow{};
        std::optional<qint64> timestamp{};
    };

    QVariantMap toVariantMap(const OrderRequest &request)
    {
        QVariantMap params;

        if (request.symbol.has_value()) params["symbol"] = request.symbol.value();
        if (request.side.has_value()) params["side"] = static_cast<int>(request.side.value());
        if (request.type.has_value()) params["type"] = static_cast<int>(request.type.value());
        if (request.timeInForce.has_value()) params["timeInForce"] = Binance::Enum::toString(request.timeInForce.value());
        if (request.quantity.has_value()) params["quantity"] = request.quantity.value();
        if (request.quoteOrderQuantity.has_value()) params["quoteOrderQty"] = request.quoteOrderQuantity.value();
        if (request.price.has_value()) params["price"] = request.price.value();
        if (request.newClientOrderId.has_value()) params["newClientOrderId"] = request.newClientOrderId.value();
        if (request.strategyId.has_value()) params["strategyId"] = request.strategyId.value();
        if (request.strategyType.has_value()) params["strategyType"] = request.strategyType.value();
        if (request.stopPrice.has_value()) params["stopPrice"] = request.stopPrice.value();
        if (request.trailingDelta.has_value()) params["trailingDelta"] = request.trailingDelta.value();
        if (request.icebergQty.has_value()) params["icebergQty"] = request.icebergQty.value();
        if (request.newOrderRespType.has_value()) params["newOrderRespType"] = Binance::Enum::toString(request.newOrderRespType.value());
        if (request.selfTradePreventionMode.has_value()) params["selfTradePreventionMode"] = Binance::Enum::toString(request.selfTradePreventionMode.value());
        if (request.pegPriceType.has_value()) params["pegPriceType"] = Binance::Enum::toString(request.pegPriceType.value());
        if (request.pegOffsetValue.has_value()) params["pegOffsetValue"] = request.pegOffsetValue.value();
        if (request.pegOffsetType.has_value()) params["pegOffsetType"] = Binance::Enum::toString(request.pegOffsetType.value());
        if (request.recvWindow.has_value()) params["recvWindow"] = request.recvWindow.value();
        if (request.timestamp.has_value()) params["timestamp"] = request.timestamp.value();

        return params;
    }

    struct OrderACK
    {
        QString symbol;
        qint64 orderId{};
        int orderListId{};
        QString clientOrderId;
        qint64 transactTime{};
    };

    struct OrderResult
    {
        QString symbol;
        qint64 orderId{};
        int orderListId{};
        double price{};
        double origQty{};
        double executedQty{};
        double origQuoteOrderQty{};
        double cummulativeQuoteQty{};
        OrderStatus status{};
        TimeInForce timeInForce{};
        OrderType type{};
        OrderSide side{};
        qint64 workingTime{};
        SelfTradePreventionMode selfTradePreventionMode{};
    };

    struct OrderFill
    {
        double price{};
        double qty{};
        double commission{};
        QString commissionAsset;
        qint64 tradeId{};
    };

    struct OrderFull
    {
        QString symbol;
        qint64 orderId{};
        int orderListId{};
        double price{};
        double origQty{};
        double executedQty{};
        double origQuoteOrderQty{};
        double cummulativeQuoteQty{};
        OrderStatus status{};
        TimeInForce timeInForce{};
        OrderType type{};
        OrderSide side{};
        qint64 workingTime{};
        SelfTradePreventionMode selfTradePreventionMode{};
        QList<OrderFill> fills;

        // conditional fields
        std::optional<double> icebergQty{};
        std::optional<qint64> preventedMatchId{};
        std::optional<double> preventedQuantity{};
        std::optional<double> stopPrice{};
        std::optional<qint64> strategyId{};
        std::optional<int> strategyType{};
        std::optional<qint64> trailingDelta{};
        std::optional<qint64> trailingTime{};
        std::optional<bool> usedSor{};
        std::optional<WorkingFloor> workingFloor{};
        std::optional<PegPriceType> pegPriceType{};
        std::optional<PegOffsetType> pegOffsetType{};
        std::optional<int> pegOffsetValue{};
        std::optional<double> peggedPrice{};
    };
} // namespace Binance::TradingData
