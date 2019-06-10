#pragma once
enum class Steps { VOI, Gauss, Canny };

struct Settings
{
	Steps step{ Steps::VOI };
	int voiCenter{};
	int voiWidth{};
	int gaussKernel{};
	double gaussSigma{};
	int cannyLow{};
	int cannyHigh{};
};