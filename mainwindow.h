#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QFocusEvent>

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

    void on_btnCreateLauncher_clicked();

    void on_txtIconName_textChanged(const QString &arg1);

    void on_txtExecCmd_textChanged(const QString &arg1);

    void on_txtImagePath_textChanged(const QString &arg1);

    void on_listActions_itemClicked(QListWidgetItem *item);

    void on_txtActionName_textChanged(const QString &arg1);

    void on_txtActionExec_textChanged(const QString &arg1);

    void EnableDisableCreateLauncher();

    void EnableDisableAddAction();

    void BlankFields();

    QStringList GetCategories();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
