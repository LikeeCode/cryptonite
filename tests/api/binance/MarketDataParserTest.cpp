#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QEventLoop>
#include <QJsonObject>
#include <QTimer>

#include "rest-api/BinanceAPI.h"
#include "rest-api/MarketDataParser.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Test fixture for BinanceAPI tests
class MarketDataParserTest : public ::testing::Test
{
protected:
    std::unique_ptr<Binance::BinanceAPI> binanceAPI;

    // This runs before each test
    void SetUp() override
    {
        binanceAPI = std::make_unique<Binance::BinanceAPI>(nullptr, true);
    }

    // This runs after each test
    void TearDown() override
    {
        binanceAPI.reset();
    }
};

TEST_F(MarketDataParserTest, OrderBook)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::MarketData::OrderBook> orderBook{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::orderBookResponse, [&](const QJsonDocument &data) {
        response = data;
        orderBook = Binance::MarketDataParser::parseOrderBook(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest OrderBook API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->orderBook(Binance::MarketData::OrderBookRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(orderBook.has_value());
    EXPECT_GT(orderBook->lastUpdateId, 0);
    EXPECT_FALSE(orderBook->bids.isEmpty());
    EXPECT_FALSE(orderBook->asks.isEmpty());
}

TEST_F(MarketDataParserTest, RecentTrades)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Trade>> trades{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::recentTradesResponse, [&](const QJsonDocument &data) {
        response = data;
        trades = Binance::MarketDataParser::parseTrades(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest RecentTrades API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->recentTrades(Binance::MarketData::RecentTradesRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(trades.has_value());
    EXPECT_FALSE(trades->isEmpty());
    if (!trades->isEmpty()) {
        const auto& trade = trades->first();
        EXPECT_GT(trade.id, 0);
        EXPECT_GT(trade.price, 0);
        EXPECT_GT(trade.qty, 0);
        EXPECT_GT(trade.quoteQty, 0);
    }
}

TEST_F(MarketDataParserTest, HistoricalTrades)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Trade>> trades{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::historicalTradesResponse, [&](const QJsonDocument &data) {
        response = data;
        trades = Binance::MarketDataParser::parseTrades(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest HistoricalTrades API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->historicalTrades(Binance::MarketData::OldTradesRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(trades.has_value());
    EXPECT_FALSE(trades->isEmpty());
    if (!trades->isEmpty()) {
        const auto& trade = trades->first();
        EXPECT_GT(trade.id, 0);
        EXPECT_GT(trade.price, 0);
        EXPECT_GT(trade.qty, 0);
        EXPECT_GT(trade.quoteQty, 0);
    }
}

TEST_F(MarketDataParserTest, AggregatedTrades)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::AggregatedTrade>> aggTrades{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::aggTradesResponse, [&](const QJsonDocument &data) {
        response = data;
        aggTrades = Binance::MarketDataParser::parseAggregatedTrades(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest AggregatedTrades API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->aggregatedTrades(Binance::MarketData::AggregatedTradeRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(aggTrades.has_value());
    EXPECT_FALSE(aggTrades->isEmpty());
    if(!aggTrades->isEmpty()){
        const auto& trade = aggTrades->first();
        EXPECT_GT(trade.a, 0);
        EXPECT_GT(trade.p, 0);
        EXPECT_GT(trade.q, 0);
        EXPECT_GT(trade.f, 0);
        EXPECT_GT(trade.l, 0);
        EXPECT_GT(trade.T, 0);
    }
}

TEST_F(MarketDataParserTest, Klines)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Kline>> klines{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::klinesResponse, [&](const QJsonDocument &data) {
        response = data;
        klines = Binance::MarketDataParser::parseKlines(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest Klines API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->klines(Binance::MarketData::KlineRequest{"BTCUSDT", Binance::Interval::FIVE_MINUTES});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(klines.has_value());
    EXPECT_FALSE(klines->isEmpty());
    if(!klines->isEmpty()){
        const auto& kline = klines->first();
        EXPECT_GT(kline.openTime, 0);
        EXPECT_GT(kline.open, 0);
        EXPECT_GT(kline.high, 0);
        EXPECT_GT(kline.low, 0);
        EXPECT_GT(kline.close, 0);
        EXPECT_GE(kline.volume, 0);
        EXPECT_GT(kline.closeTime, 0);
        EXPECT_GE(kline.quoteAssetVolume, 0);
        EXPECT_GE(kline.numberOfTrades, 0);
        EXPECT_GE(kline.takerBuyBaseAssetVolume, 0);
        EXPECT_GE(kline.takerBuyQuoteAssetVolume, 0);
    }
}

TEST_F(MarketDataParserTest, UIKlines)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::UIKline>> uiKlines{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::uiKlinesResponse, [&](const QJsonDocument &data) {
        response = data;
        uiKlines = Binance::MarketDataParser::parseUIKlines(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest UIKlines API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->uiKlines(Binance::MarketData::UIKlineRequest{"BTCUSDT", Binance::Interval::FIVE_MINUTES});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(uiKlines.has_value());
    EXPECT_FALSE(uiKlines->isEmpty());
    if(!uiKlines->isEmpty()){
        const auto& kline = uiKlines->first();
        EXPECT_GT(kline.openTime, 0);
        EXPECT_GT(kline.open, 0);
        EXPECT_GT(kline.high, 0);
        EXPECT_GT(kline.low, 0);
        EXPECT_GT(kline.close, 0);
        EXPECT_GE(kline.volume, 0);
        EXPECT_GT(kline.closeTime, 0);
        EXPECT_GE(kline.quoteAssetVolume, 0);
        EXPECT_GE(kline.numberOfTrades, 0);
        EXPECT_GE(kline.takerBuyBaseAssetVolume, 0);
        EXPECT_GE(kline.takerBuyQuoteAssetVolume, 0);
    }
}

TEST_F(MarketDataParserTest, CurrentAveragePrice)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::MarketData::CurrentAveragePrice> avgPrice{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::currentAveragePriceResponse, [&](const QJsonDocument &data) {
        response = data;
        avgPrice = Binance::MarketDataParser::parseCurrentAveragePrice(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest CurrentAveragePrice API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->currentAveragePrice(Binance::MarketData::CurrentAveragePriceRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(avgPrice.has_value());
    EXPECT_GT(avgPrice->interval, 0);
    EXPECT_GT(avgPrice->price, 0);
    EXPECT_GT(avgPrice->closeTime, 0);
}

TEST_F(MarketDataParserTest, TickerPrice24hrFull)
{
    QEventLoop loop;
    QJsonDocument response;
    QList<Binance::MarketData::Ticker24hrFull> ticker24hrFull{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tickerPrice24hrResponseFull, [&](const QJsonDocument &data) {
        response = data;
        ticker24hrFull = Binance::MarketDataParser::parseTicker24hrFull(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest TickerPrice24hrFull API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->tickerPrice24hr(Binance::MarketData::Ticker24hrRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_FALSE(ticker24hrFull.isEmpty());
    EXPECT_EQ(ticker24hrFull.first().symbol, "BTCUSDT");
    EXPECT_GT(ticker24hrFull.first().openTime, 0);
    EXPECT_GT(ticker24hrFull.first().closeTime, 0);
    EXPECT_GT(ticker24hrFull.first().highPrice, 0);
    EXPECT_GT(ticker24hrFull.first().lowPrice, 0);
    EXPECT_GT(ticker24hrFull.first().lastPrice, 0);
    EXPECT_GE(ticker24hrFull.first().count, 0);
}

TEST_F(MarketDataParserTest, TickerPrice24hrMini)
{
    QEventLoop loop;
    QJsonDocument response;
    QList<Binance::MarketData::Ticker24hrMini> ticker24hrMini{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tickerPrice24hrResponseMini, [&](const QJsonDocument &data) {
        response = data;
        ticker24hrMini = Binance::MarketDataParser::parseTicker24hrMini(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest TickerPrice24hrMini API Error received: " << error.toStdString();
        loop.quit(); });

    Binance::MarketData::Ticker24hrRequest requestMini{"BTCUSDT"};
    requestMini.type = Binance::ResponseType::MINI;
    binanceAPI->tickerPrice24hr(requestMini);
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_FALSE(ticker24hrMini.isEmpty());
    EXPECT_EQ(ticker24hrMini.first().symbol, "BTCUSDT");
    EXPECT_GT(ticker24hrMini.first().openTime, 0);
    EXPECT_GT(ticker24hrMini.first().closeTime, 0);
    EXPECT_GT(ticker24hrMini.first().highPrice, 0);
    EXPECT_GT(ticker24hrMini.first().lowPrice, 0);
    EXPECT_GT(ticker24hrMini.first().lastPrice, 0);
    EXPECT_GE(ticker24hrMini.first().count, 0);
}

TEST_F(MarketDataParserTest, TradingDayFull)
{
    QEventLoop loop;
    QJsonDocument response;
    QList<Binance::MarketData::TradingDayFull> tradingDayFull{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tradingDayResponseFull, [&](const QJsonDocument &data) {
        response = data;
        tradingDayFull = Binance::MarketDataParser::parseTradingDayFull(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest TradingDayFull API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->tradingDay(Binance::MarketData::TradingDayRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_FALSE(tradingDayFull.isEmpty());
    EXPECT_EQ(tradingDayFull.first().symbol, "BTCUSDT");
    EXPECT_GT(tradingDayFull.first().openTime, 0);
    EXPECT_GT(tradingDayFull.first().closeTime, 0);
    EXPECT_GT(tradingDayFull.first().highPrice, 0);
    EXPECT_GT(tradingDayFull.first().lowPrice, 0);
    EXPECT_GT(tradingDayFull.first().lastPrice, 0);
    EXPECT_GE(tradingDayFull.first().count, 0);
}

TEST_F(MarketDataParserTest, TradingDayMini)
{
    QEventLoop loop;
    QJsonDocument response;
    QList<Binance::MarketData::TradingDayMini> tradingDayMini{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tradingDayResponseMini, [&](const QJsonDocument &data) {
        response = data;
        tradingDayMini = Binance::MarketDataParser::parseTradingDayMini(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest TradingDayMini API Error received: " << error.toStdString();
        loop.quit(); });

    Binance::MarketData::TradingDayRequest requestMini{"BTCUSDT"};
    requestMini.type = Binance::ResponseType::MINI;
    binanceAPI->tradingDay(requestMini);
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_FALSE(tradingDayMini.isEmpty());
    EXPECT_EQ(tradingDayMini.first().symbol, "BTCUSDT");
    EXPECT_GT(tradingDayMini.first().openTime, 0);
    EXPECT_GT(tradingDayMini.first().closeTime, 0);
    EXPECT_GT(tradingDayMini.first().highPrice, 0);
    EXPECT_GT(tradingDayMini.first().lowPrice, 0);
    EXPECT_GT(tradingDayMini.first().lastPrice, 0);
    EXPECT_GE(tradingDayMini.first().count, 0);
}

TEST_F(MarketDataParserTest, SymbolPriceTicker)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::MarketData::SymbolPriceTicker> symbolPriceTicker{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::symbolPriceTickerResponse, [&](const QJsonDocument &data) {
        response = data;
        symbolPriceTicker = Binance::MarketDataParser::parseSymbolPriceTickerResponse(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest SymbolPriceTicker API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->symbolPriceTicker(Binance::MarketData::SymbolPriceTickerRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(symbolPriceTicker.has_value());
    EXPECT_EQ(symbolPriceTicker->symbol, "BTCUSDT");
    EXPECT_GT(symbolPriceTicker->price, 0);
}

TEST_F(MarketDataParserTest, SymbolOrderBookTicker)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::MarketData::SymbolOrderBookTicker> symbolOrderBookTicker{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::symbolOrderBookTickerResponse, [&](const QJsonDocument &data) {
        response = data;
        symbolOrderBookTicker = Binance::MarketDataParser::parseSymbolOrderBookTickerResponse(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest SymbolOrderBookTicker API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->symbolOrderBookTicker(Binance::MarketData::SymbolOrderBookTickerRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(symbolOrderBookTicker.has_value());
    EXPECT_EQ(symbolOrderBookTicker->symbol, "BTCUSDT");
    EXPECT_GT(symbolOrderBookTicker->bidPrice, 0);
    EXPECT_GE(symbolOrderBookTicker->bidQty, 0);
    EXPECT_GT(symbolOrderBookTicker->askPrice, 0);
    EXPECT_GE(symbolOrderBookTicker->askQty, 0);
}

TEST_F(MarketDataParserTest, RollingWindowTickerFull)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::MarketData::TickerFull> tickerFull{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::rollingWindowTickerResponseFull, [&](const QJsonDocument &data) {
        response = data;
        tickerFull = Binance::MarketDataParser::parseRollingWindowTickerResponseFull(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest RollingWindowTickerFull API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->rollingWindowTicker(Binance::MarketData::TickerRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(tickerFull.has_value());
    EXPECT_EQ(tickerFull->symbol, "BTCUSDT");
    EXPECT_GT(tickerFull->openTime, 0);
    EXPECT_GT(tickerFull->closeTime, 0);
    EXPECT_GT(tickerFull->highPrice, 0);
    EXPECT_GT(tickerFull->lowPrice, 0);
    EXPECT_GT(tickerFull->lastPrice, 0);
    EXPECT_GE(tickerFull->count, 0);
}

TEST_F(MarketDataParserTest, RollingWindowTickerMini)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::MarketData::TickerMini> tickerMini{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::rollingWindowTickerResponseMini, [&](const QJsonDocument &data) {
        response = data;
        tickerMini = Binance::MarketDataParser::parseRollingWindowTickerResponseMini(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "MarketDataParserTest RollingWindowTickerMini API Error received: " << error.toStdString();
        loop.quit(); });

    Binance::MarketData::TickerRequest tickerRequestMini{"BTCUSDT"};
    tickerRequestMini.type = Binance::ResponseType::MINI;
    binanceAPI->rollingWindowTicker(tickerRequestMini);
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(tickerMini.has_value());
    EXPECT_EQ(tickerMini->symbol, "BTCUSDT");
    EXPECT_GT(tickerMini->openTime, 0);
    EXPECT_GT(tickerMini->closeTime, 0);
    EXPECT_GT(tickerMini->highPrice, 0);
    EXPECT_GT(tickerMini->lowPrice, 0);
    EXPECT_GT(tickerMini->lastPrice, 0);
    EXPECT_GE(tickerMini->count, 0);
}
