# AlgoritmosOrdenamiento

# 📊 Benchmark de Algoritmos de Ordenamiento: C++ vs Python

## 🔍 Resumen
Comparativa de rendimiento entre implementaciones en C++ y Python de 4 algoritmos clásicos con arreglos de 1000 elementos.

## 🚀 Resultados Destacados
| Algoritmo       | Escenario   | C++ (µs) | Python (µs) | Diferencia |
|-----------------|-------------|----------|-------------|------------|
| **Bubble Sort** | Aleatorio   | 2,000-5,000 | 10,000-50,000 | 5-10x |
|                | Ordenado    | 10-100   | 100-500     | 5x        |
|                | Inverso     | 4,000-10,000 | 20,000-100,000 | 10x |
| **Insertion Sort** | Aleatorio | 500-2,000 | 5,000-20,000 | 10x |
|                | Ordenado    | 10-100   | 100-500     | 5x        |
|                | Inverso     | 2,000-5,000 | 10,000-50,000 | 10x |
| **Merge Sort**  | Todos       | 100-500  | 1,000-5,000 | 10x       |
| **Quick Sort**  | Aleatorio   | 50-200   | 500-2,000   | 10x       |
|                | Ordenado/Inverso | 500-2,000 | 5,000-20,000 | 10x |

. C++ vs Python

- C++ es 5-10x más rápido en todos los casos

- Python muestra mayor overhead en operaciones básicas

. Patrones de Rendimiento

- Órdenes O(n²): Sensibles al tamaño de entrada

- Órdenes O(n log n): Escalables para grandes volúmenes

. Casos ideales

- Bubble/Insertion Sort: Pequeños datasets o datos casi ordenados

- Merge/Quick Sort: Datos grandes y aleatorios
