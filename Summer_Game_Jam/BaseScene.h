#pragma once
#include <stdio.h>

class BaseScene {
public:
	virtual ~BaseScene() {};
	virtual BaseScene* Update() = 0;
	virtual void Draw() const = 0;
};