汎用目的組み込みプロジェクトプロトタイプ

VERSIOM1.0 : プロトタイプ作成
VERSION2.0 : KED_MODEカプセル追加
VERSION2.1 : 簡易テスト用ダミー関数追加

emb_prj_v2.0 
├── application           Application Layer
│   ├── init_tsk.c   
│   ├── scheduler.c
│   ├── sys_tim.c
│   ├── tsk_mng.c
│   ├── tsk_que.c
│   └── tsk_sync.c
├── common                
│   ├── event_flag.c
│   └── main.c
├── component
├── driver                  MCAL HAL Layer
│   ├── asm                 assemble
│   │   └── dispatch.S      dispatch
│   ├── boot                2nd boot stage loader
│   │   ├── boot2.c         binary 
│   │   ├── reset_hdr.c     reset handler
│   │   └── vector_tbl.c    vector table
│   ├── context             context
│   │   └── context.h     
│   ├── inc                 driver include
│   │   ├── sys_def.h  
│   │   └── sys_lib.h
│   ├── linker              micon linker
│   │   └── rp24_memmap.ld
│   └── uart                uart 
│       └── sys_lib.c
└── readme.txt