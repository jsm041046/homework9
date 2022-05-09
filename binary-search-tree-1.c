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
void freeNode(Node* ptr);

int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
    printf("[----- 2021041046 ������ -----]\n"); //�й� �̸� ���
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n"); //�ȳ�
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //��ɾ� �Է�

		switch(command) { //��ɾ ���� �б�
		case 'z': case 'Z':
			initializeBST(&head); //���� Ʈ�� �ʱ�ȭ
			break;
		case 'q': case 'Q':
			freeBST(head); //���� Ʈ�� �޸� �Ҵ� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			insert(head, key); //���� Ʈ���� ���Ұ� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			deleteLeafNode(head, key); //���� Ʈ������ ���Ұ��� ���� ��尡 ��������� �� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			ptr = searchIterative(head, key); //������ Ž��
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //���Ҹ� ã���� ��� ���
			else
				printf("\n Cannot find the node [%d]\n", key); //���Ҹ� �� ã���� ��� ���
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key); //���Ұ� �Է�
			ptr = searchRecursive(head->left, key); //����� Ž��
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); //���� Ž��
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); //���� Ž��
			break;
		case 't': case 'T':
			postorderTraversal(head->left); //���� Ž��
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //Q�� �Է¹��� ��� �ݺ��� ����

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
    if(ptr != NULL) //ptr�����Ͱ� ���� ����Ű�� ���� ���
    {
        inorderTraversal(ptr->left); //ptr�� ������ ���� ��ȸ
        printf(" [%d] ", ptr->key); //ptr�� ��ȸ�ؼ� ���
        inorderTraversal(ptr->right); //ptr�� �������� ���߿� ��ȸ
    }
}

void preorderTraversal(Node* ptr)
{
    if(ptr != NULL) //ptr�����Ͱ� ���� ����Ű�� ���� ���
    {
        printf(" [%d] ", ptr->key); //ptr�� ���� ��ȸ�ؼ� ���
        inorderTraversal(ptr->left); //ptr�� ������ ��ȸ
        inorderTraversal(ptr->right); //ptr�� �������� ��ȸ
    }
}

void postorderTraversal(Node* ptr)
{
    if(ptr != NULL) //ptr�����Ͱ� ���� ����Ű�� ���� ���
    {
        inorderTraversal(ptr->left); //ptr�� ������ ��ȸ
        inorderTraversal(ptr->right); //ptr�� �������� ��ȸ
        printf(" [%d] ", ptr->key); //ptr�� ���߿� ��ȸ�ؼ� ���
    }
}


int insert(Node* head, int key)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->left = NULL;
    temp->right = NULL; //temp�� �¿��� �ʱ�ȭ
    temp->key = key; //���� ������ ��� �޸� �Ҵ� �� ���Ұ� ����

    Node* p = head->left; //������ ��ġ�� Ž���ϴ� ������
    Node* prev = NULL; //������ ����� �θ� �����ϴ� ������

    while(p != NULL) //p�� Ʈ���� ������ ��� �� ����
    {
        prev = p; //prev���� p�� ����Ű�� ��
        if(p->key > key) //p�� ����Ű�� ���� �����Ϸ��� ������ Ŭ ���
            p = p->left; //p�� ���� �ڽ����� �̵���Ŵ
        else if(p->key < key) //p�� ����Ű�� ���� �����Ϸ��� ������ ���� ���
            p = p->right; //p�� ������ �ڽ����� �̵���Ŵ
        else { //p�� ����Ű�� ���� �����Ϸ��� ���� ���� ���
            printf("key is already exist\n");
            return 0; //������ ����
        }
    }

    if(prev != NULL) //������ ����� �θ� ��尡 ���� ���
    {
        if(prev->key > key) //������ ����� �θ� ���Ұ����� �����Ϸ��� ���Ұ��� ���� ���
            prev->left = temp; //�θ� ����� ���ʿ� ������ ��带 ����
        else //������ ����� �θ� ���Ұ����� �����Ϸ��� ���Ұ��� Ŭ ���
            prev->right = temp; //�θ� ����� �����ʿ� ������ ��带 ����
    } else //���� ���
        head->left = temp; //��Ʈ ��带 ������ ���� ����

    return 1;
}

