/*********************************************************************************/
/* Copyright OGAWA CONST                                                         */
/*********************************************************************************/
/* file : vector_tbl.c                                                           */
/* abst : 例外ベクタ                                                             */
/* hist : 2025 / 10 /03                                                          */
/*********************************************************************************/
#include <typedef.h>
#include <sysdef.h>
#include <syslib.h>
#include <knldef.h>

/* スタック上の実行コンテキスト情報 */
typedef struct {
    UW	r_[8];      /* R4-R11 レジスタの値（例外処理により退避） */
    UW	r[4];       /* R0-R3 レジスタの値*/
    UW	ip;	        /* R12 レジスタの値*/
    UW	lr;         /* lr レジスタの値 */
    UW	pc;         /* pc レジスタの値 */
    UW	xpsr;       /* xpsr レジスタの値 */
} StackFrame;

/* 初期実行コンテキストの作成 */
/*********************************************************************************/
/* 関数   | *make_context( UW *sp, UINT ssize, void (*fp)())                     */
/* 説明   | 初期実行コンテキストの作成                                           */
/* 引数   | UW *sp, UINT ssize, void (*fp)()                                     */
/* 戻り値 | なし                                                                 */
/* 作成   | 2025 / 10 /03                                                        */
/*********************************************************************************/
void *make_context( UW *sp, UINT ssize, void (*fp)())
{
    StackFrame	*sfp;

    /* スタック上の実行コンテクスト情報へのポインタをsfpに設定 */
    sfp = (StackFrame*)((UW)sp + ssize);
    sfp--;

    /* 実行コンテキスト情報の初期化 */
    sfp->xpsr       = 0x01000000;
    sfp->pc         = (UW)fp & ~0x00000001UL;

    return (void*)sfp;
}

typedef INT                 ER;     /* エラーコード */
typedef INT                 PRI;    /* 優先順位 */
typedef W                   TMO;    /* タイムアウト時間 */
typedef UW                  RELTIM; /* 相対時間 */
typedef W                   SZ;     /* サイズ */

typedef void                (*FP)();    /* 関数ポインタ */

#define NULL                (0)

typedef UINT                BOOL;
#define TRUE                (1)     /* True */
#define FALSE               (0)     /* False */

#endif  /* TYPEDEF_H */

/*********************************************************************************/
/* EOF                                                                           */
/*********************************************************************************/