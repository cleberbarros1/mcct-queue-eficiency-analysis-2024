#include <iostream>
#include <vector>
#include "Cliente.h"
#include "Fila.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <direct.h>
///#include <filesystem> para LINUX

using namespace std;

int main() {
    printf("\n ------------------- MESTRADO EM MODELAGEM COMPUTACIONAL - 2024.1 --------------------\n");
    printf("\n --> Mestrando: CLEBER BARROS \n");
    printf("\n --> Software de simulação para atendimento em uma fila --- \n");
    printf("\n --> Professor: Tiago Araujo Neves \n");
    printf("\n --> DESAFIO: Avaliar eficience de tempo médio de atendimento de uma fila. \n\n");
    printf("\n ------------------- INICIANDO AVALIACAO --------------------\n\n");

    mkdir("relatorios-de-testes");
    //create_directory("relatorios-de-testes");  para LINUX

    int periodo = 720;
    int n = 10; // Numero de Iteracoes
    int a = 1; // Limite inferior de calculo do valores aleatórios
    int b = 3; // Limite superior Intervalo de chegada Aleatorio
    int c = 4; // Limite superior Intervalo Aleatorio de Duração
    int tempoAleatorioChegada;

    ofstream relatorio;
    relatorio.open("relatorios-de-testes/minutos-tamanhoFila.txt", std::ios::out | std::ios::app);
    relatorio << 0;
    relatorio << " ";
    relatorio << 0 << std::endl;
    relatorio.close();

    relatorio.open("relatorios-de-testes/minutos-tempoEspera.txt", std::ios::out | std::ios::app);
    relatorio << 0;
    relatorio << " ";
    relatorio << 0 << std::endl;
    relatorio.close();

    FILE* pipe = popen("gnuplot -persist", "w");
    if (!pipe) {
        printf("Error ao carregar o gráfico!\n");
    }

    vector<int> listaDeQtd;
    vector<int> listaMaiorEspera;

    for(int i = 1; i <= n; i++) {

        cout << " --------------------------- ITERACAO NUMERO " << i <<" -------------------------- \n\n";

            int max_waitTime = 0;
            int max_size = 0;
            int tempoAtual = 0;

            Fila novaFila;
            tempoAleatorioChegada = rand() % b + a;

            Cliente primeiroCliente(tempoAleatorioChegada);

            int duracao = rand() % c + a;

            primeiroCliente.foiAtendido(tempoAleatorioChegada + duracao);

            novaFila.inserirCliente(primeiroCliente);
            cout << "Um cliente novo chegou na fila no minuto: " << primeiroCliente.horaDeChegadaNaFila << "\n";

            tempoAtual = tempoAleatorioChegada;

            while(tempoAtual <= periodo) {
            
                if(tempoAtual == novaFila.FilaClientes[0].quandoFoiAtendido) {
                    cout << "O atendimento atual finalizou no minuto: " << tempoAtual << "\n";
                    cout << "Demorou: " << duracao << " minutos para finalizar o atendimento.\n";
                    cout << "Tempo de espera deste cliente foi de " << tempoAtual - novaFila.FilaClientes[0].       horaDeChegadaNaFila  << " minutos.\n\n";

                    if(tempoAtual - novaFila.FilaClientes[0].horaDeChegadaNaFila > max_waitTime) { 
                        max_waitTime = tempoAtual - novaFila.FilaClientes[0].horaDeChegadaNaFila; 
                        }

                    relatorio.open("relatorios-de-testes/minutos-tempoEspera.txt", std::ios::out | std::ios::app);
                    relatorio << tempoAtual;
                    relatorio << " ";
                    relatorio << tempoAtual - novaFila.FilaClientes[0].horaDeChegadaNaFila << std::endl;
                    relatorio.close();

                    novaFila.atenderProximo();

                    if(novaFila.filaVazia() == true) {
                        tempoAleatorioChegada = rand() % b + a;
                        Cliente novoCliente(tempoAtual + tempoAleatorioChegada);

                        novaFila.inserirCliente(novoCliente);
                        cout << "Um cliente novo chegou na fila no minuto: " << tempoAtual + tempoAleatorioChegada <<   "\n";
                        cout << "Quantidade atual de clientes na Fila: " << novaFila.qtdClientes << "\n\n";
                        novaFila.FilaClientes[0].quandoFoiAtendido = tempoAtual + tempoAleatorioChegada;

                        if(novaFila.qtdClientes > max_size) { 
                            max_size = novaFila.qtdClientes; 
                            }

                        relatorio.open("relatorios-de-testes/minutos-tamanhoFila.txt", std::ios::out | std::ios::app);
                        relatorio << tempoAtual;
                        relatorio << " ";
                        relatorio << novaFila.qtdClientes << std::endl;
                        relatorio.close();
                        continue;
                    }

                    cout << "Atendendo agora o proximo da fila --> \n\n ";
                    duracao = rand() % c + a;
                    novaFila.FilaClientes[0].quandoFoiAtendido = tempoAtual + duracao;

                }


                tempoAleatorioChegada = rand() % b + a;

                if(tempoAtual + tempoAleatorioChegada > novaFila.FilaClientes[novaFila.FilaClientes.size()-1].      horaDeChegadaNaFila) {
                
                    Cliente novoCliente(tempoAtual + tempoAleatorioChegada);

                    novaFila.inserirCliente(novoCliente);
                    cout << "Um cliente novo chegou na fila no minuto: " << tempoAtual + tempoAleatorioChegada << "\n";
                    cout << "Quantidade atual de clientes na Fila: " << novaFila.qtdClientes << "\n\n";

                    if(novaFila.qtdClientes > max_size) { 
                        max_size = novaFila.qtdClientes; 
                        }

                    relatorio.open("relatorios-de-testes/minutos-tamanhoFila.txt", std::ios::out | std::ios::app);
                    relatorio << tempoAtual;
                    relatorio << " ";
                    relatorio << novaFila.qtdClientes << std::endl;
                    relatorio.close();
                }

                tempoAtual++;    

            }

            listaDeQtd.push_back(max_size);
            listaMaiorEspera.push_back(max_waitTime);

            cout << "Quantidade Final de clientes restantes na Fila: " << novaFila.qtdClientes << "\n\n";

    }

    cout << " ----------------- RESULTADO FINAL - MEDIAS --------------------- \n\n";

    int somaSize = 0;
    for(int i = 0; i < listaDeQtd.size(); i++) {
        somaSize += listaDeQtd[i];
    }

    int somaEspera = 0;
    for(int i = 0; i < listaMaiorEspera.size(); i++) {
        somaEspera += listaMaiorEspera[i];
    }

    int medSize = somaSize/listaDeQtd.size();
    int medEspera = somaEspera/listaMaiorEspera.size();

    cout << "Vetor de maiores filas --> [";
    for(int i = 0; i < listaDeQtd.size(); i++) {
        cout << listaDeQtd[i] << " ";
    }
    cout << "] \nMedia Fila = " << medSize << endl;

    cout << "Vetor de maiores esperas --> [";
    for(int i = 0; i < listaMaiorEspera.size(); i++) {
        cout << listaMaiorEspera[i] << " ";
    }
    cout << "] \nMedia Espera = " << medEspera << endl;


    fprintf(pipe, "plot 'relatorios-de-testes/minutos-tempoEspera.txt' title 'Espera em Minutos' with lines lw 3, 'relatorios-de-testes/minutos-tamanhoFila.txt' title 'Tamanho da Fila' with lines lw 3; \n"); // Plot data

    fprintf(pipe, "i = 1 \n");
    fprintf(pipe, "set ylabel 'Quantidade Pessoas - Minutos' \n"); 
    fprintf(pipe, "set xlabel 'Instante da medicao [min]' \n");
    fprintf(pipe, "set size 0.9, 0.9 \n");
    fprintf(pipe, "set key left top \n");
    fprintf(pipe, "set border 3 \n");
    fprintf(pipe, "set title 'Desempenho de Atendimento em filas - 10 execucoes' \n");
    fflush(pipe);

    string any;
    cin >> any;
}
    