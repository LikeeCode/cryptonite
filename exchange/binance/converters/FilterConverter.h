#pragma once

#include <optional>

#include <QString>

#include "../data/Filters.h"

namespace Binance::Filter
{
    QString toString(Type type);
    std::optional<Type> toFilterType(const QString &type);
    std::shared_ptr<BinanceFilter> fromJsonObject(const QJsonObject &jsonObj);
} // namespace Binance::Filter
