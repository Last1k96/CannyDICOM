#pragma once
// Copyright (C) 2017, Dominik Wodniok
// This software may be modified and distributed under the terms
// of the BSD 3-Clause license.
// See the LICENSE.txt file for details.

#include <string>
#include <vector>
#include "dualmc.h"

/// Example application for demonstrating the dual marching cubes builder.
class DualMarchingCubes
{
public:
	DualMarchingCubes(std::vector<uint8_t> vertices, int32_t dimX, int32_t dimY, int32_t dimZ);
private:

	/// Structure for the program options.
	struct AppOptions
	{
		int32_t dimX{0};
		int32_t dimY{0};
		int32_t dimZ{0};
		float isoValue{1.0f};
		bool generateCaffeine{false};
		bool generateQuadSoup{false};
		bool generateManifold{false};
	};
public:
	/// Compute the iso surface for the specified iso value. Optionally generate
	/// a quad soup.
	void computeSurface(float const iso, bool const generateSoup, bool const generateManifold);

	/// Write a Wavefront OBJ model for the extracted ISO surface.
	void writeOBJ(std::string const& fileName) const;

private:
	/// struct for volume data information
	struct Volume
	{
		// volume grid extents
		int32_t dimX;
		int32_t dimY;
		int32_t dimZ;
		/// volume data
		std::vector<uint8_t> data;
	};

	/// example volume
	Volume volume;

	std::vector<dualmc::Vertex> vertices;
	std::vector<dualmc::Quad> quads;
};
