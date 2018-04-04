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
	if (x1 != x0) slope = ((double)(y1 - y0) / (double)(x1 - x0));			// 기울기 측정, 이 때 x1-x0 == 0 일경우 inf 발생하니 조심

	if (y0 == y1) {
		drawVLine(x0, y0, x1, y1,c);
	}
	else if (x0 == x1) {
		drawHLine(x0, y0, x1, y1,c);
	}
	else if (abs(slope) <= 1) {						// 기울기가 |1|인 것은 HD로 그려도 VD로 그려도 똑같다.
		drawVDLine(x0, y0, x1, y1,c);
	}
	else {
		drawHDLine(x0, y0, x1, y1,c);
	}
}

void drawVLine(int x0, int y0, int x1, int y1,Color c) {	// x축과 수평인 line
	if (x0 < x1) {
		for (int i = 0; i <= x1 - x0; i++) {			// 왼쪽에서 오른쪽
			FrameBuffer::SetPixel(x0 + i, y0, c.r , c.g, c.b);
		}
	}
	else {
		for (int i = 0; i <= x0 - x1; i++) {			// 오른쪽에서 왼쪽
			FrameBuffer::SetPixel(x0 - i, y0, c.r, c.g, c.b);
		}
	}
}

void drawHLine(int x0, int y0, int x1, int y1, Color c) {	// y축과 수평인 line

	if (y0 < y1) {
		for (int i = 0; i <= y1 - y0; i++) {			// 아래에서 위
			FrameBuffer::SetPixel(x0, y0 + i, c.r, c.g, c.b);
		}
	}
	else {
		for (int i = 0; i <= y0 - y1; i++) {			// 위에서 아래
			FrameBuffer::SetPixel(x0, y0 - i, c.r, c.g, c.b);
		}
	}
}

void drawVDLine(int x0, int y0, int x1, int y1, Color c) {		// 기울기가 < |1| 일 경우

	double m = ((double)(y1 - y0) / (double)(x1 - x0));					// 명시적 선그리기 방식 채택
	double b = ((double)y0 - ((double)(y1 - y0) / (double)(x1 - x0))*x0);


	if (x0 < x1 && y0 < y1) {							// 1사분면
		for (int i = 0; i <= x1 - x0; i++) {
			FrameBuffer::SetPixel(x0 + i, round(m*(x0 + i) + b), c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 < y1) {						// 2사분면 단,x가 감소하면서 그려지기 때문에 i는 음수
		for (int i = 0; i <= x0 - x1; i++) {
			FrameBuffer::SetPixel(x0 - i, round(m*(x0 - i) + b), c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 > y1) {						//3사분면 단,x가 감소하면서 그려지기 때문에 i는 음수 
		for (int i = 0; i <= x0 - x1; i++) {
			FrameBuffer::SetPixel(x0 - i, round(m*(x0 - i) + b), c.r, c.g, c.b);
		}
	}
	else if (x0 < x1 && y0 > y1) {						//4사분면
		for (int i = 0; i <= x1 - x0; i++) {
			FrameBuffer::SetPixel(x0 + i, round(m*(x0 + i) + b), c.r, c.g, c.b);
		}
	}
}

void drawHDLine(int x0, int y0, int x1, int y1, Color c) {		// 기울기가 > |1| 일 경우

	double m = (double)(x1 - x0) / (double)(y1 - y0);			// 명시적 선그리기 방식 채택
	double b = ((double)x0 - ((double)(x1 - x0) / (double)(y1 - y0)*y0));

	if (x0 < x1 && y0 < y1) {
		for (int i = 0; i <= y1 - y0; i++) {			//1사분면
			FrameBuffer::SetPixel(round((m*(y0 + i)) + b), y0 + i, c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 < y1) {						//2사분면
		for (int i = 0; i <= y1 - y0; i++) {
			FrameBuffer::SetPixel(round((m*(y0 + i)) + b), y0 + i, c.r, c.g, c.b);
		}
	}
	else if (x0 > x1 && y0 > y1) {						//3사분면 단,y가 감소하면서 그려지기 때문에 i는 음수
		for (int i = 0; i <= y0 - y1; i++) {
			FrameBuffer::SetPixel(round((m*(y0 - i)) + b), y0 - i, c.r, c.g, c.b);
		}
	}
	else if (x0 < x1 && y0 > y1) {						//4사분면 단,y가 감소하면서 그려지기 때문에 i는 음수
		for (int i = 0; i <= y0 - y1; i++) {
			FrameBuffer::SetPixel(round((m*(y0 - i)) + b), y0 - i, c.r, c.g, c.b);
		}
	}
}
