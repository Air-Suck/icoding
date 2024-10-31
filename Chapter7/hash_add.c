#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

extern long hash_string(const char* key);

typedef enum {
    HASH_OK,
    HASH_ERROR,
    HASH_ADDED,
    HASH_REPLACED_VALUE,
    HASH_ALREADY_ADDED,
    HASH_DELETED,
    HASH_NOT_FOUND,
} HASH_RESULT;

typedef struct __HashEntry HashEntry;

struct __HashEntry {
    union {
        char* str_value;
        double dbl_value;
        int       int_value;
    } key;
    union {
        char* str_value;
        double dbl_value;
        int       int_value;
        long   long_value;
        void* ptr_value;
    } value;
    HashEntry* next;
};

struct __HashTable {
    HashEntry** bucket;
    int size;
    HASH_RESULT last_error;
};
typedef struct __HashTable HashTable;

//关键点：key的值唯一
HASH_RESULT hash_add_int(HashTable* table, const char* key, int value) {
    HASH_RESULT reValue;
    //指针判空
    if (table == NULL || key == NULL) {
        reValue = HASH_ERROR;
        return reValue;
    }
    //计算当前key的哈希地址（记住要%size）
    long hashPlace = hash_string(key)%table->size;
    //找到当前key可能存在的哈希地址
    //如果当前哈希地址存在单链表，就开始寻找是否有相同key的元素
    if (table->bucket[hashPlace] != NULL) {
        HashEntry* temp = table->bucket[hashPlace];
        //寻找当前单链表中是否有key相同的元素
        while (temp != NULL && strcmp(temp->key.str_value,key)!=0) {
            temp = temp->next;
        }
        //如果temp==NULL说明找到当前单链表尾，即没有key相同的元素，此时插入
        if (temp == NULL) {
            temp = (HashEntry*)malloc(sizeof(HashEntry));
            //指针判空
            if (temp == NULL) {
                reValue = HASH_ERROR;
                return reValue;
            }
            //给key申请空间
            temp->key.str_value = (char*)malloc(sizeof(char)*strlen(key));
            //指针判空
            if (temp->key.str_value == NULL) {
                reValue = HASH_ERROR;
                return reValue;
            }
            //将key复制给当前节点
            strcpy(temp->key.str_value, key);
            temp->value.int_value = value;
            //头插法插入节点
            temp->next = table->bucket[hashPlace];
            table->bucket[hashPlace] = temp;
            reValue = HASH_ADDED;
            return reValue;
        }
        //否则就是找到了key相同的元素
        else {
            //说明找到了key和value都相同的元素
            if (temp->value.int_value == value) {
                reValue = HASH_ALREADY_ADDED;
                return reValue;
            }
            //否则就是找到了key相同但是value不同的元素
            else {
                temp->value.int_value = value;
                reValue = HASH_REPLACED_VALUE;
                return reValue;
            }
        }
    }
    //如果当前哈希地址不存在单链表，那么必然不存在key相同的元素，直接新建单链表
    else {
        //初始化头结点（头结点存储数据）
        table->bucket[hashPlace] = (HashEntry*)malloc(sizeof(HashEntry));
        //指针判空
        if (table->bucket[hashPlace] == NULL) {
            reValue = HASH_ERROR;
            return reValue;
        }
        table->bucket[hashPlace]->next = NULL;
        //给结点的key申请空间
        table->bucket[hashPlace]->key.str_value = (char*)malloc(sizeof(char) * strlen(key));
        //指针判空
        if (table->bucket[hashPlace]->key.str_value == NULL) {
            reValue = HASH_ERROR;
            return reValue;
        }
        //将key复制给当前节点的key
        strcpy(table->bucket[hashPlace]->key.str_value, key);
        table->bucket[hashPlace]->value.int_value = value;
        reValue = HASH_ADDED;
        return reValue;
    }
}