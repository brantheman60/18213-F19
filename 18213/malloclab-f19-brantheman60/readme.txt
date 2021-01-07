Found benchmark throughput 8009 for cpu type Intel(R)Xeon(R)CPUE5520@2.27GHz, benchmark regular
Throughput targets: min=4004, max=7208, benchmark=8009
Creating initial heap...
Extending heap to fit 4096 bytes...
Coalescing at block 0x800000008...
Prev_alloc = 1, Next_alloc = 1
size = 1000, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800000008, block_next = 0x800001008
Done allocating:
Address: 0x800000008,  Header: 1002,  Footer: 1000,  Footer: 1000,  SIZE: 4096, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: (nil), Prev: (nil), Size: 4096

Malloc of size 9904
Extending heap to fit 9920 bytes...
Coalescing at block 0x800001008...
Prev_alloc = 0, Next_alloc = 1
size = 26c0, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800001008, block_next = 0x8000036c8
Splitting block 0x800000008
BLOCK_NEXT 0x8000026c8
BLOCK_NEXT HEADER 1002
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: 1002,  Footer: 1002,  Footer: 1002,  SIZE: 4096, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000026c8:: Next: (nil), Prev: (nil), Size: 4096

Malloc of size 189
Splitting block 0x8000026c8
BLOCK_NEXT 0x800002798
BLOCK_NEXT HEADER f32
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: f32,  Footer: f32,  Footer: f32,  SIZE: 3888, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002798:: Next: (nil), Prev: (nil), Size: 3888

Malloc of size 16
Splitting block 0x800002798
BLOCK_NEXT 0x8000027b8
BLOCK_NEXT HEADER f12
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: f12,  Footer: f12,  Footer: f12,  SIZE: 3856, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000027b8:: Next: (nil), Prev: (nil), Size: 3856

Malloc of size 136
Splitting block 0x8000027b8
BLOCK_NEXT 0x800002858
BLOCK_NEXT HEADER e72
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: a3,  Footer: a3,  SIZE: 160, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002858,  Header: e72,  Footer: e72,  Footer: e72,  SIZE: 3696, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002858:: Next: (nil), Prev: (nil), Size: 3696

Freeing block at 0x8000027b8
Coalescing at block 0x8000027b8...
Prev_alloc = 1, Next_alloc = 0
size = a0, choose_list(block) = 0
block_prev = 0x800002798, block = 0x8000027b8, block_next = 0x800002858
Done freeing:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: f12,  Footer: f12,  Footer: f12,  SIZE: 3856, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000027b8:: Next: (nil), Prev: (nil), Size: 3856

Malloc of size 56
Splitting block 0x8000027b8
BLOCK_NEXT 0x800002808
BLOCK_NEXT HEADER ec2
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: ec2,  Footer: ec2,  Footer: ec2,  SIZE: 3776, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002808:: Next: (nil), Prev: (nil), Size: 3776

Malloc of size 88
Splitting block 0x800002808
BLOCK_NEXT 0x800002878
BLOCK_NEXT HEADER e52
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: e52,  Footer: e52,  Footer: e52,  SIZE: 3664, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002878:: Next: (nil), Prev: (nil), Size: 3664

Freeing block at 0x800000008
Coalescing at block 0x800000008...
Prev_alloc = 1, Next_alloc = 1
size = 26c0, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800000008, block_next = 0x8000026c8
Done freeing:
Address: 0x800000008,  Header: 26c2,  Footer: 26c2,  Footer: 26c2,  SIZE: 9920, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: e52,  Footer: e52,  Footer: e52,  SIZE: 3664, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002878, Prev: (nil), Size: 9920
Curr: 0x800002878:: Next: (nil), Prev: 0x800000008, Size: 3664

Malloc of size 90
Splitting block 0x800002878
BLOCK_NEXT 0x8000028e8
BLOCK_NEXT HEADER de2
Done allocating:
Address: 0x800000008,  Header: 26c2,  Footer: 26c2,  Footer: 26c2,  SIZE: 9920, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000028e8:: Next: 0x800000008, Prev: (nil), Size: 3552
Curr: 0x800000008:: Next: (nil), Prev: 0x8000028e8, Size: 9920

