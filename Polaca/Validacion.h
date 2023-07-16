
/***********************************************************************
 * Module:  Validar.h
 * Author:  Ronny Ibarra, Milena Maldonado, Daniel Guaman
 * Modified: jueves, 02 de Julio de 2023
 * Purpose: Polaca Inversa
 ***********************************************************************/

#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
using namespace std;

class Validacion {
public:
    Validacion();
    string validarExpresion();
//    char *ingresoExpresion1(char const *msj);
//    char validarParentesis();
    bool esPunto(const std::string& expression)
    bool validarExpresion(const string& expresion);
    string ingresoExpresion(const char* msj);
};

#endif
