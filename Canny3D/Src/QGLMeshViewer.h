#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include <QGLViewer/qglviewer.h>
#include "MeshReconstruction.h"
#include "DualMarchingCubes.h"
class QGLMeshViewer : public QGLViewer
{
public:
	QGLMeshViewer(QWidget* parent, std::vector<cv::Mat> const& images);

protected:
	void draw() override;
	void init() override;
	DualMarchingCubes mc;
};
