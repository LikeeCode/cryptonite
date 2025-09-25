#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QEventLoop>
#include <QJsonObject>
#include <QTimer>

#include "rest-api/BinanceAPI.h"
#include "rest-api/GeneralDataParser.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Test fixture for BinanceAPI tests
class GeneralDataParserTest : public ::testing::Test
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

TEST_F(GeneralDataParserTest, Ping)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::GeneralData::Ping> ping{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::pingResponse, [&](const QJsonDocument &data) {
        response = data;
        ping = Binance::GeneralDataParser::parsePing(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "GeneralDataParserTest Ping API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->ping();
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(ping.has_value());
}

TEST_F(GeneralDataParserTest, ServerTime)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::GeneralData::ServerTime> serverTime{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::timeResponse, [&](const QJsonDocument &data) {
        response = data;
        serverTime = Binance::GeneralDataParser::parseServerTime(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error)
                     {
        FAIL() << "GeneralDataParserTest ServerTime API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->time();
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(serverTime.has_value());
    ASSERT_TRUE(serverTime.value().serverTime > 0);
}

TEST_F(GeneralDataParserTest, ExchangeInfo)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::GeneralData::ExchangeInfo> exchangeInfo{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::exchangeInfoResponse, [&](const QJsonDocument &data) {
        response = data;
        exchangeInfo = Binance::GeneralDataParser::parseExchangeInfo(data);
        loop.quit(); });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString &error) {
        FAIL() << "GeneralDataParserTest ExchangeInfo API Error received: " << error.toStdString();
        loop.quit(); });

    binanceAPI->exchangeInfo();
    QTimer::singleShot(15000, &loop, &QEventLoop::quit); // 15-second timeout
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(exchangeInfo.has_value());
    ASSERT_FALSE(exchangeInfo.value().timezone.toStdString().empty());
    ASSERT_TRUE(exchangeInfo.value().serverTime > 0);
    ASSERT_TRUE(exchangeInfo.value().rateLimits.size() > 0);
    ASSERT_TRUE(exchangeInfo.value().symbols.size() > 0);
}
