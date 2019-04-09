#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

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

int InitLinkList(LinkList* L);
int LinkListEmpty(LinkList* L);
int LinkListLength(LinkList* L);
int LinkListGetPos(LinkList* L, int index, LinkNode* outPos);
int LinkListGetElem(LinkList* L, int index, ElemType& outElem);
int LinkListInsertLocBefore(LinkList* L, int index, ElemType elem);
int LinkListInsertLocAfter(LinkList* L, int index, ElemType elem);
int LinkListDeleteLoc(LinkList* L, int index);
int LinkListHeadInsert(LinkList* L, ElemType elem);
int LinkListHeadDelete(LinkList* L);
int LinkListTailInsert(LinkList* L, ElemType elem);
int LinkListTailDelete(LinkList* L);
void LinkListClear(LinkList* L);
void LinkListDestory(LinkList* L);

#endif