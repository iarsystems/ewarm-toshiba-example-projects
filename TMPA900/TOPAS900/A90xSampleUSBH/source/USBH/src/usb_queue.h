/* ************************************************************************** */
/*
 * --------------------------------------------------------------------------
 *	Application			: USB Host Driver
 *	Micon				: TMP92xD28
 *	Development Tool	: -
 * 	Complie Option		: -
 *  Copyright(C) TOSHIBA CORPORATION 2007 All rights reserved
 * --------------------------------------------------------------------------
 */

/*! \file usb_queue.h
	\brief Declaration of USB Host Driver Memory Management

	\author TOSHIBA CORPORATION
	\ data 2007/05/28

 */
/* ************************************************************************** */

#ifndef _USB_QUEUE_H_SEEN_
#define _USB_QUEUE_H_SEEN_

#include "usb_types.h"

/* ========== メモリ管理用リスト ========== */
/* リスト管理時キャスト用構造体 */
typedef struct usb_tagListMgr {
  struct usb_tagListMgr* next;
} usb_typeListMgr;

/* リスト追加 */
#define USB_ENQUEUE_LIST( head, add )  { ((usb_typeListMgr*)(add))->next = (usb_typeListMgr*)head;  head = add; }
/* リストから取り出し */
#define USB_DEQUEUE_LIST( head, ret )  { ret = head; if( ret != NULL ) head = (void*)((usb_typeListMgr*)ret)->next; }
/* リスト作成 */
#define USB_CREATE_LIST( head, buffer, num ) \
  { int16_t i; for( i = 0; i < num; i++ ){ USB_ENQUEUE_LIST( head, &buffer[i] ); } }
/* リスト要素数チェック */
#define USB_NUM_CHECK_LIST( head, count ) \
  { usb_typeListMgr* temp; for( count = 0, temp = (usb_typeListMgr*)head; temp != NULL; count++, temp = temp->next); }



/*******************************************************************************/
/* 単方向リンクリスト                                                          */
/*******************************************************************************/

/*== 単方向リンクリストエントリ用 =====================================*/
typedef struct usb_slist_entry {
    struct usb_slist_entry* next;                   /* 次のエントリへのポインタ */
} usb_slist_entry_t;

/*== 単方向リンクリストヘッダ用 =======================================*/
typedef struct usb_slist_head {
    struct usb_slist_entry* first;                  /* リストの最初のエントリへのポインタ */
    struct usb_slist_entry** last_next_addr;        /* リストの最後のエントリのnextポインタ */
} usb_slist_head_t;

/*== 単方向リンクリスト用アクセスマクロ ===============================*/

/*!
 * リストヘッダを初期化する
 */
#define SLIST_INIT(head) \
	{ ((usb_slist_head_t*)(head))->first = 0; ((usb_slist_head_t*)(head))->last_next_addr = 0; }

#define SLIST_INSERT_HEAD(head,entry) \
	usb_slist_insert_head((usb_slist_head_t*)(head), (usb_slist_entry_t*)(entry))

#define SLIST_INSERT_AFTER(head,current,entry) \
	usb_slist_insert_after((usb_slist_head_t*)(head), (usb_slist_entry_t*)(current), (usb_slist_entry_t*)(entry))

#define SLIST_INSERT_TAIL(head,entry) \
	usb_slist_insert_tail((usb_slist_head_t*)(head), (usb_slist_entry_t*)(entry))

#define SLIST_REMOVE_HEAD(head) \
	usb_slist_remove_head((usb_slist_head_t*)(head))

#define SLIST_REMOVE(head,current) \
	usb_slist_remove_current((usb_slist_head_t*)(head), (usb_slist_entry_t*)(current))

#define SLIST_REMOVE_TAIL(head) \
	usb_slist_remove_tail((usb_slist_head_t*)(head))

/*!
 * type 型ノードの変数 var に head で示す単方向リストの要素を先頭から順に取得するループ
 */
#define SLIST_FOREACH(var,type,head) \
	for((var) = (type*)((usb_slist_head_t*)(head))->first; \
		(var); (var) = (type*)((usb_slist_entry_t*)(var))->next)

/*!
 * 指定エントリを初期化する
 */
#define SLIST_ENTRY_INIT(entry) \
	{ ((usb_slist_entry_t*)(entry))->next = 0; }

/*!
 * 指定エントリの次のエントリを取得する
 */
#define SLIST_ENTRY_NEXT(entry) ((usb_slist_entry_t*)(entry))->next

/*===========================================================================
説明
  head の示す単方向リストの先頭に entry を挿入する。
===========================================================================*/
extern void usb_slist_insert_head
(
    usb_slist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_slist_entry_t* entry            /* 追加するエントリ */
);

/*===========================================================================
説明
  current の指す単方向エントリの次に entry を挿入
===========================================================================*/
extern void usb_slist_insert_after
(
    usb_slist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_slist_entry_t* current,         /* このエントリの次に挿入 */
    usb_slist_entry_t* entry            /* 追加するエントリ */
);

/*===========================================================================
説明
  head の示す単方向リストの末尾に entry を挿入する。
===========================================================================*/
extern void usb_slist_insert_tail
(
    usb_slist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_slist_entry_t* entry            /* 追加するエントリ */
);



