#include <iostream>
#include <vector>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
    Parque parque;
	Carro carro(&parque);
	Passageiro *passageiros[10];

    for (int i = 0; i < 10; i++) {
    	passageiros[i] = new Passageiro(i, &carro, &parque); //inicia construtor de objetos passageiro
    	parque.addPassageiro(passageiros[i]); // adiciona os passageiros ao parque
    }


    thread tCarro(carro); //inicia thead carro

    vector<thread> tPassageiros; //inica um vector de thread de passageiros 
    for (auto &p : parque.getPassageiros()){ //for ate tamanho do vector
     tPassageiros.push_back(thread(&Passageiro::run, p)); //inicia a thread do passageiro e joga no final do vector tPassageiros
    }

    tCarro.join();
    for (auto &th : tPassageiros){
     th.join();
}
    for (int i = 0; i < 10; i++) {
    	delete passageiros[i];
    }
	return 0;
}
