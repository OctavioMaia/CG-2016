#pragma once
#ifndef COLOR_H
#define COLOR_H

#include <string>
#include <vector>

using namespace std;

class Color
{
private:
	double r, g, b;
public:
	Color(double rr, double gg, double bb);

	double getr();
	double getg();
	double getb();

};

#endif