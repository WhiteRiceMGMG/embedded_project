汎用目的組み込みプロジェクトプロトタイプ

VERSIOM1.0 : プロトタイプ作成
VERSION2.0 : KED_MODEカプセル追加
VERSION2.1 : 簡易テスト用ダミー関数追加
VERSION2.2 : RTOS適用 ボタン検出タスク+LEDイベント2つ
VERSION3.0 : OS・Application分離

.
└── emb_prj_v2.0
    ├── application  （Application Layer）
    │   ├── init_tsk.c
    │   ├── scheduler.c
    │   ├── sys_tim.c
    │   ├── tsk_mng.c
    │   ├── tsk_que.c
    │   └── tsk_sync.c
    ├── common
    │   ├── event_flag.c イベントフラグ（OS関係）
    │   └── main.c (OS関係)
    ├── component
    │   ├── compconf.h
    │   └── app
    │       ├── drvmdif.h ドライブモード公開
    │       ├── igmngif.h イグニッション公開
    │       ├── drvmd 
    │       │   ├── drvmd.h ドライブモード遷移ヘッダ
    │       │   └── drvmd.c ドライブモード遷移ロジック
    │       └── igmng
    │           ├── igmng.h イグニッション遷移ヘッダ 
    │           └── igmng.c イグニッション遷移ロジック
    └── driver  （MCAL / HAL Layer）
        ├── asm  （assemble）
        │   └── dispatch.S   （dispatch）
        ├── boot  （2nd boot stage loader）
        │   ├── boot2.c        （binary）
        │   ├── reset_hdr.c    （reset handler）
        │   └── vector_tbl.c   （vector table）
        ├── context
        │   └── context.h
        └── inc  （driver include）
            ├── sys_def.h
            └── sys_lib_


▼▼▼以下今後の機能草案▼▼▼
アプリケーション層に色々混ざっているので，OS層をつくる．
入出力に関するイベントフラグを作る（OSのものとは区別）


▼▼▼以下フォルダ構成素材▼▼▼

# emb_prj_v2.0
## application  （Application Layer）
### init_tsk.c
### scheduler.c
### sys_tim.c
### tsk_mng.c
### tsk_que.c
### tsk_sync.c

## common
### event_flag.c
### main.c

## component
###compconf.h
###app
####drvmdif.h
####igmngif.h
####drvmd
#####drvmd.c
#####drvmd.h
####igmng
#####igmng.h
#####igmng.c


## driver  （MCAL / HAL Layer）
### asm  （assemble）
#### dispatch.S   （dispatch）

### boot  （2nd boot stage loader）
#### boot2.c        （binary）
#### reset_hdr.c    （reset handler）
#### vector_tbl.c   （vector table）

### context
#### context.h

### inc  （driver include）
#### sys_def.h
#### sys_lib_

