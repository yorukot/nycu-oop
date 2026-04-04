//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2026/03/20
//
#ifndef __MY_GRAPH_MANAGER_H_
#define __MY_GRAPH_MANAGER_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "mySystem_Curve.h"
#include "../openGLbasic/ogl_basic_tools.h"

using std::vector;

#define MAX_NUM_CURVES 100			// maximum number of curves
#define MIN_NUM_CURVES 1			// minimum number of curves

/*
enum GRAPH_CURVE_OPTION {
	GRAPH_OPTION_ONE_CURVE = 0
	, GRAPH_OPTION_MULTI_CURVES
};

enum GRAPH_PARAM_OPTION {
	GRAPH_PARAM_OPTION_C = 0
	, GRAPH_PARAM_OPTION_D
};
*/

class GRAPH_MANAGER {
public:
	GRAPH_MANAGER();
	void setNumCurves(int num = MAX_NUM_CURVES);

	double getParam_D() const;
	int getNumCurves() const;
	int getNumOfSamplePoints() const { return mNumOfSamplePoints; }
	//
	const CURVE &getCurve(int curve_index) const;
	//
	double getC_Average() const;
	double getC_Lowest() const;
	double getC_Largest() const;
	//
	void setRotationFlag(bool flg);
	bool getRotationFlag() const;
	//
	void setSpecialPointsFlag(bool flg);
	bool getSpecialPointsFlag() const;
	//
	void increase_CurveNumber();
	void decrease_CurveNumber();

	void increase_NumOfSamplePoints(int delta_num = 2);
	void decrease_NumOfSamplePoints(int delta_num = 2);
	
	//
	void increase_Param_D();
	void decrease_Param_D();
	
	//
	void setCurveType(CURVE_TYPE type);

	//
	
	//
	void reset();
	void update();
	void draw() const;


protected:
	void setCurves_D(double d);
	void setCurves_NumOfSamplePoints(int num);

	void setCurves_Random_C();
	void setCurves_IntervalOfX(double min_X, int max_X);
	//
	void setCurves_EnabledRotation(bool flg);
	void setCurves_RotationAngle(float angle);
	//
	void draw_Function() const;
	void draw_Function(const CURVE& curve) const;
	void draw_BoundaryPoints(const CURVE& curve) const;
	void draw_Points(const vector<double>& X, const vector<double>& Y) const;
	//
protected:
	double mMin_X, mMax_X;					// interval of x

	int mNumCurves;							// number of curves
	double mC_LowerBound, mC_UpperBound;	// lower and upper of the paramter c
	double mD_LowerBound, mD_UpperBound;	// lower and upper of the paramter d
	//
	double mParam_D;						// parameter d
	double mDelta_D;						// change of parameter d at a time
	//
	vector<CURVE> mCurves;			// an array of curves
	//
	int mNumOfSamplePoints;					// number of sample points of a curve
	//
	bool mEnabledRotation;					// mEnabledRotation
	mutable float mRotationAngle;			// rotation angle
	//
	bool mEnabledSpecialPoints;

	//
	COLOR_TABLE mColorTable;
};

#endif

// CODE: 2023/02/26. Do not delete this line.