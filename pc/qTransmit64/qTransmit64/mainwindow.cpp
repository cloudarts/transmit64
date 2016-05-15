#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QSerialPortInfo>

namespace
{
    int currentPos = 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),  transmitting(false)
{
    ui->setupUi(this);
    initSerial();
    ui->transmitButton->setEnabled(false);
    ui->connectButton->setEnabled(false);
    ui->progressBar->reset();
    log("ready");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectButtonPushed()
{
    filename = QFileDialog::getOpenFileName(this, tr("Open File to transmit"));
    ui->labelFilename->setText(filename);
    log("file selected: " + filename);
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
        log("found available port: " + port.portName());
    }
}

void MainWindow::checkAvailabilityStart()
{
    if( port.isOpen() )
    {
        ui->connectButton->setEnabled(false);
        ui->transmitButton->setEnabled(true);
    }
    else if( !portname.isEmpty() && !filename.isEmpty() )
    {
        ui->connectButton->setEnabled(true);
        ui->transmitButton->setEnabled(false);
    }
}

void MainWindow::log(const QString &text)
{
    ui->textBrowser->append(text);
}

void MainWindow::stop()
{
    disconnect(&port, &QSerialPort::readyRead, this, &MainWindow::dataAvailable);
    port.close();
    log("closed port");
    file->close();
    delete file;
    file = nullptr;
    transmitting = false;
    checkAvailabilityStart();
}

void MainWindow::connectSerial()
{
    currentPos = 0;
    ui->progressBar->reset();
    ui->transmitButton->setEnabled(false);
    connect(&port, &QSerialPort::readyRead, this, &MainWindow::dataAvailable);
    port.setPortName(portname);
    bool success = port.open(QIODevice::ReadWrite);

    if( !success )
    {
        log(QString("error opening port: %1").arg(port.error()));
        stop();
        return;
    }

    log("opened port");
    success = port.setBaudRate(9600);

    if( !success )
    {
        log(QString("error setting baud rate: %1").arg(port.error()));
        stop();
        return;
    }

    file = new QFile(filename);
    if (!file->open(QIODevice::ReadOnly))
    {
        log(QString("error opening file: %1").arg(filename));
        stop();
        return;
    }

    checkAvailabilityStart();
}

void MainWindow::transmit()
{
    ui->transmitButton->setEnabled(false);
    transmitting = true;
    sendNextByte();
}

void MainWindow::dataAvailable()
{
    QByteArray data = port.readAll();
    QString str = QString(data);
    //log(" >> " + str);
    if( transmitting && str == "o")
    {
        sendNextByte();
    }
}

void MainWindow::sendNextByte()
{
    if( file->atEnd() )
    {
        log("done.");
        stop();
        return;
    }

    char byte = 0;
    file->read(&byte, 1);
    currentPos++;
    qint64 filesize = file->size();
    float progress = currentPos / (float)filesize;
    int progressInt = (int)(progress * 100);
    ui->progressBar->setValue(progressInt);
    log(QString("<< %1").arg((uint8_t)byte));
    port.write(&byte, 1);
}

void MainWindow::cancel()
{
    log("canceled");
    stop();
}
