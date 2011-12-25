

#ifndef MAIN_H_
#define MAIN_H_
#include <iostream>
#include <dlfcn.h>
#include <dirent.h>
#include <vector>
#include <cstring>
#include <map>

//#include "IAlgoSim.h"
#include "LibAlgoSim.h"

using namespace std;
typedef IAlgoSim* create_t();
class simplayer
{
	string buildpath;
public:
	vector<create_t*> CallList;
	vector<string> ScanDirectory(string path);
	void ProcessDirectory(string path);

};

#endif /* MAIN_H_ */
