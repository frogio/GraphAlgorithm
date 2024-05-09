#include <iostream>
#include <vector>
#include <memory.h>

#define INFINITY 0x7f7f7f7f

using namespace std;

struct Edge{
	int src;
	int dst;
	int cost;
};

void BellmanFord(vector<Edge> & graph, int node_count);

void main() {
	
	vector<Edge> graph;
	/* 음수 사이클이 발생하지 않은 예
	graph.push_back(Edge{ 0, 1, 3 });
	graph.push_back(Edge{ 1, 2, 5 });
	graph.push_back(Edge{ 1, 3, 10});
	graph.push_back(Edge{ 3, 2, -7 });
	graph.push_back(Edge{ 2, 4, 2});
	*/

	graph.push_back(Edge{ 0, 1, 3 });
	graph.push_back(Edge{ 1, 3, -8 });
	graph.push_back(Edge{ 2, 1, 3 });
	graph.push_back(Edge{ 2, 5, 5 });
	graph.push_back(Edge{ 3, 2, 3 });
	graph.push_back(Edge{ 2, 4, 2 });
	graph.push_back(Edge{ 4, 5, -1 });
	graph.push_back(Edge{ 5, 1, 8 });
	// 음수 사이클이 발생하는 경우

	BellmanFord(graph, 6);

}

void BellmanFord(vector<Edge> &graph, int node_count) {

	vector<int> distance(node_count, INFINITY);
	
	distance[0] = 0;

	for (int i = 0; i < node_count - 1; i++) {
		for (int k = 0; k < graph.size(); k++) {
			Edge e = graph[k];

			if (distance[e.src] == INFINITY)
				continue;

			int dist = distance[e.src] + e.cost;

			if (distance[e.dst] > dist)
				distance[e.dst] = dist;
			
		}
	}

	for (int i = 0; i < graph.size(); i++) {
		Edge e = graph[i];

		if (distance[e.src] == INFINITY)
			continue;

		int dist = distance[e.src] + e.cost;

		if (distance[e.dst] > dist){
			cout << "음수 사이클이 존재합니다!";
			return;
		}
	}

	for (int i = 1; i < distance.size(); i++)
		cout << i << "번 까지의 거리 : " << distance[i] << endl;

}