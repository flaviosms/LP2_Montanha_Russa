/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include <atomic>
#include <time.h>
#include <stdlib.h>

class Carro;
class Parque;

class Passageiro {
public:
	Passageiro(int id, Carro *c, Parque *p);
	int vez;
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
	void run();
private:
	int id;
	Carro *carro;
	Parque *parque;

};

#endif /* PASSAGEIRO_H_ */
