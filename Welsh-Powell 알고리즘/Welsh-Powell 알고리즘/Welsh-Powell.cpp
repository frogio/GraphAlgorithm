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
	int idx;									// �÷� ���Ϳ��� ����� ���� idx
	int degree;									// ����
	vector<unsigned> neighbors;					// �̿� ���

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
		cout << i + 1 << "��° ����� �� : ";

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

	for (int i = 0; i < node_count; i++) {						// Node �ʱ�ȭ
		nodes[i].degree = 0;
		nodes[i].idx = i;										// Node - result�� ����� ���� idx ����
		result[i] = Blank;

		for(int k = 0; k < Graph.size(); k++){					// Node ���� ���

			if (Graph[k].src == i + 1){
				nodes[i].degree++;
				nodes[i].neighbors.push_back(Graph[k].dst);		// �̿� ��� ����
			}

		}
	}

	sort(nodes.begin(), nodes.end(), greater<>());				// ������ ū ���� ���� ������ ����
	
	for (int i = 0; i < node_count; i++) {

		cout << nodes[i].idx + 1 << "��° ��� ���� : " << nodes[i].degree << endl;
		cout << nodes[i].idx + 1 << "��° ��� �̿� : ";

		for (int k = 0; k < nodes[i].neighbors.size(); k++)
			cout << nodes[i].neighbors[k] << " ";

		cout << endl << endl;

	}
	

	// Welsh-Powell �˰��� ����

	int color = Blank;														// ������ �� ����
	for (int i = 0; i < node_count; i++) {
		color++;															// ���� ���� ������Ų ��,
	
		// �ڱ� �ڽ��� ���� ������� ���, ä��
		if (result[nodes[i].idx] == Blank)
			result[nodes[i].idx] = color;

		else continue;														// �̹� ĥ���� ���� ��� ����

		// �ڽŰ� ������� ���� ��� ä��
		// ���� �ڽŰ� �̿��� �ƴ� ���(������� ���� ���)���� �˾ƿ�.

		for (int k = 1; k <= node_count; k++) {								// ��� ��� �߿�
		
			if (find(nodes[i].neighbors.begin(), nodes[i].neighbors.end(), k) == nodes[i].neighbors.end()){
																			// �ڽŰ� �̿��� �ƴ� ��带 ã��

				if (result[k - 1] == Blank)									// ������� ��� ä��
					result[k - 1] = color;

				else continue;												// ĥ���� ���� ��� ����
			}
		}

	}

	return result;

}