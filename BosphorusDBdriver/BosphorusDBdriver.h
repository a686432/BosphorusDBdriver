#pragma once
#ifndef BOSPHORUSDBDRIVER_H
#define BOSPHORUSDBDRIVER_H
#include "stdafx.h"
class BosphorusDBdriver
{
public:
	BosphorusDBdriver(const char* filepath, int index);
	~BosphorusDBdriver();
private:
	double **data;
	double zmin;
	uint16_t nrows;
	uint16_t ncols;
	uint32_t len2;
	char* imfile;
	int landmark2dn;
	int landmark3dn;
    std::vector<std::string> labels2d;
	std::vector<cv::Point2d> pts2d;
	std::vector<std::string> labels3d;
	std::vector<cv::Point3d> pts3d;
private:
	static bool uperTriangleValid(cv::Mat mask,const uint16_t row, const uint16_t col);
	static bool lowerTriangleValid(cv::Mat mask, const uint16_t row, const uint16_t col);
public:
	//int get_Mesh(const char* filepath);
	double** getdata() const { return data; };
	const double& getdata(int i, int j) const { return data[i][j]; }
	MyTriMesh getMesh();
	//void read_bntfile(const char* filepath, double** &data, double* zmin, uint16_t*  nrows, uint16_t* ncols, char *imfile);
};

#endif // BOSPHORUSDBDRIVER
