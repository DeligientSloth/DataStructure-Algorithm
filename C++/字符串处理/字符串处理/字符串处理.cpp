// 字符串处理.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<assert.h>
using namespace std;
/*各种字符串处理函数的实现*/
char* strcat(char* dest, char* src) {
	assert(dest != NULL&&src != NULL);
	char* address = dest;
	while (*dest != '\0') dest++;
	while ((*(dest++) = *(src++)) != '\0');
	return address;
}
/*char* strcpy() {

}
char* replace() {

}*/

int main()
{
	char* s1 = "abc", *s2 = "def";
	strcat(s1, s2);
    return 0;
}

