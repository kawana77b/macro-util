// Visual C++
#pragma once

//// GCC
// #ifndef MACRO_UTIL_H
// #define MACRO_UTIL_H

#include <stdlib.h>

//----------------------------------------------------------
// Array & Mem
//----------------------------------------------------------

// size_t type_t * length分のsizeofを示します
#define SIZE_OF_ELEMENTS(type_t, length) (sizeof(type_t) * length)

// size_t <T where T : struct of C> 構造体を引数に与え、指定されたメンバのsizeofを示します
#define SIZE_OF_MEMBER(type_t, member) (sizeof(((type_t*)0)->member))

// size_t 配列の要素数を示します
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

// T* 配列の最初の要素のポインタを示します
#define ARRAY_BEGIN(arr) (arr)

// T* 配列の最後のポインタを示します. これは最後のインデックスの1つ後ろの位置にあることを意味します
#define ARRAY_END(arr) (arr + ARRAY_LENGTH(arr))

// bool 配列にidxが含まれているかを示します
#define HAS_INDEX_ARRAY(arr, idx)  ((ARRAY_BEGIN(arr) <= (arr) + (idx)) && ((arr)+(idx) < ARRAY_END(arr))

// T* ヒープ領域をmallocで生成します. 失敗時NULLが返る可能性があります
#define MALLOC(type_t, size, count) (type_t*)malloc(size * count)

// T* ヒープ配列をcallocで生成します. 失敗時NULLが返る可能性があります
#define CREATE_HEAP_ARRAY(type_t, length) (type_t*)calloc(length, sizeof(type_t))

// T* ヒープ配列をlengthでreallocします. 失敗時NULLが返る可能性があります
#define RESIZE_HEAP_ARRAY(type_t, heap_arr, length) (type_t*)realloc(heap_arr, sizeof(type_t) * length)

// bool ptrがNULLか検証します
#define IS_NULL(ptr) ((ptr) == NULL)

// bool ptrがNULLでないか検証します
#define IS_NOT_NULL(ptr) ((ptr) != NULL)

// void ptrをfreeした後、ptrをNULLにします
#define FREE(ptr) do { free(ptr); ptr = NULL; } while (0)

// size_t 構造体におけるメンバのオフセットインデックスを取得します
#define OFFSET_OF(type_t, member_name) ((size_t) &((type_t*)0)->member_name)

// T* where T : struct of C 構造体のポインタを取得します
#define CONTAINER_OF(type_t, ptr, member_name) ((type_t*)((char*)(ptr) - OFFSET_OF(type_t, member_name)))

//----------------------------------------------------------
// Math
//----------------------------------------------------------

// T 引数に与えられた内最大の値を返します
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// T 引数に与えられた内最小の値を返します
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// bool 値が指定の範囲内にあるかを判定します
#define IN_RANGE(value, min, max) ((min) <= (value) && (value) <= (max))

// T 値がmaxとならない限り1インクリメントし、maxとなった場合は0クリアします
#define INCREMENT_OR_REPEAT(value, max) ((value) = ((value) + 1) % (max))

// T 値が0を下回らない限り1デクリメントし、下回った場合はmaxに差し戻して1引きます
#define DECREMENT_OR_REPEAT(value, max) (((value) = (value) - 1) < 0 ? ((value) = (max) - 1) : (value))

//----------------------------------------------------------
// Functions
//----------------------------------------------------------

// void 引数に与えられたaとbの代入値を入れ替えます
#define SWAP(type_t, a, b) do {type_t __temp = a; a = b; b = __temp;} while (0)

// void 引数に与えられたaとbをxor交換で入れ替えます
#define SWAP_XOR(a, b) do {a ^= b; b ^= a; a ^= b;} while (0)

//----------------------------------------------------------
// Conpare Expression For Order
//----------------------------------------------------------

// int <T where T : struct Of C#> qsortなどにアタッチできるオーダー関数の内部式を生成します
#define COMPARE_EXP(type_t, arg_name1, arg_name2) \
do { \
    return *(type_t*)arg_name1 - *(type_t*)arg_name2; \
} while (0)

