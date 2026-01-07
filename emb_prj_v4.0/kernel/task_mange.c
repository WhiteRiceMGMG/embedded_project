/* task_mange.c                                         */
/********************************************************/
/* object    | タスク管理                               */
/* abstract  | タスク管理定義                           */
/* edit his  | 2025/12/23 テンプレート作成              */
/*           |                                          */
/********************************************************/
/********************************************************/
/* ヘッダーインクルード                                 */
/********************************************************/
#include <rpkernel.h>
#include <knldef.h> 

/********************************************************/
/* 内部公開マクロ                                       */
/********************************************************/
/* #define  u1g_SAMPLE_VAL                              */

/********************************************************/
/* 外部公開変数                                         */
/********************************************************/
/* u1 u1g_sample_val                                    */

/********************************************************/
/* 内部公開変数                                         */
/********************************************************/
TCB tcb_tbl[CNF_MAX_TSKID];

/********************************************************/
/* 外部公開関数定義                                     */
/********************************************************/

/********************************************************/
/* 関数   | ID tk_cre_tsk( const T_CTSK *pk_ctsk )      */
/* 説明   | タスク生成API                               */
/* 引数   | T_CTSK *pk_ctsk                             */
/* 戻り値 | tskid                                       */
/********************************************************/
ID tk_cre_tsk( const T_CTSK *pk_ctsk )
{
    UINT intsts;
    ID   tskid;
    INT  i;

    if((pk_ctsk -> tskatr & ~TA_RNG3) != (TA_HLNG|TA_USERBUF))
    {
        return E_RSATR;
    }
    if(pk_ctsk -> itskpri <= 0 || pk_ctsk -> itskpri > CNF_MAX_TSKPRI)
    {
        return E_PAR;
    }
    if(pk_ctsk -> stksz == 0)
    {
        return E_PAR;
    }
    DI(intsts);
    for(i = 0; i < CNF_MAX_TSKID; i++)
    {
        if(tcb_tbl[i].state == TS_NONEXIST)
        {
            break;
        }
    }
    if(i < CNF_MAX_TSKID)
    {
        tcb_tbl[i].state   = TS_DORMANT;
        tcb_tbl[i].pre     = NULL;
        tcb_tbl[i].next    = NULL;

        tcb_tbl[i].tskadr  = pk_ctsk -> task;
        tcb_tbl[i].itskpri = pk_ctsk -> itskpri;
        tcb_tbl[i].stksz   = pk_ctsk -> stksz;
        tcb_tbl[i].stkadr  = pk_ctsk -> bufptr;

        tskid = i+1;
    }
    else
    {
        tskid = (ID)E_LIMIT;
    }
    EI(intsts);
    return tskid;
}

/********************************************************/
/* 関数   | ER tk_sta_tsk( ID tskid, INT stacd )        */
/* 説明   | タスク実行API                               */
/* 引数   | ID tskid, INT stacd                         */
/* 戻り値 | err                                         */
/********************************************************/
ER tk_sta_tsk( ID tskid, INT stacd )
{
    TCB  *tcb;
    UINT intsts;
    ER err = E_OK;
    
    if(tskid <= 0 || tskid > CNF_MAX_TSKID)
    {
        return E_ID;
    }
    DI(intsts);

    tcb = &tcb_tbl[tskid - 1];
    if(tcb -> state == TS_DORMANT)
    {
        tcb -> state = TS_READY;
        tcb -> context = make_context(tcb -> stkadr, tcb -> stksz, tcb -> tskadr);
        tqueue_add_entry(&ready_queue[tcb -> itskpri], tcb);
        scheduler();
    }
    else
    {
        err = E_OBJ;
    }

    EI(intsts);
    return err;
}


/********************************************************/
/* 関数   | void tk_ext_tsk( void )                     */
/* 説明   | タスクの動作終了API                         */
/* 引数   | なし                                        */
/* 戻り値 | なし                                        */
/********************************************************/
void tk_ext_tsk( void )
{
    UINT	intsts;

    DI(intsts); 

    cur_task->state	= TS_DORMANT; 
    tqueue_remove_top(&ready_queue[cur_task->itskpri]);

    scheduler(); 
    EI(intsts);
}

/********************************************************/
/* EOF                                                  */
/********************************************************/
