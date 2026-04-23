//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2026/03/20
//

#include "mySystem_GraphManager.h"


#define MAX_NUM_SAMPLE_POINTS 400
#define MIN_NUM_SAMPLE_POINTS 2

#define PI 3.141592654

//
// no-arg constructor
//
GRAPH_MANAGER::GRAPH_MANAGER()
{
	mEnabledRotation = true;
	mRotationAngle = 0.0;

	mEnabledSpecialPoints = true;

	mMin_X = -10;
	mMax_X = 10;


	mD_LowerBound = -10;
	mD_UpperBound = 10;

	mC_LowerBound = -2;
	mC_UpperBound = 2;

	mParam_D = -1;

	mDelta_D = 1;

	mNumOfSamplePoints = MAX_NUM_SAMPLE_POINTS / 2;

	mNumCurves = MAX_NUM_CURVES;
	mCurves.resize( MAX_NUM_CURVES );

	setCurves_IntervalOfX(mMin_X, mMax_X);
	setCurves_D(mParam_D);
	setCurves_NumOfSamplePoints(mNumOfSamplePoints);
	setCurves_Random_C( );
	setCurves_EnabledRotation(mEnabledRotation);
	setCurves_RotationAngle(mRotationAngle);

	mNumCurves = MIN_NUM_CURVES;


	mColorTable.addEntry(0.0, vector3(0.5, 0.0, 1.0));
	mColorTable.addEntry(0.1, vector3(0.0, 1.0, 1.0));
	mColorTable.addEntry(0.2, vector3(0.0, 1.0, 0.0));
	mColorTable.addEntry(0.3, vector3(1.0, 1.0, 0.0));
	//
	mColorTable.addEntry(0.4, vector3(1.0, 0.0, 0.0));
	mColorTable.addEntry(0.5, vector3(1.0, 0.5, 0.0));
	mColorTable.addEntry(0.6, vector3(1.0, 1.0, 0.0));
	mColorTable.addEntry(0.7, vector3(0.0, 1.0, 0.0));
	mColorTable.addEntry(0.8, vector3(0.0, 1.0, 1.0));
	mColorTable.addEntry(0.9, vector3(0.0, 0.0, 1.0));
	mColorTable.addEntry(1.0, vector3(1.0, 0.0, 1.0));
}

void GRAPH_MANAGER::setSpecialPointsFlag(bool flg)
{
	mEnabledSpecialPoints = flg;
}
bool GRAPH_MANAGER::getSpecialPointsFlag() const
{
	return mEnabledSpecialPoints;
}

//
// set the curve type to all the curves
//
void GRAPH_MANAGER::setCurveType(CURVE_TYPE type)
{
	for (int i = 0; i < MAX_NUM_CURVES; ++i) {
		mCurves[i].setCurveType( type );
	}
}

//
// set the interval of x, [min_X, max_X], to all the curves
//
void  GRAPH_MANAGER::setCurves_IntervalOfX(double min_X, int max_X)
{
	for (int i = 0; i < MAX_NUM_CURVES; ++i) {
		mCurves[i].set_IntervalOfX(min_X, max_X);
	}
}

//
// set the value of parameter d of all the curves
//
void GRAPH_MANAGER::setCurves_D(double d)
{
	for (int i = 0; i < MAX_NUM_CURVES; ++i) {
		mCurves[i].setD(d);
	}
}

//
// increase parameter mParam_D by mDelta_D, and set it to all the curves
// 
// mParam_D must be inside [mD_LowerBound, mD_UpperBound]
//
void GRAPH_MANAGER::increase_Param_D()
{
	mParam_D = mParam_D + mDelta_D;
	if (mParam_D > mD_UpperBound)mParam_D = mD_UpperBound;
	setCurves_D(mParam_D);
}

//
// decrease parameter mParam_D by -mDelta_D, and set it to all the curves
// 
// mParam_D must be inside [mD_LowerBound, mD_UpperBound]
//
void GRAPH_MANAGER::decrease_Param_D()
{
	mParam_D = mParam_D - mDelta_D;
	if (mParam_D < mD_LowerBound)mParam_D = mD_LowerBound;
	setCurves_D(mParam_D);
}

//
// get the value of mParam_D 
//
double GRAPH_MANAGER::getParam_D() const
{
	return mParam_D;
}

void GRAPH_MANAGER::setRotationFlag(bool flg) 
{ 
	mEnabledRotation = flg; 
	setCurves_EnabledRotation(mEnabledRotation);
}
bool GRAPH_MANAGER::getRotationFlag() const 
{ 
	return mEnabledRotation; 
}

void GRAPH_MANAGER::setCurves_EnabledRotation(bool flg)  
{
	for (int i = 0; i < MAX_NUM_CURVES; ++i) {
		mCurves[i].setEnabledRotation(flg);
	}
}

void GRAPH_MANAGER::setCurves_RotationAngle(float angle)
{
	for (int i = 0; i < MAX_NUM_CURVES; ++i) {
		mCurves[i].setRotationAngle(angle);
	}
}


