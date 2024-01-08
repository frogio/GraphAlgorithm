#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int src;
	int dst;
};

void DFS(int node_count, vector<Edge>& graph, int start_node);

void main() {
	vector<Edge> graph;
	int node_count = 8;
	
	// Node 1
	graph.emplace_back(Edge{ 1, 2 });
	graph.emplace_back(Edge{ 1, 5 });

	// Node 2					  
	graph.emplace_back(Edge{ 2, 1 });
	graph.emplace_back(Edge{ 2, 5 });
	graph.emplace_back(Edge{ 2, 4 });

	// Node 3					  
	graph.emplace_back(Edge{ 3, 4 });
	graph.emplace_back(Edge{ 3, 7 });

	// Node 4					  
	graph.emplace_back(Edge{ 4, 2 });
	graph.emplace_back(Edge{ 4, 3 });
	graph.emplace_back(Edge{ 4, 5 });
	graph.emplace_back(Edge{ 4, 6 });
	graph.emplace_back(Edge{ 4, 8 });

	// Node 5					  
	graph.emplace_back(Edge{ 5, 1 });
	graph.emplace_back(Edge{ 5, 2 });
	graph.emplace_back(Edge{ 5, 4 });
	graph.emplace_back(Edge{ 5, 8 });

	// Node 6					  
	graph.emplace_back(Edge{ 6, 4 });
	graph.emplace_back(Edge{ 6, 7 });
	graph.emplace_back(Edge{ 6, 8 });

	// Node 7					  
	graph.emplace_back(Edge{ 7, 3 });
	graph.emplace_back(Edge{ 7, 6 });

	// Node 8					  
	graph.emplace_back(Edge{ 8, 4 });
	graph.emplace_back(Edge{ 8, 5 });
	graph.emplace_back(Edge{ 8, 6 });
	
	/*
	graph.emplace_back(Edge{ 1, 3 });
	graph.emplace_back(Edge{ 2, 3 });
	*/
	DFS(node_count, graph, 1);

}

void DFS(int node_count, vector<Edge>& graph, int start_node) {

	// 알고리즘

	// 1. 현재 노드를 방문한다.

	// 2. 현재 노드와 이웃노드를 가져온다.

	// 3. 현재 노드의 이웃 노드 중, 방문하지 않은 노드를 Stack에 삽입한다.

	// 4. Stack에서 새로운 노드를 꺼내 방문하여 1 ~ 3을 반복한다.

	vector<unsigned> stack;
	vector<unsigned> search_result;																		// 방문한 노드 체크

	int curNode = start_node;
	stack.push_back(curNode);

	for (int i = 0; i < node_count; i++) {																// 방문 횟수는 노드의 개수와 같으므로,

		if (stack.empty() == false) {
			curNode = stack[stack.size() - 1];															// stack에서 현재 노드를 꺼내옴
			stack.pop_back();
		}

		else break;

		cout << curNode << endl;
		
		search_result.push_back(curNode);																// 방문 노드 체크

		vector<Edge> edgesFromNode;

		for (int k = 0; k < graph.size(); k++) {														// 현재 노드의 Edge를 가져온다.
			if (curNode == graph[k].src)
				edgesFromNode.emplace_back(graph[k]);
		}

		for (int k = 0; k < edgesFromNode.size(); k++) {												// 연결된 노드들을 가져온다.
			int dstNode = edgesFromNode[k].dst;

			if (find(search_result.begin(), search_result.end(), dstNode) == search_result.end())		// 이미 방문한 Node가 아닐 경우
				stack.push_back(dstNode);																// Stack에 삽입

		}

	}

}