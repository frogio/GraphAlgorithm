#include <iostream>
#include <queue>
#include <vector>

#define MAX_NODE	1001
#define INFINITY	0x7FFFFFFF

using namespace std;

struct Edge {
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

vector<Edge> graph;
char visited[MAX_NODE] = { 0, };
priority_queue<Edge, vector<Edge>, greater<Edge>> heap;

void addEdge(int node);
int prim(int node_count);

void main() {
	/*
	 백준 1922 네트워크 연결 Test Case
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

	답 : 23
	*/
	int computer, line;
	cin >> computer;
	cin >> line;

	for (int i = 0; i < line; i++) {
		int src, dst, cost;
		cin >> src >> dst >> cost;
		graph.push_back(Edge{src, dst, cost });
		graph.push_back(Edge{dst, src, cost });
	}

	cout << prim(computer) << endl;


}

void addEdge(int node) {

	for (int i = 0; i < graph.size(); i++) {
		if (node == graph[i].src)
			heap.push(graph[i]);
	}

}

int prim(int node_count) {

	int result = 0;
	vector<Edge> MST;

	heap.push(Edge{ 1, 1, 0 });

	for (int i = 0; i < node_count; i++) {
		int curNode = 0;
		int dist = INFINITY;

		while (heap.empty() == false){					// 최소 힙이므로 항상 최소 Edge를 보장
			Edge curEdge = heap.top();

			if (visited[curEdge.dst] == 0) {			// 방문 하면
				visited[curEdge.dst] = 1;
				MST.push_back(curEdge);					// 엣지 선택 후,
				addEdge(curEdge.dst);					// 나머지 엣지 추가
				dist = curEdge.cost;
				break;
			}

			heap.pop();									// 이미 엣지가 선택되었으므로 heap에서 제거
		}

		if (dist == INFINITY)
			return INFINITY;

		result += dist;

	}

	cout << "MST" << endl;

	for (int i = 0; i < MST.size(); i++)
		cout << " { " << MST[i].src << ' ' << MST[i].dst << " : " << MST[i].cost << " } " << endl;

	return result;
}

