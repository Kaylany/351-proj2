#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include<algorithm>

using namespace std;



struct process {
	int number;
	int starttime;
	int finishtime;
	int numberofBlocks;
	vector<int> blockofsize;
};
struct memoryblock {
	int start;
	int end;
	int processnumber;
	int pagenumber;
	bool free;
};


void readfile(string file, vector<process>& processlist)
{
	int numberOfprocess;
	process temp;
	ifstream filein;
	filein.open("in1.txt");
	if (filein.fail())
	{
		cout << "Can't open the file";
		
	}
	filein >> numberOfprocess;
	for (int i = 0; i < numberOfprocess; i++)
	{
		filein >> temp.number;
		filein >> temp.starttime;
		filein >> temp.finishtime;
		filein >> temp.numberofBlocks;
		vector<int> tempblock;
		int block;

		for (int j = 0; j < temp.numberofBlocks; j++)
		{
			filein >> block;
			tempblock.push_back(block);
		}

		temp.blockofsize = tempblock;
		processlist.push_back(temp);
	}
	filein.close();
}

//calc the time
void processtime(vector<process> &processlist, vector<int> &time)
{
	bool temp1 =false, temp2 = false;

	for (int i = 0; i < processlist.size(); i++)
	{
		//temp1 = false;
		//temp2 = false;
		for (int j = 0; j < time.size(); j++)
		{
			if (processlist[i].starttime == time[i])
			{
				temp1 = true;
				if (processlist[i].starttime + processlist[i].finishtime == time[j])
					temp2 = true;
}
		}
		if (temp1 == false)
		{
			time.push_back(processlist[i].starttime);
		}
		if (temp2 == false)
			time.push_back(processlist[i].starttime + processlist[i].finishtime);
	}
	//sort the order using sort() function
	sort(time.begin(), time.end());
}

void mapdisplay(vector<memoryblock> &memorymap, int memorysize, int pagesize)
{
	int num=0, start = 0, end = 0, processnumber = 0, pagenumber = 0;
	cout << " Memory Map: " << endl;

	while (num < (memorysize / pagesize))
	{
		if (!memorymap[num].free)
		{
			if (start != 0)
			{
				end = num - 1;
				cout << "   " << start * pagesize << "-" << ((end + 1)*pagesize) - 1 << ": Free frame(s)" << endl;
				start = 0;
			}
			cout << "    " << memorymap[num].start << "-" << memorymap[num].end << " :Process " << memorymap[num].processnumber << " ,Page " << memorymap[num].pagenumber << endl;
		}
		else if (start = 0)
			start = num;
		num++;
	}
	if (start != 0)
	{
		end = num - 1;
		cout << "    " << start * pagesize << "-" << ((end + 1)*pagesize) - 1 << ": Free frame(s)" << endl;
	}

}

void out(vector<process> &processlist, vector<int> &time,int memorysize,int pagesize)
{
	int temp;
	process temp2;
	vector<memoryblock> memorymap;
	vector<int> inqueue;
	memoryblock line;


	//init memory map
	for (int i = 0; i < (memorysize / pagesize); i++)
	{
		line.start = i * pagesize;
		line.end = ((i + 1)*pagesize) - 1;
		line.processnumber = -1;
		line.pagenumber = -1;
		line.free = true;
		memorymap.push_back(line);
	}

	//process loop
	for (int i = 0; i < time.size(); i++)
	{
		//output time
		cout << " t= " << time[i] << " : ";

		//add new process
		for (int j = 0; j < processlist.size(); j++)
		{
			if (processlist[j].starttime == time[i])
			{
				inqueue.push_back(processlist[j].number);
				cout << "Process " << processlist[j].number << " arrive" << endl;
				cout << " Input Queue: [";
				for (int k = 0; k < inqueue.size(); k++)
					cout << inqueue[k] << " ";
				cout << "]" << endl;
			}
			else if (processlist[j].starttime + processlist[j].finishtime == time[i])
			{
				cout << "process " << processlist[j].number << " complete" << endl;
				for (int i = 0; i < memorymap.size(); i++)
				{
					if (memorymap[i].processnumber == processlist[j].number)
					{
						memorymap[i].free = true;
					}
				}
				mapdisplay(memorymap, memorysize, pagesize);
			}
		}
		//add process to memory map

	}
}



int main() {

	int memomrySize = 0;
	int pageSize = 0;
	int numOfBlock;

	cout << "Enter memory size (kb): " << endl;
	cin >> memomrySize;

	cout << "Enter page size (1:100, 2:200, 3:300): " << endl;
	cin >> pageSize;
	if (pageSize == 1)
	{
		pageSize = 100;
	}
	else if (pageSize == 2)
	{
		pageSize = 200;
	}
	else if (pageSize == 3)
	{
		pageSize = 300;
	}

	vector<process> processlist;
	vector<int> time;

	string file = "in1.txt";
	readfile(file, processlist);
	processtime(processlist, time);
	out(processlist, time, memomrySize, pageSize);

	return 0;
}
