#ifndef __MESH_H__
#define __MESH_H__
#pragma once
#include "../Math/Math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace Mesh {

	struct Mesh {
		std::vector <EngineMath::vec3> Vertices, vertexData;
		std::vector <EngineMath::vec2> Texcoords, texcoordData;
		std::vector <EngineMath::vec3> Normals, normalData;

		std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;
		GLuint VaoId;
		GLuint VboId[2];
		GLuint VboVertices, VboTexcoords, VboNormals;

		bool TexcoordsLoaded, NormalsLoaded;
	};

	void parseVertex(std::stringstream& sin, Mesh& geo);

	void parseTexcoord(std::stringstream& sin, Mesh& geo);

	void parseNormal(std::stringstream& sin, Mesh& geo);

	void parseFace(std::stringstream& sin, Mesh& geo);

	void parseLine(std::stringstream& sin, Mesh& geo);

	void loadMeshData(std::string& filename, Mesh& geo);

	void processMeshData(Mesh& geo);

	void freeMeshData(Mesh& geo);

	Mesh createMesh(std::string& filename);

}


#endif