// ͳ���ַ�Ƶ�ȵ���ʱ���
typedef struct {
	unsigned char uchar;			// ��8bitsΪ��Ԫ���޷����ַ�
	unsigned long frequency;		// ÿ�ࣨ�Զ����Ʊ������֣��ַ�����Ƶ��
} CharactersFrequency;

// �����������
typedef struct {
	unsigned char uchar;				// ��8bitsΪ��Ԫ���޷����ַ�
	unsigned long frequency;			// ÿ�ࣨ�Զ����Ʊ������֣��ַ�����Ƶ��
	char *code;						// �ַ���Ӧ�Ĺ��������루��̬����洢�ռ䣩
	int parent, lchild, rchild;		// ����˫�׺����Һ���
} Huffman, *HuffmanTree;