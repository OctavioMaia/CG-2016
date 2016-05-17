#pragma once
#ifndef PATCH_H
#define PATCH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Patch
{
private: vector<int> v;

public:
	Patch();
	Patch(vector<int> vi);
	Patch(string s);

	vector<int> getVector();

	void addControl(int point);
	void setVector(vector<int> vi);
	int getAt(int i);
};

#endif
