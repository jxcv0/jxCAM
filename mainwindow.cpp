#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_pushButton_open_clicked
 * Open a program and proccess its contents
 */
void MainWindow::on_pushButton_open_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("PAF Files (*.PAF)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString filename;
    if (dialog.exec()) {
        if (dialog.selectedFiles().size() > 1) {
            QMessageBox::critical(this, "Open file", "Only one file can be opened at a time");
        }
        filename = dialog.selectedFiles().front();
    }
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        qDebug() << line << "\n";
    }
}

