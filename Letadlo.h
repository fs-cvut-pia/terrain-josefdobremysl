#ifndef LETADLO_H
#define LETADLO_H

#include "Path.h"
#include "TerrainMap.h"

#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <set>

using namespace std;
class Letadlo : public Path
{
public:
	Letadlo(TerrainMap& m, string name_in, Point start_in, Point finish_in);
	~Letadlo();
	virtual bool find();
private:

};



#endif