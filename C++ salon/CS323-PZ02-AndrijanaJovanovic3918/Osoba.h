#pragma once
#include <iostream>
#include <string>
#include "Salon.h"
using namespace std;

class Osoba
{
private:
	string ime, prezime;
public:
	Osoba() {};
	Osoba(string i, string p) : ime(i), prezime(p) {};
	~Osoba() {};

	void setIme(string i) { ime = i; }
	void setPrezime(string p) { prezime = p; }
	string getIme() { return ime; }
	string getPrezime() { return prezime; }

	virtual double racunajZaradu(Salon salon) = 0;
	virtual void prikazi() = 0;

};

