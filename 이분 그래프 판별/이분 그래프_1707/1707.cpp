#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

using namespace std;

int identify_bg(int node_count);

#define TEST_CASE	20
#define MAX_NODE	20001
#define NONE		-1
#define BLACK		0
#define RED			1

char result[TEST_CASE] = { 0, };
char visited[MAX_NODE] = { 0, };
vector<int> nodes[MAX_NODE];

int main() {
	int test_case;
	
	cin >> test_case;

	for (int i = 0; i < test_case; i++) {

		memset(visited, NONE, sizeof(visited));
		
		int node_count, edge_count;
		cin >> node_count >> edge_count;

		for (int k = 0; k < edge_count; k++) {
			int src, dst;
			cin >> src >> dst;
			nodes[src].push_back(dst);
			nodes[dst].push_back(src);
		}
	
		result[i] = identify_bg(node_count);
	
		for (int k = 1; k <= node_count; k++)
			nodes[k].clear();

	}

	for (int i = 0; i < test_case; i++) {
		if (result[i] == 1)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;

	}


}

int identify_bg(int node_count) {

	for (int i = 1; i <= node_count; i++){							// 그래프가 서로 분리되어 있을 가능성도 있으므로 모든 노드에 대해 이분그래프임을 판별한다.
		
		if (visited[i] != NONE)										// 방문한 노드일 경우, BFS 생략
			continue;

		queue<int> queue;
		queue.push(i);
		visited[i] = BLACK;

		while (queue.empty() == false) {							// BFS 시작
		
			int curNode = queue.front();
			queue.pop();
			
			for (int i = 0; i < nodes[curNode].size(); i++) {
				int dstNode = nodes[curNode][i];

				if (visited[dstNode] == NONE) {						// 방문하지 않은 노드일 경우
					queue.push(dstNode);
					visited[dstNode] = (visited[curNode] + 1) % 2;	// 인접노드(dstNode)는 모두 자신(curNode)과 다른 색으로 처리
				}

				else if (visited[dstNode] == visited[curNode])
																	// 방문한 노드일 경우
																	// 방문했던 노드(dstNode)가 현재 색(curNode)과 동일하다면
						return 0;									// 이분 그래프가 아님
			}

		}

	}
	return 1;
}