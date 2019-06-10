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

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

DualMarchingCubes::DualMarchingCubes(std::vector<uint8_t> vertices, int32_t dimX, int32_t dimY, int32_t dimZ)
	: volume{dimX, dimY, dimZ, std::move(vertices)}
{
	if (int64_t(dimX) * dimY * dimZ != vertices.size())
	{
		throw std::runtime_error("Dimentions are wrong");
	}
}

void DualMarchingCubes::computeSurface(float const iso, bool const generateSoup, bool const generateManifold)
{
	auto const startTime = high_resolution_clock::now();

	// construct iso surface
	dualmc::DualMC<uint8_t> builder;
	builder.build(&volume.data.front(), volume.dimX, volume.dimY, volume.dimZ,
		iso * std::numeric_limits<uint8_t>::max(), generateManifold, generateSoup, vertices, quads);

	auto const endTime = high_resolution_clock::now();
	auto const diffTime = duration_cast<duration<double>>(endTime - startTime);
	auto const extractionTime = diffTime.count();

	std::cout << "Extraction time: " << extractionTime << "s" << std::endl;
}

std::stringstream DualMarchingCubes::writeToStream() const
{
	// open output file
	std::stringstream file{};
	
	for (auto const& v : vertices)
	{
		file << "v " << v.x << ' ' << v.y << ' ' << v.z << '\n';
	}

	// write quad indices
	for (auto const& q : quads)
	{
		file << "f " << (q.i0 + 1) << ' ' << (q.i1 + 1) << ' ' << (q.i2 + 1) << ' ' << (q.i3 + 1) << '\n';
	}

	return file;
}
