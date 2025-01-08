#ifndef PLAYERS_H
#define PLAYERS_H

#include <QDialog>
#include <QComboBox>
#include <QStringList>
#include <QTableWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
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
    void handlePlayerDataResponse(QNetworkReply* reply);
    void handlePlayerInfoResponse(QNetworkReply* reply);
    void loadPlayerDataFromFile();   // New function to load player data from a file
    void savePlayerDataToFile(const QJsonArray& players);  // New function to save player data

private:
    Ui::Players *ui;
    QNetworkAccessManager* networkManager;
};

#endif // PLAYERS_H
