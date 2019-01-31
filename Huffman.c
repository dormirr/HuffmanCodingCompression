/*
��������������õ����ַ��Ĺ��������롣
*/

#include "Custom.h"
#include "Node.c"

//�ҵ���С�ʹ�С���������
void Select(Huffman *huffman_tree, unsigned int n, int *a, int *b)
{
	unsigned int i;
	unsigned long min = ULONG_MAX;
	for (i = 0; i < n; ++i)
		if (huffman_tree[i].parent == 0 && huffman_tree[i].frequency < min)
		{
			min = huffman_tree[i].frequency;
			*a = i;
		}
	//�������ѡ��
	huffman_tree[*a].parent = 1;

	min = ULONG_MAX;
	for (i = 0; i < n; ++i)
		if (huffman_tree[i].parent == 0 && huffman_tree[i].frequency < min)
		{
			min = huffman_tree[i].frequency;
			*b = i;
		}
}

//������������
void CreateTree(Huffman *huffman_tree, unsigned int char_kind, unsigned int number_node)
{
	unsigned int i;
	int a, b;
	for (i = char_kind; i < number_node; ++i)
	{
		//ѡ����С���������
		Select(huffman_tree, i, &a, &b);
		huffman_tree[a].parent = huffman_tree[b].parent = i;
		huffman_tree[i].lchild = a;	
		huffman_tree[i].rchild = b;
		huffman_tree[i].frequency = huffman_tree[a].frequency + huffman_tree[b].frequency;
	}
}

//���ɹ���������
void HuffmanCode(Huffman *huffman_tree, unsigned int char_kind)
{
	unsigned int i;
	int cur, next, index;
	//�ݴ���룬���256��Ҷ�ӣ����볤�Ȳ�����255
	char *code_temporarily = (char *)malloc(256 * sizeof(char));
	code_temporarily[256 - 1] = '\0';

	for (i = 0; i < char_kind; ++i)
	{
		//������ʱ�ռ�������ʼ��
		index = 256 - 1;

		//��Ҷ�����������������
		for (cur = i, next = huffman_tree[i].parent; next != 0; cur = next, next = huffman_tree[next].parent)
		{
			if (huffman_tree[next].lchild == cur)
			{
				//��0��
				code_temporarily[--index] = '0';
			}
			else
			{
				//�ҡ�1��
				code_temporarily[--index] = '1';
			}
		}
		//Ϊ��i���ַ����붯̬����洢�ռ� 
		huffman_tree[i].code = (char *)malloc((256 - index) * sizeof(char));
		//���򱣴���뵽�������Ӧ����
		strcpy(huffman_tree[i].code, &code_temporarily[index]);
	}
	//�ͷű�����ʱ�ռ�
	free(code_temporarily);
}