// int <T where T : struct Of C#> qsortなどにアタッチできるオーダー関数の内部式を生成します
#define COMPARE_EXP_DEST(type_t, arg_name1, arg_name2) \
do { \
    return *(type_t*)arg_name2 - *(type_t*)arg_name1; \
} while (0)

// int <T where T : struct Of C> qsortなどにアタッチできるオーダー関数の内部式を生成します. 構造体用です
#define COMPARE_EXP_STRUCT(type_t, member_name, arg_name1, arg_name2) \
do { \
    if (((type_t*)arg_name1)->member_name > ((type_t*)arg_name2)->member_name) return -1; \
    if (((type_t*)arg_name1)->member_name < ((type_t*)arg_name2)->member_name) return 1; \
    return 0; \
} while (0)

// int <T where T : struct Of C> qsortなどにアタッチできるオーダー関数の内部式を生成します. 構造体用です
#define COMPARE_EXP_DEST_STRUCT(type_t, member_name, arg_name1, arg_name2) \
do { \
    if (((type_t*)arg_name1)->member_name < ((type_t*)arg_name2)->member_name) return -1; \
    if (((type_t*)arg_name1)->member_name > ((type_t*)arg_name2)->member_name) return 1; \
    return 0; \
} while (0)

//----------------------------------------------------------
// Debug
//----------------------------------------------------------

// void ループで配列の要素を1個づつprintfします
#define PRINTF_ARRAY_ITEMS(arr, format, length) do { for (size_t __i = 0; __i < length; __i++) { printf(format, arr[__i]); } } while (0)

// void stderrにファイル名とライン行をfprintfします
#define TRACE() do { fprintf(stderr, "%s: %d\n", __FILE__, __LINE__) } while(0)

//----------------------------------------------------------
// Algorithm
//----------------------------------------------------------

// void 配列をvalueの値で埋めます
#define ARRAY_FILL(type_t, arr, value, length) do { type_t __v = value; for (size_t __i = 0; __i < length; __i++) { arr[__i] = __v; } } while (0)

// void バブルソートアルゴリズムで配列を昇順ソートします
#define ARRAY_SORT(type_t, arr, length) \
do { \
    for (size_t __i = 0; __i < length; __i++) \
    { \
        for (size_t __j = __i + 1; __j < length; __j++) \
        { \
          if (arr[__i] > arr[__j]) { SWAP(type_t, arr[__i], arr[__j]); } \
        } \
    } \
} while (0) \

// void バブルソートアルゴリズムで配列を降順ソートします
#define ARRAY_SORT_DEST(type_t, arr, length) \
do { \
    for (size_t __i = 0; __i < length; __i++) \
    { \
        for (size_t __j = __i + 1; __j < length; __j++) \
        { \
            if (arr[__i] < arr[__j]) { SWAP(type_t, arr[__i], arr[__j]); } \
        } \
    } \
} while (0)

// void 配列の要素順序を逆転させます
#define ARRAY_REVERSE(type_t, arr, length) \
do { \
    for (size_t __i = 0; __i < length / 2; __i++) \
    { \
        SWAP(type_t, arr[__i], arr[length - __i - 1]); \
    } \
} while (0)

// void Fisher-Yatesアルゴリズムで配列をシャッフルします. 内部的にrand()を使うので事前にseed初期化を行ってください.
#define ARRAY_SHUFFLE(type_t, arr, length) \
do { \
    for(size_t __i = 0; __i < length; __i++) \
    { \
        size_t __j = rand() % length; \
        SWAP(type_t, arr[__i], arr[__j]); \
    } \
} while (0)

// void arrにvalueと等しい値があるかを探し、見つかった場合最初のインデックスをoutに代入します。何も見つからない場合はoutは-1となります. outはsignedな整数型でなければなりません
#define ARRAY_INDEX_OF(type_t, arr, value, out, length) \
do { \
    out = -1; \
    for (size_t __i = 0; __i < length; __i++) { \
        type_t __v = value; \
        if (arr[__i] == __v) { \
            out = __i; \
            break; \
        } \
    } \
} while (0)

//// GCC
// #endif