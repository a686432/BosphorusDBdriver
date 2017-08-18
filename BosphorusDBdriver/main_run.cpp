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
	BosphorusDBdriver bp{ "",1 };
	auto data = bp.getdata();
	cout << data[300][3]<< endl;
}
void main_save_mash()
{
	BosphorusDBdriver bp{ "",1 };
	MyTriMesh depthRecMesh = bp.getMesh();
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