// Copyright (C) 2017, Dominik Wodniok
// This software may be modified and distributed under the terms
// of the BSD 3-Clause license.
// See the LICENSE.txt file for details.

/// \file   DualMarchingCubes.cpp
/// \author Dominik Wodniok
/// \date   2009

// C libs
#include <cmath>
#include <cstdlib>
#include <cstring>

// std libs
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>

// stl
#include <vector>

// dual mc builder
#include "dualmc.h"

// main include
#include "DualMarchingCubes.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

DualMarchingCubes::DualMarchingCubes(std::vector<uint8_t> vertices, int32_t dimX, int32_t dimY, int32_t dimZ)
	: volume{dimX, dimY, dimZ, std::move(vertices)}
{
	if (dimX * dimY * dimZ != this->vertices.size())
		throw std::runtime_error("Dimentions are wrong");
}

void DualMarchingCubes::computeSurface(float const iso, bool const generateSoup, bool const generateManifold)
{
	high_resolution_clock::time_point const startTime = high_resolution_clock::now();

	// construct iso surface
	dualmc::DualMC<uint8_t> builder;
	builder.build(&volume.data.front(), volume.dimX, volume.dimY, volume.dimZ,
	              iso * std::numeric_limits<uint8_t>::max(), generateManifold, generateSoup, vertices, quads);

	high_resolution_clock::time_point const endTime = high_resolution_clock::now();
	duration<double> const diffTime = duration_cast<duration<double>>(endTime - startTime);
	double const extractionTime = diffTime.count();

	std::cout << "Extraction time: " << extractionTime << "s" << std::endl;
}

//------------------------------------------------------------------------------

void DualMarchingCubes::writeOBJ(std::string const& fileName) const
{
	std::cout << "Writing OBJ file" << std::endl;
	// check if we actually have an ISO surface
	if (vertices.size() == 0 || quads.size() == 0)
	{
		std::cout << "No ISO surface generated. Skipping OBJ generation." << std::endl;
		return;
	}

	// open output file
	std::ofstream file(fileName);
	if (!file)
	{
		std::cout << "Error opening output file" << std::endl;
		return;
	}

	std::cout << "Generating OBJ mesh with " << vertices.size() << " vertices and "
		<< quads.size() << " quads" << std::endl;

	// write vertices
	for (auto const& v : vertices)
	{
		file << "v " << v.x << ' ' << v.y << ' ' << v.z << '\n';
	}

	// write quad indices
	for (auto const& q : quads)
	{
		file << "f " << (q.i0 + 1) << ' ' << (q.i1 + 1) << ' ' << (q.i2 + 1) << ' ' << (q.i3 + 1) << '\n';
	}

	file.close();
}
