#pragma once
#include "Utilities.h"

class Point;
class Line;
class Matrix;
class ShapeX;
class Color;

class Point {
public :
	float x;
	float y;
	Point(float x=0, float y=0);
};
typedef Point Vector;				// 차후 교수님 코드와의 확장성 때문에 벡터 타입은 기존과 통일
class Line {
	Point start;
	Point end;
	Line(Point &start, Point &end);
};

class Matrix {
public:
	enum TransformMat {
		NORMAL,
		SCALE,
		ROTATE,
		TRANSLATE
	};

	float m[3][3];
	Matrix();
	Matrix(TransformMat setting, float args_1, float args_2);
	Matrix(TransformMat setting, float args);
	Matrix(TransformMat setting, Point args);
	

	Vector operator*(Vector &point);
	Matrix operator*(Matrix &m);
	ShapeX operator*(ShapeX x);
};

class ShapeX {
public :
	enum PointPos {
		LEFT_TOP,
		LEFT_BOTTOM,
		RIGHT_BOTTOM,
		RIGHT_TOP
	};
	Point vertex[4];

	ShapeX(Point leftTop, Point leftBottom, Point rightBottom, Point rightTop);
	void drawShapeX(Color c);
};

class Triangle;
class Square;

class Color {
	
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	Color(unsigned char r=0, unsigned char g=0, unsigned char b=0);
};


void drawVLine(int x0, int y0, int x1, int y1, Color c);
void drawHLine(int x0, int y0, int x1, int y1, Color c);
void drawVDLine(int x0, int y0, int x1, int y1, Color c);
void drawHDLine(int x0, int y0, int x1, int y1, Color c);
void DrawLine(Point start, Point end, Color c);
Matrix Translate(const Vector &p);
Matrix Scale(const Vector &s);
Matrix Rotate(const float &alpha);
Vector matpoiMul(const Matrix &m, const Point &p);
Matrix matmatMul(const Matrix &m1, const Matrix &m2);
Vector CameraToViewport(Point point);
ShapeX CameraToViewport(ShapeX x);