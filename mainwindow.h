#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void on_agregar_boton_clicked();

    void on_tanque_boton_clicked();

    void on_reporte_placa_activated(int index);

    void on_pushButton_clicked();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    void saveFile();
    QString curFile;
    bool maybeSave();
};

#endif // MAINWINDOW_H
