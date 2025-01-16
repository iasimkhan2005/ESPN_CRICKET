#include "tournamentscreen.h"
#include "ui_tournamentscreen.h"
#include <QDateTime>
#include "championtrophy.h"

#include<set>

using namespace std;

tournamentScreen::tournamentScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tournamentScreen)
    {
        ui->setupUi(this);

        connect(ui->championTrophy,&QPushButton::clicked, this, &tournamentScreen::showSchedule);
    }

void tournamentScreen::addTeam(const string& team)
{

     if (teamMatches.find(team) == teamMatches.end())
         {
             teamMatches[team] = {};
         }
 }

void tournamentScreen::addMatch(const string& team1, const string& team2, const string& dateTime, const string& stadium)
{

    Match match;
    match.team1 = team1;
    match.team2 = team2;
    match.dateTime = dateTime;
    match.stadium = stadium;

    teamMatches[team1].push_back(match);
    teamMatches[team2].push_back(match);

}

vector<Match> tournamentScreen::getOpponents(const string& team) const
{
    return teamMatches.at(team);
}

vector<string> tournamentScreen::getAllTeams() const
{
    set<string> uniqueTeams;

    for (const auto& teamMatchesPair : teamMatches)
    {
        uniqueTeams.insert(teamMatchesPair.first);
    }

    vector<string> teams(uniqueTeams.begin(), uniqueTeams.end());

    return teams;
}

void tournamentScreen::showSchedule()
{
    // Add Teams
    addTeam("Pakistan");
    addTeam("India");
    addTeam("Afghanistan");
    addTeam("New Zealand");
    addTeam("Australia");
    addTeam("England");
    addTeam("Bangladesh");
    addTeam("South Africa");

//Group A
    addMatch("Pakistan", "New Zealand", "19/02/2025, 14:00", "National Stadium, Karachi");
    addMatch("Pakistan", "India", "23/02/2025, 14:00", "Dubai International Cricket Stadium");
    addMatch("Pakistan", "Bangladesh", "27/02/2025, 14:00", "Gaddafi Stadium, Lahore");
    addMatch("India", "New Zealand", "25/02/2025, 14:00", "Sharjah Cricket Stadium");
    addMatch("India", "Bangladesh", "27/02/2025, 14:00", "Gaddafi Stadium, Lahore");
    addMatch("New Zealand", "Bangladesh", "29/02/2025, 14:00", "Sheikh Zayed Cricket Stadium, Abu Dhabi");

//Group B
    addMatch("England", "Afghanistan", "21/02/2025, 14:00", "National Stadium, Karachi");
    addMatch("England", "Australia", "22/02/2025, 14:00", "Gaddafi Stadium, Lahore");
    addMatch("England", "South Africa", "26/02/2025, 14:00", "Rawalpindi Cricket Stadium");
    addMatch("Australia", "Afghanistan", "24/02/2025, 14:00", "Dubai International Cricket Stadium");
    addMatch("Australia", "South Africa", "28/02/2025, 14:00", "Sharjah Cricket Stadium");
    addMatch("Afghanistan", "South Africa", "21/02/2025, 14:00", "National Stadium, Karachi");


    this->close();

    // Pass the current instance of tournamentScreen
    ChampionTrophy* champ = new ChampionTrophy(this);
    champ->setWindowTitle("Champion Trophy Schedule");
    champ->show();
}

tournamentScreen::~tournamentScreen()
{
    delete ui;
}
