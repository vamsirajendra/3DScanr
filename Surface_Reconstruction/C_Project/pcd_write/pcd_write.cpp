/*
This file is for writing a PCD file "*.pcd"
The input is a "xyzPoints.txt" with x;y;z coordinates
The output is "pcd_test.pcd"

Created by: Hoang Anh Thai Vu
Updated on: February 11, 2018
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main()
{
	using namespace std;
	ifstream txtFile("xyzPoints.txt");
	string line, pointsXYZ, dummyLine;
	int cloudSize = 0;

	// Read pointcloud from txt 
	getline(txtFile, dummyLine); // skip one line
	while (getline(txtFile, line)) // looping through every line
	{
		cloudSize ++;
		string single;
		std::stringstream iss(line);
		while (iss.good()) 
		{
			std::string segment;
			while (getline(iss, segment, ';')) // replacing delimiter
			{
				pointsXYZ = pointsXYZ + segment + " ";
			}
		}
		pointsXYZ += "\n"; // new line
	}

	// To pcd fille
	// Creating header as required by PCD format
	std::string pcdHead, pcdVersion, pcdFields, pcdSize, pcdType, pcdCount, pcdWidth, pcdHeight, pcdView, pcdPoints, pcdData;
	pcdVersion = "VERSION 0.7\n";
	pcdFields = "FIELDS x y z\n";
	pcdSize = "SIZE 4 4 4\n";
	pcdType = "TYPE F F F\n";
	pcdCount = "COUNT 1 1 1\n";
	pcdWidth = "WIDTH " + to_string(cloudSize) + (string) "\n"; // edit with the right cloud size
	pcdHeight = "HEIGHT 1\n";
	pcdView = "VIEWPOINT 0 0 0 1 0 0 0\n";
	pcdPoints = "POINTS " + to_string(cloudSize) + (string) "\n"; // edit with the right cloud size
	pcdData = "DATA ascii\n";
	pcdHead = "# .PCD v0.7 - Point Cloud Data file format\n" + pcdVersion + pcdFields + pcdSize + 
		pcdType + pcdCount + pcdWidth + pcdHeight + 
		pcdView + pcdPoints + pcdData;

	// Write to pcd
	ofstream newFile("test_pcd.pcd");
	if (newFile.is_open())
	{
		newFile << pcdHead;
		newFile << pointsXYZ;
	}
	else cout << "Unable to open file";
	
	return 0;
}