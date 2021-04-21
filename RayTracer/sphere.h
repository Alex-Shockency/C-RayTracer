#ifndef sphere_H
#define sphere_H

#include "eigen3/Eigen/Dense"

using namespace Eigen;
using namespace std;

class Sphere
{
public:
	Sphere(Vector3f CV,float rad,float r,float g,float b);
	Sphere();
	Vector3f CV;
	float rad;
	float r,g,b;
};

Sphere::Sphere(Vector3f CV,float rad,float r,float g,float b){
	this -> CV= CV;
	this -> rad=rad;
	this -> r=r;
	this -> g=g;
	this -> b=b;
}

Sphere::Sphere(){
	this -> CV=Vector3f(0,0,0);
	this -> rad=0;
	this -> r=0;
	this -> g=0;
	this -> b=0;
}

#endif