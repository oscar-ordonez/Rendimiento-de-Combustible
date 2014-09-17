#ifndef TANQUE_H
#define TANQUE_H
#include <QString>

class Tanque
{
    int kilometros, litros, lempiras;
    QString fecha;
public:
    Tanque();
    void setKilometros(int);
    void setLitros(int);
    void setLempiras(int);
    void setFecha(QString);
    int getKilometros();
    int getLitros();
    int getLempiras();
    QString getFecha();
    QString toString()const;
    Tanque(QString, int, int, int);
};

#endif // TANQUE_H
