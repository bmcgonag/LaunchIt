#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>

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
        if (ui->txtActionName->text().isEmpty()) {
            ui->txtActionName->setStyleSheet("border: 2px solid red");
        }

        if (ui->txtActionExec->text().isEmpty()) {
            ui->txtActionExec->setStyleSheet("border: 2px solid red");
        }

        QMessageBox msgBox;
        msgBox.setText("You are missing required information. Please correct the fields outlined in red.");
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
    ui->btnRemoveAction->setEnabled(false);
}

void MainWindow::on_btnFindImage_clicked()
{
    QStringList filepath = QFileDialog::getOpenFileNames(this, tr("Open File"), "~/");
    QString filepathstring = filepath.first();
    ui->txtImagePath->setText(filepathstring);
}

void MainWindow::on_btnCreateLauncher_clicked()
{
    QString terminalValue;
    if (ui->cbTerminal->isChecked()) {
        terminalValue = "True";
    } else {
        terminalValue = "False";
    }


        QDir homepath = QDir::home().absolutePath().append("/.local/share/applications/" + ui->txtIconName->text());
        if (QDir(homepath).exists()) {
            QMessageBox message;
            message.setText("Folder Exists - Please choose a different Application Name to avoid conflicts with existing apps.");
            message.exec();
        } else {
            QString finalPath = homepath.absolutePath();
            QDir().mkdir(finalPath);
            QFile file(finalPath + "/" + ui->txtIconName->text() +  ".desktop");
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out(&file);
            out << "[Desktop Entry]\n";
            out << "Version=" + ui->txtVersionNumber->text() + "\n";
            out << "Name=" + ui->txtIconName->text() + "\n";
            out << "Comment=" + ui->txtComment->text() + "\n";
            out << "Exec=" + ui->txtExecCmd->text() + "\n";
            out << "Icon=" + ui->txtImagePath->text() + "\n";
            out << "Terminal=" + terminalValue + "\n";
            out << "Type=" + ui->comboType->currentText() + "\n";
            out << "Categories=";
            file.close();

            QMessageBox successMsg;
            successMsg.setText("New Icon File Successfully Created.");
            successMsg.exec();

            BlankFields();
        }
}

void MainWindow::on_txtIconName_textChanged(const QString &arg1)
{
    EnableDisableCreateLauncher();
}

void MainWindow::on_txtExecCmd_textChanged(const QString &arg1)
{
    EnableDisableCreateLauncher();
}

void MainWindow::on_txtImagePath_textChanged(const QString &arg1)
{
    EnableDisableCreateLauncher();
}

//    enable the Remove Action button
void MainWindow::on_listActions_itemClicked(QListWidgetItem *item)
{
    if (item->isSelected()) {
        ui->btnRemoveAction->setEnabled(true);
    }
}

void MainWindow::on_txtActionName_textChanged(const QString &arg1)
{
    EnableDisableAddAction();
}

void MainWindow::on_txtActionExec_textChanged(const QString &arg1)
{
    EnableDisableAddAction();
}

void MainWindow::EnableDisableCreateLauncher() {
    if (!ui->txtIconName->text().isEmpty() && !ui->txtExecCmd->text().isEmpty()
            && !ui->txtImagePath->text().isEmpty()) {
        ui->btnCreateLauncher->setEnabled(true);
    } else {
        ui->btnCreateLauncher->setEnabled(false);
    }
}

void MainWindow::EnableDisableAddAction() {
    if (!ui->txtActionExec->text().isEmpty() && !ui->txtActionName->text().isEmpty()) {
        ui->btnAddaction->setEnabled(true);
    } else {
        ui->btnAddaction->setEnabled(false);
    }
}

void MainWindow::BlankFields() {
    ui->txtActionExec->setText("");
    ui->txtActionName->setText("");
    ui->txtComment->setText("");
    ui->txtExecCmd->setText("");
    ui->txtIconName->setText("");
    ui->txtImagePath->setText("");
    ui->txtVersionNumber->setText("");

    ui->comboType->setCurrentIndex(0);
    ui->cbAccessories->setChecked(false);
    ui->cbTerminal->setChecked(false);
    ui->cbCode->setChecked(false);
    ui->cbFiles->setChecked(false);
    ui->cbGraphics->setChecked(false);
    ui->cbHelp->setChecked(false);
    ui->cbInfo->setChecked(false);
    ui->cbMusic->setChecked(false);
    ui->cbPhotos->setChecked(false);
    ui->cbReference->setChecked(false);
    ui->cbSocial->setChecked(false);
    ui->cbVideos->setChecked(false);
    ui->cbWeb->setChecked(false);

    ui->listActions->clear();


}
