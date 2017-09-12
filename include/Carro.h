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
	static std::atomic<int> numPassageiros;
	static bool voltaAcabou;

	Carro(Parque *);
	//Carro(const Carro&);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void run();
	bool FechaParque();
	void operator()()
	{
		run();
	}

private:
	int voltas;
	Parque *parque;
};

#endif /* CARRO_H_ */
