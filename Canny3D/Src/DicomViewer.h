#pragma once
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QHBoxLayout>
#include <QWheelEvent>
#include <opencv2/core/mat.hpp>
#include "Utility.h"
#include "Settings.h"

class DicomViewer : public QLabel
{
Q_OBJECT

public:
	explicit DicomViewer(QWidget* parent = Q_NULLPTR, std::vector<ImebraImage> && data = {});
[[nodiscard]] size_t imageCount() const;
[[nodiscard]] size_t index() const;
[[nodiscard]] cv::Mat computeCurrentImage() const;
	std::vector<ImebraImage> const images{};

private:	
	size_t idx{};
	void updateMargins();
	cv::Mat currentImage;
	Settings settings;

	int pixmapWidth = 0;
	int pixmapHeight = 0;

public slots:
	void setPixmap(const QPixmap& pm);
	bool selectImage(int index);
	void setSettings(Settings const& s);
cv::Mat computeImage(int index) const;

signals:
void imageChanged(int index);

protected:
void resizeEvent(QResizeEvent* event) override;

private:
bool eventFilter(QObject* obj, QEvent* event) override;
void handleWheelEvent(QWheelEvent*);
void updateImage();
};
