#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum {
	Blank,
	Red,
	Blue,
	Green,
	Yellow,
	Black,
	White
};

struct Node {
	int idx;									// 컬러 벡터와의 사상을 위한 idx
	int degree;									// 차수
	vector<unsigned> neighbors;					// 이웃 노드

	bool operator >(const Node& node) const {
		return degree > node.degree;
	}

	bool operator <(const Node& node) const {
		return degree < node.degree;
	}

};


struct Edge {
	int src;
	int dst;
};

vector<unsigned> WelshPowell(int node_count, vector<Edge> &Graph);

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


	
	vector<unsigned> nodes = WelshPowell(node_count, graph);

	for (int i = 0; i < node_count; i++) {
		cout << i + 1 << "번째 노드의 색 : ";

		switch (nodes[i]) {
			case Red:
				cout << "Red";
				break;
			case Blue:
				cout << "Blue";
				break;
			case Green:
				cout << "Green";
				break;
			case Yellow:
				cout << "Yellow";
				break;
			case Black:
				cout << "Black";
				break;
			case White:
				cout << "White";
				break;
		}

		cout << endl;

	}


}

vector<unsigned> WelshPowell(int node_count, vector<Edge>& Graph) {

	vector<Node> nodes(node_count);
	vector<unsigned> result(node_count);

	for (int i = 0; i < node_count; i++) {						// Node 초기화
		nodes[i].degree = 0;
		nodes[i].idx = i;										// Node - result간 사상을 위한 idx 변수
		result[i] = Blank;

		for(int k = 0; k < Graph.size(); k++){					// Node 차수 계산

			if (Graph[k].src == i + 1){
				nodes[i].degree++;
				nodes[i].neighbors.push_back(Graph[k].dst);		// 이웃 노드 삽입
			}

		}
	}

	sort(nodes.begin(), nodes.end(), greater<>());				// 차수가 큰 것이 먼저 오도록 정렬
	
	for (int i = 0; i < node_count; i++) {

		cout << nodes[i].idx + 1 << "번째 노드 차수 : " << nodes[i].degree << endl;
		cout << nodes[i].idx + 1 << "번째 노드 이웃 : ";

		for (int k = 0; k < nodes[i].neighbors.size(); k++)
			cout << nodes[i].neighbors[k] << " ";

		cout << endl << endl;

	}
	

	// Welsh-Powell 알고리즘 시작

	int color = Blank;														// 삽입할 색 변수
	for (int i = 0; i < node_count; i++) {
		color++;															// 색을 먼저 증가시킨 후,
	
		// 자기 자신이 먼저 비어있을 경우, 채색
		if (result[nodes[i].idx] == Blank)
			result[nodes[i].idx] = color;

		else continue;														// 이미 칠해져 있을 경우 생략

		// 자신과 연결되지 않은 노드 채색
		// 먼저 자신과 이웃이 아닌 노드(연결되지 않은 노드)부터 알아옴.

		for (int k = 1; k <= node_count; k++) {								// 모든 노드 중에
		
			if (find(nodes[i].neighbors.begin(), nodes[i].neighbors.end(), k) == nodes[i].neighbors.end()){
																			// 자신과 이웃이 아닌 노드를 찾음

				if (result[k - 1] == Blank)									// 비어있을 경우 채색
					result[k - 1] = color;

				else continue;												// 칠해져 있을 경우 생략
			}
		}

	}

	return result;

}