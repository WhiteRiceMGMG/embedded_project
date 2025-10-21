/*********************************************************************************/
/* Copyright OGAWA CONST                                                         */
/*********************************************************************************/
/* file : tsk=que.c                                                              */
/* abst : task que                                                               */
/* hist : 2025 / 10 /01                                                          */
/*********************************************************************************/
#include <trykernel.h>
#include <knldef.h>

/*********************************************************************************/
/* 関数   | tqueue_add_entry(TCB **queue, TCB *tcb)                              */
/* 説明   | エントリ追加関数                                                     */
/* 引数   | TCB **queue, TCB *tcb                                                */
/* 戻り値 | なし                                                                 */
/* 作成   | 2025 / 10 /02                                                        */
/*********************************************************************************/
void tqueue_add_entry(TCB **queue, TCB *tcb)
{
    TCB *queue_end;

    if(*queue == NULL) {    // キューは空なので先頭に追加
        *queue      = tcb;
        tcb->pre    = tcb;
	} else {                // キューの終端に追加
        queue_end       = (*queue)->pre;
        queue_end->next = tcb;
        tcb->pre        = queue_end;
        (*queue)->pre   = tcb;
    }
    tcb->next = NULL;
}

/* 先頭エントリ削除関数 */

void tqueue_remove_top(TCB **queue)
{
    TCB	*top;

    if(*queue == NULL) return;  // キューは空

    top = *queue;
    *queue = top->next;
    if(*queue != NULL) {
        (*queue)->pre = top->pre;
    }
}

/*********************************************************************************/
/* 関数   | tqueue_remove_entry(TCB **queue, TCB *tcb)                           */
/* 説明   | エントリ関数                                                         */
/* 引数   | TCB **queue, TCB *tcb                                                */
/* 戻り値 | なし                                                                 */
/* 作成   | 2025 / 10 /02                                                        */
/*********************************************************************************/
void tqueue_remove_entry(TCB **queue, TCB *tcb)
{
    if(*queue == tcb) {     // 指定したエントリはキューの先頭
        tqueue_remove_top(queue);
    } else {                // キューの途中から指定エントリを削除
        (tcb->pre)->next = tcb->next;
        if(tcb->next != NULL) {
            (tcb->next)->pre = tcb->pre;
        } else {
            (*queue)->pre = tcb->pre;
        }
    }
}

/*********************************************************************************/
/* EOF                                                                           */
/*********************************************************************************/
