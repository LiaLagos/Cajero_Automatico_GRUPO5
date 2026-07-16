/* UNIVERSIDAD NACIONAL AUTÓNOMA DE HONDURAS
FACULTAD DE CIENCIAS ECONÓMICAS, ADMINISTRATIVAS Y CONTABLES
DEPARTAMENTO DE INFORMÁTICA
DIA 044 Programación Básica
Proyecto II "FINANCIERA PUMA-Bank"
IIPAC 2026
Cindy Yaquelin Rodriguez Aguilar
Ruth Aracely Castañeda Gonzales
Aldo Misael Flores Amador
Lia Samira Lagos Palacios 
*/

#include <iostream>
#include <string>
#include <iomanip>   // Librería para dar formato a la salida (limitar decimales)
//#include <windows.h>// PARA CONFIGURAR EL IDIOMA ESPAÑOL
#include <vector>    //MEJORAMOS EL PROGRAMA USANDO VECTORES
#include <cctype>
using namespace std; 

/*================================
VARIABLES Y VECTORES GLOBALES
==================================*/

//Varibles para la apertura de la cuenta
string nombre;
string apellido;
char genero;
int edad;
double SaldoPrincipal;
vector<string> beneficiarios;
//variables para acreditar
double saldo;
int contadorAcreditaciones;
int saldoLTC;

//variables para ver saldo
int contadorConsultas = 0;       // Máximo 8 consultas
int saldoBTC;
int saldoETH;

//variables para transferencias de criptomonedas (Integrante 4)
// matrizCripto: fila = beneficiario (0,1,2), columna = 0:BTC 1:ETH 2:LTC
// Guarda cuánto le ha transferido el usuario a cada beneficiario
vector<vector<int>> matrizCripto;
int puntosAcumulados = 0;

/*=====================================
PROTOTIPOS DE FUNCIONES
========================================
*/

//01
bool esTextoValido(string texto);
//02
void aperturaCuenta (string &nombre, string &apellido, char &genero, int &edad,
                     double &saldoPrincipal, vector<string> &beneficiarios
                    );
//03
void mostrarDatosRegistro(const string &nombre, const string &apellido,
                          int edad, char genero, double saldoPrincipal,
                          const vector<string> &beneficiarios);
//04
void menuPrincipal() ;
//05
void acreditar(double &saldoPrincipal, int &contadorAcreditaciones, int &saldoLTC);
//06
int validarOpcionMenu ();
//07
void procesoMenu();
//08
void debitar(double &saldoPrincipal);
//09
void verSaldo(double &saldoPrincipal, int &contadorConsultas, int &saldoLTC, int &saldoBTC, int &saldoETH);

