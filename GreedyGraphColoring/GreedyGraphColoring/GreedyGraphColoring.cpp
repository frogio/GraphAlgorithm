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

	for (int i = 0; i < nodeCount; i++)					// ó�� �ο��� ��� ���� BLANK
		assigned_colors[i] = BLANK;

	for (int i = 0; i < nodeCount; i++) {

		vector<Edge> edgesFromNode;						// ���� ���� ���� ������� ������
		set<unsigned> neighbors_color;					// ���� ������ ������ �ִ� �������� ���� (�ߺ��� ����) (Point)

		for (int k = 0; k < G.size(); k++) {			// edgesFromNode�� ä���.
			if (i + 1 == G[k].src)
				edgesFromNode.emplace_back(G[k]);
		}

		for (int j = 0; j < edgesFromNode.size(); j++)	// �̿��� ���� �߰��Ѵ�.
			neighbors_color.insert(assigned_colors[ edgesFromNode[j].dst - 1 ]);
														// �׷��� ������ 1���� ���� �迭�� ���.
														// assigned_colors�� zero base, ���� - 1

		// ������ ������ ĥ������ ���� ���� �߿��� ���� ���� ������ ������ ����
		int smallest = RED;
		for (; smallest <= WHITE; smallest++) {
			if (neighbors_color.find(smallest) == neighbors_color.end())
				// find�� �̿��Ͽ� Ư�� ���� ã�� ���ϸ� set�� �� �ε��� + 1�� �ǹ��ϴ� end�� ����
				// �������� ���� ������ ���, ĥ������ ���� �����̹Ƿ�, �� ������ ������ ĥ�ϴ°����� ����
				break;
		}

		// ���� ���� (ZeroBase)
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
		cout << k + 1 << "��° ���� : ";
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
