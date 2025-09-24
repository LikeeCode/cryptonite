#include <QDir>
#include <QFile>
#include <QMessageAuthenticationCode>
#include <QNetworkReply>
#include <QUrlQuery>

#include "APIEndpoints.h"
#include "BinanceAPI.h"

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

    void BinanceAPI::time()
    {
        sendPublicRequest(API::TIME);
    }

    void BinanceAPI::exchangeInfo()
    {
        sendPublicRequest(API::EXCHANGE_INFO);
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

        reply->deleteLater();
    }

    void BinanceAPI::getApiKeys()
    {
        QFile file("binanceAPI.txt");
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

    void BinanceAPI::sendPublicRequest(const QString &endpoint)
    {
        QUrl url(m_baseUrl + endpoint);
        QNetworkRequest request(url);
        m_networkManager->get(request);
    }

    void BinanceAPI::sendSignedRequest(const QString &endpoint, const QString &params)
    {
        // 1. Create the signature
        QMessageAuthenticationCode code(QCryptographicHash::Sha256);
        code.setKey(m_apiSecret.toUtf8());
        code.addData(params.toUtf8());
        QString signature = code.result().toHex();

        // 2. Build the final URL with parameters and signature
        QUrl url(m_baseUrl + endpoint);
        QUrlQuery query;
        query.addQueryItem("timestamp", params.split("=").last()); // Extract timestamp from params
        query.addQueryItem("signature", signature);
        url.setQuery(query);

        // 3. Create the request and add the API key to the header
        QNetworkRequest request(url);
        request.setRawHeader("X-MBX-APIKEY", m_apiKey.toUtf8());
        m_networkManager->get(request);
    }
} // namespace Binance
