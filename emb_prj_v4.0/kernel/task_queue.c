/* task_queue.c                                         */
/********************************************************/
/* object    | タスクの待ち行列操作関数                 */
/* abstract  | タスクの待ち行列操作関数定義             */
/* edit his  | 2025/12/23 テンプレート作成              */
/*           |                                          */
/********************************************************/
/********************************************************/
/* ヘッダーインクルード                                 */
/********************************************************/
#include <rpkernel.h>
#include <knldef.h> 

/********************************************************/
/* 外部公開関数定義                                     */
/********************************************************/

/********************************************************/
/* 関数   | void tqueue_add_enrty( TCB **queue,         *//*        | TCB *tcb )                                  */
/* 説明   | エントリ追加関数                            */
/* 引数   | TCB **queue, TCB *tcb                       */
/* 戻り値 | semid                                       */
/********************************************************/
void tqueue_add_enrty( TCB **queue, TCB *tcb )
{
    TCB *queue_end;
    if(*queue == NULL)
    {
        *queue     = tcb;
        tcb -> pre = tcb;
    }
    else
    {
        queue_end         = (*queue) -> pre;
        queue_end -> next = tcb;
        tcb -> pre        = queue_end;
        (*queue) -> pre   = tcb;
    }
    tcb -> next = NULL;
}

/********************************************************/
/* 関数   | void tqueue_remove_top( TCB **queue )       */
/* 説明   | 先頭エントリ削除関数                        */
/* 引数   | TCB **queue                                 */
/* 戻り値 | err                                         */
/********************************************************/
void tqueue_remove_top( TCB **queue )
{
    TCB *top;
    if(*queue == NULL)
    {
        return;
    }
    top = *queue;
    *queue = top -> next;
    if(*queue != NULL)
    {
        (*queue) -> pre = top -> pre;
    }
}

/********************************************************/
/* 関数   | void tqueue_remove_entry (TCB **queue,      */
/*        | TCB *tcb )                                  */
/* 説明   | 指定エントリ削除関数                        */
/* 引数   | TCB **queue, TCB *tcb                       */
/* 戻り値 | なし                                        */
/********************************************************/
void tqueue_remove_enrty( TCB **queue, TCB *tcb )
{
    if(*queue == tcb)
    {
        tqueue_remove_top(queue);

    }
    else
    {
        (tcb -> pre) -> next = tcb -> next;
        if(tcb -> next != NULL)
        {
            (tcb -> next) -> pre = tcb -> pre;
        }
        else
        {
            (*queue) -> pre = tcb -> pre;
        }
    }
}

/********************************************************/
/* EOF                                                  */
/********************************************************/
