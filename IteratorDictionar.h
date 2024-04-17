#pragma once
#include "Dictionar.h"

class IteratorDictionar
{
	friend class Dictionar;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	//complexitate theta(1)
	IteratorDictionar(const Dictionar& d);

	//contine o referinta catre containerul pe care il itereaza
	const Dictionar& dict;
	/* aici e reprezentarea specifica a iteratorului */
	int actual;

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	//complexitate theta(1)
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	//complexitate theta(1)
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	//complexitate theta(1)
	bool valid() const noexcept(false);

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	//complexitate theta(1)
	TElem element() const noexcept(false);
};
