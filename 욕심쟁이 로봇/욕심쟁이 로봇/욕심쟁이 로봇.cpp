#include <iostream>
#include <vector>
#include <string.h>

#define INFINITY		-0x7f7f7f7f

using namespace std;

struct Edge {
	int src;
	int dst;
	int cost;
};

void GreedyRobot(vector<Edge> & graph, int node_count);

void main(){

	vector<Edge> graph;
	int mapSize = 0;

	cin >> mapSize;

	int node_count = mapSize * mapSize;

	for (int i = 0; i < node_count - 1; i++) {
		char direction[5] = { 0, };
		int cost;

		cin >> direction >> cost;
		
		for (int k = 0; k < strlen(direction); k++) {		// 노드 번호는 왼쪽 상단에서 부터 시작하여 오른쪽으로 증가하는 방향
			char ch = direction[k];
			switch (ch) {
				case 'E':
					graph.push_back(Edge{ i, i + 1, cost });
					break;
				case 'S':									// 남쪽은 mapSize 만큼 더해 한줄 이동하여 바로 아래를 가리킴
					graph.push_back(Edge{ i, i + mapSize, cost });
					break;
				case 'W':
					graph.push_back(Edge{ i, i - 1, cost });
					break;
				case 'N':									// 북쪽은 mapSize 만큼 빼 한줄 이동하여 바로 위를 가리킴
					graph.push_back(Edge{ i, i - mapSize, cost });
					break;
			}

		}

	}

	
	cout << "생성된 그래프 : " << endl;

	for (int i = 0; i < graph.size(); i++)
		cout << "{ " << graph[i].src << ", " << graph[i].dst << ", " << graph[i].cost << " }" << endl;

	GreedyRobot(graph, node_count);


}

void GreedyRobot(vector<Edge>& graph, int node_count) {


	vector<int> distance(node_count, INFINITY);
	int result = 0;

	distance[0] = 0;

	for (int i = 0; i < node_count - 1; i++) {				// 벨만 포드 알고리즘 시작
	
		for (int k = 0; k < graph.size(); k++) {
			Edge e = graph[k];

			if (distance[e.src] == INFINITY)
				continue;

			int dist = distance[e.src] + e.cost;

			if (distance[e.dst] < dist)
				distance[e.dst] = dist;

		}

	}

	for (int k = 0; k < graph.size(); k++) {				// 과충전 될 경우 (양의 사이클이 발생할 경우)
		Edge e = graph[k];

		if (distance[e.src] == INFINITY)
			continue;

		int dist = distance[e.src] + e.cost;

		if (distance[e.dst] < dist){
			cout << "탐색 중단" << endl;
			return;
		}

	}

	cout << distance[node_count - 1] << endl;
}