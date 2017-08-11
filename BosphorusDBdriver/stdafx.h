// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define _USE_MATH_DEFINES
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
typedef OpenMesh::TriMesh_ArrayKernelT<>  MyTriMesh;
#ifdef _DEBUG
#pragma comment(lib, "OpenMeshCored.lib")
#pragma comment(lib, "OpenMeshToolsd.lib")
#else
#pragma comment(lib, "OpenMeshCore.lib")
#pragma comment(lib, "OpenMeshTools.lib")
#endif // _DEBUG
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <opencv2/opencv.hpp>
#include "BosphorusDBdriver.h"

using namespace std;
using namespace cv;
using namespace OpenMesh;

// TODO:  在此处引用程序需要的其他头文件
