#ifndef PLAYERS_H
#define PLAYERS_H

#include <QDialog>
#include <QComboBox>
#include <QStringList>
#include <QTableWidget>
#include <QJsonArray>

namespace Ui {
class Players;
}

class Players : public QDialog
{
    Q_OBJECT

public:
    explicit Players(QWidget *parent = nullptr);
    ~Players();

private slots:
    void populateCountries();
    void onCountrySelected(const QString& country);

private:
    Ui::Players *ui;
    QJsonArray playersData;  // Store player data in memory
    void populatePlayerData();
};

#endif // PLAYERS_H
