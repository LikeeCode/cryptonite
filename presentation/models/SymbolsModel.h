#pragma once

#include <QAbstractItemModel>

#include "parsers/EnumParser.h"
#include "data/GeneralData.h"

class SymbolsModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum SymbolRoles
    {
        SymbolRole = Qt::UserRole + 1,
        StatusRole,
        BaseAssetRole,
        QuoteAssetRole,
        FiltersRole
    };

    explicit SymbolsModel(QObject *parent = nullptr);
    ~SymbolsModel() override;

    // QAbstractItemModel overrides
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setSymbols(const QList<Binance::GeneralData::Symbol> &symbols);
    Binance::GeneralData::Symbol getSymbolAt(int row) const;

private:
    QList<Binance::GeneralData::Symbol> m_symbols;
    QHash<int, QByteArray> headerNames{
        {0, "Symbol"},
        {1, "Status"},
        {2, "Base Asset"},
        {3, "Quote Asset"},
        {4, "Filters"}
    };
};