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

	for (int i = 1; i <= node_count; i++){							// �׷����� ���� �и��Ǿ� ���� ���ɼ��� �����Ƿ� ��� ��忡 ���� �̺б׷������� �Ǻ��Ѵ�.
		
		if (visited[i] != NONE)										// �湮�� ����� ���, BFS ����
			continue;

		queue<int> queue;
		queue.push(i);
		visited[i] = BLACK;

		while (queue.empty() == false) {							// BFS ����
		
			int curNode = queue.front();
			queue.pop();
			
			for (int i = 0; i < nodes[curNode].size(); i++) {
				int dstNode = nodes[curNode][i];

				if (visited[dstNode] == NONE) {						// �湮���� ���� ����� ���
					queue.push(dstNode);
					visited[dstNode] = (visited[curNode] + 1) % 2;	// �������(dstNode)�� ��� �ڽ�(curNode)�� �ٸ� ������ ó��
				}

				else if (visited[dstNode] == visited[curNode])
																	// �湮�� ����� ���
																	// �湮�ߴ� ���(dstNode)�� ���� ��(curNode)�� �����ϴٸ�
						return 0;									// �̺� �׷����� �ƴ�
			}

		}

	}
	return 1;
}