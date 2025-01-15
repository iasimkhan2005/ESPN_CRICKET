// players.h
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

struct Player {
    QString name;
    int age;
    QString role;
    QString country;
    int jerseyNumber;
    int odiScore;
    int t20Score;
    int odiWickets;
    int t20Wickets;
};

class PlayerNode {
public:
    Player player;
    PlayerNode* next;

    PlayerNode(const Player& p) : player(p), next(nullptr) {}
};

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
    PlayerNode* head;  // Head of the linked list

    void populatePlayerData();
    void displayPlayersData(PlayerNode* head);
    void clearLinkedList();
};

#endif // PLAYERS_H
