#pragma once
#include "Object.h"
class Shield :
	public Object
{
private:
	static Shield* instance;
public:
	static Shield* getInstance();
	Shield();
	~Shield();
};

