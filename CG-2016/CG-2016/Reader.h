#pragma once
#ifndef READER_H
#define READER_H

#include <string>
#include <vector>
#include <math.h>

#include "windows.h" 
#include "tinyxml.h"
#include "tinystr.h"

#include "Transformation.h"
#include "Referencial.h"
#include "Scene.h"

using namespace std;

Scene readFileXML(const char* file);

#endif // !READER_H