/*========================================
MAIN PRINCIPAL

int main() { 
     setlocale(LC_ALL, "es_ES.UTF-8");
    int opcion;
    beneficiarios.resize(3);
    //Regitsro del usuario
    aperturaCuenta(nombre, apellido, genero, edad, SaldoPrincipal, beneficiarios);
    //Estadistica del registro
    mostrarDatosRegistro(nombre, apellido, edad, genero, SaldoPrincipal, beneficiarios);
    //menuPrincipal
    procesoMenu();


    return 0;
}


/*========================================
PROCESO DE FUNCIONES
//01
bool esTextoValido(string texto) {

    if (texto.empty()) { //verifica que no este vacio
        return false;
    }
    for (int i = 0; i < texto.length(); i++) {   //verificamos caracter por caracter
        char c = texto[i];
        if (!isalpha(c) && !isspace(c)) { //verificamos que cada caracter este estre a y z
            return false;
        }
    }
    return true;
}

//02
void aperturaCuenta (string &nombre, string &apellido, char &genero, int &edad,
                     double &saldoPrincipal, vector<string> &beneficiarios)
{ 
    string _nombre, _apellido;
    char _genero;
    int _edad = 0;

    beneficiarios.resize(3);

    cout << "\n---BIENVENIDO AL REGISTRO DE CLIENTE DE FINANCIERA PUMA-Bank ---" << endl;
    cout << "==================================================================" << endl;
    cout << "\n                 REGISTRO DE CLIENTE\n\n";

    //==============================
    //Solicitar y validar el nombre
    //==============================
    do {
        cout << "Ingrese su nombre: ";
        getline(cin, _nombre);
        if (!esTextoValido(_nombre)) {
            cout << "[Error] El nombre no puede estar vacio ni contener numeros.\n\n";
        }
    } while (!esTextoValido(_nombre));

    //==============================
    //Solicitar y validar el apellido
    //==============================
    do {
        cout << "Ingrese su apellido: ";
        getline(cin, _apellido);
        if (!esTextoValido(_apellido)) {
            cout << "[Error] El apellido no puede estar vacio ni contener numeros.\n\n";
        }
    } while (!esTextoValido(_apellido));

    //============================
    //Solicitar y validar el genero
    //============================
    do {
        cout << "Ingrese su genero (M/F): ";
        cin >> _genero;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[Error] Entrada inválida. Debe ingresar M o F.\n";
        _genero = 'X';
    continue;
    }
        _genero = toupper(_genero);

    if (_genero != 'M' && _genero != 'F') {
        cout << "[Error] Solo se permiten 'M' o 'F'.\n";
    }

    cin.ignore(10000, '\n'); // Limpia el buffer para evitar problemas con getline

    } while (_genero != 'M' && _genero != 'F');


    //=========================
    //Solicitar y validar la edad
    //=========================
    do {
    cout << "Ingrese su edad: ";

    // Detecta si el usuario solo presiona ENTER
    if (cin.peek() == '\n') {
        cout << "[Error] El campo no puede quedar vacío.\n";
        cin.ignore(10000, '\n');   // Limpia el ENTER
        _edad = 0;
        continue;
    }

    cin >> _edad;

    // Detecta letras o símbolos
    if (cin.fail()) {
        cout << "[Error] Entrada inválida. Debe ingresar solo números enteros.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        _edad = 0;
        continue;
    }

    // Detecta rango inválido
    if (_edad < 18 || _edad > 100) {
        cout << "[Error] La edad debe estar entre 18 y 100 años.\n";
    }

    cin.ignore(10000, '\n'); // Limpia buffer para evitar problemas con getline

} while (_edad < 18 || _edad > 100);



    //=========================
    //Saldo principal
    //=========================
      cout << "\nIMPORTANTE---Para la apertura de la cuenta se requiere un mínimo de L.200\n";
    do {
   
        cout << "Ingrese el saldo principal: ";

    // Detectar si el usuario solo presiona ENTER
    if (cin.peek() == '\n') {
        cout << "[Error] El campo no puede quedar vacío.\n";
        cin.ignore(10000, '\n');   // Limpia el ENTER
        saldoPrincipal = 0;
        continue;
    }

    cin >> saldoPrincipal;

    // Validar que el usuario no ingrese letras o símbolos
    if (cin.fail()) {
        cin.clear();                 // Limpia el estado de error
        cin.ignore(10000, '\n');     // Limpia el buffer
        cout << "[Error] Debe ingresar un número válido (puede incluir decimales).\n";
        saldoPrincipal = 0;          // Fuerza a repetir el ciclo
        continue;                    // Vuelve al inicio del do-while
    }

    // Validar que el saldo no sea menor a 200
    if (saldoPrincipal < 200) {
        cout << "[Error] El saldo principal no puede ser menor a L.200.\n";
    } else {
        cout << "Saldo válido: L." << fixed << setprecision(2) << saldoPrincipal << "\n";
    }

    cin.ignore(10000, '\n'); // Limpia buffer para evitar problemas con getline

    } while (saldoPrincipal < 200);

    //=========================
    //Beneficiarios
    //=========================
    cout << "\nIngrese los 3 beneficiarios (Nombre del Beneficiario):\n";

    for (int i = 0; i < 3; i++) {
        string nombreBenef;

        do {
            cout << "Beneficiario " << (i + 1) << ": ";
            getline(cin, nombreBenef);

            if (!esTextoValido(nombreBenef)) {
                cout << "[Error] El nombre del beneficiario debe contener solo letras y espacios.\n";
            }

        } while (!esTextoValido(nombreBenef));

        beneficiarios[i] = nombreBenef;
    }


    //=========================
    //Asignar valores finales
    //=========================
    nombre = _nombre;
    apellido = _apellido;
    genero = _genero;
    edad = _edad;
}

//03
void mostrarDatosRegistro(const string &nombre, const string &apellido,
                          int edad, char genero, double saldoPrincipal,
                          const vector<string> &beneficiarios){
    cout << "\nRegistro Completado con éxito en FINANCIERA PUMA-BANK!" << endl;
    system("pause");
    system("cls");

     string generoTexto;
    if (genero == 'M') {
        generoTexto = "Masculino";
    } else {
        generoTexto = "Femenino";
    }

    cout << "\n==================================================\n";
    cout << "     CLIENTE REGISTRADO CON ÉXITO EN EL SISTEMA!\n";
    cout << "==================================================\n";
    cout << "  * Nombre completo : " << nombre << " " << apellido << "\n";
    cout << "  * Edad            : " << edad << " años\n";
    cout << "  * Género          : " << generoTexto << "\n";

    cout << "  * Saldo Inicial   : L." 
         << fixed << setprecision(2) << saldoPrincipal << "\n";

    cout << "--------------------------------------------------\n";
    cout << "  BENEFICIARIOS REGISTRADOS:\n";

    for (int i = 0; i < beneficiarios.size(); i++) {
        cout << "  -> " << beneficiarios[i] << "\n";
    }

    cout << "==================================================\n\n";
    system ("pause");
 }

 //04
void menuPrincipal()
{
    
        system("cls");
        cout << "==============================\n";
        cout << "        CAJERO VIRTUAL        \n";
        cout << "==============================\n";
        cout << "1) Acreditar\n";
        cout << "2) Debitar\n";
        cout << "3) Ver saldo\n";
        cout << "4) Transferencias de criptomonedas\n";
        cout << "5) Salir\n";
        cout << "==============================\n";

       
}

//05
void acreditar(double &saldoPrincipal, int &contadorAcreditaciones, int &saldoLTC)
{
    double monto = 0;

    cout << "-----------------------------------" << endl;
    cout << "            ACREDITACION           " << endl;
    cout << "-----------------------------------" << endl;
    cout << "------ FINANCIERA   PUMA-BANK -----" << endl;
    cout << "-----------------------------------" << endl;
    cout << "\nBienvenido al sistema de acreditacion de PUMA-BANK!" << endl;
    cout << "Por cada 2 acreditaciones válidas, usted obtiene 1 Litte Coin.\n" << endl;
    cout << "Saldo Actual: L." << fixed << setprecision(2) << saldoPrincipal << endl;
    // Solicitar monto
    do {
        cout << "Ingrese la cantidad en L. que desea acreditar (mínimo L.100): ";

        if (cin.peek() == '\n') {
            cout << "[ERROR] El campo no puede quedar vacío.\n";
            cin.ignore(10000, '\n');
            continue;
        }

        cin >> monto;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Debe ingresar un número válido.\n";
            monto = 0;
            continue;
        }

        if (monto < 100) {
            cout << "[ERROR] El monto mínimo para acreditar es L.100.\n";
            continue;
        }

        cin.ignore(10000, '\n');

    } while (monto < 100);
    system ("cls");
    // Acreditación válida
    saldoPrincipal += monto;
    cout << "-----------------------------------" << endl;
    cout << "            ACREDITACION           " << endl;
    cout << "-----------------------------------" << endl;
    cout << "------ FINANCIERA   PUMA-BANK -----" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Listo, usted ha acreditado: L." << monto << " a su cuenta.\n";
    cout << "Su cuenta ahora tiene: L." 
         << fixed << setprecision(2) << saldoPrincipal << endl;

    contadorAcreditaciones++;

    if (contadorAcreditaciones == 2)
    {
        saldoLTC += 1;
        contadorAcreditaciones = 0;

        cout << "\n¡Felicidades! Usted ha ganado 1 Litte Coin (LTC)!" << endl;
        cout << "LTC acumulados: " << saldoLTC << " LTC\n";
    }

}

//06
int validarOpcionMenu() {
    string entrada;

//10  (Integrante 4)

//11  (Integrante 4)

//12  (Integrante 4)

//13  (Integrante 4) - menu envoltorio de la opción 4


/*========================================
MAIN PRINCIPAL

int main() { 
     setlocale(LC_ALL, "es_ES.UTF-8");
    int opcion;
    beneficiarios.resize(3);
    matrizCripto.resize(3, vector<int>(3, 0)); // inicializa la matriz 3x3 en 0
    //Regitsro del usuario
    aperturaCuenta(nombre, apellido, genero, edad, SaldoPrincipal, beneficiarios);
    //Estadistica del registro
    mostrarDatosRegistro(nombre, apellido, edad, genero, SaldoPrincipal, beneficiarios);
    //menuPrincipal
    procesoMenu();


    return 0;
}


/*========================================
PROCESO DE FUNCIONES
=======================================*/
//01
bool esTextoValido(string texto) {

    if (texto.empty()) { //verifica que no este vacio
        return false;
    }
    for (int i = 0; i < texto.length(); i++) {   //verificamos caracter por caracter
        char c = texto[i];
        if (!isalpha(c) && !isspace(c)) { //verificamos que cada caracter este estre a y z
            return false;
        }
    }
    return true;
}

