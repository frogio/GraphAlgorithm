#include <iostream>
#include <vector>
#include <set>

using namespace std;

enum Color {
	BLANK,
	RED,
	BLUE,
	GREEN,
	YELLOW,
	BLACK,
	WHITE
};

struct Edge {

	int src;
	int dst;

};

vector<unsigned> greedy_coloring(int nodeCount ,const vector<Edge>& G) {

	vector<unsigned> assigned_colors(nodeCount);

	for (int i = 0; i < nodeCount; i++)					// 처음 부여된 모든 색은 BLANK
		assigned_colors[i] = BLANK;

	for (int i = 0; i < nodeCount; i++) {

		vector<Edge> edgesFromNode;						// 현재 노드로 부터 뻗어나가는 엣지들
		set<unsigned> neighbors_color;					// 현재 정점과 인접해 있는 정점들의 색상 (중복을 없앰) (Point)

		for (int k = 0; k < G.size(); k++) {			// edgesFromNode를 채운다.
			if (i + 1 == G[k].src)
				edgesFromNode.emplace_back(G[k]);
		}

		for (int j = 0; j < edgesFromNode.size(); j++)	// 이웃의 색을 추가한다.
			neighbors_color.insert(assigned_colors[ edgesFromNode[j].dst - 1 ]);
														// 그래프 구조를 1차원 색의 배열로 사상.
														// assigned_colors는 zero base, 따라서 - 1

		// 인접한 정점에 칠해지지 않은 색상 중에서 가장 작은 숫자의 색상을 선택
		int smallest = RED;
		for (; smallest <= WHITE; smallest++) {
			if (neighbors_color.find(smallest) == neighbors_color.end())
				// find를 이용하여 특정 값을 찾지 못하면 set의 끝 인덱스 + 1을 의미하는 end를 리턴
				// 존재하지 않은 색상일 경우, 칠해지지 않은 색상이므로, 이 색으로 정점을 칠하는것으로 결정
				break;
		}

		// 색상 적용 (ZeroBase)
		assigned_colors[i] = smallest;

	}

	return assigned_colors;

}

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


	vector<unsigned> colors = greedy_coloring(node_count, graph);

	for (int k = 0; k < colors.size(); k++) {
		cout << k + 1 << "번째 색상 : ";
		switch (colors[k]) {
		case RED:
			cout << "Red";
			break;
		case BLUE:
			cout << "Blue";
			break;
		case GREEN:
			cout << "Green";
			break;
		case YELLOW:
			cout << "Yellow";
			break;
		case BLACK:
			cout << "Black";
			break;
		case WHITE:
			cout << "White";
			break;
		}
		cout << endl;
	}

	cout << endl;



}
