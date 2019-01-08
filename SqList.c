#define LIST_INIT_SIZE 100
#define LIST_SIZE_INCREMENT 10

typedef int ElemType

typedef struct {
	ElemType* elem_base_addr;
	int cur_length;
	int max_length;
}SqList;

int InitSqList(SqList& L) {
	L.elem_base_addr = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem_base_addr) {
		return -1;
	}
	
	L.cur_length = 0;
	L.max_length = LIST_INIT_SIZE;
	
	return 0;
}

int SqListInsert(SqList& L, int index, ElemType elem) {
	if(index < 0 || index > L.length + 1) {	
		return -1;
	}
	
	if(L.cur_length == L.max_length) {
		ElemType* new_base_addr = (ElemType*) realloc(L.elem_base_addr,
								(L.max_length + LIST_SIZE_INCREMENT) * sizeof(ElemType));
		
		if(!new_base_addr) {
			return -1;
		}
		
		L.elem_base_addr = new_base_addr;
		L.max_length += LIST_SIZE_INCREMENT;
	}
	
	ElemType* insert_location = &L.elem_base_addr[index - 1];
	for(ElemType* p = &L.elem_base_addr[L.cur_length - 1]; p >= insert_location; p--) *(p + 1) = *p;
	
	*(insert_location) = elem;
	L.cur_length++;
	
	return 0;
}

int SqListDelete(SqList& L, int index) {
	if(index < 0 || index > L.length) {
		return -1;
	}
	
	ElemType* delete_location = L.elem_base_addr[index - 1];
	for(ElemType* p = &L.elem_base_addr[L.cur_length -1]; p > delete_location; p--) *(p - 1) = *p;
	
	L.cur_length--;
	
	return 0;
}

ElemType SqListGetElem(SqList& L, int index) {
	if(index < 0 || index > L.length) {
		return -1;
	}
	
	return L.elem_base_addr[index - 1];
}

int SqListGetIndex(SqList& L, ElemType elem, int (*compare)(ElemType, ElemType)) {
	int index = 1;
	
	while(index <= L.length && !(*compare)(L.elem_base_addr[index - 1], elem)) index++;
	
	if(index <= L.length) {
		return index;
	}else{
		return 0;
	}
	
}

int SqListLength(SqList& L) {
	return L.cur_length;
}

int SqListEmpty(SqList& L) {
	return L.cur_length == 0;
}

void SqListClear(SqList& L) {
	L.cur_length = 0;
}

void SqListDestory(SqList& L) {
	for(ElemType* p = &L.elem_base_addr[L.cur_length - 1]; p >= L.elem_base_addr; p--) free(p);
	
	L.elem_base_addr = NULL;
	L.cur_length = 0;
	L.max_length = 0;
}

//Assume that the SqList La and Lb are sorted, and the output Lc is sorted too
void MergeSqList(SqList& La, SqList& Lb, SqList& Lc) {
	InitSqList(Lc);
	
	int laIndex = 1;
	int lbIndex = 1;
	int lcIndex = 1;
	
	while(laIndex <= SqListLength(La) && lbIndex <= SqListLength(Lb)) {
		ElemType laValue = SqListGetElem(laIndex);
		ElemType lbValue = SqListGetElem(lbIndex);
		
		if(laValue <= lbValue) {
			SqListInsert(Lc, lcIndex++, laValue);
			laIndex++;
		}else {
			SqListInsert(Lc, lcIndex++, lbValue);
			lbIndex++;
		}
	}
	
	while(laIndex <= SqListLength(La)) {
		SqListInsert(Lc, lcIndex++, laValue);
		laIndex++;
	}
	
	while(lbIndex <= SqListLength(Lb)) {
		SqListInsert(Lc, lcIndex++, lbValue);
		lbIndex++;
	}
}