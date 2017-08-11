// BosphorusDBdriver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BosphorusDBdriver.h"
string test_fold = "../data/";
string input_fold = test_fold + "input/";
string output_fold = test_fold + "output/";
string kinect_mesh_name = "pose_1_kinect_mesh.obj";
string kinect_mesh_file = output_fold + kinect_mesh_name;



void main_read()
{
	char* filepath= "1.but";
	double **data=nullptr;
	double zmin;
	uint16_t ncols, nrows;  
	char imfile[50];
	BosphorusDBdriver::read_bntfile("1.bnt", data, &zmin, &nrows, &ncols, imfile);
	//int vertexCount = nrows * ncols;
	//int idx = 300;
	//cout << data[idx][3] << " " << idx / ncols << " " << idx%ncols << endl;
	//for (int idx = 0; idx < vertexCount; idx++)
	//	cout << data[idx] << " " << idx / ncols << " " << idx%ncols << endl;
}
void main_save_mash()
{
	MyTriMesh depthRecMesh = BosphorusDBdriver::getMesh("1.bnt");
	if (!OpenMesh::IO::write_mesh(depthRecMesh, kinect_mesh_file.c_str()))
	{
		std::cerr << "Cannot write mesh to file: " << kinect_mesh_file << std::endl;
	}
	else
		std::cout << "successfully save mesh" << std::endl;
}
int main()
{
	//main_read();
	main_save_mash();
	return 0;
}