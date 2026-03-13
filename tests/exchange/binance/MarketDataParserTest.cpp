#include <gtest/gtest.h>

#include <algorithm>

#include <QCoreApplication>
#include <QEventLoop>
#include <QJsonObject>
#include <QTimer>

#include "../../../exchange/binance/http/BinanceAPI.h"
#include "../../../exchange/binance/parsers/MarketDataParser.h"

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
    QEventLoop m_loop;
    QTimer     m_timer;
    bool       m_timedOut = false;

    MarketDataParserTest()
    {
        // Connected once in the constructor so it is never duplicated across
        // repeated SetUp() calls — m_timer is a fixture member that persists
        // for the lifetime of the fixture object.
        m_timer.setSingleShot(true);
        QObject::connect(&m_timer, &QTimer::timeout, [this]()
        {
            m_timedOut = true;
            m_loop.quit();
        });
    }

    void SetUp() override
    {
        binanceAPI = std::make_unique<Binance::BinanceAPI>(nullptr, true);
        // binanceAPI is recreated each test so this connection is always fresh.
        QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::apiError,
            [this](const QString &error)
            {
                m_timer.stop();
                m_loop.quit();
                FAIL() << "API error: " << error.toStdString();
            });
    }

    void TearDown() override
    {
        binanceAPI.reset();
    }

    // Resets the timeout flag and starts the timer. Call once per async operation.
    void startWait(int timeoutMs = 10000)
    {
        m_timedOut = false;
        m_timer.start(timeoutMs);
    }

    // Call from the success signal handler to stop the timer and unblock the loop.
    void responseReceived()
    {
        m_timer.stop();
        m_loop.quit();
    }

    // Blocks until responseReceived() or timeout. Returns false on timeout.
    [[nodiscard]] bool waitForResponse()
    {
        m_loop.exec();
        EXPECT_FALSE(m_timedOut) << "Test timed out waiting for response";
        return !m_timedOut;
    }
};

