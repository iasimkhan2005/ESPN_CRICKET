#include "players.h"
#include "ui_players.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Players::Players(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Players)
{
    ui->setupUi(this);
    populateCountries();
    populatePlayerData();  // Load data into playersData when the program starts

    connect(ui->player_dropdown, &QComboBox::currentTextChanged, this, &Players::onCountrySelected);
}

void Players::populateCountries()
{
    QStringList countries = { "Pakistan", "India", "Australia", "England", "Afghanistan", "Bangladesh", "New Zealand" };
    ui->player_dropdown->addItems(countries);
}

void Players::onCountrySelected(const QString& country)
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Filter the players data based on the selected country and display it in the table
    for (const QJsonValue& playerVal : playersData)
    {
        QJsonObject playerObj = playerVal.toObject();

        if (playerObj["Country"].toString() == country)
        {
            QString name = playerObj["Name"].toString();
            QString role = playerObj["Role"].toString();
            int age = playerObj["Age"].toInt();
            int jerseyNumber = playerObj["Jersey Number"].toInt();
            QString score = (playerObj.contains("ODI total score") ? QString::number(playerObj["ODI total score"].toInt()) : "N/A") +
                            "/" +
                            (playerObj.contains("T20 total score") ? QString::number(playerObj["T20 total score"].toInt()) : "N/A");
            QString wickets = (playerObj.contains("Total ODI wickets") ? QString::number(playerObj["Total ODI wickets"].toInt()) : "N/A") +
                              "/" +
                              (playerObj.contains("Total T20 wickets") ? QString::number(playerObj["Total T20 wickets"].toInt()) : "N/A");

            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(name));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(role));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(age)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(jerseyNumber)));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(score));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(wickets));
        }
    }
}

