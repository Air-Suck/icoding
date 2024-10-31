int str_compare(const char* ptr1, const char* ptr2) {
	int i;
	for (i = 0;ptr1[i] != '\0' && ptr2[i] != '\0';i++) {
		//若第一个字符串中的字符为大写字母
		if (ptr1[i] >= 65 && ptr1[i] <= 90) {
			//若第二个字符串中的字符为小写字母，此时经过阿斯卡码调整后进行比较（仅当大小写对应时进行该规则）
			if (ptr2[i] >= 97 && ptr2[i] <= 122) {
				if (ptr1[i] == ptr2[i] - 32) {
					continue;
				}
				else if (ptr1[i] < ptr2[i]) {
					return -1;
				}
				else if (ptr1[i] > ptr2[i]) {
					return 1;
				}
			}
			//若第二个字符串中的字符为大写字母或者数字，直接比较
			else {
				if (ptr1[i] == ptr2[i]) {
					continue;
				}
				else if (ptr1[i] < ptr2[i]) {
					return -1;
				}
				else if (ptr1[i] > ptr2[i]) {
					return 1;
				}
			}
		}
		//若第一个字符串中的字符为小写字母
		else if (ptr1[i] >= 97 && ptr1[i] <= 122) {
			//若第二个字符串中的字符为大写字母，此时经过阿斯卡码调整后进行比较(仅当大小写对应时进行该规则)
			if (ptr2[i] >= 65 && ptr2[i] <= 90) {
				if (ptr1[i] - 32 == ptr2[i]) {
					continue;
				}
				else if (ptr1[i] < ptr2[i]) {
					return -1;
				}
				else if (ptr1[i] > ptr2[i]) {
					return 1;
				}
			}
			//若第二个字符串中的字符为小写字母或者数字，直接进行比较
			else {
				if (ptr1[i] == ptr2[i]) {
					continue;
				}
				else if (ptr1[i] < ptr2[i]) {
					return -1;
				}
				else if (ptr1[i] > ptr2[i]) {
					return 1;
				}
			}
		}
		//若第一个字符串中的字符为数字，此时直接进行比较
		else {
			if (ptr1[i] == ptr2[i]) {
				continue;
			}
			else if (ptr1[i] < ptr2[i]) {
				return -1;
			}
			else if (ptr1[i] > ptr2[i]) {
				return 1;
			}
		}
	}
	//退出时一定有一个字符串走空，若两个字符串都走空说明字符串相同
	if (ptr1[i] == '\0' && ptr2[i] == '\0') {
		return 0;
	}
	//若第一个字符串走空说明第一个字符串短，输出小于零的值
	else if (ptr1[i] == '\0' && ptr2[i] != '\0') {
		return -1;
	}
	//若第二个字符串走空说明第一个字符串长，输出大于零的值
	else if (ptr2[i] == '\0' && ptr1[i] != '\0') {
		return 1;
	}
	return 0;
}