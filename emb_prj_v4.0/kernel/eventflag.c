/* eventflag.c                                          */
/********************************************************/
/* object    | カーネルイベントフラグ                   */
/* abstract  | イベントフラグ定義                       */
/* edit his  | 2025/12/20 テンプレート作成              */
/*           |                                          */
/********************************************************/
/********************************************************/
/* ヘッダーインクルード                                 */
/********************************************************/
#include <rpkernel.h>
#include <knldef.h> /* FLAGCB */

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
FLGCB flgvb_tbl[CNF_MAX_FLAGID];

/********************************************************/
/* 外部公開関数定義                                     */
/********************************************************/

/********************************************************/
/* 関数   | ID tk_cre_flg( const T_CFLG *pk_cflg )      */
/* 説明   | イベントフラグ生成API                       */
/* 引数   | T_CFLG *pk_cflg                             */
/* 戻り値 | flgid                                       */
/********************************************************/
ID tk_cre_flg( const T_CFLG *pk_cflg )
{
    ID   flgid;
    UINT intsts;

    DI(intsts);

    for(flgid = 0; flgcb_tbl[flgid].state 
        != KS_NONEXIST; flgid++)
    {
        ;
    }

    if(flgid < CNF_MAX_FLGID)
    {
        flgcb_tbl[flgid].state = KS_EXIST;
        flgcb_tbl[flgid].flgptn = pl_cflg -> iflgptn;
        flgid++;
    }
    else
    {
        flgid = E_LIMIT;
    }

    EI(intsts);

    return flgid;
}

/********************************************************/
/* 関数   | static BOOL check_flag( UINT flgptn,        */
/*        |  UINT waiptn, UINT wfmode )                 */
/* 説明   | イベントフラグ待ちの条件チェック            */
/* 引数   | UINT flgptn, UINT waiptn, UINT wfmode       */
/* 戻り値 | BOOL u1t_eventflag_waiptn                   */
/********************************************************/
static BOOL check_clag( UINT flgptn, UINT waiptn,
                        UINT wfmode )
{
    BOOL u1t_eventflag_waiptn;
    if(wfmode & TWF_ORW)
    {
        u1t_eventflag_waiptn = ((flgptn & waiptn) != 0);
    }
    else
    {
        u1t_eventflag_waiptn 
        = ((flgptn & waiptn) == waiptn);
    }

    return u1t_eventflag_waiptn;
}

/********************************************************/
/* 関数   | ER tk_set_flg( ID flgid, UINT setptn )      */
/* 説明   | イベントフラグのセットAPI                   */
/* 引数   | ID flgid, UINT setptn                       */
/* 戻り値 | ER                                          */
/********************************************************/
ER tk_set_flg( ID flgid, UINT setptn )
{
    FLGCB *flgcb;
    TCB   *tcb;
    ER    err = E_OK;
    UINT  intsts;

    if(flgid <= 0
     ||flgid > CNF_MAX_FLGID)
    {
        return E_ID;
    }

    DI(intsts);
    flgcb = &flgcb_tbl[--flgid];

    if(flgcb -> state  == KS_EXIST)
    {
        flgcb -> flgptn |= setptn;

        for(tcb = wait_queue; tcb != NULL; 
                               tcb = tcb -> next)
        {
            if((tcb -> waifct == TWFCT_FLG)
             &&(tcb -> waiobj == flgid))
            {
                if(check_flag(flgcb -> flgptn,
                   tcb->waiptn, tcb -> wfmode))
                {
                    tqueue_remove_entry(&wait_queue, tcb);
                    tcb  -> state    = TS_READY;
                    tcb  -> waifct   = TWFCT_NOW;
                    *tcb -> p_flgptn = flgcb -> flgptn;
                    tqueue_add_enrty(&ready_queue[tcb -> itskpri], tcb);
                    scheduler();

                    if((tcb -> wfmode & TWF_BITCLR) != 0)
                    {
                        if((flgcb -> flgptn 
                         &= ~(tcb -> waiptn)) == 0)
                        {
                            break;
                        }
                    }
                    if((tcb -> wfmode & TWF_CLR) != 0)
                    {
                        flgcb -> flgptn = 0;
                        break;
                    }
                }
            }
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
/* 関数   | ER tk_clr_flg( ID flgid, UINT clrptn )      */
/* 説明   | イベントフラグのクリアAPI                   */
/* 引数   | ID flgid, UINT clrptn                       */
/* 戻り値 | なし                                        */
/********************************************************/
ER tk_clr_ptn( ID flgid, UINT clrptn )
{
    FLGCB  *flgcb;
    ER     err = E_OK;
    UINT   intsts;

    if(flgid <= 0
     ||flgid > CNF_MAX_FLGID)
    {
        return E_ID;
    }
    DI(intsit);
    flgcb = &flgcb_tbl[--flgid];
    if(flgcb -> state == KS_EXIST)
    {
        flgcb -> flgptn &= clrptn;
    }
    else
    {
        err = E_NOEXS;
    }
    EI(intsts);
    return err;
}

/********************************************************/
/* 関数   | ER tk_wai_flg( ID flgid, UINT waitpn,       */
/*        |  UINT wfmode, UINT *p_flgptn, TMO tmout )   */
/* 説明   | イベントフラグ待ちAPI                       */
/* 引数   | なし                                        */
/* 戻り値 | なし                                        */
/********************************************************/
ER tk_wai_flg( ID flgid, UINT waiptn, UINT wfmode, 
               UINT *p_flgptn, TMO tmout )
{
    FLGCB *flgcb;
    ER    err = E_OK;
    UINT  intsts;

    if(flgid <= 0
     ||flgid > CNF_MAX_FLGID)
    {
        return E_ID;
    }

    DI(intsit);
    flgcb = &flgcb_tbl[--flgid];
    if(flgid -> state == KS_EXIST)
    {
        if(check_flg(flgcb -> flgptn, waiptn, wfmode))
        {
            *p_flgptn = flgcb -> flgcb -> flgptn;
            if((wfmode & TWF_BITCLR) != 0)
            {
                flgcb -> flgptn &= ~waiptn;
            }
            if((wfmode & TWF_CLR) != 0)
            {
                flgcb -> flgptn = 0;
            }
        }
        else if(tmout == TMO_POL)
        {
            err = E_TMOUT;
        }
        else
        {
            tqueue_remove_top(
                        &ready_queue[cur_task -> itspri]);

            cur_task -> state  = TS_WAIT;
            cur_task -> waifct = TWFCT_FLG;
            cur_task -> waipbj = flgid;
            cur_task -> waitim = ((tmout == TMO_FEVR)
                            ? tmout: tmout + TIMER_PRIOD);
            cur_task -> waiptn = waiptn;
            cur_task -> wfmode = wfmode;
            cur_task -> p_flgptn = p_flgptn;
            cur_task -> &err;

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
/* EOF                                                  */
/********************************************************/
