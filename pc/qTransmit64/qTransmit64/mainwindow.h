#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectButtonPushed();
    void portSelected(QListWidgetItem* item);

private:
    void initSerial();
    void checkAvailabilityStart();

    Ui::MainWindow *ui;
    QString filename;
    QString portname;
};

#endif // MAINWINDOW_H
