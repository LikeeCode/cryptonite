#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QEventLoop>
#include <QJsonObject>
#include <QTimer>

#include "BinanceAPI.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Test fixture for BinanceAPI tests
class BinanceAPIBasicTest : public ::testing::Test {
protected:
    std::unique_ptr<Binance::BinanceAPI> binanceAPI;

    // This runs before each test
    void SetUp() override {
        binanceAPI = std::make_unique<Binance::BinanceAPI>(nullptr, true);
    }

    // This runs after each test
    void TearDown() override {
        binanceAPI.reset();
    }
};

// Use TEST_F to use the fixture
TEST_F(BinanceAPIBasicTest, PingServer)
{
    QEventLoop loop;
    bool success = false;
    QJsonDocument response;

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::pingResponse, [&](const QJsonDocument& data) {
        response = data;
        success = true;
        loop.quit();
    });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString& error) {
        FAIL() << "API Error received: " << error.toStdString();
        loop.quit();
    });

    binanceAPI->ping();
    loop.exec();

    ASSERT_TRUE(success);
    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());
}

TEST_F(BinanceAPIBasicTest, GetServerTime)
{
    QEventLoop loop;
    bool success = false;
    QJsonDocument response;

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::timeResponse, [&](const QJsonDocument& data) {
        response = data;
        success = true;
        loop.quit();
    });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString& error) {
        FAIL() << "API Error received: " << error.toStdString();
        loop.quit();
    });

    binanceAPI->time();
    loop.exec();

    ASSERT_TRUE(success);
    ASSERT_TRUE(response.isObject());
    ASSERT_TRUE(response.object().contains("serverTime"));
}

TEST_F(BinanceAPIBasicTest, GetExchangeInfo)
{
    QEventLoop loop;
    bool success = false;
    QJsonDocument response;

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::exchangeInfoResponse, [&](const QJsonDocument& data) {
        response = data;
        success = true;
        loop.quit();
    });

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError, [&](const QString& error) {
        FAIL() << "API Error received: " << error.toStdString();
        loop.quit();
    });

    binanceAPI->exchangeInfo();
    QTimer::singleShot(15000, &loop, &QEventLoop::quit); // 15-second timeout
    loop.exec();

    ASSERT_TRUE(success);
    ASSERT_TRUE(response.isObject());
    ASSERT_TRUE(response.object().contains("symbols"));
}
