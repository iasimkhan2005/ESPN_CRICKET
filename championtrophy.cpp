#include "championtrophy.h"
#include "ui_championtrophy.h"

ChampionTrophy::ChampionTrophy(tournamentScreen* tournament, QWidget *parent)
    : QDialog(parent), ui(new Ui::ChampionTrophy), tournament(tournament)
{

    ui->setupUi(this);
    populateTeams();

}

void ChampionTrophy::populateTeams()
{
    if (!tournament) return;

    vector<string> teams = tournament->getAllTeams();
    QStringList teamList;

    for (const auto& teamName : teams)
    {
        teamList << QString::fromStdString(teamName);
    }

    ui->comboBox->addItems(teamList);

     connect(ui->comboBox, &QComboBox::currentTextChanged, this, &ChampionTrophy::onTeamSelected);

}

void ChampionTrophy::onTeamSelected(const QString& teamName)
{
    if (!tournament) return;

    // Clear previous match details
    ui->matchdetails->clear();

    // Get matches for the selected team
    vector<Match> matches = tournament->getOpponents(teamName.toStdString());

    // Display match details
    QString matchDetails;
    for (const auto& match : matches)
    {
        if(teamName.toStdString()!=match.team2)
            {
            matchDetails += QString("Opponent: %1\nDate: %2\nStadium: %3\n\n")
            .arg(QString::fromStdString(match.team2))
            .arg(QString::fromStdString(match.dateTime))
            .arg(QString::fromStdString(match.stadium));
            }

        else if(teamName.toStdString()!=match.team1)
            {
                matchDetails += QString("Opponent: %1\nDate: %2\nStadium: %3\n\n")
                .arg(QString::fromStdString(match.team1))
                .arg(QString::fromStdString(match.dateTime))
                .arg(QString::fromStdString(match.stadium));
            }
    }


    ui->matchdetails->setText(matchDetails);
}

ChampionTrophy::~ChampionTrophy() {
    delete ui;
}
