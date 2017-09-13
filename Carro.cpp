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
#include <stdio.h>

#define TEMPO_VOLTA 6000

const int Carro::CAPACIDADE = 5;

std::atomic<int> Carro::numPassageiros = ATOMIC_VAR_INIT(0);

bool Carro::voltaAcabou = false;

//int Carro::voltas=0;

Carro::Carro(Parque *p) {
	this->voltas = 0;
	this->parque = p;
}
Carro::~Carro() {
}

void Carro::esperaEncher() {
	while (Carro::numPassageiros < Carro::CAPACIDADE && parque->numPessoas.load(std::memory_order_relaxed) > Carro::CAPACIDADE) {}
}

void Carro::daUmaVolta() {
	Carro::voltaAcabou = false;
	delay(TEMPO_VOLTA);
	Carro::voltaAcabou = true;
}

void Carro::esperaEsvaziar() {
	while (this->numPassageiros > 0) {}
}

int Carro::getNVoltas() {
	//std::cout<<"\nTHIS:"<<voltas<<std::endl;
	return this->voltas;
}

void Carro::run() {
	while (parque->numPessoas.load(std::memory_order_relaxed) > 0) {
		esperaEncher();
		if(parque->numPessoas.load(std::memory_order_relaxed) <= 0){break;}
		std::cout<<"\n"<<"Carro--Iniciando Volta:"<<voltas<<std::endl;
		daUmaVolta();
		std::cout<<"\n"<<"Carro--Terminei a Volta:"<<voltas<<std::endl;
		esperaEsvaziar();
		Carro::voltaAcabou = false;
		this->voltas++;
	}

}

