#include "./include/timer.h"

double pegar_tempo() {
    return (double)clock() / CLOCKS_PER_SEC;
}

double calcular_diferenca_ms(double inicio, double fim) {
    return (fim - inicio) * 1000.0;
}