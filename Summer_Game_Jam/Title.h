#pragma once
#include "BaseScene.h"

class Title : public BaseScene {
private:

public:
	virtual ~Title() {};
	virtual BaseScene* Update() override;
	virtual void Draw() const override;
};