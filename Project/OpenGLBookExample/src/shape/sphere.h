#include <cmath>
#include <vector>
#include <glm\glm.hpp>

#include "shape.h"

class Sphere: public Shape
{
public:
	Sphere();
	Sphere(int prec);

private:
	void init(int);
	float toRadians(float degrees);
};