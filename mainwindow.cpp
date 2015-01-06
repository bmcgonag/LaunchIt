#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddaction_clicked()
{
    if (ui->txtActionName->text().isEmpty() || ui->txtActionExec->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText("You must enter Data into the Action Name and Action Cmd fields.");
        msgBox.exec();
    } else {
        ui->listActions->addItem(ui->txtActionName->text() + " : " + ui->txtActionExec->text());
        ui->txtActionName->setText("");
        ui->txtActionExec->setText("");
    }
}

void MainWindow::on_btnRemoveAction_clicked()
{
    QListWidgetItem *itemRemove = ui->listActions->currentItem();
    delete itemRemove;
}

void MainWindow::on_btnFindImage_clicked()
{
    QStringList filepath = QFileDialog::getOpenFileNames(this, tr("Open File"), "~/");
    QString filepathstring = filepath.first();
    ui->txtImagePath->setText(filepathstring);
}

void MainWindow::on_btnCancel_clicked()
{

}

void MainWindow::on_btnCreateLauncher_clicked()
{
    if (ui->txtIconName->text().isEmpty() || ui->txtExecCmd->text().isEmpty() || ui->txtImagePath->text().isEmpty()) {
        QMessageBox fillFieldsMsg;
        fillFieldsMsg.setText("You must fill in Icon Name, Command, and Icon Path to create a Launcher.");
        fillFieldsMsg.exec();
    } else {
        QDir homepath = QDir::home().absolutePath().append("/.local/share/applications/" + ui->txtIconName->text());
        if (QDir(homepath).exists()) {
            QMessageBox message;
            message.setText("Folder Exists");
            message.exec();
        } else {
            QMessageBox negMsg;
            negMsg.setText("Folder does not exist");
            negMsg.exec();
        }
    }
}
