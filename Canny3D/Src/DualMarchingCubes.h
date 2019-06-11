#pragma once
// Copyright (C) 2017, Dominik Wodniok
// This software may be modified and distributed under the terms
// of the BSD 3-Clause license.
// See the LICENSE.txt file for details.

#include <string>
#include <vector>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/random_simplify_point_set.h>
#include <vector>
#include <CGAL/Scale_space_surface_reconstruction_3.h>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h> 
#include <CGAL/Polygon_mesh_processing/compute_normal.h> 
typedef CGAL::Exact_predicates_inexact_constructions_kernel     Kernel;
typedef CGAL::Scale_space_surface_reconstruction_3<Kernel>    Reconstruction;
typedef Reconstruction::Facet_const_iterator                   Facet_iterator;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef CGAL::Surface_mesh<Point> Mesh;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<Polyhedron>::face_descriptor   face_descriptor;
// Concurrency
#ifdef CGAL_LINKED_WITH_TBB
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif

/// Example application for demonstrating the dual marching cubes builder.
class MeshReconstruction
{
	std::map<face_descriptor, Vector> fnormals;
	std::map<vertex_descriptor, Vector> vnormals;
public:
	MeshReconstruction() = default;
	MeshReconstruction(MeshReconstruction const&) = default;
	MeshReconstruction(MeshReconstruction &&) = default;
	MeshReconstruction& operator=(MeshReconstruction const&) = default;
	MeshReconstruction& operator=(MeshReconstruction &&) = default;

	MeshReconstruction(std::vector<Point> vertices, int dimX, int dimY, int dimZ)
	: dims{dimX, dimY, dimZ}, verts(std::move(vertices))
	{
		//simplify
		CGAL::random_simplify_point_set(verts, 20.0);
		//reconstruct
		Reconstruction reconstruct(vertices.begin(), vertices.end());
		reconstruct.increase_scale(4);
		reconstruct.reconstruct_surface();
		std::stringstream buf{};
		buf << reconstruct;
		buf >> mesh;
		//normals
		Polyhedron::Vertex_iterator v;
		Polyhedron::Facet_iterator f;
		Polyhedron::Edge_iterator eit;
		Polyhedron::Halfedge_handle h_handle;
		double x, y, z;

		CGAL::Polygon_mesh_processing::compute_normals(P,
			boost::make_assoc_property_map(vnormals),
			boost::make_assoc_property_map(fnormals));

		glBegin(GL_TRIANGLES);
		for (f = P.facets_begin(); f != P.facets_end(); f++) {
			xx = fnormals[f].x() / sqrt((fnormals[f].x() * fnormals[f].x()) +
				(fnormals[f].y() * fnormals[f].y()) + (fnormals[f].z() * fnormals[f].z()));
			yy = fnormals[f].y() / sqrt((fnormals[f].x() * fnormals[f].x()) +
				(fnormals[f].y() * fnormals[f].y()) + (fnormals[f].z() * fnormals[f].z()));
			zz = fnormals[f].z() / sqrt((fnormals[f].x() * fnormals[f].x()) +
				(fnormals[f].y() * fnormals[f].y()) + (fnormals[f].z() * fnormals[f].z()));
			glNormal3f(xx, yy, zz);
			gl_draw_facet(f);
		}
		glEnd();
	}

	Point dims;
	std::vector<Point> verts;
	Polyhedron mesh;
};