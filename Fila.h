#include <vector>
#include <iostream>

using namespace std;

class Fila {
public:
    vector<Cliente> FilaClientes;
    int qtdClientes = 0;

public:
    Fila(){};

    bool filaVazia() {
        if(qtdClientes == 0) { // Análise de Complexidade --> O(1)
            return true; // Análise de Complexidade --> O(1)
        } else {
            return false; // Análise de Complexidade --> O(1)
        }
    }

    void inserirCliente(Cliente novoCliente) {
        FilaClientes.push_back(novoCliente); // Análise de Complexidade --> O(1)
        qtdClientes++; // Análise de Complexidade --> O(1)
    }

    void atenderProximo(){
        if(qtdClientes == 1) { // Análise de Complexidade --> O(1)
            FilaClientes.pop_back(); // Análise de Complexidade --> O(1)
            qtdClientes--; // Análise de Complexidade --> O(1)
        } else {
            
        for(int i = 0; i < qtdClientes - 1; i++) { // Análise de Complexidade --> O(n)
            FilaClientes[i] = FilaClientes[i+1];
        }
        FilaClientes.pop_back(); // Análise de Complexidade --> O(1)
        qtdClientes--; // Análise de Complexidade --> O(1)
        }
    }

    Cliente consultarProximo(){
        if(filaVazia() == false) { // Análise de Complexidade --> O(1)
            return FilaClientes[0]; // Análise de Complexidade --> O(1)
        }

    }

    int tamanhoFila() {
        return qtdClientes; // Análise de Complexidade --> O(1)
    }

};