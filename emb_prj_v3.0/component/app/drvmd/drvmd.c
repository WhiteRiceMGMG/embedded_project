/*********************************************************************************/
/* Copyright OGAWA CONST                                                         */
/*********************************************************************************/
/* file : drvmd  .c                                                              */
/* abst : ドライブモード調停                                                     */
/* hist : 2025 / 10 /04                                                          */
/*********************************************************************************/

/*********************************************************************************/
/* インクルードファイル                                                          */
/*********************************************************************************/
#include "drvmd.h"
/* #include "../sampleif.h" */       /*自ヘッダでインクルードのためコメントアウト*/
/* #include "../devmdif.h"  */       /*自ヘッダでインクルードのためコメントアウト*/        
/* #include "../devmdif.h"  */       /*自ヘッダでインクルードのためコメントアウト*/   

/*********************************************************************************/
/* マクロ定義                                                                    */
/*********************************************************************************/
#define DRVMDSWUP_IS_PUSHED   (u1)0     /* ドライブモードスイッチ UP 押下状態   */
#define DRVMDSWDW_IS_PUSHED   (u1)1     /* ドライブモードスイッチ DOWN 押下状態 */
#define NUMBER_OF_DRVMDSW     (u1)2     /* スイッチの数                         */ 
#define DRVMDSW_IS_NOT_PUSHED (u1)2     /* ドライブモードスイッチ 非押下状態    */
#define DRVMDSW_IS_ERROR      (u1)3     /* ドライブモードスイッチ エラー状態    */

/*-------------------- drvmdif.h に記載のためコメントアウト ----------------------
enum 
{
    DRIVE_MODE_ECO    = 0,         
    DRIVE_MODE_NORMAL = 1,         
    DRIVE_MODE_SPORT  = 2,         
    DRIVE_MODE_OVER_DRIVE   = 3          
}
---------------------------------------------------------------------------------*/

/*********************************************************************************/
/* 変数定義                                                                      */
/*********************************************************************************/
/* 現在のモードと押されたボタン(UP or DOWN)により次のモードに移行する． */
static const u1 NEXT_DRVMD_TBL[DRIVE_MODE_NUM][NUMBER_OF_DRVMDSW] =
{ /* DOWN が押されたとき  UPが押されたとき                              */
    {DRIVE_MODE_ECO,      DRIVE_MODE_NORMAL      },   /* 現在モード : ECO     */
    {DRIVE_MODE_ECO,      DRIVE_MODE_SPORT       },   /* 現在モード : NORMAL  */
    {DRIVE_MODE_NORMAL,   DRIVE_MODE_OVER_DRIVE  },   /* 現在モード : SPORT   */
    {DRIVE_MODE_SPORT,    DRIVE_MODE_OVER_DRIVE  }    /* 現在モード : OVER_DRIVE(解放フルバースト) */
};

/*********************************************************************************/
/* コンポーネント外部公開関数定義                                                */
/*********************************************************************************/
/*********************************************************************************/
/* 関数   | vdg_ogw_get_drvmd( void )                                            */
/* 説明   | ドライブモード取得関数宣言   初期化関数を実行しておくこと            */
/* 引数   | なし                                                                 */
/* 戻り値 | なし                                                                 */
/* 作成   | 2025 / 10 /06                                                        */
/*********************************************************************************/
void vdg_ogw_get_drvmd( void )
{  
    u1 u1s_temp_pastdrvmd   = u1g_ogw_crtdrvmd;      /* 現在のドライブモード取得 */

    u1 u1s_temp_drvmdsw_pushed =  u1s_drvmdsw_conf();        /* ボタン押下を確認 */

    if((u1s_temp_drvmdsw_pushed == DRVMDSWUP_IS_PUSHED)
     ||(u1s_temp_drvmdsw_pushed == DRVMDSWDW_IS_PUSHED))
    {
        /* スイッチ種類と現在のモードを代入すると移行先のモードが設定される */
        u1g_ogw_crtdrvmd = NEXT_DRVMD_TBL[u1s_temp_pastdrvmd][u1s_temp_drvmdsw_pushed];
        u1g_ogw_drvmdsw_status = DRVMDSW_STATUS_SUCESS; /* ボタン固着なし状態 */
    }

    if(u1s_temp_drvmdsw_pushed == DRVMDSW_IS_NOT_PUSHED)
    {
        u1g_ogw_crtdrvmd = u1s_temp_pastdrvmd; /* ボタン非押下なら遷移しない */
        u1g_ogw_drvmdsw_status = DRVMDSW_STATUS_SUCCESS; /* ボタン固着なし状態 */
    }     


    if(u1s_temp_drvmdsw_pushed == DRVMDSW_IS_ERROR)
    {
        u1g_ogw_crtdrvmd = u1s_temp_pastdrvmd; /* ボタン状態エラーなら遷移しない */
        u1g_ogw_drvmdsw_status = DRVMDSW_STATUS_FAILED; /* ボタン固着あり状態 */
    } 

}