Freeing block at 0x800002798
Coalescing at block 0x800002798...
Prev_alloc = 1, Next_alloc = 1
size = 20, choose_list(block) = 0
block_prev = 0x8000026c8, block = 0x800002798, block_next = 0x8000027b8
Done freeing:
Address: 0x800000008,  Header: 26c2,  Footer: 26c2,  Footer: 26c2,  SIZE: 9920, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 22,  Footer: 22,  Footer: 22,  SIZE: 32, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002798:: Next: 0x8000028e8, Prev: (nil), Size: 32
Curr: 0x8000028e8:: Next: 0x800000008, Prev: 0x800002798, Size: 3552
Curr: 0x800000008:: Next: (nil), Prev: 0x8000028e8, Size: 9920

Malloc of size 160
Splitting block 0x800000008
BLOCK_NEXT 0x8000000b8
BLOCK_NEXT HEADER 2612
Done allocating:
Address: 0x800000008,  Header: b3,  Footer: b3,  SIZE: 176, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000000b8,  Header: 2612,  Footer: 2612,  Footer: 2612,  SIZE: 9744, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 22,  Footer: 22,  Footer: 22,  SIZE: 32, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000000b8:: Next: 0x800002798, Prev: (nil), Size: 9744
Curr: 0x800002798:: Next: 0x8000028e8, Prev: 0x8000000b8, Size: 32
Curr: 0x8000028e8:: Next: (nil), Prev: 0x800002798, Size: 3552

Freeing block at 0x8000026c8
Coalescing at block 0x8000026c8...
Prev_alloc = 0, Next_alloc = 0
size = d0, choose_list(block) = 0
block_prev = 0x8000000b8, block = 0x8000026c8, block_next = 0x800002798
Done freeing:
Address: 0x800000008,  Header: b3,  Footer: b3,  SIZE: 176, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000000b8,  Header: 2702,  Footer: 2702,  Footer: 2702,  SIZE: 9984, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000000b8:: Next: 0x8000028e8, Prev: (nil), Size: 9984
Curr: 0x8000028e8:: Next: (nil), Prev: 0x8000000b8, Size: 3552

Malloc of size 32
Splitting block 0x8000028e8
BLOCK_NEXT 0x800002918
BLOCK_NEXT HEADER db2
Done allocating:
Address: 0x800000008,  Header: b3,  Footer: b3,  SIZE: 176, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000000b8,  Header: 2702,  Footer: 2702,  Footer: 2702,  SIZE: 9984, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 33,  Footer: 33,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: db2,  Footer: db2,  Footer: db2,  SIZE: 3504, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002918:: Next: 0x8000000b8, Prev: (nil), Size: 3504
Curr: 0x8000000b8:: Next: (nil), Prev: 0x800002918, Size: 9984

Freeing block at 0x800000008
Coalescing at block 0x800000008...
Prev_alloc = 1, Next_alloc = 0
size = b0, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800000008, block_next = 0x8000000b8
Done freeing:
Address: 0x800000008,  Header: 27b2,  Footer: 27b2,  Footer: 27b2,  SIZE: 10160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 33,  Footer: 33,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: db2,  Footer: db2,  Footer: db2,  SIZE: 3504, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002918, Prev: (nil), Size: 10160
Curr: 0x800002918:: Next: (nil), Prev: 0x800000008, Size: 3504

Freeing block at 0x800002878
Coalescing at block 0x800002878...
Prev_alloc = 1, Next_alloc = 1
size = 70, choose_list(block) = 0
block_prev = 0x800002808, block = 0x800002878, block_next = 0x8000028e8
Done freeing:
Address: 0x800000008,  Header: 27b2,  Footer: 27b2,  Footer: 27b2,  SIZE: 10160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 72,  Footer: 72,  Footer: 72,  SIZE: 112, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 31,  Footer: 31,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002918,  Header: db2,  Footer: db2,  Footer: db2,  SIZE: 3504, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002878:: Next: 0x800000008, Prev: (nil), Size: 112
Curr: 0x800000008:: Next: 0x800002918, Prev: 0x800002878, Size: 10160
Curr: 0x800002918:: Next: (nil), Prev: 0x800000008, Size: 3504

