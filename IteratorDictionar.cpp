#include "IteratorDictionar.h"
#include "Dictionar.h"
#include <exception>

using namespace std;

IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d) {
	/* de adaugat */
	this->actual = this->dict.prim;
}


void IteratorDictionar::prim() {
	/* de adaugat */
	this->actual = this->dict.prim;
}


void IteratorDictionar::urmator() noexcept(false) {
	/* de adaugat */
	if (!valid())
		throw std::exception("NU este valid urmatorul");
	this->actual = dict.urm[this->actual];
}


TElem IteratorDictionar::element() const noexcept(false) {
	/* de adaugat */
	if (!valid())
		throw std::exception("AAcest element NU este valid");
	if(this->dict.elems == nullptr || this->dict.elems[this->actual] == nullptr)
		return pair <TCheie, TValoare>(-1, -1);
	TElem elem = *this->dict.elems[this->actual];
	return elem;
}


bool IteratorDictionar::valid() const{
	/* de adaugat */
	if ( this->actual == -1 || this->dict.elems == nullptr || this->dict.elems[actual] == nullptr)
		return false;
	else
		return true;
}

