#include "aplicacion.h"
#include "ui_aplicacion.h"
#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QTime>

Aplicacion::Aplicacion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Aplicacion)
{
    ui->setupUi(this);
    direccionDeDibujo = 1; //indice la direccion a dibujar de los nodos
    expresion = "true | false and false | true | false ! false";
    //expresion = "! true ! true ! true";
    colocarExpresionEnElVector(); //coloca la expresion en un vector

    nodoRaizIzquierdaDerecha = new Nodo("R"); //crea un nodo raiz para indicar donde empezar
    nodoRaizDerechaIzquierda = new Nodo("R"); //crea un nodo raiz para indicar donde empezar

    lienzo = new QPixmap( ui->labelLienzo->width(), ui->labelLienzo->height() ); //inicia el pixmap con el tamaño del label
    limpiarLienzo(); //llena el pixmap con el color blanco

    nodoRaizIzquierdaDerecha->establecerNodoAlaIzquierda( new Nodo("I")); //añade un nodo de prueba
    nodoRaizDerechaIzquierda->establecerNodoAlaDerecha( new Nodo("I")); //añade un nodo de prueba

}

Aplicacion::~Aplicacion()
{
    delete ui;
}

void Aplicacion::realizarArbolIzquierdaDerecha() //Funcion que realiza el arbol de izq a derecha
{
    for ( auto indice = 0; indice < vectorExpresion.size(); indice++){
        if ( esOperador( vectorExpresion.at(indice)) )// si el caracter es un operador
            establecerNodoAlaDerecha( vectorExpresion.at(indice), vectorExpresion.at(indice - 1), nodoRaizIzquierdaDerecha );
        else if ( indice == vectorExpresion.size() - 1) //si es el ultimo operando lo coloca a la derecha del ultimo nodo a la derecha
             establecerNodoAlaDerecha( vectorExpresion.at(indice), nodoRaizIzquierdaDerecha);
    }
}

void Aplicacion::realizarArbolDerechaIzquierda() //Funcion que realiza el arbol de derecha a izquierda
{
    for ( auto indice = vectorExpresion.size() - 1; indice >= 0; indice--){
        if ( esOperador( vectorExpresion.at(indice)) )// si el caracter es un operador
            establecerNodoAlaIzquierda( vectorExpresion.at(indice), vectorExpresion.at(indice + 1), nodoRaizDerechaIzquierda );
        else if ( indice == 0 ) //si es el ultimo operador lo coloca a la derecha del ultimo nodo a la derecha
             establecerNodoAlaIzquierda( vectorExpresion.at(indice), nodoRaizDerechaIzquierda);
    }
}

void Aplicacion::realizarArbolBlanceo() //Funcion que inicia en cascada para el arbol de balanceo
{
    obtenerRaizDelArbolBalanceo(); //Funcion para obtener la raiz del arbol de balanceo

}

void Aplicacion::obtenerRaizDelArbolBalanceo() //Cuerpo de la funcion para obtener la raiz del arbol de balanceo
{
    int indice = vectorExpresion.size() / 2; //divide en dos el vector y obtiene un indice
    nodoRaizBalanceo = new Nodo( vectorExpresion.at(indice) ); //realiza la raiz del  nodo
    realizarParticionIzquierda( indice ); //realiza la parte izquierda del arbol de balanceo
    realizarParticionDerecha( indice ); //realiza la parte derecha del arbol de balanceo
}

void Aplicacion::realizarParticionIzquierda(int indice) //Funcion que realice la parte izquierda del arbol de balanceo
{
    indice--;
    while ( indice >= 0 ) {
        if ( esOperador( vectorExpresion.at(indice)) )// si el caracter es un operador
            establecerNodoAlaIzquierda( vectorExpresion.at(indice), vectorExpresion.at(indice + 1), nodoRaizBalanceo );
        else if ( indice == 0 ) //si es el ultimo operador lo coloca a la derecha del ultimo nodo a la derecha
             establecerNodoAlaIzquierda( vectorExpresion.at(indice), nodoRaizBalanceo);
       indice--;
    }
}

