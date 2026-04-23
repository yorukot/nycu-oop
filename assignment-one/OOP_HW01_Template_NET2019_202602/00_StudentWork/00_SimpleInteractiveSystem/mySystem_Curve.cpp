//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2026/03/20
//
#include "mySystem_Curve.h"
#include <iostream>

using namespace std;

//
// Rotate a point (x, y) in the counter-clockwise direction with angle (radian) on the x-y plane
// Output (nx, ny), the new position of the point
//
void rotatePoint(float x, float y, float angle, float& nx, float& ny) {
	double cosA = std::cos(angle);
	double sinA = std::sin(angle);

	nx = x;
	ny = y;
	nx = static_cast<float>(x * cosA - y * sinA);
	ny = static_cast<float>(x * sinA + y * cosA);
}

//
// no-arg constructor
//
CURVE::CURVE()
{
	mEnabledRotation = true;
	mAngle = 0.0;

	//xMin = -100.0;
	//xMax= 100.0;

	xMin = -100.0;
	xMax = 100.0;

	mNumSamples = 100;

	a = b = c = d = 1;
	a = 1.0;
	b = -0.5;

	mCurveType = CURVE_TYPE_EXPONENTIAL;

	computePoints();
}

void CURVE::setRotationAngle(float angle) 
{
	//if (mAngle != angle) {
		mAngle = angle;
		computePoints();
	//}
}
void CURVE::setEnabledRotation(bool flg)
{
	mEnabledRotation = flg;
}

// set the curve type
void CURVE::setCurveType(CURVE_TYPE type)
{
	mCurveType = type;

	computePoints();
}

// increase parameter b
void CURVE::increase(double dv)
{
	b += dv;
}

// decrease parameter b
void CURVE::decrease(double dv)
{
	b -= dv;

}

// set the value to parameter c
void CURVE::setC(double c)
{
	this->c = c;
}

// set the value to parameter d
void CURVE::setD(double d)
{
	this->d = d;
}

// ask for input
void CURVE::askForInput()
{
	//empty
}

//
// set the interval of x
// xMin <- min_X
// xMax <- max_X
//
void CURVE::set_IntervalOfX(double min_X, int max_X)
{
	this->xMin = min_X;
	this->xMax = max_X;
}

//
// return the interval of x
// xMin <- this->xMin
// xMax <- this->xMax
void CURVE::getIntervalOfX(double& xMin, double& xMax) const
{

	xMin = this->xMin;
	xMax = this->xMax;
}

//
// return the number of sample points
//
int CURVE::getNumOfSamples() const
{
	return mNumSamples;
}

//
// set the number of sample points
// mNumSamples <- num
//
void CURVE::setNumOfSamplePoints(int num)
{
	mNumSamples = num;
	computePoints();
}

//
// get the value of a function for x
//
double CURVE::getValue(double x) const
{
	double y = 0;
	switch (mCurveType) {
	case CURVE_TYPE_EXPONENTIAL:
	{
		double w = x / 5.0;
		y = w + (c + std::cos(16.0 * d * w)) * std::exp(-w);
		break;
	}
	case CURVE_TYPE_FUNC2:
		y = c * x - d * std::sin(8.0 * std::sin(x));
		break;
	case CURVE_TYPE_FUNC3:
		y = c * x + 4.0 * std::cos(x) + d;
		break;
	}

	return y;
}

//
// randomly compute a value for c 
// inside the interval [u0, u1] in a uniform manner
//
void CURVE::setRandom_C(double u0, double u1)
{

	double f = (rand() % RAND_MAX) / (double)(RAND_MAX - 1);
	double u = u0 + f * (u1 - u0);
	c = u;
}

//
// randomly compute a value for d 
// inside the interval [u0, u1] in a uniform manner
//
void CURVE::setRandom_D(double u0, double u1)
{

	double f = (rand() % RAND_MAX) / (double)(RAND_MAX - 1);
	double u = u0 + f * (u1 - u0);
	d = u;
}

//
// get the boundary point (x, y)
// point_index = 0: return the leftmost point (x,y)
// point_index = 1: return the rightmost point (x,y)
// 
void CURVE::getBoundaryPoint(int point_index, double& x, double& y) const
{
	if (mPoints.empty()) {
		x = 0.0;
		y = 0.0;
		return;
	}

	x = mPoints[0].x;
	y = mPoints[0].y;
	if (point_index == 1) {
		x = mPoints[mPoints.size() - 1].x;
		y = mPoints[mPoints.size() - 1].y;
	}
}

//
// get the x- and y-coordinates of all the extreme points 
//
// store the x- and y-coordinates to X and Y vectors, respectively
//
void CURVE::getExtremePoints(vector<double>& X, vector<double>& Y) const
{
	X.clear();
	Y.clear();
	if (mPoints.size() < 3) return;

	for (int i = 1; i < mNumSamples - 1; ++i) {
		double x = mPoints[i].x;
		double y = mPoints[i].y;

		double yL = mPoints[i - 1].y;
		double yR = mPoints[i + 1].y;

		if ((y > yL && y > yR) || (y < yL && y < yR)) {
			X.push_back(x);
			Y.push_back(y);
		}
	}
}

//
// compute the position of each sample point as normal
// after that, rotate it based on the rotation angle, mAngle
//
void CURVE::computePoints( ) {

	double &x0 = xMin;
	double &x1 = xMax;

	mPoints.clear();
	for (int i = 0; i < mNumSamples; ++i) {
		float y;
		float x;
		x = x0 + (i / ((double)mNumSamples - 1)) * (x1 - x0);
		y = static_cast<float>(getValue(x));
		{
			float nx = x;
			float ny = y;
			if (mEnabledRotation) {
				rotatePoint(x, y, mAngle, nx, ny);
			}
			x = nx;
			y = ny;
		}

		mPoints.emplace_back(x, y, 0.);
	}
}

const vector<vector3>& CURVE::getPoints() const {
	return mPoints;
}
