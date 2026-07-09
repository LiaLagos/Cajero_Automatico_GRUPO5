/* UNIVERSIDAD NACIONAL AUTÓNOMA DE HONDURAS
FACULTAD DE CIENCIAS ECONÓMICAS, ADMINISTRATIVAS Y CONTABLES
DEPARTAMENTO DE INFORMÁTICA
DIA 044 Programación Básica
Proyecto: CAJERO AUTOMÁTICO
Grupo N°5
*/

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<cstdlib>

using namespace std;

// Funciones 
void mostrarMenu();
void abrirCuenta(bool &cuentaAbierta, string &nombreCliente, 
string &generoCliente, int &edadCliente, double &saldoInicial, vector<string> &beneficiarios);
void pausa();
void limpiarPantalla();
// Variables globales
int main() {
    bool cuentaAbierta = false;
    string nombreCliente;
    string generoCliente;
    int edadCliente = 0;
    double saldoInicial = 0.0;
    int opcion;

    // Vector para guardar los 3 beneficiarios
    vector<string> beneficiarios(3);

    // EDITAR OPCIONES DEL MENU PRINCIPAL (LA QUE SE ASIGNO A CADA QUIEN)
    // solo esta validado para cuenta creada, las demas opciones no estan programadas

    do {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
            if (cuentaAbierta) {
                    cout << "\nOpcion 1: Acreditar\n";
                    // Lógica para acreditar dinero
                } else {
                    cout << "\nDebe aperturar una cuenta primero.\n";
                    pausa();
                }
                break;
            case 2:
                if (cuentaAbierta) {
                    cout << "\nOpcion 2: Debitar\n";
                    // Lógica para debitar dinero
                } else {
                    cout << "\nDebe aperturar una cuenta primero.\n";
                    pausa();
                }
                break;
            case 3:
                if (cuentaAbierta) {
                    cout << "\nOpcion 3: Ver saldo\n";
                    // Lógica para ver saldo
                } else {
                    cout << "\nDebe aperturar una cuenta primero.\n";
                    pausa();
                }
                break;
            case 4:
                if (cuentaAbierta) {
                    cout << "\nOpcion 4: Transferencias de criptomonedas\n";
                    // Lógica para transferencias de criptomonedas
                } else {
                    cout << "\nDebe aperturar una cuenta primero.\n";
                    pausa();
                }
                break;
            case 5:
                if (cuentaAbierta) {
                    cout << "\nLa cuenta ya fue aperturada.\n";
                    pausa();
                } else {
                    abrirCuenta(cuentaAbierta, nombreCliente, generoCliente, edadCliente, saldoInicial, beneficiarios);
                }
                break;

            case 6:
                cout << "\nGracias por su preferencia.\n";
                break;

            default:
                cout << "\nPor ahora solo esta programada la opcion 5 (Apertura de cuenta).\n";
                pausa();
        }

    } while(opcion != 6);

    return 0;
}

// ===== MENU PRINCIPAL =====
void mostrarMenu() {
    limpiarPantalla();
    cout << "=============================================\n";
    cout << "======== | BIENVENIDO A PUMA-BANK | =========\n";
    cout << "=============================================\n";
    cout << "         CAJERO AUTOMATICO PUMA-BANK         \n";
    cout << "=============================================\n";
    cout << "1. Acreditar\n";
    cout << "2. Debitar\n";
    cout << "3. Ver saldo\n";
    cout << "4. Transferencias de criptomonedas\n";
    cout << "5. Apertura de cuenta\n";
    cout << "6. Salir\n";
    cout << "=============================================\n";
}

// ===== APERTURA DE CUENTA + REGISTRO DE BENEFICIARIOS =====
void abrirCuenta(bool &cuentaAbierta, string &nombreCliente, 
string &generoCliente, int &edadCliente, double &saldoInicial, vector<string> &beneficiarios) 
{

    limpiarPantalla();
    cout << "========= BIENVENIDO A PUMA-BANK =========\n";
    cout << "========== APERTURA DE CUENTA ==========\n";

    // Solicitar nombre del cliente
    cin.ignore(); // Limpiar el buffer de entrada
    cout << "Ingrese su nombre: ";
    getline(cin, nombreCliente);

    // validación de genero del cliente
    do {
        cout << "Ingrese su genero (M/F): ";
        getline(cin, generoCliente);
    } while (generoCliente != "M" && generoCliente != "F");

    // validación de edad del cliente
    do {
        cout << "Ingrese su edad: ";
        cin >> edadCliente;
        if (edadCliente < 18 || edadCliente > 100) {
            cout << "Edad no valida. Debe estar entre 18 y 100 años.\n";
        }
    } while (edadCliente < 18 || edadCliente > 100);

    // Saldo inicial de apertura
    saldoInicial = 200.00;
    cuentaAbierta = true;

    cout << "\nCuenta aperturada con exito.\n";
    cout << "Saldo inicial: L. " << fixed << setprecision(2) << saldoInicial << "\n";

    // Registro de beneficiarios
    cin.ignore();
    cout << "\nIngrese los 3 beneficiarios (Nombre del Beneficiario):\n"; // Se solicita el nombre de los beneficiarios
    for (int i = 0; i < 3; i++) { // i es el índice del vector beneficiarios
        cout << "Beneficiario " << (i + 1) << ": ";
        getline(cin, beneficiarios[i]); // Se guarda el nombre del beneficiario en el vector
    }

    cout << "\nBeneficiarios registrados correctamente.\n";

    // Mostrar resumen
    cout << "\n========== RESUMEN DE LA CUENTA ==========\n";
    cout << "Nombre: " << nombreCliente << "\n";
    cout << "Genero: " << generoCliente << "\n";
    cout << "Edad: " << edadCliente << "\n";
    cout << "Saldo inicial: L. " << saldoInicial << "\n";

    cout << "\nBeneficiarios registrados:\n";
    for (int i = 0; i < 3; i++) { // Se recorre el vector beneficiarios para mostrar los nombres
        cout << (i + 1) << ". " << beneficiarios[i] << "\n";
    }

    pausa(); // Se llama a la función pausa para que el usuario pueda leer el resumen antes de volver al menú principal
}

// ===== FUNCION PARA PAUSAR =====
void pausa() { // Función para pausar la ejecución del programa y esperar a que el usuario presione ENTER
    cout << "\nPresione ENTER para volver al Menu Principal de | PUMA-BANK |";
    cin.ignore();
    cin.get(); // el cin.get() es un método para pausar la ejecución del programa hasta que el usuario presione la tecla ENTER. 
    // Esto permite al usuario leer los mensajes en pantalla antes de continuar con el programa.
}

// ===== FUNCION PARA LIMPIAR PANTALLA =====
void limpiarPantalla() {
    system("cls"); // Si usas otro compilador diferente a Windows, puede ser system("clear");
}
