#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_check_clicked();
    void on_btn_book_clicked();
    void on_btn_remove_clicked();
    void on_btn_rollback_clicked(); // <-- YE LINE ZAROORI HAI
    void on_btn_analytics_clicked();

private:
    Ui::MainWindow *ui;
};
#endif
