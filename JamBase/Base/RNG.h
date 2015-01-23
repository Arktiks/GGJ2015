// Yleisesti k‰ytettyj‰ RNG-funktiota.
// K‰ytt‰‰ hyv‰ksi srand, joten seed pit‰‰ alustaa jossain kohti.

#pragma once
class RNG
{
public:
	static bool Chance(int percentualSuccess);	// Palauttaa true jos arvottu luku pienempi kuin annettu luku.
	static int Random(int max);					// Luku v‰lilt‰ 0-Max.
	static int RandomNotZero(int max);			// Luku v‰lilt‰ 1-Max.
	static int Between(int min, int max);		// Luku v‰lilt‰ Min-Max.
};