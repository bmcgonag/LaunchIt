#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnAddaction_clicked();

    void on_btnRemoveAction_clicked();

    void on_btnFindImage_clicked();

    void on_btnCancel_clicked();

    void on_btnCreateLauncher_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
