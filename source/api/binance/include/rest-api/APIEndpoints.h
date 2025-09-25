#pragma once

#include <QString>

#include "enums/Enums.h"

namespace Binance::API
{
    const QString BASE_URL = "https://api.binance.com";
    const QString BASE_URL_TESTNET = "https://testnet.binance.vision";

    // General endpoints
    const QString PING = "/api/v3/ping";
    const QString TIME = "/api/v3/time";
    const QString EXCHANGE_INFO = "/api/v3/exchangeInfo";

    // Market Data endpoints
    const QString DEPTH = "/api/v3/depth";
    const QString TRADES = "/api/v3/trades";
    const QString HISTORICAL_TRADES = "/api/v3/historicalTrades";
    const QString AGG_TRADES = "/api/v3/aggTrades";
    const QString KLINES = "/api/v3/klines";
    const QString UI_KLINES = "/api/v3/uiKlines";
    const QString AVG_PRICE = "/api/v3/avgPrice";
    const QString TICKER_24HR = "/api/v3/ticker/24hr";
    const QString TRADING_DAY = "/api/v3/ticker/tradingDay";
    const QString PRICE_TICKER = "/api/v3/ticker/price";
    const QString BOOK_TICKER = "/api/v3/ticker/bookTicker";
    const QString ROLLING_WINDOW_TICKER = "/api/v3/ticker";

    // Trading endpoints
    const QString NEW_ORDER = "/api/v3/order";
    const QString TEST_NEW_ORDER = "/api/v3/order/test";
    const QString QUERY_ORDER = "/api/v3/order";
    const QString CANCEL_ORDER = "/api/v3/order"; // DELETE
    const QString CANCEL_ALL_OPEN_ORDERS = "/api/v3/openOrders"; // DELETE
    const QString CANCEL_REPLACE_ORDER = "/api/v3/order/cancelReplace";
    const QString KEEP_PRIORITY = "/api/v3/order/amend/keepPriority"; // PUT
    const QString ORDER_LISTS = "/api/v3/orderList/oco";
    const QString NEW_ORDER_LIST_OTO = "/api/v3/orderList/oto";
    const QString NEW_ORDER_LIST_OTOCO = "/api/v3/orderList/otoco";
    const QString CANCEL_ORDER_LIST = "/api/v3/orderList"; // DELETE
    const QString NEW_ORDER_SOR = "/api/v3/sor/order";
    const QString TEST_NEW_ORDER_SOR = "/api/v3/sor/order/test";

    // Account endpoints
    const QString ACCOUNT = "/api/v3/account"; // GET
    const QString OPEN_ORDERS = "/api/v3/openOrders"; // GET
    const QString ALL_ORDERS = "/api/v3/allOrders"; // GET
    const QString ORDER_LIST = "/api/v3/orderList"; // GET
    const QString ALL_ORDER_LIST = "/api/v3/allOrderList"; // GET
    const QString OPEN_ORDER_LIST = "/api/v3/openOrderList"; // GET
    const QString MY_TRADES = "/api/v3/myTrades"; // GET
    const QString UNFILLED_ORDER_COUNT = "/api/v3/rateLimit/order"; // GET
    const QString PREVENTED_MATCHES = "/api/v3/myPreventedMatches"; // GET
    const QString ALLOCATIONS = "/api/v3/myAllocations"; // GET
    const QString COMISSION_RATES = "/api/v3/account/commission"; // GET
    const QString ORDER_AMENDMENTS = "/api/v3/order/amendments"; // GET

    // User Data Stream endpoints
    const QString USER_DATA_STREAM = "/api/v3/userDataStream"; // POST
    const QString KEEP_ALIVE_USER_DATA_STREAM = "/api/v3/userDataStream"; // PUT
    const QString CLOSE_USER_DATA_STREAM = "/api/v3/userDataStream"; // DELETE
} // namespace Binance::API
