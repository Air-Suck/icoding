#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
// #include<stdlib.h>

//注意下面函数传参传的是const指针，所以这里传参也用const防止出现类型不同的警告
int strLen(const char* str) {
	int len = 0;
	while (str[len] != '\0')len++;
	return len;
}

int str_replace(const char* in, char* out, int outlen, const char* oldstr, const char* newstr) {
	int i, j, k,m;
	int outIndex = 0;
	int recordNum = 0;
	int length = strLen(in);
	int inLen = strLen(in);
	int newLen = strLen(newstr);
	int oldLen = strLen(oldstr);
	//最外层循环应该只需要遍历原字符串即可
	for (i = 0;i < inLen;i++) {
		//判断是否是子串
		j = i;
		for (k = 0;k<oldLen;) {
			if (in[j] == oldstr[k]&&k< oldLen) {
				j++;
				k++;
			}
			else {
				break;
			}
		}
		//如果当前串需要替换的话
		if (k == oldLen) {
			//判断替换后长度是否会越界（注意加一是空字符的空间）
			//注意length在每次替换后都要更新
			if (length - oldLen + newLen+1 > outlen) {
				//如果无法再替换了要将原字符串的剩余字符复制给out
				while (in[i] != '\0') {
					out[outIndex] = in[i];
					i++;
					outIndex++;
				}
				//注意空字符的补充
				out[outIndex] = '\0';
				return recordNum;
			}
			//可以替换时
			else {
				//注意m每次替换时都要重置
				m = 0;
				while (newstr[m] != '\0') {
					out[outIndex] = newstr[m];
					m++;
					outIndex++;
				}
				//每次替换后length都要更新用于判断下次是否可以替换
				length = length - oldLen + newLen;
				recordNum++;
				//替换成功后要跳过原字符串中的部分元素
				//原因：例如要在bbb中将bb替换为1
				//此时若不跳过原字符串中将有两个bb子串，所以要跳过已经被替换的元素（前两个b）
				//下次进入循环时就从第三个元素开始比对
				i += oldLen-1;
			}
		}
		//当当前串不是目标串时，直接将原串里面的第一个元素赋值给输出串
		else {
			out[outIndex] = in[i];
			outIndex++;
		}
	}
	//注意补充空字符
	out[outIndex] = '\0';
	return recordNum;
}

int main() {
	char in[100];
	char out[100];
	char old[100];
	char new[100];
	scanf("%s", in);
	scanf("%s", old);
	scanf("%s", new);
	printf("%d\n", str_replace(in, out, 14, old, new));
	printf("%s", out);
	return 0;
}