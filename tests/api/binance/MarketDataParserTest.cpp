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
}
