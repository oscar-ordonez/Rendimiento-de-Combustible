#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "carros.h"
#include "tanque.h"
#include <QVector>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <fstream>
#include <stdio.h>
#include <ctype.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QVector<Carros> carros;
QVector<Tanque> tanque_carros;

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_agregar_boton_clicked()//agrega un nuevo carro
{
    QString placa = ui->agregar_placa->text();
    QString marca = ui->agregar_marca->text();
    QString stringCilindraje = ui->agregar_cilindraje->text();
    QVector<Tanque> tanque;
    int cilindraje = stringCilindraje.toInt();
    carros.push_back(Carros(placa, marca, cilindraje, tanque));

    ui->tanque_placa->addItem(placa);
    ui->reporte_placa->addItem(placa);
    ui->eliminar_placa->addItem(placa);

    ui->agregar_placa->setText(" ");
    ui->agregar_marca->setText(" ");
    ui->agregar_cilindraje->setText(" ");
}

void MainWindow::on_tanque_boton_clicked()//agrega gasolina al carro
{
    QString fecha = ui->tanque_dia->text() + "/" + ui->tanque_mes->text() + "/" + ui->tanque_ano->text();
    QString stringLempiras = ui->tanque_lempiras->text();
    QString stringLitros = ui->tanque_litros->text();
    QString stringKilometros = ui->tanque_kilometros->text();
    int lempiras = stringLempiras.toInt();
    int litros = stringLitros.toInt();
    int kilometros = stringKilometros.toInt();
    int index = ui->tanque_placa->currentIndex();
    QVector<Tanque> temporal = carros[index].getTanque();
    temporal.push_back(Tanque(fecha, lempiras, litros, kilometros));
    carros[index] = Carros(carros[index].getPlaca(), carros[index].getMarca(), carros[index].getCilindraje(), temporal);

    ui->tanque_dia->setValue(1);
    ui->tanque_ano->setValue(1990);
    ui->tanque_mes->setValue(1);
    ui->tanque_lempiras->setText(" ");
    ui->tanque_litros->setText(" ");
    ui->tanque_kilometros->setText(" ");
    ui->tanque_placa->setCurrentIndex(0);
}

void MainWindow::on_pushButton_clicked()//eliminar carro
{
    int index = ui->eliminar_placa->currentIndex();
    ui->eliminar_placa->clear();
    ui->reporte_placa->clear();
    ui->tanque_placa->clear();
    carros.remove(index);
    for(int i=0; i<carros.size(); i++){
        ui->eliminar_placa->addItem(carros[i].getPlaca());
        ui->reporte_placa->addItem(carros[i].getPlaca());
        ui->tanque_placa->addItem(carros[i].getPlaca());
    }
}
void MainWindow::on_reporte_placa_activated(int index)
{
    ui->reporte_marca->setText(carros[ui->reporte_placa->currentIndex()].getMarca());
    QString cilindraje = QString::number(carros[ui->reporte_placa->currentIndex()].getCilindraje());
    ui->reporte_cilindraje->setText(cilindraje);
    ui->reporte_cuadro->setText(" ");
    ui->reporte_cuadro->append("    FECHA \t       LEMPIRAS               LITROS \tKILOMETROS\n");
    for(int i = 0; i<carros[ui->reporte_placa->currentIndex()].getTanque().size();i++){
        ui->reporte_cuadro->append(carros[ui->reporte_placa->currentIndex()].getTanque()[i].toString());
    }

    double totalKilometros = 0;
    double totalLitros = 0;
    double totalLempiras = 0;
    for(int i = 0; i<carros[ui->reporte_placa->currentIndex()].getTanque().size();i++){
        totalKilometros += carros[ui->reporte_placa->currentIndex()].getTanque()[i].getKilometros();
        totalLitros += carros[ui->reporte_placa->currentIndex()].getTanque()[i].getLitros();
        totalLempiras += carros[ui->reporte_placa->currentIndex()].getTanque()[i].getLempiras();
    }

    double kilometrosporlitros = totalKilometros/totalLitros;
    double lempirasporkilometros = totalLempiras/totalKilometros;
    double totalGalones = totalLitros/0.2641720512415584;
    double kilometrosporgalones = totalKilometros/totalGalones;
    QString stringkilometrosporlitros = QString::number(kilometrosporlitros);
    QString stringkilometrosporgalones = QString::number(kilometrosporgalones);
    QString stringlempirasporkilometros = QString::number(lempirasporkilometros);
    ui->reporte_kmporlitro->setText(stringkilometrosporlitros);
    ui->reporte_lpsporkm->setText(stringlempirasporkilometros);
    ui->reporte_kmporgal->setText(stringkilometrosporgalones);

    //sacar los dias acumulados
    int diasAcumulados = 0;
    QString dias;
    QString sdia, smes, sano, stemporal;
    QString sdia2, smes2, sano2, stemporal2;

    int contador = 0;
    for(int i=0; i<carros[index].getTanque().size();i++){
        dias = carros[index].getTanque()[i].getFecha();
        if(i ==0){
             for(int j = 0; j<dias.size();j++){
                 if(dias[j]=='/'){
                   if (contador==0){
                        sdia = stemporal;
                        stemporal ="";
                        contador++;
                    }else if(contador==1){
                        smes = stemporal;
                        stemporal ="";
                        contador++;
                    }else if(contador==2){
                        sano = stemporal;
                        stemporal ="";
                        contador++;
                    }
                }else{
                    stemporal += dias[j];
                }
            }
        }else{
            for(int j = 0; j<dias.size();j++){
                if(dias[j]=='/'){
                  if (contador==0){
                       sdia2 = stemporal2;
                       stemporal2 = "";
                       contador++;
                   }else if(contador==1){
                       smes2 = stemporal2;
                       stemporal2 = "";
                       contador++;
                   }else if(contador==2){
                       sano2 = stemporal2;
                       stemporal2 = "";
                       contador++;
                   }
               }else{
                   stemporal2 += dias[j];
               }
           }
            int ano2 = sano2.toInt();
            int ano = sano.toInt();
            int mes2 = smes2.toInt();
            int mes = smes.toInt();
            int dia2 = sdia2.toInt();
            int dia = sdia.toInt();
            diasAcumulados += (((ano2-ano)*12)+((mes2-mes)*31)+(dia2-dia));
            dia = dia2;
            ano = ano2;
            mes = mes2;
        }
        double lempiraspordia = totalLempiras/diasAcumulados;
        QString stringlempiraspordia = QString::number(lempiraspordia);
        ui->reporte_lpspordia->setText(stringlempiraspordia);
    }



}

