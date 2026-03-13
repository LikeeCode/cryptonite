#include "BinanceMarketDataRepository.h"

#include "../parsers/MarketDataParser.h"

namespace Binance
{
    BinanceMarketDataRepository::BinanceMarketDataRepository(BinanceHttpClient *client, QObject *parent)
        : QObject(parent), m_client(client)
    {
        connect(m_client, &BinanceHttpClient::apiError, this, &BinanceMarketDataRepository::error);

        connect(m_client, &BinanceHttpClient::orderBookResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseOrderBook(doc);
            if (result) emit orderBookReady(*result);
            else emit error("Failed to parse order book");
        });

        connect(m_client, &BinanceHttpClient::recentTradesResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseTrades(doc);
            if (result) emit recentTradesReady(*result);
            else emit error("Failed to parse recent trades");
        });

        connect(m_client, &BinanceHttpClient::historicalTradesResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseTrades(doc);
            if (result) emit historicalTradesReady(*result);
            else emit error("Failed to parse historical trades");
        });

        connect(m_client, &BinanceHttpClient::aggTradesResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseAggregatedTrades(doc);
            if (result) emit aggregatedTradesReady(*result);
            else emit error("Failed to parse aggregated trades");
        });

        connect(m_client, &BinanceHttpClient::klinesResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseKlines(doc);
            if (result) emit klinesReady(*result);
            else emit error("Failed to parse klines");
        });

        connect(m_client, &BinanceHttpClient::uiKlinesResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseUIKlines(doc);
            if (result) emit uiKlinesReady(*result);
            else emit error("Failed to parse UI klines");
        });

        connect(m_client, &BinanceHttpClient::currentAveragePriceResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseCurrentAveragePrice(doc);
            if (result) emit currentAveragePriceReady(*result);
            else emit error("Failed to parse current average price");
        });

        connect(m_client, &BinanceHttpClient::tickerPrice24hrResponseFull, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseTicker24hrFull(doc);
            if (result) emit tickerPrice24hrFullReady(*result);
            else emit error("Failed to parse 24hr ticker (full)");
        });

        connect(m_client, &BinanceHttpClient::tickerPrice24hrResponseMini, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseTicker24hrMini(doc);
            if (result) emit tickerPrice24hrMiniReady(*result);
            else emit error("Failed to parse 24hr ticker (mini)");
        });

        connect(m_client, &BinanceHttpClient::tradingDayResponseFull, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseTradingDayFull(doc);
            if (result) emit tradingDayFullReady(*result);
            else emit error("Failed to parse trading day (full)");
        });

        connect(m_client, &BinanceHttpClient::tradingDayResponseMini, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseTradingDayMini(doc);
            if (result) emit tradingDayMiniReady(*result);
            else emit error("Failed to parse trading day (mini)");
        });

        connect(m_client, &BinanceHttpClient::symbolPriceTickerResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseSymbolPriceTicker(doc);
            if (result) emit symbolPriceTickerReady(*result);
            else emit error("Failed to parse symbol price ticker");
        });

        connect(m_client, &BinanceHttpClient::symbolOrderBookTickerResponse, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseSymbolOrderBookTicker(doc);
            if (result) emit symbolOrderBookTickerReady(*result);
            else emit error("Failed to parse symbol order book ticker");
        });

        connect(m_client, &BinanceHttpClient::rollingWindowTickerResponseFull, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseRollingWindowTickerFull(doc);
            if (result) emit rollingWindowTickerFullReady(*result);
            else emit error("Failed to parse rolling window ticker (full)");
        });

        connect(m_client, &BinanceHttpClient::rollingWindowTickerResponseMini, this, [this](const QJsonDocument &doc) {
            auto result = MarketDataParser::parseRollingWindowTickerMini(doc);
            if (result) emit rollingWindowTickerMiniReady(*result);
            else emit error("Failed to parse rolling window ticker (mini)");
        });
    }

    void BinanceMarketDataRepository::orderBook(const MarketData::OrderBookRequest &request) { m_client->orderBook(request); }
    void BinanceMarketDataRepository::recentTrades(const MarketData::RecentTradesRequest &request) { m_client->recentTrades(request); }
    void BinanceMarketDataRepository::historicalTrades(const MarketData::OldTradesRequest &request) { m_client->historicalTrades(request); }
    void BinanceMarketDataRepository::aggregatedTrades(const MarketData::AggregatedTradeRequest &request) { m_client->aggregatedTrades(request); }
    void BinanceMarketDataRepository::klines(const MarketData::KlineRequest &request) { m_client->klines(request); }
    void BinanceMarketDataRepository::uiKlines(const MarketData::UIKlineRequest &request) { m_client->uiKlines(request); }
    void BinanceMarketDataRepository::currentAveragePrice(const MarketData::CurrentAveragePriceRequest &request) { m_client->currentAveragePrice(request); }
    void BinanceMarketDataRepository::tickerPrice24hr(const MarketData::Ticker24hrRequest &request) { m_client->tickerPrice24hr(request); }
    void BinanceMarketDataRepository::tradingDay(const MarketData::TradingDayRequest &request) { m_client->tradingDay(request); }
    void BinanceMarketDataRepository::symbolPriceTicker(const MarketData::SymbolPriceTickerRequest &request) { m_client->symbolPriceTicker(request); }
    void BinanceMarketDataRepository::symbolOrderBookTicker(const MarketData::SymbolOrderBookTickerRequest &request) { m_client->symbolOrderBookTicker(request); }
    void BinanceMarketDataRepository::rollingWindowTicker(const MarketData::TickerRequest &request) { m_client->rollingWindowTicker(request); }
} // namespace Binance