Malloc of size 12
Splitting block 0x800002918
BLOCK_NEXT 0x800002938
BLOCK_NEXT HEADER d92
Done allocating:
Address: 0x800000008,  Header: 27b2,  Footer: 27b2,  Footer: 27b2,  SIZE: 10160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 72,  Footer: 72,  Footer: 72,  SIZE: 112, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 31,  Footer: 31,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002918,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002938:: Next: 0x800002878, Prev: (nil), Size: 3472
Curr: 0x800002878:: Next: 0x800000008, Prev: 0x800002938, Size: 112
Curr: 0x800000008:: Next: (nil), Prev: 0x800002878, Size: 10160

Freeing block at 0x8000027b8
Coalescing at block 0x8000027b8...
Prev_alloc = 0, Next_alloc = 1
size = 50, choose_list(block) = 0
block_prev = 0x800000008, block = 0x8000027b8, block_next = 0x800002808
Done freeing:
Address: 0x800000008,  Header: 2802,  Footer: 2802,  Footer: 2802,  SIZE: 10240, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 71,  Footer: 71,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002878,  Header: 72,  Footer: 72,  Footer: 72,  SIZE: 112, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 31,  Footer: 31,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002918,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002938, Prev: (nil), Size: 10240
Curr: 0x800002938:: Next: 0x800002878, Prev: 0x800000008, Size: 3472
Curr: 0x800002878:: Next: (nil), Prev: 0x800002938, Size: 112

Freeing block at 0x8000028e8
Coalescing at block 0x8000028e8...
Prev_alloc = 0, Next_alloc = 1
size = 30, choose_list(block) = 0
block_prev = 0x800002878, block = 0x8000028e8, block_next = 0x800002918
Done freeing:
Address: 0x800000008,  Header: 2802,  Footer: 2802,  Footer: 2802,  SIZE: 10240, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 71,  Footer: 71,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002878,  Header: a2,  Footer: a2,  Footer: a2,  SIZE: 160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: 21,  Footer: 21,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002878:: Next: 0x800000008, Prev: (nil), Size: 160
Curr: 0x800000008:: Next: 0x800002938, Prev: 0x800002878, Size: 10240
Curr: 0x800002938:: Next: (nil), Prev: 0x800000008, Size: 3472

Freeing block at 0x800002808
Coalescing at block 0x800002808...
Prev_alloc = 0, Next_alloc = 0
size = 70, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800002808, block_next = 0x800002878
Done freeing:
Address: 0x800000008,  Header: 2912,  Footer: 2912,  Footer: 2912,  SIZE: 10512, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: 21,  Footer: 21,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002938, Prev: (nil), Size: 10512
Curr: 0x800002938:: Next: (nil), Prev: 0x800000008, Size: 3472

Freeing block at 0x800002918
Coalescing at block 0x800002918...
Prev_alloc = 0, Next_alloc = 0
size = 20, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800002918, block_next = 0x800002938
Done freeing:
Address: 0x800000008,  Header: 36c2,  Footer: 36c2,  Footer: 36c2,  SIZE: 14016, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: (nil), Prev: (nil), Size: 14016

Creating initial heap...
Extending heap to fit 4096 bytes...
Coalescing at block 0x800000008...
Prev_alloc = 1, Next_alloc = 1
size = 1000, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800000008, block_next = 0x800001008
Done allocating:
Address: 0x800000008,  Header: 1002,  Footer: 1000,  Footer: 1000,  SIZE: 4096, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: (nil), Prev: (nil), Size: 4096

