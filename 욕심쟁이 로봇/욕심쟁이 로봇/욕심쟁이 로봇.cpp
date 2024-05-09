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
		
		for (int k = 0; k < strlen(direction); k++) {		// ��� ��ȣ�� ���� ��ܿ��� ���� �����Ͽ� ���������� �����ϴ� ����
			char ch = direction[k];
			switch (ch) {
				case 'E':
					graph.push_back(Edge{ i, i + 1, cost });
					break;
				case 'S':									// ������ mapSize ��ŭ ���� ���� �̵��Ͽ� �ٷ� �Ʒ��� ����Ŵ
					graph.push_back(Edge{ i, i + mapSize, cost });
					break;
				case 'W':
					graph.push_back(Edge{ i, i - 1, cost });
					break;
				case 'N':									// ������ mapSize ��ŭ �� ���� �̵��Ͽ� �ٷ� ���� ����Ŵ
					graph.push_back(Edge{ i, i - mapSize, cost });
					break;
			}

		}

	}

	
	cout << "������ �׷��� : " << endl;

	for (int i = 0; i < graph.size(); i++)
		cout << "{ " << graph[i].src << ", " << graph[i].dst << ", " << graph[i].cost << " }" << endl;

	GreedyRobot(graph, node_count);


}

void GreedyRobot(vector<Edge>& graph, int node_count) {


	vector<int> distance(node_count, INFINITY);
	int result = 0;

	distance[0] = 0;

	for (int i = 0; i < node_count - 1; i++) {				// ���� ���� �˰��� ����
	
		for (int k = 0; k < graph.size(); k++) {
			Edge e = graph[k];

			if (distance[e.src] == INFINITY)
				continue;

			int dist = distance[e.src] + e.cost;

			if (distance[e.dst] < dist)
				distance[e.dst] = dist;

		}

	}

	for (int k = 0; k < graph.size(); k++) {				// ������ �� ��� (���� ����Ŭ�� �߻��� ���)
		Edge e = graph[k];

		if (distance[e.src] == INFINITY)
			continue;

		int dist = distance[e.src] + e.cost;

		if (distance[e.dst] < dist){
			cout << "Ž�� �ߴ�" << endl;
			return;
		}

	}

	cout << distance[node_count - 1] << endl;
}