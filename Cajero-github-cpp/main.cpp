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
#include <windows.h>// PARA CONFIGURAR EL IDIOMA ESPAÑOL
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

//06
int validarOpcionMenu ();
//07
void procesoMenu();
//08

//09

//10  (Integrante 4)
int validarSubOpcionCripto(int minOpcion, int maxOpcion);

//11  (Integrante 4)
void transferenciaCripto(double &saldoPrincipal, vector<string> &beneficiarios,
                          vector<vector<int>> &matrizCripto,
                          int &saldoBTC, int &saldoETH, int &saldoLTC,
                          int &puntosAcumulados);
//12  (Integrante 4)
void consultaBeneficiarios(const vector<string> &beneficiarios,
                            const vector<vector<int>> &matrizCripto,
                            int puntosAcumulados);
//13  (Integrante 4) - menu envoltorio de la opción 4
void criptomonedas(double &saldoPrincipal, vector<string> &beneficiarios,
                   vector<vector<int>> &matrizCripto,
                   int &saldoBTC, int &saldoETH, int &saldoLTC,
                   int &puntosAcumulados);

/*========================================
MAIN PRINCIPAL
=========================================*/

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
// INTEGRANTE 2 (CINDY): AQUI SISTEMA DE ACREDITACION






//06
int validarOpcionMenu() {
    string entrada;
    int opcion;

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
// PROCESO DE MENU
void procesoMenu(){
    int opcion = 0;

    do {
        menuPrincipal();
         // Validación de opción
       opcion = validarOpcionMenu();


        switch (opcion)
        {
            case 1:
                system("cls");
                // ACREDITAR
                
                cout << "\n>>> PARA VOLVER AL MENÚ PRINCIPAL: ";
                system ("pause");
                break;

            case 2:
                system("cls");
                // DEBITAR
            
                cout << "\n>>> PARA VOLVER AL MENÚ PRINCIPAL: ";
                system ("pause");
                break;

            case 3:
                // VER SALDO
                system("cls");
                
                cout << "\n>>> PARA VOLVER AL MENÚ PRINCIPAL: ";
                system ("pause");
                break;

            case 4:
                // TRANSFERENCIAS DE CRIPTOMONEDAS (Integrante 4)
                system("cls");
               criptomonedas(SaldoPrincipal, beneficiarios,
                   matrizCripto, saldoBTC, saldoETH, saldoLTC,
                   puntosAcumulados);
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
// INTEGRANTE 2 (CINDY): AQUI SISTEMA DE DEBITAR







// 09 VER SALDO
// INTEGRANTE 3 (RUTH): AQUI SISTEMA DE SALDO









/*==========================================================
  (INTEGRANTE 4 - ALDO)
  Opción 4: Transferencias de criptomonedas + Consulta de beneficiarios
===========================================================*/

// 10) Validador de submenú (reutiliza la misma lógica que validarOpcionMenu,
//     pero con rango configurable, para el submenú de criptomonedas)

int validarSubOpcionCripto(int minOpcion, int maxOpcion) {
    string entrada;
    int opcion;
 
    while (true) {
        cout << "Ingrese una opcion (" << minOpcion << "-" << maxOpcion << "): ";
        getline(cin, entrada);
 
        if (entrada.empty()) {
            cout << "\n[ERROR] El campo no puede quedar vacio.\n";
            continue;
        }
 
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
 
        opcion = stoi(entrada);
 
        if (opcion < minOpcion || opcion > maxOpcion) {
            cout << "\n[ERROR] La opcion debe estar entre " << minOpcion << " y " << maxOpcion << ".\n";
            continue;
        }
 
        return opcion;
    }
}
//11.
void transferenciaCripto(double &saldoPrincipal, vector<string> &beneficiarios,
                          vector<vector<int>> &matrizCripto,
                          int &saldoBTC, int &saldoETH, int &saldoLTC,
                          int &puntosAcumulados) {
 
    system("cls");
 
    int opcionBenef, opcionCripto;
    int cantidadCripto;
    double precioDolar = 0, totalDolares, totalLempiras;
    string nombreCripto;      // Nombre de la cripto seleccionada (BTC/ETH/LTC)
    int puntosGanados = 0;    // Puntos ganados en ESTA transacción
    const double TIPO_CAMBIO = 26.42;
 
    cout << "============================================" << endl;
    cout << "     TRANSFERENCIA DE CRIPTOMONEDAS" << endl;
    cout << "============================================" << endl;
    cout << "Seleccione el beneficiario:\n";
    for (int i = 0; i < 3; i++) {
        cout << (i + 1) << ") " << beneficiarios[i] << endl;
    }
    opcionBenef = validarSubOpcionCripto(1, 3);
 
    cout << "\nSeleccione la criptomoneda:\n";
    cout << "1) BTC = $25\n";
    cout << "2) ETH = $20\n";
    cout << "3) LTC = $10\n";
    opcionCripto = validarSubOpcionCripto(1, 3);
 
    switch (opcionCripto) {
        case 1: precioDolar = 25; nombreCripto = "BTC"; break;
        case 2: precioDolar = 20; nombreCripto = "ETH"; break;
        case 3: precioDolar = 10; nombreCripto = "LTC"; break;
    }
 
    // Validar cantidad de cripto (número entero positivo)
    do {
        cout << "Ingrese la cantidad de criptomoneda a transferir: ";
 
        if (cin.peek() == '\n') {
            cout << "[ERROR] El campo no puede quedar vacio.\n";
            cin.ignore(10000, '\n');
            cantidadCripto = 0;
            continue;
        }
 
        cin >> cantidadCripto;
 
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "[ERROR] Debe ingresar un numero entero valido.\n";
            cantidadCripto = 0;
            continue;
        }
 
        if (cantidadCripto <= 0) {
            cout << "[ERROR] La cantidad debe ser mayor a 0.\n";
        }
 
        cin.ignore(10000, '\n');
 
    } while (cantidadCripto <= 0);
 
    totalDolares = cantidadCripto * precioDolar;
    totalLempiras = totalDolares * TIPO_CAMBIO;
 
    system("cls");
    cout << "============================================" << endl;
    cout << "     TRANSFERENCIA DE CRIPTOMONEDAS" << endl;
    cout << "============================================" << endl;
 
    if (saldoPrincipal >= totalLempiras) {
        saldoPrincipal -= totalLempiras;
 
        int idxBenef = opcionBenef - 1;
 
        // Guardar en la matriz: fila = beneficiario, columna = cripto elegida
        matrizCripto[idxBenef][opcionCripto - 1] += cantidadCripto;
 
        // Actualizar el saldo de criptomonedas del usuario (lo usa Ver saldo)
        switch (opcionCripto) {
            case 1:
                saldoBTC += cantidadCripto;
                puntosGanados = 5;
                break;
            case 2:
                saldoETH += cantidadCripto;
                puntosGanados = 3;
                break;
            case 3:
                saldoLTC += cantidadCripto;
                puntosGanados = 2;
                break;
        }
 
        puntosAcumulados += puntosGanados;
 
        cout << fixed << setprecision(2);
        cout << "\nTransferencia exitosa a " << beneficiarios[idxBenef] << endl;
        cout << "Enviado: " << cantidadCripto << " " << nombreCripto << " ($"
             << totalDolares << " / L." << totalLempiras << ")\n";
        cout << "Saldo restante: L." << saldoPrincipal << endl;
 
        // Mensaje de puntos ANTES de continuar
        cout << "\n¡Felicidades! Ha acumulado " << puntosGanados
             << " puntos por esta transaccion.\n";
 
    } else {
        cout << fixed << setprecision(2);
        cout << "\n[ERROR] Saldo insuficiente para realizar esta transferencia.\n";
        cout << "Se necesitan L." << totalLempiras << " y su saldo actual es L." << saldoPrincipal << endl;
    }
 
    cout << "\n>>> Presione una tecla para continuar...";
    system("pause");
}
// 12) Consulta de beneficiarios
void consultaBeneficiarios(const vector<string> &beneficiarios,
                            const vector<vector<int>> &matrizCripto,
                            int puntosAcumulados) {
 
    system("cls");
 
    int opcionBenef;
 
    cout << "============================================" << endl;
    cout << "        CONSULTA DE BENEFICIARIOS" << endl;
    cout << "============================================" << endl;
    cout << "Seleccione el beneficiario a consultar:\n";
    for (int i = 0; i < 3; i++) {
        cout << (i + 1) << ") " << beneficiarios[i] << endl;
    }
    opcionBenef = validarSubOpcionCripto(1, 3);
 
    int idx = opcionBenef - 1;
    int btc = matrizCripto[idx][0];
    int eth = matrizCripto[idx][1];
    int ltc = matrizCripto[idx][2];
 
    double totalDolares = (btc * 25) + (eth * 20) + (ltc * 10);
    double totalLempiras = totalDolares * 26.42;
 
    system("cls");
    cout << fixed << setprecision(2);
    cout << "============================================" << endl;
    cout << "  RESUMEN DE " << beneficiarios[idx] << endl;
    cout << "============================================" << endl;
    cout << "BTC recibido: " << btc << endl;
    cout << "ETH recibido: " << eth << endl;
    cout << "LTC recibido: " << ltc << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Total enviado en dolares: $" << totalDolares << endl;
    cout << "Total enviado en lempiras: L." << totalLempiras << endl;
    cout << "Puntos acumulados del usuario: " << puntosAcumulados << endl;
    cout << "============================================" << endl;
 
    cout << "\n>>> Presione una tecla para continuar...";
    system("pause");
}


// 13) Menú envoltorio de la opción 4 (submenú de criptomonedas)
void criptomonedas(double &saldoPrincipal, vector<string> &beneficiarios,
                   vector<vector<int>> &matrizCripto,
                   int &saldoBTC, int &saldoETH, int &saldoLTC,
                   int &puntosAcumulados) {
 
    int subOpcion = 0;
 
    do {
        system("cls");
        cout << "============================================" << endl;
        cout << "     MENU DE CRIPTOMONEDAS - PUMA-BANK" << endl;
        cout << "============================================" << endl;
        cout << "1) Transferir criptomoneda a un beneficiario\n";
        cout << "2) Consultar beneficiario\n";
        cout << "0) Regresar al menu principal\n";
        cout << "============================================" << endl;
 
        subOpcion = validarSubOpcionCripto(0, 2);
 
        switch (subOpcion) {
            case 1:
                transferenciaCripto(saldoPrincipal, beneficiarios, matrizCripto,
                                     saldoBTC, saldoETH, saldoLTC, puntosAcumulados);
                break;
            case 2:
                consultaBeneficiarios(beneficiarios, matrizCripto, puntosAcumulados);
                break;
            case 0:
                cout << "\nRegresando al menu principal...\n";
                system("pause");
                break;
        }
 
    } while (subOpcion != 0);
}