/**
 * @file
 * USB Host Driver source file.
 *
 * Copyright(C) TOSHIBA CORPORATION 2006 All rights reserved
 * Copyright(C) 2006 TOSHIBA INFORMATION SYSTEMS (JAPAN) CORPORATION
 *
*/

/* $Id: usb_queue.c 41 2014-01-27 14:05:18Z danielru $ */

#include "usb_queue.h"                                  /* リスト管理モジュール */

/*******************************************************************************/
/* 単方向リンクリスト                                                          */
/*******************************************************************************/

/*===========================================================================
説明
  単方向リストの先頭に entry を挿入する。
===========================================================================*/
void
usb_slist_insert_head(usb_slist_head_t* head, usb_slist_entry_t* entry)
{
    if(head == NULL || entry == NULL) {             /* 引数チェック */
        return;
    }

    if(head->first == NULL) {                       /* リストの先頭がNULLの場合 */
        head->last_next_addr = &(entry->next);      /* リストの最後のエントリのnextポインタアドレスを登録 */
	}
	entry->next = head->first;                  /* 現在のfirstを追加エントリのnextにする */
    head->first = entry;                            /* リストの先頭に追加エントリを登録 */
}

/*===========================================================================
説明
  単方向リスト中のcurrentエントリの次に entry を挿入
===========================================================================*/
void
usb_slist_insert_after(usb_slist_head_t* head, usb_slist_entry_t* current, usb_slist_entry_t* entry)
{
    if(head == NULL || head->first == NULL || current == NULL || entry == NULL) {   /* 引数チェック */
        return;
    }

    if(current->next == *(head->last_next_addr)) {  /* 指定エントリがリストの最後の場合 */
        head->last_next_addr = &(entry->next);      /* リストの最後のエントリのnextポインタアドレスを変更 */
    }
    entry->next = current->next;                    /* 追加エントリの次アドレスを変更 */
    current->next = entry;                          /* 指定エントリの次アドレスを変更 */
}

/*===========================================================================
説明
  単方向リストの末尾に entry を挿入する。
===========================================================================*/
void
usb_slist_insert_tail(usb_slist_head_t* head, usb_slist_entry_t* entry)
{
    if(head == NULL || entry == NULL) {             /* 引数チェック */
        return;
    }

    if(NULL == head->first) {                       /* リストの先頭がNULLの場合 */
        head->first = entry;                        /* リストの先頭を登録 */
    } else {
        *(head->last_next_addr) = entry;            /* リストの最後のエントリのnextに追加エントリポインタ登録 */
    }
    entry->next = NULL;
    head->last_next_addr = &(entry->next);          /* リストの最後のエントリのnextポインタアドレスを登録 */
}

/*===========================================================================
説明
  先頭のエントリを単方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
usb_slist_entry_t*
usb_slist_remove_head(usb_slist_head_t* head)
{
    usb_slist_entry_t* first_tmp;                       /* 戻り値用テンポラリ */

    if(head == NULL || head->first == NULL) {       /* 引数チェック */
        return((usb_slist_entry_t*)NULL);
    }

    first_tmp = head->first;                        /* 先頭エントリアドレス退避 */

    head->first = head->first->next;                /* リストの先頭を変更 */
    if(head->first == NULL) {                       /* リストにエントリが無くなった場合 ? */
        head->last_next_addr = NULL;                /* リストの最後のエントリも無しにする */
    }

    first_tmp->next = NULL;                         /* 取り除いたリストの初期化 */

    return(first_tmp);
}

