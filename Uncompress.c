/*
���룺���ļ�B�������룬�õ��ļ�C
*/

#include "Custom.h"
#include "Node.c"

int Uncompress(char *input_file_name, char *output_file_name)
{
	unsigned int i;
	unsigned long file_length;
	//�����ļ�д�볤��
	unsigned long file_write_length = 0;
	FILE *input_file, *output_file;
	//�洢�ַ�����
	unsigned int char_kind;
	unsigned int number_node;
	HuffmanTree huffman_tree;
	//�ݴ�8bits����
	unsigned char temporary_char;
	//������ڵ���������ƥ�����ʹ��
	unsigned int root;

	//�Զ����Ʒ�ʽ��ѹ���ļ�
	input_file = fopen(input_file_name, "rb");

	if (input_file == NULL)
	{
		return -1;
	}

	//��ȡѹ���ļ�ǰ�˵��ַ�����Ӧ���룬�����ؽ���������
	//��ȡ�ַ�������
	fread((char *)&char_kind, sizeof(unsigned int), 1, input_file);
	if (char_kind == 1)
	{
		//��ȡΨһ���ַ�
		fread((char *)&temporary_char, sizeof(unsigned char), 1, input_file);
		//��ȡ�ļ�����
		fread((char *)&file_length, sizeof(unsigned long), 1, input_file);
		//��ѹ�������ɵ��ļ�
		output_file = fopen(output_file_name, "wb");
		while (file_length--)
		{
			fwrite((char *)&temporary_char, sizeof(unsigned char), 1, output_file);
		}
		fclose(input_file);
		fclose(output_file);
	}
	else
	{
		//�����ַ������������㽨������������������ 
		number_node = 2 * char_kind - 1;
		//��̬��������������ռ�
		huffman_tree = (Huffman *)malloc(number_node * sizeof(Huffman));
		//��ȡ�ַ�����ӦȨ�أ�������������ڵ�
		for (i = 0; i < char_kind; ++i)
		{
			//�����ַ�
			fread((char *)&huffman_tree[i].uchar, sizeof(unsigned char), 1, input_file);
			//�����ַ���ӦȨ��
			fread((char *)&huffman_tree[i].frequency, sizeof(unsigned long), 1, input_file);
			huffman_tree[i].parent = 0;
		}
		//��ʼ����number_node-char_kins������parent
		for (; i < number_node; ++i)
		{
			huffman_tree[i].parent = 0;
		}

		//�ؽ�������������ѹ��ʱ��һ�£�
		CreateTree(huffman_tree, char_kind, number_node);

		//�����ַ���Ȩ����Ϣ�������Ŷ�ȡ�ļ����Ⱥͱ��룬���н���
		//�����ļ�����
		fread((char *)&file_length, sizeof(unsigned long), 1, input_file);
		//��ѹ�������ɵ��ļ�
		output_file = fopen(output_file_name, "wb");
		root = number_node - 1;
		while (1)
		{
			//��ȡһ���ַ����ȵı��루8λ��
			fread((char *)&temporary_char, sizeof(unsigned char), 1, input_file);

			//�����ȡ��һ���ַ����ȵı���
			for (i = 0; i < 8; ++i)
			{
				//�ɸ�����ֱ��Ҷ�ڵ�����ƥ������Ӧ�ַ�
				if (temporary_char & 128)
				{
					root = huffman_tree[root].rchild;
				}
				else
				{
					root = huffman_tree[root].lchild;
				}

				if (root < char_kind)
				{
					fwrite((char *)&huffman_tree[root].uchar, sizeof(unsigned char), 1, output_file);
					++file_write_length;
					//�����ļ����ȣ������ڲ�ѭ��
					if (file_write_length == file_length)
					{
						break;
					}
					//��λΪ��������ƥ����һ���ַ�
					root = number_node - 1;
				}
				//�����뻺�����һλ�Ƶ����λ����ƥ��
				temporary_char <<= 1;
			}
			//�����ļ����ȣ��������ѭ��
			if (file_write_length == file_length)
			{
				break;
			}
		}

		//�ر��ļ�
		fclose(input_file);
		fclose(output_file);

		//�ͷ��ڴ�
		free(huffman_tree);
	}
}