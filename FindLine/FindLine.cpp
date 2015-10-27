#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

void printOutput(vector<double> params, int freq) {
	double slope = params[0];
	double intercept = params[1];
	if (slope != numeric_limits<double>::infinity()) {
		cout << "Y=";
		if (slope == 0) {
			cout << intercept << ", " << freq << endl;
			return;
		}
		if (slope != 1)
			cout << slope;
		cout << "x+";
		if (intercept != 0)
			cout << intercept;
		cout << ", " << freq << endl;
	}
		
	else
		cout << "X=" << intercept << ", " << freq << endl;
}

void FindLine(vector<vector<int> > allPoints) {
	map<vector<double>, vector<vector<vector<int> > > > Slopes;
	for (int i = 0; i < allPoints.size(); i++) {
		for (int j = i+1; j < allPoints.size(); j++) {
			double X1 = allPoints[i][0];
			double Y1 = allPoints[i][1];
			double X2 = allPoints[j][0];
			double Y2 = allPoints[j][1];

			double slope, intercept;
			if (X1 != X2) {
				slope = (Y2 - Y1) / (X2 - X1);
				intercept = Y1 - X1 * slope;
			}
			else {
				slope = numeric_limits<double>::infinity();
				intercept = X1;
			}

			vector<double> key;
			key.push_back(slope);
			key.push_back(intercept);

			vector<vector<int> > value;
			value.push_back(allPoints[i]);
			value.push_back(allPoints[j]);

			if (Slopes.find(key) == Slopes.end()) {
				vector<vector<vector<int> > > values;
				values.push_back(value);
				Slopes[key] = values;
			}
			else 
				Slopes[key].push_back(value);
		}
	}

	int freq = 0;
	vector<double> params;
	for(map<vector<double>, vector<vector<vector<int> > > >::iterator it = Slopes.begin(); it != Slopes.end(); ++it) {
		if (it->second.size() > freq) {
			params = it->first;
			freq = it->second.size();
		}
	}

	printOutput(params, freq);
}

int main(int argc, char const *argv[]){
    ifstream file;
    file.open(argv[1]);
    string temp;
    int numberOfPoints = int(getline(file, temp));
    vector<vector<int> > allPoints;
    while (getline(file, temp)) {
    	int commaIndex = temp.find(",");
    	int X = stoi(temp.substr(1, commaIndex-1));
     	int Y = stoi(temp.substr(commaIndex+1, temp.size()-commaIndex-2));
    	vector<int> point;
    	point.push_back(X);
    	point.push_back(Y);
    	allPoints.push_back(point);
    }
    FindLine(allPoints);
}