//02
void aperturaCuenta (string &nombre, string &apellido, char &genero, int &edad,
                     double &saldoPrincipal, vector<string> &beneficiarios)
{ 
    string _nombre, _apellido;
    char _genero;
    int _edad = 0;

    beneficiarios.resize(3);

    cout << "\n---BIENVENIDO AL REGISTRO DE CLIENTE DE FINANCIERA PUMA-Bank ---" << endl;
    cout << "==================================================================" << endl;
    cout << "\n                 REGISTRO DE CLIENTE\n\n";

    //==============================
    //Solicitar y validar el nombre
    //==============================
    do {
        cout << "Ingrese su nombre: ";
        getline(cin, _nombre);
        if (!esTextoValido(_nombre)) {
            cout << "[Error] El nombre no puede estar vacio ni contener numeros.\n\n";
        }
    } while (!esTextoValido(_nombre));

    //==============================
    //Solicitar y validar el apellido
    //==============================
    do {
        cout << "Ingrese su apellido: ";
        getline(cin, _apellido);
        if (!esTextoValido(_apellido)) {
            cout << "[Error] El apellido no puede estar vacio ni contener numeros.\n\n";
        }
    } while (!esTextoValido(_apellido));

    //============================
    //Solicitar y validar el genero
    //============================
    do {
        cout << "Ingrese su genero (M/F): ";
        cin >> _genero;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[Error] Entrada inválida. Debe ingresar M o F.\n";
        _genero = 'X';
    continue;
    }
        _genero = toupper(_genero);

    if (_genero != 'M' && _genero != 'F') {
        cout << "[Error] Solo se permiten 'M' o 'F'.\n";
    }

    cin.ignore(10000, '\n'); // Limpia el buffer para evitar problemas con getline

    } while (_genero != 'M' && _genero != 'F');


    //=========================
    //Solicitar y validar la edad
    //=========================
    do {
    cout << "Ingrese su edad: ";

    // Detecta si el usuario solo presiona ENTER
    if (cin.peek() == '\n') {
        cout << "[Error] El campo no puede quedar vacío.\n";
        cin.ignore(10000, '\n');   // Limpia el ENTER
        _edad = 0;
        continue;
    }

    while (true) {
        cout << "Ingrese una opcion (1-5): ";
        getline(cin, entrada);

        // Detectar ENTER vacío
        if (entrada.empty()) {
            cout << "\n[ERROR] El campo no puede quedar vacio.\n";
            continue;
        }

        // Detectar si NO es número
        bool esNumero = true;
        for (char c : entrada) {
            if (!isdigit(c)) {
                esNumero = false;
                break;
            }
        }

        if (!esNumero) {
            cout << "\n[ERROR] Debe ingresar solo numeros.\n";
            continue;
        }

        // Convertir a entero
        opcion = stoi(entrada);

        // Validar rango
        if (opcion < 1 || opcion > 5) {
            cout << "\n[ERROR] La opcion debe estar entre 1 y 5.\n";
            continue;
        }

        return opcion; // ← Opción válida
    }
}

