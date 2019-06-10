#include "QGLMeshViewer.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <cstring>


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/refine.h>
#include <CGAL/Polygon_mesh_processing/fair.h>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Surface_mesh.h>

typedef Mesh::Vertex_index vertex_descriptor;
typedef Mesh::Face_index face_descriptor;
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel>  Polyhedron;
typedef Polyhedron::Vertex_handle   Vertex_handle;


QGLMeshViewer::QGLMeshViewer(QWidget* parent, std::vector<cv::Mat> const& images)
{
	auto const dimX = images[0].rows;
	auto const dimY = images[0].cols;
	auto const dimZ = images.size();
	
	auto voxels = std::vector<uint8_t>(dimX * dimY * dimZ);

#pragma omp parallel for 
	for (auto z = 0; z < dimZ; ++z)
	{
		auto& image = images[z];
		auto const xy = dimX * dimY;
		std::memcpy(voxels.data() + z * xy, image.data + z * xy, xy);
	}

	mc = DualMarchingCubes(std::move(voxels), dimX, dimY, dimZ);
}

void QGLMeshViewer::draw()
{

}
//quad 1 2 3 4
//==>
//triangle 1 2 3
//triangle 3 4 1
void QGLMeshViewer::init()
{
	mc.computeSurface(1.0f, false, false);
	typedef CGAL::Surface_mesh<Point> Mesh;
	Mesh m;
	auto vindex = std::vector<Mesh::Vertex_index>{};
	vindex.reserve(mc.vertices.size());
	for (auto& v : mc.vertices)
	{
		auto index = m.add_vertex({ v.x, v.y, v.z });
		vindex.push_back(index);
	}

	for (auto const& q : mc.quads)
	{
		auto const& p1 = vindex[q.i0];
		auto const& p2 = vindex[q.i1];
		auto const& p3 = vindex[q.i2];
		auto const& p4 = vindex[q.i3];
		m.add_face(p1, p2, p3);
		m.add_face(p3, p4, p1);
	}
}
