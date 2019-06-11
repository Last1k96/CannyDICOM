#include "QGLMeshViewer.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <cstring>

QGLMeshViewer::QGLMeshViewer(QWidget* parent, std::vector<cv::Mat> const& images)
{
	auto const dimX = images[0].rows;
	auto const dimY = images[0].cols / 2; // т.к. две склеенные картинки
	auto const dimZ = images.size();

	auto vertex = std::vector<Point>();
	vertex.reserve(dimX * dimY * dimZ);
	for (auto z = 0; z < dimZ; ++z)
	{
		auto& image = images[z];
		for (auto y = 0; y < dimY; ++y)
		{
			for (auto x = 0; x < dimX; ++x)
			{
				if (image.at<uint8_t>(y, x + dimY) > 0)
					vertex.emplace_back(x, y, z);
			}
		}
	}
	vertex.shrink_to_fit();
	mesh = MeshReconstruction(std::move(vertex), dimX, dimY, dimZ);
}

void QGLMeshViewer::draw()
{
	glColor3f(0.6, 0.2, 1.0);

	if (false)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_TRIANGLES);
	for (auto& f : faces(mesh.poly))
	{
		for (auto& v : CGAL::vertices_around_face(halfedge(f, mesh.poly), mesh.poly))
		{
			auto point = v->point();
			glVertex3f(point.x(), point.y(), point.z());
			auto normal = mesh.vnormals[v];
			glNormal3f(normal.x(), normal.y(), normal.z());
		}
	}

	glEnd();
}

//quad 1 2 3 4
//==>
//triangle 1 2 3
//triangle 3 4 1
void QGLMeshViewer::init()
{
	glShadeModel(GL_SMOOTH);

	//CGAL::copy_face_graph(m, p);
	//double target_edge_length = 0.03;
	//unsigned int nb_iter = 3;

	//PMP::isotropic_remeshing(
	//	faces(m),
	//	target_edge_length,
	//	m,
	//	PMP::parameters::number_of_iterations(nb_iter)
	//	.protect_constraints(true)//i.e. protect border, here
	//);

	//CGAL::copy_face_graph(m, p);
}