void Players::populatePlayerData()
{
    // Full player data as QJsonArray
    QString playerData = R"(
    [
        {"Name": "Babar Azam", "Age": 29, "Role": "Batsman", "Country": "Pakistan", "Jersey Number": 56, "ODI total score": 4500, "T20 total score": 1700},
        {"Name": "Shaheen Afridi", "Age": 23, "Role": "Bowler", "Country": "Pakistan", "Jersey Number": 10, "Total ODI wickets": 180, "Total T20 wickets": 50},
        {"Name": "Fakhar Zaman", "Age": 33, "Role": "Batsman", "Country": "Pakistan", "Jersey Number": 12, "ODI total score": 3500, "T20 total score": 1200},
        {"Name": "Shadab Khan", "Age": 26, "Role": "Bowler", "Country": "Pakistan", "Jersey Number": 23, "Total ODI wickets": 80, "Total T20 wickets": 40},
        {"Name": "Mohammad Rizwan", "Age": 31, "Role": "Batsman", "Country": "Pakistan", "Jersey Number": 14, "ODI total score": 3500, "T20 total score": 1600},
        {"Name": "Haris Rauf", "Age": 30, "Role": "Bowler", "Country": "Pakistan", "Jersey Number": 17, "Total ODI wickets": 65, "Total T20 wickets": 55},
        {"Name": "Imam-ul-Haq", "Age": 28, "Role": "Batsman", "Country": "Pakistan", "Jersey Number": 9, "ODI total score": 4000, "T20 total score": 1200},
        {"Name": "Mohammad Nawaz", "Age": 29, "Role": "Bowler", "Country": "Pakistan", "Jersey Number": 18, "Total ODI wickets": 70, "Total T20 wickets": 40},
        {"Name": "Shoaib Malik", "Age": 42, "Role": "Batsman", "Country": "Pakistan", "Jersey Number": 6, "ODI total score": 7500, "T20 total score": 2200},
        {"Name": "Usman Qadir", "Age": 30, "Role": "Bowler", "Country": "Pakistan", "Jersey Number": 44, "Total ODI wickets": 50, "Total T20 wickets": 35},
        {"Name": "Virat Kohli", "Age": 35, "Role": "Batsman", "Country": "India", "Jersey Number": 18, "ODI total score": 12000, "T20 total score": 2500},
        {"Name": "Rohit Sharma", "Age": 36, "Role": "Batsman", "Country": "India", "Jersey Number": 45, "ODI total score": 9000, "T20 total score": 2200},
        {"Name": "Hardik Pandya", "Age": 30, "Role": "All-rounder", "Country": "India", "Jersey Number": 33, "ODI total score": 2500, "T20 total score": 1500},
        {"Name": "KL Rahul", "Age": 31, "Role": "Batsman", "Country": "India", "Jersey Number": 11, "ODI total score": 3500, "T20 total score": 1400},
        {"Name": "Jasprit Bumrah", "Age": 29, "Role": "Bowler", "Country": "India", "Jersey Number": 93, "Total ODI wickets": 120, "Total T20 wickets": 50},
        {"Name": "Shikhar Dhawan", "Age": 38, "Role": "Batsman", "Country": "India", "Jersey Number": 25, "ODI total score": 5500, "T20 total score": 1500},
        {"Name": "David Warner", "Age": 37, "Role": "Batsman", "Country": "Australia", "Jersey Number": 23, "ODI total score": 8000, "T20 total score": 2200},
        {"Name": "Steve Smith", "Age": 35, "Role": "Batsman", "Country": "Australia", "Jersey Number": 49, "ODI total score": 7000, "T20 total score": 1900},
        {"Name": "Glenn Maxwell", "Age": 36, "Role": "All-rounder", "Country": "Australia", "Jersey Number": 32, "ODI total score": 3500, "T20 total score": 1200},
        {"Name": "Mitchell Starc", "Age": 33, "Role": "Bowler", "Country": "Australia", "Jersey Number": 56, "Total ODI wickets": 200, "Total T20 wickets": 80},
        {"Name": "Pat Cummins", "Age": 30, "Role": "Bowler", "Country": "Australia", "Jersey Number": 14, "Total ODI wickets": 120, "Total T20 wickets": 60},
        {"Name": "Ben Stokes", "Age": 34, "Role": "All-rounder", "Country": "England", "Jersey Number": 55, "ODI total score": 4000, "T20 total score": 1600},
        {"Name": "Joe Root", "Age": 33, "Role": "Batsman", "Country": "England", "Jersey Number": 66, "ODI total score": 6000, "T20 total score": 1500},
        {"Name": "Jonny Bairstow", "Age": 34, "Role": "Batsman", "Country": "England", "Jersey Number": 57, "ODI total score": 4500, "T20 total score": 1300},
        {"Name": "Jos Buttler", "Age": 33, "Role": "Wicketkeeper-Batsman", "Country": "England", "Jersey Number": 62, "ODI total score": 5000, "T20 total score": 1700},
        {"Name": "Chris Woakes", "Age": 35, "Role": "All-rounder", "Country": "England", "Jersey Number": 19, "ODI total score": 2000, "T20 total score": 1000},
        {"Name": "Kane Williamson", "Age": 34, "Role": "Batsman", "Country": "New Zealand", "Jersey Number": 22, "ODI total score": 7500, "T20 total score": 2000},
        {"Name": "Martin Guptill", "Age": 38, "Role": "Batsman", "Country": "New Zealand", "Jersey Number": 7, "ODI total score": 6000, "T20 total score": 1800},
        {"Name": "Ross Taylor", "Age": 39, "Role": "Batsman", "Country": "New Zealand", "Jersey Number": 3, "ODI total score": 8500, "T20 total score": 1500},
        {"Name": "Trent Boult", "Age": 34, "Role": "Bowler", "Country": "New Zealand", "Jersey Number": 18, "Total ODI wickets": 300, "Total T20 wickets": 100},
        {"Name": "Mitchell Santner", "Age": 32, "Role": "All-rounder", "Country": "New Zealand", "Jersey Number": 48, "ODI total score": 2500, "T20 total score": 1200},
        {"Name": "Colin de Grandhomme", "Age": 36, "Role": "All-rounder", "Country": "New Zealand", "Jersey Number": 6, "ODI total score": 1800, "T20 total score": 800},
        {"Name": "Rashid Khan", "Age": 25, "Role": "Bowler", "Country": "Afghanistan", "Jersey Number": 11, "Total ODI wickets": 140, "Total T20 wickets": 100},
        {"Name": "Mohammad Nabi", "Age": 39, "Role": "All-rounder", "Country": "Afghanistan", "Jersey Number": 5, "ODI total score": 3500, "T20 total score": 1500},
        {"Name": "Gulbadin Naib", "Age": 34, "Role": "All-rounder", "Country": "Afghanistan", "Jersey Number": 3, "ODI total score": 1500, "T20 total score": 600},
        {"Name": "Najibullah Zadran", "Age": 31, "Role": "Batsman", "Country": "Afghanistan", "Jersey Number": 12, "ODI total score": 2500, "T20 total score": 1000},
        {"Name": "Mohammad Shahzad", "Age": 36, "Role": "Wicketkeeper-Batsman", "Country": "Afghanistan", "Jersey Number": 7, "ODI total score": 2200, "T20 total score": 800},
        {"Name": "Hamid Hassan", "Age": 36, "Role": "Bowler", "Country": "Afghanistan", "Jersey Number": 22, "Total ODI wickets": 80, "Total T20 wickets": 30},
        {"Name": "Shakib Al Hasan", "Age": 37, "Role": "All-rounder", "Country": "Bangladesh", "Jersey Number": 75, "ODI total score": 12000, "T20 total score": 3000},
        {"Name": "Tamim Iqbal", "Age": 34, "Role": "Batsman", "Country": "Bangladesh", "Jersey Number": 28, "ODI total score": 8000, "T20 total score": 2200},
        {"Name": "Mushfiqur Rahim", "Age": 37, "Role": "Wicketkeeper-Batsman", "Country": "Bangladesh", "Jersey Number": 15, "ODI total score": 6000, "T20 total score": 1500},
        {"Name": "Mahmudullah", "Age": 38, "Role": "All-rounder", "Country": "Bangladesh", "Jersey Number": 5, "ODI total score": 4000, "T20 total score": 1300},
        {"Name": "Mustafizur Rahman", "Age": 28, "Role": "Bowler", "Country": "Bangladesh", "Jersey Number": 45, "Total ODI wickets": 150, "Total T20 wickets": 60},
        {"Name": "Sabbir Rahman", "Age": 32, "Role": "All-rounder", "Country": "Bangladesh", "Jersey Number": 2, "ODI total score": 2000, "T20 total score": 800}
    ]
    )";

    QJsonDocument doc = QJsonDocument::fromJson(playerData.toUtf8());
    playersData = doc.array();
}


Players::~Players()
{
    delete ui;
}
