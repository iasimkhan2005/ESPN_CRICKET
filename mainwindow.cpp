#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tournamentscreen.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create scenes
    mainScene = new QGraphicsScene(this);
    tournamentScene = new QGraphicsScene(this);
    dataScene = new QGraphicsScene(this);

    //Tournament Buttton
       connect(ui->tournament_btn, &QPushButton::clicked, this, &MainWindow::showTournamentsScreen);

  ui->view->setScene(mainScene);

}

void MainWindow :: onTournamentButtonClicked(){
    qDebug() << "Tournament button clicked!";
        // Perform your desired function here
}


void MainWindow::showTournamentsScreen(){
    tournamentScreen* Tournament = new tournamentScreen(this);
    Tournament->setWindowTitle("Tournaments");
    Tournament->show();
}


MainWindow::~MainWindow()
{
    delete ui;
}
