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
#include <random>
#include <thread>

#if defined (_MSC_VER)  // Visual studio
    #define thread_local __declspec( thread )
#elif defined (__GCC__) // GCC
    #define thread_local __thread
#endif

#define MAX_NUM_VOLTAS 5

Passageiro::Passageiro(int id, Carro *c, Parque *p) {
	this->id = id;
	this->carro = c;
	this->parque = p;
}


Passageiro::~Passageiro() {
}
int Passageiro::continuar = 1;

void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	int max=0; //Valor maximo ou fim da fila
	for(auto &tred : parque->getPassageiros()){//conta até o final do vector de threads do parque(ver main.cpp)
 		if(tred->vez>max){ //se a vez de alguem que está esperando for maior que o maximo
 			max+=tred->vez;//o maximo passa a ser o maior mais 1
 		}
 	}
	this->vez=max + 1; //passa o valor maximo para ser a vez do passageiro 
	for(auto &tred : parque->getPassageiros()){//conta até o final do vector de threads do parque(ver main.cpp)
		if(this->id!=tred->id){
			while((tred->vez!=0 && ( this->vez > tred->vez || (vez == tred->vez && this->id > tred->id) ) ) || (carro->Carro::numPassageiros) >= (Carro::CAPACIDADE) || (carro->voltaAcabou)){
				
			}
		}
	}
	std::atomic_fetch_add(&carro->numPassageiros,1);//Incrementa o numero de passageiros no carro
	this->vez=0;
}

void Passageiro::esperaVoltaAcabar() {
	while (!Carro::voltaAcabou) {} //espera ate o carro estar parado
}

void Passageiro::saiDoCarro() {
	std::atomic_fetch_sub(&carro->numPassageiros,1);
}

void Passageiro::passeiaPeloParque() {
	//-----------------------------------------------
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0,9000); // guaranteed unbiased

	auto random_integer = uni(rng);
	//-----------------------------------------------
	std::cout<<"\n"<<this->id<<"--Esperando"<<random_integer+1000<<"segundos"<<std::endl;
	delay((random_integer)+1000); ///dorme por um tempo randomico
}

bool Passageiro::parqueFechado() {
	if (carro->getNVoltas() < MAX_NUM_VOLTAS){
		//fprintf(stderr, "\n Voltas %d",carro->getNVoltas());
		return false;
	}

	return true;
}

void Passageiro::run() {
	int pvoltas=0;
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada
		std::cout<<"\n"<<this->id<<"--Entrei no Carro"<<std::endl;
		esperaVoltaAcabar();
		pvoltas++;
		saiDoCarro(); // protocolo de saida
		std::cout<<"\n"<<this->id<<"--Sai do Carro"<<std::endl;
		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de pessoas no parque
	std::atomic_fetch_sub(&parque->numPessoas,1);
	std::cout<<"\n"<<this->id<<"--Eu dei "<<pvoltas<<" voltas na montanha russa."<<std::endl;

}

int Passageiro::intRand(const int & min, const int & max) {
    static thread_local std::mt19937 generator;
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}


