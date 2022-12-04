#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>
using namespace std;

void dfs_inverse(vector <list <int> > g, vector <bool> & used, int v, vector <int> & path)
{
	used[v] = true;
	for (int u = 0; u < g.size(); u++)
		for (int w : g[u])
			if (w == v && !used[u])
				dfs_inverse(g, used, u, path);
	path.push_back(v);
}

void find_path(vector <list <int> > g, vector <int> & path)
{
	vector <bool> used(g.size(), false);
	for (int u = 0; u < g.size(); u++)
		if (!used[u])
			dfs_inverse(g, used, u, path);
}

void find_component(vector <list <int>> g, vector <int> & path, int v, int & kn, int & next, vector <int> & ind, vector <int> & pre, vector <int> & low, list <int> & s, vector <int> & component)
{
	path.erase(find(path.begin(), path.end(), v));
	pre[v] = next;
	low[v] = next;
	next++;
	s.push_front(v);
	for (int w : g[v])
		if (pre[w] < 0)
		{
			find_component(g, path, w, kn, next, ind, pre, low, s, component);
			low[v] = min(low[v], low[w]);
		}
		else
			if (find(s.begin(), s.end(), w) != s.end())
				low[v] = min(low[v], low[w]);
	if (low[v] == pre[v])
	{
		while (s.front() != v)
		{
			ind[s.front()] = kn;
			component.push_back(s.front());
			s.pop_front();
		}
		ind[s.front()] = kn;
		component.push_back(s.front());
		s.pop_front();
		kn++;
	}
}

void taryan_strong(vector <list <int>> g, vector <vector <int> > & components)
{
	vector <int> path;
	find_path(g, path);
	int kn = 1;
	int next = 0;
	vector <int> ind(g.size(), -1);
	vector <int> pre(g.size(), -1);
	vector <int> low(g.size(), g.size());
	list <int> s;
	while (!path.empty())
		if (pre[path.back()] < 0)
		{
			vector <int> component;
			int v = path.back();
			find_component(g, path, v, kn, next, ind, pre, low, s, component);
			components.push_back(component);
		}
}

int main()
{
	srand(time(0));
	ofstream outFile;
  outFile.open("out.txt");
	int n = rand() % 499 + 2;
	outFile << n;
	vector <list <int>> g(n);
	int a, b;
	int m = rand() % (n*(n-1)) + n - 1;
	outFile << " " << m;
	for (int i = 0; i < n - 1; i++)
	{
		a = rand() % 2 + i;
		b = 2*i - a + 1;
		g[a].push_back(b);
	}
	for (int i = 0; i < m - n + 1; i++)
	{
		a = rand() % n;
		b = rand() % n;
		g[a].push_back(b);
	}
	vector <vector <int>> components;
	auto start = clock();
	taryan_strong(g, components);
	auto end = clock();
	outFile <<" "<< end - start << endl;
	outFile.close();
	system("pause");
	return 0;
}
