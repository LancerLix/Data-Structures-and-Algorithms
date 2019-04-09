#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#define LIST_INIT_SIZE 100
#define LIST_SIZE_INCREMENT 10

typedef int ElemType;

typedef struct {
	ElemType* elem_base_addr;
	int cur_length;
	int max_length;
}SqList;

int InitSqList(SqList* L);
int SqListInsert(SqList* L, int index, ElemType elem);
int SqListDelete(SqList* L, int index);
int SqListGetElem(SqList* L, int index, ElemType* outElem);
int SqListGetIndex(SqList* L, ElemType elem, int (*compare)(ElemType, ElemType));
void SqListTraverse(SqList* L, void (*visit)(ElemType));
int SqListLength(SqList* L);
int SqListEmpty(SqList* L);
void SqListClear(SqList* L);
void SqListDestory(SqList* L);
void MergeSqList(SqList* La, SqList* Lb, SqList* Lc);

#endif