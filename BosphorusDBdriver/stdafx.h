// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
