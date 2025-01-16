#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tournamentscreen.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) , networkManager(new QNetworkAccessManager(this)) //QNetwork Use for Api
    , apiKey("593bc6a5-36b3-44f1-bd5a-b53770645324") //API
{
    ui->setupUi(this);

    // Fetch match data
        //Function to Fetch Data.
        fetchMatchData();
        connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::handleApiResponse);


    //Tournament Buttton
       connect(ui->tournament_btn, &QPushButton::clicked, this, &MainWindow::showTournamentsScreen);

    //Refresh Button
       connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::fetchMatchData);





}

//Fetch  Data Function which will fetch the data from  API
        void MainWindow::fetchMatchData()
            {
                QString url = QString("https://api.cricapi.com/v1/currentMatches?apikey=%1&offset=0").arg(apiKey);
                QNetworkRequest request((QUrl(url)));
                networkManager->get(request);
            }

//The following will handle the API Response.
void MainWindow::handleApiResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);

        if (!jsonDoc.isNull())
        {
            QJsonObject jsonObj = jsonDoc.object();
            QJsonArray matches = jsonObj["data"].toArray();

            // Clear previous data
            while (!matchQueue.empty()) matchQueue.pop();

            // Process matches
            for (const QJsonValue &matchVal : matches)
            {
                QJsonObject matchObj = matchVal.toObject();

                QString id = matchObj["id"].toString();
                QString name = matchObj["name"].toString();
                QString status = matchObj["status"].toString();
                QDateTime dateTime = QDateTime::fromString(matchObj["dateTimeGMT"].toString(), Qt::ISODate);
                bool ongoing = matchObj["matchStarted"].toBool() && !matchObj["matchEnded"].toBool();

                Matchdetail match(id, name, status, dateTime, ongoing);
                matchQueue.push(match);
            }

            // Update UI
            updateMatchList();
        }

    }

    else
    {
        qDebug() << "Error fetching data:" << reply->errorString();
    }

    reply->deleteLater();
}

void MainWindow::updateMatchList()
{
    ui->listWidget->clear();

    // Priority Queue
    priority_queue<Matchdetail, std::vector<Matchdetail>, MatchComparator> tempQueue = matchQueue;

    while (!tempQueue.empty())
    {
        Matchdetail match = tempQueue.top();
        tempQueue.pop();

        QString displayText = QString("%1 - %2").arg(match.name).arg(match.status);
        if (match.ongoing)
        {
            displayText += " (Ongoing)";
        }
        ui->listWidget->addItem(displayText);
    }
}

//When Tournament Button has been Clicked On mainWindow, The Follwoing will Implement.
void MainWindow::showTournamentsScreen()
    {
        tournamentScreen* Tournament = new tournamentScreen(this);
        Tournament->setWindowTitle("Tournaments");
        Tournament->show();
    }


MainWindow::~MainWindow()
{
    delete ui;
}


