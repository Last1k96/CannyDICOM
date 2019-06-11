// Copyright (C) 2017, Dominik Wodniok
// This software may be modified and distributed under the terms
// of the BSD 3-Clause license.
// See the LICENSE.txt file for details.

/// \file   example.cpp
/// \author Dominik Wodniok
/// \date   2009

// std libs
#include <chrono>
#include <sstream>
#include <iostream>
#include <limits>

#include <vector>
#include "dualmc.h"
#include "DualMarchingCubes.h"
#include <algorithm>

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

DualMarchingCubes::DualMarchingCubes(std::vector<uint8_t> verts, int dimX, int dimY, int dimZ)
{
	////simplify
	//CGAL::random_simplify_point_set(verts, 0.20);

	//reconstruct
	dualmc::DualMC<uint8_t> builder;
	builder.build(&verts.front(), dimX, dimY, dimZ, 1.0f
		, false, false, vertices, quads);

	//normalize
	normalize();
	computeNormals();
}

Vertex DualMarchingCubes::normal(Vertex v1, Vertex v2, Vertex v3)
{
	const auto u = Vertex{ v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
	const auto v = Vertex{ v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };
	auto r = Vertex
	{
		u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x,
	};
	auto length = std::sqrt(r.x * r.x + r.y * r.y + r.z * r.z);
	return { r.x / length, r.y / length, r.z / length };
}
void DualMarchingCubes::computeNormals()
{
	normals.clear();
	normals.resize(quads.size() * 2);
#pragma omp parallel for
	for (int i = 0; i < quads.size(); i++)
	{
		normals[2 * i] =	 normal(vertices[quads[i].i0], vertices[quads[i].i1], vertices[quads[i].i2]);
		normals[2 * i + 1] = normal(vertices[quads[i].i2], vertices[quads[i].i3], vertices[quads[i].i1]);
	}
}

void DualMarchingCubes::normalize()
{
	auto minX = std::numeric_limits<decltype(this->vertices[0].x)>::max();
	auto maxX = std::numeric_limits<decltype(this->vertices[0].x)>::min();
	auto minY = std::numeric_limits<decltype(this->vertices[0].x)>::max();
	auto maxY = std::numeric_limits<decltype(this->vertices[0].x)>::min();
	auto minZ = std::numeric_limits<decltype(this->vertices[0].x)>::max();
	auto maxZ = std::numeric_limits<decltype(this->vertices[0].x)>::min();
	for (auto& v : vertices)
	{
		minX = std::min(minX, v.x);
		maxX = std::max(maxX, v.x);
		minY = std::min(minY, v.y);
		maxY = std::max(maxY, v.y);
		minZ = std::min(minZ, v.z);
		maxZ = std::max(maxZ, v.z);
	}

	auto const deltaX = (maxX + minX) / 2.0;
	auto const deltaY = (maxY + minY) / 2.0;
	auto const deltaZ = (maxZ + minZ) / 2.0;

	auto const normalizeX = (maxX - minX) / 2.0;
	auto const normalizeY = (maxY - minY) / 2.0;
	auto const normalizeZ = (maxZ - minZ) / 2.0;
	for (auto& v : vertices)
	{
		v.x = (v.x - deltaX) / normalizeX;
		v.y = (v.y - deltaY) / normalizeY;
		v.z = (v.z - deltaZ) / normalizeZ;
	}
}
