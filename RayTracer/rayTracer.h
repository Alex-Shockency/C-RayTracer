#ifndef rayTrace_H
#define rayTrace_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cmath>
#include <cstring>
#include <omp.h>
#include <limits>

#include "model.h"
#include "sphere.h"
#include "light.h"
#include "ray.h"
#include "material.h"
#include "eigen3/Eigen/Dense"

using namespace Eigen;
using namespace std;

class rayTracer
{
public:
	bool polyCast(Ray &ray);
	bool sphereCast(Ray &ray);
	//void rayFind(Vector3f rayStart,Vector3f rayDirection);
	Vector3f rayTrace(Ray &ray,Vector3f &accum,Vector3f refatt, int level);

	inline int getIndex(int &row, int &col){
		return row*height+col;
	};
	inline Vector3f getVert(Model &model,int &faceIndex,int vertIndex){
		return model.vertList[model.faceList[faceIndex](vertIndex)];
	};
	inline Vector3f getNormal(Model &model,int &faceIndex){
		return model.vecnormList[model.facenormList[faceIndex]];
	};

	void readModel(const char* fileName);
	vector<Material> readMtl(const char* fileName);
	void buildScene(const char* fileName);
	void writeImage(const char* fileName);
	void writeImage(float tvals[],const char* fileName);

	int numVerts= 0,numFaces = 0,faceSize=0;
	char* outFile;
	vector<Model> modelList;
	vector<Sphere> sphereList;
	vector<Light> lightList;

private:
	//vector<Vector3f> vertList;
	//vector<Vector3f> faceVals;
	//vector<string> header;
	//char* modelFile;
	float tmax=-1; float tmin=-1;
	//Camera attributes
	Vector3f EV;
	Vector3f LV;
	Vector3f UP;
	Vector3f WV;
	Vector3f UV;
	Vector3f VV;
	Vector3f ambi;

	float near = 0;
	float far = 0;
	float umin=0,umax=0,vmin=0,vmax=0;
	int width=0,height =0;
	float mtranX =0,mtranY =0,mtranZ =0;
};
#endif
