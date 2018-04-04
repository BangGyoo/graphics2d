#pragma once

#include "Utilities.h"
#include "Shape.h"

typedef Point Vector;

class Point {
public :
	float x;
	float y;
	Point(float x=0.0f, float y=0.0f) {
		this->x = x;
		this->y = y;
	}
};
class Line {
public :
	Point start;
	Point end;
	Line(Point &start,Point &end) {
		this->start = start;
		this->end = end;
	}
};

void DrawLine(Point start, Point end, Color c) {
	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;

	long slope = 0;
	if (x1 != x0) slope = ((double)(y1 - y0) / (double)(x1 - x0));			// ���� ����, �� �� x1-x0 == 0 �ϰ�� inf �߻��ϴ� ����

	if (y0 == y1) {
		drawVLine(x0, y0, x1, y1,c);
	}
	else if (x0 == x1) {
		drawHLine(x0, y0, x1, y1,c);
	}
	else if (abs(slope) <= 1) {						// ���Ⱑ |1|�� ���� HD�� �׷��� VD�� �׷��� �Ȱ���.
		drawVDLine(x0, y0, x1, y1,c);
	}
	else {
		drawHDLine(x0, y0, x1, y1,c);
	}
}

void drawVLine(int x0, int y0, int x1, int y1,Color c) {	// x��� ������ line
	if (x0 < x1) {
		for (int i = 0; i <= x1 - x0; i++) {			// ���ʿ��� ������
			FrameBuffer::SetPixel(x0 + i, y0, c.r , c.g, c.b);
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

	double m = ((double)(y1 - y0) / (double)(x1 - x0));					// ����� ���׸��� ��� ä��
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

	double m = (double)(x1 - x0) / (double)(y1 - y0);			// ����� ���׸��� ��� ä��
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