Malloc of size 9904
Extending heap to fit 9920 bytes...
Coalescing at block 0x800001008...
Prev_alloc = 0, Next_alloc = 1
size = 26c0, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800001008, block_next = 0x8000036c8
Splitting block 0x800000008
BLOCK_NEXT 0x8000026c8
BLOCK_NEXT HEADER 1002
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: 1002,  Footer: 1002,  Footer: 1002,  SIZE: 4096, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000026c8:: Next: (nil), Prev: (nil), Size: 4096

Malloc of size 189
Splitting block 0x8000026c8
BLOCK_NEXT 0x800002798
BLOCK_NEXT HEADER f32
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: f32,  Footer: f32,  Footer: f32,  SIZE: 3888, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002798:: Next: (nil), Prev: (nil), Size: 3888

Malloc of size 16
Splitting block 0x800002798
BLOCK_NEXT 0x8000027b8
BLOCK_NEXT HEADER f12
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: f12,  Footer: f12,  Footer: f12,  SIZE: 3856, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000027b8:: Next: (nil), Prev: (nil), Size: 3856

Malloc of size 136
Splitting block 0x8000027b8
BLOCK_NEXT 0x800002858
BLOCK_NEXT HEADER e72
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: a3,  Footer: a3,  SIZE: 160, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002858,  Header: e72,  Footer: e72,  Footer: e72,  SIZE: 3696, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002858:: Next: (nil), Prev: (nil), Size: 3696

Freeing block at 0x8000027b8
Coalescing at block 0x8000027b8...
Prev_alloc = 1, Next_alloc = 0
size = a0, choose_list(block) = 0
block_prev = 0x800002798, block = 0x8000027b8, block_next = 0x800002858
Done freeing:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: f12,  Footer: f12,  Footer: f12,  SIZE: 3856, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000027b8:: Next: (nil), Prev: (nil), Size: 3856

Malloc of size 56
Splitting block 0x8000027b8
BLOCK_NEXT 0x800002808
BLOCK_NEXT HEADER ec2
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: ec2,  Footer: ec2,  Footer: ec2,  SIZE: 3776, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002808:: Next: (nil), Prev: (nil), Size: 3776

Malloc of size 88
Splitting block 0x800002808
BLOCK_NEXT 0x800002878
BLOCK_NEXT HEADER e52
Done allocating:
Address: 0x800000008,  Header: 26c3,  Footer: 26c3,  SIZE: 9920, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d3,  Footer: d3,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: e52,  Footer: e52,  Footer: e52,  SIZE: 3664, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002878:: Next: (nil), Prev: (nil), Size: 3664

Freeing block at 0x800000008
Coalescing at block 0x800000008...
Prev_alloc = 1, Next_alloc = 1
size = 26c0, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800000008, block_next = 0x8000026c8
Done freeing:
Address: 0x800000008,  Header: 26c2,  Footer: 26c2,  Footer: 26c2,  SIZE: 9920, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: e52,  Footer: e52,  Footer: e52,  SIZE: 3664, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002878, Prev: (nil), Size: 9920
Curr: 0x800002878:: Next: (nil), Prev: 0x800000008, Size: 3664

Malloc of size 90
Splitting block 0x800002878
BLOCK_NEXT 0x8000028e8
BLOCK_NEXT HEADER de2
Done allocating:
Address: 0x800000008,  Header: 26c2,  Footer: 26c2,  Footer: 26c2,  SIZE: 9920, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 53,  Footer: 53,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000028e8:: Next: 0x800000008, Prev: (nil), Size: 3552
Curr: 0x800000008:: Next: (nil), Prev: 0x8000028e8, Size: 9920

Freeing block at 0x800002798
Coalescing at block 0x800002798...
Prev_alloc = 1, Next_alloc = 1
size = 20, choose_list(block) = 0
block_prev = 0x8000026c8, block = 0x800002798, block_next = 0x8000027b8
Done freeing:
Address: 0x800000008,  Header: 26c2,  Footer: 26c2,  Footer: 26c2,  SIZE: 9920, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 22,  Footer: 22,  Footer: 22,  SIZE: 32, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002798:: Next: 0x8000028e8, Prev: (nil), Size: 32
Curr: 0x8000028e8:: Next: 0x800000008, Prev: 0x800002798, Size: 3552
Curr: 0x800000008:: Next: (nil), Prev: 0x8000028e8, Size: 9920

