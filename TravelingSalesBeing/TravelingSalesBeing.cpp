// TravelingSalesBeing.cpp 
// Barrett Koster 2023
/*
  This program solves the Traveling SalesBeing problem.  It will
  make random cities (and assumes that all connections are possible,
  distance of edge is just distance).  Or it can read a data file
  with city xy coordinates.
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

struct City
{
	char name;
	double x, y;
	bool visited;
};


struct Path
{
	vector<City*> cities; // at least one
	double dist; // includes the dist back to the first city
};

void print(Path& p)
{
	cout << p.dist << " : ";
	for(City* pc : p.cities)
	{
		cout << pc->name <<" ";
	}
	cout << endl;
}

// ask user for filename.  read file "city x y "
// allocate and load the vector
vector<City*>* load()
{
	vector<City*>* pv;
	pv = new vector<City*>;
	string filename;
	cout << "file to load? ";
	cin >> filename;

	ifstream fin(filename);
	if(!fin.is_open()) { cout << "file open error\n\n";  }
	else
	{
		string line;
		getline(fin, line);
		while(!fin.eof())
		{ 
			stringstream ss(line);
			char name;
			ss >> name;
			double x, y;
			ss >> x >> y;
			City* pc = new City{name,x,y};
			pv->push_back(pc);
			getline(fin, line);
        }
	}
	return pv;
}

// short name function to generate random doubles 0-1000
double r()
{
	return (double)(rand() % 1000);
}

vector<City*>* makeCities(int n)
{
	char name = 'A';
	vector<City*>* pw = new vector<City*>;
	for(int i = 0; i < n; i++)
	{
		City* pc = new City{ name++, r(), r(), false };
		pw->push_back(pc);
	}
	return pw;
}

void print(vector<City*>* pw)
{
	for(City* pc : *pw)
	{
		cout << pc->name << " "
			<< pc->x << " "
			<< pc->y << " "
			<< pc->visited << " "
			<< endl;
	}
}

void unvisitAll(vector<City*>* pw)
{
	for(City* pc : *pw) { pc->visited = false; }
}

void deal(vector<City*>* pw)
{
	for(City* pc : *pw) { delete pc; }
	delete pw;
}

City* find(vector<City*>* pw, char name)
{
	City* found = nullptr;
	for(City* pc : *pw) { if(pc->name==name) { found=pc; break; } }
	return found;
}

// return the distance between these two cities
double tween(City* a, City* b)
{
	double difx = a->x - b->x;
	double dify = a->y - b->y;
	double d = sqrt( difx* difx + dify*dify );
	return d;
}

// find the best path from pc to #togo remaining unvisited
// cities and back to the first city.  return it.
Path tsbr(vector<City*>* pw, City* pc, int togo)
{
	Path bestPath;
    if (togo == 0)
    {
        // Add the starting city to complete the path
        bestPath.dist = tween(pc, pw->front()); // Distance back to the starting city
        return bestPath;
    }

    // Try visiting each unvisited city
    for (City* dest : *pw)
    {
        if (!dest->visited)
        {
            dest->visited = true;

            // Recursive call to find the best path from dest to remaining cities
            Path currentPath = tsbr(pw, dest, togo - 1);
            
            // Update the current path with the distance to dest
            currentPath.dist += tween(pc, dest);
            currentPath.cities.push_back(dest);

            // If the current path is shorter than the best known path, update it
            if (bestPath.cities.empty() || currentPath.dist < bestPath.dist)
            {
                bestPath = currentPath;
            }

            // Backtrack: mark the current city as unvisited for other possibilities
            dest->visited = false;
        }
    }
    
    return bestPath;
}

// solve the traveling salesbeing problem and print the answer.
void tsb(vector<City*>* pw)
{
	City* pc = pw->front(); // pick the first City
	pc->visited = true;
	Path thePath = tsbr(pw, pc, pw->size() - 1);
    thePath.cities.push_back(pc);
	print(thePath);
}



int main()
{
    cout << "Traveling Sales Being\n";
	srand((int)time(0));

	cout << "How many cities? (-1 for data file) ";
	int many;
	cin >> many;

	vector<City*>* pw;
	if(many == -1) { pw = load(); }
	else           { pw = makeCities(many); }

	print(pw);

	tsb(pw);

	// clean up
	deal(pw);
}
