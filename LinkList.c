typedef int ElemType;

typedef struct {
	ElemType data;
	LinkNode* next;
}LinkNode;

typedef struct {
	LinkNode* head;
	LinkNode* tail;
	int length;
}LinkList;

int InitLinkList(LinkList& L) {
	LinkNode* headNode = (LinkNode*)malloc(sizeof(LinkNode));
	if(!headNode) {
		return -1;
	}
	
	headNode->next = NULL;
	
	L.head = headNode;
	L.tail = headNode;
	L.length = 0;
	return 0;
}

int LinkListEmpty(LinkList& L) {
	return L.head == L.tail;
}

int LinkListLength(LinkList& L) {
	return L.length;
}

void LinkListGetPos(LinkList& L, int index, LinkNode* outPos) {	
	NodeLink* p = L.head;
	int cIndex = 0;
	
	while(index != cIndex) {
		p = p->next;
		cIndex++;
	}
	
	outPis = p;
}

int LinkListGetElem(LinkList& L, int index, ElemType& outElem) {
	if(!L.head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > LinkListLength(L)) {
		return -1;
	}
	
	LinkNode node;
	LinkListGetPos(L, index, &node);
	
	outElem = node.data;
	return 0;
}

int LinkListInsertLocBefore(LinkList& L, int index, ElemType elem) {
	if(!L.head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > LinkListLength(L)) {
		return -1;
	}
	
	LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
	if(!node) {
		return -1;
	}
	
	LinkNode* insertPos;
	LinkListGetPos(L, index, insertPos);
	
	for(LinkNode* p = L.head; p->next != insertPos; p=p->next);
	
	node->next = p->next;
	p->next = node;
	
	L.length++;	
	return 0;
}

int LinkListInsertLocAfter(LinkList& L, int index, ElemType elem) {
	if(!L.head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 0 || index > LinkListLength(L)) {
		return -1;
	}
	
	LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
	if(!node) {
		return -1;
	}
	
	LinkNode* insertPos;
	LinkListGetPos(L, index, insertPos);
	
	node->next = insertPos->next;
	insertPos->next = node;
	
	if(insertPos == L.tail) {
		L.tail = node;
	}
	
	L.length++;	
	return 0;
}

int LinkListDeleteLoc(LinkList& L, int index) {
	if(!L.head) {
		//LinkList is not init
		return -1;
	}
	
	if(index < 1 || index > LinkListLength(L)) {
		return -1;
	}
	
	LinkNode* deletePos;
	LinkListGetPos(L, index, deletePos);
	
	for(LinkNode* p = L.head; p->next != deletePos; p=p->next);
	
	p->next = deletePos->next;
	
	if(deletePos == L.tail) {
		L.tail = p;
	}
	
	free(deletePos);
	L.length--;
	return 0;
}

int LinkListHeadInsert(LinkList& L, ElemType elem) {
	return LinkListInsertLocAfter(L, 0, elem);
}

int LinkListHeadDelete(LinkList& L) {
	return LinkListDeleteLoc(L, 1, elem);
}

int LinkListTailInsert(LinkList& L, ElemType elem) {
	return LinkListInsertLocAfter(L, LinkListLength(L), elem);
}

int LinkListTailDelete(LinkList& L) {
	return LinkListDeleteLoc(L, LinkListLength(L), elem);
}

void LinkListClear(LinkList& L) {
	if(!L.head) {
		//LinkList is not init
		return;
	}
	
	while(LinkListHeadDelete(L) >= 0);
}

void LinkListDestory(LinkList& L) {
	if(!L.head) {
		//LinkList is not init
		return;
	}
	
	LinkListClear(L);
	
	free(L.head);
	L.head = NULL;
	L.tail = NULL;
}
