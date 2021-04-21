#ifndef model_H
#define model_H

#include "eigen3/Eigen/Dense"
#include "material.h"

using namespace Eigen;
using namespace std;

class Model
{
public:
	Model(vector<Vector3f> vL,vector<Vector3f> vnL,vector<Vector4f> fL,vector<int> fnL,vector<Material> matList);
	Model();
	vector<Vector3f> vertList;
	vector<Vector3f> vecnormList;
	vector<Vector4f> faceList;
	vector<Material> matList;
	vector<int> facenormList;
	char* mtlib;
};

Model::Model(){

}

Model::Model(vector<Vector3f> vL,vector<Vector3f> vnL,vector<Vector4f> fL,vector<int> fnL,vector<Material> mL){
	vertList = vL;
	vecnormList = vnL;
	faceList = fL;
	facenormList = fnL;
	matList = mL;
}

#endif