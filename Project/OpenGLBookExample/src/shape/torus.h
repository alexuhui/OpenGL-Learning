#include <cmath>
#include <vector>
#include <glm\glm.hpp>

#include "shape.h"

class Torus : public Shape
{
public:
	Torus();
	Torus(float inner, float outer, int prec);

private:
	int prec;
	float inner;
	float outer;

	void init();
};