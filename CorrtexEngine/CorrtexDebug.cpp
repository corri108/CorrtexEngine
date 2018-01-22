#include "stdafx.h"
#include "CorrtexDebug.h"

bool CorrtexDebug::on = false;

CorrtexDebug::CorrtexDebug()
{

}


CorrtexDebug::~CorrtexDebug()
{
}

bool CorrtexDebug::Get()
{
	return on;
}

void CorrtexDebug::Set(bool isOn)
{
	on = isOn;
}

void CorrtexDebug::GetErrorIfExists()
{

}
