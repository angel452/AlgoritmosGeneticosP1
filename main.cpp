#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

std::random_device rd;
std::mt19937 gen(rd());

// ######################## FUNCIONES #########################
int random(int low, int high) {
  std::uniform_int_distribution<> dist(low, high);
  return dist(gen);
}

// ####################### CLASES ##############################
class Genetic_algorithm {
  public:
    // --> Variables...
    vector<int> poblacion;
    vector<int> poblacionMaximizada;
    vector<double> pSelect;
    vector<double> valorEsperado;
    vector<int> valorActual;
    double media = 0, suma = 0, maximo = 0;
    double mediaPS = 0, sumaPS = 0, maximoPS = 0;
    double mediaVE = 0, sumaVE = 0, maximoVE = 0;
    double mediaVA = 0, sumaVA = 0, maximoVA = 0;
    int epocas;

    // ------------------- CONSTRUCTOR ---------------------------
    Genetic_algorithm(int NPoblaciones, int min, int max, int epocasInput) {

      for (int i = 0; i < NPoblaciones; i++) {
        poblacion.push_back(random(min, max));
      }
      
      /*
      poblacion.push_back(13);
      poblacion.push_back(24);
      poblacion.push_back(8);
      poblacion.push_back(19);
      */
      epocas = epocasInput;
    }

    // -------------------- FUNCIONES ------------------------------
    // --> Funciones adicionales
    // * Funcion que convierte un vector de enteros a binario
    vector<string> convertirABinario(const vector<int> &numeros) {
      vector<string> binarios;

      // Encontrar la longitud máxima de binario en el vector
      int maxLongitud = 0;
      for (int numero : numeros) {
        string binario = "";

        if (numero == 0) {
          binario = "0";
        } else {
          while (numero > 0) {
            int bit = numero % 2;
            binario = to_string(bit) + binario;
            numero /= 2;
          }
        }

        binarios.push_back(binario);

        if (binario.length() > maxLongitud) {
          maxLongitud = binario.length();
        }
      }

      // Rellenar con ceros a la izquierda para igualar la longitud
      for (string &binario : binarios) {
        int diferencia = maxLongitud - binario.length();
        if (diferencia > 0) {
          string ceros(diferencia, '0');
          binario = ceros + binario;
        }
      }

      return binarios;
    }

    // * Funcion para limpiar las variables
    void limpiar_variables() {
      poblacionMaximizada.clear();
      pSelect.clear();
      valorEsperado.clear();
      valorActual.clear();
      media = 0;
      suma = 0;
      maximo = 0;
      mediaPS = 0;
      sumaPS = 0;
      maximoPS = 0;
      mediaVE = 0;
      sumaVE = 0;
      maximoVE = 0;
      mediaVA = 0;
      sumaVA = 0;
      maximoVA = 0;

      /*
      cout << "--------- Variables limpiadas -------------" << endl;
      cout << "Poblacion: "; printPoblacion();
      cout << "Poblacion maximizada: "; printPoblacionMaximizada();
      cout << "Pselect: "; printPSelect();
      cout << "Valor esperado: "; printValorEsperado();
      cout << "Valor actual: "; printValorActual();
      cout << "Media: " << media << endl;
      cout << "Suma: " << suma << endl;
      cout << "Maximo: " << maximo << endl;
      cout << "MediaPS: " << mediaPS << endl;
      cout << "SumaPS: " << sumaPS << endl;
      cout << "MaximoPS: " << maximoPS << endl;
      cout << "MediaVE: " << mediaVE << endl;
      cout << "SumaVE: " << sumaVE << endl;
      cout << "MaximoVE: " << maximoVE << endl;
      cout << "MediaVA: " << mediaVA << endl;
      cout << "SumaVA: " << sumaVA << endl;
      cout << "MaximoVA: " << maximoVA << endl;
      cout << "------------------------------------------" << endl;
      */
    }

    // * Funcion para convertir de binario a entero
    int binarioAEntero(const std::string &binario) {
      int entero = 0;
      int longitud = binario.length();

      for (int i = 0; i < longitud; ++i) {
        if (binario[i] == '1') {
          entero += static_cast<int>(std::pow(2, longitud - 1 - i));
        }
      }

      return entero;
    }

