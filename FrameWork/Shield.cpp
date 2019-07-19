#include "Shield.h"

Shield * Shield::instance = NULL;

Shield::Shield()
{
}

Shield* Shield::getInstance()
{
	if (!instance)
		instance = new Shield();
	return instance;
}

Shield::~Shield()
{
}
