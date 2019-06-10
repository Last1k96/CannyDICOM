#include "QGLMeshViewer.h"

QGLMeshViewer::QGLMeshViewer(QWidget* parent, std::vector<cv::Mat> edges)
	: edges(std::move(edges))
{
}

void QGLMeshViewer::draw()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (auto const& point : result)
	{
		glVertex3f(point.x(), point.y(), 0);
	}
	glEnd();

	glPointSize(3.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (auto const& point : points)
	{
		glVertex3f(point.x(), point.y(), 0);
	}
	glEnd();
}

void QGLMeshViewer::init()
{
	result = {
		{0.5, -0.5},
		{0.5, 0.5},
		{-0.5, 0.5},
		{-0.5, -0.5}
	};
}
