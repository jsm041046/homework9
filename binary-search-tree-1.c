/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
    printf("[----- 2021041046 전설민 -----]\n"); //학번 이름 출력
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n"); //안내
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어 입력

		switch(command) { //명령어에 따른 분기
		case 'z': case 'Z':
			initializeBST(&head); //이진 트리 초기화
			break;
		case 'q': case 'Q':
			freeBST(head); //이진 트리 메모리 할당 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			insert(head, key); //이진 트리에 원소값 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			deleteLeafNode(head, key); //이진 트리에서 원소값과 같은 노드가 리프노드일 때 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			ptr = searchIterative(head, key); //순차적 탐색
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //원소를 찾았을 경우 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //원소를 못 찾았을 경우 출력
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); //원소값 입력
			ptr = searchRecursive(head->left, key); //재귀적 탐색
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); //중위 탐색
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); //전위 탐색
			break;
		case 't': case 'T':
			postorderTraversal(head->left); //후위 탐색
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //Q를 입력받을 경우 반복문 종료

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
    if(ptr != NULL) //ptr포인터가 값을 가르키고 있을 경우
    {
        inorderTraversal(ptr->left); //ptr의 왼쪽을 먼저 순회
        printf(" [%d] ", ptr->key); //ptr을 순회해서 출력
        inorderTraversal(ptr->right); //ptr의 오른쪽을 나중에 순회
    }
}

void preorderTraversal(Node* ptr)
{

}

void postorderTraversal(Node* ptr)
{

}


int insert(Node* head, int key)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->left = NULL;
    temp->right = NULL;
    temp->key = key; //새로 대입할 노드 메모리 할당 및 원소값 대입

    Node* p = head->left; //대입할 위치를 탐색하는 포인터
    Node* prev = NULL; //대입할 노드의 부모를 결정하는 포인터

    while(p != NULL) //p가 트리의 범위를 벗어날 때 까지
    {
        prev = p; //prev값을 p를 가르키게 함
        if(p->key > key) //p가 가르키는 값이 대입하려는 값보다 클 경우
            p = p->left; //p를 왼쪽 자식으로 이동시킴
        else if(p->key < key) //p가 가르키는 값이 대입하려는 값보다 작을 경우
            p = p->right; //p를 오른쪽 자식으로 이동시킴
        else { //p가 가르키는 값이 대입하려는 값과 같을 경우
            printf("key is already exist\n");
            return 0; //비정상 종료
        }
    }

    if(prev != NULL) //대입할 노드의 부모 노드가 있을 경우
    {
        if(prev->key > key) //대입할 노드의 부모 원소값보다 대입하려는 원소값이 작을 경우
            prev->left = temp; //부모 노드의 왼쪽에 대입할 노드를 대입
        else //대입할 노드의 부모 원소값보다 대입하려는 원소값이 클을 경우
            prev->right = temp; //부모 노드의 오른쪽에 대입할 노드를 대입
    } else //없을 경우
        head->left = temp; //루트 노드를 대입할 노드로 설정

    return 1;
}

int deleteLeafNode(Node* head, int key)
{

}

Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{
    Node* p = head->left; //검색할 노드의 포인터

    while(p != NULL && p->key != key) //p가 끝을 가르키거나, 해당하는 원소값을 찾았을 경우 반복문에서 빠져나감
    {
        if(p->key > key) //p가 가르키는 값이 찾는 값보다 클 경우
            p = p->left; //p를 왼쪽 자식으로 이동시킴
        else //p가 가르키는 값이 찾는 값보다 작을 경우(같은 경우는 해당 while문의 성질 상 애초에 존재할 수 없음)
            p = p->right; //p를 오른쪽 자식으로 이동시킴
    }

    return p; //p를 반환
}


int freeBST(Node* head)
{

}
