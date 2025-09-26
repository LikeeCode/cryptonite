#pragma once

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QVariantMap>

#include "rest-api/APIEndpoints.h"
#include "../../../RequestType.h"

namespace Binance
{
    class BinanceAPI : public QObject
    {
        Q_OBJECT
    public:
        explicit BinanceAPI(QObject *parent = nullptr, bool useTestNetwork = true);
        ~BinanceAPI();

        void setApiKeys(const QString &key, const QString &secret);

        // General endpoints
        void ping();
        void time();
        void exchangeInfo();
        void exchangeInfo(const QVariantMap &params);

    private:
        void getApiKeys();
        void sendPublicRequest(const QString &endpoint, const QVariantMap &params = {}, RequestType type = RequestType::Get);
        void sendSignedRequest(const QString &endpoint, const QVariantMap &params, RequestType type);

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
        void pingResponse(const QJsonDocument &data);
        void timeResponse(const QJsonDocument &data);
        void exchangeInfoResponse(const QJsonDocument &data);
    };
} // namespace Binance
