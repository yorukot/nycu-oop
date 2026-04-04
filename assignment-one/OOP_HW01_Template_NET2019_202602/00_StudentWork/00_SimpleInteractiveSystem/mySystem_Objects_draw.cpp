#include "mySystem_Objects.h"

#define PI 3.1415

void CIRCLE::draw() const
{
	int n = 100;
	vector3 color1(.9, .3, .9);
	vector3 color2(.2, .8, .3);
	
	glBegin(GL_TRIANGLE_FAN);
	//glVertex3f(p.x, p.y, p.z);
	glVertex3f(p.x, 0.0, p.y);

	for (int i = 0; i < n+1; ++i) {
		float f = i / (float)n;

		float f1 = sin(f * 4 * PI);
		float f2 = cos(f * 8 * PI);
		glColor3f(
			f1* color1[0] + f2 * color2[0]
			, f1 * color1[1] + f2 * color2[1]
			, f1 * color1[2] + f2 * color2[2]
		);

		float x, y, z;
		double a = i / ((float)n) * 2*PI;
		x = p.x + r * cos(a);
		y = p.y + r * sin(a);
		z = 0.0;
		glVertex3f(x, 0, y);
	}
	glEnd();
}