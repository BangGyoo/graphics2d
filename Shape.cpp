#pragma once
#include "Shape.h"


Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}


Line::Line(Point &start, Point &end) {
		this->start = start;
		this->end = end;
}


Color::Color(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;
		this->g = g;
		this->b = b;
}



void drawVLine(int x0, int y0, int x1, int y1, Color c) {	// x��� ������ line
	if (x0 < x1) {
		for (int i = 0; i <= x1 - x0; i++) {			// ���ʿ��� ������
			FrameBuffer::SetPixel(x0 + i, y0, c.r, c.g, c.b);
		}
	}
	else {
		for (int i = 0; i <= x0 - x1; i++) {			// �����ʿ��� ����
			FrameBuffer::SetPixel(x0 - i, y0, c.r, c.g, c.b);
		}
	}
}

void drawHLine(int x0, int y0, int x1, int y1, Color c) {	// y��� ������ line

	if (y0 < y1) {
		for (int i = 0; i <= y1 - y0; i++) {			// �Ʒ����� ��
			FrameBuffer::SetPixel(x0, y0 + i, c.r, c.g, c.b);
		}
	}
	else {
		for (int i = 0; i <= y0 - y1; i++) {			// ������ �Ʒ�
			FrameBuffer::SetPixel(x0, y0 - i, c.r, c.g, c.b);
		}
	}
}

void drawVDLine(int x0, int y0, int x1, int y1, Color c) {		// ���Ⱑ < |1| �� ���

	double m = ((double)(y1 - y0) / (double)(x1 - x0));					// ������ ���׸��� ��� ä��
	double b = ((double)y0 - ((double)(y1 - y0) / (double)(x1 - x0))*x0);


	if (x0 < x1 && y0 < y1) {							// 1��и�
		for (int i = 0; i <= x1 - x0; i++) {
			FrameBuffer::SetPixel(x0 + i, round(m*(x0 + i) + b), c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 < y1) {						// 2��и� ��,x�� �����ϸ鼭 �׷����� ������ i�� ����
		for (int i = 0; i <= x0 - x1; i++) {
			FrameBuffer::SetPixel(x0 - i, round(m*(x0 - i) + b), c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 > y1) {						//3��и� ��,x�� �����ϸ鼭 �׷����� ������ i�� ���� 
		for (int i = 0; i <= x0 - x1; i++) {
			FrameBuffer::SetPixel(x0 - i, round(m*(x0 - i) + b), c.r, c.g, c.b);
		}
	}
	else if (x0 < x1 && y0 > y1) {						//4��и�
		for (int i = 0; i <= x1 - x0; i++) {
			FrameBuffer::SetPixel(x0 + i, round(m*(x0 + i) + b), c.r, c.g, c.b);
		}
	}
}

void drawHDLine(int x0, int y0, int x1, int y1, Color c) {		// ���Ⱑ > |1| �� ���

	double m = (double)(x1 - x0) / (double)(y1 - y0);			// ������ ���׸��� ��� ä��
	double b = ((double)x0 - ((double)(x1 - x0) / (double)(y1 - y0)*y0));

	if (x0 < x1 && y0 < y1) {
		for (int i = 0; i <= y1 - y0; i++) {			//1��и�
			FrameBuffer::SetPixel(round((m*(y0 + i)) + b), y0 + i, c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 < y1) {						//2��и�
		for (int i = 0; i <= y1 - y0; i++) {
			FrameBuffer::SetPixel(round((m*(y0 + i)) + b), y0 + i, c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 > y1) {						//3��и� ��,y�� �����ϸ鼭 �׷����� ������ i�� ����
		for (int i = 0; i <= y0 - y1; i++) {
			FrameBuffer::SetPixel(round((m*(y0 - i)) + b), y0 - i, c.r, c.g, c.b);
		}
	}
	else if (x0 < x1 && y0 > y1) {						//4��и� ��,y�� �����ϸ鼭 �׷����� ������ i�� ����
		for (int i = 0; i <= y0 - y1; i++) {
			FrameBuffer::SetPixel(round((m*(y0 - i)) + b), y0 - i, c.r, c.g, c.b);
		}
	}
}

void DrawLine(Point start, Point end, Color c) {
	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;

	long slope = 0;
	if (x1 != x0) slope = ((double)(y1 - y0) / (double)(x1 - x0));			// ���� ����, �� �� x1-x0 == 0 �ϰ�� inf �߻��ϴ� ����

	if (y0 == y1) {
		drawVLine(x0, y0, x1, y1, c);
	}
	else if (x0 == x1) {
		drawHLine(x0, y0, x1, y1, c);
	}
	else if (abs(slope) <= 1) {						// ���Ⱑ |1|�� ���� HD�� �׷��� VD�� �׷��� �Ȱ���.
		drawVDLine(x0, y0, x1, y1, c);
	}
	else {
		drawHDLine(x0, y0, x1, y1, c);
	}
}

Matrix Translate(const Vector &p)
{
	Matrix m;

	m.m[0][0] = 1.0f; m.m[0][1] = 0.0f; m.m[0][2] = p.x;
	m.m[1][0] = 0.0f; m.m[1][1] = 1.0f; m.m[1][2] = p.y;
	m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f;

	return m;
}
Matrix Scale(const Vector &s)
{
	Matrix m;

	m.m[0][0] = s.x; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f;
	m.m[1][0] = 0.0f; m.m[1][1] = s.y; m.m[1][2] = 0.0f;
	m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f;

	return m;
}
Matrix Rotate(const float &alpha)
{
	Matrix m;

	m.m[0][0] = cos(alpha); m.m[0][1] = -sin(alpha); m.m[0][2] = 0.0f;
	m.m[1][0] = sin(alpha); m.m[1][1] = cos(alpha); m.m[1][2] = 0.0f;
	m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f;

	return m;
}
Vector matpoiMul(const Matrix &m, const Point &p)
{
	Vector result;

	result.x = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2];
	result.y = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2];
	float w = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2];

	result.x /= w;
	result.y /= w;

	return result;
}
Matrix matmatMul(const Matrix &m1, const Matrix &m2)
{
	Matrix result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}
Vector CameraToViewport(Point point) {		// ����Ʈ�� ����
	float viewportPointX, viewportPointY;

	viewportPointX = ((float)WIDTH / (float)CAMERA_WIDTH)*(float)(point.x) + ((float)WIDTH / 2);
	viewportPointY = (-1)*(float)(HEIGHT / (float)CAMERA_HEIGHT)*(float)(point.y) + ((float)HEIGHT / 2);
	return Vector(viewportPointX, viewportPointY);

	/////
}
