#ifndef APLICACION_H
#define APLICACION_H

#include <QPixmap>
#include <QPainter>
#include <QDialog>
#include "nodo.h"

namespace Ui {
class Aplicacion;
}

class Aplicacion : public QDialog
{
    Q_OBJECT

public:
    explicit Aplicacion(QWidget *parent = 0);
    ~Aplicacion();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Aplicacion *ui;
    Nodo *nodoRaizIzquierdaDerecha;
    Nodo *nodoRaizDerechaIzquierda;
    Nodo *nodoRaizBalanceo;
    QString expresion;
    QString resultadoInOrden;
    int coordenaX;
    int coordenaY;
    int coordenaX2;
    int coordenaY2;
    int direccionDeDibujo;
    QPixmap *lienzo;
    QVector<QString> vectorExpresion;

    //funcion para realizar los arboles
    void realizarArbolIzquierdaDerecha();
    void realizarArbolDerechaIzquierda();
    void realizarArbolBlanceo();
    void obtenerRaizDelArbolBalanceo();
    void realizarParticionIzquierda(int indice);
    void realizarParticionDerecha(int indice);
    bool esOperador(QString operador);


    //Funciones para crear nodos a la izquierda o derecha y leer el arbol
    Nodo *obtenerUltimoNodoAlaIzquierda(Nodo *raiz);
    Nodo *obtenerUltimoNodoAlaDerecha(Nodo *raiz);
    void establecerNodoAlaDerecha(QString indice, QString operando, Nodo *raiz);
    void establecerNodoAlaDerecha(QString operando, Nodo *raiz);
    void establecerNodoAlaIzquierda(QString indice, QString operando, Nodo *raiz);
    void establecerNodoAlaIzquierda(QString operando, Nodo *raiz);
    void inOrdenIzqDer(Nodo *raiz);
    void inOrdenDerIzq(Nodo *raiz);
    void inOrdenBa(Nodo *raiz);

    //funciones extra
    void establecerCoordenadasIzqDere();
    void establecerCoordenadasDereIzq();
    void establecerCoordenadasBa();
    void colocarExpresionEnElVector();
    void mostrarRecorridoInOrden();

    //funciones para dibujar los arboles
    void limpiarLienzo();
    void dibujarArbolIzqDer(QString valor);
    void dibujarArbolDerIzq(QString valor);
    void dibujarArbolBa(QString valor);
};

#endif // APLICACION_H
