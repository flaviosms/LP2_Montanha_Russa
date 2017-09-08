/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_

#include <stdlib.h>
#include <atomic>

class Parque;

class Carro {
public:
	static const int CAPACIDADE;
	static int numPassageiros;
	static int inicioFila; //conta o numero do inicio da fila
	static bool parado;
	static bool vazio;
	static std::atomic<int> pnc;//variavel atomica de pessoas no carrinho

	Carro();
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void run();

	void operator()()
	{
		run();
	}

private:
	int voltas;

};

#endif /* CARRO_H_ */
