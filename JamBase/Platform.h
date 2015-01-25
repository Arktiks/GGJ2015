#pragma once
#include "GameObject.h"
class Platform : public GameObject
{
public:
	Platform() : angle(0), speedboost(false) {};
	Platform(int angle, bool speedboost) : angle(angle), speedboost(speedboost) {};
	~Platform() {};

private:
	int angle;
	bool speedboost;
};

