#pragma once

#include "raylib.h"
#include <string>
#include <vector>

using namespace std;

class DataFile
{
public:
	struct Record {
		Image image;
		string name;
		int age;
	};

private:
	string recordsFilePath;
	std::vector<int> recordIndices;



public:
	Record* GetRecord(int index);
	int GetRecordCount();

	void Load(string filename);
};