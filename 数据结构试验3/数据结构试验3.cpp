//树形图创作者
#include "pch.h"
#include <iostream>
#include <stdlib.h>
struct TreeNode {
	struct TreeNode * LeftNode;
	int data;
	struct TreeNode * RightNode;
};
TreeNode* FidNode(TreeNode * tree, int value);//查找节点
void AddNode(TreeNode **tree, int value);//添加节点
void DelNode(TreeNode **tree, int value);//删除节点
void PriNode(TreeNode * tree, int value);//打印树
TreeNode* FidMax(TreeNode * tree); //查找最大
TreeNode* FidMin(TreeNode * tree); //查找最小
void CreatTree(TreeNode **tree); //创建树
void FirPut(TreeNode * tree); //先序遍历
void SecPut(TreeNode * tree); //中序遍历
void ThrPut(TreeNode * tree); //后序遍历
void LevPut(TreeNode * tree); //层序遍历
void PriMain();
int  Judgeint(int x);

int main()
{
	TreeNode * tree = NULL;
	int x;
	PriMain();
	while (1)
	{
		switch (Judgeint(1))
		{
		case 0: system("cls"); PriNode(tree, 0); PriMain(); break;
		case 1: if (tree == NULL)
		{
			CreatTree(&tree);
			getchar();
			break;
		}
				else
		{
			printf("树已经创建过 请勿重复创建\n");
		}
		case 2:	
			int i;
			printf("请输入要插入的节点\n");
			AddNode(&tree, Judgeint(2));
			break;
		case 3:
			printf("请输入要删除的节点\n");
			DelNode(&tree, Judgeint(3));
			break;
		case 4:
			printf("请输入要查找的节点\n");
			if (FidNode(tree, Judgeint(4)))
			{
				printf("节点存在 \n");
			}
			else
			{
				printf("节点不存在 \n");
			}
			break;
		case 5:
			printf("树中最大的节点为 ： %d\n", FidMax(tree)->data);
			break;
		case 6:
			printf("树中最小的节点为 ： %d\n", FidMin(tree)->data);
			break;
		case 7:
			printf("前序遍历 ：");
			FirPut(tree);
			printf("\n");
			break;
		case 8:
			printf("中序遍历 : ");
			SecPut(tree);
			printf("\n");
			break;
		case 9:
			printf("后序遍历 : ");
			ThrPut(tree);
			printf("\n");
			break;
		case 10:
			printf("层序遍历 : ");
			LevPut(tree);
			printf("\n");
			break;
		case 11:
			system("cls");
			PriMain();
			break;
		case 12:
			return 0;
		default:
			printf("输入错误 请重新输入 \n");
			break;
		}
	}
}

void AddNode(TreeNode ** tree, int value)
{
	if (*tree == NULL)
	{
		*tree = (TreeNode*)malloc(sizeof(TreeNode));
		if (*tree != NULL)
		{
			(*tree)->LeftNode = NULL;
			(*tree)->data = value;
			(*tree)->RightNode = NULL;
		}
		else
		{
			printf("Error AddNode Malloc Fail\n");
		}
	}
	else
	{
		if (value < (*tree)->data)
			AddNode(&((*tree)->LeftNode), value);
		if (value > (*tree)->data)
			AddNode(&((*tree)->RightNode), value);
	}
}//添加节点

TreeNode* FidNode(TreeNode * tree, int value)
{
	TreeNode * Node = tree;
	while (Node != NULL && Node->data != value)
	{
		if (value < Node->data)
			Node = Node->LeftNode;
		else
			Node = Node->RightNode;
	}
	if (Node == NULL)
		return NULL;
	else
		return Node;
}//查找节点

void PriNode(TreeNode * tree, int value)
{
	while (tree != NULL)
	{
		PriNode(tree->RightNode, value + 4);
		for (int i = 0; i < value; i++)
		{
			printf(" ");
		}
		printf("%d\n", tree->data);

		PriNode(tree->LeftNode, value + 4);

		tree = NULL;
	}
}

TreeNode* FidMax(TreeNode * tree)
{
	while (tree->RightNode != NULL)
	{
		tree = tree->RightNode;
	}
	return tree;
} //查找最大 

TreeNode* FidMin(TreeNode * tree)
{
	while (tree->LeftNode != NULL)
	{
		tree = tree->LeftNode;
	}
	return tree;
}

