#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QEventLoop>
#include <QJsonObject>
#include <QTimer>

#include "ApiHelper.h"
#include "../../../exchange/binance/http/BinanceHttpClient.h"
#include "../../../exchange/binance/parsers/GeneralDataParser.h"

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
    std::unique_ptr<Binance::BinanceHttpClient> binanceHttpClient;

    // This runs before each test
    void SetUp() override
    {
         auto apiKeys = ApiHelper::getApiKeys(); // Ensure API keys file exists before creating client
        if (apiKeys.first.isEmpty() || apiKeys.second.isEmpty())
        {
            // FAIL() << "API keys not found";
        }

        binanceHttpClient = std::make_unique<Binance::BinanceHttpClient>(nullptr, apiKeys.first, apiKeys.second, true);
    }

    // This runs after each test
    void TearDown() override
    {
        binanceHttpClient.reset();
    }
};

TEST_F(GeneralDataParserTest, Ping)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::GeneralData::Ping> ping{};

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::pingResponse, [&](const QJsonDocument &data)
    {
        response = data;
        ping = Binance::GeneralDataParser::parsePing(data);
        loop.quit();
    });

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::apiError, [&](const QString &error)
    {
        FAIL() << "GeneralDataParserTest Ping API Error received: " << error.toStdString();
        loop.quit();
    });

    binanceHttpClient->ping();
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

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::timeResponse, [&](const QJsonDocument &data)
    {
        response = data;
        serverTime = Binance::GeneralDataParser::parseServerTime(data);
        loop.quit();
    });

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::apiError, [&](const QString &error)
    {
        FAIL() << "GeneralDataParserTest ServerTime API Error received: " << error.toStdString();
        loop.quit();
    });

    binanceHttpClient->time();
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

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::exchangeInfoResponse, [&](const QJsonDocument &data)
    {
        response = data;
        exchangeInfo = Binance::GeneralDataParser::parseExchangeInfo(data);
        loop.quit();
    });

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::apiError, [&](const QString &error)
    {
        FAIL() << "GeneralDataParserTest ExchangeInfo API Error received: " << error.toStdString();
        loop.quit();
    });

    binanceHttpClient->exchangeInfo();
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

TEST_F(GeneralDataParserTest, ExchangeInfoSymbol)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::GeneralData::ExchangeInfo> exchangeInfo{};

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::exchangeInfoResponse, [&](const QJsonDocument &data)
    {
        response = data;
        exchangeInfo = Binance::GeneralDataParser::parseExchangeInfo(data);
        loop.quit();
    });

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::apiError, [&](const QString &error)
    {
        FAIL() << "GeneralDataParserTest ExchangeInfoWithParams API Error received: " << error.toStdString();
        loop.quit();
    });

    Binance::GeneralData::ExchangeInfoRequest request;
    request.symbol = "BTCUSDT";

    binanceHttpClient->exchangeInfo(request);
    QTimer::singleShot(15000, &loop, &QEventLoop::quit); // 15-second timeout
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(exchangeInfo.has_value());
    // Verify that the server correctly filtered the results
    ASSERT_EQ(exchangeInfo.value().symbols.size(), 1);
    ASSERT_EQ(exchangeInfo.value().symbols.first().symbol.toStdString(), "BTCUSDT");
}

TEST_F(GeneralDataParserTest, ExchangeInfoSymbols)
{
    QEventLoop loop;
    QJsonDocument response;
    std::optional<Binance::GeneralData::ExchangeInfo> exchangeInfo{};

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::exchangeInfoResponse, [&](const QJsonDocument &data)
    {
        response = data;
        exchangeInfo = Binance::GeneralDataParser::parseExchangeInfo(data);
        loop.quit();
    });

    QObject::connect(binanceHttpClient.get(), &Binance::BinanceHttpClient::apiError, [&](const QString &error)
    {
        FAIL() << "GeneralDataParserTest ExchangeInfoWithParams API Error received: " << error.toStdString();
        loop.quit();
    });

    Binance::GeneralData::ExchangeInfoRequest request;
    request.symbols = {"BTCUSDT", "BNBBTC"};

    binanceHttpClient->exchangeInfo(request);
    QTimer::singleShot(15000, &loop, &QEventLoop::quit); // 15-second timeout
    loop.exec();

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(exchangeInfo.has_value());
    // Verify that the server correctly filtered the results
    ASSERT_EQ(exchangeInfo.value().symbols.size(), 2);
    ASSERT_EQ(exchangeInfo.value().symbols.first().symbol.toStdString(), "BNBBTC");
}