    // * Funcion para evaluar
    int funcion(int x) { 
      return x * x; 
    };

    // --> Funciones principales
    // * Poblacion maximizada
    void maximizar() {
      limpiar_variables();
      cout << "----------------------" << endl;
      cout << "Poblacion: "; printPoblacion();
      cout << "-----------------------" << endl;

      // - Evaluacion de la funcion y suma total
      for (int i = 0; i < poblacion.size(); i++) {
        poblacionMaximizada.push_back(funcion(poblacion[i]));
        suma += poblacionMaximizada[i];
      }

      // - Media de las poblaciones
      media = suma / poblacion.size();

      // - Maximo de numero de las poblaciones
      vector<int>::iterator max_Num = max_element(poblacionMaximizada.begin(), poblacionMaximizada.end());
      maximo = *max_Num;

      cout << "Resultados funcion: " << endl;
      printPoblacionMaximizada();
      printResultados(suma, media, maximo);
    }

    // * Construccion de la tabla
    void modelar(int num_epoca) {
      cout <<  endl << "Epoca " << num_epoca << endl;
      // ------------------ FUNCION ------------------------
      maximizar();

      // ---------------- PSELECI ----------------------------
      // * Calculo del Pseleci [Funcion / Suma] y tambien de la suma total

      for (int i = 0; i < poblacion.size(); i++) {
        pSelect.push_back(poblacionMaximizada[i] / (suma * 1.0));
        sumaPS += pSelect[i];
      }

      // * Media del Pseleci
      mediaPS = sumaPS / poblacion.size();

      // * Maximo del Pseleci
      vector<double>::iterator max_pselect = max_element(pSelect.begin(), pSelect.end());
      maximoPS = *max_pselect;

      cout << "Resultados Peleci" << endl;
      printPSelect();
      printResultados(sumaPS, mediaPS, maximoPS);

      // ------------------ VALOR ESPERADO -----------------------
      // * Calculo del valor esperado [Peseleci / Media] y tambien de la suma
      for (int i = 0; i < poblacion.size(); i++) {
        valorEsperado.push_back(pSelect[i] / (mediaPS * 1.0));
        sumaVE += valorEsperado[i];
      }

      // * Media del Pseleci
      mediaVE = sumaVE / poblacion.size();

      // * Maximo del Pseleci
      vector<double>::iterator max_valorEsperado = max_element(valorEsperado.begin(), valorEsperado.end());
      maximoVE = *max_valorEsperado;

      cout << "Resultados valor esperado" << endl;
      printValorEsperado();
      printResultados(sumaVE, mediaVE, maximoVE);

      // --------------------- VALOR ACTUAL --------------------------
      // * Calculo del valor actual [round(valorActual)] y tambien de la suma 
      sumaVA = 0;
      for (int i = 0; i < poblacion.size(); i++) {
        valorActual.push_back(rint(valorEsperado[i]));
        sumaVA += valorActual[i];
      }

      mediaVA = sumaVA / valorActual.size();

      vector<int>::iterator max_va = max_element(valorActual.begin(), valorActual.end());
      maximoVA = *max_va;

      cout << "Resultados Valor actual: " << endl;
      printValorActual();
      printResultados(sumaVA, mediaVA, maximoVA);
    }

    void intercambiar(std::string &a, std::string &b, int &intA, int &intB) {

      // generar posicion aleatoria para el intercambio

      int posicion = random(1, a.size()-1);

      cout << "Intercambiando " << a << " y " << b << " en la posicion " << posicion << endl;

      for (int i = posicion; i < a.size(); i++) {
        // Intercambiar los bits en la posición especificada
        char bitA = a[i];
        char bitB = b[i];
        a[i] = bitB;
        b[i] = bitA;
      }

      cout << "* RES: " << a << " y " << b << endl;

      intA = binarioAEntero(a);
      intB = binarioAEntero(b);
    }

