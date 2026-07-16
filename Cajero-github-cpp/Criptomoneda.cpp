
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
 
// 11) Transferencia de criptomonedas
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

