

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <limits>
using namespace std;

class EmpleadoRFC {
private:
    string nombre;
    string apellidoPaterno;
    string apellidoMaterno;
    int dia, mes, anio;

public:
    
void capturarDatos() {
    cout << "========== CALCULO DE RFC ==========" << endl;

    do {
    cout << "Introduce tu nombre:" << endl;
    std::getline(cin, nombre);

    if (nombre.empty()) {
        cout << "Error: El nombre es obligatorio." << endl;
    }

} while (nombre.empty());

    // Apellido paterno obligatorio
    do {
        cout << "Introduce tu apellido paterno (obligatorio):" << endl;
        std::getline(cin, apellidoPaterno);

        if (apellidoPaterno.empty()) {
            cout << "Error: El apellido paterno es obligatorio." << endl;
        }

    } while (apellidoPaterno.empty());

    // Apellido materno opcional
    cout << "Introduce tu apellido materno (si no tienes, presiona ENTER):" << endl;
    std::getline(cin, apellidoMaterno);

    // Validacion de fecha
    bool fechaValida = false;

    do {
        cout << "Introduce dia, mes y anio de nacimiento:" << endl;

        if (!(cin >> dia >> mes >> anio)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Error: Debes introducir valores numericos." << endl;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        fechaValida = (anio >= 1000 && anio <= 9999 &&
                       mes >= 1 && mes <= 12);

        if (fechaValida) {
            int diasMes[] = {
                0, 31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31
            };

            bool bisiesto = (anio % 400 == 0) ||
                            (anio % 4 == 0 && anio % 100 != 0);

            if (mes == 2 && bisiesto) {
                diasMes[2] = 29;
            }

            fechaValida = (dia >= 1 && dia <= diasMes[mes]);
        }

        if (!fechaValida) {
            cout << "Error: La fecha ingresada no es valida." << endl;
            cout << "Intenta nuevamente." << endl;
        }

    } while (!fechaValida);
}
 // Cierre de capturarDatos()


    string generarRFC() {
        string rfc = "";

        // Convertir los apellidos y el nombre a mayusculas
        for (char &c : apellidoPaterno)
            c = toupper(c);

        for (char &c : apellidoMaterno)
            c = toupper(c);

        for (char &c : nombre)
            c = toupper(c);

        // Primera letra del apellido paterno
        rfc += apellidoPaterno[0];

        // Primera vocal interna del apellido paterno
        bool encontrada = false;

        for (int i = 1; i < apellidoPaterno.length(); i++) {
            char letra = apellidoPaterno[i];

            if (letra == 'A' || letra == 'E' ||
                letra == 'I' || letra == 'O' ||
                letra == 'U') {
                rfc += letra;
                encontrada = true;
                break;
            }
        }

        // Si no existe vocal interna, se utiliza X
        if (!encontrada) {
            rfc += 'X';
        }

        // Inicial del apellido materno
        if (apellidoMaterno.empty()) {
            rfc += 'X';
        } else {
            rfc += apellidoMaterno[0];
        }

        // Inicial del nombre
        rfc += nombre[0];

        // Ultimos dos digitos del anio
        int anioCorto = anio % 100;

if (anioCorto < 10) {
    rfc += '0';
}

rfc += to_string(anioCorto);

        // Mes y dia con dos digitos
        stringstream fecha;
        fecha << setfill('0') << setw(2) << mes
              << setw(2) << dia;

        rfc += fecha.str();

        return rfc;
    }
};

int main() {
    EmpleadoRFC empleado;

    empleado.capturarDatos();

    cout << endl;
    cout << "Tu RFC sin homoclave es: "
         << empleado.generarRFC() << endl;

    return 0;
}

