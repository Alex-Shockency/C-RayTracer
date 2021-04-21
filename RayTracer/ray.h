#ifndef ray_H
#define ray_H

#include "eigen3/Eigen/Dense"

using namespace Eigen;
using namespace std;


class Ray
{
public:
	Ray(Vector3f L,Vector3f D);
	Vector3f L;
	Vector3f D;
	float best_t=numeric_limits<float>::infinity();
	Vector3f best_pt;
	Sphere best_sphere;
	Model best_model;
	int best_face;
	bool isSphere;
	
};

Ray::Ray(Vector3f L,Vector3f D){
	this -> L=L;
	this -> D=D;
	this -> best_t =numeric_limits<float>::infinity();
	this -> best_pt=Vector3f(0,0,0);
	this -> best_sphere=Sphere();
	this -> best_face=0;
	this -> isSphere=false;
}
#endif