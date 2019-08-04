#pragma once
#include"Solder.h"

class GreenSolder :public Solder
{
public:
	GreenSolder(RunType runType, float x, float y);
	~GreenSolder();
	void LoadAllAnimation()override;
};