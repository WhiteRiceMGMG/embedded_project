汎用目的組み込みプロジェクトプロトタイプ

VERSIOM1.0 : プロトタイプ作成
VERSION2.0 : KED_MODEカプセル追加
VERSION2.1 : 簡易テスト用ダミー関数追加
VERSION2.2 : RTOS適用 ボタン検出タスク+LEDイベント2つ
VERSION3.0 : OS・Application分離

.
└── emb_prj_v2.0
    ├── application  （Application Layer）
    ├── common
    │   └── main.c
    ├── component
    │   ├── compconf.h
    │   └── app
    │       ├── drvmdif.h
    │       ├── igmngif.h
    │       ├── drvmd
    │       │   ├── drvmd.c
    │       │   └── drvmd.h
    │       └── igmng
    │           ├── igmng.h
    │           └── igmng.c
    ├── driver  （MCAL / HAL Layer）
    │   ├── asm  （assemble）
    │   │   └── dispatch.S   （dispatch）
    │   ├── boot  （2nd boot stage loader）
    │   │   ├── boot2.c        （binary）
    │   │   ├── reset_hdr.c    （reset handler）
    │   │   └── vector_tbl.c   （vector table）
    │   ├── drv
    │   │   ├── button.h
    │   │   ├── button.c
    │   │   ├── driver.h
    │   │   └── driver.c
    │   ├── inc
    │   │   ├── sys_def.h
    │   │   └── sys_lib.h
    │   ├── linker
    │   │   └── rp24_memmap.ld
    │   ├── uart
    │   │   └── sys_lib.c
    │   └── context
    │       └── context.h
    ├── inc
    │   ├── api_def.h
    │   ├── err.h
    │   ├── ked_knl.h
    │   ├── knl_def.h
    │   ├── tsk_config.h
    │   └── type_def.h
    └── os
        ├── event_flg.c
        ├── init_tsk.c
        ├── scheduler.c
        ├── semaphore.c
        ├── sys_tim.c
        ├── tsk_mng.c
        ├── tsk_que.c
        └── tsk_sync.c


▼▼▼以下今後の機能草案▼▼▼
アプリケーション層に色々混ざっているので，OS層をつくる． 完了
入出力に関するイベントフラグを作る（OSのものとは区別）  
もう少しドメインが欲しいナ．．．→ 


▼▼▼以下フォルダ構成素材▼▼▼
# emb_prj_v2.0
## application  （Application Layer）
## common
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
### drv
#### button.h
#### button.c
#### driver.h
#### driver.c
### inc
#### sys_def.h
#### sys_lib.h
### linker
#### rp24_memmap.ld
### uart
#### sys_lib.c
### context
#### context.h
## inc
### api_def.h
### err.h
### ked_knl.h
### knl_def.h
### tsk_config.h
### type_def.h
## os
### event_flg.c
### init_tsk.c
### scheduler.c
### semaphore.c
### sys_tim.c
### tsk_mng.c
### tsk_que.c
### tsk_sync.c

---------------------------------------------------
