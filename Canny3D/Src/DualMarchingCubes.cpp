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
#include "MeshReconstruction.h"
#include <algorithm>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Polyhedron_3.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

#include <CGAL/Simple_cartesian.h>
#include <CGAL/random_simplify_point_set.h>
#include <vector>
#include <iostream>
#include <CGAL/Scale_space_surface_reconstruction_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/read_off_points.h>
#include <CGAL/Timer.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel     Kernel;
typedef CGAL::Scale_space_surface_reconstruction_3<Kernel>    Reconstruction;
typedef Reconstruction::Facet_const_iterator                   Facet_iterator;
typedef Kernel::Point_3 Point;
typedef CGAL::Surface_mesh<Point> Mesh;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
// Concurrency
#ifdef CGAL_LINKED_WITH_TBB
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif

DualMarchingCubes::DualMarchingCubes(std::vector<uint8_t> voxels, int32_t dimX, int32_t dimY, int32_t dimZ)
	: volume{dimX, dimY, dimZ, std::move(voxels)}
{
	if (int64_t(dimX) * dimY * dimZ != this->volume.data.size())
	{
		throw std::runtime_error("Dimentions are wrong");
	}
}

void DualMarchingCubes::computeSurface(uint8_t const iso, bool const generateSoup, bool const generateManifold)
{
	// construct iso surface

	auto count = 0;
	for (auto z = 0; z < volume.dimZ; ++z)
	{
		auto zz = z * volume.dimY * volume.dimX;
		for (auto y = 0; y < volume.dimY; ++y)
		{
			auto yy = y * volume.dimX;
			for (auto x = 0; x < volume.dimX; ++x)
			{
				if (volume.data[zz + yy + x] != 0) count++;
			}
		}
	}
	dualmc::DualMC<uint8_t> builder;
	builder.build(&volume.data.front(), volume.dimX, volume.dimY, volume.dimZ, iso
		, generateManifold, generateSoup, vertices, quads);
	auto x = getSurface();
}

Polyhedron DualMarchingCubes::getSurface()
{
	// WLOP optimization
	std::vector<Point> output;
	//parameters
	CGAL::random_simplify_point_set(vertices, 30.0);
	Reconstruction reconstruct(vertices.begin(), vertices.end());
	reconstruct.increase_scale(4);
	reconstruct.reconstruct_surface();
	Polyhedron p;
	std::stringstream buf{};
	buf << reconstruct;
	buf >> p;
	return p;
}

//Vertex DualMarchingCubes::normal(Vertex v1, Vertex v2, Vertex v3)
//{
//	const auto u = Vertex{ v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
//	const auto v = Vertex{ v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };
//	auto r = Vertex
//	{
//		u.y * v.z - u.z * v.y,
//		u.z * v.x - u.x * v.z,
//		u.x * v.y - u.y * v.x,
//	};
//	auto length = std::sqrt(r.x * r.x + r.y * r.y + r.z * r.z);
//	return { r.x / length, r.y / length, r.z / length };
//}
//void DualMarchingCubes::computeNormals()
//{
//	normals.clear();
//	normals.resize(quads.size());
//#pragma omp parallel for
//	for (int i = 0; i < quads.size(); i++)
//	{
//		normals[i] = normal(vertices[quads[i].i0], vertices[quads[i].i1], vertices[quads[i].i2]);
//	}
//}

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
//
//std::stringstream DualMarchingCubes::writeToStream() const
//{
//	// open output file
//	std::stringstream file{};
//	
//	for (auto const& v : vertices)
//	{
//		file << "v " << v.x << ' ' << v.y << ' ' << v.z << '\n';
//	}
//
//	// write quad indices
//	for (auto const& q : quads)
//	{
//		file << "f " << (q.i0 + 1) << ' ' << (q.i1 + 1) << ' ' << (q.i2 + 1) << ' ' << (q.i3 + 1) << '\n';
//	}
//
//	return file;
//}
