#pragma once

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>

#include "rest-api/APIEndpoints.h"

namespace Binance
{
    class BinanceAPI : public QObject
    {
        Q_OBJECT
    public:
        explicit BinanceAPI(QObject *parent = nullptr, bool useTestNetwork = true);
        ~BinanceAPI();

        void setApiKeys(const QString& key, const QString& secret);

        // General endpoints
        void ping();
        void time();
        void exchangeInfo();

    private:
        void getApiKeys();
        void sendPublicRequest(const QString& endpoint);
        void sendSignedRequest(const QString& endpoint, const QString& params);

        bool m_useTestNetwork;
        QString m_baseUrl;
        QString m_apiKey;
        QString m_apiSecret;
        QNetworkAccessManager* m_networkManager;

    private slots:
        void onReplyFinished(QNetworkReply *reply);

    signals:
        void apiKeysFileError();
        void apiError(const QString &error);
        void pingResponse(const QJsonDocument& data);
        void timeResponse(const QJsonDocument& data);
        void exchangeInfoResponse(const QJsonDocument& data);
    };
} // namespace Binance
