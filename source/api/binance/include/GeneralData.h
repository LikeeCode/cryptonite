#pragma once

#include <QList>
#include <QString>
#include <QVariant>

#include "Enums.h"
#include "Filters.h"

namespace Binance::GeneralData
{
    // Check server time
    // GET /api/v3/time
    // Response
    struct ServerTime
    {
        qint64 serverTime{};
    };
}
