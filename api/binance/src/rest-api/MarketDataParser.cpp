#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

#include "enums/Converter.h"
#include "filters/Converter.h"
#include "rest-api/MarketDataParser.h"

namespace Binance{
    std::optional<MarketData::OrderBook> MarketDataParser::parseOrderBook(const QJsonDocument &jsonDoc)
    {
        MarketData::OrderBook orderBook{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();
        
        // lastUpdateId
        if (!json.contains("lastUpdateId") || !json["lastUpdateId"].isDouble())
        {
            return {}; // lastUpdateId is required
        }
        orderBook.lastUpdateId = json["lastUpdateId"].toDouble();

        // bids: array of [price, quantity] pairs
        if (!json.contains("bids") || !json["bids"].isArray())
        {
            return {}; // bids is required
        }
        QJsonArray bidsArray = json["bids"].toArray();
        for (int i = 0; i < bidsArray.size(); ++i)
        {
            if (!bidsArray[i].isArray() || bidsArray[i].toArray().size() < 2)
            {
                continue; // skip malformed entries
            }
            QJsonArray bidPair = bidsArray[i].toArray();
            bool priceOk = false, qtyOk = false;
            double price = bidPair[0].toString().toDouble(&priceOk);
            double quantity = bidPair[1].toString().toDouble(&qtyOk);
            if (priceOk && qtyOk)
            {
                orderBook.bids.append(qMakePair(price, quantity));
            }
        }

        // asks: array of [price, quantity] pairs
        if (!json.contains("asks") || !json["asks"].isArray())
        {
            return {}; // asks is required
        }
        QJsonArray asksArray = json["asks"].toArray();
        for (int i = 0; i < asksArray.size(); ++i)
        {
            if (!asksArray[i].isArray() || asksArray[i].toArray().size() < 2)
            {
                continue; // skip malformed entries
            }
            QJsonArray askPair = asksArray[i].toArray();
            bool priceOk = false, qtyOk = false;
            double price = askPair[0].toString().toDouble(&priceOk);
            double quantity = askPair[1].toString().toDouble(&qtyOk);
            if (priceOk && qtyOk)
            {
                orderBook.asks.append(qMakePair(price, quantity));
            }
        }

        return orderBook;
    }

    std::optional<QList<MarketData::Trade>> MarketDataParser::parseTrades(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::Trade> trades;

        // json array
        if (!jsonDoc.isArray())
        {
            return {}; // invalid format
        }
        QJsonArray jsonArray = jsonDoc.array();

        for (int i = 0; i < jsonArray.size(); ++i)
        {
            if (!jsonArray[i].isObject())
            {
                continue; // skip malformed entries
            }
            QJsonObject tradeObj = jsonArray[i].toObject();
            MarketData::Trade trade{};

            // id
            if (!tradeObj.contains("id") && !tradeObj["id"].isDouble())
            {
                return {}; // id is required
            }
            trade.id = static_cast<qint64>(tradeObj["id"].toDouble());

            // price
            if (!tradeObj.contains("price") && !tradeObj["price"].isString())
            {
                return {}; // price is required
            }
            trade.price = tradeObj["price"].toString().toDouble();

            // qty
            if (!tradeObj.contains("qty") && !tradeObj["qty"].isString())
            {
                return {}; // qty is required
            }
            trade.qty = tradeObj["qty"].toString().toDouble();

            // quoteQty
            if (!tradeObj.contains("quoteQty") && !tradeObj["quoteQty"].isString())
            {
                return {}; // quoteQty is required
            }
            trade.quoteQty = tradeObj["quoteQty"].toString().toDouble();

            // time
            if (!tradeObj.contains("time") && !tradeObj["time"].isDouble())
            {
                return {}; // time is required
            }
            trade.time = tradeObj["time"].toString().toDouble();

            // isBuyerMaker
            if (!tradeObj.contains("isBuyerMaker") && !tradeObj["isBuyerMaker"].isBool())
            {
                return {}; // isBuyerMaker is required
            }
            trade.isBuyerMaker = tradeObj["isBuyerMaker"].toBool();

            // isBestMatch
            if (!tradeObj.contains("isBestMatch") && !tradeObj["isBestMatch"].isBool())
            {
                return {}; // isBestMatch is required
            }
            trade.isBestMatch = tradeObj["isBestMatch"].toBool();

            trades.append(trade);
        }

        return trades;
    }

    std::optional<QList<MarketData::AggregatedTrade>> MarketDataParser::parseAggregatedTrades(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::AggregatedTrade> aggTrades;

        // json array
        if (!jsonDoc.isArray())
        {
            return {}; // invalid format
        }
        QJsonArray jsonArray = jsonDoc.array();

        for (int i = 0; i < jsonArray.size(); ++i)
        {
            if (!jsonArray[i].isObject())
            {
                continue; // skip malformed entries
            }
            QJsonObject tradeObj = jsonArray[i].toObject();
            MarketData::AggregatedTrade trade{};

            // aggregate tradeId
            if (!tradeObj.contains("a") && !tradeObj["a"].isDouble())
            {
                return {}; // aggregate tradeId is required
            }
            trade.a = static_cast<qint64>(tradeObj["a"].toDouble());

            // price
            if (!tradeObj.contains("p") && !tradeObj["p"].isString())
            {
                return {}; // price is required
            }
            trade.p = tradeObj["p"].toString().toDouble();

            // quantity
            if (!tradeObj.contains("q") && !tradeObj["q"].isString())
            {
                return {}; // quantity is required
            }
            trade.q = tradeObj["q"].toString().toDouble();

            // first tradeId
            if (!tradeObj.contains("f") && !tradeObj["f"].isDouble())
            {
                return {}; // first tradeId is required
            }
            trade.f = static_cast<qint64>(tradeObj["f"].toDouble());

            // last tradeId
            if (!tradeObj.contains("l") && !tradeObj["l"].isDouble())
            {
                return {}; // last tradeId is required
            }
            trade.l = static_cast<qint64>(tradeObj["l"].toDouble());

            // timestamp
            if (!tradeObj.contains("T") && !tradeObj["T"].isDouble())
            {
                return {}; // timestamp is required
            }
            trade.T = static_cast<qint64>(tradeObj["T"].toDouble());

            // was the buyer the maker?
            if (!tradeObj.contains("m") && !tradeObj["m"].isBool())
            {
                return {}; // was the buyer the maker? is required
            }
            trade.m = tradeObj["m"].toBool();

            // was the trade the best price match?
            if (!tradeObj.contains("M") && !tradeObj["M"].isBool())
            {
                return {}; // was the trade the best price match? is required
            }
            trade.M = tradeObj["M"].toBool();

            aggTrades.append(trade);
        }

        return aggTrades;
    }

    std::optional<QList<MarketData::Kline>> MarketDataParser::parseKlines(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::Kline> klines;

        // json array
        if (!jsonDoc.isArray())
        {
            return {}; // invalid format
        }
        QJsonArray jsonArray = jsonDoc.array();

        for (int i = 0; i < jsonArray.size(); ++i)
        {
            if (!jsonArray[i].isArray())
            {
                continue; // skip malformed entries
            }
            QJsonArray klineArray = jsonArray[i].toArray();
            if (klineArray.size() < 12)
            {
                continue; // skip incomplete entries
            }
            MarketData::Kline kline{};

            kline.openTime = static_cast<qint64>(klineArray[0].toDouble());
            kline.open = klineArray[1].toString().toDouble();
            kline.high = klineArray[2].toString().toDouble();
            kline.low = klineArray[3].toString().toDouble();
            kline.close = klineArray[4].toString().toDouble();
            kline.volume = klineArray[5].toString().toDouble();
            kline.closeTime = static_cast<qint64>(klineArray[6].toDouble());
            kline.quoteAssetVolume = klineArray[7].toString().toDouble();
            kline.numberOfTrades = static_cast<qint64>(klineArray[8].toDouble());
            kline.takerBuyBaseAssetVolume = klineArray[9].toString().toDouble();
            kline.takerBuyQuoteAssetVolume = klineArray[10].toString().toDouble();
            // Ignore the 12th element (ignore)

            klines.append(kline);
        }

        return klines;
    }

    std::optional<QList<MarketData::UIKline>> MarketDataParser::parseUIKlines(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::UIKline> uiKlines;

        // json array
        if (!jsonDoc.isArray())
        {
            return {}; // invalid format
        }
        QJsonArray jsonArray = jsonDoc.array();

        for (int i = 0; i < jsonArray.size(); ++i)
        {
            if (!jsonArray[i].isArray())
            {
                continue; // skip malformed entries
            }
            QJsonArray klineArray = jsonArray[i].toArray();
            if (klineArray.size() < 12)
            {
                continue; // skip incomplete entries
            }
            MarketData::UIKline uiKline{};

            uiKline.openTime = static_cast<qint64>(klineArray[0].toDouble());
            uiKline.open = klineArray[1].toString().toDouble();
            uiKline.high = klineArray[2].toString().toDouble();
            uiKline.low = klineArray[3].toString().toDouble();
            uiKline.close = klineArray[4].toString().toDouble();
            uiKline.volume = klineArray[5].toString().toDouble();
            uiKline.closeTime = static_cast<qint64>(klineArray[6].toDouble());
            uiKline.quoteAssetVolume = klineArray[7].toString().toDouble();
            uiKline.numberOfTrades = static_cast<qint64>(klineArray[8].toDouble());
            uiKline.takerBuyBaseAssetVolume = klineArray[9].toString().toDouble();
            uiKline.takerBuyQuoteAssetVolume = klineArray[10].toString().toDouble();
            // Ignore the 12th element (ignore)

            uiKlines.append(uiKline);
        }

        return uiKlines;
    }

    std::optional<MarketData::CurrentAveragePrice> MarketDataParser::parseCurrentAveragePrice(const QJsonDocument &jsonDoc)
    {
        MarketData::CurrentAveragePrice avgPrice{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();

        // mins
        if (!json.contains("mins") || !json["mins"].isDouble())
        {
            return {}; // mins is required
        }
        avgPrice.interval = static_cast<int>(json["mins"].toDouble());

        // price
        if (!json.contains("price") || !json["price"].isString())
        {
            return {}; // price is required
        }
        avgPrice.price = json["price"].toString().toDouble();

        // closeTime
        if (!json.contains("closeTime") || !json["closeTime"].isDouble())
        {
            return {}; // closeTime is required
        }
        avgPrice.closeTime = static_cast<qint64>(json["closeTime"].toDouble());

        return avgPrice;
    }

    QList<MarketData::Ticker24hrFull> MarketDataParser::parseTicker24hrFull(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::Ticker24hrFull> tickers;

        // json can be either an object or an array (when multiple symbols are requested)
        if (jsonDoc.isObject())
        {
            auto maybeTicker = parseSymbolTicker24hrFull(jsonDoc);
            if (maybeTicker.has_value())            {
                tickers.append(maybeTicker.value());
            }
        }
        else if (jsonDoc.isArray())
        {
            const QJsonArray array = jsonDoc.array();
            if (array.isEmpty())
            {
                for(const auto& item : array)
                {
                    if(!item.isObject())
                    {
                        return {}; // invalid format
                    }
                    auto maybeTicker = parseSymbolTicker24hrFull(jsonDoc);
                    if (maybeTicker.has_value())            {
                        tickers.append(maybeTicker.value());
                    }
                }
            }
            else
            {
                return {}; // empty array is invalid
            }
        }
        else
        {
            return {}; // invalid format
        }

        return tickers;
    }

    std::optional<MarketData::Ticker24hrFull> MarketDataParser::parseSymbolTicker24hrFull(const QJsonDocument &jsonDoc)
    {
        MarketData::Ticker24hrFull ticker24hrFull{};
        QJsonObject json = jsonDoc.object();

        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        ticker24hrFull.symbol = json["symbol"].toString();

        // priceChange
        if (!json.contains("priceChange") || !json["priceChange"].isString())
        {
            return {}; // priceChange is required
        }
        ticker24hrFull.priceChange = json["priceChange"].toString().toDouble();

        // priceChangePercent
        if (!json.contains("priceChangePercent") || !json["priceChangePercent"].isString())
        {
            return {}; // priceChangePercent is required
        }
        ticker24hrFull.priceChangePercent = json["priceChangePercent"].toString().toDouble();

        // weightedAvgPrice
        if (!json.contains("weightedAvgPrice") || !json["weightedAvgPrice"].isString())
        {
            return {}; // weightedAvgPrice is required
        }
        ticker24hrFull.weightedAvgPrice = json["weightedAvgPrice"].toString().toDouble();

        // prevClosePrice
        if (!json.contains("prevClosePrice") || !json["prevClosePrice"].isString())
        {
            return {}; // prevClosePrice is required
        }
        ticker24hrFull.prevClosePrice = json["prevClosePrice"].toString().toDouble();

        // lastPrice
        if (!json.contains("lastPrice") || !json["lastPrice"].isString())
        {
            return {}; // lastPrice is required
        }
        ticker24hrFull.lastPrice = json["lastPrice"].toString().toDouble();

        // lastQty
        if (!json.contains("lastQty") || !json["lastQty"].isString())
        {
            return {}; // lastQty is required
        }
        ticker24hrFull.lastQty = json["lastQty"].toString().toDouble();

        // bidPrice
        if (!json.contains("bidPrice") || !json["bidPrice"].isString())
        {
            return {}; // bidPrice is required
        }
        ticker24hrFull.bidPrice = json["bidPrice"].toString().toDouble();

        // bidQty
        if (!json.contains("bidQty") || !json["bidQty"].isString())
        {
            return {}; // bidQty is required
        }
        ticker24hrFull.bidQty = json["bidQty"].toString().toDouble();

        // askPrice
        if (!json.contains("askPrice") || !json["askPrice"].isString())
        {
            return {}; // askPrice is required
        }
        ticker24hrFull.askPrice = json["askPrice"].toString().toDouble();

        // askQty
        if (!json.contains("askQty") || !json["askQty"].isString())
        {
            return {}; // askQty is required
        }
        ticker24hrFull.askQty = json["askQty"].toString().toDouble();

        // openPrice
        if (!json.contains("openPrice") || !json["openPrice"].isString())
        {
            return {}; // openPrice is required
        }
        ticker24hrFull.openPrice = json["openPrice"].toString().toDouble();

        // highPrice
        if (!json.contains("highPrice") || !json["highPrice"].isString())
        {
            return {}; // highPrice is required
        }
        ticker24hrFull.highPrice = json["highPrice"].toString().toDouble();

        // lowPrice
        if (!json.contains("lowPrice") || !json["lowPrice"].isString())
        {
            return {}; // lowPrice is required
        }
        ticker24hrFull.lowPrice = json["lowPrice"].toString().toDouble();

        // volume
        if (!json.contains("volume") || !json["volume"].isString())
        {
            return {}; // volume is required
        }
        ticker24hrFull.volume = json["volume"].toString().toDouble();

        // quoteVolume
        if (!json.contains("quoteVolume") || !json["quoteVolume"].isString())
        {
            return {}; // quoteVolume is required
        }
        ticker24hrFull.quoteVolume = json["quoteVolume"].toString().toDouble();

        // openTime
        if (!json.contains("openTime") || !json["openTime"].isDouble())
        {
            return {}; // openTime is required
        }
        ticker24hrFull.openTime = static_cast<qint64>(json["openTime"].toDouble());

        // closeTime
        if (!json.contains("closeTime") || !json["closeTime"].isDouble())
        {
            return {}; // closeTime is required
        }
        ticker24hrFull.closeTime = static_cast<qint64>(json["closeTime"].toDouble());

        // firstId
        if (!json.contains("firstId") || !json["firstId"].isDouble())
        {
            return {}; // firstId is required
        }
        ticker24hrFull.firstId = static_cast<qint64>(json["firstId"].toDouble());

        // lastId
        if (!json.contains("lastId") || !json["lastId"].isDouble())
        {
            return {}; // lastId is required
        }
        ticker24hrFull.lastId = static_cast<qint64>(json["lastId"].toDouble());

        // count
        if (!json.contains("count") || !json["count"].isDouble())
        {
            return {}; // count is required
        }
        ticker24hrFull.count = static_cast<qint64>(json["count"].toDouble());

        return ticker24hrFull;
    }

    QList<MarketData::Ticker24hrMini> MarketDataParser::parseTicker24hrMini(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::Ticker24hrMini> tickers;

        // json can be either an object or an array (when multiple symbols are requested)
        if (jsonDoc.isObject())
        {
            auto maybeTicker = parseSymbolTicker24hrMini(jsonDoc);
            if (maybeTicker.has_value())            {
                tickers.append(maybeTicker.value());
            }
        }
        else if (jsonDoc.isArray())
        {
            const QJsonArray array = jsonDoc.array();
            if (array.isEmpty())
            {
                for(const auto& item : array)
                {
                    if(!item.isObject())
                    {
                        return {}; // invalid format
                    }
                    auto maybeTicker = parseSymbolTicker24hrMini(jsonDoc);
                    if (maybeTicker.has_value())            {
                        tickers.append(maybeTicker.value());
                    }
                }
            }
            else
            {
                return {}; // empty array is invalid
            }
        }
        else
        {
            return {}; // invalid format
        }

        return tickers;
    }

    std::optional<MarketData::Ticker24hrMini> MarketDataParser::parseSymbolTicker24hrMini(const QJsonDocument &jsonDoc)
    {
        MarketData::Ticker24hrMini ticker24hrMini{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();

        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        ticker24hrMini.symbol = json["symbol"].toString();

        // openPrice
        if (!json.contains("openPrice") || !json["openPrice"].isString())
        {
            return {}; // openPrice is required
        }
        ticker24hrMini.openPrice = json["openPrice"].toString().toDouble();

        // highPrice
        if (!json.contains("highPrice") || !json["highPrice"].isString())
        {
            return {}; // highPrice is required
        }
        ticker24hrMini.highPrice = json["highPrice"].toString().toDouble();

        // lowPrice
        if (!json.contains("lowPrice") || !json["lowPrice"].isString())
        {
            return {}; // lowPrice is required
        }
        ticker24hrMini.lowPrice = json["lowPrice"].toString().toDouble();

        // lastPrice
        if (!json.contains("lastPrice") || !json["lastPrice"].isString())
        {
            return {}; // lastPrice is required
        }
        ticker24hrMini.lastPrice = json["lastPrice"].toString().toDouble();

        // volume
        if (!json.contains("volume") || !json["volume"].isString())
        {
            return {}; // volume is required
        }
        ticker24hrMini.volume = json["volume"].toString().toDouble();

        // quoteVolume
        if (!json.contains("quoteVolume") || !json["quoteVolume"].isString())
        {
            return {}; // quoteVolume is required
        }
        ticker24hrMini.quoteVolume = json["quoteVolume"].toString().toDouble();

        // openTime
        if (!json.contains("openTime") || !json["openTime"].isDouble())
        {
            return {}; // openTime is required
        }
        ticker24hrMini.openTime = static_cast<qint64>(json["openTime"].toDouble());

        // closeTime
        if (!json.contains("closeTime") || !json["closeTime"].isDouble())
        {
            return {}; // closeTime is required
        }
        ticker24hrMini.closeTime = static_cast<qint64>(json["closeTime"].toDouble());

        // firstId
        if (!json.contains("firstId") || !json["firstId"].isDouble())
        {
            return {}; // firstId is required
        }
        ticker24hrMini.firstId = static_cast<qint64>(json["firstId"].toDouble());

        // lastId
        if (!json.contains("lastId") || !json["lastId"].isDouble())
        {
            return {}; // lastId is required
        }
        ticker24hrMini.lastId = static_cast<qint64>(json["lastId"].toDouble());

        // count
        if (!json.contains("count") || !json["count"].isDouble())
        {
            return {}; // count is required
        }
        ticker24hrMini.count = static_cast<qint64>(json["count"].toDouble());

        return ticker24hrMini;
    }

    QList<MarketData::TradingDayFull> MarketDataParser::parseTradingDayFull(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::TradingDayFull> tradingDayFull;

        // json can be either an object or an array (when multiple symbols are requested)
        if (jsonDoc.isObject())
        {
            auto maybeTradingDayFull = parseSymbolTradingDayFull(jsonDoc);
            if (maybeTradingDayFull.has_value()) {
                tradingDayFull.append(maybeTradingDayFull.value());
            }
        }
        else if (jsonDoc.isArray())
        {
            const QJsonArray array = jsonDoc.array();
            if (array.isEmpty())
            {
                for(const auto& item : array)
                {
                    if(!item.isObject())
                    {
                        return {}; // invalid format
                    }
                    auto maybeTradingDayFull = parseSymbolTradingDayFull(jsonDoc);
                    if (maybeTradingDayFull.has_value()) {
                        tradingDayFull.append(maybeTradingDayFull.value());
                    }
                }
            }
            else
            {
                return {}; // empty array is invalid
            }
        }
        else
        {
            return {}; // invalid format
        }

        return tradingDayFull;
    }

    std::optional<MarketData::TradingDayFull> MarketDataParser::parseSymbolTradingDayFull(const QJsonDocument &jsonDoc)
    {
        MarketData::TradingDayFull tradingDayFull{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();

        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        tradingDayFull.symbol = json["symbol"].toString();

        // priceChange
        if (!json.contains("priceChange") || !json["priceChange"].isString())
        {
            return {}; // priceChange is required
        }
        tradingDayFull.priceChange = json["priceChange"].toString().toDouble();

        // priceChangePercent
        if (!json.contains("priceChangePercent") || !json["priceChangePercent"].isString())
        {
            return {}; // priceChangePercent is required
        }
        tradingDayFull.priceChangePercent = json["priceChangePercent"].toString().toDouble();

        // weightedAvgPrice
        if (!json.contains("weightedAvgPrice") || !json["weightedAvgPrice"].isString())
        {
            return {}; // weightedAvgPrice is required
        }
        tradingDayFull.weightedAvgPrice = json["weightedAvgPrice"].toString().toDouble();

        // openPrice
        if (!json.contains("openPrice") || !json["openPrice"].isString())
        {
            return {}; // openPrice is required
        }
        tradingDayFull.openPrice = json["openPrice"].toString().toDouble();

        // highPrice
        if (!json.contains("highPrice") || !json["highPrice"].isString())
        {
            return {}; // highPrice is required
        }
        tradingDayFull.highPrice = json["highPrice"].toString().toDouble();

        // lowPrice
        if (!json.contains("lowPrice") || !json["lowPrice"].isString())
        {
            return {}; // lowPrice is required
        }
        tradingDayFull.lowPrice = json["lowPrice"].toString().toDouble();

        // lastPrice
        if (!json.contains("lastPrice") || !json["lastPrice"].isString())
        {
            return {}; // lastPrice is required
        }
        tradingDayFull.lastPrice = json["lastPrice"].toString().toDouble();

        // volume
        if (!json.contains("volume") || !json["volume"].isString())
        {
            return {}; // volume is required
        }
        tradingDayFull.volume = json["volume"].toString().toDouble();

        // quoteVolume
        if (!json.contains("quoteVolume") || !json["quoteVolume"].isString())
        {
            return {}; // quoteVolume is required
        }
        tradingDayFull.quoteVolume = json["quoteVolume"].toString().toDouble();

        // openTime
        if (!json.contains("openTime") || !json["openTime"].isDouble())
        {
            return {}; // openTime is required
        }
        tradingDayFull.openTime = static_cast<qint64>(json["openTime"].toDouble());

        // closeTime
        if (!json.contains("closeTime") || !json["closeTime"].isDouble())
        {
            return {}; // closeTime is required
        }
        tradingDayFull.closeTime = static_cast<qint64>(json["closeTime"].toDouble());

        // firstId
        if (!json.contains("firstId") || !json["firstId"].isDouble())
        {
            return {}; // firstId is required
        }
        tradingDayFull.firstId = static_cast<qint64>(json["firstId"].toDouble());

        // lastId
        if (!json.contains("lastId") || !json["lastId"].isDouble())
        {
            return {}; // lastId is required
        }
        tradingDayFull.lastId = static_cast<qint64>(json["lastId"].toDouble());

        // count
        if (!json.contains("count") || !json["count"].isDouble())
        {
            return {}; // count is required
        }
        tradingDayFull.count = static_cast<qint64>(json["count"].toDouble());

        return tradingDayFull;
    }

    QList<MarketData::TradingDayMini> MarketDataParser::parseTradingDayMini(const QJsonDocument &jsonDoc)
    {
        QList<MarketData::TradingDayMini> tradingDayMini;

        // json can be either an object or an array (when multiple symbols are requested)
        if (jsonDoc.isObject())
        {
            auto maybeTradingDayMini = parseSymbolTradingDayMini(jsonDoc);
            if (maybeTradingDayMini.has_value()) {
                tradingDayMini.append(maybeTradingDayMini.value());
            }
        }
        else if (jsonDoc.isArray())
        {
            const QJsonArray array = jsonDoc.array();
            if (array.isEmpty())
            {
                for(const auto& item : array)
                {
                    if(!item.isObject())
                    {
                        return {}; // invalid format
                    }
                    auto maybeTradingDayMini = parseSymbolTradingDayMini(jsonDoc);
                    if (maybeTradingDayMini.has_value()) {
                        tradingDayMini.append(maybeTradingDayMini.value());
                    }
                }
            }
            else
            {
                return {}; // empty array is invalid
            }
        }
        else
        {
            return {}; // invalid format
        }

        return tradingDayMini;
    }

    std::optional<MarketData::TradingDayMini> MarketDataParser::parseSymbolTradingDayMini(const QJsonDocument &jsonDoc)
    {
        MarketData::TradingDayMini tradingDayMini{};
    
        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();

        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        tradingDayMini.symbol = json["symbol"].toString();

        // openPrice
        if (!json.contains("openPrice") || !json["openPrice"].isString())
        {
            return {}; // openPrice is required
        }
        tradingDayMini.openPrice = json["openPrice"].toString().toDouble();
        
        // highPrice
        if (!json.contains("highPrice") || !json["highPrice"].isString())
        {
            return {}; // highPrice is required
        }
        tradingDayMini.highPrice = json["highPrice"].toString().toDouble();
        
        // lowPrice
        if (!json.contains("lowPrice") || !json["lowPrice"].isString())
        {
            return {}; // lowPrice is required
        }
        tradingDayMini.lowPrice = json["lowPrice"].toString().toDouble();
        
        // lastPrice
        if (!json.contains("lastPrice") || !json["lastPrice"].isString())
        {
            return {}; // lastPrice is required
        }
        tradingDayMini.lastPrice = json["lastPrice"].toString().toDouble();

        // volume
        if (!json.contains("volume") || !json["volume"].isString())
        {
            return {}; // volume is required
        }
        tradingDayMini.volume = json["volume"].toString().toDouble();

        // quoteVolume
        if (!json.contains("quoteVolume") || !json["quoteVolume"].isString())
        {
            return {}; // quoteVolume is required
        }
        tradingDayMini.quoteVolume = json["quoteVolume"].toString().toDouble();

        // openTime
        if (!json.contains("openTime") || !json["openTime"].isDouble())
        {
            return {}; // openTime is required
        }
        tradingDayMini.openTime = static_cast<qint64>(json["openTime"].toDouble());

        // closeTime
        if (!json.contains("closeTime") || !json["closeTime"].isDouble())
        {
            return {}; // closeTime is required
        }
        tradingDayMini.closeTime = static_cast<qint64>(json["closeTime"].toDouble());

        // firstId
        if (!json.contains("firstId") || !json["firstId"].isDouble())
        {
            return {}; // firstId is required
        }
        tradingDayMini.firstId = static_cast<qint64>(json["firstId"].toDouble());

        // lastId
        if (!json.contains("lastId") || !json["lastId"].isDouble())
        {
            return {}; // lastId is required
        }
        tradingDayMini.lastId = static_cast<qint64>(json["lastId"].toDouble());

        // count
        if (!json.contains("count") || !json["count"].isDouble())
        {
            return {}; // count is required
        }
        tradingDayMini.count = static_cast<qint64>(json["count"].toDouble());

        return tradingDayMini;
    }

    std::optional<MarketData::SymbolPriceTicker> MarketDataParser::parseSymbolPriceTickerResponse(const QJsonDocument &jsonDoc){
        MarketData::SymbolPriceTicker symbolPriceTicker{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();
        
        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        symbolPriceTicker.symbol = json["symbol"].toString();

        // price
        if (!json.contains("price") || !json["price"].isString())
        {
            return {}; // price is required
        }
        symbolPriceTicker.price = json["price"].toString().toDouble();

        return symbolPriceTicker;
    }

    std::optional<MarketData::SymbolOrderBookTicker> MarketDataParser::parseSymbolOrderBookTickerResponse(const QJsonDocument &jsonDoc){
        MarketData::SymbolOrderBookTicker symbolOrderBookTicker{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();

        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        symbolOrderBookTicker.symbol = json["symbol"].toString();

        // bidPrice
        if (!json.contains("bidPrice") || !json["bidPrice"].isString())
        {
            return {}; // bidPrice is required
        }
        symbolOrderBookTicker.bidPrice = json["bidPrice"].toString().toDouble();

        // bidQty
        if (!json.contains("bidQty") || !json["bidQty"].isString())
        {
            return {}; // bidQty is required
        }
        symbolOrderBookTicker.bidQty = json["bidQty"].toString().toDouble();

        // askPrice
        if (!json.contains("askPrice") || !json["askPrice"].isString())
        {
            return {}; // askPrice is required
        }
        symbolOrderBookTicker.askPrice = json["askPrice"].toString().toDouble();

        // askQty
        if (!json.contains("askQty") || !json["askQty"].isString())
        {
            return {}; // askQty is required
        }
        symbolOrderBookTicker.askQty = json["askQty"].toString().toDouble();

        return symbolOrderBookTicker;
    }

    std::optional<MarketData::TickerFull> MarketDataParser::parseRollingWindowTickerResponseFull(const QJsonDocument &jsonDoc){
        MarketData::TickerFull tickerFull{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();

        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        tickerFull.symbol = json["symbol"].toString();

        // priceChange
        if (!json.contains("priceChange") || !json["priceChange"].isString())
        {
            return {}; // priceChange is required
        }
        tickerFull.priceChange = json["priceChange"].toString().toDouble();

        // priceChangePercent
        if (!json.contains("priceChangePercent") || !json["priceChangePercent"].isString())
        {
            return {}; // priceChangePercent is required
        }
        tickerFull.priceChangePercent = json["priceChangePercent"].toString().toDouble();

        // weightedAvgPrice
        if (!json.contains("weightedAvgPrice") || !json["weightedAvgPrice"].isString())
        {
            return {}; // weightedAvgPrice is required
        }
        tickerFull.weightedAvgPrice = json["weightedAvgPrice"].toString().toDouble();

        // openPrice
        if (!json.contains("openPrice") || !json["openPrice"].isString())
        {
            return {}; // openPrice is required
        }
        tickerFull.openPrice = json["openPrice"].toString().toDouble();

        // highPrice
        if (!json.contains("highPrice") || !json["highPrice"].isString())
        {
            return {}; // highPrice is required
        }
        tickerFull.highPrice = json["highPrice"].toString().toDouble();

        // lowPrice
        if (!json.contains("lowPrice") || !json["lowPrice"].isString())
        {
            return {}; // lowPrice is required
        }
        tickerFull.lowPrice = json["lowPrice"].toString().toDouble();

        // lastPrice
        if (!json.contains("lastPrice") || !json["lastPrice"].isString())
        {
            return {}; // lastPrice is required
        }
        tickerFull.lastPrice = json["lastPrice"].toString().toDouble();
        
        // volume
        if (!json.contains("volume") || !json["volume"].isString())
        {
            return {}; // volume is required
        }
        tickerFull.volume = json["volume"].toString().toDouble();

        // quoteVolume
        if (!json.contains("quoteVolume") || !json["quoteVolume"].isString())
        {
            return {}; // quoteVolume is required
        }
        tickerFull.quoteVolume = json["quoteVolume"].toString().toDouble();
        
        // openTime
        if (!json.contains("openTime") || !json["openTime"].isDouble())
        {
            return {}; // openTime is required
        }
        tickerFull.openTime = static_cast<qint64>(json["openTime"].toDouble());

        // closeTime
        if (!json.contains("closeTime") || !json["closeTime"].isDouble())
        {
            return {}; // closeTime is required
        }
        tickerFull.closeTime = static_cast<qint64>(json["closeTime"].toDouble());

        // firstId
        if (!json.contains("firstId") || !json["firstId"].isDouble())
        {
            return {}; // firstId is required
        }
        tickerFull.firstId = static_cast<qint64>(json["firstId"].toDouble());
        
        // lastId
        if (!json.contains("lastId") || !json["lastId"].isDouble())
        {
            return {}; // lastId is required
        }
        tickerFull.lastId = static_cast<qint64>(json["lastId"].toDouble());

        // count
        if (!json.contains("count") || !json["count"].isDouble())
        {
            return {}; // count is required
        }
        tickerFull.count = static_cast<qint64>(json["count"].toDouble());
        
        return tickerFull;
    }

    std::optional<MarketData::TickerMini> MarketDataParser::parseRollingWindowTickerResponseMini(const QJsonDocument &jsonDoc){
        MarketData::TickerMini tickerMini{};

        // json object
        if (!jsonDoc.isObject())
        {
            return {}; // invalid format
        }
        QJsonObject json = jsonDoc.object();

        // symbol
        if (!json.contains("symbol") || !json["symbol"].isString())
        {
            return {}; // symbol is required
        }
        tickerMini.symbol = json["symbol"].toString();

        // openPrice
        if (!json.contains("openPrice") || !json["openPrice"].isString())
        {
            return {}; // openPrice is required
        }
        tickerMini.openPrice = json["openPrice"].toString().toDouble();

        // highPrice
        if (!json.contains("highPrice") || !json["highPrice"].isString())
        {
            return {}; // highPrice is required
        }
        tickerMini.highPrice = json["highPrice"].toString().toDouble();

        // lowPrice
        if (!json.contains("lowPrice") || !json["lowPrice"].isString())
        {
            return {}; // lowPrice is required
        }
        tickerMini.lowPrice = json["lowPrice"].toString().toDouble();

        // lastPrice
        if (!json.contains("lastPrice") || !json["lastPrice"].isString())
        {
            return {}; // lastPrice is required
        }
        tickerMini.lastPrice = json["lastPrice"].toString().toDouble();

        // volume
        if (!json.contains("volume") || !json["volume"].isString())
        {
            return {}; // volume is required
        }
        tickerMini.volume = json["volume"].toString().toDouble();

        // quoteVolume
        if (!json.contains("quoteVolume") || !json["quoteVolume"].isString())
        {
            return {}; // quoteVolume is required
        }
        tickerMini.quoteVolume = json["quoteVolume"].toString().toDouble();

        // openTime
        if (!json.contains("openTime") || !json["openTime"].isDouble())
        {
            return {}; // openTime is required
        }
        tickerMini.openTime = static_cast<qint64>(json["openTime"].toDouble());

        // closeTime
        if (!json.contains("closeTime") || !json["closeTime"].isDouble())
        {
            return {}; // closeTime is required
        }
        tickerMini.closeTime = static_cast<qint64>(json["closeTime"].toDouble());

        // firstId
        if (!json.contains("firstId") || !json["firstId"].isDouble())
        {
            return {}; // firstId is required
        }
        tickerMini.firstId = static_cast<qint64>(json["firstId"].toDouble());

        // lastId
        if (!json.contains("lastId") || !json["lastId"].isDouble())
        {
            return {}; // lastId is required
        }
        tickerMini.lastId = static_cast<qint64>(json["lastId"].toDouble());

        // count
        if (!json.contains("count") || !json["count"].isDouble())
        {
            return {}; // count is required
        }
        tickerMini.count = static_cast<qint64>(json["count"].toDouble());

        return tickerMini;
    }
}