void MainWindow::on_actionExit_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Redimiento Carros", "/home/oscar/Documentos","Text Files (*.txt);;All Files (*.*)");
    if(!fileName.isEmpty()){
        curFile = fileName;
        saveFile();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(curFile.isEmpty()){
        on_actionExit_triggered();
    }else{
        saveFile();
    }
}

void MainWindow::saveFile()
{
    QFile file(curFile);
    if(file.open(QFile::WriteOnly)){
        for(int i=0; i<carros.size();i++){
            QString cilindraje = QString::number(carros[i].getCilindraje());
            file.write((carros[i].getPlaca()+",").toUtf8());
            file.write((carros[i].getMarca()+"_").toUtf8());
            file.write((cilindraje+";").toUtf8());
            for(int j=0; j<carros[i].getTanque().size();j++){
                file.write((carros[i].getTanque()[j].getFecha()+"<").toUtf8());
                QString kilometros = QString::number(carros[i].getTanque()[j].getKilometros());
                file.write((kilometros+">").toUtf8());
                QString litros = QString::number(carros[i].getTanque()[j].getLitros());
                file.write((litros+"!").toUtf8());
                QString lempiras = QString::number(carros[i].getTanque()[j].getLempiras());
                file.write((lempiras+"$").toUtf8());
            }
        }
    }else{
        QMessageBox::warning(this,"Rendimiento Carros", tr("No se puede escribir archivo %1.\nError: %2").arg(curFile).arg(file.errorString()));
    }
}

bool MainWindow::maybeSave()
{
    return true;
}

void MainWindow::on_actionOpen_triggered()
{
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this,"Rendimiento Carros","/home/oscar/Documentos","Text Files (*.txt);;All Files (*.*)");
         QFile file(fileName);
         if(!file.exists()){

            ui->reporte_cuadro->append(file.readAll());
            if(file.open(QFile::ReadOnly)){
                carros.clear();
                int contador = -1;
                int contador2 = -1;
                QString fecha = "";
                QString kilometros = "";
                QString litros = "";
                QString lempiras = "";
                QString temporal;
                int ikilometros, ilitros, ilempiras;
                QVector <Tanque> tanque;
                QString line = file.readAll();
                ui->reporte_cuadro->setText(line);
                //getline(file,line);
                for(int i=0; i < file.readAll().size();i++){
                    if(line[i] == ','){
                        if(contador >= 0){
                            carros[contador].setTanque(tanque);
                            tanque.clear();
                        }
                        contador++;
                        carros[contador].setPlaca(temporal);
                        temporal = "";
                    }else if(line[i] == '_'){
                        carros[contador].setMarca(temporal);
                        temporal = "";
                    }else if(line[i] == ';'){
                        int cilindraje = temporal.toInt();
                        carros[contador].setCilindraje(cilindraje);
                        temporal = "";
                    }else if(line[i] == '<'){
                        if(contador2 >=0){
                            fecha = temporal;
                            tanque.push_back(Tanque(fecha, ikilometros, ilitros, ilempiras));
                        }else{
                            fecha = temporal;
                        }
                        contador2++;
                        temporal = "";
                    }else if(line[i] == '>'){
                        kilometros = temporal;
                        ikilometros = kilometros.toInt();
                        temporal = "";
                    }else if(line[i] == '!'){
                        litros = temporal;
                        ilitros = litros.toInt();
                        temporal = "";
                    }else if(line[i] == '$'){
                        lempiras = temporal;
                        ilempiras = lempiras.toInt();
                        temporal = "";
                    }else{
                        temporal += line[i];
                    }
                }
                ui->eliminar_placa->clear();
                ui->reporte_placa->clear();
                ui->tanque_placa->clear();
                for(int i=0; i<carros.size(); i++){
                    ui->eliminar_placa->addItem(carros[i].getPlaca());
                    ui->reporte_placa->addItem(carros[i].getPlaca());
                    ui->tanque_placa->addItem(carros[i].getPlaca());
                }
            }else{
                QMessageBox::warning(this, "Rendimiento Carros",tr("No se puede leer archivo %1.\nError: %2").arg(fileName).arg(file.errorString()));
            }
        }
    }
}
