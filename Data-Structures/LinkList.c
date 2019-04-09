#include "LinkList.h"

int InitLinkList(LinkList* L) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	LinkNode* headNode = (LinkNode*)malloc(sizeof(LinkNode));
	if(!headNode) {
		return -1;
	}
	
	headNode->next = NULL;
	
	L->head = headNode;
	L->tail = headNode;
	L->length = 0;
	return 0;
}

int LinkListEmpty(LinkList* L) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->head) {
		//LinkList is not init
		return -1;
	}
	
	return L->head == L->tail;
}

int LinkListLength(LinkList* L) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->head) {
		//LinkList is not init
		return -1;
	}
	
	return L->length;
}

int LinkListGetPos(LinkList* L, int index, LinkNode* outPos) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > L->Length) {
		//parameter is not legal
		return -1;
	}
	
	NodeLink* p = L->head;
	int cIndex = 0;
	
	while(index != cIndex) {
		p = p->next;
		cIndex++;
	}
	
	outPis = p;
	return 0;
}

int LinkListGetElem(LinkList* L, int index, ElemType& outElem) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > L->Length) {
		//parameter is not legal
		return -1;
	}
	
	LinkNode node;
	//do not check return value because we checked before
	LinkListGetPos(L, index, &node);
	
	outElem = node.data;
	return 0;
}

int LinkListInsertLocBefore(LinkList* L, int index, ElemType elem) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > L->Length) {
		//parameter is not legal
		return -1;
	}
	
	LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
	if(!node) {
		return -1;
	}
	
	LinkNode* insertPos;
	//do not check return value because we checked before
	LinkListGetPos(L, index, insertPos);
	
	for(LinkNode* p = L->head; p->next != insertPos; p=p->next);
	
	node->next = p->next;
	p->next = node;
	
	L->length++;	
	return 0;
}

int LinkListInsertLocAfter(LinkList* L, int index, ElemType elem) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > L->Length) {
		//parameter is not legal
		return -1;
	}
	
	LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
	if(!node) {
		return -1;
	}
	
	LinkNode* insertPos;
	//do not check return value because we checked before
	LinkListGetPos(L, index, insertPos);
	
	node->next = insertPos->next;
	insertPos->next = node;
	
	if(insertPos == L->tail) {
		L->tail = node;
	}
	
	L.length++;	
	return 0;
}

int LinkListDeleteLoc(LinkList* L, int index) {
	if(!L) {
		//illegal operation
		return -1;
	}
	
	if(!L->head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > L->Length) {
		//parameter is not legal
		return -1;
	}
	
	LinkNode* deletePos;
	//do not check return value because we checked before
	LinkListGetPos(L, index, deletePos);
	
	for(LinkNode* p = L->head; p->next != deletePos; p=p->next);
	
	p->next = deletePos->next;
	
	if(deletePos == L->tail) {
		L->tail = p;
	}
	
	free(deletePos);
	L.length--;
	return 0;
}

int LinkListHeadInsert(LinkList* L, ElemType elem) {
	return LinkListInsertLocAfter(L, 1, elem);
}

int LinkListHeadDelete(LinkList* L) {
	return LinkListDeleteLoc(L, 1, elem);
}

int LinkListTailInsert(LinkList* L, ElemType elem) {
	return LinkListInsertLocAfter(L, LinkListLength(L), elem);
}

int LinkListTailDelete(LinkList* L) {
	return LinkListDeleteLoc(L, LinkListLength(L), elem);
}

void LinkListClear(LinkList* L) {	
	while(LinkListHeadDelete(L) >= 0);
}

void LinkListDestory(LinkList* L) {	
	LinkListClear(L);
	
	free(L->head);
	L->head = NULL;
	L->tail = NULL;
}
