#pragma once


#define NULL_TVALOARE -1
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Dictionar {
	friend class IteratorDictionar;

private:
	/* aici e reprezentarea */
	int cp, prim, primLiber;
	TElem** elems;
	int* urm;

	//complexitatea theta(2*n)
	//cel mai bun/rau caz O(2*n)
	void redimensionare();

	//complexitatea theta(m)
	//cel mai bun Omega(1) (vid)
	//cel mai rau caz O(n) il gaseste sau nu 
	int urmPrimLiber();
public:

	// constructorul implicit al dictionarului
	//complexitate theta(1)
	Dictionar();

	// adauga o pereche (cheie, valoare) in dictionar	
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	//complexitatea theta(m)
	//cel mai bun/caz Omega(1) (vid/inceput)
	//cel mai rau caz O(n) il gaseste sau nu 
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	//complexitatea theta(m)
	//cel mai bun Omega(1) (vid)
	//cel mai rau caz O(m) il gaseste sau nu 
	TValoare cauta(TCheie c) const;

	//eroare de cautare (asauga (-1,-1) si cand cauta daca exista (-1,-1) da (-1) "ceea ce inseamna NULL_TVALOARE = nu exista"
	//complexitatea theta(m)
	//cel mai bun Omega(1) (vid/inceput)
	//cel mai bun/rau caz O(n)
	char find(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	//complexitatea theta(m)
	//cel mai bun Omega(1) (vid/inceput)
	//cel mai rau caz O(n) il gaseste sau nu 
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar 
	//complexitatea theta(n)
	//cel mai bun/rau caz O(n)
	int dim() const;

	//verifica daca dictionarul e vid 
	//complexitate theta(1)
	bool vid() const;

	// se returneaza iterator pe dictionar
	//complexitate theta(1)
	IteratorDictionar iterator() const;


	// destructorul dictionarului	
	//complexitatea theta(n)
	//cel mai bun/caz Omega(n)
	~Dictionar();

	/*
	TAD Dicționar

	// returnează diferența dintre cheia maximă și cheia minimă (presupunem chei intregi)

	// Dacă dicționarul este vid, se returnează  -1
	*/


	/*
	daca dictionar = vid atunci return -1
	altfel
		actual <- dictionar.prim
		(TElem) elem <- *dictionar.elems[actual]
		minim,maxim <- elem
		cat timp elems[actual] =/= nullptr executa
			elem <- *dictionar.elems[actual]
			daca elem.first > maxim.first atunci
				maxim = actual.elem
			daca elem.first < minim.first atunci
				minim = actual.elem
			actual = actual.next
		return maxim.second - minim.second
	*/


	//complexitatea theta(n)
	//cel mai bun/rau caz O(n)
	int diferentaCheieMaxMin() const;


	/*
	Pseudocode

	daca d = vid atunci
		return 0
	altfel
		nr <- 0
		actual_new <- d.prim
		cat timp d.elems[actual_new] =/= nil executa
			actual <- prim
			(TElem) elem <- *d.elems[actual_new]
			cat timp elems[actual] =/= nil executa
				daca find(elem.first) = 'f') atunci
					adauga(elems.first, elems.second)
					nr <- nr + 1
				actual <- urm[aactual]
			actual_new <- d.urm[actual_new]
		return nr;
	
	*/

	//complexitate O(n*m)
	//cel mai bun caz tetha(m^2) (primele m elemente sunt egale cu elementele din dictionarul d)
	//cel mai rau caz tetha(n*m) m-dimensiunea dictionarului d (nu se afla cheile din d in dictionarul curent)

	int adaugaInexistente(Dictionar& d);

};


