#pragma once
#include "CorrtexObject.h"

//create different kind of delegates, mostly for dealing with behaviours
typedef void(*CorrtexFunc)(void);
typedef int(*CorrtexFunci)(void);
typedef int(*CorrtexFunci_i)(int);
typedef void(*CorrtexFuncf)(float, int);