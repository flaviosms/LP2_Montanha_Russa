/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"
#include <atomic>
#include <time.h>
#include <iostream>

#define MAX_NUM_VOLTAS 50

Passageiro::Passageiro(int id, Carro *c, Parque *p) {
	this->id = id;
	this->carro = c;
	this->parque = p;
}


Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	int max=0; //Valor maximo ou fim da fila
	int i;
	for(auto &tred : parque->getPassageiros()){//conta até o final do vector de threads do parque(ver main.cpp)
 		if(tred->vez>max){ //se a vez de alguem que está esperando for maior que o maximo
 			max+=tred->vez;//o maximo passa a ser o maior mais 1
 		}
 	}
	vez=max; //passa o valor maximo para ser a vez do passageiro que chegou
	while(!Carro::vazio){delay(100);} // espera o carrinho ficar vazio
	iniciodafila:
	if((vez==Carro::inicioFila) && (Carro::numPassageiros<(Carro::CAPACIDADE))){//ve se esta na vez se carro nao esta cheio
		for(auto &tred : parque->getPassageiros()){//conta até o final do vector de threads do parque(ver main.cpp)
			if(vez==tred->vez){ //ve se existe outra thread que tem a mesma vez
				if((this->id)>tred->id){ //Caso tenha , testa para ver qual a maior id (nao se atrapalha com si mesma pois o operador é >)
					delay(25);
					goto iniciodafila; //Se o id for menor vai pro começo da fila
				}
			}
		}
		std::atomic_fetch_add(&Carro::numPassageiros,1);//Incrementa o numero de passageiros no carro
	}
	


}

void Passageiro::esperaVoltaAcabar() {
	while (!Carro::parado) { delay(100); } //espera ate o carro estar parado
}

void Passageiro::saiDoCarro() {
	if(Carro::numPassageiros > 0 && Carro::parado){ // Teste so pra ter certeza mesmo
		std::atomic_fetch_add(&Carro::numPassageiros,-1); //Sai do carro
	}
	else{
		std::cout<<"404 caiu do carrinho"<<std::endl;
	}
}

void Passageiro::passeiaPeloParque() {
	srand(time(NULL));//randomiza a seed 
	delay((rand()%10000)); ///dorme por um tempo randomico
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS){
		return false;
	}

	return true;
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de pessoas no parque
	Parque::numPessoas -=1;
}

