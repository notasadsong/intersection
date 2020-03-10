#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>
#include "class.h"

using namespace std;

int main(int argc, char* argv[]) {

	ifstream input;
	ofstream output;

	for (int arg = 0; arg < argc; arg++) {
		if ((string)argv[arg] == "-i") {
			input = ifstream(argv[arg + 1]);
		}
		else if ((string)argv[arg] == "-o"){
			output = ofstream(argv[arg + 1]);
		}
	}

	int n, i;
	vector<Line> lines;
	vector<Circle> circles;
	set<Point> intersections;
	
	input >> n;
	char op;
	double a, b, c, d;
	for (i = 0; i < n; i++) {
		input >> op;
		if (op == 'L') {
			input >> a >> b >> c >> d;
			Line l(a, b, c, d);
			for (auto it : lines) it.intersect(&intersections, l);
			for (auto it : circles) it.intersectwithline(&intersections,l);
			lines.push_back(l);
		}
		else {
			input >> a >> b >> d;
			Circle c(a, b, d);
			for (auto it : lines) c.intersectwithline(&intersections, it);
			for (auto it : circles) it.interscetwithcircle(&intersections, c);
			circles.push_back(c);
		}
	}

	output << intersections.size() << endl;
	
	return 0;
}