#pragma once
//very small and simple debug class
class CorrtexDebug
{
public:
	CorrtexDebug();
	~CorrtexDebug();
	static bool Get();
	static void Set(bool isOn);
	static void GetErrorIfExists();
private:
	static bool on;
};

