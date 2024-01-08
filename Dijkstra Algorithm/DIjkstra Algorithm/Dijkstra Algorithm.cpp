#include <iostream>
#include <vector>
#include <queue>

#define MAX_NODE 1001
#define INFINITY 0x7FFFFFFF

using namespace std;

struct Edge {
	int src;
	int dst;
	int cost;		   
};

struct Node{
	int id;
	int cost;

	friend bool operator<(const Node& n1, const Node& n2);
	friend bool operator>(const Node& n1, const Node& n2);
};

bool operator<(const Node& n1, const Node& n2) {
	return n1.cost < n2.cost;
}

bool operator>(const Node& n1, const Node& n2) {
	return n1.cost > n2.cost;
}

vector<Edge> graph[MAX_NODE];
priority_queue<Node, vector<Node>, greater<Node>> heap;
char visited[MAX_NODE] = { 0, };
int parent[MAX_NODE] = {0, };

int dijkstra(int node_count, int target);

int main() {
	// �׽�Ʈ ���̽�
	/*
	8 12
	1 2 2
	1 5 3
	2 4 1
	2 5 5
	5 4 2
	5 8 3
	4 8 5
	4 6 4
	4 3 2
	8 6 1
	3 7 3
	6 7 4
	6
	*/


	int node_count, edge_count;

	cin >> node_count >> edge_count;

	for (int i = 0; i < edge_count; i++) {
		int src, dst, cost;
		cin >> src >> dst >> cost;
		graph[src].push_back(Edge{ src, dst, cost });
		graph[dst].push_back(Edge{ dst, src, cost });
	}
	
	int target;
	cin >> target;

	dijkstra(node_count, target);												// 1������ target���� ���ϴ� dijkstra

}

int dijkstra(int node_count, int target) {
	int result = 0;
	unsigned shortest[MAX_NODE] = { 0, };
	
	memset(shortest, INFINITY, sizeof(shortest));
	shortest[1] = 0;

	heap.push(Node{ 1, 0 });

	while(heap.empty() == false){												// ���� �׻� �ּ� ������ ������.
		Node curNode = heap.top();

		if (visited[curNode.id] == 0) {											// �湮���� ���� ����̸�
			visited[curNode.id] = 1;											// �湮

			for(int i = 0; i < graph[curNode.id].size(); i++){					// �湮�� ����� ��� ������ ����Ѵ�
				int dstNode = graph[curNode.id][i].dst;
				int minDist = curNode.cost + graph[curNode.id][i].cost;			// ���� ���� ��, ���� �Ÿ� ���

				if (minDist < shortest[dstNode]){								// �ּ� �Ÿ��� ���
					shortest[dstNode] = minDist;								// �ּ� �Ÿ��� ���
					heap.push(Node{ dstNode, minDist });
					parent[dstNode] = curNode.id;
				}
				
			}
			
		}
		heap.pop();																// ��带 ��������Ƿ� ����
	}

	for (int i = 1; i <= node_count; i++)
		cout << shortest[i] << " ";


	cout << endl;

	vector<unsigned> route;

	int back_tracking = target;
	route.push_back(back_tracking);

	while (back_tracking != 1){
		back_tracking = parent[back_tracking];									// �� Ʈ��ŷ
		route.push_back(back_tracking);
	}
	
	for (int i = route.size() - 1; i >= 0 ; i--)
		cout << route[i] << " ";

	return result;

}