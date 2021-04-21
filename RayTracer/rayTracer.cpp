#include "rayTracer.h"
#include "model.h"

void rayTracer::readModel(const char* fileName)
{
	string line;
	ifstream inFile;
	inFile.open(fileName);

	float x= 0.0,y= 0.0,z= 0.0;
	float xN= 0.0,yN= 0.0,zN= 0.0;
	char tag;
	string mtlFile;
	vector<Vector3f> vertList;
	vector<Vector3f> vecnormList;
	vector<Vector4f> faceList;
	vector<Material> matList;
	vector<int> facenormList;
	int matIndex=-1;
	

	stringstream ss;
	while(getline(inFile,line)){
		std::istringstream iss(line);
		if(line!=""){
			if(line.at(0) == 'v' && line.at(1)=='n'){
				iss >> tag >> tag >> x >> y >> z;
				Vector3f tempVert(3);
				tempVert(0)=x; tempVert(1)=y; tempVert(2)=z;
				vecnormList.push_back(tempVert);
			}
			else if(line.at(0) == 'v'){
				iss >> tag >> x >> y >> z;
				Vector3f tempVert(3);
				tempVert(0)=x+mtranX; tempVert(1)=y+mtranY; tempVert(2)=z+mtranZ;
				vertList.push_back(tempVert);
			}
			if(line.at(0) == 'u'){
				matIndex++;
			}
			if(line.at(0) == 'f'){
				replace(line.begin(),line.end(),'/',' ');
				std::istringstream iss(line);
				iss >> tag >> x >> xN >> y >> yN >> z >> zN;
				Vector4f tempVert(4);
				tempVert(0)=x-1; tempVert(1)=y-1; tempVert(2)=z-1; tempVert(3)=matIndex;
				faceList.push_back(tempVert);
				tempVert(0)=xN; tempVert(1)=yN; tempVert(2)=zN;
				facenormList.push_back(xN-1);
			}

			else if(line.at(0) == 'm'){
				iss >> mtlFile >> mtlFile;
			}
		}
	}
	matList = readMtl(mtlFile.c_str());
	Model model(vertList,vecnormList,faceList,facenormList,matList);
	this -> modelList.push_back(model);
	inFile.close();
}
vector<Material> rayTracer::readMtl(const char* fileName)
{
	string line;
	ifstream inFile;
	inFile.open(fileName);
	stringstream ss;
	string tag;
	Vector3f Ka;
	Vector3f Kd;
	Vector3f Ks;
	vector<Material> matList;
	float x= 0.0,y= 0.0,z= 0.0;
	
	while(getline(inFile,line)){
		std::istringstream iss(line);
		if(line!=""){
			if(line.find("newmtl") != string::npos){
				iss >> tag >> tag;
			}
			if(line.at(0)=='K'){
				if(line.at(1)=='a'){
					iss >> tag >> x >> y >> z;
					//cout << x << y << z << endl;
					Ka(0)=x; Ka(1)=y; Ka(2)=z;
				}
				if(line.at(1)=='d'){
					iss >> tag >> x >> y >> z;
					//cout << x << y << z << endl;
					Kd(0)=x; Kd(1)=y; Kd(2)=z;
				}
				if(line.at(1)=='s'){
					iss >> tag >> x >> y >> z;
					//cout << x << y << z << endl;
					Ks(0)=x; Ks(1)=y; Ks(2)=z;
				}

			}
			if(line.at(0)=='i'){
				matList.push_back(Material(Ka,Kd,Ks));
			}
		}
	}
	inFile.close();
	return matList;
}

