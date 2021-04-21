#include "model.h"

/*Model::Model(vector<Vector3f> vL,vector<Vector3f> vnL){
	vertList = vL;
	vecnormList = vnL;
}*/

void Model::readFile(const char* fileName)
{
	string line;
	ifstream inFile;
	inFile.open(fileName);

	float x= 0.0,y= 0.0,z= 0.0;
	float xN= 0.0,yN= 0.0,zN= 0.0;
	char tag;

	stringstream ss;
	while(getline(inFile,line)){
		std::istringstream iss(line);
		if(line!=""){
			if(line.at(0) == 'v' && line.at(1)=='n'){
				iss >> tag >> x >> y >> z;
				Vector3f tempVert(3);
				tempVert(0)=x; tempVert(1)=y; tempVert(2)=z;
				this -> vecnormList.push_back(tempVert);
			}
			else if(line.at(0) == 'v'){
				iss >> tag >> x >> y >> z;
				Vector3f tempVert(3);
				tempVert(0)=x; tempVert(1)=y; tempVert(2)=z;
				this -> vertList.push_back(tempVert);
			}
			if(line.at(0) == 'f'){
				replace(line.begin(),line.end(),'/',' ');
				std::istringstream iss(line);
				iss >> tag >> x >> xN >> y >> yN >> z >> zN;
				Vector3f tempVert(3);
				tempVert(0)=x; tempVert(1)=y; tempVert(2)=z;
				this -> faceList.push_back(tempVert);
				tempVert(0)=xN; tempVert(1)=yN; tempVert(2)=zN;
				this -> facenormList.push_back(tempVert);
			}
		}
	}
	inFile.close();
}


int main(int argc, char**argv)
{	
	Model Model;
	Model.readFile(argv[1]);
	return 0;
}