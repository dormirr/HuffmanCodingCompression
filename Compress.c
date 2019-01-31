/*
���չ��������뽫�ļ�A����ΪHuffman�����ļ�B��
*/

#include "Custom.h"
#include "Node.c"

// ѹ������
int Compress(char *input_file_name, char *output_file_name)
{
	unsigned int i, j;
	//�ַ�����
	unsigned int char_kind;
	//�ݴ�8bits�ַ�
	unsigned char temporary_char;
	unsigned long file_length = 0;
	FILE *input_file, *output_file;
	CharactersFrequency temporary_node;
	unsigned int number_node;
	HuffmanTree huffman_tree;
	//������뻺����
	char code_the_buffer[256] = "\0";
	unsigned int code_length;

	/*
	** ��̬����256����㣬�ݴ��ַ�Ƶ�ȣ�
	** ͳ�Ʋ������������������ͷ�
	*/
	CharactersFrequency *temporary_char_frequency = (CharactersFrequency *)malloc(256 * sizeof(CharactersFrequency));

	//��ʼ���ݴ���
	for (i = 0; i < 256; ++i)
	{
		temporary_char_frequency[i].frequency = 0;
		//�����256���±���256���ַ���Ӧ
		temporary_char_frequency[i].uchar = (unsigned char)i;
	}

	//�����ļ�����ȡ�ַ�Ƶ��
	input_file = fopen(input_file_name, "rb");
	//�ж������ļ��Ƿ����
	if (input_file == NULL)
	{
		return -1;
	}

	//����һ���ַ�
	fread((char *)&temporary_char, sizeof(unsigned char), 1, input_file);
	while (!feof(input_file))
	{
		//ͳ���±��Ӧ�ַ���Ȩ�أ����������������ʿ���ͳ���ַ�Ƶ��
		++temporary_char_frequency[temporary_char].frequency;
		++file_length;
		//����һ���ַ�
		fread((char *)&temporary_char, sizeof(unsigned char), 1, input_file);
	}
	fclose(input_file);

	// ���򣬽�Ƶ��Ϊ��ķ�����޳�
	for (i = 0; i < 256 - 1; ++i)
	{
		for (j = i + 1; j < 256; ++j)
			if (temporary_char_frequency[i].frequency < temporary_char_frequency[j].frequency)
			{
				temporary_node = temporary_char_frequency[i];
				temporary_char_frequency[i] = temporary_char_frequency[j];
				temporary_char_frequency[j] = temporary_node;
			}
	}

	// ͳ��ʵ�ʵ��ַ����ࣨ���ִ�����Ϊ0��
	for (i = 0; i < 256; ++i)
	{
		if (temporary_char_frequency[i].frequency == 0)
		{
			break;
		}
	}
	char_kind = i;

	if (char_kind == 1)
	{
		//��ѹ�������ɵ��ļ�
		output_file = fopen(output_file_name, "wb");
		//д���ַ�����
		fwrite((char *)&char_kind, sizeof(unsigned int), 1, output_file);
		//д��Ψһ���ַ�
		fwrite((char *)&temporary_char_frequency[0].uchar, sizeof(unsigned char), 1, output_file);
		//д���ַ�Ƶ�ȣ�Ҳ�����ļ�����
		fwrite((char *)&temporary_char_frequency[0].frequency, sizeof(unsigned long), 1, output_file);
		free(temporary_char_frequency);
		fclose(output_file);
	}
	else
	{
		//�����ַ������������㽨������������������
		number_node = 2 * char_kind - 1;
		//��̬������������������
		huffman_tree = (Huffman *)malloc(number_node * sizeof(Huffman));

		//��ʼ��ǰchar_kind�����
		for (i = 0; i < char_kind; ++i)
		{
			//���ݴ�����ַ���Ƶ�ȿ����������
			huffman_tree[i].uchar = temporary_char_frequency[i].uchar;
			huffman_tree[i].frequency = temporary_char_frequency[i].frequency;
			huffman_tree[i].parent = 0;
		}
		//�ͷ��ַ�Ƶ��ͳ�Ƶ��ݴ���
		free(temporary_char_frequency);

		//��ʼ����number_node-char_kind�����
		for (; i < number_node; ++i)
		{
			huffman_tree[i].parent = 0;
		}

		//������������
		CreateTree(huffman_tree, char_kind, number_node);

		//���ɹ���������
		HuffmanCode(huffman_tree, char_kind);

		//д���ַ�����ӦȨ�أ�����ѹʱ�ؽ���������
		//��ѹ�������ɵ��ļ�
		output_file = fopen(output_file_name, "wb");
		//д���ַ�����
		fwrite((char *)&char_kind, sizeof(unsigned int), 1, output_file);
		for (i = 0; i < char_kind; ++i)
		{
			//д���ַ��������򣬶�����˳�򲻱䣩
			fwrite((char *)&huffman_tree[i].uchar, sizeof(unsigned char), 1, output_file);
			//д���ַ���ӦȨ��
			fwrite((char *)&huffman_tree[i].frequency, sizeof(unsigned long), 1, output_file);
		}

		//�������ַ���Ȩ����Ϣ����д���ļ����Ⱥ��ַ�����
		//д���ļ�����
		fwrite((char *)&file_length, sizeof(unsigned long), 1, output_file);
		//�Զ�������ʽ�򿪴�ѹ�����ļ�
		input_file = fopen(input_file_name, "rb");
		//ÿ�ζ�ȡ8bits
		fread((char *)&temporary_char, sizeof(unsigned char), 1, input_file);
		while (!feof(input_file))
		{
			//ƥ���ַ���Ӧ����
			for (i = 0; i < char_kind; ++i)
			{
				if (temporary_char == huffman_tree[i].uchar)
				{
					strcat(code_the_buffer, huffman_tree[i].code);
				}
			}
			//��8λ��һ���ֽڳ��ȣ�Ϊ����Ԫ
			while (strlen(code_the_buffer) >= 8)
			{
				//����ַ��ݴ�ռ䣬��Ϊ�ݴ��ַ���Ӧ����
				temporary_char = '\0';
				for (i = 0; i < 8; ++i)
				{
					//����һλ��Ϊ��һ��bit�ڳ�λ��
					temporary_char <<= 1;
					if (code_the_buffer[i] == '1')
					{
						//������Ϊ"1"��ͨ���������������ӵ��ֽڵ����λ
						temporary_char |= 1;
					}
				}
				//���ֽڶ�Ӧ��������ļ�
				fwrite((char *)&temporary_char, sizeof(unsigned char), 1, output_file);
				//���뻺��ȥ���Ѵ����ǰ��λ
				strcpy(code_the_buffer, code_the_buffer + 8);
			}
			//ÿ�ζ�ȡ8bits
			fread((char *)&temporary_char, sizeof(unsigned char), 1, input_file);
		}
		//���������8bits����
		code_length = strlen(code_the_buffer);
		if (code_length > 0)
		{
			temporary_char = '\0';
			for (i = 0; i < code_length; ++i)
			{
				temporary_char <<= 1;
				if (code_the_buffer[i] == '1')
				{
					temporary_char |= 1;
				}
			}
			//�������ֶδ�β���Ƶ��ֽڵĸ�λ
			temporary_char <<= 8 - code_length;
			//�������һ���ֽ�
			fwrite((char *)&temporary_char, sizeof(unsigned char), 1, output_file);      
		}

		// �ر��ļ�
		fclose(input_file);
		fclose(output_file);

		// �ͷ��ڴ�
		for (i = 0; i < char_kind; ++i)
		{
			free(huffman_tree[i].code);
		}
		free(huffman_tree);
	}
}