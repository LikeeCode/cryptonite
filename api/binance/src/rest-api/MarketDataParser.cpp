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
}
