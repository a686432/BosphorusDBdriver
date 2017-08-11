
#include "stdafx.h"
void BosphorusDBdriver::read_bntfile(const char* filepath, double** &data, double* zmin, uint16_t*  nrows, uint16_t* ncols, char *imfile)
{
	long size;
	ifstream in(filepath, ios::in | ios::binary | ios::ate);
	if (!in.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	uint16_t len;
	uint32_t len2;
	double k;
	size = in.tellg();
	in.seekg (0, ios::beg);
	in.read((char*)nrows, sizeof(uint16_t));
	in.read((char*)ncols, sizeof(uint16_t));
	in.read((char*)zmin, sizeof(double));
	in.read((char*)&len, sizeof(uint16_t));
	in.read((char*)imfile, sizeof(char)*len);
	in.read((char*)&len2, sizeof(uint32_t));
	data = new double*[len2 / 5];
	for (int i = 0; i < len2 / 5; i++)
		data[i] = new double[5];
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < len2 / 5; i++)
		{
			in.read((char*)&k, sizeof(double));
			data[i][j] = k;
		}
	}
	in.close();
	cout<< "the complete file is in a buffer"<<endl;
}

bool BosphorusDBdriver::uperTriangleValid(Mat mask, const uint16_t row, const uint16_t col)
{
	int widthImage = mask.cols;
	int heightImage = mask.rows;
	if (row == heightImage - 1 || col == widthImage - 1)
		return false;
	if (mask.at<cv::Vec3d>(row, col) == cv::Vec3d(0, 0, 0) || mask.at<cv::Vec3d>(row + 1, col) == cv::Vec3d(0, 0, 0) || mask.at<cv::Vec3d>(row, col + 1) == cv::Vec3d(0, 0, 0))
		return false;
	else
		return true;
}
bool BosphorusDBdriver::lowerTriangleValid(Mat mask, const uint16_t row, const uint16_t col)
{
	int widthImage = mask.cols;
	int heightImage = mask.rows;
		if (row == heightImage - 1 || col == widthImage - 1)
			return false;
		if (mask.at<cv::Vec3d>(row + 1, col + 1)== cv::Vec3d(0, 0, 0) || mask.at<cv::Vec3d>(row + 1, col) == cv::Vec3d(0, 0, 0) || mask.at<cv::Vec3d>(row, col + 1) == cv::Vec3d(0, 0, 0))
			return false;
		else
			return true;
}

MyTriMesh BosphorusDBdriver::getMesh(const char* filepath)
{
	MyTriMesh mesh;
	double **data;
	double zmin;
	uint16_t ncols, nrows;
	char imfile[50];
	BosphorusDBdriver::read_bntfile("1.bnt", data, &zmin, &nrows, &ncols, imfile);
	int vertexCount = nrows * ncols;
	MyTriMesh::VertexHandle* vhandle = new MyTriMesh::VertexHandle[vertexCount];
	cv::Mat mask = cv::Mat::zeros(nrows, ncols, CV_64FC3);
	for (int idx = 0; idx < vertexCount; idx++)
	{
		vhandle[idx] = mesh.add_vertex(MyTriMesh::Point(data[idx][0], data[idx][1], data[idx][2]));
		if (data[idx][0] == zmin)
			mask.at<cv::Vec3d>(idx / ncols, idx%ncols) = cv::Vec3d(0, 0, 0);
		else
     		mask.at<cv::Vec3d>(idx / ncols, idx%ncols) = cv::Vec3d(data[idx][0], data[idx][1], data[idx][2]);
	}
	
	std::set<int> validVertIdx;
	// Insert topology on the Mesh
	std::vector<MyTriMesh::VertexHandle>  face_vhandles;
	for (int row = 0; row < nrows; row++)
	{
		for (int col = 0; col < ncols; col++)
		{
			if (uperTriangleValid(mask, row, col))
			{
				int index_0 = row*ncols + col;
				int index_2 = row*ncols + col + 1;
				int index_1 = (row + 1)*ncols + col;
				//record valid vertices
				validVertIdx.insert(index_0);
				validVertIdx.insert(index_1);
				validVertIdx.insert(index_2);

				face_vhandles.clear();
				face_vhandles.push_back(vhandle[index_0]);
				face_vhandles.push_back(vhandle[index_1]);
				face_vhandles.push_back(vhandle[index_2]);
				mesh.add_face(face_vhandles);
			}

			if (lowerTriangleValid(mask, row, col))
			{
				int index_0 = (row + 1)*ncols + col;
				int index_2 = row*ncols + col + 1;
				int index_1 = (row + 1)*ncols + col + 1;
				//record valid vertices
				validVertIdx.insert(index_0);
				validVertIdx.insert(index_1);
				validVertIdx.insert(index_2);

				face_vhandles.clear();
				face_vhandles.push_back(vhandle[index_0]);
				face_vhandles.push_back(vhandle[index_1]);
				face_vhandles.push_back(vhandle[index_2]);
				mesh.add_face(face_vhandles);
			}
		}
	}
	if (!mesh.has_vertex_status())
		mesh.request_vertex_status();
	if (!mesh.has_face_status())
		mesh.request_face_status();
	if (!mesh.has_edge_status())
		mesh.request_edge_status();
	//find the invalid pt set
	vector<int> invalidVertIdx;
	invalidVertIdx.reserve(vertexCount - validVertIdx.size());
	std::set<int>::iterator iter = validVertIdx.begin();
	for (int i = 0; i<vertexCount; i++)
	{
		if (i<(*iter))
			invalidVertIdx.push_back(i);
		else
		{
			if (iter != validVertIdx.end())
			{
				iter++;
				if (iter == validVertIdx.end())
				{
					for (int j = i + 1; j<vertexCount; j++)
						invalidVertIdx.push_back(j);
					break;
				}
			}
		}
	}
	for (int i = 0; i<invalidVertIdx.size(); i++)
		mesh.delete_vertex(mesh.vertex_handle(invalidVertIdx[i]), false);

	delete vhandle;
	mesh.garbage_collection();
	//release attribute
	if (mesh.has_vertex_status())
		mesh.release_vertex_status();
	if (mesh.has_face_status())
		mesh.release_vertex_status();
	if (mesh.has_edge_status())
		mesh.release_vertex_status();

	//update face normal
	mesh.request_face_normals();
	mesh.update_face_normals();

	//update vertex normal
	mesh.request_vertex_normals();
	mesh.update_vertex_normals();
	
	return mesh;
}