#pragma once
#include "GameObject.h"
class Platform : public GameObject
{
public:

	Platform();
	Platform(int angle, bool speedboost);
	~Platform();


private:

	int angle;

	bool speedboost;
};

