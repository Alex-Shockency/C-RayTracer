#ifndef light_H
#define light_H

#include "eigen3/Eigen/Dense"

using namespace Eigen;
using namespace std;

class Light
{
public:
	Light(Vector3f P,float w,Vector3f E);
	Vector3f P;
	float w;
	Vector3f E;
};

Light::Light(Vector3f P,float w,Vector3f E){
	this -> P=P;
	this -> w=w;
	this -> E=E;
}

#endif