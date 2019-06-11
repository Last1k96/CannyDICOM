#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/random_simplify_point_set.h>
#include <vector>
#include <CGAL/Scale_space_surface_reconstruction_3.h>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_mesh_processing/compute_normal.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Scale_space_surface_reconstruction_3<Kernel> Reconstruction;
typedef Reconstruction::Facet_const_iterator Facet_iterator;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef CGAL::Surface_mesh<Point> Mesh;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;
// Concurrency
#ifdef CGAL_LINKED_WITH_TBB
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif

#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/array.h>
#include <CGAL/disable_warnings.h>
typedef CGAL::cpp11::array<std::size_t, 3> Facet;
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3  Point_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;

struct Construct {
	Mesh& mesh;
	template < typename PointIterator>
	Construct(Mesh& mesh, PointIterator b, PointIterator e)
		: mesh(mesh)
	{
		for (; b != e; ++b) {
			boost::graph_traits<Mesh>::vertex_descriptor v;
			v = add_vertex(mesh);
			mesh.point(v) = *b;
		}
	}
	Construct& operator=(const Facet f)
	{
		typedef boost::graph_traits<Mesh>::vertex_descriptor vertex_descriptor;
		typedef boost::graph_traits<Mesh>::vertices_size_type size_type;
		mesh.add_face(vertex_descriptor(static_cast<size_type>(f[0])),
			vertex_descriptor(static_cast<size_type>(f[1])),
			vertex_descriptor(static_cast<size_type>(f[2])));
		return *this;
	}
	Construct&
		operator*() { return *this; }
	Construct&
		operator++() { return *this; }
	Construct
		operator++(int) { return *this; }
};

/// Example application for demonstrating the dual marching cubes builder.
class MeshReconstruction
{
public:
	MeshReconstruction() = default;
	MeshReconstruction(MeshReconstruction const&) = default;
	MeshReconstruction(MeshReconstruction&&) = default;
	MeshReconstruction& operator=(MeshReconstruction const&) = default;
	MeshReconstruction& operator=(MeshReconstruction&&) = default;
	~MeshReconstruction() = default;

	MeshReconstruction(std::vector<Point> vertices, int dimX, int dimY, int dimZ)
		: dims{dimX, dimY, dimZ}, verts(std::move(vertices))
	{
		//simplify
		//CGAL::random_simplify_point_set(verts, 30.0);
		//reconstruct
		Mesh m;
		Construct construct(m, verts.begin(), verts.end());
		CGAL::advancing_front_surface_reconstruction(verts.begin(),
			verts.end(),
			construct);
		CGAL::copy_face_graph(m, poly);
		return;
		Reconstruction reconstruct(verts.begin(), verts.end());
		reconstruct.increase_scale(1);
		reconstruct.reconstruct_surface();
		
		std::stringstream buf{};
		buf << reconstruct;
		buf >> poly;

		CGAL::Polygon_mesh_processing::compute_normals(poly,
			boost::make_assoc_property_map(vnormals),
			boost::make_assoc_property_map(fnormals));
	}

	std::map<face_descriptor, Vector> fnormals;
	std::map<vertex_descriptor, Vector> vnormals;
	Point dims;
	std::vector<Point> verts;
	Polyhedron poly{};
};
