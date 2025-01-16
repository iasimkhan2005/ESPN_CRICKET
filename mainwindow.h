#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QString>
#include<queue>
#include<vector>


using namespace std;



struct Matchdetail {
    QString id;
    QString name;
    QString status;
    QDateTime dateTime;
    bool ongoing;


    Matchdetail(const QString &id, const QString &name, const QString &status, const QDateTime &dateTime, bool ongoing)
        : id(id), name(name), status(status), dateTime(dateTime), ongoing(ongoing) {}

};

struct MatchComparator {
    bool operator()(const Matchdetail &m1, const Matchdetail &m2) {
        // Ongoing matches have higher priority
        if (m1.ongoing != m2.ongoing)
            return !m1.ongoing; // false < true, so ongoing comes first

        // If both are ongoing or not, sort by date (most recent first)
        return m1.dateTime < m2.dateTime;
    }
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void onTournamentButtonClicked();
   void showTournamentsScreen();
    //void showICCRankingScreen();
    void showPlayerCardsScreen();
    //void showMatchScheduleScreen();

    void showTournamentsScreen();

private slots:
   void fetchMatchData();
   void handleApiResponse(QNetworkReply *reply);
   void updateMatchList();



   private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *networkManager;
    QString apiKey;

    // Priority queue for matches
    priority_queue<Matchdetail, std::vector<Matchdetail>, MatchComparator> matchQueue;
};


#endif // MAINWINDOW_H
