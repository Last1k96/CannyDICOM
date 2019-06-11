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

	auto vertex = std::vector<uint8_t>(dimX * dimY * dimZ);
	
#pragma omp parallel for
	for (auto z = 0; z < dimZ; ++z)
	{
		auto& image = images[z];
		for (auto y = 0; y < dimY; ++y)
		{
			for (auto x = 0; x < dimX; ++x)
			{
				vertex[z * dimX * dimY + y * dimX + x] = image.at<uint8_t>(y, x + dimY);
			}
		}
	}
	mc = DualMarchingCubes(std::move(vertex), dimX, dimY, dimZ);
}

void QGLMeshViewer::draw()
{
	glColor3f(0.8, 0.7, 0.65);

	if constexpr (false)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < mc.quads.size(); ++i)
	{
		auto& q = mc.quads[i];
		auto& v1 = mc.vertices[q.i0];
		auto& v2 = mc.vertices[q.i1];
		auto& v3 = mc.vertices[q.i2];
		auto& v4 = mc.vertices[q.i3];

		for (auto v : { v1, v2, v3 }) {
			glVertex3f(v.x, v.y, v.z);
			auto& norm = mc.normals[2 * i];
			glNormal3f(norm.x, norm.y, norm.z);
		}
		for (auto v : { v3, v4, v1 }) {
			glVertex3f(v.x, v.y, v.z);
			auto& norm = mc.normals[2 * i + 1];
			glNormal3f(norm.x, norm.y, norm.z);
		}
	}
	glEnd();

	//	glBegin(GL_TRIANGLES);
	//for (auto& f : faces(mesh.poly))
	//{
	//	for (auto& v : CGAL::vertices_around_face(halfedge(f, mesh.poly), mesh.poly))
	//	{
	//		count++;
	//		auto& point = v->point();
	//		glVertex3f(point.x(), point.y(), point.z());
	//		//auto& normal = mesh.vnormals[v];
	//		//glNormal3f(normal.x(), normal.y(), normal.z());
	//		auto length = std::sqrt(point.x() * point.x() + point.y() * point.y() + point.z() * point.z());
	//		glNormal3f(point.x() / length, point.y() / length, point.z() / length);
	//	}
	//}

	//glEnd();
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
