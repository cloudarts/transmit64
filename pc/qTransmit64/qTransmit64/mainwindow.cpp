#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSerialPortInfo>
#include <QSerialPort>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSerial();
    ui->transmitButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectButtonPushed()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open File to transmit"));
    ui->labelFilename->setText(filename);
    checkAvailabilityStart();
}

void MainWindow::portSelected(QListWidgetItem *item)
{
    this->portname = item->text();
    checkAvailabilityStart();
}

void MainWindow::initSerial()
{
    auto ports = QSerialPortInfo::availablePorts();
    for( auto port : ports )
    {
        new QListWidgetItem(port.portName(), ui->listWidget);
    }
}

void MainWindow::checkAvailabilityStart()
{
    if( !portname.isEmpty() && !filename.isEmpty() )
    {
        ui->transmitButton->setEnabled(true);
    }
}
