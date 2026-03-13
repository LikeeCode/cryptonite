#include "BinanceGeneralDataRepository.h"

#include "../parsers/GeneralDataParser.h"

namespace Binance
{
    BinanceGeneralDataRepository::BinanceGeneralDataRepository(BinanceHttpClient *client, QObject *parent)
        : QObject(parent), m_client(client)
    {
        connect(m_client, &BinanceHttpClient::apiError, this, &BinanceGeneralDataRepository::error);

        connect(m_client, &BinanceHttpClient::pingResponse, this, [this](const QJsonDocument &doc) {
            auto result = GeneralDataParser::parsePing(doc);
            if (result) emit pingReady(*result);
            else emit error("Failed to parse ping response");
        });

        connect(m_client, &BinanceHttpClient::timeResponse, this, [this](const QJsonDocument &doc) {
            auto result = GeneralDataParser::parseServerTime(doc);
            if (result) emit serverTimeReady(*result);
            else emit error("Failed to parse server time");
        });

        connect(m_client, &BinanceHttpClient::exchangeInfoResponse, this, [this](const QJsonDocument &doc) {
            auto result = GeneralDataParser::parseExchangeInfo(doc);
            if (result) emit exchangeInfoReady(*result);
            else emit error("Failed to parse exchange info");
        });
    }

    void BinanceGeneralDataRepository::ping() { m_client->ping(); }
    void BinanceGeneralDataRepository::time() { m_client->time(); }
    void BinanceGeneralDataRepository::exchangeInfo() { m_client->exchangeInfo(); }
    void BinanceGeneralDataRepository::exchangeInfo(const GeneralData::ExchangeInfoRequest &request) { m_client->exchangeInfo(request); }
} // namespace Binance
