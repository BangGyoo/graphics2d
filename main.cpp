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
		xPos.y += 3.0f;
		break;
	case 'a':
		xPos.x -= 3.0f;
		break;
	case 's':
		xPos.y -= 3.0f;
		break;
	case 'd':
		xPos.x += 3.0f;
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

	ShapeX x(pCross[0], pCross[1], pCross[2], pCross[3]);

	Matrix mScale_1(Matrix::SCALE, 8, 8);
	Matrix mRotate_1(Matrix::ROTATE, (float)(0.0f * DEG_TO_RAD));
	Matrix mTranslate_1(Matrix::TRANSLATE, xPos);

	Matrix result = mTranslate_1 * mRotate_1;
	result = result * mScale_1;

	x = result * x;
	x = CameraToViewport(x);
	Color c(255, 128, 0);
	x.drawShapeX(c);

	// Object 2
	Vector points[4];

	Matrix mScale_2(Matrix::SCALE,60,20);
	Matrix mRotate_2 = Rotate(ang2 * DEG_TO_RAD);
	Matrix mTranslate_2(Matrix::TRANSLATE, 100 + xPos.x , 100 + xPos.y);

	result =  mTranslate_2 * mRotate_2;
	result = result * mScale_2;

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
	
	Matrix mScale_3(Matrix::SCALE,10,100);
	Matrix mRotate_3(Matrix::ROTATE, ang3 * DEG_TO_RAD);
	Matrix mTranslate_3(Matrix::TRANSLATE, -100 + xPos.x, 100 + xPos.y);

	result = mTranslate_3 * mRotate_3;
	result = result * mScale_3;

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
	
	Matrix mScale_4(Matrix::SCALE, 110, 50);
	Matrix mRotate_4(Matrix::ROTATE,ang4 * DEG_TO_RAD);
	Matrix mTranslate_4(Matrix::TRANSLATE, 100 + xPos.x, -100 + xPos.y);

	result = mTranslate_4 * mRotate_4;
	result = result * mScale_4;

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

	Matrix mScale_5(Matrix::SCALE, 100, 25);
	Matrix mRotate_5(Matrix::ROTATE, ang5 * DEG_TO_RAD);
	Matrix mTranslate_5(Matrix::TRANSLATE,-100+xPos.x,-100 + xPos.y);

	result = mTranslate_5 * mRotate_5;
	result = result * mScale_5;

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
	glutInitWindowPosition(1000, 400);
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