void rayTracer::buildScene(const char* fileName)
{
	vector<VectorXf> tempVertList;

	Vector3f EV;
	Vector3f LV;
	Vector3f UP;
	Vector3f WV;
	Vector3f UV;
	Vector3f VV;
	float bound[4];
	float near = 0;
	float far = 0;
	float umin=0,umax=0,vmax=0,vmin=0;
	int width=0,height =0;
	string modelFile;

	string line;
	ifstream inFile;
	inFile.open(fileName);
	while(!inFile.eof()){
		getline(inFile,line); 
		stringstream ss;
		if(line.find("eye") != string::npos){
			int i=0;
			ss << line;
			while(getline(ss,line,' ')){
				if(line != "eye"){
					stringstream(line)>>EV(i);
					i++;
				}
			}
			this -> EV = EV;
		}
		else if(line.find("look") != string::npos){
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "look"){
					stringstream(line)>>LV(i);
					i++;
				}
			}
			this -> LV = LV;
		}
		else if(line.find("up") != string::npos){
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "up"){
					stringstream(line)>>UP(i);
					i++;
				}
			}
			this -> UP = UP;
		}
		else if(line.find("bounds") != string::npos){
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "bounds"){
					stringstream(line)>>bound[i];
					i++;
				}
			}
			this -> umin = bound[0];
			this -> vmax = bound[1];
			this -> vmin = bound[2];
			this -> umax = bound[3];
		}
		else if(line.find("res") != string::npos){
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "res"){
					if(i==0)
						stringstream(line)>>width;
					else
						stringstream(line)>>height;
					i++;
				}
			}
			this -> width =width;
			this -> height =height;
		}
		else if(line.find("model") != string::npos){
			float mod[7];
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "model" && i<7){
					stringstream(line)>>mod[i];
					i++;
				}
				else if(line != "model"){
					stringstream(line)>>modelFile;
				}
			}
			this -> mtranX=mod[0];
			this -> mtranY=mod[1];
			this -> mtranZ=mod[2];
			readModel(modelFile.c_str());
		}
		else if(line.find("sphere") != string::npos){
			float sp[7];
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "sphere" && i<7){
					stringstream(line)>>sp[i];
					i++;
				}
			}
			Vector3f CV(sp[0],sp[1],sp[2]);
			Sphere sphere(CV,sp[3],sp[4],sp[5],sp[6]);
			this -> sphereList.push_back(sphere);
		}
		else if(line.find("ambient") != string::npos){
			float ambi[3];
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "ambient" && i<3){
					stringstream(line)>>ambi[i];
					i++;
				}
			}
			Vector3f tempVec(ambi[0],ambi[1],ambi[2]);
			this -> ambi = tempVec;
		}
		else if(line.find("light") != string::npos){
			float lt[7];
			ss << line;
			int i=0;
			while(getline(ss,line,' ')){
				if(line != "light" && i<7){
					stringstream(line)>>lt[i];
					i++;
				}
			}
			Vector3f P(lt[0],lt[1],lt[2]);
			Vector3f E(lt[4],lt[5],lt[6]);
			Light light(P,lt[3],E);
			this -> lightList.push_back(light);
		}
		else if(line.find("d") != string::npos){
			ss << line;
			while(getline(ss,line,' ')){
				if(line != "d"){
					stringstream(line)>>near;
				}
			}
			this -> near= -near;
		}
		
	}
	//calculate WV
	WV=EV-LV;
	if(WV.norm()!=0)
		WV=WV/WV.norm();
	this -> WV= WV;
	//============
	//calculate UV
	UV = UP.cross(WV);
	if(UV.norm()!=0)
		UV=UV/UV.norm();
	this -> UV = UV;
	//============
	//calculate VV
	VV = WV.cross(UV);
	this -> VV = VV;
	//============
	inFile.close();
}

bool rayTracer::polyCast(Ray &ray)
{
	bool hit=false;
	for(int i=0;i<modelList.size();i++){
		for(int j=0;j<modelList[i].faceList.size();j++){
			float tval = -1;
			Matrix3f MM;
			Vector3f result;

			Vector3f Av = getVert(modelList[i],j,0);
			Vector3f Bv = getVert(modelList[i],j,1);
			Vector3f Cv = getVert(modelList[i],j,2);
			Vector3f Yv=(Av-ray.L);

			MM.col(0)=Av-Bv;
			MM.col(1)=Av-Cv;
			MM.col(2)=ray.D;

			result = MM.inverse()*Yv;

			float beta=result(0);
			float gamma=result(1);
			tval=result(2);
			if(beta >= 0 && gamma >=0 && beta+gamma<=1 && tval>=0){
				if(tval < ray.best_t && tval > 0.00001){
					hit =true;
					ray.best_face=j;
					ray.best_model=modelList[i];
					ray.best_t=tval;
					ray.best_pt=ray.L + tval * ray.D;	
				}
			}
		}
	}
	if(hit){
		ray.isSphere=false;
		return true;
	}
	return false;
}

bool rayTracer::sphereCast(Ray &ray)
{
	bool hit=false;
	for(int k=0;k<sphereList.size();k++){
		Vector3f TV = sphereList[k].CV - ray.L;
		float V = TV.dot(ray.D);
		float csq = TV.dot(TV);
		float disc = (sphereList[k].rad*sphereList[k].rad) - (csq - V*V);
		float tval = -1;
		if(disc > 0)
		{
			hit=true;
			tval = V - sqrt(disc);
			if(tval < ray.best_t && tval > 0.00001){
				ray.best_t=tval;
				ray.best_sphere = sphereList[k];
				ray.best_pt = ray.L + tval * ray.D;
			}
			
		}
	}
	if(hit){
		ray.isSphere=true;
		return true;
	}
	return false;
}

