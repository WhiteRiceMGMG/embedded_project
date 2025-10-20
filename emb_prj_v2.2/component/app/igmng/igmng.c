/*********************************************************************************/
/* Copyright OGAWA CONST                                                         */
/*********************************************************************************/
/* file : igmnh .c                                                               */
/* abst : ドライブモード調停                                                     */
/* hist : 2025 / 10 /16                                                          *
/
/*********************************************************************************/

/*********************************************************************************/
/* インクルードファイル                                                          */
/*********************************************************************************/ 
#include "igmng.h" /* 自ヘッダ */


/*********************************************************************************/
/* マクロ定義                                                                    */
/*********************************************************************************/
#define IGNITIONSW_IS_PUSHED     (u1)0  /* イグニッションスイッチ押下状態        */
#define IGNITIONSW_IS_NOT_PUSHED (u1)1  /* イグニッションスイッチ 非押下状態     */
#define IGNITIONSW_IS_ERROR      (u1)2  /*イグニッションスイッチエラー状態       */

/*********************************************************************************/
/* 変数定義                                                                      */
/*********************************************************************************/

/*********************************************************************************/
/* コンポーネント外部公開関数定義                                                */
/*********************************************************************************/
/*********************************************************************************/
/* 関数   | vdg_ogw_get_drvmd( void )                                            */
/* 説明   | ドライブモード取得関数宣言   初期化関数を実行しておくこと            */
/* 引数   | なし                                                                 */
/* 戻り値 | なし                                                                 */
/* 作成   | 2025 / 10 /16                                                        */
/*********************************************************************************/
 void u1g_igmng_igmdjudge( void )
 {
    u1 u1s_temp_igswmd = u1g_igmng_igmd;
    u1 u1s_temp_igswst = u1s_igsw_conf(); /*  ボタン押下を確認 */

    /*  ボタン押下，かつ現在イグニッションオフなら遷移 */
    if((u1s_temp_igswst == IGNITIONSW_IS_PUSHED)
     &&(u1s_temp_igswmd == IGNITION_MODE_OFF))
    {
        u1g_igmng_igmd    = IGNITION_MODE_ON;
        u1g_igmng_igswsts = IGNITIONSW_STATUS_SUCCESS; 
    }

    /*  ボタン押下，かつ現在イグニッションオンなら遷移 */
    if((u1s_temp_igswst == IGNITIONSW_IS_PUSHED)
     &&(u1s_temp_igswmd == IGNITION_MODE_ON))
    {
        u1g_igmng_igmd = IGNITION_MODE_OFF;
        u1g_igmng_igswsts = IGNITIONSW_STATUS_SUCCESS; 
    }
    
     /* ボタン非状態なら遷移しない */
    if(u1s_temp_igswst == IGNITIONSW_IS_ERROR)
    {
        u1g_igmng_igmd    = u1s_temp_igswmd ;
        u1g_igmng_igswsts = IGNITIONSW_STATUS_SUCCESS;
    }     

     /* ボタン状態エラーなら遷移しない */
    if(u1s_temp_igswst == IGNITIONSW_IS_ERROR)
    {
        u1g_igmng_igmd    = u1s_temp_igswmd ;
        u1g_igmng_igswsts = IGNITIONSW_STATUS_FAILED;
    } 


 }

/*********************************************************************************/
/* コンポーネント内部公開関数定義                                                */
/*********************************************************************************/
/*********************************************************************************/
/* 関数   | u1s_igsw_conf( void )                                                */
/* 説明   | 押下ボタン判定                                                       */
/* 引数   | なし                                                                 */
/* 戻り値 | u1型 スイッチステータス                                              */
/* 作成   | 2025 / 10 /16                                                        */
/*********************************************************************************/
u1 u1s_igsw_conf( void )
{
    static u2 u2s_temp_igsw_cnt = 0;
    u1 u1s_temp_igsw_pushsts    = IGNITIONSW_IS_NOT_PUSHED;

    if(Ked.IgSw.Pushed())
    {
        u2s_temp_igsw_cnt = u2s_temp_igsw_cnt + 1;
        /*一応上限ガード*/
        if(u2s_temp_igsw_cnt >= IGSW_CNT_TIME_MAX)
        {
            u2s_tmep_igsw_cnt = IGSW_CNT_TIME_MAX;
        }
    }
    else
    {
        if(u2s_temp_igsw_cnt > 0)
        {
            u2s_temp_igsw_cnt = u2s_temp_igsw_cnt - 1;
        }
    }

    /* IGカウントが押下定義時間を超えたらIG押下判定 */
    if(u2s_tmep_igsw_cnt >= IGSW_PUSHED_TIME_DEFINE)
    {
        u1s_temp_igsw_pushsts = IGNITIONSW_IS_PUSHED;
    }

    /* IGカウントが固着定義時間を超えたら固着判定 */
    if(u2s_temp_igsw_cnt >= IGSW_HOLD_TIME_DEFINE)
    {
        u1s_temp_igsw_pushsts = IGNITIONSW_IS_ERROR; 
    }
    
    return u1s_temp_igsw_pushsts;

}


/*********************************************************************************/
/* EOF                                                                           */
/*********************************************************************************/


