//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2026/03/20
//
#ifndef __MY_OBJECTS_H_
#define __MY_OBJECTS_H_

#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;

class CIRCLE {
public:
	CIRCLE(const vector3 &p, float r);
public:
	void draw() const;
	void reset();
protected:
public:
	vector3 p;	// position
	double r;	// radius
	vector3 v; // velocity;

};

class CIRCLE_MANAGER {
public:
	CIRCLE_MANAGER();
	void draw() const;

	void resolveCollisions();
	void update();
	void reset();
protected:
	void applyForce();
protected:
	int mNumberOfObjects;
	vector<CIRCLE> mCircles;
};
#endif