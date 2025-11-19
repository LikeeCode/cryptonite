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
        FAIL() << "GeneralDataParserTest OrderBook API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->orderBook(Binance::MarketData::OrderBookRequest{"BTCUSDT"});
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(orderBook.has_value());
}
