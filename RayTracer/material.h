#ifndef material_H
#define material_H

#include "eigen3/Eigen/Dense"

using namespace Eigen;
using namespace std;

class Material
{
public:
	Material(Vector3f ka,Vector3f kd,Vector3f ks);
	Material();
	Vector3f ka;
	Vector3f kd;
	Vector3f ks;
};

Material::Material(){

}

Material::Material(Vector3f ka,Vector3f kd,Vector3f ks){
	this -> ka= ka;
	this -> kd= kd;
	this -> ks= ks;
}

#endif