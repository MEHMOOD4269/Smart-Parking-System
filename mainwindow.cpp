#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ParkingSystem.h"

// Global System Pointer
ParkingSystem* mySystem = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // System Initialize Karein
    if (mySystem == nullptr) {
        mySystem = new ParkingSystem();
    }

    // Welcome Message
    ui->output_log->append("<span style='color:#00d4ff;'>[SYSTEM] Ready for Manual Selection...</span>");
}

MainWindow::~MainWindow()
{
    delete ui;
    if (mySystem) {
        delete mySystem;
        mySystem = nullptr;
    }
}

// --- BUTTON 1: CHECK AVAILABILITY ---
void MainWindow::on_btn_check_clicked()
{
    QString zText = ui->input_zone->text();
    if(zText.isEmpty()) {
        ui->output_log->append("<span style='color:#ef4444;'>Enter Zone first!</span>");
        return;
    }

    if(mySystem) {
        // Show List
        QString res = mySystem->checkAvailableSlots(zText.toInt());
        ui->output_log->append("<span style='color:#38bdf8;'>" + res + "</span>");
    }
}

// --- BUTTON 2: BOOK MANUAL ---
void MainWindow::on_btn_book_clicked()
{
    QString vText = ui->input_vehicle->text();
    QString zText = ui->input_zone->text();
    QString sText = ui->input_slot->text();

    if(vText.isEmpty() || zText.isEmpty() || sText.isEmpty()) {
        ui->output_log->append("<span style='color:#ef4444;'>Enter Vehicle, Zone AND Slot ID!</span>");
        return;
    }

    if(mySystem) {
        QString res = mySystem->bookManualGUI(vText.toInt(), zText.toInt(), sText.toInt());

        // Agar Success hai to Green, warna Red
        QString color = res.contains("SUCCESS") ? "#4ade80" : "#ef4444";
        ui->output_log->append("<span style='color:" + color + ";'>" + res + "</span>");
    }
}

// --- BUTTON 3: DEPART VEHICLE ---
void MainWindow::on_btn_remove_clicked()
{
    QString vText = ui->input_vehicle->text();
    if(vText.isEmpty()) {
        ui->output_log->append("<span style='color:#ef4444;'>Enter Vehicle ID to depart!</span>");
        return;
    }

    if(mySystem) {
        QString res = mySystem->leaveVehicleGUI(vText.toInt());
        ui->output_log->append("<span style='color:#f472b6;'>" + res + "</span>");
    }
}

// --- BUTTON 4: UNDO / ROLLBACK (YE NAYA HAI) ---
void MainWindow::on_btn_rollback_clicked()
{
    if(mySystem) {
        QString res = mySystem->rollbackGUI();
        // Orange Color Message
        ui->output_log->append("<span style='color:#fbbf24;'>" + res + "</span>");
    }
}

// --- BUTTON 5: VIEW ANALYTICS ---
void MainWindow::on_btn_analytics_clicked()
{
    if(mySystem) {
        // Analytics Report Show karein
        QString report = mySystem->getAnalyticsGUI();
        ui->output_log->append("<span style='color:#a78bfa;'>" + report + "</span>");
    }
}
