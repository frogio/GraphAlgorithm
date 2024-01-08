#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node{

	int id;
	
	// DisjointSet에 쓰이는 데이터
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

	void make_set(int x) { nodes.emplace_back(x); }				// 트리를 생성한다.

	int find(int id) {											// 특정 노드가 포함된 트리의 루트를 찾는다.
		// 트리의 루트는 자기 자신을 가리키는 포인터를 갖는다.

		while (id != nodes[id].parent)						
			id = nodes[id].parent;
	
		return id;
	}

	void union_set(int x, int y) {
		int root_x = find(x);
		int root_y = find(y);
		// 두 x, y가 포함된 각각의 트리의 루트들을 찾는다.

		if (root_x == root_y)	// 두 루트가 같을 경우, 같은 트리이므로 그래프에선 사이클이 발생한다.
			return;				// 아무 작업도 하지 않는다.


		// 낮은 랭크의 트리를 랭크가 높은 트리에 붙힌다.
		// 루트가 같은 트리가 아니면 그래프에서 사이클이 발생하지 않으므로
		
		// ex)	root_x = 3
		// 		root_y = 1
		
		// 		if (root_x > root_y) then swap root_x and root_y
		
		// 		root_x = 1
		// 		root_y = 3
		
		// 		nodes[root_x].parent => nodes[1].parent(y) = nodes[3].parent(x);	// 낮은 랭크(1, y)의 부모를 높은 랭크(3, x)의 부모로 변경한다.
		// 		nodes[root_y].rank++ => nodes[3].rank++(x);							// 마지막으로 최종적인 부모 랭크를 1 증가시킨다.
 
		if (nodes[root_x].rank > nodes[root_y].rank)
			swap(root_x, root_y);
			
		nodes[root_x].parent = nodes[root_y].parent;
		nodes[root_y].rank++;
	}

};


vector<Edge> Kruskal(vector<Edge>& graph, int node_count) {

	sort(graph.begin(), graph.end(), greater<>());
	// Edge를 정렬하여 가중치가 가장 큰 값이 맨 앞에 오도록 내림차순으로 정렬한다.

	DisjointSet dset;
	
	// DisjointSet 초기화
	for (int i = 0; i < node_count; i++)
		dset.make_set(i);			// 각 노드당 0 ~ node_cnt 번호를 매김

	vector<Edge> MST;
	// 최소신장 트리
	// 그래프와 DisjointSet 두 자료구조를 사상하여 구현.

	while (graph.empty() == false) {		// 그래프의 원소가 남아있을 때 까지
		Edge e = graph.back();
		graph.pop_back();
		// 엣지가 내림차순으로 정렬되어 있으므로 (맨 뒤에 있는 엣지의 가중치가 가장 작음)
		// edge 하나를 맨 뒤에서 가져온다

		if (dset.find(e.src) != dset.find(e.dst)) {					// edge의 시작점과 끝점이 같은 트리에 존재하지 않을 경우 (사이클이 발생하지 않을 경우)
			MST.emplace_back(Edge{ e.src, e.dst, e.weight });		// 최소 신장 트리에 포함시킨다.
			dset.union_set(e.src, e.dst);							// union_set 연산을 통해 disjointSet 구조를 업데이트 한다.
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
	// Edge의 정점 번호는 1부터 시작하지만 DisjointSet의 Node는 Zero-Base이기 때문에
	// 잘못된 메모리 번지를 참조할 가능성이 있다.
	// 따라서 정점 번호를 모두 1씩 뺀다.
	// (Weight은 예외)

	vector<Edge> MST = Kruskal(graph, node_count);

	cout << "src\t" << "dst\t" << "weight" << endl;

	for (int i = 0; i < MST.size(); i++)
		cout << MST[i].src << '\t' << MST[i].dst << '\t' << MST[i].weight << endl;

}
