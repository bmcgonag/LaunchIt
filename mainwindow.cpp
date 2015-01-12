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
    // add the extra Action item name and command to the list-view
    ui->listActions->addItem(ui->txtActionName->text() + " : " + ui->txtActionExec->text());
    ui->txtActionName->setText("");
    ui->txtActionExec->setText("");
}

void MainWindow::on_btnRemoveAction_clicked()
{
    // remove the selected item from the extra Actions list view
    QListWidgetItem *itemRemove = ui->listActions->currentItem();
    delete itemRemove;
    ui->btnRemoveAction->setEnabled(false);
}

void MainWindow::on_btnFindImage_clicked()
{
    // open the system file dialog to find the icon image desired

    QDir userHome = QDir::home().absolutePath();
    QString userHomePath = userHome.absolutePath();
    QStringList filepath = QFileDialog::getOpenFileNames(this, tr("Open File"), userHomePath);
    QString filepathstring = filepath.first();
    ui->txtImagePath->setText(filepathstring);
}

void MainWindow::on_btnCreateLauncher_clicked()
{
    // set the value based on the checkbox selection for Terminal
    QString terminalValue;
    if (ui->cbTerminal->isChecked()) {
        terminalValue = "True";
    } else {
        terminalValue = "False";
    }

        // set the path for the icon folder
        QDir homepath = QDir::home().absolutePath().append("/.local/share/applications/" + ui->txtIconName->text());

        // if the folder already exists warn the user (if part)
        // if not, then create the folder, and generate the .desktop file (else part)

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
    // make sure all required fields are filled in
    EnableDisableCreateLauncher();

    // show a scaled version of the selected image on the Window
    ui->IconImage->setScaledContents(true);
    ui->IconImage->setPixmap(QPixmap(ui->txtImagePath->text()));
}


void MainWindow::on_listActions_itemClicked(QListWidgetItem *item)
{
    // make sure an item is selected in the listbox, then enable the Remove Action button
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

    // ensure that all required fields for creating a launcher are filled then enable the button
    if (!ui->txtIconName->text().isEmpty() && !ui->txtExecCmd->text().isEmpty()
            && !ui->txtImagePath->text().isEmpty()) {
        ui->btnCreateLauncher->setEnabled(true);
    } else {
        ui->btnCreateLauncher->setEnabled(false);
    }
}

void MainWindow::EnableDisableAddAction() {

    // ensure that all required fields for Adding an extra Action are filled then enable the button
    if (!ui->txtActionExec->text().isEmpty() && !ui->txtActionName->text().isEmpty()) {
        ui->btnAddaction->setEnabled(true);
    } else {
        ui->btnAddaction->setEnabled(false);
    }
}

void MainWindow::BlankFields() {

    // blank out all fields after a successful .desktop creation
    // there's probably a more elegant way to do this.

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
