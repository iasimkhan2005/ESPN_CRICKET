#include "players.h"
#include "ui_players.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

Players::Players(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Players),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    populateCountries();
    loadPlayerDataFromFile();   // Load data when the program starts

    connect(ui->player_dropdown, &QComboBox::currentTextChanged, this, &Players::onCountrySelected);
    connect(networkManager, &QNetworkAccessManager::finished, this, &Players::handlePlayerDataResponse);
}

void Players::populateCountries()
{
    QStringList countries = {
        "Pakistan", "India", "Australia", "England",
        "South Africa", "New Zealand", "Bangladesh",
        "Afghanistan", "Sri Lanka", "West Indies"
    };

    ui->player_dropdown->addItems(countries);
}

void Players::onCountrySelected(const QString& country)
{
    QString url = QString("https://api.cricapi.com/v1/players?apikey=593bc6a5-36b3-44f1-bd5a-b53770645324&offset=0");
    QNetworkRequest request{QUrl(url)};
    networkManager->get(request);
    ui->player_dropdown->setEnabled(false); // Disable while fetching
}

void Players::handlePlayerDataResponse(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj["status"].toString() == "success")
        {
            QJsonArray players = jsonObj["data"].toArray();
            savePlayerDataToFile(players); // Save the fetched player data to a file

            QString selectedCountry = ui->player_dropdown->currentText();

            ui->player_dropdown->setEnabled(true);
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);

            for (const QJsonValue& playerVal : players)
            {
                QJsonObject playerObj = playerVal.toObject();

                if (playerObj["country"].toString() == selectedCountry)
                {
                    QString name = playerObj["name"].toString();
                    int row = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(row);
                    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
                }
            }
        }
    }
    reply->deleteLater();
}

void Players::handlePlayerInfoResponse(QNetworkReply* reply)
{
    // This function remains unchanged for handling player info details
}

void Players::loadPlayerDataFromFile()
{
    QFile file("players.json");
    if (file.exists() && file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj["status"].toString() == "success")
        {
            QJsonArray players = jsonObj["data"].toArray();
            QString selectedCountry = ui->player_dropdown->currentText();

            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);

            for (const QJsonValue& playerVal : players)
            {
                QJsonObject playerObj = playerVal.toObject();

                if (playerObj["country"].toString() == selectedCountry)
                {
                    QString name = playerObj["name"].toString();
                    int row = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(row);
                    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
                }
            }
        }
        file.close();
    }
}

void Players::savePlayerDataToFile(const QJsonArray& players)
{
    QFile file("players.json");
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonObject jsonObj;
        jsonObj["status"] = "success";
        jsonObj["data"] = players;
        QJsonDocument jsonDoc(jsonObj);

        file.write(jsonDoc.toJson());
        file.close();
    }
}

Players::~Players()
{
    delete ui;
}