//07
void procesoMenu(){
    int opcion = 0;



    //=========================
    //Saldo principal
    //=========================
      cout << "\nIMPORTANTE---Para la apertura de la cuenta se requiere un mínimo de L.200\n";
    do {
        menuPrincipal();
         // Validación de opción
       opcion = validarOpcionMenu();


        switch (opcion)
        {
            case 1:
                system("cls");
                // ACREDITAR
                acreditar(SaldoPrincipal, contadorAcreditaciones, saldoLTC);
                cout << "\n>>> PARA VOLVER AL MENÚ PRINCIPAL: ";
                system ("pause");
                break;

            case 2:
                system("cls");
                debitar (SaldoPrincipal);
                cout << "\n>>> PARA VOLVER AL MENÚ PRINCIPAL: ";
                system ("pause");
                break;

            case 3:
                // VER SALDO

                system("cls");
                verSaldo(SaldoPrincipal, contadorConsultas, saldoLTC, saldoBTC, saldoETH);
                cout << "\n>>> PARA VOLVER AL MENÚ PRINCIPAL: ";
                system ("pause");
                break;

            case 4:
                // TRANSFERENCIAS (te la puedo crear si querés)
                cout << "\n>>> Función TRANSFERENCIAS aún no implementada.\n";
                system("pause");
                break;

            case 5:
                cout << "\nGracias por usar FINANCIERA PUMA‑Bank.\n";
                system("pause");
                break;

            default:
                cout << "\n[ERROR] Opción inválida.\n";
                system("pause");
                break;
        }

    } while (opcion != 5);
}

