#include "Mesh.h"

void Mesh::parseVertex(std::stringstream & sin, Mesh & geo)
{
	EngineMath::vec3 v = EngineMath::vec3(0, 0, 0);
	sin >> v.x >> v.y >> v.z;
	geo.vertexData.push_back(v);
}

void Mesh::parseTexcoord(std::stringstream & sin, Mesh & geo)
{
	EngineMath::vec2 t = EngineMath::vec2(0, 0);
	sin >> t.x >> t.y;
	geo.texcoordData.push_back(t);
}

void Mesh::parseNormal(std::stringstream & sin, Mesh & geo)
{
	EngineMath::vec3 n = EngineMath::vec3(0, 0, 0);
	sin >> n.x >> n.y >> n.z;
	geo.normalData.push_back(n);
}

void Mesh::parseFace(std::stringstream & sin, Mesh & geo)
{
	std::string token;
	for (int i = 0; i < 3; i++) {
		std::getline(sin, token, '/');
		if (token.size() > 0) geo.vertexIdx.push_back(std::stoi(token));
		std::getline(sin, token, '/');
		if (token.size() > 0) geo.texcoordIdx.push_back(std::stoi(token));
		std::getline(sin, token, ' ');
		if (token.size() > 0) geo.normalIdx.push_back(std::stoi(token));
	}
}

void Mesh::parseLine(std::stringstream & sin, Mesh & geo)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin, geo);
	else if (s.compare("vt") == 0) parseTexcoord(sin, geo);
	else if (s.compare("vn") == 0) parseNormal(sin, geo);
	else if (s.compare("f") == 0) parseFace(sin, geo);
}

void Mesh::loadMeshData(std::string & filename, Mesh & geo)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) {
		parseLine(std::stringstream(line), geo);
	}
	geo.TexcoordsLoaded = (geo.texcoordIdx.size() > 0);
	geo.NormalsLoaded = (geo.normalIdx.size() > 0);
}

void Mesh::processMeshData(Mesh & geo)
{
	for (unsigned int i = 0; i < geo.vertexIdx.size(); i++) {
		unsigned int vi = geo.vertexIdx[i];
		EngineMath::vec3 v = geo.vertexData[vi - 1];
		geo.Vertices.push_back(v);
		if (geo.TexcoordsLoaded) {
			unsigned int ti = geo.texcoordIdx[i];
			EngineMath::vec2 t = geo.texcoordData[ti - 1];
			geo.Texcoords.push_back(t);
		}
		if (geo.NormalsLoaded) {
			unsigned int ni = geo.normalIdx[i];
			EngineMath::vec3 n = geo.normalData[ni - 1];
			geo.Normals.push_back(n);
		}
	}
}

void Mesh::freeMeshData(Mesh & geo)
{
	geo.vertexData.clear();
	geo.texcoordData.clear();
	geo.normalData.clear();
	geo.vertexIdx.clear();
	geo.texcoordIdx.clear();
	geo.normalIdx.clear();
}

Mesh::Mesh Mesh::createMesh(std::string & filename)
{
	Mesh geo;
	loadMeshData(filename, geo);
	processMeshData(geo);
	freeMeshData(geo);

	return geo;
}
