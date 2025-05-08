#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

// Declaración de funciones de ordenamiento
void bubbleSort(vector<int>& arr);
void insertionSort(vector<int>& arr);
void merge(vector<int>& arr, int left, int mid, int right);
void mergeSort(vector<int>& arr, int left, int right);
int partition(vector<int>& arr, int low, int high);
void quickSort(vector<int>& arr, int low, int high);

// Implementación de Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Implementación de Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;

        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Implementación de Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin()+left, arr.begin()+mid+1);
    vector<int> rightArr(arr.begin()+mid+1, arr.begin()+right+1);

    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i++];
        } else {
            arr[k] = rightArr[j++];
        }
        k++;
    }

    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right-left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

// Implementación de Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low-1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

// Función para generar arrays según el tipo
vector<int> generateArray(int size, int type) {
    vector<int> arr(size);

    switch(type) {
        case 0: // Aleatorio
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 10000;
            }
            break;

        case 1: // Ordenado
            for (int i = 0; i < size; i++) {
                arr[i] = i+1;
            }
            break;

        case 2: // Inverso
            for (int i = 0; i < size; i++) {
                arr[i] = size-i;
            }
            break;

        default:
            cout << "Tipo no válido. Usando array aleatorio." << endl;
            for (int i = 0; i < size; i++) {
                arr[i] = rand() % 10000;
            }
    }
    return arr;
}

// Función para medir tiempos
void measureTime(void (*sortFunc)(vector<int>&), vector<int> arr, string sortName) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop-start);
    cout << sortName << ": " << duration.count() << " microsegundos" << endl;
}

int main() {
    srand(time(0));

    // Menú de selección
    cout << "SELECCIONE EL TIPO DE ARRAY:" << endl;
    cout << "0 - Aleatorio" << endl;
    cout << "1 - Ordenado" << endl;
    cout << "2 - Inverso" << endl;
    cout << "Ingrese opcion (0-2): ";

    int choice;
    cin >> choice;

    // Validar entrada
    while (choice < 0 || choice > 2) {
        cout << "Opcion no valida. Ingrese 0-2: ";
        cin >> choice;
    }

    const int SIZE = 1000;
    vector<int> baseArray = generateArray(SIZE, choice);

    // Crear copias para cada algoritmo
    vector<int> arr1 = baseArray;
    vector<int> arr2 = baseArray;
    vector<int> arr3 = baseArray;
    vector<int> arr4 = baseArray;

    cout << "\nRESULTADOS CON ";
    switch(choice) {
        case 0: cout << "ARRAY ALEATORIO"; break;
        case 1: cout << "ARRAY ORDENADO"; break;
        case 2: cout << "ARRAY INVERSO"; break;
    }
    cout << " (Tamaño: " << SIZE << " elementos):\n" << endl;

    // Medir y mostrar tiempos
    measureTime(bubbleSort, arr1, "Bubble Sort");
    measureTime(insertionSort, arr2, "Insertion Sort");
    measureTime([](vector<int>& a){ mergeSort(a, 0, a.size()-1); }, arr3, "Merge Sort");
    measureTime([](vector<int>& a){ quickSort(a, 0, a.size()-1); }, arr4, "Quick Sort");

    return 0;
}
