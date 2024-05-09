#include <iostream>
#include <vector>
#include <stack>
#include <memory.h>

#define MAX_NODE		10001

using namespace std;

vector<int> graph[MAX_NODE];
vector<int> transpose_graph[MAX_NODE];
char visited[MAX_NODE] = { 0, };

void DFS(int node, stack<int>& stack);
void TransposeDFS(int node, vector<int>& scc);
void Kosaraju(int node_count);

vector<vector<int>> SCC;

void main() {

	// 테스트 케이스
	/*
	* 
	7 9
	1 4
	4 5
	5 1
	1 6
	6 7
	2 7
	7 3
	3 7
	7 2

	9 14
	1 2
	1 4
	2 3
	2 5
	3 4
	3 6
	4 8
	5 3
	6 5
	6 7
	7 8
	7 3
	8 9
	9 4

	*/


	cin.tie(NULL);

	int vertex, edge;

	cin >> vertex >> edge;

	for (int i = 0; i < edge; i++) {
		int src, dst;
		cin >> src >> dst;
		graph[src].push_back(dst);					// 그래프 생성
		transpose_graph[dst].push_back(src);		// 전치 그래프 생성
	}

	Kosaraju(vertex);

	for (int i = 0; i < SCC.size(); i++) {			// 최종 SCC를 출력

		for (int k = 0; k < SCC[i].size(); k++)
			cout << SCC[i][k] << " ";

		cout << '\n';
	}



}

void DFS(int node, stack<int> & stack) {
		
	visited[node] = 1;

	for (int i = 0; i < graph[node].size(); i++) {			// 이웃을 먼저 탐색한 다음
		
		int dstNode = graph[node][i];
		
		if(visited[dstNode] == 0)
			DFS(dstNode, stack);
	
	}

	stack.push(node);										// 자기 자신을 stack에 삽입한다.

}

void TransposeDFS(int node, vector<int> & scc) {

	visited[node] = 1;
	scc.push_back(node);

	for (int i = 0; i < transpose_graph[node].size(); i++){

		int dstNode = transpose_graph[node][i];
		
		if(visited[dstNode] == 0)
			TransposeDFS(dstNode, scc);

	}

}

void Kosaraju(int node_count) {

	stack<int> stack;
	vector<int> scc;

	for (int i = 1; i <= node_count; i++) {			// 첫번째 DFS로 Node 탐색, 이동할 수 없는 노드가 존재할 수도 있으므로 for 루프로 전부 탐색
		if(visited[i] == 0)
			DFS(i, stack);
	}


	memset(visited, 0, sizeof(visited));			// 방문 모두 초가화

	while (stack.empty() == false) {				// 두번째, 스택에 쌓인 순서대로 DFS를 수행해 SCC를 찾음
		int curNode = stack.top();
		stack.pop();
	
		if(visited[curNode] == 0){
			TransposeDFS(curNode, scc);					// 탐색 최종 결과로 scc를 찾는다.
			SCC.push_back(scc);							// scc를 추가한다.
			scc.clear();								// scc를 비움
		}

	}

}
