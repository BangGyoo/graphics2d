#include "Utilities.h"
#include "Shape.h"

float ang2, ang3, ang4, ang5;
int rot;

Vector xPos;

Point pTriangle[3] = { { 0, 1 },{ -1, -1 },{ 1, -1 } };
Point pSquare[4] = { { -1, 1 },{ -1, -1 },{ 1, -1 },{ 1, 1 } };
Point pCross[4] = { { -1, 1 },{ -1, -1 },{ 1, -1 },{ 1, 1 } };

int winID;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		xPos.y += 1.0f;
		break;
	case 'a':
		xPos.x -= 1.0f;
		break;
	case 's':
		xPos.y -= 1.0f;
		break;
	case 'd':
		xPos.x += 1.0f;
		break;
	case VK_SPACE:
		if (rot == 1) rot = 0;
		else rot = 1;
		break;
	case VK_ESCAPE:
		delete[] FrameBuffer::buffer;
		glutDestroyWindow(winID);
		exit(0);
		break;
	}
}


void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	}
}

void mouseMove(int x, int y)
{
}

void loop(void)
{
	glutPostRedisplay();
}

void render(void)
{
	FrameBuffer::Clear(255, 255, 255);

	//Put your rendering code here
	Vector pScale, pTranslate;
	Vector points[4];
	Matrix mScale, mRotate, mTranslate;
	
	pScale.x = 8;
	pScale.y = 8;
	pTranslate = xPos;

	mScale = Scale(pScale);
	mRotate = Rotate(0.0f * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	Matrix result = mTranslate * mRotate;
	result = result * mScale;

	points[0] = result * pCross[0]; points[1] = result * pCross[1];
	points[2] = result * pCross[2]; points[3] = result * pCross[3];

	points[0] = CameraToViewport(points[0]); points[1] = CameraToViewport(points[1]);
	points[2] = CameraToViewport(points[2]); points[3] = CameraToViewport(points[3]);

	Color c;
	c.r = 255, c.g = 128, c.b = 0;


	DrawLine(points[0], points[2], c);
	DrawLine(points[1], points[3], c);
	// Object 2
	pScale.x = 60, pScale.y = 20;
	pTranslate.x = 100 + xPos.x, pTranslate.y = 100 + xPos.y;

	mScale = Scale(pScale);
	mRotate = Rotate(ang2 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	result = mTranslate * mRotate;
	result = result * mScale;

	points[0] = result * pSquare[0];
	points[1] = result * pSquare[1];
	points[2] = result * pSquare[2];
	points[3] = result * pSquare[3];

	points[0] = CameraToViewport(points[0]);
	points[1] = CameraToViewport(points[1]);
	points[2] = CameraToViewport(points[2]);
	points[3] = CameraToViewport(points[3]);
	c.r = 255, c.g = 0, c.b = 0;

	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[3], c);
	DrawLine(points[3], points[0], c);

	if (rot) ang2 += (1);
	// Object 3
	pScale.x = 10, pScale.y = 100;
	pTranslate.x = -100 + xPos.x, pTranslate.y = 100 + xPos.y;

	mScale = Scale(pScale);
	mRotate = Rotate(ang3 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	result = mTranslate * mRotate;
	result = result * mScale;

	points[0] = result * pTriangle[0];
	points[1] = result * pTriangle[1];
	points[2] = result * pTriangle[2];

	points[0] = CameraToViewport(points[0]);
	points[1] = CameraToViewport(points[1]);
	points[2] = CameraToViewport(points[2]);
	c.r = 0, c.g = 0, c.b = 0;

	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[0], c);

	if (rot) ang3 += (-1);
	// Object 4
	pScale.x = 110, pScale.y = 50;
	pTranslate.x = 100 + xPos.x, pTranslate.y = -100 + xPos.y;

	mScale = Scale(pScale);
	mRotate = Rotate(ang4 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	result = matmatMul(mTranslate, mRotate);
	result = matmatMul(result, mScale);

	points[0] = result * pTriangle[0];
	points[1] = result * pTriangle[1];
	points[2] = result * pTriangle[2];

	points[0] = CameraToViewport(points[0]);
	points[1] = CameraToViewport(points[1]);
	points[2] = CameraToViewport(points[2]);
	c.r = 0, c.g = 0, c.b = 255;

	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[0], c);

	if (rot) ang4 += (1);
	// Object 5
	pScale.x = 100, pScale.y = 25;
	pTranslate.x = -100 + xPos.x, pTranslate.y = -100 + xPos.y;

	mScale = Scale(pScale);
	mRotate = Rotate(ang5 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	result = mTranslate * mRotate;
	result = result * mScale;

	points[0] = result * pSquare[0];
	points[1] = result * pSquare[1];
	points[2] = result * pSquare[2];
	points[3] = result * pSquare[3];

	points[0] = CameraToViewport(points[0]);
	points[1] = CameraToViewport(points[1]);
	points[2] = CameraToViewport(points[2]);
	points[3] = CameraToViewport(points[3]);
	c.r = 128, c.g = 128, c.b = 128;

	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[3], c);
	DrawLine(points[3], points[0], c);

	if (rot) ang5 += (-1);


	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, FrameBuffer::buffer);
	glutSwapBuffers();
}

void init(void)
{
	FrameBuffer::Init(WIDTH, HEIGHT);

	//Initialize everything here
	rot = 1;
	xPos.x = xPos.y = 0.0f;
	ang2 = 0.0f, ang3 = 45.0f, ang4 = 0.0f, ang5 = 60.0f;
}


int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	winID = glutCreateWindow("CS200");

	glClearColor(0, 0, 0, 1);

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);
	glutIdleFunc(loop);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	init();

	glutMainLoop();

	return 0;
}