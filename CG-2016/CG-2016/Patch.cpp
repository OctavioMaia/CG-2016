#include "Patch.h"

/*
string removeSpaces(string input)
{
	std::string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
	//input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	return input;
}
*/

int min(int i1, int i2) {
	if (i1 <= i2) return i1;
	return i2;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}



string trim(string& str)
{
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

Patch::Patch() {}

Patch::Patch(vector<int> vi) {
	v = vi;
}

Patch::Patch(string s) {
	vector<string> campos;
	// sl = removeSpaces(s);
	string sl = trim(s);
	split(sl, ',', campos);
	for (int i = 0; i < 16; i++)
	{
		trim(campos[i]);
		v.push_back(atoi(campos[i].c_str()));
	}
}

void Patch::addControl(int i) {
	v.push_back(i);

}
void Patch::setVector(vector<int> vi) {
	v = vi;
}

vector<int> Patch::getVector() {
	return v;

}

int Patch::getAt(int i) {
	return v[i];
}
