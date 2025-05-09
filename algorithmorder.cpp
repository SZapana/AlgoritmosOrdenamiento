#include <iostream>
#include <vector>
#include <chrono>   // Para medir tiempos
#include <algorithm> // Para funciones como swap() y sort()
#include <random>    // Para generación de números aleatorios

using namespace std;
using namespace std::chrono;

/* DECLARACIONES DE FUNCIONES*/
void bubbleSort(vector<int>& arr);
void insertionSort(vector<int>& arr);
void merge(vector<int>& arr, int left, int mid, int right);
void mergeSort(vector<int>& arr, int left, int right);
int partition(vector<int>& arr, int low, int high);
void quickSort(vector<int>& arr, int low, int high);

/*IMPLEMENTACIÓN DE ALGORITMOS*/

// Algoritmo Bubble Sort (Ordenamiento de Burbuja)
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    // Primer bucle: pasa por todo el array
    for (int i = 0; i < n-1; i++) {
        // Segundo bucle: compara elementos adyacentes
        for (int j = 0; j < n-i-1; j++) {
            // Si el elemento actual es mayor que el siguiente
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]); // Intercambia los elementos
            }
        }
    }
}

// Algoritmo Insertion Sort (Ordenamiento por Inserción)
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    // Comienza desde el segundo elemento
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Elemento a insertar
        int j = i-1;

        // Mueve los elementos mayores que key hacia la derecha
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        // Inserta key en su posición correcta
        arr[j+1] = key;
    }
}

// Función Merge para Merge Sort (Combina dos subarrays ordenados)
void merge(vector<int>& arr, int left, int mid, int right) {
    // Crea subarrays temporales
    vector<int> leftArr(arr.begin()+left, arr.begin()+mid+1);
    vector<int> rightArr(arr.begin()+mid+1, arr.begin()+right+1);

    int i = 0, j = 0, k = left; // Índices para leftArr, rightArr y arr

    // Combina los subarrays ordenados
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // Copia los elementos restantes (si los hay)
    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

// Algoritmo Merge Sort (Ordenamiento por Mezcla)
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right-left)/2; // Punto medio

        // Ordena recursivamente ambas mitades
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        // Combina las mitades ordenadas
        merge(arr, left, mid, right);
    }
}

// Función Partition para Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Selecciona el último elemento como pivote
    int i = low - 1; // Índice del elemento más pequeño

    for (int j = low; j < high; j++) {
        // Si el elemento actual es menor que el pivote
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]); // Intercambia los elementos
        }
    }
    swap(arr[i+1], arr[high]); // Coloca el pivote en su posición correcta
    return i+1; // Retorna la posición del pivote
}

// Algoritmo Quick Sort (Ordenamiento Rápido)
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Obtiene la posición del pivote
        int pi = partition(arr, low, high);

        // Ordena recursivamente los subarrays
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

/* =====================================================
   FUNCIONES AUXILIARES
   ===================================================== */

// Genera un array según el tipo especificado
vector<int> generateArray(int size, int type) {
    vector<int> arr(size);

    switch(type) {
        case 0: // Array aleatorio
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 10000; // Números entre 0 y 9999
            }
            break;

        case 1: // Array ordenado
            for (int i = 0; i < size; i++) {
                arr[i] = i+1; // 1, 2, 3,..., size
            }
            break;

        case 2: // Array inverso
            for (int i = 0; i < size; i++) {
                arr[i] = size-i; // size, size-1,..., 1
            }
            break;

        default: // Por defecto, array aleatorio
            cout << "Tipo no válido. Usando array aleatorio." << endl;
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 10000;
            }
    }
    return arr;
}

// Mide el tiempo de ejecución de una función de ordenamiento
void measureTime(void (*sortFunc)(vector<int>&), vector<int> arr, string sortName) {
    auto start = high_resolution_clock::now(); // Marca de tiempo inicial
    sortFunc(arr); // Ejecuta la función de ordenamiento
    auto stop = high_resolution_clock::now(); // Marca de tiempo final

    // Calcula la duración en microsegundos
    auto duration = duration_cast<microseconds>(stop-start);
    cout << sortName << ": " << duration.count() << " microsegundos" << endl;
}

/*FUNCIÓN PRINCIPAL*/
int main() {
    srand(time(0)); // Inicializa la semilla para números aleatorios

    // Menú de selección
    cout << "SELECCIONE EL TIPO DE ARRAY" << endl;
    cout << " 0 - Aleatorio                " << endl;
    cout << " 1 - Ordenado               " << endl;
    cout << " 2 - Inverso                 " << endl;
    cout << "" << endl;
    cout << "> Ingrese su elección (0-2): ";

    int choice;
    cin >> choice;

    // Validación de entrada
    while (choice < 0 || choice > 2) {
        cout << "Entrada no válida. Por favor ingrese 0, 1 ó 2: ";
        cin >> choice;
    }

    const int SIZE = 1000; // Tamaño del array
    vector<int> baseArray = generateArray(SIZE, choice); // Genera el array base

    // Crea copias para cada algoritmo
    vector<int> arr1 = baseArray;
    vector<int> arr2 = baseArray;
    vector<int> arr3 = baseArray;
    vector<int> arr4 = baseArray;

    // Encabezado de resultados
    cout << "  RESULTADOS PARA ARRAY DE " << SIZE << " ELEMENTOS" << endl;

    // Mide y muestra los tiempos de ejecución
    measureTime(bubbleSort, arr1, "1. Bubble Sort ");
    measureTime(insertionSort, arr2, "2. Insertion Sort");
    measureTime([](vector<int>& a){ mergeSort(a, 0, a.size()-1); }, arr3, "3. Merge Sort   ");
    measureTime([](vector<int>& a){ quickSort(a, 0, a.size()-1); }, arr4, "4. Quick Sort   ");

    return 0;
}
