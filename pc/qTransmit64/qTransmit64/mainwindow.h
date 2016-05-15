#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QSerialPort>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void progressChanged(int progress);

public slots:
    void selectButtonPushed();
    void portSelected(QListWidgetItem* item);
    void connectSerial();
    void transmit();
    void dataAvailable();
    void cancel();

private:
    void initSerial();
    void checkAvailabilityStart();
    void log(const QString& text);
    void sendNextByte();
    void stop();

    Ui::MainWindow *ui;
    QString filename;
    QString portname;
    QSerialPort port;
    QFile* file;
    bool transmitting;
};

#endif // MAINWINDOW_H
