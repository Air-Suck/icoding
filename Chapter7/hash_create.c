#include<stdio.h>
#include <stdlib.h>
#include <string.h>

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

// 创建大小为hash_size的哈希表，创建成功后返回HashTable类型的指针，否则返回NULL。
HashTable* create_hash(int hash_size) {
    //申请哈希表的指针，其申请空间就是其对应的结构体大小
    HashTable* p = (HashTable*)malloc(sizeof(HashTable));
    //指针判空
    if (p == NULL) {
        return NULL;
    }
    //申请指针数组的二级指针，其申请空间就是指针数组的大小，指针数组的元素为指针HashEntry*，所以申请空间为hash_size * sizeof(HashEntry*)
    p->bucket = (HashEntry**)malloc(hash_size * sizeof(HashEntry*));
    //指针判空
    if (p->bucket == NULL) {
        free(p);
        return NULL;
    }
    //用menset函数给指针数组初始化
    memset(p->bucket, 0, hash_size * sizeof(HashEntry*));
    p->size = hash_size;
    p->last_error = HASH_OK;
    return p;
}