// StripCharacter.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LF 'N'
#define CR 'R'

void StripCharacter(char *buf)
{
	int len = strlen(buf);
	char *p = buf, *q = buf;
	while( p < (buf + len))
	{
		if( *p != CR)
			*q++ = *p++;
		else
		{
			if( p < (buf + len - 1) )  //check next character
			{
				if( *(p+1) == LF)
				{
					p += 2;
					*q++ = LF;
				}
				else
				{
					p += 1;
					*q++ = LF;
				}
			}
			else                     // end with 'R'
				*q++ = LF;
		}
	}
}

int main(int argc, char* argv[])
{
	char str[] = "abcdefNefdfRNdfelsfeRdfsdfe";
	StripCharacter(str);
	printf("%s\n", str);


	system("pause");
	return 0;
}

/* ����������
   �ַ�����RN��N�滻�� R��N�滻

   ���˼·��
   ������ָ��p,q�� pָ�����ڴ�����ַ���qָ������ġ�
   1. p������R���� *q++ = *q++; ֱ�ӿ���
   2. p����R�������һ����һ���ַ���������N����ת1
   3. ����һ���ַ���N����pǰ��������*q++ = 'N'

   ע�⣺���ó��滻���ַ���ʱ�򣬲����ô˷���
   */