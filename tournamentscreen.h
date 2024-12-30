#ifndef TOURNAMENTSCREEN_H
#define TOURNAMENTSCREEN_H

#include <QDialog>
#include <vector>
#include <map>
#include <vector>
#include <string>


using namespace std;
namespace Ui {
class tournamentScreen;
}

struct Match {
    string team1;
   string team2;
    string dateTime;
   string stadium;
};
class tournamentScreen : public QDialog
{
    Q_OBJECT

public:
    explicit tournamentScreen(QWidget *parent = nullptr);
    ~tournamentScreen();

    // Add a team to the graph
    void addTeam(const string& team);

    // Add a match with date/time and stadium
    void addMatch(const string& team1, const string& team2, const string& dateTime, const string& stadium);

    // Get the opponents of a given team
    vector<Match> getOpponents(const string& team) const;

    // Get all teams in the graph
    vector<string> getAllTeams() const;

    void showSchedule();
private:
    map<string, vector<Match>> teamMatches;

    Ui::tournamentScreen *ui;
};

#endif // TOURNAMENTSCREEN_H
