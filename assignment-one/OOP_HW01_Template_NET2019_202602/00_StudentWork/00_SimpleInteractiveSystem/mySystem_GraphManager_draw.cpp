//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2026/03/20
//

#include <cmath>
#include "mySystem_GraphManager.h"


void GRAPH_MANAGER::draw() const
{
	vector<double> X;
	vector<double> Y;
	int numCurves = getNumCurves();
	for (int i = 0; i < numCurves; ++i) {
		const CURVE& curve = getCurve(i);
		draw_Function(curve);
		if (!mEnabledSpecialPoints) continue;

		curve.getExtremePoints(X, Y);
		draw_Points(X, Y);
		//
		draw_BoundaryPoints(curve);
	}


}

void GRAPH_MANAGER::draw_Points(
	const vector<double>& X
	, const vector<double>& Y) const
{
	if (X.size() != Y.size()) return;
	glPointSize(15.0);

	int numSamples = X.size();

	//cout << "numSamples:" << numSamples << endl;

	glBegin(GL_POINTS);
	for (int i = 0; i < numSamples; ++i) {
		float x, z;
		x = X[i];
		z = Y[i];
		//glColor3f(1.0, 0.5, 0.0);
		glColor3f(0.0, 0.0, 0.7);
		glVertex3f(x, 0.0, z);
	}
	glEnd();
}


void GRAPH_MANAGER::draw_BoundaryPoints(const CURVE& curve) const
{
	double x, z;

	glPointSize(15);
	glBegin(GL_POINTS);
	curve.getBoundaryPoint(0, x, z);
	glColor3f(1.0, 0.2, 0.2);
	glVertex3f(x, 0.0, z);

	curve.getBoundaryPoint(1, x, z);
	glColor3f(0.2, 1.0, 0.2);
	glVertex3f(x, 0.0, z);
	glEnd();
}



void GRAPH_MANAGER::draw_Function(const CURVE& curve) const
{
	glLineWidth(6.0);
	glColor3f(0.2, 0.2, 0.2);

	glBegin(GL_LINE_STRIP);
	int numSamples = curve.getNumOfSamples();
	auto curve_points = curve.getPoints();

	/*
	for (int i = 0; i < numSamples; ++i) {
		float y;
		float x;
		//x = x0 + (i / ((double)numSamples - 1)) * (x1 - x0);
		//y = curve.getValue(x);

		x = curve_points[i].x;
		y = curve_points[i].y;

		glVertex3f(x, 0.0, y);
	}
	glEnd();
	*/

	double cf = 1.0;

	glLineWidth(3.0);
	glColor3f(0.9, 0.9, 0.0);
	glBegin(GL_LINE_STRIP);
	numSamples = curve.getNumOfSamples();
	for (int i = 0; i < numSamples; ++i) {
		float y;
		float x;
		//x = x0 + (i / ((double)numSamples - 1)) * (x1 - x0);
		//y = curve.getValue(x);
		x = curve_points[i].x;
		y = curve_points[i].y;

		double f = i / (double)numSamples;
		vector3 color = mColorTable.getColor_Linear(f);
		glColor3f(cf * color.x, color.y, color.z);
		glVertex3f(x, 0.0, y);
	}
	glEnd();

	glLineWidth(2.0);

}

void GRAPH_MANAGER::draw_Function() const
{
	//draw_Function(mCurveFunction);
}