#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{

	int id;
	
	// DisjointSet�� ���̴� ������
	int rank;
	int parent;

	Node(int _id) : id(_id), rank(0), parent(_id) {}

};

struct Edge {
	int src;
	int dst;
	int weight;

	bool operator >(const Edge& e) const {
		return weight > e.weight;
	}

	bool operator <(const Edge& e) const {
		return weight < e.weight;
	}

};

class DisjointSet {
private:
	vector<Node> nodes;

public:

	void make_set(int x) { nodes.emplace_back(x); }				// Ʈ���� �����Ѵ�.

	int find(int id) {											// Ư�� ��尡 ���Ե� Ʈ���� ��Ʈ�� ã�´�.
		// Ʈ���� ��Ʈ�� �ڱ� �ڽ��� ����Ű�� �����͸� ���´�.

		while (id != nodes[id].parent)						
			id = nodes[id].parent;
	
		return id;
	}

	void union_set(int x, int y) {
		int root_x = find(x);
		int root_y = find(y);
		// �� x, y�� ���Ե� ������ Ʈ���� ��Ʈ���� ã�´�.

		if (root_x == root_y)	// �� ��Ʈ�� ���� ���, ���� Ʈ���̹Ƿ� �׷������� ����Ŭ�� �߻��Ѵ�.
			return;				// �ƹ� �۾��� ���� �ʴ´�.


		// ���� ��ũ�� Ʈ���� ��ũ�� ���� Ʈ���� ������.
		// ��Ʈ�� ���� Ʈ���� �ƴϸ� �׷������� ����Ŭ�� �߻����� �����Ƿ�
		
		// ex)	root_x = 3
		// 		root_y = 1
		
		// 		if (root_x > root_y) then swap root_x and root_y
		
		// 		root_x = 1
		// 		root_y = 3
		
		// 		nodes[root_x].parent => nodes[1].parent(y) = nodes[3].parent(x);	// ���� ��ũ(1, y)�� �θ� ���� ��ũ(3, x)�� �θ�� �����Ѵ�.
		// 		nodes[root_y].rank++ => nodes[3].rank++(x);							// ���������� �������� �θ� ��ũ�� 1 ������Ų��.
 
		if (nodes[root_x].rank > nodes[root_y].rank)
			swap(root_x, root_y);
			
		nodes[root_x].parent = nodes[root_y].parent;
		nodes[root_y].rank++;
	}

};


vector<Edge> Kruskal(vector<Edge>& graph, int node_count) {

	sort(graph.begin(), graph.end(), greater<>());
	// Edge�� �����Ͽ� ����ġ�� ���� ū ���� �� �տ� ������ ������������ �����Ѵ�.

	DisjointSet dset;
	
	// DisjointSet �ʱ�ȭ
	for (int i = 0; i < node_count; i++)
		dset.make_set(i);			// �� ���� 0 ~ node_cnt ��ȣ�� �ű�

	vector<Edge> MST;
	// �ּҽ��� Ʈ��
	// �׷����� DisjointSet �� �ڷᱸ���� ����Ͽ� ����.

	while (graph.empty() == false) {		// �׷����� ���Ұ� �������� �� ����
		Edge e = graph.back();
		graph.pop_back();
		// ������ ������������ ���ĵǾ� �����Ƿ� (�� �ڿ� �ִ� ������ ����ġ�� ���� ����)
		// edge �ϳ��� �� �ڿ��� �����´�

		if (dset.find(e.src) != dset.find(e.dst)) {					// edge�� �������� ������ ���� Ʈ���� �������� ���� ��� (����Ŭ�� �߻����� ���� ���)
			MST.emplace_back(Edge{ e.src, e.dst, e.weight });		// �ּ� ���� Ʈ���� ���Խ�Ų��.
			dset.union_set(e.src, e.dst);							// union_set ������ ���� disjointSet ������ ������Ʈ �Ѵ�.
		}
	
	}


	return MST;
}


void main() {
	vector<Edge> graph;
	int node_count = 8;

	graph.emplace_back(Edge{ 0, 1, 2 });
	graph.emplace_back(Edge{ 0, 4, 3 });
	// 2
	graph.emplace_back(Edge{ 1, 0, 2 });
	graph.emplace_back(Edge{ 1, 4, 3 });
	graph.emplace_back(Edge{ 1, 3, 1 });
	// 5
	graph.emplace_back(Edge{ 2, 3, 2 });
	graph.emplace_back(Edge{ 2, 6, 3 });
	// 7
	graph.emplace_back(Edge{ 3, 1, 1 });
	graph.emplace_back(Edge{ 3, 2, 2 });
	graph.emplace_back(Edge{ 3, 4, 2 });
	graph.emplace_back(Edge{ 3, 5, 4 });
	graph.emplace_back(Edge{ 3, 7, 5 });
	// 12
	graph.emplace_back(Edge{ 4, 0, 3 });
	graph.emplace_back(Edge{ 4, 1, 5 });
	graph.emplace_back(Edge{ 4, 3, 2 });
	graph.emplace_back(Edge{ 4, 7, 3 });
	// 16
	graph.emplace_back(Edge{ 5, 3, 4 });
	graph.emplace_back(Edge{ 5, 6, 4 });
	graph.emplace_back(Edge{ 5, 7, 1 });
	// 19
	graph.emplace_back(Edge{ 6, 2, 3 });
	graph.emplace_back(Edge{ 6, 5, 4 });
	// 21
	graph.emplace_back(Edge{ 7, 3, 5 });
	graph.emplace_back(Edge{ 7, 4, 3 });
	graph.emplace_back(Edge{ 7, 5, 1 });
	// 24
	// Edge�� ���� ��ȣ�� 1���� ���������� DisjointSet�� Node�� Zero-Base�̱� ������
	// �߸��� �޸� ������ ������ ���ɼ��� �ִ�.
	// ���� ���� ��ȣ�� ��� 1�� ����.
	// (Weight�� ����)

	vector<Edge> MST = Kruskal(graph, node_count);

	cout << "src\t" << "dst\t" << "weight" << endl;

	for (int i = 0; i < MST.size(); i++)
		cout << MST[i].src << '\t' << MST[i].dst << '\t' << MST[i].weight << endl;

}
