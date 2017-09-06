#include <iostream>
#include <vector>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	Parque parque;
	Carro carro;
	Passageiro *passageiros[10];

    for (int i = 0; i < 10; i++) {
    	passageiros[i] = new Passageiro(i, &carro);
    	parque.addPassageiro(passageiros[i]);
    }

    thread tCarro(carro);

    vector<thread> tPassageiros;
    for (auto &p : parque.getPassageiros()) tPassageiros.push_back(thread(&Passageiro::run, p));

    tCarro.join();
    for (auto &th : tPassageiros) th.join();

    for (int i = 0; i < 10; i++) {
    	delete passageiros[i];
    }

	return 0;
}
