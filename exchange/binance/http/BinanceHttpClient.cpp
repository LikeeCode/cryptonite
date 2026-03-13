#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageAuthenticationCode>
#include <QNetworkReply>
#include <QUrlQuery>

#include "../data/APIEndpoints.h"
#include "BinanceHttpClient.h"

namespace Binance
{

    BinanceHttpClient::BinanceHttpClient(QObject *parent, bool useTestNetwork)
        : QObject(parent),
        m_useTestNetwork(useTestNetwork), m_networkManager(new QNetworkAccessManager(this))
    {
        m_baseUrl = m_useTestNetwork ? API::BASE_URL_TESTNET : API::BASE_URL;
        getApiKeys();

        m_networkManager = std::make_unique<QNetworkAccessManager>(this);
        connect(m_networkManager.get(), &QNetworkAccessManager::finished, this, &BinanceHttpClient::onReplyFinished);
    }

    BinanceHttpClient::~BinanceHttpClient()
    {
    }

    void BinanceHttpClient::setApiKeys(const QString &key, const QString &secret)
    {
        m_apiKey = key;
        m_apiSecret = secret;
    }

    void BinanceHttpClient::ping()
    {
        sendPublicRequest(API::PING);
    }

    // GeneralData
    void BinanceHttpClient::time()
    {
        sendPublicRequest(API::TIME);
    }

    void BinanceHttpClient::exchangeInfo()
    {
        sendPublicRequest(API::EXCHANGE_INFO);
    }

    void BinanceHttpClient::exchangeInfo(const Binance::GeneralData::ExchangeInfoRequest &request)
    {
        sendPublicRequest(API::EXCHANGE_INFO, request.toVariantMap());
    }

    // MarketData
    void BinanceHttpClient::orderBook(const Binance::MarketData::OrderBookRequest &request)
    {
        sendPublicRequest(API::DEPTH, request.toVariantMap());
    }

    void BinanceHttpClient::recentTrades(const Binance::MarketData::RecentTradesRequest &request)
    {
        sendPublicRequest(API::TRADES, request.toVariantMap());
    }

    void BinanceHttpClient::historicalTrades(const Binance::MarketData::OldTradesRequest &request)
    {
        sendPublicRequest(API::HISTORICAL_TRADES, request.toVariantMap());
    }

    void BinanceHttpClient::aggregatedTrades(const Binance::MarketData::AggregatedTradeRequest &request)
    {
        sendPublicRequest(API::AGG_TRADES, request.toVariantMap());
    }

    void BinanceHttpClient::klines(const Binance::MarketData::KlineRequest &request)
    {
        sendPublicRequest(API::KLINES, request.toVariantMap());
    }

    void BinanceHttpClient::uiKlines(const Binance::MarketData::UIKlineRequest &request)
    {
        sendPublicRequest(API::UI_KLINES, request.toVariantMap());
    }

    void BinanceHttpClient::currentAveragePrice(const Binance::MarketData::CurrentAveragePriceRequest &request)
    {
        sendPublicRequest(API::AVG_PRICE, request.toVariantMap());
    }

    void BinanceHttpClient::tickerPrice24hr(const Binance::MarketData::Ticker24hrRequest &request)
    {
        QNetworkReply *reply = sendPublicRequest(API::TICKER_24HR, request.toVariantMap());
        if (!reply)
        {
            emit apiError("Failed to create request for " + API::TICKER_24HR);
            return;
        }
        const bool isFull = !request.type.has_value() || request.type.value() == ResponseType::FULL;
        reply->setProperty("isFull", isFull);
    }

    void BinanceHttpClient::tradingDay(const Binance::MarketData::TradingDayRequest &request)
    {
        QNetworkReply *reply = sendPublicRequest(API::TRADING_DAY, request.toVariantMap());
        if (!reply)
        {
            emit apiError("Failed to create request for " + API::TRADING_DAY);
            return;
        }
        const bool isFull = !request.type.has_value() || request.type.value() == ResponseType::FULL;
        reply->setProperty("isFull", isFull);
    }

    void BinanceHttpClient::symbolPriceTicker(const Binance::MarketData::SymbolPriceTickerRequest &request)
    {
        sendPublicRequest(API::PRICE_TICKER, request.toVariantMap());
    }

    void BinanceHttpClient::symbolOrderBookTicker(const Binance::MarketData::SymbolOrderBookTickerRequest &request)
    {
        sendPublicRequest(API::BOOK_TICKER, request.toVariantMap());
    }

    void BinanceHttpClient::rollingWindowTicker(const Binance::MarketData::TickerRequest &request)
    {
        QNetworkReply *reply = sendPublicRequest(API::ROLLING_WINDOW_TICKER, request.toVariantMap());
        if (!reply)
        {
            emit apiError("Failed to create request for " + API::ROLLING_WINDOW_TICKER);
            return;
        }
        const bool isFull = !request.type.has_value() || request.type.value() == ResponseType::FULL;
        reply->setProperty("isFull", isFull);
    }

