#ifndef CHAMPIONTROPHY_H
#define CHAMPIONTROPHY_H

#include <QComboBox>
#include <QDialog>
#include "tournamentscreen.h"

namespace Ui {
class ChampionTrophy;
}

class ChampionTrophy : public QDialog
{
    Q_OBJECT

public:
    explicit ChampionTrophy(tournamentScreen* tournament, QWidget *parent = nullptr);
    ~ChampionTrophy();

private slots:
    void populateTeams();
    void onTeamSelected(const QString& teamName);
private:
    Ui::ChampionTrophy *ui;
    tournamentScreen* tournament; // Pointer to the tournament instance
};

#endif // CHAMPIONTROPHY_H