    void cruzar() {

      cout << "--> Cruzamiento" << endl;

      // * Ordenamos la poblacion de mayor a menor
      sort(poblacion.rbegin(), poblacion.rend());
      cout << "Poblacion ordenada: "; printPoblacion();

      // * Eliminamos los n elementos menos aptos 
      // OJO: 4 elementos - elimino 1 elemento
      // OJO: 5 elementos - elimino 2 elementos
      // OJO: 6 elementos - elimino 2 elementos
      // OJO: etc...
      // - Formula: nEliminados = nPoblacion - [(nPoblacion/2) + 1])]

      int nEliminados = poblacion.size() - ((poblacion.size() / 2) + 1);
      cout << "Con poblacion " << poblacion.size() << ", se eliminan " << nEliminados << " elementos" << endl;
      for(int i = 0; i < nEliminados; i++){
        vector<int>::iterator menosApto = min_element(poblacion.begin(), poblacion.end());
        poblacion.erase(menosApto);
      }

      cout << "Nueva poblacion (Antes del cruze): "; printPoblacion();

      int numCruzes = poblacion.size()-1;
      
      vector<int> poblacion_before_cross;
      // * Tengo: poblacion {24 19 13}. Tengo que transformarlo a {24 19 24 13}
      for(int i = 1; i <= numCruzes; i++){
        poblacion_before_cross.push_back(poblacion[0]);
        poblacion_before_cross.push_back(poblacion[i]);
      }

      cout << "Poblacion AUX: ";
      for(int i = 0; i < poblacion_before_cross.size(); i++){
        cout << poblacion_before_cross[i] << " ";
      }
      cout << endl;

      vector<string> listInBinary = convertirABinario(poblacion_before_cross);
      cout << "Poblacion en binario: ";  
      for(int i = 0; i < listInBinary.size(); i++){
        cout << listInBinary[i] << " ";
      }
      cout << endl;
      
      vector<int> poblacion_cruzada;
      for(int i = 0; i < poblacion_before_cross.size(); i = i + 2){
        int a, b;
        // * Intercambiamos el mas apto (primera posicion) con el resto
        intercambiar(listInBinary[i], listInBinary[i+1], a, b);
        poblacion_cruzada.push_back(a);
        poblacion_cruzada.push_back(b);
      }
      
      //sort(poblacion_cruzada.rbegin(), poblacion_cruzada.rend());

      poblacion.clear();
      for (int i = 0; i < poblacion_cruzada.size(); i++) {
        poblacion.push_back(poblacion_cruzada[i]);
      }

      cout << "Nueva poblacion (Despues del cruze): "; printPoblacion();
    }

    void ejecucion() {
      for (int i = 0; i < epocas - 1; i++) {
        modelar(i + 1);
        cruzar();
      }
      cout << endl << "Ultima Epoca: " << epocas << endl;
      maximizar();
      cout << "######## FIN DE LAS EPOCAS ########" << endl;
    }

    // * FUNCIONES DE IMPRESION
    void printResultados(double suma, double media, double maximo) {
      cout << "* Suma: " << std::fixed << std::setprecision(3) << suma << endl;
      cout << "* Media: " << std::fixed << std::setprecision(3) << media << endl;
      cout << "* Maximo: " << std::fixed << std::setprecision(3) << maximo
          << endl;
      cout << endl;
    }

    void printPoblacion() {
      for (int i = 0; i < poblacion.size(); i++) {
        cout << poblacion[i] << " ";
      }
      cout << endl;
    }

    void printPoblacionMaximizada() {
      for (int i = 0; i < poblacionMaximizada.size(); i++) {
        cout << poblacionMaximizada[i] << " ";
      }
      cout << endl;
    }

    void printPSelect() {
      for (int i = 0; i < pSelect.size(); i++) {
        cout << pSelect[i] << " ";
      }
      cout << endl;
    }

    void printValorEsperado() {
      for (int i = 0; i < valorEsperado.size(); i++) {
        cout << valorEsperado[i] << " ";
      }
      cout << endl;
    }

    void printValorActual() {
      for (int i = 0; i < valorActual.size(); i++) {
        cout << valorActual[i] << " ";
      }
      cout << endl;
    }
};

// ######################## MAIN ###############################
int main() {
  // --> test1(numero de poblaciones, minimo, maximo, numero de Epocas)
  Genetic_algorithm test1(100, 0, 31, 14);
  cout << "Poblacion: -->  ";
  test1.printPoblacion();
  cout << endl;
  test1.ejecucion();

  return 0;
}