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
}
