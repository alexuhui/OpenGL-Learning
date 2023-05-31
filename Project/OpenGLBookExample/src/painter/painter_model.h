#pragma once

#include "painter.h"
#include "../model/imported_model.h"

using namespace std;

class Painter_Model:public Painter
{
public:
	const char* modelPath = "";

protected:
	virtual void setupVertices(ImportedModel myModel);

private:
	
	
};