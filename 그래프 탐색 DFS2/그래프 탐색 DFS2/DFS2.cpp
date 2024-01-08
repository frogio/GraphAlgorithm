#include <iostream>
#include <vector>

using namespace std;

struct Edge {
	int src;
	int dst;
};

void DFS(vector<Edge> & graph, int start_node);

void main() {
	vector<Edge> graph;
	/*
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
	*/

	// Node 1
	graph.emplace_back(Edge{ 1, 2 });

	// Node 2					  
	graph.emplace_back(Edge{ 2, 1 });
	graph.emplace_back(Edge{ 2, 3 });
	graph.emplace_back(Edge{ 2, 8 });

	// Node 3					  
	graph.emplace_back(Edge{ 3, 2 });
	graph.emplace_back(Edge{ 3, 4 });

	// Node 4					  
	graph.emplace_back(Edge{ 4, 3 });
	graph.emplace_back(Edge{ 4, 6 });

	// Node 5					  
	graph.emplace_back(Edge{ 5, 7 });
	graph.emplace_back(Edge{ 5, 9 });

	// Node 6					  
	graph.emplace_back(Edge{ 6, 4 });

	// Node 7					  
	graph.emplace_back(Edge{ 7, 5 });

	// Node 8					  
	graph.emplace_back(Edge{ 8, 2 });
	graph.emplace_back(Edge{ 8, 9 });

	// Node 9					  
	graph.emplace_back(Edge{ 9, 5 });
	graph.emplace_back(Edge{ 9, 8 });

	DFS(graph, 1);
}
	
void DFS(vector<Edge> & graph, int start_node) {

	vector<unsigned> stack;
	vector<unsigned> visited;

	stack.push_back(start_node);

	while (stack.empty() == false) {
		// ������ ������ ����� �� ���� �׷����� Ž���Ѵ�.
		
		int node = stack[stack.size() - 1];					// stack�� �� ������ �湮�Ѵ�.
		visited.push_back(node);
		stack.pop_back();

		for (int i = 0; i < graph.size(); i++) {
			if (node == graph[i].src) {
				int dstNode = graph[i].dst;
				// ���� ���� �̿��� dstNode�� ���ؼ�

				if (find(visited.begin(), visited.end(), dstNode) == visited.end() && 
					find(stack.begin(), stack.end(), dstNode) == stack.end())
					// �湮���� ���� �����̰�, ���ÿ� ���ٸ� �����Ѵ�.
					stack.push_back(dstNode);
			}
		}
	}

	for (int i = 0; i < visited.size(); i++)
		cout << visited[i] << endl;


}