Malloc of size 160
Splitting block 0x800000008
BLOCK_NEXT 0x8000000b8
BLOCK_NEXT HEADER 2612
Done allocating:
Address: 0x800000008,  Header: b3,  Footer: b3,  SIZE: 176, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000000b8,  Header: 2612,  Footer: 2612,  Footer: 2612,  SIZE: 9744, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000026c8,  Header: d1,  Footer: d1,  SIZE: 208, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002798,  Header: 22,  Footer: 22,  Footer: 22,  SIZE: 32, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000000b8:: Next: 0x800002798, Prev: (nil), Size: 9744
Curr: 0x800002798:: Next: 0x8000028e8, Prev: 0x8000000b8, Size: 32
Curr: 0x8000028e8:: Next: (nil), Prev: 0x800002798, Size: 3552

Freeing block at 0x8000026c8
Coalescing at block 0x8000026c8...
Prev_alloc = 0, Next_alloc = 0
size = d0, choose_list(block) = 0
block_prev = 0x8000000b8, block = 0x8000026c8, block_next = 0x800002798
Done freeing:
Address: 0x800000008,  Header: b3,  Footer: b3,  SIZE: 176, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000000b8,  Header: 2702,  Footer: 2702,  Footer: 2702,  SIZE: 9984, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: de2,  Footer: de2,  Footer: de2,  SIZE: 3552, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x8000000b8:: Next: 0x8000028e8, Prev: (nil), Size: 9984
Curr: 0x8000028e8:: Next: (nil), Prev: 0x8000000b8, Size: 3552

Malloc of size 32
Splitting block 0x8000028e8
BLOCK_NEXT 0x800002918
BLOCK_NEXT HEADER db2
Done allocating:
Address: 0x800000008,  Header: b3,  Footer: b3,  SIZE: 176, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000000b8,  Header: 2702,  Footer: 2702,  Footer: 2702,  SIZE: 9984, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 33,  Footer: 33,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: db2,  Footer: db2,  Footer: db2,  SIZE: 3504, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002918:: Next: 0x8000000b8, Prev: (nil), Size: 3504
Curr: 0x8000000b8:: Next: (nil), Prev: 0x800002918, Size: 9984

Freeing block at 0x800000008
Coalescing at block 0x800000008...
Prev_alloc = 1, Next_alloc = 0
size = b0, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800000008, block_next = 0x8000000b8
Done freeing:
Address: 0x800000008,  Header: 27b2,  Footer: 27b2,  Footer: 27b2,  SIZE: 10160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 33,  Footer: 33,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: db2,  Footer: db2,  Footer: db2,  SIZE: 3504, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002918, Prev: (nil), Size: 10160
Curr: 0x800002918:: Next: (nil), Prev: 0x800000008, Size: 3504

Freeing block at 0x800002878
Coalescing at block 0x800002878...
Prev_alloc = 1, Next_alloc = 1
size = 70, choose_list(block) = 0
block_prev = 0x800002808, block = 0x800002878, block_next = 0x8000028e8
Done freeing:
Address: 0x800000008,  Header: 27b2,  Footer: 27b2,  Footer: 27b2,  SIZE: 10160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 72,  Footer: 72,  Footer: 72,  SIZE: 112, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 31,  Footer: 31,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002918,  Header: db2,  Footer: db2,  Footer: db2,  SIZE: 3504, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002878:: Next: 0x800000008, Prev: (nil), Size: 112
Curr: 0x800000008:: Next: 0x800002918, Prev: 0x800002878, Size: 10160
Curr: 0x800002918:: Next: (nil), Prev: 0x800000008, Size: 3504