TEST_F(MarketDataParserTest, OrderBook)
{
    QJsonDocument response;
    std::optional<Binance::MarketData::OrderBook> orderBook{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::orderBookResponse, [&](const QJsonDocument &data)
    {
        response = data;
        orderBook = Binance::MarketDataParser::parseOrderBook(data);
        responseReceived();
    });

    startWait();
    binanceAPI->orderBook(Binance::MarketData::OrderBookRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(orderBook.has_value());
    EXPECT_GT(orderBook->lastUpdateId, 0);
    EXPECT_FALSE(orderBook->bids.isEmpty());
    EXPECT_FALSE(orderBook->asks.isEmpty());
}

TEST_F(MarketDataParserTest, RecentTrades)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Trade>> trades{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::recentTradesResponse, [&](const QJsonDocument &data)
    {
        response = data;
        trades = Binance::MarketDataParser::parseTrades(data);
        responseReceived();
    });

    startWait();
    binanceAPI->recentTrades(Binance::MarketData::RecentTradesRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(trades.has_value());
    EXPECT_FALSE(trades->isEmpty());
    if (!trades->isEmpty())
    {
        const auto& trade = trades->first();
        EXPECT_GT(trade.id, 0);
        EXPECT_GT(trade.price, 0);
        EXPECT_GT(trade.qty, 0);
        EXPECT_GT(trade.quoteQty, 0);
    }
}

TEST_F(MarketDataParserTest, HistoricalTrades)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Trade>> trades{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::historicalTradesResponse, [&](const QJsonDocument &data)
    {
        response = data;
        trades = Binance::MarketDataParser::parseTrades(data);
        responseReceived();
    });

    startWait();
    binanceAPI->historicalTrades(Binance::MarketData::OldTradesRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(trades.has_value());
    EXPECT_FALSE(trades->isEmpty());
    if (!trades->isEmpty())
    {
        const auto& trade = trades->first();
        EXPECT_GT(trade.id, 0);
        EXPECT_GT(trade.price, 0);
        EXPECT_GT(trade.qty, 0);
        EXPECT_GT(trade.quoteQty, 0);
    }
}

TEST_F(MarketDataParserTest, AggregatedTrades)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::AggregatedTrade>> aggTrades{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::aggTradesResponse, [&](const QJsonDocument &data)
    {
        response = data;
        aggTrades = Binance::MarketDataParser::parseAggregatedTrades(data);
        responseReceived();
    });

    startWait();
    binanceAPI->aggregatedTrades(Binance::MarketData::AggregatedTradeRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(aggTrades.has_value());
    EXPECT_FALSE(aggTrades->isEmpty());
    if (!aggTrades->isEmpty())
    {
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
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Kline>> klines{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::klinesResponse, [&](const QJsonDocument &data)
    {
        response = data;
        klines = Binance::MarketDataParser::parseKlines(data);
        responseReceived();
    });

    startWait();
    binanceAPI->klines(Binance::MarketData::KlineRequest{"BTCUSDT", Binance::Interval::FIVE_MINUTES});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(klines.has_value());
    EXPECT_FALSE(klines->isEmpty());
    if (!klines->isEmpty())
    {
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
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::UIKline>> uiKlines{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::uiKlinesResponse, [&](const QJsonDocument &data)
    {
        response = data;
        uiKlines = Binance::MarketDataParser::parseUIKlines(data);
        responseReceived();
    });

    startWait();
    binanceAPI->uiKlines(Binance::MarketData::UIKlineRequest{"BTCUSDT", Binance::Interval::FIVE_MINUTES});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(uiKlines.has_value());
    EXPECT_FALSE(uiKlines->isEmpty());
    if (!uiKlines->isEmpty())
    {
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
    QJsonDocument response;
    std::optional<Binance::MarketData::CurrentAveragePrice> avgPrice{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::currentAveragePriceResponse, [&](const QJsonDocument &data)
    {
        response = data;
        avgPrice = Binance::MarketDataParser::parseCurrentAveragePrice(data);
        responseReceived();
    });

    startWait();
    binanceAPI->currentAveragePrice(Binance::MarketData::CurrentAveragePriceRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(avgPrice.has_value());
    EXPECT_GT(avgPrice->interval, 0);
    EXPECT_GT(avgPrice->price, 0);
    EXPECT_GT(avgPrice->closeTime, 0);
}

TEST_F(MarketDataParserTest, TickerPrice24hrFull)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Ticker24hrFull>> ticker24hrFull{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tickerPrice24hrResponseFull, [&](const QJsonDocument &data)
    {
        response = data;
        ticker24hrFull = Binance::MarketDataParser::parseTicker24hrFull(data);
        responseReceived();
    });

    startWait();
    binanceAPI->tickerPrice24hr(Binance::MarketData::Ticker24hrRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(ticker24hrFull.has_value());
    EXPECT_EQ(ticker24hrFull->first().symbol, "BTCUSDT");
    EXPECT_GT(ticker24hrFull->first().openTime, 0);
    EXPECT_GT(ticker24hrFull->first().closeTime, 0);
    EXPECT_GT(ticker24hrFull->first().highPrice, 0);
    EXPECT_GT(ticker24hrFull->first().lowPrice, 0);
    EXPECT_GT(ticker24hrFull->first().lastPrice, 0);
    EXPECT_GE(ticker24hrFull->first().count, 0);

    startWait();
    Binance::MarketData::Ticker24hrRequest requestFullMultiple{};
    requestFullMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    binanceAPI->tickerPrice24hr(requestFullMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(ticker24hrFull.has_value());
    ASSERT_GE(ticker24hrFull->size(), 2);
    auto btcIt = std::find_if(ticker24hrFull->begin(), ticker24hrFull->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(ticker24hrFull->begin(), ticker24hrFull->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, ticker24hrFull->end());
    EXPECT_GT(btcIt->openTime, 0);
    EXPECT_GT(btcIt->closeTime, 0);
    EXPECT_GT(btcIt->highPrice, 0);
    EXPECT_GT(btcIt->lowPrice, 0);
    EXPECT_GT(btcIt->lastPrice, 0);
    EXPECT_GE(btcIt->count, 0);
    ASSERT_NE(ethIt, ticker24hrFull->end());
    EXPECT_GT(ethIt->openTime, 0);
    EXPECT_GT(ethIt->closeTime, 0);
    EXPECT_GT(ethIt->highPrice, 0);
    EXPECT_GT(ethIt->lowPrice, 0);
    EXPECT_GT(ethIt->lastPrice, 0);
    EXPECT_GE(ethIt->count, 0);
}

TEST_F(MarketDataParserTest, TickerPrice24hrMini)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::Ticker24hrMini>> ticker24hrMini{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tickerPrice24hrResponseMini, [&](const QJsonDocument &data)
    {
        response = data;
        ticker24hrMini = Binance::MarketDataParser::parseTicker24hrMini(data);
        responseReceived();
    });

    startWait();
    Binance::MarketData::Ticker24hrRequest requestMini{"BTCUSDT"};
    requestMini.type = Binance::ResponseType::MINI;
    binanceAPI->tickerPrice24hr(requestMini);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(ticker24hrMini.has_value());
    EXPECT_EQ(ticker24hrMini->first().symbol, "BTCUSDT");
    EXPECT_GT(ticker24hrMini->first().openTime, 0);
    EXPECT_GT(ticker24hrMini->first().closeTime, 0);
    EXPECT_GT(ticker24hrMini->first().highPrice, 0);
    EXPECT_GT(ticker24hrMini->first().lowPrice, 0);
    EXPECT_GT(ticker24hrMini->first().lastPrice, 0);
    EXPECT_GE(ticker24hrMini->first().count, 0);

    startWait();
    Binance::MarketData::Ticker24hrRequest requestMiniMultiple{};
    requestMiniMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    requestMiniMultiple.type = Binance::ResponseType::MINI;
    binanceAPI->tickerPrice24hr(requestMiniMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(ticker24hrMini.has_value());
    ASSERT_GE(ticker24hrMini->size(), 2);
    auto btcIt = std::find_if(ticker24hrMini->begin(), ticker24hrMini->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(ticker24hrMini->begin(), ticker24hrMini->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, ticker24hrMini->end());
    EXPECT_GT(btcIt->openTime, 0);
    EXPECT_GT(btcIt->closeTime, 0);
    EXPECT_GT(btcIt->highPrice, 0);
    EXPECT_GT(btcIt->lowPrice, 0);
    EXPECT_GT(btcIt->lastPrice, 0);
    EXPECT_GE(btcIt->count, 0);
    ASSERT_NE(ethIt, ticker24hrMini->end());
    EXPECT_GT(ethIt->openTime, 0);
    EXPECT_GT(ethIt->closeTime, 0);
    EXPECT_GT(ethIt->highPrice, 0);
    EXPECT_GT(ethIt->lowPrice, 0);
    EXPECT_GT(ethIt->lastPrice, 0);
    EXPECT_GE(ethIt->count, 0);
}

TEST_F(MarketDataParserTest, TradingDayFull)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::TradingDayFull>> tradingDayFull{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tradingDayResponseFull, [&](const QJsonDocument &data)
    {
        response = data;
        tradingDayFull = Binance::MarketDataParser::parseTradingDayFull(data);
        responseReceived();
    });

    startWait();
    binanceAPI->tradingDay(Binance::MarketData::TradingDayRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(tradingDayFull.has_value());
    EXPECT_EQ(tradingDayFull->first().symbol, "BTCUSDT");
    EXPECT_GT(tradingDayFull->first().openTime, 0);
    EXPECT_GT(tradingDayFull->first().closeTime, 0);
    EXPECT_GT(tradingDayFull->first().highPrice, 0);
    EXPECT_GT(tradingDayFull->first().lowPrice, 0);
    EXPECT_GT(tradingDayFull->first().lastPrice, 0);
    EXPECT_GE(tradingDayFull->first().count, 0);

    startWait();
    Binance::MarketData::TradingDayRequest requestFullMultiple{};
    requestFullMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    binanceAPI->tradingDay(requestFullMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(tradingDayFull.has_value());
    ASSERT_GE(tradingDayFull->size(), 2);
    auto btcIt = std::find_if(tradingDayFull->begin(), tradingDayFull->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(tradingDayFull->begin(), tradingDayFull->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, tradingDayFull->end());
    EXPECT_GT(btcIt->openTime, 0);
    EXPECT_GT(btcIt->closeTime, 0);
    EXPECT_GT(btcIt->highPrice, 0);
    EXPECT_GT(btcIt->lowPrice, 0);
    EXPECT_GT(btcIt->lastPrice, 0);
    EXPECT_GE(btcIt->count, 0);
    ASSERT_NE(ethIt, tradingDayFull->end());
    EXPECT_GT(ethIt->openTime, 0);
    EXPECT_GT(ethIt->closeTime, 0);
    EXPECT_GT(ethIt->highPrice, 0);
    EXPECT_GT(ethIt->lowPrice, 0);
    EXPECT_GT(ethIt->lastPrice, 0);
    EXPECT_GE(ethIt->count, 0);
}

TEST_F(MarketDataParserTest, TradingDayMini)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::TradingDayMini>> tradingDayMini{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::tradingDayResponseMini, [&](const QJsonDocument &data)
    {
        response = data;
        tradingDayMini = Binance::MarketDataParser::parseTradingDayMini(data);
        responseReceived();
    });

    startWait();
    Binance::MarketData::TradingDayRequest requestMini{"BTCUSDT"};
    requestMini.type = Binance::ResponseType::MINI;
    binanceAPI->tradingDay(requestMini);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(tradingDayMini.has_value());
    EXPECT_EQ(tradingDayMini->first().symbol, "BTCUSDT");
    EXPECT_GT(tradingDayMini->first().openTime, 0);
    EXPECT_GT(tradingDayMini->first().closeTime, 0);
    EXPECT_GT(tradingDayMini->first().highPrice, 0);
    EXPECT_GT(tradingDayMini->first().lowPrice, 0);
    EXPECT_GT(tradingDayMini->first().lastPrice, 0);
    EXPECT_GE(tradingDayMini->first().count, 0);

    startWait();
    Binance::MarketData::TradingDayRequest requestMiniMultiple{};
    requestMiniMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    requestMiniMultiple.type = Binance::ResponseType::MINI;
    binanceAPI->tradingDay(requestMiniMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(tradingDayMini.has_value());
    ASSERT_GE(tradingDayMini->size(), 2);
    auto btcIt = std::find_if(tradingDayMini->begin(), tradingDayMini->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(tradingDayMini->begin(), tradingDayMini->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, tradingDayMini->end());
    EXPECT_GT(btcIt->openTime, 0);
    EXPECT_GT(btcIt->closeTime, 0);
    EXPECT_GT(btcIt->highPrice, 0);
    EXPECT_GT(btcIt->lowPrice, 0);
    EXPECT_GT(btcIt->lastPrice, 0);
    EXPECT_GE(btcIt->count, 0);
    ASSERT_NE(ethIt, tradingDayMini->end());
    EXPECT_GT(ethIt->openTime, 0);
    EXPECT_GT(ethIt->closeTime, 0);
    EXPECT_GT(ethIt->highPrice, 0);
    EXPECT_GT(ethIt->lowPrice, 0);
    EXPECT_GT(ethIt->lastPrice, 0);
    EXPECT_GE(ethIt->count, 0);
}

TEST_F(MarketDataParserTest, SymbolPriceTicker)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::SymbolPriceTicker>> symbolPriceTicker{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::symbolPriceTickerResponse, [&](const QJsonDocument &data)
    {
        response = data;
        symbolPriceTicker = Binance::MarketDataParser::parseSymbolPriceTicker(data);
        responseReceived();
    });

    startWait();
    binanceAPI->symbolPriceTicker(Binance::MarketData::SymbolPriceTickerRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(symbolPriceTicker.has_value());
    EXPECT_EQ(symbolPriceTicker->first().symbol, "BTCUSDT");
    EXPECT_GT(symbolPriceTicker->first().price, 0);

    startWait();
    Binance::MarketData::SymbolPriceTickerRequest requestMiniMultiple{};
    requestMiniMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    binanceAPI->symbolPriceTicker(requestMiniMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(symbolPriceTicker.has_value());
    ASSERT_GE(symbolPriceTicker->size(), 2);
    auto btcIt = std::find_if(symbolPriceTicker->begin(), symbolPriceTicker->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(symbolPriceTicker->begin(), symbolPriceTicker->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, symbolPriceTicker->end());
    EXPECT_GT(btcIt->price, 0);
    ASSERT_NE(ethIt, symbolPriceTicker->end());
    EXPECT_GT(ethIt->price, 0);
}

TEST_F(MarketDataParserTest, SymbolOrderBookTicker)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::SymbolOrderBookTicker>> symbolOrderBookTicker{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::symbolOrderBookTickerResponse, [&](const QJsonDocument &data)
    {
        response = data;
        symbolOrderBookTicker = Binance::MarketDataParser::parseSymbolOrderBookTicker(data);
        responseReceived();
    });

    startWait();
    binanceAPI->symbolOrderBookTicker(Binance::MarketData::SymbolOrderBookTickerRequest{"BTCUSDT"});
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(symbolOrderBookTicker.has_value());
    EXPECT_EQ(symbolOrderBookTicker->first().symbol, "BTCUSDT");
    EXPECT_GT(symbolOrderBookTicker->first().bidPrice, 0);
    EXPECT_GE(symbolOrderBookTicker->first().bidQty, 0);
    EXPECT_GT(symbolOrderBookTicker->first().askPrice, 0);
    EXPECT_GE(symbolOrderBookTicker->first().askQty, 0);

    startWait();
    Binance::MarketData::SymbolOrderBookTickerRequest requestMultiple{};
    requestMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    binanceAPI->symbolOrderBookTicker(requestMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(symbolOrderBookTicker.has_value());
    ASSERT_GE(symbolOrderBookTicker->size(), 2);
    auto btcIt = std::find_if(symbolOrderBookTicker->begin(), symbolOrderBookTicker->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(symbolOrderBookTicker->begin(), symbolOrderBookTicker->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, symbolOrderBookTicker->end());
    EXPECT_GT(btcIt->bidPrice, 0);
    EXPECT_GE(btcIt->bidQty, 0);
    EXPECT_GT(btcIt->askPrice, 0);
    EXPECT_GE(btcIt->askQty, 0);
    ASSERT_NE(ethIt, symbolOrderBookTicker->end());
    EXPECT_GT(ethIt->bidPrice, 0);
    EXPECT_GE(ethIt->bidQty, 0);
    EXPECT_GT(ethIt->askPrice, 0);
    EXPECT_GE(ethIt->askQty, 0);
}

TEST_F(MarketDataParserTest, RollingWindowTickerFull)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::TickerFull>> tickerFull{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::rollingWindowTickerResponseFull, [&](const QJsonDocument &data)
    {
        response = data;
        tickerFull = Binance::MarketDataParser::parseRollingWindowTickerFull(data);
        responseReceived();
    });

    startWait();
    Binance::MarketData::TickerRequest symbol{"BTCUSDT"};
    binanceAPI->rollingWindowTicker(symbol);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(tickerFull.has_value());
    EXPECT_EQ(tickerFull->first().symbol, "BTCUSDT");
    EXPECT_GT(tickerFull->first().openTime, 0);
    EXPECT_GT(tickerFull->first().closeTime, 0);
    EXPECT_GT(tickerFull->first().highPrice, 0);
    EXPECT_GT(tickerFull->first().lowPrice, 0);
    EXPECT_GT(tickerFull->first().lastPrice, 0);
    EXPECT_GE(tickerFull->first().count, 0);

    startWait();
    Binance::MarketData::TickerRequest requestFullMultiple{};
    requestFullMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    binanceAPI->rollingWindowTicker(requestFullMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(tickerFull.has_value());
    ASSERT_GE(tickerFull->size(), 2);
    auto btcIt = std::find_if(tickerFull->begin(), tickerFull->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(tickerFull->begin(), tickerFull->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, tickerFull->end());
    EXPECT_GT(btcIt->openTime, 0);
    EXPECT_GT(btcIt->closeTime, 0);
    EXPECT_GT(btcIt->highPrice, 0);
    EXPECT_GT(btcIt->lowPrice, 0);
    EXPECT_GT(btcIt->lastPrice, 0);
    EXPECT_GE(btcIt->count, 0);
    ASSERT_NE(ethIt, tickerFull->end());
    EXPECT_GT(ethIt->openTime, 0);
    EXPECT_GT(ethIt->closeTime, 0);
    EXPECT_GT(ethIt->highPrice, 0);
    EXPECT_GT(ethIt->lowPrice, 0);
    EXPECT_GT(ethIt->lastPrice, 0);
    EXPECT_GE(ethIt->count, 0);
}

TEST_F(MarketDataParserTest, RollingWindowTickerMini)
{
    QJsonDocument response;
    std::optional<QList<Binance::MarketData::TickerMini>> tickerMini{};

    QObject::connect(binanceAPI.get(), &Binance::BinanceAPI::rollingWindowTickerResponseMini, [&](const QJsonDocument &data)
    {
        response = data;
        tickerMini = Binance::MarketDataParser::parseRollingWindowTickerMini(data);
        responseReceived();
    });

    startWait();
    Binance::MarketData::TickerRequest symbol{"BTCUSDT"};
    symbol.type = Binance::ResponseType::MINI;
    binanceAPI->rollingWindowTicker(symbol);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isObject());

    ASSERT_TRUE(tickerMini.has_value());
    EXPECT_EQ(tickerMini->first().symbol, "BTCUSDT");
    EXPECT_GT(tickerMini->first().openTime, 0);
    EXPECT_GT(tickerMini->first().closeTime, 0);
    EXPECT_GT(tickerMini->first().highPrice, 0);
    EXPECT_GT(tickerMini->first().lowPrice, 0);
    EXPECT_GT(tickerMini->first().lastPrice, 0);
    EXPECT_GE(tickerMini->first().count, 0);

    startWait();
    Binance::MarketData::TickerRequest requestMiniMultiple{};
    requestMiniMultiple.symbols = QList<QString>{"BTCUSDT", "ETHUSDT"};
    requestMiniMultiple.type = Binance::ResponseType::MINI;
    binanceAPI->rollingWindowTicker(requestMiniMultiple);
    ASSERT_TRUE(waitForResponse());

    ASSERT_FALSE(response.isNull());
    ASSERT_TRUE(response.isArray());

    ASSERT_TRUE(tickerMini.has_value());
    ASSERT_GE(tickerMini->size(), 2);
    auto btcIt = std::find_if(tickerMini->begin(), tickerMini->end(),
        [](const auto &t) { return t.symbol == "BTCUSDT"; });
    auto ethIt = std::find_if(tickerMini->begin(), tickerMini->end(),
        [](const auto &t) { return t.symbol == "ETHUSDT"; });
    ASSERT_NE(btcIt, tickerMini->end());
    EXPECT_GT(btcIt->openTime, 0);
    EXPECT_GT(btcIt->closeTime, 0);
    EXPECT_GT(btcIt->highPrice, 0);
    EXPECT_GT(btcIt->lowPrice, 0);
    EXPECT_GT(btcIt->lastPrice, 0);
    EXPECT_GE(btcIt->count, 0);
    ASSERT_NE(ethIt, tickerMini->end());
    EXPECT_GT(ethIt->openTime, 0);
    EXPECT_GT(ethIt->closeTime, 0);
    EXPECT_GT(ethIt->highPrice, 0);
    EXPECT_GT(ethIt->lowPrice, 0);
    EXPECT_GT(ethIt->lastPrice, 0);
    EXPECT_GE(ethIt->count, 0);
}
