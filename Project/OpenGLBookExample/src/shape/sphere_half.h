#pragma once

#include <cmath>
#include <vector>
#include <glm\glm.hpp>

#include "shape.h"

class HalfSphere: public Shape
{
public:
	HalfSphere();
	HalfSphere(int prec);

private:
	void init(int);
};