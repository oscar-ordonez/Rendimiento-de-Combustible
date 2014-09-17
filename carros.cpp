#include "carros.h"
#include <QString>
#include <QVector>
#include "tanque.h"

Carros::Carros(QString placa, QString marca, int cilindraje, QVector<Tanque> tanque){
    this-> placa = placa;
    this-> marca = marca;
    this-> cilindraje = cilindraje;
    this-> tanque = tanque;
}

Carros::Carros(){

}

QString Carros::getPlaca(){
    return placa;
}

QString Carros::getMarca(){
    return marca;
}

int Carros::getCilindraje(){
    return cilindraje;
}

void Carros::setPlaca(QString placa){
    this->placa = placa;
}

void Carros::setMarca(QString marca){
    this->marca = marca;
}

void Carros::setCilindraje(int cilindraje){
    this->cilindraje = cilindraje;
}

void Carros::setTanque(QVector<Tanque> tanque){
    this->tanque = tanque;
}

QVector<Tanque> Carros::getTanque(){
    return tanque;
}