/*===========================================================================
説明
  current の指すエントリを単方向リストから取り除いて返します。
===========================================================================*/
usb_slist_entry_t*
usb_slist_remove_current(usb_slist_head_t* head, usb_slist_entry_t* current)
{
    usb_slist_entry_t* prev_entry;                      /* currentの前のエントリ検索用 */

    if(head == NULL || head->first == NULL || current == NULL) {    /* 引数チェック */
        return( NULL );
    }

    prev_entry = head->first;                       /* 検索用にリストの先頭を用意する */

    if(prev_entry == current) {                     /* 最初のエントリを取り除く場合 */
        head->first = head->first->next;
    } else {
        while(prev_entry->next != current) {        /* 次アドレスがcurrentになるまで繰り返す */
            if(prev_entry->next == NULL) {          /* 次アドレスがNULLだったら終了 */
                return( NULL );                     /* @エラー */
            }
            prev_entry = prev_entry->next;          /* 検索用を次にする */
        }
        prev_entry->next = current->next;           /* currentを削除しリストつなぎ直し */
    }

    if(head->first == NULL) {                       /* リストにエントリが無くなった場合 ? */
        head->last_next_addr = NULL;                /* リストの最後のエントリも無しにする */
    } else if(current->next == *(head->last_next_addr)) {   /* 指定エントリがリストの最後の場合 */
        head->last_next_addr = &(prev_entry->next); /* リストの最後のエントリのnextポインタアドレスを変更 */
    }

    current->next = NULL;                           /* 取り除いたリストの初期化 */

  return( current );
}

/*===========================================================================
説明
  最後のエントリを単方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
usb_slist_entry_t*
usb_slist_remove_tail(usb_slist_head_t* head)
{
    usb_slist_entry_t* prev_entry;                      /* 最終エントリ検索用 */
    usb_slist_entry_t* last_entry_tmp;                  /* 戻り値用テンポラリ */

    if(head == NULL || head->first == NULL) {       /* 引数チェック */
        return( NULL );
    }

    prev_entry = head->first;                       /* 検索用にリストの先頭を用意する */

    if(head->first->next == NULL) {                 /* リストに1つのエントリしか無い場合？ */
        last_entry_tmp = head->first;               /* 戻り値用に最後のエントリを保持 */
        head->first = NULL;                         /* リストの最初のエントリを無しにする */
        head->last_next_addr = NULL;                /* リストの最後のエントリも無しにする */
    } else {
        while(prev_entry->next->next != NULL) {     /* 次アドレスの次アドレスが最後になるまで繰り返す */
            prev_entry = prev_entry->next;          /* 検索用を次にする */
        }
        last_entry_tmp = prev_entry->next;          /* 戻り値用に最後のエントリを保持 */
        prev_entry->next = NULL;                    /* リストの最後のエントリをNULLにする */
        head->last_next_addr = &(prev_entry->next); /* リストの最後のエントリのnextポインタアドレスを変更 */
    }

    last_entry_tmp->next = NULL;                    /* 取り除いたリストの初期化 */

    return(last_entry_tmp);
}









/*******************************************************************************/
/* 双方向リンクリスト                                                          */
/*******************************************************************************/

/*===========================================================================
説明
  head の示す双方向リストの先頭に entry を挿入する。
===========================================================================*/
void
usb_dlist_insert_head(usb_dlist_head_t* head, usb_dlist_entry_t* entry)
{
    if(head == NULL || entry == NULL) {             /* 引数チェック */
        return;
    }

    entry->next = head->first;                      /* nextは現在のリストの先頭にする */
    entry->prev = NULL;                             /* リストの先頭なのでprevはNULL */

    if(head->first == NULL) {                       /* リストの先頭が無い場合 ? */
        head->last = entry;                         /* リストの最後は追加エントリ */
    } else {
        head->first->prev = entry;                  /* リストの先頭のprevを追加エントリに */
    }

    head->first = entry;                            /* リストの先頭は追加エントリ */
}

/*===========================================================================
説明
  current の指す双方向エントリの次に entry を挿入
===========================================================================*/
void
usb_dlist_insert_after(usb_dlist_head_t* head, usb_dlist_entry_t* current, usb_dlist_entry_t* entry)
{
    if(head == NULL || head->first == NULL || current == NULL || entry == NULL) {   /* 引数チェック */
        return;
    }

    entry->next = current->next;                    /* エントリの更新 */
    entry->prev = current;                          /*  */

    if(current == head->last) {                     /* カレントがリストの最後? */
        head->last = entry;                         /* リストの最後を追加エントリにする */
    } else {                                        /*  */
        current->next->prev = entry;                /*  */
    }

    current->next = entry;                          /* カレントの次は追加エントリ */
}

