#pragma once
#include "CorrtexObject.h"

typedef void(*CorrtexFunc)(void);
typedef int(*CorrtexFunci)(void);
typedef int(*CorrtexFunci_i)(int);
typedef void(*CorrtexFuncf)(float);
//typedef void(*CorrtexBehaviour)(CorrtexObject);
//typedef void(CorrtexObject::*CorrtexBehaviour)(void);

class CorrtexDelegate
{
public:
	CorrtexDelegate();
	~CorrtexDelegate();
};

