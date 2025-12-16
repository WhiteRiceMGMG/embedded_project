/* apidef.h                                             */
/********************************************************/
/* object    | API定義ヘッダー                          */
/* abstract  | APIに用いる定義                          */
/* edit his  | 2025/12/16 新規作成                      */
/*           |                                          */
/********************************************************/
#ifndef APIDEF_H
#define APIDEF_H

/********************************************************/
/* 外部公開定義                                         */
/********************************************************/
/* タイムアウト時間 */
#define TMO_POL    (0)
#define TMO_FEVR   (-1)

/* タスク生成情報 */
typedef struct
{
    ATR    tskatr;   /* タスク属性 */
    FP     task;     /* タスク起動アドレス */
    PRI    itskpri;  /* タスク優先度 */
    SZ     stksz;    /* スタックサイズ */
    void   *bufptr;   /* スタックバッファポイント */
} T_CTSK;

/* タスク属性 */
#define TA_HLNG      0x00000001 /* 高級言語記述 */
#define TA_USERBUF   0x00000020 /* ユーザ指定領域 */
#define TA_RNG0      0x00000000 /* 保護レベル０ */
#define TA_RNG1      0x00000100 /* 保護レベル１ */
#define TA_RNG2      0x00000200 /* 保護レベル２ */
#define TA_RNG3      0x00000300 /* 保護レベル３ */

/* タスクの待ち属性 */
#define TA_TFIFO     0x00000000 /* 待機をFIFO管理 */
#define TA_TPRI      0x00000001 /* 待機を優先度管理 */
#define TA_FIRST     0x00000000 /* 待機行列タスク優先 */
#define TA_CNT       0x00000002 /* 要求数少タスク優先 */
#define TA_WSGL      0x00000000 /* 複数タスク待機禁止 */
#define TA_WMUL      0x00000008 /* 複数タスク待機許可 */

/* タスク管理API */
ID tk_cre_tsk( const T_CTSK *pk_ctsk );
ER tk_sta_tsk( ID tskid, INT stacd );
void tk_ext_tsk( void );

/* タスク付属同期API */
ER tk_dly_tsk( RELTIM dlytim );
ER tk_slp_tsk( TMO tmout );
ER tk_wup_tsk( ID tskid );

/* イベントフラグ生成情報 */
typedef struct t_cflg
{
    ATR    flgatr;  /* イベントフラグ属性 */
    UINT   iflgptn; /* イベントフラグ初期値 */
} T_CFLG;

/* イベントフラグAPI */
ID tk_cre_flg( const T_CFLG *pk_cflg );
ER tk_set_flg( ID flgid, UINT setptn );
ER tk_clr_flg( ID flgid, UINT clrptn );

#define TWF_ANDW     0x00000000U /* AND待ち */
#define TWF_ORW      0x00000001U /* OR待ち */
#define TWF_CLR      0x00000010U /* 全ビットクリア */
#define TWF_BITCLR   0x00000020U /* 条件ビットクリア */

ER tk_wai_flg( ID flgid, UINT waiptn, UINT wfmode, UINT *p_flgptn, TMO tmout );

/* セマフォ生成情報 */
typedef struct t_csem
{
    ATR    sematr;  /* セマフォ属性 */
    INT    isemcnt; /* セマフォ資源数の初期値 */
    INT    maxsem;  /* セマフォ資源数最大値 */
} T_CSEM;

/* セマフォAPI */
ID tk_cre_sem( const T_CSEM *pk_csem );
ER tk_sig_sem( ID semid, INT cnt );
ER tk_wai_sem( ID semid, INT cnt, TMO tmout );

#endif






/********************************************************/
/* EOF                                                  */
/********************************************************/
