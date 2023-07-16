/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Module:  main.cpp
 * Author:  Ronny Ibarra, Milena Maldonado, Daniel Guaman
 * Modified: miércoles, 23 de Junio de 2023 8:20:18
 * Purpose: Polaca Inversa
 ***********************************************************************/


#include<iostream>
#include "Polaca.cpp"
#include "Operaciones.cpp"
#include "Validacion.cpp"
#include <string>
#include <conio.h>

using namespace std;

void mostrarMenu() {
    cout << "Opciones disponibles:" << std::endl;
    cout << "  + : Suma" << endl;
    cout << "  - : Resta" << endl;
    cout << "  * : Multiplicacion" << endl;
    cout << "  / : Division" << endl;
    cout << "  ^ : Potencia" << endl;
    cout << "  r : Raiz cuadrada" << endl;
    cout << "  s : Seno" << endl;
    cout << "  c : Coseno" << endl;
    cout << "  t : Tangente" << endl;
    cout << "  q : Raiz cubica" << endl;
    cout << "Ingrese la expresion matematica en notacion infija: " << endl;
}

int main() {
    Polaca polaca;
    string expresion;
    Operaciones op;
    Validacion v;
    bool validacion;

    do {
    	system("cls");
        try {
            mostrarMenu();
            expresion= v.ingresoExpresion(">");
            //expresion = v.ingresoExpresion1("> ");
            //getline(cin, expresion);
            if(validacion==false){
                Pila<string> prefijo = polaca.convertirExpresionInfijaAPrefija(expresion);
                Pila<string> posfijo = polaca.convertirExpresionInfijaAPosfija(expresion);

                cout << endl << "Expresion original: " << expresion << endl;
                cout << "Expresion en notacion prefijo: ";
                prefijo.print();
                cout << "Expresion en notacion posfija: ";
                posfijo.print();

                printf("resultado:  %.2lf\n", polaca.calcular(posfijo));
            }
            cout<<endl;
            system("pause");

        } catch (const runtime_error& error) {
            cout << "Error: " << error.what() << endl;
        }
    } while (!expresion.empty());

    return 0;
}
