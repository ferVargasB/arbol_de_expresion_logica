#ifndef NODO_H
#define NODO_H
#include <QString>

class Nodo
{
public:
    Nodo(QString valor);
    void establecerNodoRaiz(QString valor);//establece el item
    void establecerNodoAlaIzquierda(Nodo *ptr);//coloca el apuntador del parametro
    void establecerNodoAlaDerecha(Nodo *ptr);//coloca el apuntador del parametro
    Nodo* obtenerNodoAlaDerecha();//regresa un aputador del nodo solicitado
    Nodo* obtenerNodoAlaIzquierda();//regresa un aputador del nodo solicitado
    QString obtenerItem();
private:
    QString item; //valor para identificar el nodo
    Nodo *nodoIzquierdo;
    Nodo *nodoDerecho;
};
#endif // NODO_H
