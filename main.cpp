// 

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

struct process {
	int processId;
	int arrivalTime;
	int lifeTime;
	int memoryRequest;
	int numOfBlock;
	int sum;
	int timeFinished;

};

vector <process> processList;


int main () {

	int memomrySize = 0;
	int pageSize = 0;
	int numOfBlock;

	cout << "Enter memory size (kb): " << endl;
	cin >> memomrySize;

	cout << "Enter page size (1:100, 2:200, 3:300): " << endl;
	cin >> pageSize;

	cout << "Enter the input file name (with .txt): " << endl;
	cin >> file;

	ifstream file;
	file.open(fileName);

	if (!file) {
		cout << "Unable to open file. " << endl;
		break;
	}

	if (file.is_open()) {
		file >> numberOfProcess;
		process processList;

		for (int i = 0; i < numberOfProcess; i++) {
			file >> processList[i].processId;
			file >> processList[i].arrivalTime >> processList[i].lifeTime;
			file >> processList[i].numOfBlock;

			for (int i = 0; i < numOfBlock; i++) {
				int temp;
				file >> temp;
				processList[i].sum += temp;
			}
		}
	}
	file.close();
}