Malloc of size 12
Splitting block 0x800002918
BLOCK_NEXT 0x800002938
BLOCK_NEXT HEADER d92
Done allocating:
Address: 0x800000008,  Header: 27b2,  Footer: 27b2,  Footer: 27b2,  SIZE: 10160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000027b8,  Header: 51,  Footer: 51,  SIZE: 80, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002808,  Header: 73,  Footer: 73,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002878,  Header: 72,  Footer: 72,  Footer: 72,  SIZE: 112, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 31,  Footer: 31,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002918,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002938:: Next: 0x800002878, Prev: (nil), Size: 3472
Curr: 0x800002878:: Next: 0x800000008, Prev: 0x800002938, Size: 112
Curr: 0x800000008:: Next: (nil), Prev: 0x800002878, Size: 10160

Freeing block at 0x8000027b8
Coalescing at block 0x8000027b8...
Prev_alloc = 0, Next_alloc = 1
size = 50, choose_list(block) = 0
block_prev = 0x800000008, block = 0x8000027b8, block_next = 0x800002808
Done freeing:
Address: 0x800000008,  Header: 2802,  Footer: 2802,  Footer: 2802,  SIZE: 10240, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 71,  Footer: 71,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002878,  Header: 72,  Footer: 72,  Footer: 72,  SIZE: 112, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x8000028e8,  Header: 31,  Footer: 31,  SIZE: 48, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002918,  Header: 23,  Footer: 23,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 1
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002938, Prev: (nil), Size: 10240
Curr: 0x800002938:: Next: 0x800002878, Prev: 0x800000008, Size: 3472
Curr: 0x800002878:: Next: (nil), Prev: 0x800002938, Size: 112

Freeing block at 0x8000028e8
Coalescing at block 0x8000028e8...
Prev_alloc = 0, Next_alloc = 1
size = 30, choose_list(block) = 0
block_prev = 0x800002878, block = 0x8000028e8, block_next = 0x800002918
Done freeing:
Address: 0x800000008,  Header: 2802,  Footer: 2802,  Footer: 2802,  SIZE: 10240, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002808,  Header: 71,  Footer: 71,  SIZE: 112, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002878,  Header: a2,  Footer: a2,  Footer: a2,  SIZE: 160, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: 21,  Footer: 21,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800002878:: Next: 0x800000008, Prev: (nil), Size: 160
Curr: 0x800000008:: Next: 0x800002938, Prev: 0x800002878, Size: 10240
Curr: 0x800002938:: Next: (nil), Prev: 0x800000008, Size: 3472

Freeing block at 0x800002808
Coalescing at block 0x800002808...
Prev_alloc = 0, Next_alloc = 0
size = 70, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800002808, block_next = 0x800002878
Done freeing:
Address: 0x800000008,  Header: 2912,  Footer: 2912,  Footer: 2912,  SIZE: 10512, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Address: 0x800002918,  Header: 21,  Footer: 21,  SIZE: 32, ALLOC STATUS: 1, 
PREV_ALLOC STATUS: 0
Address: 0x800002938,  Header: d92,  Footer: d92,  Footer: d92,  SIZE: 3472, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: 0x800002938, Prev: (nil), Size: 10512
Curr: 0x800002938:: Next: (nil), Prev: 0x800000008, Size: 3472

Freeing block at 0x800002918
Coalescing at block 0x800002918...
Prev_alloc = 0, Next_alloc = 0
size = 20, choose_list(block) = 0
block_prev = 0x800000008, block = 0x800002918, block_next = 0x800002938
Done freeing:
Address: 0x800000008,  Header: 36c2,  Footer: 36c2,  Footer: 36c2,  SIZE: 14016, ALLOC STATUS: 0, 
PREV_ALLOC STATUS: 1
Printing heads_of_free[0]:
Curr: 0x800000008:: Next: (nil), Prev: (nil), Size: 14016



correctness check finished, by running tracefile "traces/syn-mix-short.rep".
 => correct.

Average utilization = 0.0%.
Average throughput (Kops/sec) = 0.
Perf index = 0.0 (util) + 0.0 (thru) = 0.0/100
SBRK_COUNT = 4