void Aplicacion::realizarParticionDerecha(int indice) //Funcion que realice la parte derecha del arbol de balanceo
{
    indice++;
    while ( indice < vectorExpresion.size() ){
        if ( esOperador( vectorExpresion.at(indice)) )// si el caracter es un operador
            establecerNodoAlaDerecha( vectorExpresion.at(indice), vectorExpresion.at(indice - 1), nodoRaizBalanceo );
        else if ( indice == vectorExpresion.size() - 1) //si es el ultimo operando lo coloca a la derecha del ultimo nodo a la derecha
             establecerNodoAlaDerecha( vectorExpresion.at(indice), nodoRaizBalanceo);
        indice++;
    }
}

bool Aplicacion::esOperador(QString operador) //Funcion para saber si el indice es un operador
{
    if ( operador == "!") // si es el operador not
        return true;
    else if ( operador == "|") //si es el operador or
        return true;
    else if ( operador == "and") //si es el operador and
        return true;
    else
        return false; // no es un operador
}

Nodo *Aplicacion::obtenerUltimoNodoAlaIzquierda(Nodo *raiz)  //Funcion recursiva para encontrar el Ultimo Nodo a la Izquierda
{
    if ( raiz->obtenerNodoAlaIzquierda()== nullptr )
        return raiz;
    else
        return obtenerUltimoNodoAlaIzquierda( raiz->obtenerNodoAlaIzquierda() );
}

Nodo *Aplicacion::obtenerUltimoNodoAlaDerecha(Nodo *raiz) //Funcion recursiva para encontrar el Ultimo Nodo a la derecha
{
    if ( raiz->obtenerNodoAlaDerecha() == nullptr ) //si la raiz ya no tiene nodo
        return raiz; //caso baso, detiene la funcion
    else
        return obtenerUltimoNodoAlaDerecha( raiz->obtenerNodoAlaDerecha() ); //paso recursivo
}

void Aplicacion::establecerNodoAlaDerecha(QString indice, QString operando, Nodo *raiz) //Funcion para crear nodo a al derecha
{
    Nodo *nodoActual = obtenerUltimoNodoAlaDerecha( raiz ); //Procedimiento para crear nodo
    nodoActual->establecerNodoAlaDerecha( new Nodo(indice) ); //Crear nodo con el valor del indice a la derecha
    nodoActual = obtenerUltimoNodoAlaDerecha( raiz ); //obtiene la direccion del apuntador actual de nodo
    nodoActual->establecerNodoAlaIzquierda( new Nodo(operando) ); //Crear nodo con el valor del indice a la derecha
}

void Aplicacion::establecerNodoAlaDerecha(QString operando, Nodo *raiz) //Funcion para crear nodo a al derecha, es una sobrecarga
{
    Nodo *nodoActual = obtenerUltimoNodoAlaDerecha( raiz ); //Procedimiento para crear nodo, pero si es el ultimo operador
    nodoActual->establecerNodoAlaDerecha( new Nodo(operando) ); //Procedimiento para crear nodo a la derecha
}

void Aplicacion::establecerNodoAlaIzquierda(QString indice, QString operando, Nodo *raiz) //Funcion para crear nodo a al izq
{
    Nodo *nodoActual = obtenerUltimoNodoAlaIzquierda( raiz );//Procedimiento para crear nodo
    nodoActual->establecerNodoAlaIzquierda( new Nodo(indice) );//Crear nodo con el valor del indice a la izq
    nodoActual = obtenerUltimoNodoAlaIzquierda( raiz );//obtiene la direccion del apuntador actual de nodo
    nodoActual->establecerNodoAlaDerecha( new Nodo(operando) );//Crear nodo con el valor del indice a la izquierda
}

void Aplicacion::establecerNodoAlaIzquierda(QString operando, Nodo *raiz)//Funcion para crear nodo a al derecha, es una sobrecarga
{
    Nodo *nodoActual = obtenerUltimoNodoAlaIzquierda( raiz );//Procedimiento para crear nodo, pero si es el ultimo operador
    nodoActual->establecerNodoAlaIzquierda( new Nodo(operando) );//Procedimiento para crear nodo a la derecha
}

