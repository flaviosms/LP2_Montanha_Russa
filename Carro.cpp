/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include <stdlib.h>
#include <atomic>

#define TEMPO_VOLTA 5000

const int Carro::CAPACIDADE = 5;

Carro::Carro() {
	this->voltas = 0;
	numPassageiros = ATOMIC_VAR_INIT(0); //Inicia a variavel Atomica
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (Carro::numPassageiros < Carro::CAPACIDADE) {
		bool proximo=true;
		for(auto &tredi : tPassageiros){//conta até o final do vector de threads do parque(ver main.cpp)			
			if(tredi.vez<=Carro::inicioFila){proximo=false;}//se alguma variavel vez for menor ou igual ao inicio da fila nao avança o inciodafila 
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
