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
        static QList<MarketData::Ticker24hrFull> parseTicker24hrFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::Ticker24hrFull> parseSingleTicker24hrFull(const QJsonDocument &jsonDoc);
        static QList<MarketData::Ticker24hrMini> parseTicker24hrMini(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::Ticker24hrMini> parseSingleTicker24hrMini(const QJsonDocument &jsonDoc);
        static QList<MarketData::TradingDayFull> parseTradingDayFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TradingDayFull> parseSingleTradingDayFull(const QJsonDocument &jsonDoc);
        static QList<MarketData::TradingDayMini> parseTradingDayMini(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TradingDayMini> parseSingleTradingDayMini(const QJsonDocument &jsonDoc);
        static QList<MarketData::SymbolPriceTicker> parseSymbolPriceTickerResponse(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::SymbolPriceTicker> parseSingleSymbolPriceTickerResponse(const QJsonDocument &jsonDoc);
        static QList<MarketData::SymbolOrderBookTicker> parseSymbolOrderBookTickerResponse(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::SymbolOrderBookTicker> parseSingleSymbolOrderBookTickerResponse(const QJsonDocument &jsonDoc);
        static QList<MarketData::TickerFull> parseRollingWindowTickerResponseFull(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TickerFull> parseSingleRollingWindowTickerResponseFull(const QJsonDocument &jsonDoc);
        static QList<MarketData::TickerMini> parseRollingWindowTickerResponseMini(const QJsonDocument &jsonDoc);
        static std::optional<MarketData::TickerMini> parseSingleRollingWindowTickerResponseMini(const QJsonDocument &jsonDoc);
    };
} // namespace Binance
