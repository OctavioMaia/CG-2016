#include "Color.h"

Color::Color(double rr, double gg, double bb) {
	r = rr;
	g = gg;
	b = bb;
}

double Color::getr() { return r; }
double Color::getg() { return g; }
double Color::getb() { return b; }
