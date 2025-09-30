汎用目的embedded_projectフォルダ構成

emb_prj_v1.0
├── application 
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
│   ├── asm
│   │   └── dispatch.S
│   ├── boot
│   │   ├── boot2.c
│   │   ├── reset_hdr.c
│   │   └── vector_tbl.c
│   ├── context
│   │   └── context.h
│   ├── inc
│   │   ├── sys_def.h
│   │   └── sys_lib.h
│   ├── linker
│   │   └── rp24_memmap.ld
│   └── uart
│       └── sys_lib.c
└── readme.txt


