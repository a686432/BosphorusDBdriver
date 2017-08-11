#pragma once
#ifndef BOSPHORUSDBDRIVER_H
#define BOSPHORUSDBDRIVER_H
#include "stdafx.h"
class BosphorusDBdriver
{
public:
	BosphorusDBdriver();
	~BosphorusDBdriver();

private:
	static bool uperTriangleValid(cv::Mat mask,const uint16_t row, const uint16_t col);
	static bool lowerTriangleValid(cv::Mat mask, const uint16_t row, const uint16_t col);
public:
	//int get_Mesh(const char* filepath);
	static MyTriMesh getMesh(const char* filepath);
	static void read_bntfile(const char* filepath, double** &data, double* zmin, uint16_t*  nrows, uint16_t* ncols, char *imfile);
};

#endif // BOSPHORUSDBDRIVER
