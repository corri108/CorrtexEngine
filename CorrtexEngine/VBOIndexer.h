#pragma once
#include "glm\ext.hpp"
#include <vector>
#include <map>
using namespace glm;

//make comparing positions, uvs, and normals easier by packing them into a struct
struct PackedVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
	};
};

//an indexer that will correctly index all of the verticies in a model to make drawing the model much faster. used in correlation
//with index buffer objects that OpenGL provides creation methods for.
class VBOIndexer
{
public:
	VBOIndexer();
	~VBOIndexer();
	//helper funcs 
	bool IsNear(float v1, float v2);
	bool GetSimilarVertexIndex(glm::vec3 & in_vertex,glm::vec2 & in_uv,glm::vec3 & in_normal,std::vector<glm::vec3> & out_vertices,std::vector<glm::vec2> & out_uvs,std::vector<glm::vec3> & out_normals,unsigned short & result);
	void IndexVBOSlow(std::vector<glm::vec3> & in_vertices,std::vector<glm::vec2> & in_uvs,std::vector<glm::vec3> & in_normals,std::vector<unsigned short> & out_indices,std::vector<glm::vec3> & out_vertices,std::vector<glm::vec2> & out_uvs,std::vector<glm::vec3> & out_normals);
	bool GetSimilarVertexIndexFast(PackedVertex & packed, std::map<PackedVertex, unsigned short> & VertexToOutIndex, unsigned short & result);
	
	//indexing standard position, uvs, and normals
	void IndexVBO(
		std::vector<glm::vec3> & in_vertices,
		std::vector<glm::vec2> & in_uvs,
		std::vector<glm::vec3> & in_normals,

		std::vector<unsigned short> & out_indices,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
	);
	//indexing with extra tangents and bitangents (usually for lighting calculations)
	void IndexVBO_TBN(
		std::vector<glm::vec3> & in_vertices,
		std::vector<glm::vec2> & in_uvs,
		std::vector<glm::vec3> & in_normals,
		std::vector<glm::vec3> & in_tangents,
		std::vector<glm::vec3> & in_bitangents,

		std::vector<unsigned short> & out_indices,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals,
		std::vector<glm::vec3> & out_tangents,
		std::vector<glm::vec3> & out_bitangents
	);
};