//08
void debitar(double &saldoPrincipal)
{
    double monto = 0;
    double comision = 0;
    double saldoFinal = 0;

    cout << "-----------------------------------" << endl;
    cout << "               DEBITAR             " << endl;
    cout << "-----------------------------------" << endl;
    cout << "------ FINANCIERA   PUMA-BANK -----" << endl;
    cout << "-----------------------------------" << endl;
    cout << "\nBienvenido al sistema de débitos de PUMA-BANK!" << endl;
    cout << "Por cada retiro se aplica una comisión según el monto.\n" << endl;
    cout << "Saldo Actual: L." << fixed << setprecision(2) << saldoPrincipal << endl;
    // Solicitar monto
    do {
        cout << "Ingrese la cantidad en L. que desea retirar: ";

        // Detectar ENTER vacío
        if (cin.peek() == '\n') {
            cout << "[ERROR] El campo no puede quedar vacío.\n";
            cin.ignore(10000, '\n');
            continue;
        }

        cin >> monto;
        system("cls");

        // Validación de número
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Debe ingresar solo números. No se permiten letras ni símbolos.\n";
            monto = 0;
            continue;
        }

        // Validación de monto positivo
        if (monto <= 0) {
            cout << "[ERROR] El monto debe ser mayor a 0.\n";
            continue;
        }

        cin.ignore(10000, '\n'); // Limpia buffer

    } while (monto <= 0);

    // Calcular comisión
    if (monto >= 100 && monto <= 1000) {
        comision = 10.00;
    } 
    else if (monto > 1000) {
        comision = monto * 0.08;  // 8%
    } 
    else {
        comision = 0; // Retiros menores a 100 no tienen comisión
    }

    // Calcular saldo final
    saldoFinal = saldoPrincipal - monto - comision;

    // Validar saldo mínimo del proyecto
    if (saldoFinal < 100) {
        cout << "\n[ERROR] No se puede realizar el retiro." << endl;
        cout << "Lo menos que puede tener en la cuenta son L.100.00." << endl;
        cout << "Saldo actual: L." << fixed << setprecision(2) << saldoPrincipal << endl;
        return;
    }

    // Retiro válido
    saldoPrincipal = saldoFinal;
    system ("cls");
    cout << "-----------------------------------" << endl;
    cout << "               DEBITAR             " << endl;
    cout << "-----------------------------------" << endl;
    cout << "------ FINANCIERA   PUMA-BANK -----" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Retiro realizado con éxito." << endl;
    cout << "Monto retirado: L." << fixed << setprecision(2) << monto << endl;
    cout << "Comisión aplicada: L." << fixed << setprecision(2) << comision << endl;
    cout << "Saldo final: L." << fixed << setprecision(2) << saldoPrincipal << endl;
    cout << "-----------------------------------" << endl;
}
// 09 VER SALDO
// INTEGRANTE 3 (RUTH): AQUI SISTEMA DE SALDO

