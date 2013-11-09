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

/* 问题描述：
   字符串中RN用N替换， R用N替换

   解决思路：
   用两个指针p,q； p指向正在处理的字符，q指向处理过的。
   1. p若不是R，则 *q++ = *q++; 直接拷贝
   2. p若是R，则检验一下下一个字符，若不是N，则转1
   3. 若下一个字符是N，则p前进两步，*q++ = 'N'

   注意：当用长替换短字符的时候，不能用此方法
   */