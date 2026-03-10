#include "SymbolsModel.h"

SymbolsModel::SymbolsModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

SymbolsModel::~SymbolsModel()
{
}

QModelIndex SymbolsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid() && row >= 0 && row < m_symbols.size() && column >= 0 && column < 1)
    {
        return createIndex(row, column);
    }
    return QModelIndex();
}

int SymbolsModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        return m_symbols.size();
    }
    return 0;
}

int SymbolsModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5; // Only one column for symbol names
}

QVariant SymbolsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_symbols.size())
    {
        return QVariant();
    }

    switch (role)
    {
    case SymbolRole:
        return m_symbols[index.row()].symbol;
    case StatusRole:
        return Binance::Enum::toString(m_symbols[index.row()].status);
    case BaseAssetRole:
        return m_symbols[index.row()].baseAsset;
    case QuoteAssetRole:
        return m_symbols[index.row()].quoteAsset;
    case FiltersRole:
        {
            /// TODO: Implement filter conversion to QVariantList
            // QVariantList filtersList;
            // for (const auto &filter : m_symbols[index.row()].filters)
            // {
            //     filtersList.append(Filter::filterToVariantMap(filter));
            // }
            // return filtersList;
            return QVariant();
        }
    }

    return QVariant();
}

QVariant SymbolsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (section >= 0 && section < headerNames.size())
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            return headerNames[section];
        }
    }
    return QVariant();
}

Qt::ItemFlags SymbolsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QHash<int, QByteArray> SymbolsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SymbolRole] = "symbol";
    roles[StatusRole] = "status";
    roles[BaseAssetRole] = "baseAsset";
    roles[QuoteAssetRole] = "quoteAsset";
    roles[FiltersRole] = "filters";
    return roles;
}

void SymbolsModel::setSymbols(const QList<Binance::GeneralData::Symbol> &symbols)
{
    beginResetModel();
    m_symbols = symbols;
    endResetModel();
}

Binance::GeneralData::Symbol SymbolsModel::getSymbolAt(int row) const
{
    if (row >= 0 && row < m_symbols.size())
    {
        return m_symbols[row];
    }
    return Binance::GeneralData::Symbol{};
}
