/*
 * Parque.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PARQUE_H_
#define PARQUE_H_

//--------------------------------------------------
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
  #include <windows.h>
  inline void delay( unsigned long ms )
    {
    Sleep( ms );
    }
#else  /* presume POSIX */

  #include <unistd.h>

  inline void delay( unsigned long ms )
    {
    usleep( ms * 1000 );
    }

#endif 
//----------------------------------------------------
#include <vector>
#include <atomic>

class Passageiro;

using namespace std;

class Parque {
public:
  static std::atomic<int> numPessoas;

	Parque();
	virtual ~Parque();

	void addPassageiro(Passageiro *p);
	std::vector<Passageiro*>& getPassageiros();

private:
	std::vector<Passageiro*> passageiros;
};

#endif /* PARQUE_H_ */
