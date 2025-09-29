#include <stdio.h>
#include <stdlib.h>

typedef struct GraphNode{
	int vertex; //정점
	//int cost;
	struct GraphNode* link; //인접정점 가리킬 포인터
}GraphNode;

typedef struct GraphHeader{
	int n; //정점 개수
	GraphNode* head; //노드 배열의 첫 주소를 가리킴
}GraphHeader;

void Init(GraphHeader* g, int n){
	//정점 개수 n개 설정, 배열원소는 모두 0으로 초기화ㅣ

	g->n=n;
	g->head = (GraphNode*)malloc(sizeof(GraphHeader)*n);

	for(int i=0;i<g->n;i++){
		g->head[i].vertex = i;
		g->head[i].link=NULL;
	}
}

void insert_directed_edge(GraphHeader* g, int v1,int v2){
	//g->list[v1]의 주소를 따라 가장 마지막 노드 뒤에 새 노드 추가
	//아무것도 연결되지 않은 상태와 하나라도 연결된 상태로 나누어서 추가

	if(v1>=g->n || v2==g->n || v1==-1 || v2==-1)return;

	GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
	newNode->vertex = v2;
	newNode->link = NULL;

	if(g->head[v1].link == NULL){
		g->head[v1].link = newNode;
		return;
	}else{ //하나라도 연결된 상태, 맨 앞 추가
		newNode->link = g->head[v1].link;
		g->head[v1].link = newNode;
	}
	
}

void insert_undirected_edge(GraphHeader* g, int v1, int v2){
	insert_directed_edge(g,v1,v2);
	insert_directed_edge(g,v2,v1);
}

void print_matrix(GraphHeader* g){
	GraphNode* curNode;

	for(int i=0;i<g->n;i++){
		curNode = g->head[i].link;
		printf("정점 %d의 인접리스트", g->head[i].vertex);

		//연결리스트 순회
		while(curNode != NULL){
			printf("-> %d", curNode->vertex);
			curNode = curNode->link;
		}
		puts("");
	}
}

void memory_free(GraphHeader* p){
	//연결리스트 삭제 후 graphHeader도 삭제

	GraphNode* del;

	for(int i=0;i<p->n;i++){
		while(p->head[i].link!=NULL){
			del = p->head[i].link;
			p->head[i].link=del->link;
			printf("%d노드 제거\n",del->vertex);
			free(del);
		}
	}
	free(p);
}

int main() {
	GraphHeader* g = (GraphHeader*)malloc(sizeof(GraphHeader));
	int n,v1,v2;

	scanf("%d",&n);
	Init(g,n);

	while(1){
		scanf("%d %d",&v1,&v2);
		if(v1==-1 && v2==-1)break;

		insert_undirected_edge(g,v1,v2);
	}

	print_matrix(g);
	memory_free(g);
	return 0;
}