//
// increase the number of curves by 10 at a time
//
// mNumCurves must be inside [MAX_NUM_CURVES, MAX_NUM_CURVES]
//
void GRAPH_MANAGER::increase_CurveNumber()
{
	mNumCurves += 10;
	if (mNumCurves > MAX_NUM_CURVES) mNumCurves = MAX_NUM_CURVES;
	setCurves_Random_C();

}

//
// decrease the number of curves by 10 at a time
//
// mNumCurves must be inside [MAX_NUM_CURVES, MAX_NUM_CURVES]
//
void GRAPH_MANAGER::decrease_CurveNumber()
{
	mNumCurves -= 10;
	if (mNumCurves < MIN_NUM_CURVES) mNumCurves = MIN_NUM_CURVES;

	setCurves_Random_C();
}

//
// Set the number of curves
// mNumCurves <- num
//
void GRAPH_MANAGER::setNumCurves(int num) {
	if (num < 0) return;
	mNumCurves = num;
	
}

//
// get the number of curves
// return mNumCurves
//
int GRAPH_MANAGER::getNumCurves() const
{
	int numCurves = mNumCurves;
	return numCurves;
}

//
// get curve with index curve_index
//
// return mCurves[curve_index]
//
const CURVE& GRAPH_MANAGER::getCurve(int curve_index) const
{
	return mCurves[curve_index];
}

//
// increase the number of sample points by delta_num at a time
//
// mNumOfSamplePoints must be inside [MIN_NUM_SAMPLE_POINTS, MAX_NUM_SAMPLE_POINTS]
//
void GRAPH_MANAGER::increase_NumOfSamplePoints(int delta_num)
{
	mNumOfSamplePoints += delta_num;
	if (mNumOfSamplePoints > MAX_NUM_SAMPLE_POINTS)
		mNumOfSamplePoints = MAX_NUM_SAMPLE_POINTS;
	setCurves_NumOfSamplePoints(mNumOfSamplePoints);
}

//
// decrease the number of sample points by delta_num at a time
//
// mNumOfSamplePoints must be inside [MIN_NUM_SAMPLE_POINTS, MAX_NUM_SAMPLE_POINTS]
//
void GRAPH_MANAGER::decrease_NumOfSamplePoints(int delta_num)
{
	mNumOfSamplePoints -= delta_num;
	if (mNumOfSamplePoints < MIN_NUM_SAMPLE_POINTS)
		mNumOfSamplePoints = MIN_NUM_SAMPLE_POINTS;
	setCurves_NumOfSamplePoints(mNumOfSamplePoints);
}

//
// set the number of sample points to all the curves
//
void GRAPH_MANAGER::setCurves_NumOfSamplePoints(int num)
{
	for (int i = 0; i < MAX_NUM_CURVES; ++i) {
		mCurves[i].setNumOfSamplePoints(num);
	}
}

//
// For each curve mCurves[i]
// 
// randomly generate parameter C inside 
// [mC_LowerBound, mC_UpperBound] in a uniform manner
// 
// set the parameter value of C to mCurves[i]
//
void GRAPH_MANAGER::setCurves_Random_C()
{
	for (int i = 0; i < MAX_NUM_CURVES; ++i) {
		mCurves[i].setRandom_C(mC_LowerBound, mC_UpperBound);
	}
}

//
// get the average value of parameter c of all the curves
//
double GRAPH_MANAGER::getC_Average() const
{
	double v = 0;
	for (int i = 0; i < mNumCurves; ++i) {
		v += mCurves[i].getC();
	}
	v = v / mNumCurves;
	return v;
}

//
// get the lowest value of parameter c of all the curves
//
double GRAPH_MANAGER::getC_Lowest() const
{
	double v = mCurves[0].getC();
	for (int i = 0; i < mNumCurves; ++i) {
		double tv = mCurves[i].getC();
		if (tv < v) v = tv;
	}
	return v;
}

//
// get the largest value of parameter c of all the curves
//
double GRAPH_MANAGER::getC_Largest() const
{
	double v = mCurves[0].getC();
	for (int i = 0; i < mNumCurves; ++i) {
		double tv = mCurves[i].getC();
		if (tv > v) v = tv;
	}
	return v;
}


void GRAPH_MANAGER::update( ) {
	//if (mEnabledRotation) {
	
	if (mEnabledRotation) {
		mRotationAngle += 0.001;
		if (mRotationAngle > 2 * PI) {
			mRotationAngle -= 2 * PI;
		}
		setCurves_RotationAngle(mRotationAngle);
	}

	//}
	for (int i = 0; i < mNumCurves; ++i) {
		mCurves[i].computePoints();
	}
}

void GRAPH_MANAGER::reset()
{
	mRotationAngle = 0;
	setCurves_Random_C();
	setCurves_RotationAngle(mRotationAngle);
	for (int i = 0; i < mNumCurves; ++i) {
		mCurves[i].computePoints();
	}
}
