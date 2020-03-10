#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>

#define inf (1e-10)
#define equal_(a, b) (fabs(a - b) < inf)

using namespace std;

class Point {

public:

	double x, y;

	Point(double a, double b) {
		x = a;
		y = b;
	}

	bool operator<(const Point& p) const {
		if (equal_(x, p.x) && equal_(y, p.y)) {
			return false;
		}
		if (!equal_(x, p.x)) {
			return x < p.x;
		}
		else {
			return y < p.y;
		}
	}

};

class Line {

public:

	double a, b, c;

	Line(double x0, double y0, double x1, double y1) {
		//将直线的ax+by+c=0中的系数求出
		a = y1 - y0;
		b = x0 - x1;
		c = x1 * y0 - x0 * y1;
	}

	Line(double a0, double b0, double c0) {
		a = a0;
		b = b0;
		c = c0;
	}

	bool parallel(Line l) {
		return (l.a * b == l.b * a);
	}

	void intersect(set<Point>* intersections, Line l) {
		if (parallel(l)) return;
		else {
			intersections->insert(getLLintersection(l));
		}
	}

	Point getLLintersection(Line l) {
		double x = (l.c * b - c * l.b) / (a * l.b - l.a * b);
		double y = (l.a * c - a * l.c) / (a * l.b - l.a * b);
		return Point(x, y);
	}
};

class Circle {

public:

	double x, y, r;

	Circle(double x1, double y1, double r1) {
		x = x1;
		y = y1;
		r = r1;
	}

	bool sameCenter(Circle c) {
		if (x == c.x && y == c.y) return true;
		else return false;
	}

	double line2circle(Line l) {
		return abs(l.a * x + l.b * y + l.c) / sqrt(l.a * l.a + l.b * l.b);
	}

	void intersectwithline(set<Point>* intersections, Line l) {
		double dis = line2circle(l);
		if (dis > r) return;
		//先找到圆心在直线上的投影点,用与直线垂直的线做交点得到
		Line l_(l.b, -l.a, y * l.a - x * l.b);
		Point p = l_.getLLintersection(l);
		if (dis < r) {
			double delta_x = sqrt((r * r - dis * dis) * l.b * l.b / (l.a * l.a + l.b * l.b));
			double k = -(l.a / l.b);
			Point p1(p.x + delta_x, p.y + k * delta_x);
			Point p2(p.x - delta_x, p.y - k * delta_x);
			intersections->insert(p1);
			intersections->insert(p2);
		}
		else {
			intersections->insert(p);
			return;
		}
	}

	vector<Point> get_c_l(Line l) {
		
		vector<Point> re;
		double dis = line2circle(l);
		if (dis > r) return re;
		//先找到圆心在直线上的投影点,用与直线垂直的线做交点得到
		Line l_(l.b, -l.a, y * l.a - x * l.b);
		Point p = l_.getLLintersection(l);
		if (dis < r) {
			if (l.b == 0) {
				Point p1(p.x, p.y + sqrt(r * r - dis * dis));
				Point p2(p.x, p.y - sqrt(r * r - dis * dis));
				re.push_back(p1);
				re.push_back(p2);
				return re;
			}
			else {
				double delta_x = sqrt((r * r - dis * dis) * l.b * l.b / (l.a * l.a + l.b * l.b));
				double k = -(l.a / l.b);
				Point p1(p.x + delta_x, p.y + k * delta_x);
				Point p2(p.x - delta_x, p.y - k * delta_x);
				re.push_back(p1);
				re.push_back(p2);
				return re;
			}
		}
		else {
			re.push_back(p);
			return re;
		}
	}

	double min(double a, double b) {
		return a < b ? a : b;
	}

	double max(double a, double b) {
		return a > b ? a : b;
	}

	void interscetwithcircle(set<Point>* intersections, Circle c) {
		if (sameCenter(c)) return;
		double dis_center = sqrt((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y));
		//外离
		if (dis_center > r + c.r) return;
		//包含
		if (dis_center < max(r, c.r) - min(r, c.r)) return;
		//有交点
		double a_ = -2 * (x - c.x);
		double b_ = -2 * (y - c.y);
		double c_ = x * x + y * y - r * r - c.x * c.x - c.y * c.y + c.r * c.r;
		Line l_(a_, b_, c_);
		intersectwithline(intersections, l_);
	}

	vector<Point> get_c_c(Circle c) {

		vector<Point> re;
		double dis_center = sqrt((x - c.x) * (x - c.x) + (y - c.y) * (y - c.y));
		//外离
		if (dis_center > r + c.r) return re;
		//包含
		if (dis_center < max(r, c.r) - min(r, c.r)) return re;
		//有交点
		double a_ = -2 * (x - c.x);
		double b_ = -2 * (y - c.y);
		double c_ = x * x + y * y - r * r - c.x * c.x - c.y * c.y + c.r * c.r;
		Line l_(a_, b_, c_);
		re = get_c_l(l_);
		return re;
	}

};