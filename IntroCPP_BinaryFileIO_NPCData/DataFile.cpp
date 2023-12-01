#include "DataFile.h"
#include <fstream>
#include <iostream>
using namespace std;

DataFile::Record* DataFile::GetRecord(int index)
{
	if (index >= recordIndices.size())
	{
		std::cout << "No record exists with the given index";
		return nullptr;
	}

	ifstream infile(recordsFilePath, ios::binary);

	infile.seekg(recordIndices[index], ios_base::beg);

	int nameSize = 0;
	int ageSize = 0;
	int width = 0, height = 0, imageSize = 0;

	infile.read((char*)&width, sizeof(int));
	infile.read((char*)&height, sizeof(int));

	imageSize = sizeof(Color) * width * height;

	infile.read((char*)&nameSize, sizeof(int));
	infile.read((char*)&ageSize, sizeof(int));

	char* imgdata = new char[imageSize];
	infile.read(imgdata, imageSize);

	Image img = LoadImageEx((Color*)imgdata, width, height);
	char* name = new char[nameSize + 1];
	int age = 0;

	infile.read((char*)name, nameSize);
	name[nameSize] = '\0';
	infile.read((char*)&age, ageSize);

	Record* record = new Record();
	record->image = img;
	record->name = string(name);
	record->age = age;

	delete[] imgdata;
	delete[] name;

	return record;
}

void DataFile::Load(string filename)
{
	recordsFilePath = filename;

	ifstream infile(filename, ios::binary);

	int recordCount = 0;
	infile.read((char*)&recordCount, sizeof(int));

	for (int i = 0; i < recordCount; i++)
	{
		recordIndices.push_back(infile.tellg());

		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, imageSize = 0;

		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));

		imageSize = sizeof(Color) * width * height;

		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));

		infile.seekg((streamoff)nameSize + ageSize + imageSize, ios_base::cur);
	}

	infile.close();
}

int DataFile::GetRecordCount()
{
	return recordIndices.size();
}