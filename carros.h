#ifndef CARROS_H
#define CARROS_H
#include <QString>
#include <QVector>
#include "tanque.h"

class Carros
{
    QVector <Tanque> tanque;
    QString placa;
    QString marca;
    int cilindraje;
public:
    Carros();
    Carros(QString, QString, int, QVector <Tanque>);
    QString getMarca();
    int getCilindraje();
    QString getPlaca();
    QVector<Tanque> getTanque();
    void setTanque(QVector<Tanque>);
    void setMarca(QString);
    void setPlaca(QString);
    void setCilindraje(int);
};

#endif // CARROS_H