Vector3f rayTracer::rayTrace(Ray &ray,Vector3f &accum,Vector3f refatt, int level){
	bool hitS=false;
	bool hitP=false;
	if(sphereList.size()!=0){
		hitS=sphereCast(ray);
	}
	if(modelList.size()!=0){
		hitP=polyCast(ray);
	}
	if(hitS||hitP){
		Vector3f ka;
		Vector3f kd;
		Vector3f ks;
		Vector3f N;
		if(ray.isSphere){
			N = ray.best_pt - ray.best_sphere.CV;
			N = N/N.norm();
			ka(0) = ray.best_sphere.r;
			ka(1) = ray.best_sphere.g;
			ka(2) = ray.best_sphere.b;
			kd = ka;
			ks = ka;
		}
		else{
			N=getNormal(ray.best_model,ray.best_face);
			N = N/N.norm();
			ka=ray.best_model.matList[ray.best_model.faceList[ray.best_face](3)].ka;
			kd=ray.best_model.matList[ray.best_model.faceList[ray.best_face](3)].kd;
			ks=ray.best_model.matList[ray.best_model.faceList[ray.best_face](3)].ks;
		}
		float kr = .8;
		Vector3f color;
		color(0) = ambi(0) * ka(0);
		color(1) = ambi(1) * ka(1);
		color(2) = ambi(2) * ka(2);
		for(int lt=0; lt < lightList.size();lt++){
			Vector3f toL = lightList[lt].P - ray.best_pt;
			toL=toL/toL.norm();
			float NdotL = N.dot(toL);
			if(NdotL > 0.0){
				Vector3f tempVec(kd(0)*lightList[lt].E(0) * NdotL,kd(1)*lightList[lt].E(1) * NdotL,kd(2)*lightList[lt].E(2) * NdotL);
				color(0) += tempVec(0);
				color(1) += tempVec(1);
				color(2) += tempVec(2);
				Vector3f toC = ray.L - ray.best_pt;
				toC = toC/toC.norm();
				Vector3f spR = (2*NdotL*N) - toL;
				spR = spR/spR.norm();
				color(0) += (ks(0)*lightList[lt].E(0)) * pow((toC.dot(spR)),16);
				color(1) += (ks(0)*lightList[lt].E(1)) * pow((toC.dot(spR)),16);
				color(2) += (ks(0)*lightList[lt].E(2)) * pow((toC.dot(spR)),16);
			}

		}
		for(int ac=0;ac<3;ac++){
			accum(ac) += (refatt(ac) * color(ac));
		}
		if(level >0){
			Vector3f Uinv= -1 * ray.D;
			Vector3f refR= (2*N.dot(Uinv)*N) - Uinv;
			refR= refR / refR.norm();
			ray = Ray(ray.best_pt,refR);
			rayTrace(ray,accum,kr*refatt,level-1);
		}
	}
	return accum;
}


void rayTracer::writeImage(const char* fileName)
{
	ofstream outFile;
	outFile.open(fileName);
	outFile << "P3" << endl;
	outFile << width << " " << height << " " << "255" << endl;
	vector<Vector3f> pixelVals;
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			float px= (float)j/(width-1)*(umax-umin)+umin;
			float py= (float)i/(height-1)*(vmax-vmin)+vmin;
			Vector3f rayStart = EV + (near * WV) + (px * UV) + (py * VV);
			Vector3f rayDirect = rayStart - EV;
			rayDirect = rayDirect / rayDirect.norm();
			Ray ray(rayStart,rayDirect);
			Vector3f rgb(0,0,0);
			Vector3f refatt(1,1,1);
			Vector3f tempVec = rayTrace(ray,rgb,refatt,6);
			int r = max((float)0, min((float)255,round((float)255*tempVec(0))));
			int g = max((float)0, min((float)255,round((float)255*tempVec(1)))); 
			int b = max((float)0, min((float)255,round((float)255*tempVec(2))));
			outFile << r <<" "<< g << " " << b << " ";
		}
		outFile << endl;
	}
	outFile.close();
}

void rayTracer::writeImage(float tvals[],const char* fileName)
{
	ofstream outFile;
	outFile.open(fileName);
	outFile << "P3" << endl;
	outFile << width << " " << height << " " << "255" << endl;
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(tvals[getIndex(j,i)]==-1){
				outFile << "239 239 239 ";
			}
			else{
				float ratio = 2 * (tvals[getIndex(j,i)] - tmin) / (tmax - tmin); 
				int r = max((float)0, 255 * (1 - ratio));
				int b = max((float)0, 255 * (ratio - 1)); 
				int g = 255 - b - r; 
				outFile << r <<" "<< g << " " << b << " ";
			}
		}
		outFile << endl;
	}
	outFile.close();
}

int main(int argc, char**argv)
{
	rayTracer rayTracer;
	rayTracer.outFile=argv[2];
	rayTracer.buildScene(argv[1]);
	rayTracer.writeImage(rayTracer.outFile);
	return 0;
}
