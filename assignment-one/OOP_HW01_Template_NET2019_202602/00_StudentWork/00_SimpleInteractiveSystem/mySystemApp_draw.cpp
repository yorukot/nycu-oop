//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2023/02/26
//
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::drawOrigin() const
{
	glLineWidth(3.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-100.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glEnd();
	//
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, -100.0);
	glVertex3f(0.0, 0.0, 100.0);
	glEnd();
}

void MY_SYSTEM_APP::draw() const
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	FREE_CANVAS_2D::begin_draw();

	glLineWidth(1.0);
	glColor3f(0.5, 0.5, 0.5);



	if (mFlgShow_Grid) {
		FREE_CANVAS_2D::draw_wire_grid();
	}

	draw_System_Content();

	drawOrigin();

	FREE_CANVAS_2D::end_draw();
	//cout << "END CROWD_SIMULATION_APP::draw( )" << endl;
	glEnable(GL_LIGHTING);
}

void MY_SYSTEM_APP::draw_System_Content() const
{

	m_CircleManager.draw();

	switch (mSystemType) {
	case SYSTEM_TYPE_GRAPH:
		mGraphManager.draw();
		break;


	}
}


// CODE: 2026/03/21. Do not delete this line.