int deleteLeafNode(Node* head, int key)
{
    Node* p = head->left; //�˻��� ����� ������
    Node* prev = NULL; //�˻��� ����� �θ��� ������

    while(p != NULL && p->key != key) //p�� ���� ����Ű�ų�, �ش��ϴ� ���Ұ��� ã���� ��� �ݺ������� ��������
    {
        prev = p;
        if(p->key > key) //p�� ����Ű�� ���� ã�� ������ Ŭ ���
            p = p->left; //p�� ���� �ڽ����� �̵���Ŵ
        else //p�� ����Ű�� ���� ã�� ������ ���� ���(���� ���� �ش� while���� ���� �� ���ʿ� ������ �� ����)
            p = p->right; //p�� ������ �ڽ����� �̵���Ŵ
    }

    if(p == NULL) //ã�� ���Ұ� ���� ���
    {
        printf("key is already exist\n");
        return 0; //������ ����
    }
    if(p->left != NULL || p->right != NULL) //p�� ������尡 �ƴ� ���
    {
        printf("that node is not leaf node\n");
        return 0; //������ ����
    }
    free(p); //�ش� ��带 ����
    
    if(prev == NULL) //�ش� ����� �θ� ���� ���
        head->left = NULL; //��Ʈ ��带 ����
    else { //�θ� ���� ���
        if(p == prev->left) //p�� prev�� ���� �ڽ��̾��� ���
            prev->left = NULL; //�θ����� ���� ��ũ�� ����
        else //�ƴ� ���
            prev->right = NULL; //�θ����� ������ ��ũ�� ����
    }

}

Node* searchRecursive(Node* ptr, int key)
{
    if(ptr != NULL) //����Ű�� ��尡 ��ȿ�� ���
    {
        if(ptr->key > key) //ã�� ���Ұ��� ����Ű�� ���Ұ����� ���� ���
            return searchRecursive(ptr->left,key); //���� �ڽ� ��带 Ž���ϴ� �Լ� ��ȣ��
        else if(ptr->key < key) //ã�� ���Ұ��� ����Ű�� ���Ұ����� Ŭ ���
            return searchRecursive(ptr->right,key); //������ �ڽ� ��带 Ž���ϴ� �Լ� ��ȣ��
        else //ã�� ���� ����Ű�� ���� ���� ���
            return ptr; //�ش� ����� �ּҸ� ��ȯ
    } else { //����Ű�� ��尡 ��ȿ���� ���� ���
        return NULL; //NULL��ȯ
    }
    
}

Node* searchIterative(Node* head, int key)
{
    Node* p = head->left; //�˻��� ����� ������

    while(p != NULL && p->key != key) //p�� ���� ����Ű�ų�, �ش��ϴ� ���Ұ��� ã���� ��� �ݺ������� ��������
    {
        if(p->key > key) //p�� ����Ű�� ���� ã�� ������ Ŭ ���
            p = p->left; //p�� ���� �ڽ����� �̵���Ŵ
        else //p�� ����Ű�� ���� ã�� ������ ���� ���(���� ���� �ش� while���� ���� �� ���ʿ� ������ �� ����)
            p = p->right; //p�� ������ �ڽ����� �̵���Ŵ
    }

    return p; //p�� ��ȯ
}


int freeBST(Node* head)
{
    if(head != NULL) //head�� ����Ű�� ���� ���� ���
    {
        if(head->left != NULL) //��Ʈ��尡 ���� ���
            freeNode(head->left); //freeNode�Լ� ȣ��

        free(head); //head�� �Ҵ�� �޸�����
    }
    
}

void freeNode(Node* ptr)
{
    //���� ��ȸ����� �̿��� ��� ó��
    if(ptr != NULL) //ptr�� ����Ű�� ��尡 ���� ���
    {
        freeNode(ptr->left); //ptr�� �����ڽĿ��Ե� ��������Լ� ȣ��
        freeNode(ptr->right); //ptr�� �������ڽĿ��Ե� ��������Լ� ȣ��
        free(ptr); //ptr��� �޸� ����
    }
}