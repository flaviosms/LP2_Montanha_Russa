#include <iostream>
#include <vector>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

void Exibe(Parque *parque,Carro *carro){
    cout<<"||\tParque\t||\tParado\t||\tPassageiros\t||"<<endl;
    int aux;
    while(1){
        if(carro->parado){aux=1;}
        else{aux=0;}
        cout<<"||\t"<<(parque->getPassageiros()).size()<<"\t||\t"<<aux<<"\t||\t"<<(carro->numPassageiros).load(memory_order_relaxed)<<endl;
        delay(25);
    }
}

int main() {
    Parque parque;
	Carro carro(&parque);
	Passageiro *passageiros[10];
    thread tExibe(Exibe,&parque,&carro);

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