/*===========================================================================
説明
  先頭のエントリを単方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
extern usb_slist_entry_t*   usb_slist_remove_head
(
    usb_slist_head_t* head              /* リストの最初のエントリへのポインタ */
);

/*===========================================================================
説明
  current の指すエントリを単方向リストから取り除いて返します。
===========================================================================*/
extern usb_slist_entry_t*  usb_slist_remove_current
(
    usb_slist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_slist_entry_t* current          /* 取り除くエントリ */
);

/*===========================================================================
説明
  最後のエントリを単方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
extern usb_slist_entry_t*   usb_slist_remove_tail
(
    usb_slist_head_t* head              /* リストの最初のエントリへのポインタ */
);









/*******************************************************************************/
/* 双方向リンクリスト                                                          */
/*******************************************************************************/

/*== 双方向リンクリストエントリ用 =====================================*/
typedef struct usb_dlist_entry {
    struct usb_dlist_entry* next;                   /* 次のエントリへのポインタ */
    struct usb_dlist_entry* prev;                   /* 前のエントリへのポインタ */
} usb_dlist_entry_t;

/*== 双方向リンクリストヘッダ用 ========================================*/
typedef struct usb_dlist_head {
    struct usb_dlist_entry* first;                  /* リストの最初のエントリへのポインタ */
    struct usb_dlist_entry* last;                   /* リストの最後のエントリへのポインタ */
} usb_dlist_head_t;

/*== 双方向リンクリスト用アクセスマクロ ===============================*/

/*!
 * リストヘッダを初期化する
 */
#define DLIST_INIT(head) \
	{ ((usb_dlist_head_t*)(head))->first = 0; ((usb_dlist_head_t*)(head))->last = 0; }

#define DLIST_INSERT_HEAD(head,entry) \
	usb_dlist_insert_head((usb_dlist_head_t*)(head), (usb_dlist_entry_t*)(entry))

#define DLIST_INSERT_AFTER(head,current,entry) \
	usb_dlist_insert_after((usb_dlist_head_t*)(head), (usb_dlist_entry_t*)(current), (usb_dlist_entry_t*)(entry))

#define DLIST_INSERT_TAIL(head,entry) \
	usb_dlist_insert_tail((usb_dlist_head_t*)(head), (usb_dlist_entry_t*)(entry))

#define DLIST_REMOVE_HEAD(head) \
	usb_dlist_remove_head((usb_dlist_head_t*)(head))

#define DLIST_REMOVE(head,current) \
	usb_dlist_remove_current((usb_dlist_head_t*)(head), (usb_dlist_entry_t*)(current))

#define DLIST_REMOVE_TAIL(head) \
	usb_dlist_remove_tail((usb_dlist_head_t*)(head))

/*!
 * type 型ノードの変数 var に head で示す単方向リストの要素を先頭から順に取得するループ
 */
#define DLIST_FOREACH(var,type,head) \
	for((var) = (type*)((usb_dlist_head_t*)(head))->first; \
	(var); (var) = (type*)((usb_dlist_entry_t*)(var))->next)

/*!
 * 指定エントリを初期化する
 */
#define DLIST_ENTRY_INIT(entry) \
	{ ((usb_dlist_entry_t*)(entry))->prev = 0; ((usb_dlist_entry_t*)(entry))->next = 0; }

/*!
 * 指定エントリの次のエントリを取得する
 */
#define DLIST_ENTRY_NEXT(entry) ((usb_dlist_entry_t*)(entry))->next

/*===========================================================================
説明
  head の示す双方向リストの先頭に entry を挿入する。
===========================================================================*/
extern void usb_dlist_insert_head
(
    usb_dlist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_dlist_entry_t* entry            /* 追加するエントリ */
);

/*===========================================================================
説明
  current の指す双方向エントリの次に entry を挿入
===========================================================================*/
extern void usb_dlist_insert_after
(
    usb_dlist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_dlist_entry_t* current,         /* このエントリの次に挿入 */
    usb_dlist_entry_t* entry            /* 追加するエントリ */
);

/*===========================================================================
説明
  head の示す双方向リストの末尾に entry を挿入する。
===========================================================================*/
extern void usb_dlist_insert_tail
(
    usb_dlist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_dlist_entry_t* entry            /* 追加するエントリ */
);

/*===========================================================================
説明
  先頭のエントリを双方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
extern usb_dlist_entry_t*   usb_dlist_remove_head
(
    usb_dlist_head_t* head              /* リストの最初のエントリへのポインタ */
);

/*===========================================================================
説明
  current の指すエントリを双方向リストから取り除いて返します。
===========================================================================*/
extern void  usb_dlist_remove_current
(
    usb_dlist_head_t* head,             /* リストの最初のエントリへのポインタ */
    usb_dlist_entry_t* current          /* 取り除くエントリ */
);

/*===========================================================================
説明
  最後のエントリを双方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
extern usb_dlist_entry_t*   usb_dlist_remove_tail
(
    usb_dlist_head_t* head              /* リストの最初のエントリへのポインタ */
);

#endif /* _USB_QUEUE_H_SEEN_ */
/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
