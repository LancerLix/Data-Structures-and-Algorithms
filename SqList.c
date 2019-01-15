#include <stdlib.h>
#include <stdio.h>

#define LIST_INIT_SIZE 100
#define LIST_SIZE_INCREMENT 10

typedef int ElemType;

typedef struct {
	ElemType* elem_base_addr;
	int cur_length;
	int max_length;
}SqList;

int InitSqList(SqList* L) {
	if(!L) {
		//illegal operation
		return -1;
	}
		
	L->elem_base_addr = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L->elem_base_addr) {
		return -1;
	}
	
	L->cur_length = 0;
	L->max_length = LIST_INIT_SIZE;
	
	return 0;
}

int SqListInsert(SqList* L, int index, ElemType elem) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(index < 1 || index > L->cur_length + 1) {	
		//parameter is not legal
		return -1;
	}
	
	if(!L->elem_base_addr) {
		//SqList is not init
		return -1;
	}
	
	if(L->cur_length == L->max_length) {
		ElemType* new_base_addr = (ElemType*) realloc(L->elem_base_addr,
								(L->max_length + LIST_SIZE_INCREMENT) * sizeof(ElemType));
		
		if(!new_base_addr) {
			return -1;
		}
		
		L->elem_base_addr = new_base_addr;
		L->max_length += LIST_SIZE_INCREMENT;
	}
	
	ElemType* insert_location = &L->elem_base_addr[index - 1];
	for(ElemType* p = &L->elem_base_addr[L->cur_length - 1]; p >= insert_location; p--) *(p + 1) = *p;
	
	*(insert_location) = elem;
	L->cur_length++;
	
	return 0;
}

int SqListDelete(SqList* L, int index) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(index < 1 || index > L->cur_length) {
		//parameter is not legal
		return -1;
	}
	
	if(!L->elem_base_addr) {
		//SqList is not init
		return -1;
	}
	
	ElemType* delete_location = &L->elem_base_addr[index - 1];
	for(ElemType* p = delete_location; p <= &L->elem_base_addr[L->cur_length - 1]; p++) *p = *(p + 1);
	
	L->cur_length--;
	
	return 0;
}

int SqListGetElem(SqList* L, int index, ElemType* outElem) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(index < 1 || index > L->cur_length) {
		//parameter is not legal
		return -1;
	}
	
	if(!L->elem_base_addr) {
		//SqList is not init
		return -1;
	}
	
	*outElem = L->elem_base_addr[index - 1];
	return 0;
}

int SqListGetIndex(SqList* L, ElemType elem, int (*compare)(ElemType, ElemType)) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->elem_base_addr) {
		//SqList in not init
		return -1;
	}
	
	int index = 1;
	
	while(index <= L->cur_length && !(*compare)(L->elem_base_addr[index - 1], elem)) index++;
	
	if(index <= L->cur_length) {
		return index;
	}else{
		return 0;
	}
}

void SqListTraverse(SqList* L, void (*visit)(ElemType)) {
	if(!L) {
		return;
	}
	
	if(!L->elem_base_addr) {
		return;
	}
	
	int index = 0;
	
	while(index < L->cur_length) {
		(*visit)(L->elem_base_addr[index++]);
	}
}

int SqListLength(SqList* L) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->elem_base_addr) {
		//SqList in not init
		return -1;
	}
	
	return L->cur_length;
}

int SqListEmpty(SqList* L) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->elem_base_addr) {
		//SqList in not init
		return -1;
	}
	
	return L->cur_length == 0;
}

void SqListClear(SqList* L) {
	if(!L) {
		//illegal operation
		return;
	}
	
	if(!L->elem_base_addr) {
		//SqList in not init
		return;
	}
	
	L->cur_length = 0;
}

void SqListDestory(SqList* L) {
	if(!L) {
		//illegal operation
		return;
	}
	
	if(!L->elem_base_addr) {
		//SqList in not init
		return;
	}
	
	for(ElemType* p = &L->elem_base_addr[L->cur_length - 1]; p >= L->elem_base_addr; p--) free(p);
	
	L->elem_base_addr = NULL;
	L->cur_length = 0;
	L->max_length = 0;
}

//Assume that the SqList La and Lb are sorted, and the output Lc is sorted too
void MergeSqList(SqList* La, SqList* Lb, SqList* Lc) {
	if(!La || !Lb || !Lc) {
		//illegal operation
		return;
	}
	
	if(!La->elem_base_addr || !Lb->elem_base_addr || !Lc->elem_base_addr) {
		//SqList in not init
		return;
	}
	
	int laIndex = 1, lbIndex = 1, lcIndex = 1;
	ElemType laValue;
	ElemType lbValue;
		
	while(laIndex <= SqListLength(La) && lbIndex <= SqListLength(Lb)) {		
		SqListGetElem(La, laIndex, &laValue);
		SqListGetElem(Lb, lbIndex, &lbValue);
		
		
		if(laValue <= lbValue) {
			SqListInsert(Lc, lcIndex++, laValue);
			laIndex++;
		}else {
			SqListInsert(Lc, lcIndex++, lbValue);
			lbIndex++;
		}
	}
	
	while(laIndex <= SqListLength(La)) {
		SqListGetElem(La, laIndex++, &laValue);
		SqListInsert(Lc, lcIndex++, laValue);
	}
	
	while(lbIndex <= SqListLength(Lb)) {
		SqListGetElem(Lb, lbIndex++, &lbValue);
		SqListInsert(Lc, lcIndex++, lbValue);
	}
}

//just for test, if the ElemType is not int, error
void visit(ElemType elem) {
	printf("%d ", elem);
}

int main(int argc, char** argv) {
	SqList La, Lb;
	
	//init sqlist a
	InitSqList(&La);
	for(int i = 1, data = 1; i <= 10; i++, data += 2) {
		SqListInsert(&La, i, data);
	}
	
	printf("Init La data:");
	SqListTraverse(&La, visit);
	printf("\n");
	
	SqListClear(&La);
	
	printf("La data after clear:");
	SqListTraverse(&La, visit);
	printf("\n");
	
	
	for(int i = 1, data = 1; i <= 5; i++, data++) {
		SqListInsert(&La, i, data);
	}
	printf("La data reconstruct:");
	SqListTraverse(&La, visit);
	printf("\n");
	
	//init sqlist b
	InitSqList(&Lb);
	for(int i = 1, data = 0; i <= 10; i++, data += 2) {
		SqListInsert(&Lb, i, data);
	}
	
	printf("Init Lb data:");
	SqListTraverse(&Lb, visit);
	printf("\n");
	
	SqListDelete(&Lb, 1);
	SqListDelete(&Lb, 1);
	SqListDelete(&Lb, SqListLength(&Lb));
	printf("Lb data after delete:");
	SqListTraverse(&Lb, visit);
	printf("\n");
	
	ElemType data;
	SqListGetElem(&Lb, 3, &data);
	printf("Lb data 3th:%d", data);
	printf("\n");
	
	SqList Lc;
	//init sqlist a
	InitSqList(&Lc);
	MergeSqList(&La, &Lb, &Lc);
	
	printf("Merge Lc data:");
	SqListTraverse(&Lc, visit);
	printf("\n");
	
	return 0;
}