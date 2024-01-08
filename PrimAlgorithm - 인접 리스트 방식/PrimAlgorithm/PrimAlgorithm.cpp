#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_NODE 1001
#define INFINITY 0x7FFFFFFF
struct Edge{
	int src;
	int dst;
	int cost;

	friend bool operator<(const Edge& e1, const Edge& e2);
	friend bool operator>(const Edge& e1, const Edge& e2);

};

bool operator<(const Edge& e1, const Edge& e2) {
	return e1.cost < e2.cost;
}

bool operator>(const Edge& e1, const Edge& e2) {
	return e1.cost > e2.cost;
}


vector<Edge> graph[MAX_NODE];
priority_queue<Edge, vector<Edge>, greater<Edge>> heap;
char visited[MAX_NODE] = { 0, };

void addEdge(int node);
int prim(int node_count);

void main() {
	/*
		���� 1922 ��Ʈ��ũ ���� Test Case
		6
		9
		1 2 5
		1 3 4
		2 3 2
		2 4 7
		3 4 6
		3 5 11
		4 5 3
		4 6 8
		5 6 8
		
		�� : 23
	*/

	int computer, line;
	cin >> computer;
	cin >> line;

	for (int i = 0; i < line; i++) {
		int src, dst, cost;
		cin >> src >> dst >> cost;
		graph[src].push_back(Edge{ src, dst, cost });
		graph[dst].push_back(Edge{ dst, src, cost });
	}

	cout << prim(computer) << endl;

}

void addEdge(int node) {
	
	for (int i = 0; i < graph[node].size(); i++)
		heap.push(graph[node][i]);

}

int prim(int node_count) {
	int result = 0;

	vector<Edge> MST;
	heap.push(Edge{1, 1, 0 });

	for (int i = 0; i < node_count; i++) {
		int curNode, minDist = INFINITY;

		while (heap.empty() == false) {					// heap�� �׻� �ּ� ���� ����
			Edge curEdge = heap.top();

			if (visited[curEdge.dst] == 0) {				// �湮�ϸ�
				visited[curEdge.dst] = 1;
				minDist = curEdge.cost;						// ������ �ٷ� ���� ��,

				if(curEdge.src != curEdge.dst)
					MST.push_back(curEdge);

				addEdge(curEdge.dst);						// �ڽ��� ���� �߰�
				break;
			}
		
			heap.pop();									// �̹� �湮�ߴٸ�, ������ �̹� ���õǾ����Ƿ� ������ ������ ���� ����
		}

		if (minDist == INFINITY)
			return INFINITY;

		result += minDist;
	}

	cout << "MST Result" << endl;
	for (int i = 0; i < MST.size(); i++)
		cout << "{ " << MST[i].src << ' ' << MST[i].dst << " : " << MST[i].cost << " }" << endl;

	return result;

}