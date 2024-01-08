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

	// �˰���

	// 1. ���� ��带 �湮�Ѵ�.

	// 2. ���� ���� �̿���带 �����´�.

	// 3. ���� ����� �̿� ��� ��, �湮���� ���� ��带 Stack�� �����Ѵ�.

	// 4. Stack���� ���ο� ��带 ���� �湮�Ͽ� 1 ~ 3�� �ݺ��Ѵ�.

	vector<unsigned> stack;
	vector<unsigned> search_result;																		// �湮�� ��� üũ

	int curNode = start_node;
	stack.push_back(curNode);

	for (int i = 0; i < node_count; i++) {																// �湮 Ƚ���� ����� ������ �����Ƿ�,

		if (stack.empty() == false) {
			curNode = stack[stack.size() - 1];															// stack���� ���� ��带 ������
			stack.pop_back();
		}

		else break;

		cout << curNode << endl;
		
		search_result.push_back(curNode);																// �湮 ��� üũ

		vector<Edge> edgesFromNode;

		for (int k = 0; k < graph.size(); k++) {														// ���� ����� Edge�� �����´�.
			if (curNode == graph[k].src)
				edgesFromNode.emplace_back(graph[k]);
		}

		for (int k = 0; k < edgesFromNode.size(); k++) {												// ����� ������ �����´�.
			int dstNode = edgesFromNode[k].dst;

			if (find(search_result.begin(), search_result.end(), dstNode) == search_result.end())		// �̹� �湮�� Node�� �ƴ� ���
				stack.push_back(dstNode);																// Stack�� ����

		}

	}

}