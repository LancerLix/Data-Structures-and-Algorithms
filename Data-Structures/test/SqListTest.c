#include <stdlib.h>
#include <stdio.h>

#include "SqList.h"

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