    void BinanceHttpClient::onReplyFinished(QNetworkReply *reply)
    {
        if (reply->error() != QNetworkReply::NoError)
        {
            emit apiError(reply->errorString());
            reply->deleteLater();
            return;
        }

        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

        const QString endpoint = reply->url().path();

        // General endpoints
        if (endpoint == API::PING)
        {
            emit pingResponse(jsonDoc);
        }
        else if (endpoint == API::TIME)
        {
            emit timeResponse(jsonDoc);
        }
        else if (endpoint == API::EXCHANGE_INFO)
        {
            emit exchangeInfoResponse(jsonDoc);
        }
        // Market data endpoints
        else if (endpoint == API::DEPTH)
        {
            emit orderBookResponse(jsonDoc);
        }
        else if (endpoint == API::TRADES)
        {
            emit recentTradesResponse(jsonDoc);
        }
        else if (endpoint == API::HISTORICAL_TRADES)
        {
            emit historicalTradesResponse(jsonDoc);
        }
        else if (endpoint == API::AGG_TRADES)
        {
            emit aggTradesResponse(jsonDoc);
        }
        else if (endpoint == API::KLINES)
        {
            emit klinesResponse(jsonDoc);
        }
        else if (endpoint == API::UI_KLINES)
        {
            emit uiKlinesResponse(jsonDoc);
        }
        else if (endpoint == API::AVG_PRICE)
        {
            emit currentAveragePriceResponse(jsonDoc);
        }
        else if (endpoint == API::TICKER_24HR)
        {
            bool isFull = false;
            if (jsonDoc.isObject())
            {
                isFull = jsonDoc.object().contains("priceChange");
            }
            else if (jsonDoc.isArray())
            {
                const QJsonArray arr = jsonDoc.array();
                if (!arr.isEmpty() && arr.first().isObject())
                {
                    isFull = arr.first().toObject().contains("priceChange");
                }
            }

            if (reply->property("isFull").toBool() || isFull)
            {
                emit tickerPrice24hrResponseFull(jsonDoc);
            }
            else
            {
                emit tickerPrice24hrResponseMini(jsonDoc);
            }
        }
        else if (endpoint == API::TRADING_DAY)
        {
            if (reply->property("isFull").toBool())
            {
                emit tradingDayResponseFull(jsonDoc);
            }
            else
            {
                emit tradingDayResponseMini(jsonDoc);
            }
        }
        else if (endpoint == API::PRICE_TICKER)
        {
            emit symbolPriceTickerResponse(jsonDoc);
        }
        else if (endpoint == API::BOOK_TICKER)
        {
            emit symbolOrderBookTickerResponse(jsonDoc);
        }
        else if (endpoint == API::ROLLING_WINDOW_TICKER)
        {
            if (reply->property("isFull").toBool())
            {
                emit rollingWindowTickerResponseFull(jsonDoc);
            }
            else
            {
                emit rollingWindowTickerResponseMini(jsonDoc);
            }
        }
        else
        {
            emit apiError("Unknown API endpoint: " + endpoint);
        }

        reply->deleteLater();
    }

    void BinanceHttpClient::getApiKeys()
    {
        QFile file("apiKeys/binanceAPI.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            emit apiKeysFileError();
            return;
        }

        QTextStream in(&file);
        m_apiKey = in.readLine().trimmed();
        m_apiSecret = in.readLine().trimmed();
        file.close();
    }

    QNetworkReply* BinanceHttpClient::sendPublicRequest(const QString &endpoint, const QVariantMap &params, RequestType type)
    {
        QUrl url(m_baseUrl + endpoint);

        if (!params.isEmpty())
        {
            QUrlQuery query;
            for (auto it = params.constBegin(); it != params.constEnd(); ++it)
            {
                query.addQueryItem(it.key(), it.value().toString());
            }
            url.setQuery(query);
        }

        QNetworkRequest request(url);
        QNetworkReply *reply = nullptr;

        switch (type)
        {
        case RequestType::Get:
            reply = m_networkManager->get(request);
            break;
        case RequestType::Post:
            reply = m_networkManager->post(request, QByteArray());
            break;
        case RequestType::Put:
            reply = m_networkManager->put(request, QByteArray());
            break;
        case RequestType::Delete:
            reply = m_networkManager->deleteResource(request);
            break;
        }

        return reply;
    }

    QNetworkReply* BinanceHttpClient::sendSignedRequest(const QString &endpoint, const QVariantMap &params, RequestType type)
    {
        QUrlQuery query;
        for (auto it = params.constBegin(); it != params.constEnd(); ++it)
        {
            query.addQueryItem(it.key(), it.value().toString());
        }
        QString paramsString = query.toString(QUrl::FullyEncoded);

        QMessageAuthenticationCode code(QCryptographicHash::Sha256);
        code.setKey(m_apiSecret.toUtf8());
        code.addData(paramsString.toUtf8());
        QString signature = code.result().toHex();

        query.addQueryItem("signature", signature);

        QUrl url(m_baseUrl + endpoint);
        url.setQuery(query);

        QNetworkRequest request(url);
        request.setRawHeader(QByteArray(API::API_HEADER.toUtf8()), QByteArray(m_apiKey.toUtf8()));
        QNetworkReply *reply = nullptr;

        switch (type)
        {
        case RequestType::Get:
            reply = m_networkManager->get(request);
            break;
        case RequestType::Post:
            reply = m_networkManager->post(request, QByteArray());
            break;
        case RequestType::Put:
            reply = m_networkManager->put(request, QByteArray());
            break;
        case RequestType::Delete:
            reply = m_networkManager->deleteResource(request);
            break;
        }

        return reply;
    }
} // namespace Binance
