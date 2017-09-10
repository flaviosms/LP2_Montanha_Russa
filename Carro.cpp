/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include "include/Passageiro.h"
#include <stdlib.h>
#include <atomic>

#define TEMPO_VOLTA 500

const int Carro::CAPACIDADE = 5;

Carro::Carro(Parque *p) {
	this->voltas = 0;
	numPassageiros = ATOMIC_VAR_INIT(0); //Inicia a variavel Atomica
	this->parque = p;
	this->inicioFila=0;
	this->parado=true;
	this->vazio=true;
}
Carro::Carro(const Carro& origin)
: numPassageiros(origin.numPassageiros.load())
{
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (Carro::numPassageiros < Carro::CAPACIDADE) {
		bool proximo=true;
		int i;
		for(auto &tredi : parque->getPassageiros()){//conta até o final do vector de threads do parque(ver main.cpp)			
 			if(tredi->vez<Carro::inicioFila){proximo=false;}
 		}
		if(proximo){
			Carro::inicioFila++;
		}
	}
	vazio = false;

}

void Carro::daUmaVolta() {
	parado = false;
	delay(TEMPO_VOLTA);
	parado = true;
}

void Carro::esperaEsvaziar() {
	while (Carro::numPassageiros > 0) { delay(250); }
	vazio = true;
}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	while (Parque::numPessoas > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

		voltas++;

	}
}