void DelNode(TreeNode **tree, int value)
{
	if (FidNode(*tree, value))
	{
		TreeNode * Node = *tree;
		TreeNode * PNode = NULL;
		TreeNode * SNode = NULL;
		TreeNode * PSNode = NULL;
		while (Node != NULL && Node->data != value)
		{
			PNode = Node;
			if (value < Node->data)
				Node = Node->LeftNode;
			else
				Node = Node->RightNode;
		}
		if (Node->LeftNode == NULL && Node->RightNode == NULL)//左右无叶节点
		{
			if (PNode->LeftNode == Node)
			{
				PNode->LeftNode = NULL;
			}
			else
			{
				PNode->RightNode = NULL;
			}
		}
		else if (Node->LeftNode != NULL && Node->RightNode != NULL)//左右有叶节点
		{
			PSNode = Node;
			SNode = Node->LeftNode;
			while (SNode->RightNode != NULL) //查找代替节点和其父节点
			{
				PSNode = SNode;
				SNode = SNode->RightNode;
			}
			if (PNode == NULL)
				*tree = SNode;
			else if (PNode->LeftNode == Node) //用代替结点替换删除结点
				PNode->LeftNode = SNode;
			else
				PNode->RightNode = SNode;

			if (PSNode->LeftNode == SNode)//让代替结点的父节点左/右指针指向代替结点的左/右指针
				PSNode->LeftNode = SNode->RightNode;
			else
				PSNode->RightNode = SNode->LeftNode;
			SNode->RightNode = Node->RightNode;//让代替结点左右指针指向删除结点左右指针
			SNode->LeftNode = Node->LeftNode;
		}
		else	//单边有叶节点
		{
			if (PNode->LeftNode == Node)
			{
				if (Node->LeftNode == NULL)
					PNode->LeftNode = Node->RightNode;
				else
					PNode->LeftNode = Node->LeftNode;
			}
			else
			{
				if (Node->RightNode == NULL)
					PNode->RightNode = Node->LeftNode;
				else
					PNode->RightNode = Node->RightNode;
			}
		}
		free(Node);
		return;
	}
	else
	{
		printf("要删除的节点不存在 ERROR : DelNode \n");
		return;
	}
}//删除节点 

void FirPut(TreeNode * tree)
{
	if (tree == NULL)
	{
		return;
	}
	printf("%d ", tree->data);
	FirPut(tree->LeftNode);
	FirPut(tree->RightNode);
}//先序遍历

void SecPut(TreeNode * tree)
{
	if (tree == NULL)
	{
		return;
	}
	SecPut(tree->LeftNode);
	printf("%d ", tree->data);
	SecPut(tree->RightNode);
} //中序遍历 

void ThrPut(TreeNode * tree)
{
	if (tree == NULL)
	{
		return;
	}
	ThrPut(tree->LeftNode);
	ThrPut(tree->RightNode);
	printf("%d ", tree->data);
} //后序遍历

void LevPut(TreeNode * tree)
{
	struct Queue
	{
		TreeNode * data;
		struct Queue * Next;
	};
	Queue *head, *end, *data;
	head = (Queue*)malloc(sizeof(Queue));
	head->data = tree;
	head->Next = NULL;
	end = head;

	do
	{
		TreeNode * Temp = NULL;
		Temp = head->data;
		//head = head->Next;

		if (Temp->LeftNode != NULL)
		{
			data = (Queue*)malloc(sizeof(Queue));
			data->data = NULL;
			data->Next = NULL;
			data->data = Temp->LeftNode;
			end->Next = data;
			end = end->Next;
		}
		if (Temp->RightNode != NULL)
		{
			data = (Queue*)malloc(sizeof(Queue));
			data->data = NULL;
			data->Next = NULL;
			data->data = Temp->RightNode;
			end->Next = data;
			end = end->Next;
		}
		printf("%d ", Temp->data);
		head = head->Next;
	} while (head != NULL);
}//层序遍历

void CreatTree(TreeNode **Tree)
{
	printf("请输入要创建树的数据 \n输入的第一个数据作为根节点\n结尾用任意字母结束输入\n");
	int x = 0;
	while (scanf_s("%d", &x))
	{
		AddNode(Tree, x);
	}
	printf("创建完成\n");
}//创建树 ？？？

void PriMain()
{
	printf("____________________________________________\n");
	printf("| 0.打印二叉树                              |\n");
	printf("| 1.创建二叉树                              |\n");
	printf("| 2.添加节点                                |\n");
	printf("| 3.删除节点                                |\n");
	printf("| 4.查找节点                                |\n");
	printf("| 5.查找最大节点                            |\n");
	printf("| 6.查找最小节点                            |\n");
	printf("| 7.打印前序遍历结果                        |\n");
	printf("| 8.打印中序遍历结果                        |\n");
	printf("| 9.打印后序遍历结果                        |\n");
	printf("|10.打印层序遍历结果                        |\n");
	printf("|11.清空屏幕                                |\n");
	printf("|12.退出                                    |\n");
	printf("|___________________________________________|\n");
	return;
}

int  Judgeint(int x)
{
	int i = NULL;
	while (1)
	{
		if (scanf_s("%d", &i) == 0)
		{
			printf("输入错误请 重新输入 Error : %d\n", x);
			rewind(stdin);
		}
		else
		{
			return i;
		}
	}
}
//netsh interface ip set DNS "本地连接" static 8.8.8.8
