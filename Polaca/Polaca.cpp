/***********************************************************************
 * Universidad de las Fuerzas Armadas ESPE
 * Module:  Polaca.cpp
 * Author:  Ronny Ibarra, Milena Maldonado, Daniel Guaman
 * Modified: miércoles, 23 de Junio de 2023 8:20:18
 * Purpose: Polaca Inversa
 ***********************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include "Polaca.h"

using namespace std;

Polaca::Polaca(void)
{
}



bool Polaca::isOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool Polaca::isFuncion(char c) {
    return c == 's' || c == 'c' || c == 't'  || c == 'r' || c == 'q';
}

bool Polaca::isOperadorStr(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

bool Polaca::isFuncionStr(string c) {
    return c == "s" || c == "c" || c == "t" || c == "r" || c == "q";
}


int Polaca::obtenerPrecedencia(string operador) {
    if (operador == "s" || operador == "c" || operador == "t")
        return 4;
    else if (operador == "^" || operador == "r" || operador == "q")
        return 3;
    else if (operador == "*" || operador == "/")
        return 2;
    else if (operador == "+" || operador == "-")
        return 1;
    else
        return 0;
}


Pila<string> Polaca::convertirExpresionInfijaAPrefija(string expresionInfija) {
    Pila<string> pilaSalida;
    Pila<string> pilaOperadores;
    string infijoRevertido;

    for (auto it = expresionInfija.rbegin(); it != expresionInfija.rend(); ++it) {
        if (*it == '(')
            infijoRevertido += ')';
        else if (*it == ')')
            infijoRevertido += '(';
        else
            infijoRevertido += *it;
    }

    string numero;
    bool esNegativo = false;

    for (char c : infijoRevertido) {
        if (std::isdigit(c) || c == '.') {
            numero = c + numero; // Agregar el dígito o el punto al inicio del número
        }
        else if (c == '-' && (numero.empty() || esNegativo)) {
            // Detectar números negativos
            esNegativo = true;
        }
        else {
            if (!numero.empty()) {
                if (esNegativo) {
                    numero = "-" + numero; // Agregar el signo negativo al número
                    esNegativo = false;
                }
                pilaSalida.push(numero);
                numero.clear(); // Limpiar la variable para el siguiente número
            }
            if (c == '(') {
                while (!pilaOperadores.empty() && pilaOperadores.top() != ")") {
                    pilaSalida.push(pilaOperadores.top());
                    pilaOperadores.pop();
                }
                // Quitar el paréntesis de cierre de la pila de operadores
                if (!pilaOperadores.empty())
                    pilaOperadores.pop();
            }
            else {
                while (!pilaOperadores.empty() && obtenerPrecedencia(string(1, c)) <= obtenerPrecedencia(pilaOperadores.top())) {
                    pilaSalida.push(pilaOperadores.top());
                    pilaOperadores.pop();
                }
                if (c != ')')
                    pilaOperadores.push(string(1, c));
            }
        }
    }

    if (!numero.empty()) {
        if (esNegativo) {
            numero = "-" + numero; // Agregar el signo negativo al número
        }
        pilaSalida.push(numero);
    }

    while (!pilaOperadores.empty()) {
        pilaSalida.push(pilaOperadores.top());
        pilaOperadores.pop();
    }

    return pilaSalida;
}



Pila<string> Polaca::convertirExpresionInfijaAPosfija(string expresionInfija) {
    Pila<string> pilaPosfija;
    Pila<string> pilaOperadores;
    string numero;
    bool ultimoCaracterFueOperador = true;  // Variable para detectar números negativos

    for (char c : expresionInfija) {
        if (isdigit(c) || c == '.') {
            numero += c;
            ultimoCaracterFueOperador = false;
        }
        else if (c == '-' && ultimoCaracterFueOperador) {
            // Manejo de números negativos
            numero += c;
            ultimoCaracterFueOperador = false;
        }
        else {
            if (!numero.empty()) {
                pilaPosfija.push(numero);
                numero.clear();
            }
            if (c == '(') {
                pilaOperadores.push(string(1, c));
            }
            else if (c == ')') {
                while (!pilaOperadores.empty() && pilaOperadores.top() != "(") {
                    pilaPosfija.push(pilaOperadores.top());
                    pilaOperadores.pop();
                }
                if (!pilaOperadores.empty() && pilaOperadores.top() == "(") {
                    pilaOperadores.pop();
                }
            }
            else {
                while (!pilaOperadores.empty() && obtenerPrecedencia(string(1, c)) <= obtenerPrecedencia(pilaOperadores.top())) {
                    pilaPosfija.push(pilaOperadores.top());
                    pilaOperadores.pop();
                }
                pilaOperadores.push(string(1, c));
            }
            ultimoCaracterFueOperador = true;
        }
    }

    if (!numero.empty()) {
        // Agregar el último número construido (si existe) a la pila de operandos
        pilaPosfija.push(numero);
    }

    while (!pilaOperadores.empty()) {
        pilaPosfija.push(pilaOperadores.top());
        pilaOperadores.pop();
    }

    Pila<string> pilaSalida;
    while (!pilaPosfija.empty()) {
        pilaSalida.push(pilaPosfija.top());
        pilaPosfija.pop();
    }

    return pilaSalida;
}



double Polaca::calcular(Pila<string>& expresion) {
    Pila<double> pilaOperandos;
    Operaciones op;

    int tamInicial = expresion.size();

    for (int i = 0; i < tamInicial; i++) {
        string token = expresion.top();
        expresion.pop();

        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            // Si el token es un número (incluyendo números negativos), lo convertimos a double y lo agregamos a la pila de operandos
            double numero = stod(token);
            pilaOperandos.push(numero);
        }
        else if (isOperador(token[0])) {
            // Si el token es un operador, realizamos la operación correspondiente
            double operand2 = pilaOperandos.top();
            pilaOperandos.pop();
            double operand1 = pilaOperandos.top();
            pilaOperandos.pop();

            double resultado;

            switch (token[0]) {
            case '+':
                resultado = operand1 + operand2;
                break;
            case '-':
                resultado = operand1 - operand2;
                break;
            case '*':
                resultado = operand1 * operand2;
                break;
            case '/':
                resultado = operand1 / operand2;
                break;
            case '^':
                resultado = op.potencia(operand1, operand2);
                break;
            }

            pilaOperandos.push(resultado);
        }
        else if (isFuncion(token[0])) {
            // Si el token es una función, aplicamos la función al operando de la pila
            double operando = pilaOperandos.top();
            pilaOperandos.pop();

            double resultado;

            switch (token[0]) {
            case 's':
                resultado = op.sin(operando);
                break;
            case 'c':
                resultado = op.cos(operando);
                break;
            case 't':
                resultado = op.tan(operando);
                break;
            case 'r':
                resultado = op.raizCuadrada(operando);
                break;
            case 'q':
                resultado = op.raizCubica(operando);
                break;
            }

            pilaOperandos.push(resultado);
        }
    }

    return pilaOperandos.top();
}