/*===========================================================================
説明
  head の示す双方向リストの末尾に entry を挿入する。
===========================================================================*/
void
usb_dlist_insert_tail(usb_dlist_head_t* head, usb_dlist_entry_t* entry)
{
    if(head == NULL || entry == NULL) {             /* 引数チェック */
        return;
    }

    if(head->last == NULL) {                        /* エントリが無い場合 */
        head->first = entry;                        /* リスト先頭に追加 */
    } else {
        head->last->next = entry;                   /* 最後に追加 */
    }

    entry->prev = head->last;                       /* エントリのprevは現在のリストの最後 */
    entry->next = NULL;                             /* 最後のエントリなのでNULL */

    head->last = entry;                             /* リストの最後は追加するエントリ */

}

/*===========================================================================
説明
  先頭のエントリを双方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
usb_dlist_entry_t*
usb_dlist_remove_head(usb_dlist_head_t* head)
{
    usb_dlist_entry_t* first_tmp;                       /* 戻り値用テンポラリ */

    if(head == NULL || head->first == NULL) {       /* 引数チェック */
        return((usb_dlist_entry_t*)NULL);
    }

    first_tmp = head->first;                        /* 先頭エントリ退避 */

    head->first = head->first->next;                /* リストの先頭を変更 */
    if(head->first == NULL) {                       /* リストにエントリが無くなった場合 ? */
        head->last = NULL;                          /* リストの最後のエントリも無しにする */
    } else {
        head->first->prev = NULL;                   /* リストの先頭なのでNULL */
    }

    first_tmp->prev = NULL;                         /* 取り除いたリストの初期化 */
    first_tmp->next = NULL;                         /* 取り除いたリストの初期化 */

    return (first_tmp);
}

/*===========================================================================
説明
  current の指すエントリを双方向リストから取り除いて返します。
===========================================================================*/
void
usb_dlist_remove_current(usb_dlist_head_t* head, usb_dlist_entry_t* current)
{
    if(head == NULL || head->first == NULL || current == NULL) {    /* 引数チェック */
        return;
    }

    if(current->prev == NULL) {                     /* 取り除くエントリがリストの先頭? */
        head->first = current->next;                /* リストの先頭を取り除くエントリのnextにする */
    } else {
        current->prev->next = current->next;
    }

    if(current->next == NULL) {                     /* 取り除くエントリがリストの最後 */
        head->last = current->prev;                 /* リストの先頭を取り除くエントリのprevにする */
    } else {
        current->next->prev = current->prev;
    }

    current->prev = NULL;                           /* 取り除いたリストの初期化 */
    current->next = NULL;                           /* 取り除いたリストの初期化 */

}

/*===========================================================================
説明
  最後のエントリを双方向リストから取り除いて返します。

戻り値
  リストから取り除いたエントリ
===========================================================================*/
usb_dlist_entry_t*
usb_dlist_remove_tail(usb_dlist_head_t* head)
{
    usb_dlist_entry_t* last_tmp;                        /* 戻り値用テンポラリ */

    if(head == NULL || head->first == NULL) {       /* 引数チェック */
        return((usb_dlist_entry_t*)NULL);
    }

    last_tmp = head->last;

    if(head->last->prev == NULL) {                  /* 最後のエントリの場合 ? */
        head->first = NULL;                         /* リストの先頭をNULLにする */
    } else {
        head->last->prev->next = NULL;              /* 最後のエントリの1つ前のエントリのnextをNULLにする */
    }

    head->last = head->last->prev;                  /* リストの最後を */

    last_tmp->prev = NULL;                          /* 取り除いたリストの初期化 */
    last_tmp->next = NULL;                          /* 取り除いたリストの初期化 */

    return (last_tmp);
}

/*
 * Local variables:
 * coding: sjis-dos
 * mode: C
 * c-file-style: "CC-MODE"
 * tab-width: 4
 * indent-tabs-mode: t
 * End:
 */
