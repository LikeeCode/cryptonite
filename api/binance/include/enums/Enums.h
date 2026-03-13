#pragma once

namespace Binance
{

    // See: https://github.com/binance/binance-spot-api-docs/blob/master/testnet/enums.md

    enum class SymbolStatus
    {
        TRADING,
        END_OF_DAY,
        HALT,
        BREAK
    };

    enum class AccountAndSymbolPermissions
    {
        SPOT,
        MARGIN
    };

    enum class OrderStatus
    {
        NEW,
        PENDING_NEW,
        PARTIALLY_FILLED,
        FILLED,
        CANCELED,
        PENDING_CANCEL,
        REJECTED,
        EXPIRED,
        EXPIRED_IN_MATCH
    };

    enum class OrderListStatus
    {
        RESPONSE,
        EXEC_STARTED,
        UPDATED,
        ALL_DONE
    };

    enum class OrderListOrderStatus
    {
        EXECUTING,
        ALL_DONE,
        REJECT
    };

    enum class ContingencyType
    {
        OCO,
        OTO
    };

    enum class AllocationType
    {
        SOR
    };

    enum class OrderType
    {
        LIMIT,
        MARKET,
        STOP_LOSS,
        STOP_LOSS_LIMIT,
        TAKE_PROFIT,
        TAKE_PROFIT_LIMIT,
        LIMIT_MAKER
    };

    enum class OrderResponseType
    {
        ACK,
        RESULT,
        FULL
    };

    enum class WorkingFloor
    {
        EXCHANGE,
        SOR
    };

    enum class OrderSide
    {
        BUY,
        SELL
    };

    enum class TimeInForce
    {
        GTC, // Good Til Canceled
        IOC, // Immediate Or Cancel
        FOK  // Fill or Kill
    };

    enum class RateLimitInterval
    {
        SECOND,
        MINUTE,
        DAY
    };

    enum class RateLimitType
    {
        REQUEST_WEIGHT,
        ORDERS,
        RAW_REQUESTS
    };

    enum class SelfTradePreventionMode
    {
        NONE,
        EXPIRE_MAKER,
        EXPIRE_TAKER,
        EXPIRE_BOTH,
        DECREMENT
    };

    enum class Interval
    {
        ONE_SECOND,
        ONE_MINUTE,
        THREE_MINUTES,
        FIVE_MINUTES,
        FIFTEEN_MINUTES,
        THIRTY_MINUTES,
        ONE_HOUR,
        TWO_HOURS,
        FOUR_HOURS,
        SIX_HOURS,
        EIGHT_HOURS,
        TWELVE_HOURS,
        ONE_DAY,
        THREE_DAYS,
        ONE_WEEK,
        ONE_MONTH
    };

    enum class ResponseType
    {
        FULL,
        MINI
    };

    enum class PegPriceType
    {
        PRIMARY_PEG,
        MARKET_PEG
    };

    enum class PegOffsetType
    {
        PRICE_LEVEL
    };

} // namespace Binance
