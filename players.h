#ifndef PLAYERS_H
#define PLAYERS_H

#include <QDialog>
#include <QMap>
#include <QStringList>

namespace Ui {
class Players;
}

class Players : public QDialog
{
    Q_OBJECT

public:
    explicit Players(QWidget *parent = nullptr);
    ~Players();

private slots:
    void onTeamSelected(int index);

private:
    Ui::Players *ui;
};

#endif // PLAYERS_H
