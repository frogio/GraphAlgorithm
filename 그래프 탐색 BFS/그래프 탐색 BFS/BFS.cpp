#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int src;
	int dst;
};

void BFS(int node_count, vector<Edge> & graph, int start_node);

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

	BFS(node_count, graph, 1);

}

void BFS(int node_count, vector<Edge>& graph, int start_node) {

	// 알고리즘

	// 1. 현재 노드를 방문한다.

	// 2. 현재 노드와 이웃노드를 가져온다.

	// 3. 현재 노드의 이웃 노드 중, 중복되지 않은 노드를 Queue에 삽입한다.

	// 4. Queue에서 다음 노드를 꺼내 방문하여 1 ~ 3을 반복한다.

	vector<unsigned> queue;														// 방문한 노드 체크
	int curNode = start_node;
	queue.push_back(curNode);

	for(int i = 0; i < node_count; i++){										// 방문 횟수는 노드의 개수와 같으므로,

		curNode = queue[i];														// 현재 노드를 가져옴
		cout << curNode << endl;												// 현재 노드 방문

		vector<Edge> edgesFromNode;												// 현재 노드로 부터 뻗어나가는 엣지들

		for (int k = 0; k < graph.size(); k++) {								// 현재 노드의 Edge를 가져온다.
			if (curNode == graph[k].src)
				edgesFromNode.emplace_back(graph[k]);
		}

		for (int k = 0; k < edgesFromNode.size(); k++) {						// 연결된 노드들을 가져온다.
			int dstNode = edgesFromNode[k].dst;

			if(find(queue.begin(), queue.end(), dstNode) == queue.end())		// Queue에 존재하지 않은 dstNode일 경우
				queue.push_back(dstNode);										// Queue에 삽입
		
		}

	}

}