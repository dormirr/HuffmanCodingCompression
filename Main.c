#include "Custom.h"
#include "Node.c"

int main()
{
	while (1)
	{
		int n, flag = 0;
		char name[2222], names[2222], input_file_name[2222] = "D:\\�����\\Documents\\���ݽṹ���㷨�ۺ����\\�ù���������ʵ��ѹ�����\\��Դ�ļ�\\", output_file_name[2222] = "D:\\�����\\Documents\\���ݽṹ���㷨�ۺ����\\�ù���������ʵ��ѹ�����\\��Դ�ļ�\\";
		printf("1��ѹ��\n2����ѹ��\n���������˳�,��ѡ���ܣ�");
		scanf("%d", &n);
		getchar();
		switch (n)
		{
		case 1: 
			printf("�����뽫Ҫ���в������ļ�����");
			gets(name);
			strcat(input_file_name, name);
			printf("��������в�����������ļ�����");
			gets(names);
			strcat(output_file_name, names); 
			printf("���ڽ���ѹ��\n");

			flag = Compress(input_file_name, output_file_name);
			break;
		case 2: 
			printf("�����뽫Ҫ���в������ļ�����");
			gets(name);
			strcat(input_file_name, name);
			printf("��������в�����������ļ�����");
			gets(names);
			strcat(output_file_name, names); 
			printf("���ڽ��н�ѹ��\n");

			flag = Uncompress(input_file_name, output_file_name);
			break;
		default:
			return 0;
		}

		if (flag == -1)
		{
			printf("�ļ�\"%s\"������!\n", input_file_name);
		}
		else
		{
			printf("���!\n\n");
		}
	}
}
