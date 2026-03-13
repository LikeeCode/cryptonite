#pragma once

#include <optional>

#include <QJsonDocument>

#include "MarketData.h"

namespace Binance
{
    class MarketDataParser
    {
    public:
        static std::optional<MarketData::OrderBook> parseOrderBook(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::Trade>> parseTrades(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::AggregatedTrade>> parseAggregatedTrades(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::Kline>> parseKlines(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::UIKline>> parseUIKlines(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::CurrentAveragePrice> parseCurrentAveragePrice(const QJsonDocument &jsonDoc);
        static std::optional<QList<MarketData::Ticker24hrFull>> parseTicker24hrFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::Ticker24hrFull> parseSingleTicker24hrFull(const QJsonObject &json);
        static std::optional<QList<MarketData::Ticker24hrMini>> parseTicker24hrMini(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::Ticker24hrMini> parseSingleTicker24hrMini(const QJsonObject &json);
        static std::optional<QList<MarketData::TradingDayFull>> parseTradingDayFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TradingDayFull> parseSingleTradingDayFull(const QJsonObject &json);
        static std::optional<QList<MarketData::TradingDayMini>> parseTradingDayMini(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TradingDayMini> parseSingleTradingDayMini(const QJsonObject &json);
        static std::optional<QList<MarketData::SymbolPriceTicker>> parseSymbolPriceTicker(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::SymbolPriceTicker> parseSingleSymbolPriceTicker(const QJsonObject &json);
        static std::optional<QList<MarketData::SymbolOrderBookTicker>> parseSymbolOrderBookTicker(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::SymbolOrderBookTicker> parseSingleSymbolOrderBookTicker(const QJsonObject &json);
        static std::optional<QList<MarketData::TickerFull>> parseRollingWindowTickerFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TickerFull> parseSingleRollingWindowTickerFull(const QJsonObject &json);
        static std::optional<QList<MarketData::TickerMini>> parseRollingWindowTickerMini(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TickerMini> parseSingleRollingWindowTickerMini(const QJsonObject &json);
    };
} // namespace Binance
