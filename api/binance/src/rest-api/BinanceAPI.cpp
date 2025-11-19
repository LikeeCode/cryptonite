#include <QDir>
#include <QFile>
#include <QJsonArray>
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
        else if (endpoint == API::DEPTH)
        {
            emit orderBookResponse(jsonDoc);
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
