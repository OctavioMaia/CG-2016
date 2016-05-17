#pragma once
#ifndef READER_H
#define READER_H

#include "windows.h" 
#include "tinyxml.h"
#include "tinystr.h"
#include <string>
#include <vector>
#include "Referencial.h"
#include <math.h>
#include "Scene.h"
using namespace std;

Scene readFileXML(const char* file);

#endif // !READER_H