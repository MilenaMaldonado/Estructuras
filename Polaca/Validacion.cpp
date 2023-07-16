/***********************************************************************
 * Module:  Validar.h
 * Author:  Ronny Ibarra, Milena Maldonado, Daniel Guaman
 * Modified: jueves, 02 de Julio de 2023
 * Purpose: Polaca Inversa
 ***********************************************************************/

#include <iostream>
#include <conio.h>
#include "Validacion.h"


Validacion::Validacion()
{
}

string Validacion::validarExpresion(){
	int n = 0;

	return to_string(n);
}

//char Validacion::validarParentesis() {
//
//    char r;
//    char c;
//   while ((c = getch()) != 13) {
//      
//        
//    
//                    if(c == 41 ||c == 43 || c == 45 || c == 42 || c == 47|| c == 94||c=='\b'){
//                        cout << c;
//                        r = c;
//                        if (c !='\b'){
//                            r='q';        
//                        }
//                        break;
//                    }
//        
//    }
//    return r;
//
//}

//   char* Validacion::ingresoExpresion1(char const *msj)
//    {
// 
//    char* a = new char[0];
//    char c;
//    int i = 0;
//    bool esPunto = false;
//    bool esParentesis= false;
//    
//    cout << msj;
//    while ((c = getch()) != 13) {
//      
//        if (c >= '0' && c <= '9' || c == 113|| c == 114 || c == 115 || c == 116|| c == 99
//            || c == 47||c == 42 || c == 43|| c == 45 || c == 94|| c == 40|| c == 41 ) {
//            cout << c;
//            a[i++] = c;
//            esPunto = false;
//           // esLetra= false;
//           if(c==40){
//            esParentesis= true;
//                if (c == '\b') {
//                i--;
//                cout << "\b \b";
//        }
//           }
//        //    if(c == 41){
//        //     esParentesis=false;
//        //             c=validarParentesis();
//        //             if(c=='q'){
//        //                 i--;
//        //             cout << "\b \b";        
//        //             }
//        //         }
//        }
//        else if (c == '.' && !esPunto) {
//            cout << c;
//            a[i++] = c;
//            esPunto = true;
//        }
//        else if (c == '\b') {
//            i--;
//            if (a[i] == '.') {
//                esPunto = false;
//               // esLetra = false;
//            }
//            cout << "\b \b";
//        }
//            
//        if (i == 0 && (a[0] >= 'a' && a[0] <= 'z')) {
//            a[0] = a[0] - 32;
//        }
//
//       
//
//    }
//    a[i] = '\0';
//    return a;
//    }

bool Validacion::esPunto(const std::string& expression) {
  int espunto = 0;
  for (char c : expression) {
    if (c == '.') {
      espunto++;
      if (espunto > 2) {
        return false;
      }
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '(' || c == ')' || c == '^') {
      espunto = 0;
    }
  }
  return true;
}

   
bool Validacion::validarExpresion(const string& expresion)
{
    int contadorParentesis = 0;
    bool esOperadorPermitido = false;
    bool esDecimalPermitido = true;  // Variable para controlar la validez de los decimales

    for (size_t i = 0; i < expresion.length(); i++) {
        char c = expresion[i];

        if (c == '(') {
            contadorParentesis++;
            esOperadorPermitido = false;
            esDecimalPermitido = true;  // Reiniciar la validación de decimales al abrir un paréntesis

            // Verificar si el paréntesis es seguido por un signo de menos para permitir números negativos
            if (i + 1 < expresion.length() && expresion[i + 1] == '-') {
                esOperadorPermitido = true;
                i++;  // Saltar al siguiente carácter después del signo de menos
            }
        }
        else if (c == ')') {
            contadorParentesis--;
            esOperadorPermitido = true;
            esDecimalPermitido = false;  // Desactivar la validación de decimales al cerrar un paréntesis
        }
         else if (isdigit(c) || c == '.' ) {
        //  if (!esDecimalPermitido && c == '.') {
        //     return false;  // Decimal no permitido en esta posición
        // }

        // Verificar si ya se encontró un punto decimal previamente en el número actual
        size_t puntoDecimal = expresion.find('.', i + 1);
        if (puntoDecimal != string::npos) {
                return false;  // Más de un punto decimal en el mismo número
            }

        esDecimalPermitido = false;  // Desactivar la validación de decimales después del primer punto decimal
        esOperadorPermitido = true;
}
        else if (isalpha(c)) {
            char letra = tolower(c);
            if (letra != 'q' && letra != 'r' && letra != 's' && letra != 't' && letra != 'c' && letra != 'y') {
                return false;  // Letra no permitida
            }
            esOperadorPermitido = true;
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (!esOperadorPermitido) {
                // Verificar si el signo de menos es para un número negativo
                if (c == '-' && i + 1 < expresion.length() && (isdigit(expresion[i + 1]) || expresion[i + 1] == '.')) {
                    esOperadorPermitido = true;
                    i++;  // Saltar al siguiente carácter después del signo de menos
                }
                else {
                    return false;  // Operador sin número o letra previo
                }
            }
            else {
                esOperadorPermitido = false;
            }
        }
        else {
            return false;  // Carácter no permitido
        }

        if (contadorParentesis < 0) {
            return false;  // Hay un paréntesis ")" sin su correspondiente "(" previo
        }
    }

    if (contadorParentesis != 0) {
        return false;  // Hay un paréntesis "(" sin cerrar
    }

    // Verificar si hay paréntesis sin operador entre ellos
    size_t pos = expresion.find(")(");
    if (pos != string::npos) {
        return false;  // Existen paréntesis sin operador entre ellos
    }

    return expresion.length() > 0;
   
}

string Validacion::ingresoExpresion(const char* msj)
{
    string expresion;
    bool expresionValida = false;

    while (!expresionValida)
    {
        cout << msj;
        getline(cin, expresion);
        expresionValida = validarExpresion(expresion);

        if (!expresionValida)
        {
            cout << "Expresion mal escrita. Por favor, intenta nuevamente." << endl;
        }
    }

    return expresion;
}
