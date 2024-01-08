#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

#define MAX_NODE 264327
#define MAX_EDGE 733847
#define INFINITY 0xFFFFFFFF

#pragma warning(disable:4996)

using namespace std;

struct Edge {					// 인덱스가 src, 다음이 dst, cost
	int dst;
	int cost;
};

struct Node {
	int id;
	int minDist;

	friend bool operator<(const Node& n1, const Node& n2);
	friend bool operator>(const Node& n1, const Node& n2);
};

bool operator<(const Node& n1, const Node& n2) {
	return n1.minDist < n2.minDist;
}
bool operator>(const Node& n1, const Node& n2) {
	return n1.minDist > n2.minDist;
}

vector<Edge> graph[MAX_EDGE];
char visited[MAX_NODE] = { 0, };
priority_queue<Node, vector<Node>, greater<Node>> heap;
int parent[MAX_NODE] = { 0, };


void LoadGraph();
void SearchPath(int start, int dst);

void main() {
	LoadGraph();
	printf("Load Complete\n");
	/*
	printf("Loaded Result\n");

	for (int i = 1; i <= MAX_EDGE; i++) {
		for (int k = 0; k < graph[i].size(); k++)
			printf("%d - %d : %d\n",i, graph[i][k].dst,  graph[i][k].cost);
	}
	*/
	vector<unsigned> route;

	SearchPath(913, 542);
	int target = 542;
	route.push_back(target);

	while (target != 913) {
		target = parent[target];
		route.push_back(target);
	}

	for (int i = route.size() - 1; i >= 0; i--)
		printf("%d ", route[i]);


}

void LoadGraph() {
	FILE* fp = fopen("USA-road-d.NY.gr", "rt");

	if (fp == NULL){
		printf("error occured!, while open file\n");
		return;
	}

	char buf[100] = {0, };
	char * token;
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		
		if (buf[0] ==  'a') {						// 첫번째 문자가 a 일 때 그래프 정보임
			int src, dst, cost;
			token = strtok(buf, " ");				// a 반환
			
			token = strtok(NULL, " ");				// 노드 1
			src = atoi(token);

			token = strtok(NULL, " ");				// 노드 2
			dst = atoi(token);

			token = strtok(NULL, " ");				// 가중치
			cost = atoi(token);

			graph[src].push_back(Edge{ dst, cost });
		}

	}

	fclose(fp);
}

void SearchPath(int start, int dst) {
	unsigned * shortest = (unsigned*)malloc(sizeof(unsigned) * MAX_NODE);

	memset(shortest, INFINITY, sizeof(shortest));
	shortest[start] = 0;
	heap.push(Node{ start, 0 });

	while (heap.empty() == false) {
		Node curNode = heap.top();
		heap.pop();
		
		if (curNode.id == dst){
			free(shortest);
			return;
		}

		if(visited[curNode.id] == 0){
			visited[curNode.id] = 1;
			for (int i = 0; i < graph[curNode.id].size(); i++) {				// 현재 노드의 모든 엣지를 검사
				int dstNode = graph[curNode.id][i].dst;
				int minDist = curNode.minDist + graph[curNode.id][i].cost;		// 현재 노드의 이웃 노드까지 가는데에 걸리는 비용을 누적

				if (minDist < shortest[dstNode]) {
					shortest[dstNode] = minDist;
					heap.push(Node{ dstNode, minDist });
					parent[dstNode] = curNode.id;
				}

			}
		}

	}
	free(shortest);

}