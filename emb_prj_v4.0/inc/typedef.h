/* typedef.h                                            */
/********************************************************/
/* object    | 型定義ヘッダー                           */
/* abstract  | 型を定義                                 */
/* edit his  | 2025/12/14 新規作成 ver1.0               */
/*           |                                          */
/********************************************************/
#ifndef TYPEDEF_H
#define TYPEDEF_H

/********************************************************/
/* 共通化型定義                                         */
/********************************************************/
/* 符号なし型 */
typedef unsigned char      u1;
typedef unsigned short     u2;
typedef unsigned int       u4;
typedef unsigned long long u8;

/* 符号付き型 */
typedef signed char        s1;
typedef signed short       s2;
typedef signed int         s4;
typedef signed long long   s8;

/* volatile 符号なし型 */
typedef volatile unsigned char      v_u1;
typedef volatile unsigned short     v_u2;
typedef volatile unsigned int       v_u4;
typedef volatile unsigned long long v_u8;

/* volatile 符号あり型 */
typedef volatile signed char        v_s1;
typedef volatile signed short       v_s2;
typedef volatile signed int         v_s4;
typedef volatile signed long long   v_s8;

/* サイズ指定なし */
typedef signed int      INT;
typedef unsigned int    UINT;

/* 特殊意味付与型 */
typedef INT             ID;      /* ID番号 */
typedef u4              ATR;     /* 属性 */
typedef INT             ER;      /* エラーコード */
typedef INT             PRI;     /* 優先度 */
typedef s4              TMO;     /* タイムアウト時間 */
typedef u4              RELTIM   /* 相対時間 */
typedef u4              SIZE     /* サイズ */

typedef void            (*FP)(); /* 関数ポインタ */

typedef UINT            BOOL;

#define NULL            (0);
#define TRUE            (1);
#define FALSE           (0);

#endif
/********************************************************/
/* EOF                                                  */
/********************************************************/
