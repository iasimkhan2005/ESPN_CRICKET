#include "players.h"
#include "ui_players.h"

Players::Players(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Players)
{
    ui->setupUi(this);

    // Populate dropdown with team names
    ui->players_dropdown->addItem("--- Select Team ---");
    ui->players_dropdown->addItem("Pakistan");
    ui->players_dropdown->addItem("India");
    ui->players_dropdown->addItem("Bangladesh");
    ui->players_dropdown->addItem("England");
    ui->players_dropdown->addItem("New Zealand");
    ui->players_dropdown->addItem("Australia");
    ui->players_dropdown->addItem("South Africa");
    ui->players_dropdown->addItem("Sri Lanka");
    ui->players_dropdown->addItem("West Indies");

    // Connect the signal for dropdown selection change to a slot
    connect(ui->players_dropdown, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Players::onTeamSelected);
}

Players::~Players()
{
    delete ui;
}

// Slot to handle team selection
void Players::onTeamSelected(int index)
{
    if (index == 0) {
        // If "--- Select Team ---" is selected, clear the label
        ui->players_label->setText("");
        return;
    }

    // Map teams to their players
    QMap<QString, QStringList> teamPlayers = {
        {"Pakistan", {"Babar Azam", "Shaheen Afridi", "Shadab Khan"}},
        {"India", {"Virat Kohli", "Rohit Sharma", "Jasprit Bumrah"}},
        {"Bangladesh", {"Shakib Al Hasan", "Mushfiqur Rahim", "Tamim Iqbal"}},
        {"England", {"Joe Root", "Ben Stokes", "Jofra Archer"}},
        {"New Zealand", {"Kane Williamson", "Trent Boult", "Ross Taylor"}},
        {"Australia", {"Steve Smith", "David Warner", "Pat Cummins"}},
        {"South Africa", {"Quinton de Kock", "Kagiso Rabada", "David Miller"}},
        {"Sri Lanka", {"Angelo Mathews", "Kusal Perera", "Lasith Malinga"}},
        {"West Indies", {"Chris Gayle", "Kieron Pollard", "Jason Holder"}}
    };

    // Get the selected team name
    QString selectedTeam = ui->players_dropdown->currentText();

    // Fetch players for the selected team
    QStringList players = teamPlayers.value(selectedTeam);

    // Update the label with the list of players
    ui->players_label->setText(players.join("\n"));
}
