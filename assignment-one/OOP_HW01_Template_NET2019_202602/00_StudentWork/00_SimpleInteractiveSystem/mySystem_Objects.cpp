#include <cmath>
#include "mySystem_Objects.h"

float getRand() {
	return (rand() % RAND_MAX) / (float)(RAND_MAX - 1);
}

float getRand(float u0, float u1) {
	return u0 + getRand() * (u1 - u0);
}

CIRCLE::CIRCLE(const vector3& p, float r)
{
	this->p = p;
	this->r = r;
	v = vector3(0, 0, 0);
}

void CIRCLE::reset()
{
    v = vector3(0, 0, 0);
}

CIRCLE_MANAGER::CIRCLE_MANAGER()
{
    mNumberOfObjects = 20;
	reset();
}

void CIRCLE_MANAGER::reset()
{
    mCircles.clear();
	int &n = mNumberOfObjects;
	for (int i = 0; i < n; ++i) {
		vector3 p;
		double r;
		p.x = getRand(-10, 10);
		p.y = getRand(-10, 10);
        p.z = .0;

		r = getRand(1, 3);
        mCircles.emplace_back(p, r);
		mCircles.back().reset();
	}
}


// Check collision between two CIRCLEs
bool isColliding(const CIRCLE& c1, const CIRCLE& c2) {
    double dx = c1.p.x - c2.p.x;
    double dy = c1.p.y - c2.p.y;
    double dist2 = dx * dx + dy * dy;
    double r = c1.r + c2.r;
    return dist2 < r * r;
}

// Resolve collision by pushing CIRCLEs apart
void resolveCollision(CIRCLE& c1, CIRCLE& c2) {
    double dx = c1.p.x - c2.p.x;
    double dy = c1.p.y - c2.p.y;
    double dist = std::sqrt(dx * dx + dy * dy);

    // check if the two circles overlap
    // If no, return
    // If yes, push each CIRCLE away equally
    // You can use copilot to generete the source code here.
	const double minDist = c1.r + c2.r;
	if (dist >= minDist) return;

	if (dist <= 1e-8) {
		dx = minDist;
		dy = 0.0;
		dist = minDist;
	}

	double overlap = minDist - dist;
	double nx = dx / dist;
	double ny = dy / dist;
	double half = overlap * 0.5;

	c1.p.x += static_cast<float>(nx * half);
	c1.p.y += static_cast<float>(ny * half);
	c2.p.x -= static_cast<float>(nx * half);
	c2.p.y -= static_cast<float>(ny * half);

}

void CIRCLE_MANAGER::resolveCollisions() {
    //Detect and resolve collisions for all pairs of circles
    //Make sure that you use references of circles. Not pass-by-value
    //for (size_t i = 0; i < mCircles.size(); ++i) {
    //    ci = mCircles[i];
    //    for (size_t j = i + 1; j < mCircles.size(); ++j) {
    //        cj = mCircles[j];
    //        if (isColliding(ci, cj)) {
    //            resolveCollision(ci, cj);
    //        }
    //    }
    //}
	for (size_t i = 0; i < mCircles.size(); ++i) {
		CIRCLE& ci = mCircles[i];
		for (size_t j = i + 1; j < mCircles.size(); ++j) {
			CIRCLE& cj = mCircles[j];
			if (isColliding(ci, cj)) {
				resolveCollision(ci, cj);
			}
		}
	}

    // need to make sure the circles are about the line y = 0
    for (size_t i = 0; i < mCircles.size(); ++i) {
        CIRCLE& ci = mCircles[i];
        float x = ci.p.x;
        float y = ci.p.y;

        // Check if the circle above y = 0?
        if (y - ci.r < 0) {
            ci.p.y += static_cast<float>(ci.r - y);
            if (ci.v.y < 0.0f) {
                ci.v.y = 0.0f;
            }

        }
    }
}
void CIRCLE_MANAGER::draw() const {
	for (auto& c : mCircles) {
		c.draw();
	}
}

//
// comptue force F
// F = ma => a = F/m => a = F, where a is the acceleration, m is the mass (assuming 1).
// v = v + a*dt, where dt is the simulation time step size and v is the velocity
// p = p + v * dt, where p is the position of the circle
//
void CIRCLE_MANAGER::applyForce()
{
    float dt = 0.01;
    float c = 10.0;
    vector3 g(0.0, -9.0, 0.0);
    for (size_t i = 0; i < mCircles.size(); ++i) {
        CIRCLE& ci = mCircles[i];
		float x = ci.p.x;
		float y = ci.p.y;
		(void)x;
		(void)y;

		vector3 f = c * g * dt;
		vector3 a = f;
		ci.v += a * dt;
		ci.p.x += ci.v.x * dt;
		ci.p.y += ci.v.y * dt;
    }
}
void CIRCLE_MANAGER::update() {
    applyForce();
    resolveCollisions();
}