void Aplicacion::inOrdenDerIzq(Nodo *raiz) //Funcion recursiva para recorrer el arbol dercha a Izq
{
    if ( raiz != nullptr){ //si la raiz es diferente a null
        inOrdenDerIzq( raiz->obtenerNodoAlaIzquierda() ); //paso recursivo
        resultadoInOrden += raiz->obtenerItem();
        resultadoInOrden += " ";
        dibujarArbolDerIzq( raiz->obtenerItem() ); //cada que lee un nodo lo dibuja
        inOrdenDerIzq( raiz->obtenerNodoAlaDerecha() ); //pason recursivo
    }
}

void Aplicacion::inOrdenBa(Nodo *raiz) //Funcion recursiva para recorrer el arbol balanceo
{
    if ( raiz != nullptr){ //si la raiz es diferente a null
        inOrdenBa( raiz->obtenerNodoAlaIzquierda() ); //paso recursivo
        resultadoInOrden += raiz->obtenerItem();
        resultadoInOrden += " ";
        dibujarArbolBa( raiz->obtenerItem() ); //cada que lee un nodo lo dibuja
        inOrdenBa( raiz->obtenerNodoAlaDerecha() ); //pason recursivo
    }
}

void Aplicacion::establecerCoordenadasIzqDere() //Establece las coordenadas para dibujar el arbol de izquierda a derecha
{
    coordenaX = 40;//coordenadas
    coordenaY = 70;//operandos
    coordenaX2 = coordenaX + 40;
    coordenaY2 = coordenaY - 40;//operadores
}

void Aplicacion::establecerCoordenadasDereIzq() //Establece las coordenadas para dibujar el arbol de derecha a izquierda
{
    coordenaX = 500;//coordenadas
    coordenaY = 70;//operandos
    coordenaX2 = coordenaX - 40;
    coordenaY2 = coordenaY - 40;//operadores
}

void Aplicacion::establecerCoordenadasBa() //Establece las coordenadas para dibujar el arbol de balanceo
{
    coordenaX = 500; //coordenadas
    coordenaY = 70; //operandos
    coordenaX2 = coordenaX - 40; //coordenadas
    coordenaY2 = coordenaY - 40;//operadores
}

void Aplicacion::colocarExpresionEnElVector() //coloca cada palabra en un vector de cadenas
{
    QString palabra;

    for ( auto indice : expresion ){
        if ( !indice.isSpace() ){ //si el indice es diferente a un espacio, sigue la palabra
            palabra += indice; //se concatena a la palabra
        }
        else{
            vectorExpresion.push_back(palabra); //termina la palabra y se añade al vector
            palabra = "";
        }
    }
    vectorExpresion.push_back(palabra);
}

void Aplicacion::mostrarRecorridoInOrden() //Funcion para mostrar el resultado del recorrido en un label
{
    ui->labelIndicadorIzqDer->setText(resultadoInOrden);
}

void Aplicacion::dibujarArbolIzqDer(QString valor) //Funcion para dibujar el arbol de izq a derecha
{
    QPainter p(lienzo);
    p.setPen(Qt::black);
    if ( direccionDeDibujo == 1){
        p.drawText(coordenaX, coordenaY,valor);
        coordenaX += 40;//aumenta las coordenaas
        coordenaY += 40;//de los operandos
        direccionDeDibujo = 2;
    }
    else if ( direccionDeDibujo == 2){
        p.drawText(coordenaX2, coordenaY2, valor);
        p.drawEllipse(coordenaX2-5, coordenaY2-15, 30, 30);
        coordenaX2 = coordenaX + 40;//aumenta las coordenaas
        coordenaY2 = coordenaY - 40;//de los operadores
        direccionDeDibujo = 1;
    }
    ui->labelLienzo->setPixmap(*lienzo);
}

void Aplicacion::dibujarArbolDerIzq(QString valor) //Funcion para dibujar el arbol de derecha a izquierda
{
    QPainter p(lienzo);
    p.setPen(Qt::black);
    if ( direccionDeDibujo == 1){
        p.drawText(coordenaX, coordenaY,valor);
        coordenaX -= 40;//aumenta las coordenaas
        coordenaY += 40;//de los operandos
        direccionDeDibujo = 2;
    }
    else if ( direccionDeDibujo == 2){
        p.drawText(coordenaX2, coordenaY2, valor);
        p.drawEllipse(coordenaX2-5, coordenaY2-15, 30, 30);
        coordenaX2 = coordenaX - 40;//aumenta las coordenaas
        coordenaY2 = coordenaY - 40;//de los operadores
        direccionDeDibujo = 1;
    }
    ui->labelLienzo->setPixmap(*lienzo);
}

