#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include <QGLViewer/qglviewer.h>
#include "dualmc.h"
#include "DualMarchingCubes.h"
#include <CGAL/Surface_mesh/Surface_mesh.h>

typedef CGAL::Simple_cartesian<double> K;
typedef K::Point_3 Point;
typedef CGAL::Surface_mesh<Point> Mesh;

class QGLMeshViewer : public QGLViewer
{
public:
	QGLMeshViewer(QWidget* parent, std::vector<cv::Mat> const& images);

protected:
	void draw() override;
	void init() override;

private:
	DualMarchingCubes mc;
	Mesh m;
};
