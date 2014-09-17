#include "tanque.h"
#include <QString>

Tanque::Tanque(){

}

Tanque::Tanque(QString fecha, int lempiras, int litros, int kilometros){
    this->fecha = fecha;
    this->lempiras = lempiras;
    this->litros = litros;
    this->kilometros = kilometros;
}

QString Tanque::getFecha(){
    return fecha;
}

int Tanque::getLempiras(){
    return lempiras;
}

int Tanque::getLitros(){
    return litros;
}

int Tanque::getKilometros(){
    return kilometros;
}

void Tanque::setFecha(QString fecha){
    this->fecha = fecha;
}

void Tanque::setLempiras(int lempiras){
    this->lempiras = lempiras;
}

void Tanque::setLitros(int litros){
    this->litros= litros;
}

void Tanque::setKilometros(int kilometros){
    this->kilometros = kilometros;
}

QString Tanque::toString()const{
    QString cadena = "";
    QString lemp = QString::number(lempiras);
    QString lit = QString::number(litros);
    QString kilo = QString::number(kilometros);
    cadena +=fecha;
    cadena +="\t          ";
    cadena +=lemp;
    cadena +="\t                  ";
    cadena +=lit;
    cadena +="\t     ";
    cadena +=kilo;
    cadena +="\n";
    return cadena;
}
