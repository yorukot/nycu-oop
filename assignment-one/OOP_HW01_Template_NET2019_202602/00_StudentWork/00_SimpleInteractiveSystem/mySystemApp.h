//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Instructor: Sai-Keung Wong
// Email:	cswingo@cs.nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Hsinchu, Taiwan
// Computer Science
// Date: 2026/03/21
//
#ifndef __MY_SYSTEM_APP_APP_H_
#define __MY_SYSTEM_APP_APP_H_
/////////////////////////////////////////////
#include "../headers.h"
#include <string>
#include "../openGLbasic/opengl_stuff.h"
#include "../freeCanvas2D/freeCanvas2D.h"
#include "../textureManager/texture.h"
/////////////////////////////////////////////
#include "mySystem_Curve.h"
#include "mySystem_GraphManager.h"
#include "mySystem_Objects.h"

#define SYSTEM_TYPE_MONTE_CARLO_CIRCLE		1
#define SYSTEM_TYPE_SINECOSINE_FUNCTION		2
#define SYSTEM_TYPE_CUBIC_FUNCTION			3
#define SYSTEM_TYPE_STUDENT_RECORD_MANAGER	4
#define SYSTEM_TYPE_GRAPH					5
/////////////////////////////////////////////

using namespace ns_opengl;
class MY_SYSTEM_APP : public FREE_CANVAS_2D
{
protected:
	bool mFlgShow_Grid;
	int mMouseButton;
	//
    void updateMonteCarloTitle();
    void updateSineConsineTitle( );
    void updateCurveFunctionTitle();
	void updateGraphManagerTitle();
    //
	void drawOrigin( ) const;
	void draw_MonteCarlo_Circle( ) const;
	void draw_System_Content( ) const;
	void draw_SineCosineFunction( ) const;

	void draw_StudentRecordManager( ) const;
	void askForInput( );
    void increase();
    void decrease();
    void increaseRadius();
    void decreaseRadius();
    void handle_key01();
    void handle_key02();
    void handle_key03();
    void handle_key04();
	//
	void showMyStudentInfo( ) const;
public:
	MY_SYSTEM_APP( );
	virtual void update( );
	virtual void draw( ) const;
	virtual void initApp( );
	//
	bool specialFunc(int key, int x, int y);
	bool handleKeyEvent( unsigned char key );
	bool passiveMouseFunc( int mx, int my );
	bool mouseMotionFunc( int x, int y );
	bool mouseFunc( int button, int state, int x, int y );
	//////////////////////////////////////////////////
protected:
	int mSystemType;
	CURVE mCurveFunction;

	GRAPH_MANAGER mGraphManager;


	CIRCLE_MANAGER m_CircleManager;
};

#endif
// CODE: 2019/02/25. Do not delete this line.