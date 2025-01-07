#include "players.h"
#include "ui_players.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Players::Players(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Players),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    populateCountries();

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
            QString selectedCountry = ui->player_dropdown->currentText();

            ui->player_dropdown->setEnabled(true);
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);

            for (const QJsonValue& playerVal : players)
            {
                QJsonObject playerObj = playerVal.toObject();

                if (playerObj["country"].toString() == selectedCountry)
                {
                    QString id = playerObj["id"].toString();
                    QString name = playerObj["name"].toString();

                    QNetworkRequest infoRequest(QUrl(QString("https://api.cricapi.com/v1/players_info?apikey=593bc6a5-36b3-44f1-bd5a-b53770645324&offset=0&id=%1").arg(id)));
                    networkManager->get(infoRequest);

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
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj["status"].toString() == "success")
        {
            QJsonObject playerData = jsonObj["data"].toObject();
            QString name = playerData["name"].toString();
            QString role = playerData["role"].toString();
            QString battingStyle = playerData["battingStyle"].toString();
            QString bowlingStyle = playerData["bowlingStyle"].toString();
            QString dob = playerData["dateOfBirth"].toString();

            for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
            {
                if (ui->tableWidget->item(row, 0)->text() == name)
                {
                    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(role));
                    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(battingStyle));
                    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(bowlingStyle));
                    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(dob));
                    break;
                }
            }
        }
    }
    reply->deleteLater();
}

Players::~Players()
{
    delete ui;
}
