#pragma once
#include <QGLViewer/qglviewer.h>
#include <Qstring>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <opencv2/core/mat.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef std::vector<Point_2> Points;

class QGLMeshViewer : public QGLViewer
{
	std::vector<cv::Mat> edges;
public:
	Points points, result;

	QGLMeshViewer(QWidget* parent, std::vector<cv::Mat> edges);

protected:
	void draw() override;
	void init() override;
};
