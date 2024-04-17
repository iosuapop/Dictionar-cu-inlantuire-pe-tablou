#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

Dictionar::Dictionar() {
	/* de adaugat */
	cp = 1;
	elems = (TElem**)malloc(sizeof(TElem*));
	elems[0] = nullptr;
	urm = (int*)malloc(sizeof(int));
	urm[0] = -1;
	prim = -1;
	primLiber = 0;
}

Dictionar::~Dictionar() {
	/* de adaugat */
	int actual = this->prim;
	if (vid()) {
		if (elems != nullptr)
			free(elems);

		if (urm != nullptr)
			free(urm);
	}
	else {
		while (elems[actual] != nullptr) {
			delete this->elems[actual];
			actual = urm[actual];
		}
		if (elems != nullptr)
			free(elems);

		if (urm != nullptr)
			free(urm);
	}
	this->prim = -1;
	this->primLiber = 0;
	this->cp = 1;
}

TValoare Dictionar::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	if (vid())
	{
		this->prim = this->primLiber;
		TElem* elem = new TElem(c, v);
		this->elems[this->primLiber] = elem;
		int vechi_primLiber = this->primLiber;
		this->primLiber = urmPrimLiber();
		if (primLiber >= cp)
			redimensionare();
		this->urm[vechi_primLiber] = this->primLiber;
		return NULL_TVALOARE;

	}
	if (this->find(c) != 'f')
		//(cauta(c) != NULL_TVALOARE) 
	{
		//exista elementul
		int actual = this->prim;
		TElem elem = *this->elems[actual];
		if (elem.first == c)
		{
			int veche = elem.second;
			elem.second = v;
			delete this->elems[actual];
			TElem* new_elem = new TElem(c, v);
			this->elems[actual] = new_elem;
			return veche;
		}
		while (elem.first != c)
		{
			actual = this->urm[actual];
			elem = *this->elems[actual];
		}
		int veche = elem.second;
		elem.second = v;
		delete this->elems[actual];
		TElem* new_elem = new TElem(c, v);
		this->elems[actual] = new_elem;
		return veche;
	}
	else
	{
		if (this->primLiber < this->cp) {
			TElem* elem = new TElem(c, v);
			this->elems[this->primLiber] = elem;
			int vechi_primLiber = this->primLiber;
			this->primLiber = urmPrimLiber();
			if (primLiber >= cp)
				redimensionare();
			this->urm[vechi_primLiber] = this->primLiber;
			return NULL_TVALOARE;
		}
		else
		{
			redimensionare();
			TElem* elem = new TElem(c, v);
			this->elems[this->primLiber] = elem;
			int vechi_primLiber = this->primLiber;
			this->primLiber = urmPrimLiber();
			if (primLiber >= cp)
				redimensionare();
			this->urm[vechi_primLiber] = this->primLiber;
			return NULL_TVALOARE;
		}
	}
	return NULL_TVALOARE;
}

void Dictionar::redimensionare() {
	int new_cp = this->cp * 2;
	TElem** new_elems = (TElem**)malloc(new_cp * sizeof(TElem*));
	int* new_urm = (int*)malloc(new_cp * sizeof(int));
	for (int i = 0; i < this->cp; i++) {
		new_urm[i] = this->urm[i];
		new_elems[i] = this->elems[i];
	}
	for (int i = this->cp; i < new_cp; i++)
	{
		new_urm[i] = -1;
		new_elems[i] = nullptr;
	}
	if(elems != nullptr)
		free(this->elems);
	if(urm != nullptr)
		free(this->urm);

	this->cp = new_cp;
	this->elems = new_elems;
	this->urm = new_urm;
}

int Dictionar::urmPrimLiber() {
	if (vid()) {
		return 0;
	}
	for (int i = 0; i < this->cp; i++) {
		if (this->elems[i] == nullptr) {
			if(i != this->prim)
				return i;
		}
	}
	return cp;
}


//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const {
	/* de adaugat */
	if (vid())
		return NULL_TVALOARE;//NULL
	int actual = prim;
	TElem elem = *elems[actual];
	if (elem.first == c)
		return elem.second;
	while (elems[urm[actual]] != nullptr && urm[actual] < cp)
	{
		actual = urm[actual];
		elem = *elems[actual];
		if (elem.first == c)
			return elem.second;
	}
	return NULL_TVALOARE;//NULL
}

char Dictionar::find(TCheie c) const {
	if (vid())
		return 'f';
	int actual = prim;
	TElem elem = *elems[actual];
	if (elem.first == c)
		return 't';
	while (elems[urm[actual]] != nullptr && urm[actual] < cp)
	{
		actual = urm[actual];
		elem = *elems[actual];
		if (elem.first == c)
			return 't';
	}
	return 'f';
}


TValoare Dictionar::sterge(TCheie c) {
	/* de adaugat */
	if (this->find(c) == 'f')
		//(this->cauta(c) == NULL_TVALOARE)//nu existaa elmentul de sters
		return NULL_TVALOARE;
	else {
		int actual = this->prim;
		int veche;
		TElem elem = *this->elems[actual];
		if (elem.first == c && this->dim() == 1) {//exista un singur element
			this->urm[prim] = -1;
			this->prim = -1;
			veche = elem.second;
			delete this->elems[actual];
			return veche;
		}
		else {
			if (elem.first == c && urm[actual] != -1) {//stergem primul element
				int vechi_prim = this->prim;
				this->prim = urm[actual];
				urm[vechi_prim] = -1;
				veche = elem.second;
				delete this->elems[actual];
				return veche;
			}
			else
			{// e pe la mijloc
				actual = this->urm[actual];
				int prev = this->prim;
				elem = *this->elems[actual];
				while (elem.first != c)
				{
					prev = actual;
					actual = urm[actual];
					elem = *this->elems[actual];
				}
				this->urm[prev] = this->urm[actual];
				this->urm[actual] = -1;
				int veche = elem.second;
				delete this->elems[actual];
				return veche;
			}
			
		}
	}
	return NULL_TVALOARE;
}


int Dictionar::dim() const {
	/* de adaugat */
	if (vid())
		return 0;
	int actual = this->prim;
	int nr = 0;
	while (this->urm[actual] != -1) {
		nr++;
		actual = this->urm[actual];
	}
	return nr;
}

bool Dictionar::vid() const {
	/* de adaugat */
	if(this->prim == -1)
		return true;
	return false;
}


IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}

int Dictionar::diferentaCheieMaxMin() const {
	TElem minim, maxim;
	if (vid())
		return NULL_TVALOARE;
	else
	{
		int actual = this->prim;
		TElem elem = *this->elems[actual];
		minim = elem;
		maxim = elem;

		while (this->elems[actual] != nullptr) {
			elem = *this->elems[actual];
			if (elem.first > maxim.first)
				maxim = elem;

			if (elem.first < minim.first)
				minim = elem;

			actual = this->urm[actual];
		}
		return maxim.second - minim.second;
	}

}

int Dictionar::adaugaInexistente(Dictionar& d)
{
	if (d.vid())
		return 0;
	else 
	{
		int nr = 0;
		int actual, actual_new = d.prim;
		while(d.elems[actual_new] != nullptr){
			actual = this->prim;
			TElem elem = *d.elems[actual_new];
			while(this->elems[actual] != nullptr){
				if (this->find(elem.first) == 'f')
				{
					adauga(elem.first, elem.second);
					nr++;
				}
				actual = this->urm[actual];
			}
			actual_new = d.urm[actual_new];
		}
		return nr;
	}
}