/*********************************************************************************/
/* コンポーネント内部公開関数定義                                                */
/*********************************************************************************/
/*********************************************************************************/
/* 関数   | u1s_drvmdsw_conf( void )                                             */
/* 説明   | 押下ボタン種類判定                                                   */
/* 引数   | なし                                                                 */
/* 戻り値 | u1型 スイッチステータス                                              */
/* 作成   | 2025 / 10 /06 ?                                                       */
/*********************************************************************************/
static u1 u1s_drvmdsw_conf( void ) 
{
    static u2 u2s_temp_drvmdswup_cnt = 0;
    static u2 u2s_temp_drvmdswdw_cnt = 0;
    u1 u1s_temp_drvmdsw_pushsts = DRVMDSW_IS_NOT_PUSHED;

    if(Ked.DrvmdSwUp.Pushed())
    {
        u2s_temp_drvmdswup_cnt = u2s_temp_drvmdswup_cnt + 1;
        /* 一応上限ガード */
        if(u2s_temp_drvmdswup_cnt >= DRVMDSW_CNT_TIME_MAX)
        {
            u2s_temp_drvmdswup_cnt = DRVMDSW_CNT_TIME_MAX;
        }
    }
    else
    {
        if(u2s_temp_drvmdswup_cnt > 0)
        {
            u2s_temp_drvmdswup_cnt = u2s_temp_drvmdswup_cnt - 1;
        }
    }

    if(Ked.DrvmdSwDw.Pushed())
    {
        u2s_temp_drvmdswdw_cnt = u2s_temp_drvmdswdw_cnt + 1;
        /* 一応上限ガード */
        if(u2s_temp_drvmdswdw_cnt >= DRVMDSW_CNT_TIME_MAX)
        {
            u2s_temp_drvmdswdw_cnt = DRVMDSW_CNT_TIME_MAX;
        }
    }
    else
    {
        if(u2s_temp_drvmdswdw_cnt > 0)
        {
            u2s_temp_drvmdswdw_cnt = u2s_temp_drvmdswdw_cnt - 1;
        }
    }

    /* 同時押しは固着モード判定にする． */
    if((u2s_temp_drvmdswup_cnt >= DRVMDSW_PUSHED_TIME_DEFINE)
     &&(u2s_temp_drvmdswdw_cnt >= DRVMDSW_PUSHED_TIME_DEFINE))
    {
        u1s_temp_drvmdsw_pushsts = DRVMDSW_IS_ERROR;
    }

    /* UPカウントが押下定義時間を超えたらUP押下判定 */
    if(u2s_temp_drvmdswup_cnt >= DRVMDSW_PUSHED_TIME_DEFINE)
    {
        u1s_temp_drvmdsw_pushsts = DRVMDSWUP_IS_PUSHED;
    }

    /* DWカウントが押下定義時間を超えたDWP押下判定 */
    if(u2s_temp_drvmdswdw_cnt >= DRVMDSW_PUSHED_TIME_DEFINE)
    {
        u1s_temp_drvmdsw_pushsts = DRVMDSWDW_IS_PUSHED;
    }

    /* UP or DWカウントが固着定義時間を超えたら固着判定 */
    if((u2s_temp_drvmdswup_cnt >= DRVMDSW_HOLD_TIME_DEFINE)
     ||(u2s_temp_drvmdswdw_cnt >= DRVMDSW_HOLD_TIME_DEFINE))
    {
       u1s_temp_drvmdsw_pushsts = DRVMDSW_IS_ERROR;
    }

    return u1s_temp_drvmdsw_pushsts;

}

/*********************************************************************************/
/* EOF                                                                           */
/*********************************************************************************/


