import time
import random
from typing import List, Callable


# Algoritmo Bubble Sort: compara elementos adyacentes e intercambia si están en orden incorrecto
def bubble_sort(arr: List[int]) -> None:
    n = len(arr)
    for i in range(n - 1):
        swapped = False
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:  # Intercambio si están en el orden incorrecto
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break  # Si no hubo intercambio, ya está ordenado


# Algoritmo Insertion Sort: inserta cada elemento en su posición correcta
def insertion_sort(arr: List[int]) -> None:
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:  # Desplaza elementos mayores hacia la derecha
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key  # Inserta el valor en su posición


# Algoritmo Merge Sort: divide y combina ordenadamente usando recursión
def merge_sort(arr: List[int]) -> None:
    def _merge(left: int, mid: int, right: int) -> None:
        temp = arr[left:right + 1]  # Copia temporal del subarray
        i, j, k = 0, mid - left + 1, left
        while i <= mid - left and j <= right - left:
            if temp[i] <= temp[j]:
                arr[k] = temp[i]
                i += 1
            else:
                arr[k] = temp[j]
                j += 1
            k += 1
        while i <= mid - left:
            arr[k] = temp[i]
            i += 1
            k += 1

    def _merge_sort(left: int, right: int) -> None:
        if left < right:
            mid = (left + right) // 2
            _merge_sort(left, mid)  # Ordena mitad izquierda
            _merge_sort(mid + 1, right)  # Ordena mitad derecha
            _merge(left, mid, right)  # Combina las mitades

    _merge_sort(0, len(arr) - 1)


# Algoritmo Quick Sort: divide el arreglo en torno a un pivote y ordena recursivamente
def quick_sort(arr: List[int]) -> None:
    def _partition(low: int, high: int) -> int:
        pivot = arr[(low + high) // 2]  # Pivote es el valor del medio
        i, j = low - 1, high + 1
        while True:
            i += 1
            while arr[i] < pivot:
                i += 1
            j -= 1
            while arr[j] > pivot:
                j -= 1
            if i >= j:
                return j  # Devuelve índice de partición
            arr[i], arr[j] = arr[j], arr[i]  # Intercambia fuera de lugar

    def _quick_sort(low: int, high: int) -> None:
        if low < high:
            pi = _partition(low, high)  # Particiona
            _quick_sort(low, pi)  # Ordena izquierda
            _quick_sort(pi + 1, high)  # Ordena derecha

    _quick_sort(0, len(arr) - 1)


# Genera un arreglo según tipo: aleatorio, ordenado o inverso
def generate_array(size: int, array_type: int) -> List[int]:
    if array_type == 0:
        return [random.randint(1, 10_000) for _ in range(size)]
    elif array_type == 1:
        return [i + 1 for i in range(size)]
    elif array_type == 2:
        return [size - i for i in range(size)]
    else:
        raise ValueError("Tipo de array no válido")


# Mide el tiempo que tarda un algoritmo en ordenar un arreglo (en microsegundos)
def measure_time(sort_func: Callable[[List[int]], None],
                 arr: List[int],
                 algorithm_name: str) -> float:
    arr_copy = arr.copy()  # Usa copia para no modificar el arreglo original
    start_time = time.perf_counter()  # Inicio
    sort_func(arr_copy)  # Ordena
    end_time = time.perf_counter()  # Fin
    elapsed = (end_time - start_time) * 1_000_000  # Tiempo en microsegundos
    print(f"{algorithm_name:<15}: {elapsed:>10.2f} µs")
    return elapsed


# Compara todos los algoritmos en un arreglo de 1000 elementos de distintos tipos
def compare_algorithms(array_size: int = 1000) -> None:
    print("COMPARACIÓN DE ALGORITMOS DE ORDENAMIENTO EN PYTHON")
    print(f"Array size: {array_size} elementos")

    print("Seleccione el tipo de array:")
    print("0 - Aleatorio")
    print("1 - Ordenado")
    print("2 - Inverso")

    while True:
        try:
            array_type = int(input("0-2): "))
            if 0 <= array_type <= 2:
                break
            print("¡Entrada inválida 0, 1 ó 2")
        except ValueError:
            print("¡Debe ingresar un número!")

    arr = generate_array(array_size, array_type)  # Genera el arreglo base

    algorithms = [
        (bubble_sort, "Bubble Sort"),
        (insertion_sort, "Insertion Sort"),
        (merge_sort, "Merge Sort"),
        (quick_sort, "Quick Sort")
    ]


    tipo = ["ALEATORIO", "ORDENADO", "INVERSO"][array_type]
    print(f"RESULTADOS PARA ARRAY {tipo}")


    results = []
    for algorithm, name in algorithms:
        time_taken = measure_time(algorithm, arr, name)
        results.append((name, time_taken))

    # Imprime comparación relativa
    fastest_time = min(t for _, t in results)
    print("\nCOMPARACIÓN RELATIVA (1.0 = más rápido):")
    for name, time_taken in results:
        ratio = time_taken / fastest_time
        print(f"{name:<15}: {ratio:>10.2f}x")


# Ejecuta la comparación en bucle para probar distintas entradas
if __name__ == "__main__":
    while True:
        compare_algorithms()
