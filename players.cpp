#include "players.h"
#include "ui_players.h"

Players::Players(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Players)
{
    ui->setupUi(this);
}

Players::~Players()
{
    delete ui;
}