// 09 VER SALDO
void verSaldo(double &saldoPrincipal, int &contadorConsultas, int &saldoLTC, int &saldoBTC, int &saldoETH) {
  
      // Validar límite de 8 consultas
      if (contadorConsultas >= 8) {
          cout << "Ha alcanzado el limite de 8 consultas de saldo." << endl;
          return;
      }

      // Verificar que el cobro no deje la cuenta por debajo de L.100 
      if ((saldoPrincipal - 5) < 100) {
          cout << "No se puede realizar la consulta. El cobro de L.5.00" << endl;
          cout << "dejaria su saldo por debajo del minimo permitido (L.100.00)." << endl;
          return;
      }
  
      // Cobrar L.5.00 por consulta
      saldoPrincipal = saldoPrincipal - 5;
      cout << "Se ha cobrado L.5.00 por consulta de saldo." << endl;
  
      // Incrementar contador de consultas
      contadorConsultas = contadorConsultas + 1;
  
      // Calcular consultas restantes
      int consultasRestantes = 8 - contadorConsultas;

      // Mostrar saldo principal 
      cout << fixed << setprecision(2); // Formatear salida a 2 decimales
      cout << "\n============================================" << endl;
      cout << "           CONSULTA DE SALDO" << endl;
      cout << "============================================" << endl;
      cout << "Saldo Principal: L." << saldoPrincipal << endl;
  
      // Mostrar saldo de criptomonedas
      cout << "--------------------------------------------" << endl;
      cout << "       Saldo en Criptomonedas" << endl;
      cout << "--------------------------------------------" << endl;

      string nombresCripto[3] = {"Bitcoin (BTC)", "Ethereum (ETH)", "Litte Coin (LTC)"};
      int valoresCripto[3] = {saldoBTC, saldoETH, saldoLTC};
  
      for (int i = 0; i < 3; i++) {
          cout << nombresCripto[i] << ": " << valoresCripto[i] << endl;
      }
  
      // Mostrar consultas realizadas y restantes
      cout << "--------------------------------------------" << endl;
      cout << "Consultas realizadas: " << contadorConsultas << " de 8" << endl;
      cout << "Consultas restantes: " << consultasRestantes << endl;
      cout << "============================================" << endl;
  }
