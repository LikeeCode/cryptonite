#pragma once

#include <optional>

#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include <QString>
#include <QVariant>

#include "../data/Enums.h"
#include "../converters/EnumConverter.h"
#include "../data/Filters.h"

namespace Binance::MarketData
{
    struct OrderBookRequest
    {
        QString symbol;
        int limit{100}; // Optional, default 100; max 5000
        SymbolStatus status{ SymbolStatus::TRADING };

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            params.insert("symbol", symbol);
            if (limit != 100 && limit > 0 && limit <= 5000)
            {
                params.insert("limit", limit);
            }
            if (status != SymbolStatus::TRADING)
            {
                params.insert("status", Binance::Enum::toString(status));
            }

            return params;
        }
    };

    struct OrderBook
    {
        qint64 lastUpdateId{};
        QList<QPair<double, double>> bids; // price, quantity
        QList<QPair<double, double>> asks; // price, quantity
    };

    struct RecentTradesRequest
    {
        QString symbol;
        int limit{500}; // Optional, default 500; max 1000

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            params.insert("symbol", symbol);
            if (limit != 500 && limit > 0 && limit <= 1000)
            {
                params.insert("limit", limit);
            }

            return params;
        }
    };

    struct Trade
    {
        qint64 id{};
        double price{};
        double qty{};
        double quoteQty{};
        qint64 time{};
        bool isBuyerMaker{};
        bool isBestMatch{};
    };

    struct OldTradesRequest
    {
        QString symbol;
        int limit{500}; // Optional, default 500; max 1000
        std::optional<qint64> fromId{}; // Trade id to fetch from. Default gets most recent trades.

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            params.insert("symbol", symbol);
            if (limit != 500 && limit > 0 && limit <= 1000)
            {
                params.insert("limit", limit);
            }
            if (fromId.has_value())
            {
                params.insert("fromId", fromId.value());
            }

            return params;
        }
    };

    struct AggregatedTradeRequest
    {
        QString symbol;
        std::optional<qint64> fromId{}; // Optional, id to get aggregate trades from INCLUSIVE.
        std::optional<qint64> startTime{}; // Optional, timestamp in ms to get aggregate trades from INCLUSIVE.
        std::optional<qint64> endTime{}; // Optional, timestamp in ms to get aggregate trades until INCLUSIVE.
        int limit{500}; // Optional, default 500; max 1000

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            params.insert("symbol", symbol);
            if (fromId.has_value())
            {
                params.insert("fromId", fromId.value());
            }
            if (startTime.has_value())
            {
                params.insert("startTime", startTime.value());
            }
            if (endTime.has_value())
            {
                params.insert("endTime", endTime.value());
            }
            if (limit != 500 && limit > 0 && limit <= 1000)
            {
                params.insert("limit", limit);
            }

            return params;
        }
    };

    struct AggregatedTrade
    {
        qint64 a{}; // Aggregate tradeId
        double p{}; // Price
        double q{}; // Quantity
        qint64 f{}; // First tradeId
        qint64 l{}; // Last tradeId
        qint64 T{}; // Timestamp
        bool m{}; // Was the buyer the maker?
        bool M{}; // Was the trade the best price match?
    };

    struct KlineRequest
    {
        QString symbol;
        Interval interval;
        std::optional<qint64> startTime{}; // Optional, timestamp in ms to get candlesticks from INCLUSIVE.
        std::optional<qint64> endTime{}; // Optional, timestamp in ms to get candlesticks until INCLUSIVE.
        std::optional<QString> timeZone; // Optional, default 0 UTC
        int limit{500}; // Optional, default 500; max 1000

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            params.insert("symbol", symbol);
            params.insert("interval", Binance::Enum::toString(interval));
            if (startTime.has_value())
            {
                params.insert("startTime", startTime.value());
            }
            if (endTime.has_value())
            {
                params.insert("endTime", endTime.value());
            }
            if (timeZone.has_value())
            {
                params.insert("timeZone", timeZone.value());
            }
            if (limit != 500 && limit > 0 && limit <= 1000)
            {
                params.insert("limit", limit);
            }

            return params;
        }
    };

    struct Kline
    {
        qint64 openTime{};
        double open{};
        double high{};
        double low{};
        double close{};
        double volume{};
        qint64 closeTime{};
        double quoteAssetVolume{};
        qint64 numberOfTrades{};
        double takerBuyBaseAssetVolume{};
        double takerBuyQuoteAssetVolume{};
        double ignore{};
    };

    struct UIKlineRequest
    {
        QString symbol;
        Interval interval;
        std::optional<qint64> startTime{}; // Optional, timestamp in ms to get candlesticks from INCLUSIVE.
        std::optional<qint64> endTime{}; // Optional, timestamp in ms to get candlesticks until INCLUSIVE.
        std::optional<QString> timeZone; // Optional, default 0 UTC
        int limit{500}; // Optional, default 500; max 1000

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            params.insert("symbol", symbol);
            params.insert("interval", Binance::Enum::toString(interval));
            if (startTime.has_value())
            {
                params.insert("startTime", startTime.value());
            }
            if (endTime.has_value())
            {
                params.insert("endTime", endTime.value());
            }
            if (timeZone.has_value())
            {
                params.insert("timeZone", timeZone.value());
            }
            if (limit != 500 && limit > 0 && limit <= 1000)
            {
                params.insert("limit", limit);
            }

            return params;
        }
    };

    struct UIKline
    {
        qint64 openTime{};
        double open{};
        double high{};
        double low{};
        double close{};
        double volume{};
        qint64 closeTime{};
        double quoteAssetVolume{};
        qint64 numberOfTrades{};
        double takerBuyBaseAssetVolume{};
        double takerBuyQuoteAssetVolume{};
        double ignore{};
    };

    struct CurrentAveragePriceRequest
    {
        QString symbol;

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            params.insert("symbol", symbol);

            return params;
        }
    };

    struct CurrentAveragePrice
    {
        int interval{}; // Average price interval (in minutes)
        double price{}; // Average price
        qint64 closeTime{}; // Last trade time
    };

    struct Ticker24hrRequest
    {
        std::optional<QString> symbol;
        std::optional<QList<QString>> symbols;
        std::optional<ResponseType> type;
        std::optional<SymbolStatus> symbolStatus;

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            if (symbol.has_value())
            {
                params.insert("symbol", symbol.value());
            }
            else if (symbols.has_value() && !symbols.value().isEmpty())
            {
                QJsonArray symbolsArray;
                for (const auto& s : symbols.value())
                {
                    symbolsArray.append(s);
                }
                params.insert("symbols", QString::fromUtf8(QJsonDocument(symbolsArray).toJson(QJsonDocument::Compact)));
            }

            if (type.has_value())
            {
                params.insert("type", Binance::Enum::toString(type.value()));
            }
            if (symbolStatus.has_value())
            {
                params.insert("symbolStatus", Binance::Enum::toString(symbolStatus.value()));
            }

            return params;
        }
    };

    struct Ticker24hrFull
    {
        QString symbol;
        double priceChange{};
        double priceChangePercent{};
        double weightedAvgPrice{};
        double prevClosePrice{};
        double lastPrice{};
        double lastQty{};
        double bidPrice{};
        double bidQty{};
        double askPrice{};
        double askQty{};
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        qint64 firstId{};   // First tradeId
        qint64 lastId{};    // Last tradeId
        qint64 count{};     // Trade count
    };

    struct Ticker24hrMini
    {
        QString symbol;
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        qint64 firstId{};   // First tradeId
        qint64 lastId{};    // Last tradeId
        qint64 count{};     // Trade count
    };

    struct TradingDayRequest
    {
        std::optional<QString> symbol;
        std::optional<QList<QString>> symbols;
        std::optional<QString> timeZone; // Optional, default 0 UTC
        std::optional<ResponseType> type;
        std::optional<SymbolStatus> symbolStatus;

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            if (symbol.has_value())
            {
                params.insert("symbol", symbol.value());
            }
            else if (symbols.has_value() && !symbols.value().isEmpty())
            {
                QJsonArray symbolsArray;
                for (const auto& s : symbols.value())
                {
                    symbolsArray.append(s);
                }
                params.insert("symbols", QString::fromUtf8(QJsonDocument(symbolsArray).toJson(QJsonDocument::Compact)));
            }

            if (timeZone.has_value())
            {
                params.insert("timeZone", timeZone.value());
            }
            if (type.has_value())
            {
                params.insert("type", Binance::Enum::toString(type.value()));
            }
            if (symbolStatus.has_value())
            {
                params.insert("symbolStatus", Binance::Enum::toString(symbolStatus.value()));
            }

            return params;
        }
    };

    struct TradingDayFull
    {
        QString symbol;
        double priceChange{};
        double priceChangePercent{};
        double weightedAvgPrice{};
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        qint64 firstId{};   // First tradeId
        qint64 lastId{};    // Last tradeId
        qint64 count{};     // Trade count
    };

    struct TradingDayMini
    {
        QString symbol;
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        qint64 firstId{};   // First tradeId
        qint64 lastId{};    // Last tradeId
        qint64 count{};     // Trade count
    };

    struct SymbolPriceTickerRequest
    {
        std::optional<QString> symbol;
        std::optional<QList<QString>> symbols;
        std::optional<SymbolStatus> symbolStatus;

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            if (symbol.has_value())
            {
                params.insert("symbol", symbol.value());
            }
            else if (symbols.has_value() && !symbols.value().isEmpty())
            {
                QJsonArray symbolsArray;
                for (const auto& s : symbols.value())
                {
                    symbolsArray.append(s);
                }
                params.insert("symbols", QString::fromUtf8(QJsonDocument(symbolsArray).toJson(QJsonDocument::Compact)));
            }

            if (symbolStatus.has_value())
            {
                params.insert("symbolStatus", Binance::Enum::toString(symbolStatus.value()));
            }

            return params;
        }
    };

    struct SymbolPriceTicker
    {
        QString symbol;
        double price{};
    };

    struct SymbolOrderBookTickerRequest
    {
        std::optional<QString> symbol;
        std::optional<QList<QString>> symbols;
        std::optional<SymbolStatus> symbolStatus;

        QVariantMap toVariantMap() const
        {
            QVariantMap params;
            if (symbol.has_value())
            {
                params.insert("symbol", symbol.value());
            }
            else if (symbols.has_value() && !symbols.value().isEmpty())
            {
                QJsonArray symbolsArray;
                for (const auto& s : symbols.value())
                {
                    symbolsArray.append(s);
                }
                params.insert("symbols", QString::fromUtf8(QJsonDocument(symbolsArray).toJson(QJsonDocument::Compact)));
            }
            if (symbolStatus.has_value())
            {
                params.insert("symbolStatus", Binance::Enum::toString(symbolStatus.value()));
            }
            return params;
        }
    };

    struct SymbolOrderBookTicker
    {
        QString symbol;
        double bidPrice{};
        double bidQty{};
        double askPrice{};
        double askQty{};
    };

    struct TickerRequest
    {
        std::optional<QString> symbol;
        std::optional<QList<QString>> symbols;
        std::optional<QString> windowSize; // e.g., "1m", "5m", "1h", "1d"
        std::optional<ResponseType> type;
        std::optional<SymbolStatus> symbolStatus;

        QVariantMap toVariantMap() const
        {
            QVariantMap params;

            if (symbol.has_value())
            {
                params.insert("symbol", symbol.value());
            }
            else if (symbols.has_value() && !symbols.value().isEmpty())
            {
                QJsonArray symbolsArray;
                for (const auto& s : symbols.value())
                {
                    symbolsArray.append(s);
                }
                params.insert("symbols", QString::fromUtf8(QJsonDocument(symbolsArray).toJson(QJsonDocument::Compact)));
            }

            if (windowSize.has_value())
            {
                params.insert("windowSize", windowSize.value());
            }
            if (type.has_value())
            {
                params.insert("type", Binance::Enum::toString(type.value()));
            }
            if (symbolStatus.has_value())
            {
                params.insert("symbolStatus", Binance::Enum::toString(symbolStatus.value()));
            }
            return params;
        }
    };

    struct TickerFull
    {
        QString symbol;
        double priceChange{};
        double priceChangePercent{};
        double weightedAvgPrice{};
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        qint64 firstId{};
        qint64 lastId{};
        qint64 count{};
    };

    struct TickerMini
    {
        QString symbol;
        double openPrice{};
        double highPrice{};
        double lowPrice{};
        double lastPrice{};
        double volume{};
        double quoteVolume{};
        qint64 openTime{};
        qint64 closeTime{};
        qint64 firstId{};
        qint64 lastId{};
        qint64 count{};
    };
} // namespace Binance::MarketData
