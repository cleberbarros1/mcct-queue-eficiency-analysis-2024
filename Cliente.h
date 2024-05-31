#include <iostream>

using namespace std;

class Cliente {
public:
    int horaDeChegadaNaFila;
    int quandoFoiAtendido;
    bool atendido = false;

public:
    Cliente(int chegada) {
        horaDeChegadaNaFila = chegada; // Análise de Complexidade --> O(1)
    }

    void foiAtendido(int horarioAtendido) {
        atendido = true; // Análise de Complexidade --> O(1)
        quandoFoiAtendido = horarioAtendido; // Análise de Complexidade --> O(1)
    }
};

