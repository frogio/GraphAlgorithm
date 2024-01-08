#include <iostream>
#include <queue>
#include <vector>
#include <memory.h>

using namespace std;

#define MAX_NODE 1001
#define INFINITY 0x7FFFFFFF

struct Edge {
	int src;
	int dst;
	int cost;

	friend bool operator<(const Edge& e1, const Edge e2);
	friend bool operator>(const Edge& e1, const Edge e2);
};

bool operator<(const Edge& e1, const Edge e2) {
	return e1.cost < e2.cost;
}
bool operator>(const Edge& e1, const Edge e2) {
	return e1.cost > e2.cost;
}

int MST[MAX_NODE][MAX_NODE];
int graph[MAX_NODE][MAX_NODE];
int visited[MAX_NODE] = { 0, };
priority_queue<Edge, vector<Edge>, greater<Edge>> heap;

void addEdge(int node, int node_count);
int prim(int node_count);

int main() {

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
	memset(graph, 0, sizeof(graph));

	int computer, line;
	cin >> computer;
	cin >> line;

	for (int i = 0; i < line; i++) {
		int src, dst, cost;
		cin >> src >> dst >> cost;
		graph[src][dst] = cost;
		graph[dst][src] = cost;
	}

	cout << prim(computer) << endl;

	return 0;
}

void addEdge(int node, int node_count) {

	for (int i = 1; i <= node_count; i++) {
		if (graph[node][i] != 0)
			heap.push(Edge{node, i, graph[node][i] });
	}

}
int prim(int node_count) {
	int result = 0;

	heap.push(Edge{ 1, 1, 0 });

	for(int i = 0; i < node_count; i++){			// 모든 노드에 대해 반복

		int dist = INFINITY;

		while (heap.empty() == false) {				// 엣지 선택
			Edge curEdge = heap.top();

			if (visited[curEdge.dst] == 0) {		// 방문하면
				visited[curEdge.dst] = 1;
				dist = curEdge.cost;				// 엣지 선택
				MST[curEdge.src][curEdge.dst] = dist;
				MST[curEdge.dst][curEdge.src] = dist;
				addEdge(curEdge.dst, node_count);
				break;
			}

			 heap.pop();							// 재방문 시 이미 엣지가 선택되었으므로 엣지 제거
		
		}

		if (dist == INFINITY)
			return INFINITY;

		result += dist;

	}

	cout << endl;

	for (int i = 1; i <= node_count; i++) {
		
		for (int k = 1; k <= node_count; k++)
			cout << MST[i][k] << " ";
		
		cout << endl;
	}

	return result;
}