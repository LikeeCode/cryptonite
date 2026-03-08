#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageAuthenticationCode>
#include <QNetworkReply>
#include <QUrlQuery>

#include "rest-api/APIEndpoints.h"
#include "rest-api/BinanceAPI.h"

namespace Binance
{

    BinanceAPI::BinanceAPI(QObject *parent, bool useTestNetwork)
        : QObject(parent),
        m_useTestNetwork(useTestNetwork), m_networkManager(new QNetworkAccessManager(this))
    {
        m_baseUrl = m_useTestNetwork ? API::BASE_URL_TESTNET : API::BASE_URL;
        getApiKeys();
        
        connect(m_networkManager, &QNetworkAccessManager::finished, this, &BinanceAPI::onReplyFinished);
    }

    BinanceAPI::~BinanceAPI()
    {
        delete m_networkManager;
    }

    void BinanceAPI::setApiKeys(const QString &key, const QString &secret)
    {
        m_apiKey = key;
        m_apiSecret = secret;
    }

    void BinanceAPI::ping()
    {
        sendPublicRequest(API::PING);
    }

    // GeneralData
    void BinanceAPI::time()
    {
        sendPublicRequest(API::TIME);
    }

    void BinanceAPI::exchangeInfo()
    {
        sendPublicRequest(API::EXCHANGE_INFO);
    }
    
    void BinanceAPI::exchangeInfo(const Binance::GeneralData::ExchangeInfoRequest &request)
    {
        sendPublicRequest(API::EXCHANGE_INFO, request.toVariantMap());
    }

    // MarketData
    void BinanceAPI::orderBook(const Binance::MarketData::OrderBookRequest &request)
    {
        sendPublicRequest(API::DEPTH, request.toVariantMap());
    }

    void BinanceAPI::recentTrades(const Binance::MarketData::RecentTradesRequest &request)
    {
        sendPublicRequest(API::TRADES, request.toVariantMap());
    }

    void BinanceAPI::historicalTrades(const Binance::MarketData::OldTradesRequest &request)
    {
        sendPublicRequest(API::HISTORICAL_TRADES, request.toVariantMap());
    }

    void BinanceAPI::aggregatedTrades(const Binance::MarketData::AggregatedTradeRequest &request)
    {
        sendPublicRequest(API::AGG_TRADES, request.toVariantMap());
    }

    void BinanceAPI::klines(const Binance::MarketData::KlineRequest &request)
    {
        sendPublicRequest(API::KLINES, request.toVariantMap());
    }
    
    void BinanceAPI::uiKlines(const Binance::MarketData::UIKlineRequest &request)
    {
        sendPublicRequest(API::UI_KLINES, request.toVariantMap());
    }

    void BinanceAPI::currentAveragePrice(const Binance::MarketData::CurrentAveragePriceRequest &request)
    {
        sendPublicRequest(API::AVG_PRICE, request.toVariantMap());
    }

    void BinanceAPI::tickerPrice24hr(const Binance::MarketData::Ticker24hrRequest &request)
    {
        sendPublicRequest(API::TICKER_24HR, request.toVariantMap());
    }

    void BinanceAPI::tradingDay(const Binance::MarketData::TradingDayRequest &request)
    {
        sendPublicRequest(API::TRADING_DAY, request.toVariantMap());
    }

    void BinanceAPI::symbolPriceTicker(const Binance::MarketData::SymbolPriceTickerRequest &request)
    {
        sendPublicRequest(API::PRICE_TICKER, request.toVariantMap());
    }

    void BinanceAPI::symbolOrderBookTicker(const Binance::MarketData::SymbolOrderBookTickerRequest &request)
    {
        sendPublicRequest(API::BOOK_TICKER, request.toVariantMap());
    }
    void BinanceAPI::onReplyFinished(QNetworkReply *reply)
    {
        if (reply->error() != QNetworkReply::NoError)
        {
            emit apiError(reply->errorString());
            reply->deleteLater();
            return;
        }

        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

        // Determine which signal to emit based on the URL
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
            if(jsonDoc.isObject() && jsonDoc.object().contains("priceChange")) // Full ticker info contains "priceChange", while mini ticker does not
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
            if(jsonDoc.isObject() && jsonDoc.object().contains("priceChange")) // Full trading day info contains "priceChange", while mini trading day does not
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
        else
        {
            emit apiError("Unknown API endpoint: " + endpoint);
        }

        reply->deleteLater();
    }

    void BinanceAPI::getApiKeys()
    {
        QFile file("apiKeys/binanceAPI.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            emit apiKeysFileError();
            return;
        }
        else{
            QTextStream in(&file);
            m_apiKey = in.readLine().trimmed();
            m_apiSecret = in.readLine().trimmed();
            file.close();
        }
    }

    void BinanceAPI::sendPublicRequest(const QString &endpoint, const QVariantMap &params, RequestType type)
    {
        QUrl url(m_baseUrl + endpoint);

        // If there are parameters, add them to the URL as a query string
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

        switch (type)
        {
        case RequestType::Get:
            m_networkManager->get(request);
            break;
        case RequestType::Post:
            m_networkManager->post(request, QByteArray());
            break;
        case RequestType::Put:
            m_networkManager->put(request, QByteArray());
            break;
        case RequestType::Delete:
            m_networkManager->deleteResource(request);
            break;
        }
    }

    void BinanceAPI::sendSignedRequest(const QString &endpoint, const QVariantMap &params, RequestType type)
    {
        // Create a query string from the parameters. This is what gets signed.
        QUrlQuery query;
        for (auto it = params.constBegin(); it != params.constEnd(); ++it)
        {
            query.addQueryItem(it.key(), it.value().toString());
        }
        // The signature is based on the query string (e.g., "symbol=BTCUSDT&timestamp=12345")
        QString paramsString = query.toString(QUrl::FullyEncoded);

        // 1. Create the signature
        QMessageAuthenticationCode code(QCryptographicHash::Sha256);
        code.setKey(m_apiSecret.toUtf8());
        code.addData(paramsString.toUtf8());
        QString signature = code.result().toHex();

        // 2. Add the signature to our query
        query.addQueryItem("signature", signature);

        // 3. Build the final URL
        QUrl url(m_baseUrl + endpoint);
        url.setQuery(query);

        // 4. Create the request and add the API key to the header
        QNetworkRequest request(url);
        request.setRawHeader(QByteArray(API::API_HEADER.toUtf8()), QByteArray(m_apiKey.toUtf8()));

        // 5. Send the request
        switch (type)
        {
        case RequestType::Get:
            m_networkManager->get(request);
            break;
        case RequestType::Post:
            // Note: For POST, params would typically be in the body, not the URL.
            // This implementation assumes params are always in the query string.
            m_networkManager->post(request, QByteArray());
            break;
        case RequestType::Put:
            m_networkManager->put(request, QByteArray());
            break;
        case RequestType::Delete:
            m_networkManager->deleteResource(request);
            break;
        }
    }
} // namespace Binance
