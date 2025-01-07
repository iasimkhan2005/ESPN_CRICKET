#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *mainScene;
   // QGraphicsScene *tournamentScene;
    QGraphicsScene *dataScene;
     QGraphicsScene *tournamentScene;
};

#endif // MAINWINDOW_H
