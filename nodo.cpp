#include "nodo.h"

Nodo::Nodo(QString valor)
{
    nodoIzquierdo = nullptr;
    nodoDerecho = nullptr;
    item = valor;
}

void Nodo::establecerNodoRaiz(QString valor)
{
    item = valor;
}

void Nodo::establecerNodoAlaIzquierda(Nodo *ptr)
{
    nodoIzquierdo = ptr;
}

void Nodo::establecerNodoAlaDerecha(Nodo *ptr)
{
    nodoDerecho = ptr;
}

Nodo *Nodo::obtenerNodoAlaDerecha()
{
    return nodoDerecho;
}

Nodo *Nodo::obtenerNodoAlaIzquierda()
{
    return nodoIzquierdo;
}

QString Nodo::obtenerItem()
{
    return item;
}
