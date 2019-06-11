#pragma once
// Copyright (C) 2017, Dominik Wodniok
// This software may be modified and distributed under the terms
// of the BSD 3-Clause license.
// See the LICENSE.txt file for details.
#include "dualmc.h"
#include <string>
#include <vector>
#include <CGAL/random_simplify_point_set.h>
using namespace dualmc;

/// Example application for demonstrating the dual marching cubes builder.
class DualMarchingCubes
{

public:
	DualMarchingCubes() = default;
	DualMarchingCubes(DualMarchingCubes const&) = default;
	DualMarchingCubes(DualMarchingCubes &&) = default;
	DualMarchingCubes& operator=(DualMarchingCubes const&) = default;
	DualMarchingCubes& operator=(DualMarchingCubes &&) = default;
	void normalize();
	Vertex normal(Vertex v1, Vertex v2, Vertex v3);
	void computeNormals();
	DualMarchingCubes(std::vector<uint8_t> verts, int dimX, int dimY, int dimZ);
	

	std::vector<Vertex> vertices;
	std::vector<Quad> quads;
	std::vector<Vertex> normals;
};