#pragma once
#include"Global.h"

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};
	virtual void LoadResources() {};			
	virtual void Update(float dt) {};			
	virtual void Render() {};					
	virtual void OnKeyDown() {};		
	virtual void OnKeyUp() {};		
};