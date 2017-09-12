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
#include <iostream>

#define TEMPO_VOLTA 1000

const int Carro::CAPACIDADE = 5;

std::atomic<int> Carro::numPassageiros= ATOMIC_VAR_INIT(0);

bool Carro::voltaAcabou = false;


Carro::Carro(Parque *p) {
	this->voltas = 0;
	this->parque = p;
}
Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (Carro::numPassageiros < Carro::CAPACIDADE) {delay(1000);}
}

void Carro::daUmaVolta() {
	Carro::voltaAcabou = false;
	delay(TEMPO_VOLTA);
	Carro::voltaAcabou = true;
}

void Carro::esperaEsvaziar() {
	while (this->numPassageiros > 0) {delay(1000);}
}

int Carro::getNVoltas() {
	return voltas;
}

void Carro::run() {
	while (parque->numPessoas > 0) {
		esperaEncher();
		std::cout<<"Carro--Iniciando Volta:"<<voltas<<std::endl;
		daUmaVolta();
		std::cout<<"Carro--Terminei a Volta:"<<voltas<<std::endl;
		esperaEsvaziar();
		Carro::voltaAcabou = false;
		voltas++;

	}

}

