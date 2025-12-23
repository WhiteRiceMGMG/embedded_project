
/* semaphore.c                                          */
/********************************************************/
/* object    | セマフォ                                 */
/* abstract  | セマフォ定義                             */
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
SEMCB semcb_tbl[CNF_MAX_SEMID];

/********************************************************/
/* 内部公開変数                                         */
/********************************************************/
FLGCB flgvb_tbl[CNF_MAX_FLAGID];

/********************************************************/
/* 外部公開関数定義                                     */
/********************************************************/

/********************************************************/
/* 関数   | ID tk_cre_sem( const T_CSEM *pk_csem )      */
/* 説明   | セマフォ生成API                             */
/* 引数   | T_CSEM *pk_csem                             */
/* 戻り値 | semid                                       */
/********************************************************/
ID tk_cre_sem( const T_CSEM *pk_csem )
{
    ID   semid;
    UINT intsts; 
    
    DI(intsts);
    for(semid = 0; semcb_tbl[semid].state != KS_NONEXIST; 
        semid++)

    if(semid < CNF_MAX_SEMID)
    {
        semcb_tbl[semid].state  = KS_EXIST;
        semcb_tbl[semid].semcnt = pk_csem -> isemcnt;
        semcb_tbl[semid].maxsem = pk_csem -> maxsem;
        semid++;
    }
    else
    {
        semid = E_LIMIT;
    }
    EI(intsts);
    return semid;
}

/********************************************************/
/* 関数   |ER tk_wai_sem( ID semid, INT cnt, TMO tmout )*/
/* 説明   | セマフォの資源獲得API                       */
/* 引数   | ID semid, INT cnt, TMO tmout                */
/* 戻り値 | err                                         */
/********************************************************/
ER tk_wai_sem( ID semid, INT cnt, TMO tmout )
{
    SEMCB *semcb;
    ER    err = E_OK;
    UINT  intsts;

    if(semid <= 0 || semid > CNF_MAX_SEMID)
    {
        return E_ID;
    }
    DI(intsts);
    semcb = &semcb_tbl[--semid];
    if(semcb -> state == KS_EXIST)
    {
        if(semcb -> semcnt >= cnt)
        {
            semcb -> semcnt -= cnt;
        }
        else if(tmout == TMO_POL)
        {
            err = E_MOUT;
        }
        else
        {
            tqueue_remove_top
                       (&ready_queue[cur_task -> itspri]);
            cur_task -> state = TS_WAIT;
            cur_task -> waifct = TWFCT_SEM;
            cur_task -> waiobj = semid;
            cur_task -> waitim = ((tmout == TMO_FEVR)
                           ? tmout: tmout + TIMER_PERIOD);
            cur_task -> waisem = cnt;
            cur_task -> waierr = &err;

            tqueue_add_entry(&wait_queue, cur_task);
            scheduler();
        }
    }
    else
    {
        err = E_NOEXS;
    }

    EI(intsts);
    return err;
}

/********************************************************/
/* 関数   | ER tk_sig_sem( ID semid, INT cnt )          */
/* 説明   | セマフォの資源返却API                       */
/* 引数   | ID semid, INT cnt                           */
/* 戻り値 | ER                                          */
/********************************************************/
ER tk_sig_sem( ID semid, INT cnt )
{
    SEMCB *semcb;
    TCB   *tcb;
    ER    err = E_OK;
    UINT  intsts;

    if(semid <= 0 || semid > CNF_MAX_SEMID)
    {
        return E_ID;
    }
    DI(intsts);
    semcb = &semcb_tbl[--semid];
    if(semcb -> state == KS_EXIST)
    {
        semcb -> semcnt += cnt;
        if(semcb -> semcnt <= semcb -> maxsem)
        {
            for(tcb = wait_queue; tcb != NULL; tcb = tcb -> next)
            {
                if((cb->waifct == TWFCT_SEM)
                 &&(tcb -> waiobj == semid))
                {
                    if(semcb -> semcnt >= tcb -> waisem)
                    {
                        semcb -> semcnt -= tcb -> waisem;
                        tqueue_remove_enrty(&wait_queue
                                            , tcb);
                        tcb -> state  = TS_READY;
                        tcb -> waifct = TWFCT_NOW;
                        tcb -> waierr = &err;
                        tqueue_remove_enrty(&ready_queue[tcb -> itskpri], tcb);
                        scheduler();
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            semcb -> semcnt -= cnt;
            err = E_QOVR;
        }
    }
    else
    {
        err = E_NOEXS;
    }
    EI(intsts);
    return err;
}

/********************************************************/
/* EOF                                                  */
/********************************************************/