void Aplicacion::dibujarArbolBa(QString valor) //Funcion para dibujar el arbol de balanceo
{
    QPainter p(lienzo);
    p.setPen(Qt::black);
    if ( direccionDeDibujo == 1){
        p.drawText(coordenaX, coordenaY,valor);
        coordenaX += 40; //aumenta las coordenadas
        coordenaY += 40; //de los operandos
        direccionDeDibujo = 2;
    }
    else if ( direccionDeDibujo == 2){
        p.drawText(coordenaX2, coordenaY2, valor);
        p.drawEllipse(coordenaX2-5, coordenaY2-15, 30, 30);
        coordenaX2 = coordenaX + 40; //aumenta las coordenaas
        coordenaY2 = coordenaY - 40; //de los operadores
        direccionDeDibujo = 1;
    }
    ui->labelLienzo->setPixmap(*lienzo);
}

void Aplicacion::inOrdenIzqDer(Nodo *raiz){ //Proceso de recorrer el arbol con Inorden
    if ( raiz != nullptr){ //caso base
        inOrdenIzqDer( raiz->obtenerNodoAlaIzquierda() ); //paso recursivo
        resultadoInOrden += raiz->obtenerItem();
        resultadoInOrden += " ";
        dibujarArbolIzqDer( raiz->obtenerItem() ); //cada que lee un nodo lo dibuja
        inOrdenIzqDer( raiz->obtenerNodoAlaDerecha() );  //paso recursivo
    }
}

void Aplicacion::limpiarLienzo() //Funciones que llena el pixmap de color blanco
{
    lienzo->fill(Qt::white);
    ui->labelLienzo->setPixmap(*lienzo);
}

void Aplicacion::on_pushButton_clicked() //Funcion cuando se presiona el arbol de izquierda a derecha
{
    establecerCoordenadasIzqDere(); //Establece coordeandas para realizar el dibujo del arbol que se solicita
    limpiarLienzo(); //Llena de color blanco el pixmap lienzo
    resultadoInOrden = "";
    QMessageBox::information(this, "Arbol izquierda a derecha", "Arbol izquierda a derecha");
    realizarArbolIzquierdaDerecha();
    inOrdenIzqDer( nodoRaizIzquierdaDerecha ); //realiza el balanceo del arbol que se solicita
    ui->labelIndicadorIzqDer->setText( resultadoInOrden ); //pega el resultado del recorrido en el label
}

void Aplicacion::on_pushButton_2_clicked() //Funcion cuando se presiona el arbol derecha a izquierda
{
    establecerCoordenadasDereIzq(); //Establece coordeandas para realizar el dibujo del arbol que se solicita
    limpiarLienzo(); //Llena de color blanco el pixmap lienzo
    resultadoInOrden = "";  //restablecer la cadena iroden
    QMessageBox::information(this, "Arbol izquierda a derecha", "Arbol izquierda a derecha");
    realizarArbolDerechaIzquierda();
    inOrdenDerIzq( nodoRaizDerechaIzquierda ); //realiza el balanceo del arbol que se solicita
    ui->labelIndicadorDerIzq->setText( resultadoInOrden ); //pega el resultado del recorrido en el label
}

void Aplicacion::on_pushButton_3_clicked() //Funcion cuando se presiona el arbol de balanceo
{
    establecerCoordenadasBa(); //Establece coordeandas para realizar el dibujo del arbol que se solicita
    limpiarLienzo(); //Llena de color blanco el pixmap lienzo
    resultadoInOrden = ""; //restablecer la cadena iroden
    QMessageBox::information(this, "Arbol balanceado", "Arbol balanceado");
    realizarArbolBlanceo();
    inOrdenBa( nodoRaizBalanceo ); //realiza el balanceo del arbol que se solicita
    ui->labelIndicadorBa->setText( resultadoInOrden ); //pega el resultado del recorrido en el label
}
