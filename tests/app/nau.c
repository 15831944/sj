#ifdef WIN32
#pragma warning(disable:4996)
#define GLEW_STATIC
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
/**
* Maximum number of attributes per vertex
*
* @private
*/
#define MAX_VERTEX_ATTRIBUTE 16    
#ifdef EMSCRIPTEN
#include <GLES3/gl3.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif
#ifdef EMSCRIPTEN
#include <SDL.h>
#endif
#ifdef WIN32
#include <SDL.h>
#endif
#ifdef __APPLE__
#include <SDL2/SDL.h>
#endif
#include <assert.h>
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif
#ifdef EMSCRIPTEN
#include <emscripten/html5.h>
#endif
#include <float.h>
#include <ft2build.h>
#include <limits.h>
#include <math.h>
#include <png.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include FT_FREETYPE_H
#include FT_LCD_FILTER_H
#include FT_STROKER_H

   /* memcmp, memset, strlen */
   /* ptrdiff_t */
   /* exit */
/* These macros use decltype or the earlier __typeof GNU extension.
As decltype is only available in newer compilers (VS2010 or gcc 4.3+
when compiling c++ source) this code uses whatever method is needed
or, for VS2008 where neither is available, uses casting workarounds. */
#if !defined(DECLTYPE) && !defined(NO_DECLTYPE)
#if defined(_MSC_VER)   /* MS compiler */
#if _MSC_VER >= 1600 && defined(__cplusplus)  /* VS2010 or newer in C++ mode */
#define DECLTYPE(x) (decltype(x))
#else                   /* VS2008 or older (or VS2010 in C mode) */
#define NO_DECLTYPE
#endif
#elif defined(__BORLANDC__) || defined(__ICCARM__) || defined(__LCC__) || defined(__WATCOMC__)
#define NO_DECLTYPE
#else                   /* GNU, Sun and other compilers */
#define DECLTYPE(x) (__typeof(x))
#endif
#endif
#ifdef NO_DECLTYPE
#define DECLTYPE(x)
#define DECLTYPE_ASSIGN(dst,src)                                                 \
do {                                                                             \
char **_da_dst = (char**)(&(dst));                                             \
*_da_dst = (char*)(src);                                                       \
} while (0)
#else
#define DECLTYPE_ASSIGN(dst,src)                                                 \
do {                                                                             \
(dst) = DECLTYPE(dst)(src);                                                    \
} while (0)
#endif
/* a number of the hash function use uint32_t which isn't defined on Pre VS2010 */
#if defined(_WIN32)
#if defined(_MSC_VER) && _MSC_VER >= 1600
#include <stdint.h>
#elif defined(__WATCOMC__) || defined(__MINGW32__) || defined(__CYGWIN__)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#endif
#elif defined(__GNUC__) && !defined(__VXWORKS__)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#endif
#ifndef uthash_malloc
#define uthash_malloc(sz) malloc(sz)      /* malloc fcn                      */
#endif
#ifndef uthash_free
#define uthash_free(ptr,sz) free(ptr)     /* free fcn                        */
#endif
#ifndef uthash_bzero
#define uthash_bzero(a,n) memset(a,'\0',n)
#endif
#ifndef uthash_memcmp
#define uthash_memcmp(a,b,n) memcmp(a,b,n)
#endif
#ifndef uthash_strlen
#define uthash_strlen(s) strlen(s)
#endif
#ifndef uthash_noexpand_fyi
#define uthash_noexpand_fyi(tbl)          /* can be defined to log noexpand  */
#endif
#ifndef uthash_expand_fyi
#define uthash_expand_fyi(tbl)            /* can be defined to log expands   */
#endif
#ifndef HASH_NONFATAL_OOM
#define HASH_NONFATAL_OOM 0
#endif
#if HASH_NONFATAL_OOM
/* malloc failures can be recovered from */
#ifndef uthash_nonfatal_oom
#define uthash_nonfatal_oom(obj) do {} while (0)    /* non-fatal OOM error */
#endif
#define HASH_RECORD_OOM(oomed) do { (oomed) = 1; } while (0)
#define IF_HASH_NONFATAL_OOM(x) x
#else
/* malloc failures result in lost memory, hash tables are unusable */
#ifndef uthash_fatal
#define uthash_fatal(msg) halt("Unknown")        /* fatal OOM error */
#endif
#define HASH_RECORD_OOM(oomed) uthash_fatal("out of memory")
#define IF_HASH_NONFATAL_OOM(x)
#endif
/* initial number of buckets */
#define HASH_INITIAL_NUM_BUCKETS 32U     /* initial number of buckets        */
#define HASH_INITIAL_NUM_BUCKETS_LOG2 5U /* lg2 of initial number of buckets */
#define HASH_BKT_CAPACITY_THRESH 10U     /* expand when bucket count reaches */
/* calculate the element whose hash handle address is hhp */
#define ELMT_FROM_HH(tbl,hhp) ((void*)(((char*)(hhp)) - ((tbl)->hho)))
/* calculate the hash handle from element address elp */
#define HH_FROM_ELMT(tbl,elp) ((UT_hash_handle *)(((char*)(elp)) + ((tbl)->hho)))
#define HASH_ROLLBACK_BKT(hh, head, itemptrhh)                                   \
do {                                                                             \
struct UT_hash_handle *_hd_hh_item = (itemptrhh);                              \
unsigned _hd_bkt;                                                              \
HASH_TO_BKT(_hd_hh_item->hashv, (head)->hh.tbl->num_buckets, _hd_bkt);         \
(head)->hh.tbl->buckets[_hd_bkt].count++;                                      \
_hd_hh_item->hh_next = NULL;                                                   \
_hd_hh_item->hh_prev = NULL;                                                   \
} while (0)
#define HASH_VALUE(keyptr,keylen,hashv)                                          \
do {                                                                             \
HASH_FCN(keyptr, keylen, hashv);                                               \
} while (0)
#define HASH_FIND_BYHASHVALUE(hh,head,keyptr,keylen,hashval,out)                 \
do {                                                                             \
(out) = NULL;                                                                  \
if (head) {                                                                    \
unsigned _hf_bkt;                                                            \
HASH_TO_BKT(hashval, (head)->hh.tbl->num_buckets, _hf_bkt);                  \
if (HASH_BLOOM_TEST((head)->hh.tbl, hashval) != 0) {                         \
HASH_FIND_IN_BKT((head)->hh.tbl, hh, (head)->hh.tbl->buckets[ _hf_bkt ], keyptr, keylen, hashval, out); \
}                                                                            \
}                                                                              \
} while (0)
#define HASH_FIND(hh,head,keyptr,keylen,out)                                     \
do {                                                                             \
unsigned _hf_hashv;                                                            \
HASH_VALUE(keyptr, keylen, _hf_hashv);                                         \
HASH_FIND_BYHASHVALUE(hh, head, keyptr, keylen, _hf_hashv, out);               \
} while (0)
#ifdef HASH_BLOOM
#define HASH_BLOOM_BITLEN (1UL << HASH_BLOOM)
#define HASH_BLOOM_BYTELEN (HASH_BLOOM_BITLEN/8UL) + (((HASH_BLOOM_BITLEN%8UL)!=0UL) ? 1UL : 0UL)
#define HASH_BLOOM_MAKE(tbl,oomed)                                               \
do {                                                                             \
(tbl)->bloom_nbits = HASH_BLOOM;                                               \
(tbl)->bloom_bv = (uint8_t*)uthash_malloc(HASH_BLOOM_BYTELEN);                 \
if (!(tbl)->bloom_bv) {                                                        \
HASH_RECORD_OOM(oomed);                                                      \
} else {                                                                       \
uthash_bzero((tbl)->bloom_bv, HASH_BLOOM_BYTELEN);                           \
(tbl)->bloom_sig = HASH_BLOOM_SIGNATURE;                                     \
}                                                                              \
} while (0)
#define HASH_BLOOM_FREE(tbl)                                                     \
do {                                                                             \
uthash_free((tbl)->bloom_bv, HASH_BLOOM_BYTELEN);                              \
} while (0)
#define HASH_BLOOM_BITSET(bv,idx) (bv[(idx)/8U] |= (1U << ((idx)%8U)))
#define HASH_BLOOM_BITTEST(bv,idx) (bv[(idx)/8U] & (1U << ((idx)%8U)))
#define HASH_BLOOM_ADD(tbl,hashv)                                                \
HASH_BLOOM_BITSET((tbl)->bloom_bv, ((hashv) & (uint32_t)((1UL << (tbl)->bloom_nbits) - 1U)))
#define HASH_BLOOM_TEST(tbl,hashv)                                               \
HASH_BLOOM_BITTEST((tbl)->bloom_bv, ((hashv) & (uint32_t)((1UL << (tbl)->bloom_nbits) - 1U)))
#else
#define HASH_BLOOM_MAKE(tbl,oomed)
#define HASH_BLOOM_FREE(tbl)
#define HASH_BLOOM_ADD(tbl,hashv)
#define HASH_BLOOM_TEST(tbl,hashv) (1)
#define HASH_BLOOM_BYTELEN 0U
#endif
#define HASH_MAKE_TABLE(hh,head,oomed)                                           \
do {                                                                             \
(head)->hh.tbl = (UT_hash_table*)uthash_malloc(sizeof(UT_hash_table));         \
if (!(head)->hh.tbl) {                                                         \
HASH_RECORD_OOM(oomed);                                                      \
} else {                                                                       \
uthash_bzero((head)->hh.tbl, sizeof(UT_hash_table));                         \
(head)->hh.tbl->tail = &((head)->hh);                                        \
(head)->hh.tbl->num_buckets = HASH_INITIAL_NUM_BUCKETS;                      \
(head)->hh.tbl->log2_num_buckets = HASH_INITIAL_NUM_BUCKETS_LOG2;            \
(head)->hh.tbl->hho = (char*)(&(head)->hh) - (char*)(head);                  \
(head)->hh.tbl->buckets = (UT_hash_bucket*)uthash_malloc(                    \
HASH_INITIAL_NUM_BUCKETS * sizeof(struct UT_hash_bucket));               \
(head)->hh.tbl->signature = HASH_SIGNATURE;                                  \
if (!(head)->hh.tbl->buckets) {                                              \
HASH_RECORD_OOM(oomed);                                                    \
uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                        \
} else {                                                                     \
uthash_bzero((head)->hh.tbl->buckets,                                      \
HASH_INITIAL_NUM_BUCKETS * sizeof(struct UT_hash_bucket));             \
HASH_BLOOM_MAKE((head)->hh.tbl, oomed);                                    \
IF_HASH_NONFATAL_OOM(                                                      \
if (oomed) {                                                             \
uthash_free((head)->hh.tbl->buckets,                                   \
HASH_INITIAL_NUM_BUCKETS*sizeof(struct UT_hash_bucket));           \
uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                    \
}                                                                        \
)                                                                          \
}                                                                            \
}                                                                              \
} while (0)
#define HASH_REPLACE_BYHASHVALUE_INORDER(hh,head,fieldname,keylen_in,hashval,add,replaced,cmpfcn) \
do {                                                                             \
(replaced) = NULL;                                                             \
HASH_FIND_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, replaced); \
if (replaced) {                                                                \
HASH_DELETE(hh, head, replaced);                                             \
}                                                                              \
HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh, head, &((add)->fieldname), keylen_in, hashval, add, cmpfcn); \
} while (0)
#define HASH_REPLACE_BYHASHVALUE(hh,head,fieldname,keylen_in,hashval,add,replaced) \
do {                                                                             \
(replaced) = NULL;                                                             \
HASH_FIND_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, replaced); \
if (replaced) {                                                                \
HASH_DELETE(hh, head, replaced);                                             \
}                                                                              \
HASH_ADD_KEYPTR_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, add); \
} while (0)
#define HASH_REPLACE(hh,head,fieldname,keylen_in,add,replaced)                   \
do {                                                                             \
unsigned _hr_hashv;                                                            \
HASH_VALUE(&((add)->fieldname), keylen_in, _hr_hashv);                         \
HASH_REPLACE_BYHASHVALUE(hh, head, fieldname, keylen_in, _hr_hashv, add, replaced); \
} while (0)
#define HASH_REPLACE_INORDER(hh,head,fieldname,keylen_in,add,replaced,cmpfcn)    \
do {                                                                             \
unsigned _hr_hashv;                                                            \
HASH_VALUE(&((add)->fieldname), keylen_in, _hr_hashv);                         \
HASH_REPLACE_BYHASHVALUE_INORDER(hh, head, fieldname, keylen_in, _hr_hashv, add, replaced, cmpfcn); \
} while (0)
#define HASH_APPEND_LIST(hh, head, add)                                          \
do {                                                                             \
(add)->hh.next = NULL;                                                         \
(add)->hh.prev = ELMT_FROM_HH((head)->hh.tbl, (head)->hh.tbl->tail);           \
(head)->hh.tbl->tail->next = (add);                                            \
(head)->hh.tbl->tail = &((add)->hh);                                           \
} while (0)
#define HASH_AKBI_INNER_LOOP(hh,head,add,cmpfcn)                                 \
do {                                                                             \
do {                                                                           \
if (cmpfcn(DECLTYPE(head)(_hs_iter), add) > 0) {                             \
break;                                                                     \
}                                                                            \
} while ((_hs_iter = HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->next));           \
} while (0)
#ifdef NO_DECLTYPE
#undef HASH_AKBI_INNER_LOOP
#define HASH_AKBI_INNER_LOOP(hh,head,add,cmpfcn)                                 \
do {                                                                             \
char *_hs_saved_head = (char*)(head);                                          \
do {                                                                           \
DECLTYPE_ASSIGN(head, _hs_iter);                                             \
if (cmpfcn(head, add) > 0) {                                                 \
DECLTYPE_ASSIGN(head, _hs_saved_head);                                     \
break;                                                                     \
}                                                                            \
DECLTYPE_ASSIGN(head, _hs_saved_head);                                       \
} while ((_hs_iter = HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->next));           \
} while (0)
#endif
#if HASH_NONFATAL_OOM
#define HASH_ADD_TO_TABLE(hh,head,keyptr,keylen_in,hashval,add,oomed)            \
do {                                                                             \
if (!(oomed)) {                                                                \
unsigned _ha_bkt;                                                            \
(head)->hh.tbl->num_items++;                                                 \
HASH_TO_BKT(hashval, (head)->hh.tbl->num_buckets, _ha_bkt);                  \
HASH_ADD_TO_BKT((head)->hh.tbl->buckets[_ha_bkt], hh, &(add)->hh, oomed);    \
if (oomed) {                                                                 \
HASH_ROLLBACK_BKT(hh, head, &(add)->hh);                                   \
HASH_DELETE_HH(hh, head, &(add)->hh);                                      \
(add)->hh.tbl = NULL;                                                      \
uthash_nonfatal_oom(add);                                                  \
} else {                                                                     \
HASH_BLOOM_ADD((head)->hh.tbl, hashval);                                   \
HASH_EMIT_KEY(hh, head, keyptr, keylen_in);                                \
}                                                                            \
} else {                                                                       \
(add)->hh.tbl = NULL;                                                        \
uthash_nonfatal_oom(add);                                                    \
}                                                                              \
} while (0)
#else
#define HASH_ADD_TO_TABLE(hh,head,keyptr,keylen_in,hashval,add,oomed)            \
do {                                                                             \
unsigned _ha_bkt;                                                              \
(head)->hh.tbl->num_items++;                                                   \
HASH_TO_BKT(hashval, (head)->hh.tbl->num_buckets, _ha_bkt);                    \
HASH_ADD_TO_BKT((head)->hh.tbl->buckets[_ha_bkt], hh, &(add)->hh, oomed);      \
HASH_BLOOM_ADD((head)->hh.tbl, hashval);                                       \
HASH_EMIT_KEY(hh, head, keyptr, keylen_in);                                    \
} while (0)
#endif
#define HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh,head,keyptr,keylen_in,hashval,add,cmpfcn) \
do {                                                                             \
IF_HASH_NONFATAL_OOM( int _ha_oomed = 0; )                                     \
(add)->hh.hashv = (hashval);                                                   \
(add)->hh.key = (char*) (keyptr);                                              \
(add)->hh.keylen = (unsigned) (keylen_in);                                     \
if (!(head)) {                                                                 \
(add)->hh.next = NULL;                                                       \
(add)->hh.prev = NULL;                                                       \
HASH_MAKE_TABLE(hh, add, _ha_oomed);                                         \
IF_HASH_NONFATAL_OOM( if (!_ha_oomed) { )                                    \
(head) = (add);                                                            \
IF_HASH_NONFATAL_OOM( } )                                                    \
} else {                                                                       \
void *_hs_iter = (head);                                                     \
(add)->hh.tbl = (head)->hh.tbl;                                              \
HASH_AKBI_INNER_LOOP(hh, head, add, cmpfcn);                                 \
if (_hs_iter) {                                                              \
(add)->hh.next = _hs_iter;                                                 \
if (((add)->hh.prev = HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->prev)) {     \
HH_FROM_ELMT((head)->hh.tbl, (add)->hh.prev)->next = (add);              \
} else {                                                                   \
(head) = (add);                                                          \
}                                                                          \
HH_FROM_ELMT((head)->hh.tbl, _hs_iter)->prev = (add);                      \
} else {                                                                     \
HASH_APPEND_LIST(hh, head, add);                                           \
}                                                                            \
}                                                                              \
HASH_ADD_TO_TABLE(hh, head, keyptr, keylen_in, hashval, add, _ha_oomed);       \
HASH_FSCK(hh, head, "HASH_ADD_KEYPTR_BYHASHVALUE_INORDER");                    \
} while (0)
#define HASH_ADD_KEYPTR_INORDER(hh,head,keyptr,keylen_in,add,cmpfcn)             \
do {                                                                             \
unsigned _hs_hashv;                                                            \
HASH_VALUE(keyptr, keylen_in, _hs_hashv);                                      \
HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh, head, keyptr, keylen_in, _hs_hashv, add, cmpfcn); \
} while (0)
#define HASH_ADD_BYHASHVALUE_INORDER(hh,head,fieldname,keylen_in,hashval,add,cmpfcn) \
HASH_ADD_KEYPTR_BYHASHVALUE_INORDER(hh, head, &((add)->fieldname), keylen_in, hashval, add, cmpfcn)
#define HASH_ADD_INORDER(hh,head,fieldname,keylen_in,add,cmpfcn)                 \
HASH_ADD_KEYPTR_INORDER(hh, head, &((add)->fieldname), keylen_in, add, cmpfcn)
#define HASH_ADD_KEYPTR_BYHASHVALUE(hh,head,keyptr,keylen_in,hashval,add)        \
do {                                                                             \
IF_HASH_NONFATAL_OOM( int _ha_oomed = 0; )                                     \
(add)->hh.hashv = (hashval);                                                   \
(add)->hh.key = (char*) (keyptr);                                              \
(add)->hh.keylen = (unsigned) (keylen_in);                                     \
if (!(head)) {                                                                 \
(add)->hh.next = NULL;                                                       \
(add)->hh.prev = NULL;                                                       \
HASH_MAKE_TABLE(hh, add, _ha_oomed);                                         \
IF_HASH_NONFATAL_OOM( if (!_ha_oomed) { )                                    \
(head) = (add);                                                            \
IF_HASH_NONFATAL_OOM( } )                                                    \
} else {                                                                       \
(add)->hh.tbl = (head)->hh.tbl;                                              \
HASH_APPEND_LIST(hh, head, add);                                             \
}                                                                              \
HASH_ADD_TO_TABLE(hh, head, keyptr, keylen_in, hashval, add, _ha_oomed);       \
HASH_FSCK(hh, head, "HASH_ADD_KEYPTR_BYHASHVALUE");                            \
} while (0)
#define HASH_ADD_KEYPTR(hh,head,keyptr,keylen_in,add)                            \
do {                                                                             \
unsigned _ha_hashv;                                                            \
HASH_VALUE(keyptr, keylen_in, _ha_hashv);                                      \
HASH_ADD_KEYPTR_BYHASHVALUE(hh, head, keyptr, keylen_in, _ha_hashv, add);      \
} while (0)
#define HASH_ADD_BYHASHVALUE(hh,head,fieldname,keylen_in,hashval,add)            \
HASH_ADD_KEYPTR_BYHASHVALUE(hh, head, &((add)->fieldname), keylen_in, hashval, add)
#define HASH_ADD(hh,head,fieldname,keylen_in,add)                                \
HASH_ADD_KEYPTR(hh, head, &((add)->fieldname), keylen_in, add)
#define HASH_TO_BKT(hashv,num_bkts,bkt)                                          \
do {                                                                             \
bkt = ((hashv) & ((num_bkts) - 1U));                                           \
} while (0)
/* delete "delptr" from the hash table.
* "the usual" patch-up process for the app-order doubly-linked-list.
* The use of _hd_hh_del below deserves special explanation.
* These used to be expressed using (delptr) but that led to a bug
* if someone used the same symbol for the head and deletee, like
*  HASH_DELETE(hh,users,users);
* We want that to work, but by changing the head (users) below
* we were forfeiting our ability to further refer to the deletee (users)
* in the patch-up process. Solution: use scratch space to
* copy the deletee pointer, then the latter references are via that
* scratch pointer rather than through the repointed (users) symbol.
*/
#define HASH_DELETE(hh,head,delptr)                                              \
HASH_DELETE_HH(hh, head, &(delptr)->hh)
#define HASH_DELETE_HH(hh,head,delptrhh)                                         \
do {                                                                             \
struct UT_hash_handle *_hd_hh_del = (delptrhh);                                \
if ((_hd_hh_del->prev == NULL) && (_hd_hh_del->next == NULL)) {                \
HASH_BLOOM_FREE((head)->hh.tbl);                                             \
uthash_free((head)->hh.tbl->buckets,                                         \
(head)->hh.tbl->num_buckets * sizeof(struct UT_hash_bucket));    \
uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                          \
(head) = NULL;                                                               \
} else {                                                                       \
unsigned _hd_bkt;                                                            \
if (_hd_hh_del == (head)->hh.tbl->tail) {                                    \
(head)->hh.tbl->tail = HH_FROM_ELMT((head)->hh.tbl, _hd_hh_del->prev);     \
}                                                                            \
if (_hd_hh_del->prev != NULL) {                                              \
HH_FROM_ELMT((head)->hh.tbl, _hd_hh_del->prev)->next = _hd_hh_del->next;   \
} else {                                                                     \
DECLTYPE_ASSIGN(head, _hd_hh_del->next);                                   \
}                                                                            \
if (_hd_hh_del->next != NULL) {                                              \
HH_FROM_ELMT((head)->hh.tbl, _hd_hh_del->next)->prev = _hd_hh_del->prev;   \
}                                                                            \
HASH_TO_BKT(_hd_hh_del->hashv, (head)->hh.tbl->num_buckets, _hd_bkt);        \
HASH_DEL_IN_BKT((head)->hh.tbl->buckets[_hd_bkt], _hd_hh_del);               \
(head)->hh.tbl->num_items--;                                                 \
}                                                                              \
HASH_FSCK(hh, head, "HASH_DELETE_HH");                                         \
} while (0)
/* convenience forms of HASH_FIND/HASH_ADD/HASH_DEL */
#define HASH_FIND_STR(head,findstr,out)                                          \
HASH_FIND(hh,head,findstr,(unsigned)uthash_strlen(findstr),out)
#define HASH_ADD_STR(head,strfield,add)                                          \
HASH_ADD(hh,head,strfield[0],(unsigned)uthash_strlen(add->strfield),add)
#define HASH_REPLACE_STR(head,strfield,add,replaced)                             \
HASH_REPLACE(hh,head,strfield[0],(unsigned)uthash_strlen(add->strfield),add,replaced)
#define HASH_FIND_INT(head,findint,out)                                          \
HASH_FIND(hh,head,findint,sizeof(int),out)
#define HASH_ADD_INT(head,intfield,add)                                          \
HASH_ADD(hh,head,intfield,sizeof(int),add)
#define HASH_REPLACE_INT(head,intfield,add,replaced)                             \
HASH_REPLACE(hh,head,intfield,sizeof(int),add,replaced)
#define HASH_FIND_PTR(head,findptr,out)                                          \
HASH_FIND(hh,head,findptr,sizeof(void *),out)
#define HASH_ADD_PTR(head,ptrfield,add)                                          \
HASH_ADD(hh,head,ptrfield,sizeof(void *),add)
#define HASH_REPLACE_PTR(head,ptrfield,add,replaced)                             \
HASH_REPLACE(hh,head,ptrfield,sizeof(void *),add,replaced)
#define HASH_DEL(head,delptr)                                                    \
HASH_DELETE(hh,head,delptr)
/* HASH_FSCK checks hash integrity on every add/delete when HASH_DEBUG is defined.
* This is for uthash developer only; it compiles away if HASH_DEBUG isn't defined.
*/
#ifdef HASH_DEBUG
#define HASH_OOPS(...) do { halt(__VA_ARGS__); } while (0)
#define HASH_FSCK(hh,head,where)                                                 \
do {                                                                             \
struct UT_hash_handle *_thh;                                                   \
if (head) {                                                                    \
unsigned _bkt_i;                                                             \
unsigned _count = 0;                                                         \
char *_prev;                                                                 \
for (_bkt_i = 0; _bkt_i < (head)->hh.tbl->num_buckets; ++_bkt_i) {           \
unsigned _bkt_count = 0;                                                   \
_thh = (head)->hh.tbl->buckets[_bkt_i].hh_head;                            \
_prev = NULL;                                                              \
while (_thh) {                                                             \
if (_prev != (char*)(_thh->hh_prev)) {                                   \
HASH_OOPS("%s: invalid hh_prev %p, actual %p\n",                       \
(where), (void*)_thh->hh_prev, (void*)_prev);                      \
}                                                                        \
_bkt_count++;                                                            \
_prev = (char*)(_thh);                                                   \
_thh = _thh->hh_next;                                                    \
}                                                                          \
_count += _bkt_count;                                                      \
if ((head)->hh.tbl->buckets[_bkt_i].count !=  _bkt_count) {                \
HASH_OOPS("%s: invalid bucket count %u, actual %u\n",                    \
(where), (head)->hh.tbl->buckets[_bkt_i].count, _bkt_count);         \
}                                                                          \
}                                                                            \
if (_count != (head)->hh.tbl->num_items) {                                   \
HASH_OOPS("%s: invalid hh item count %u, actual %u\n",                     \
(where), (head)->hh.tbl->num_items, _count);                           \
}                                                                            \
_count = 0;                                                                  \
_prev = NULL;                                                                \
_thh =  &(head)->hh;                                                         \
while (_thh) {                                                               \
_count++;                                                                  \
if (_prev != (char*)_thh->prev) {                                          \
HASH_OOPS("%s: invalid prev %p, actual %p\n",                            \
(where), (void*)_thh->prev, (void*)_prev);                           \
}                                                                          \
_prev = (char*)ELMT_FROM_HH((head)->hh.tbl, _thh);                         \
_thh = (_thh->next ? HH_FROM_ELMT((head)->hh.tbl, _thh->next) : NULL);     \
}                                                                            \
if (_count != (head)->hh.tbl->num_items) {                                   \
HASH_OOPS("%s: invalid app item count %u, actual %u\n",                    \
(where), (head)->hh.tbl->num_items, _count);                           \
}                                                                            \
}                                                                              \
} while (0)
#else
#define HASH_FSCK(hh,head,where)
#endif
/* When compiled with -DHASH_EMIT_KEYS, length-prefixed keys are emitted to
* the descriptor to which this macro is defined for tuning the hash function.
* The app can #include <unistd.h> to get the prototype for write(2). */
#ifdef HASH_EMIT_KEYS
#define HASH_EMIT_KEY(hh,head,keyptr,fieldlen)                                   \
do {                                                                             \
unsigned _klen = fieldlen;                                                     \
write(HASH_EMIT_KEYS, &_klen, sizeof(_klen));                                  \
write(HASH_EMIT_KEYS, keyptr, (unsigned long)fieldlen);                        \
} while (0)
#else
#define HASH_EMIT_KEY(hh,head,keyptr,fieldlen)
#endif
/* default to Jenkin's hash unless overridden e.g. DHASH_FUNCTION=HASH_SAX */
#ifdef HASH_FUNCTION
#define HASH_FCN HASH_FUNCTION
#else
#define HASH_FCN HASH_JEN
#endif
/* The Bernstein hash function, used in Perl prior to v5.6. Note (x<<5+x)=x*33. */
#define HASH_BER(key,keylen,hashv)                                               \
do {                                                                             \
unsigned _hb_keylen = (unsigned)keylen;                                        \
const unsigned char *_hb_key = (const unsigned char*)(key);                    \
(hashv) = 0;                                                                   \
while (_hb_keylen-- != 0U) {                                                   \
(hashv) = (((hashv) << 5) + (hashv)) + *_hb_key++;                           \
}                                                                              \
} while (0)
/* SAX/FNV/OAT/JEN hash functions are macro variants of those listed at
* http://eternallyconfuzzled.com/tuts/algorithms/jsw_tut_hashing.aspx */
#define HASH_SAX(key,keylen,hashv)                                               \
do {                                                                             \
unsigned _sx_i;                                                                \
const unsigned char *_hs_key = (const unsigned char*)(key);                    \
hashv = 0;                                                                     \
for (_sx_i=0; _sx_i < keylen; _sx_i++) {                                       \
hashv ^= (hashv << 5) + (hashv >> 2) + _hs_key[_sx_i];                       \
}                                                                              \
} while (0)
/* FNV-1a variation */
#define HASH_FNV(key,keylen,hashv)                                               \
do {                                                                             \
unsigned _fn_i;                                                                \
const unsigned char *_hf_key = (const unsigned char*)(key);                    \
(hashv) = 2166136261U;                                                         \
for (_fn_i=0; _fn_i < keylen; _fn_i++) {                                       \
hashv = hashv ^ _hf_key[_fn_i];                                              \
hashv = hashv * 16777619U;                                                   \
}                                                                              \
} while (0)
#define HASH_OAT(key,keylen,hashv)                                               \
do {                                                                             \
unsigned _ho_i;                                                                \
const unsigned char *_ho_key=(const unsigned char*)(key);                      \
hashv = 0;                                                                     \
for(_ho_i=0; _ho_i < keylen; _ho_i++) {                                        \
hashv += _ho_key[_ho_i];                                                   \
hashv += (hashv << 10);                                                    \
hashv ^= (hashv >> 6);                                                     \
}                                                                              \
hashv += (hashv << 3);                                                         \
hashv ^= (hashv >> 11);                                                        \
hashv += (hashv << 15);                                                        \
} while (0)
#define HASH_JEN_MIX(a,b,c)                                                      \
do {                                                                             \
a -= b; a -= c; a ^= ( c >> 13 );                                              \
b -= c; b -= a; b ^= ( a << 8 );                                               \
c -= a; c -= b; c ^= ( b >> 13 );                                              \
a -= b; a -= c; a ^= ( c >> 12 );                                              \
b -= c; b -= a; b ^= ( a << 16 );                                              \
c -= a; c -= b; c ^= ( b >> 5 );                                               \
a -= b; a -= c; a ^= ( c >> 3 );                                               \
b -= c; b -= a; b ^= ( a << 10 );                                              \
c -= a; c -= b; c ^= ( b >> 15 );                                              \
} while (0)
#define HASH_JEN(key,keylen,hashv)                                               \
do {                                                                             \
unsigned _hj_i,_hj_j,_hj_k;                                                    \
unsigned const char *_hj_key=(unsigned const char*)(key);                      \
hashv = 0xfeedbeefu;                                                           \
_hj_i = _hj_j = 0x9e3779b9u;                                                   \
_hj_k = (unsigned)(keylen);                                                    \
while (_hj_k >= 12U) {                                                         \
_hj_i +=    (_hj_key[0] + ( (unsigned)_hj_key[1] << 8 )                      \
+ ( (unsigned)_hj_key[2] << 16 )                                         \
+ ( (unsigned)_hj_key[3] << 24 ) );                                      \
_hj_j +=    (_hj_key[4] + ( (unsigned)_hj_key[5] << 8 )                      \
+ ( (unsigned)_hj_key[6] << 16 )                                         \
+ ( (unsigned)_hj_key[7] << 24 ) );                                      \
hashv += (_hj_key[8] + ( (unsigned)_hj_key[9] << 8 )                         \
+ ( (unsigned)_hj_key[10] << 16 )                                        \
+ ( (unsigned)_hj_key[11] << 24 ) );                                     \
\
HASH_JEN_MIX(_hj_i, _hj_j, hashv);                                          \
\
_hj_key += 12;                                                              \
_hj_k -= 12U;                                                               \
}                                                                              \
hashv += (unsigned)(keylen);                                                   \
switch ( _hj_k ) {                                                             \
case 11: hashv += ( (unsigned)_hj_key[10] << 24 ); /* FALLTHROUGH */         \
case 10: hashv += ( (unsigned)_hj_key[9] << 16 );  /* FALLTHROUGH */         \
case 9:  hashv += ( (unsigned)_hj_key[8] << 8 );   /* FALLTHROUGH */         \
case 8:  _hj_j += ( (unsigned)_hj_key[7] << 24 );  /* FALLTHROUGH */         \
case 7:  _hj_j += ( (unsigned)_hj_key[6] << 16 );  /* FALLTHROUGH */         \
case 6:  _hj_j += ( (unsigned)_hj_key[5] << 8 );   /* FALLTHROUGH */         \
case 5:  _hj_j += _hj_key[4];                      /* FALLTHROUGH */         \
case 4:  _hj_i += ( (unsigned)_hj_key[3] << 24 );  /* FALLTHROUGH */         \
case 3:  _hj_i += ( (unsigned)_hj_key[2] << 16 );  /* FALLTHROUGH */         \
case 2:  _hj_i += ( (unsigned)_hj_key[1] << 8 );   /* FALLTHROUGH */         \
case 1:  _hj_i += _hj_key[0];                                                \
}                                                                              \
HASH_JEN_MIX(_hj_i, _hj_j, hashv);                                             \
} while (0)
/* The Paul Hsieh hash function */
#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__)             \
|| defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif
#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)             \
+(uint32_t)(((const uint8_t *)(d))[0]) )
#endif
#define HASH_SFH(key,keylen,hashv)                                               \
do {                                                                             \
unsigned const char *_sfh_key=(unsigned const char*)(key);                     \
uint32_t _sfh_tmp, _sfh_len = (uint32_t)keylen;                                \
\
unsigned _sfh_rem = _sfh_len & 3U;                                             \
_sfh_len >>= 2;                                                                \
hashv = 0xcafebabeu;                                                           \
\
/* Main loop */                                                                \
for (;_sfh_len > 0U; _sfh_len--) {                                             \
hashv    += get16bits (_sfh_key);                                            \
_sfh_tmp  = ((uint32_t)(get16bits (_sfh_key+2)) << 11) ^ hashv;              \
hashv     = (hashv << 16) ^ _sfh_tmp;                                        \
_sfh_key += 2U*sizeof (uint16_t);                                            \
hashv    += hashv >> 11;                                                     \
}                                                                              \
\
/* Handle end cases */                                                         \
switch (_sfh_rem) {                                                            \
case 3: hashv += get16bits (_sfh_key);                                       \
hashv ^= hashv << 16;                                                \
hashv ^= (uint32_t)(_sfh_key[sizeof (uint16_t)]) << 18;              \
hashv += hashv >> 11;                                                \
break;                                                               \
case 2: hashv += get16bits (_sfh_key);                                       \
hashv ^= hashv << 11;                                                \
hashv += hashv >> 17;                                                \
break;                                                               \
case 1: hashv += *_sfh_key;                                                  \
hashv ^= hashv << 10;                                                \
hashv += hashv >> 1;                                                 \
}                                                                              \
\
/* Force "avalanching" of final 127 bits */                                    \
hashv ^= hashv << 3;                                                           \
hashv += hashv >> 5;                                                           \
hashv ^= hashv << 4;                                                           \
hashv += hashv >> 17;                                                          \
hashv ^= hashv << 25;                                                          \
hashv += hashv >> 6;                                                           \
} while (0)
#ifdef HASH_USING_NO_STRICT_ALIASING
/* The MurmurHash exploits some CPU's (x86,x86_64) tolerance for unaligned reads.
* For other types of CPU's (e.g. Sparc) an unaligned read causes a bus error.
* MurmurHash uses the faster approach only on CPU's where we know it's safe.
*
* Note the preprocessor built-in defines can be emitted using:
*
*   gcc -m64 -dM -E - < /dev/null                  (on gcc)
*   cc -## a.c (where a.c is a simple test file)   (Sun Studio)
*/
#if (defined(__i386__) || defined(__x86_64__)  || defined(_M_IX86))
#define MUR_GETBLOCK(p,i) p[i]
#else /* non intel */
#define MUR_PLUS0_ALIGNED(p) (((unsigned long)p & 3UL) == 0UL)
#define MUR_PLUS1_ALIGNED(p) (((unsigned long)p & 3UL) == 1UL)
#define MUR_PLUS2_ALIGNED(p) (((unsigned long)p & 3UL) == 2UL)
#define MUR_PLUS3_ALIGNED(p) (((unsigned long)p & 3UL) == 3UL)
#define WP(p) ((uint32_t*)((unsigned long)(p) & ~3UL))
#if (defined(__BIG_ENDIAN__) || defined(SPARC) || defined(__ppc__) || defined(__ppc64__))
#define MUR_THREE_ONE(p) ((((*WP(p))&0x00ffffff) << 8) | (((*(WP(p)+1))&0xff000000) >> 24))
#define MUR_TWO_TWO(p)   ((((*WP(p))&0x0000ffff) <<16) | (((*(WP(p)+1))&0xffff0000) >> 16))
#define MUR_ONE_THREE(p) ((((*WP(p))&0x000000ff) <<24) | (((*(WP(p)+1))&0xffffff00) >>  8))
#else /* assume little endian non-intel */
#define MUR_THREE_ONE(p) ((((*WP(p))&0xffffff00) >> 8) | (((*(WP(p)+1))&0x000000ff) << 24))
#define MUR_TWO_TWO(p)   ((((*WP(p))&0xffff0000) >>16) | (((*(WP(p)+1))&0x0000ffff) << 16))
#define MUR_ONE_THREE(p) ((((*WP(p))&0xff000000) >>24) | (((*(WP(p)+1))&0x00ffffff) <<  8))
#endif
#define MUR_GETBLOCK(p,i) (MUR_PLUS0_ALIGNED(p) ? ((p)[i]) :           \
(MUR_PLUS1_ALIGNED(p) ? MUR_THREE_ONE(p) : \
(MUR_PLUS2_ALIGNED(p) ? MUR_TWO_TWO(p) :  \
MUR_ONE_THREE(p))))
#endif
#define MUR_ROTL32(x,r) (((x) << (r)) | ((x) >> (32 - (r))))
#define MUR_FMIX(_h) \
do {                 \
_h ^= _h >> 16;    \
_h *= 0x85ebca6bu; \
_h ^= _h >> 13;    \
_h *= 0xc2b2ae35u; \
_h ^= _h >> 16;    \
} while (0)
#define HASH_MUR(key,keylen,hashv)                                     \
do {                                                                   \
const uint8_t *_mur_data = (const uint8_t*)(key);                    \
const int _mur_nblocks = (int)(keylen) / 4;                          \
uint32_t _mur_h1 = 0xf88D5353u;                                      \
uint32_t _mur_c1 = 0xcc9e2d51u;                                      \
uint32_t _mur_c2 = 0x1b873593u;                                      \
uint32_t _mur_k1 = 0;                                                \
const uint8_t *_mur_tail;                                            \
const uint32_t *_mur_blocks = (const uint32_t*)(_mur_data+(_mur_nblocks*4)); \
int _mur_i;                                                          \
for (_mur_i = -_mur_nblocks; _mur_i != 0; _mur_i++) {                \
_mur_k1 = MUR_GETBLOCK(_mur_blocks,_mur_i);                        \
_mur_k1 *= _mur_c1;                                                \
_mur_k1 = MUR_ROTL32(_mur_k1,15);                                  \
_mur_k1 *= _mur_c2;                                                \
\
_mur_h1 ^= _mur_k1;                                                \
_mur_h1 = MUR_ROTL32(_mur_h1,13);                                  \
_mur_h1 = (_mur_h1*5U) + 0xe6546b64u;                              \
}                                                                    \
_mur_tail = (const uint8_t*)(_mur_data + (_mur_nblocks*4));          \
_mur_k1=0;                                                           \
switch ((keylen) & 3U) {                                             \
case 0: break;                                                     \
case 3: _mur_k1 ^= (uint32_t)_mur_tail[2] << 16; /* FALLTHROUGH */ \
case 2: _mur_k1 ^= (uint32_t)_mur_tail[1] << 8;  /* FALLTHROUGH */ \
case 1: _mur_k1 ^= (uint32_t)_mur_tail[0];                         \
_mur_k1 *= _mur_c1;                                                \
_mur_k1 = MUR_ROTL32(_mur_k1,15);                                  \
_mur_k1 *= _mur_c2;                                                \
_mur_h1 ^= _mur_k1;                                                \
}                                                                    \
_mur_h1 ^= (uint32_t)(keylen);                                       \
MUR_FMIX(_mur_h1);                                                   \
hashv = _mur_h1;                                                     \
} while (0)
#endif  /* HASH_USING_NO_STRICT_ALIASING */
/* iterate over items in a known bucket to find desired item */
#define HASH_FIND_IN_BKT(tbl,hh,head,keyptr,keylen_in,hashval,out)               \
do {                                                                             \
if ((head).hh_head != NULL) {                                                  \
DECLTYPE_ASSIGN(out, ELMT_FROM_HH(tbl, (head).hh_head));                     \
} else {                                                                       \
(out) = NULL;                                                                \
}                                                                              \
while ((out) != NULL) {                                                        \
if ((out)->hh.hashv == (hashval) && (out)->hh.keylen == (keylen_in)) {       \
if (uthash_memcmp((out)->hh.key, keyptr, keylen_in) == 0) {                \
break;                                                                   \
}                                                                          \
}                                                                            \
if ((out)->hh.hh_next != NULL) {                                             \
DECLTYPE_ASSIGN(out, ELMT_FROM_HH(tbl, (out)->hh.hh_next));                \
} else {                                                                     \
(out) = NULL;                                                              \
}                                                                            \
}                                                                              \
} while (0)
/* add an item to a bucket  */
#define HASH_ADD_TO_BKT(head,hh,addhh,oomed)                                     \
do {                                                                             \
UT_hash_bucket *_ha_head = &(head);                                            \
_ha_head->count++;                                                             \
(addhh)->hh_next = _ha_head->hh_head;                                          \
(addhh)->hh_prev = NULL;                                                       \
if (_ha_head->hh_head != NULL) {                                               \
_ha_head->hh_head->hh_prev = (addhh);                                        \
}                                                                              \
_ha_head->hh_head = (addhh);                                                   \
if ((_ha_head->count >= ((_ha_head->expand_mult + 1U) * HASH_BKT_CAPACITY_THRESH)) \
&& !(addhh)->tbl->noexpand) {                                              \
HASH_EXPAND_BUCKETS(addhh,(addhh)->tbl, oomed);                              \
IF_HASH_NONFATAL_OOM(                                                        \
if (oomed) {                                                               \
HASH_DEL_IN_BKT(head,addhh);                                             \
}                                                                          \
)                                                                            \
}                                                                              \
} while (0)
/* remove an item from a given bucket */
#define HASH_DEL_IN_BKT(head,delhh)                                              \
do {                                                                             \
UT_hash_bucket *_hd_head = &(head);                                            \
_hd_head->count--;                                                             \
if (_hd_head->hh_head == (delhh)) {                                            \
_hd_head->hh_head = (delhh)->hh_next;                                        \
}                                                                              \
if ((delhh)->hh_prev) {                                                        \
(delhh)->hh_prev->hh_next = (delhh)->hh_next;                                \
}                                                                              \
if ((delhh)->hh_next) {                                                        \
(delhh)->hh_next->hh_prev = (delhh)->hh_prev;                                \
}                                                                              \
} while (0)
/* Bucket expansion has the effect of doubling the number of buckets
* and redistributing the items into the new buckets. Ideally the
* items will distribute more or less evenly into the new buckets
* (the extent to which this is true is a measure of the quality of
* the hash function as it applies to the key domain).
*
* With the items distributed into more buckets, the chain length
* (item count) in each bucket is reduced. Thus by expanding buckets
* the hash keeps a bound on the chain length. This bounded chain
* length is the essence of how a hash provides constant time lookup.
*
* The calculation of tbl->ideal_chain_maxlen below deserves some
* explanation. First, keep in mind that we're calculating the ideal
* maximum chain length based on the *new* (doubled) bucket count.
* In fractions this is just n/b (n=number of items,b=new num buckets).
* Since the ideal chain length is an integer, we want to calculate
* ceil(n/b). We don't depend on floating point arithmetic in this
* hash, so to calculate ceil(n/b) with integers we could write
*
*      ceil(n/b) = (n/b) + ((n%b)?1:0)
*
* and in fact a previous version of this hash did just that.
* But now we have improved things a bit by recognizing that b is
* always a power of two. We keep its base 2 log handy (call it lb),
* so now we can write this with a bit shift and logical AND:
*
*      ceil(n/b) = (n>>lb) + ( (n & (b-1)) ? 1:0)
*
*/
#define HASH_EXPAND_BUCKETS(hh,tbl,oomed)                                        \
do {                                                                             \
unsigned _he_bkt;                                                              \
unsigned _he_bkt_i;                                                            \
struct UT_hash_handle *_he_thh, *_he_hh_nxt;                                   \
UT_hash_bucket *_he_new_buckets, *_he_newbkt;                                  \
_he_new_buckets = (UT_hash_bucket*)uthash_malloc(                              \
2UL * (tbl)->num_buckets * sizeof(struct UT_hash_bucket));            \
if (!_he_new_buckets) {                                                        \
HASH_RECORD_OOM(oomed);                                                      \
} else {                                                                       \
uthash_bzero(_he_new_buckets,                                                \
2UL * (tbl)->num_buckets * sizeof(struct UT_hash_bucket));               \
(tbl)->ideal_chain_maxlen =                                                  \
((tbl)->num_items >> ((tbl)->log2_num_buckets+1U)) +                      \
((((tbl)->num_items & (((tbl)->num_buckets*2U)-1U)) != 0U) ? 1U : 0U);    \
(tbl)->nonideal_items = 0;                                                   \
for (_he_bkt_i = 0; _he_bkt_i < (tbl)->num_buckets; _he_bkt_i++) {           \
_he_thh = (tbl)->buckets[ _he_bkt_i ].hh_head;                             \
while (_he_thh != NULL) {                                                  \
_he_hh_nxt = _he_thh->hh_next;                                           \
HASH_TO_BKT(_he_thh->hashv, (tbl)->num_buckets * 2U, _he_bkt);           \
_he_newbkt = &(_he_new_buckets[_he_bkt]);                                \
if (++(_he_newbkt->count) > (tbl)->ideal_chain_maxlen) {                 \
(tbl)->nonideal_items++;                                               \
_he_newbkt->expand_mult = _he_newbkt->count / (tbl)->ideal_chain_maxlen; \
}                                                                        \
_he_thh->hh_prev = NULL;                                                 \
_he_thh->hh_next = _he_newbkt->hh_head;                                  \
if (_he_newbkt->hh_head != NULL) {                                       \
_he_newbkt->hh_head->hh_prev = _he_thh;                                \
}                                                                        \
_he_newbkt->hh_head = _he_thh;                                           \
_he_thh = _he_hh_nxt;                                                    \
}                                                                          \
}                                                                            \
uthash_free((tbl)->buckets, (tbl)->num_buckets * sizeof(struct UT_hash_bucket)); \
(tbl)->num_buckets *= 2U;                                                    \
(tbl)->log2_num_buckets++;                                                   \
(tbl)->buckets = _he_new_buckets;                                            \
(tbl)->ineff_expands = ((tbl)->nonideal_items > ((tbl)->num_items >> 1)) ?   \
((tbl)->ineff_expands+1U) : 0U;                                          \
if ((tbl)->ineff_expands > 1U) {                                             \
(tbl)->noexpand = 1;                                                       \
uthash_noexpand_fyi(tbl);                                                  \
}                                                                            \
uthash_expand_fyi(tbl);                                                      \
}                                                                              \
} while (0)
/* This is an adaptation of Simon Tatham's O(n log(n)) mergesort */
/* Note that HASH_SORT assumes the hash handle name to be hh.
* HASH_SRT was added to allow the hash handle name to be passed in. */
#define HASH_SORT(head,cmpfcn) HASH_SRT(hh,head,cmpfcn)
#define HASH_SRT(hh,head,cmpfcn)                                                 \
do {                                                                             \
unsigned _hs_i;                                                                \
unsigned _hs_looping,_hs_nmerges,_hs_insize,_hs_psize,_hs_qsize;               \
struct UT_hash_handle *_hs_p, *_hs_q, *_hs_e, *_hs_list, *_hs_tail;            \
if (head != NULL) {                                                            \
_hs_insize = 1;                                                              \
_hs_looping = 1;                                                             \
_hs_list = &((head)->hh);                                                    \
while (_hs_looping != 0U) {                                                  \
_hs_p = _hs_list;                                                          \
_hs_list = NULL;                                                           \
_hs_tail = NULL;                                                           \
_hs_nmerges = 0;                                                           \
while (_hs_p != NULL) {                                                    \
_hs_nmerges++;                                                           \
_hs_q = _hs_p;                                                           \
_hs_psize = 0;                                                           \
for (_hs_i = 0; _hs_i < _hs_insize; ++_hs_i) {                           \
_hs_psize++;                                                           \
_hs_q = ((_hs_q->next != NULL) ?                                       \
HH_FROM_ELMT((head)->hh.tbl, _hs_q->next) : NULL);                   \
if (_hs_q == NULL) {                                                   \
break;                                                               \
}                                                                      \
}                                                                        \
_hs_qsize = _hs_insize;                                                  \
while ((_hs_psize != 0U) || ((_hs_qsize != 0U) && (_hs_q != NULL))) {    \
if (_hs_psize == 0U) {                                                 \
_hs_e = _hs_q;                                                       \
_hs_q = ((_hs_q->next != NULL) ?                                     \
HH_FROM_ELMT((head)->hh.tbl, _hs_q->next) : NULL);                 \
_hs_qsize--;                                                         \
} else if ((_hs_qsize == 0U) || (_hs_q == NULL)) {                     \
_hs_e = _hs_p;                                                       \
if (_hs_p != NULL) {                                                 \
_hs_p = ((_hs_p->next != NULL) ?                                   \
HH_FROM_ELMT((head)->hh.tbl, _hs_p->next) : NULL);               \
}                                                                    \
_hs_psize--;                                                         \
} else if ((cmpfcn(                                                    \
DECLTYPE(head)(ELMT_FROM_HH((head)->hh.tbl, _hs_p)),             \
DECLTYPE(head)(ELMT_FROM_HH((head)->hh.tbl, _hs_q))              \
)) <= 0) {                                                       \
_hs_e = _hs_p;                                                       \
if (_hs_p != NULL) {                                                 \
_hs_p = ((_hs_p->next != NULL) ?                                   \
HH_FROM_ELMT((head)->hh.tbl, _hs_p->next) : NULL);               \
}                                                                    \
_hs_psize--;                                                         \
} else {                                                               \
_hs_e = _hs_q;                                                       \
_hs_q = ((_hs_q->next != NULL) ?                                     \
HH_FROM_ELMT((head)->hh.tbl, _hs_q->next) : NULL);                 \
_hs_qsize--;                                                         \
}                                                                      \
if ( _hs_tail != NULL ) {                                              \
_hs_tail->next = ((_hs_e != NULL) ?                                  \
ELMT_FROM_HH((head)->hh.tbl, _hs_e) : NULL);                       \
} else {                                                               \
_hs_list = _hs_e;                                                    \
}                                                                      \
if (_hs_e != NULL) {                                                   \
_hs_e->prev = ((_hs_tail != NULL) ?                                  \
ELMT_FROM_HH((head)->hh.tbl, _hs_tail) : NULL);                    \
}                                                                      \
_hs_tail = _hs_e;                                                      \
}                                                                        \
_hs_p = _hs_q;                                                           \
}                                                                          \
if (_hs_tail != NULL) {                                                    \
_hs_tail->next = NULL;                                                   \
}                                                                          \
if (_hs_nmerges <= 1U) {                                                   \
_hs_looping = 0;                                                         \
(head)->hh.tbl->tail = _hs_tail;                                         \
DECLTYPE_ASSIGN(head, ELMT_FROM_HH((head)->hh.tbl, _hs_list));           \
}                                                                          \
_hs_insize *= 2U;                                                          \
}                                                                            \
HASH_FSCK(hh, head, "HASH_SRT");                                             \
}                                                                              \
} while (0)
/* This function selects items from one hash into another hash.
* The end result is that the selected items have dual presence
* in both hashes. There is no copy of the items made; rather
* they are added into the new hash through a secondary hash
* hash handle that must be present in the structure. */
#define HASH_SELECT(hh_dst, dst, hh_src, src, cond)                              \
do {                                                                             \
unsigned _src_bkt, _dst_bkt;                                                   \
void *_last_elt = NULL, *_elt;                                                 \
UT_hash_handle *_src_hh, *_dst_hh, *_last_elt_hh=NULL;                         \
ptrdiff_t _dst_hho = ((char*)(&(dst)->hh_dst) - (char*)(dst));                 \
if ((src) != NULL) {                                                           \
for (_src_bkt=0; _src_bkt < (src)->hh_src.tbl->num_buckets; _src_bkt++) {    \
for (_src_hh = (src)->hh_src.tbl->buckets[_src_bkt].hh_head;               \
_src_hh != NULL;                                                         \
_src_hh = _src_hh->hh_next) {                                            \
_elt = ELMT_FROM_HH((src)->hh_src.tbl, _src_hh);                         \
if (cond(_elt)) {                                                        \
IF_HASH_NONFATAL_OOM( int _hs_oomed = 0; )                             \
_dst_hh = (UT_hash_handle*)(((char*)_elt) + _dst_hho);                 \
_dst_hh->key = _src_hh->key;                                           \
_dst_hh->keylen = _src_hh->keylen;                                     \
_dst_hh->hashv = _src_hh->hashv;                                       \
_dst_hh->prev = _last_elt;                                             \
_dst_hh->next = NULL;                                                  \
if (_last_elt_hh != NULL) {                                            \
_last_elt_hh->next = _elt;                                           \
}                                                                      \
if ((dst) == NULL) {                                                   \
DECLTYPE_ASSIGN(dst, _elt);                                          \
HASH_MAKE_TABLE(hh_dst, dst, _hs_oomed);                             \
IF_HASH_NONFATAL_OOM(                                                \
if (_hs_oomed) {                                                   \
uthash_nonfatal_oom(_elt);                                       \
(dst) = NULL;                                                    \
continue;                                                        \
}                                                                  \
)                                                                    \
} else {                                                               \
_dst_hh->tbl = (dst)->hh_dst.tbl;                                    \
}                                                                      \
HASH_TO_BKT(_dst_hh->hashv, _dst_hh->tbl->num_buckets, _dst_bkt);      \
HASH_ADD_TO_BKT(_dst_hh->tbl->buckets[_dst_bkt], hh_dst, _dst_hh, _hs_oomed); \
(dst)->hh_dst.tbl->num_items++;                                        \
IF_HASH_NONFATAL_OOM(                                                  \
if (_hs_oomed) {                                                     \
HASH_ROLLBACK_BKT(hh_dst, dst, _dst_hh);                           \
HASH_DELETE_HH(hh_dst, dst, _dst_hh);                              \
_dst_hh->tbl = NULL;                                               \
uthash_nonfatal_oom(_elt);                                         \
continue;                                                          \
}                                                                    \
)                                                                      \
HASH_BLOOM_ADD(_dst_hh->tbl, _dst_hh->hashv);                          \
_last_elt = _elt;                                                      \
_last_elt_hh = _dst_hh;                                                \
}                                                                        \
}                                                                          \
}                                                                            \
}                                                                              \
HASH_FSCK(hh_dst, dst, "HASH_SELECT");                                         \
} while (0)
#define HASH_CLEAR(hh,head)                                                      \
do {                                                                             \
if ((head) != NULL) {                                                          \
HASH_BLOOM_FREE((head)->hh.tbl);                                             \
uthash_free((head)->hh.tbl->buckets,                                         \
(head)->hh.tbl->num_buckets*sizeof(struct UT_hash_bucket));      \
uthash_free((head)->hh.tbl, sizeof(UT_hash_table));                          \
(head) = NULL;                                                               \
}                                                                              \
} while (0)
#define HASH_OVERHEAD(hh,head)                                                   \
(((head) != NULL) ? (                                                           \
(size_t)(((head)->hh.tbl->num_items   * sizeof(UT_hash_handle))   +             \
((head)->hh.tbl->num_buckets * sizeof(UT_hash_bucket))   +             \
sizeof(UT_hash_table)                                   +             \
(HASH_BLOOM_BYTELEN))) : 0U)
#ifdef NO_DECLTYPE
#define HASH_ITER(hh,head,el,tmp)                                                \
for(((el)=(head)), ((*(char**)(&(tmp)))=(char*)((head!=NULL)?(head)->hh.next:NULL)); \
(el) != NULL; ((el)=(tmp)), ((*(char**)(&(tmp)))=(char*)((tmp!=NULL)?(tmp)->hh.next:NULL)))
#else
#define HASH_ITER(hh,head,el,tmp)                                                \
for(((el)=(head)), ((tmp)=DECLTYPE(el)((head!=NULL)?(head)->hh.next:NULL));      \
(el) != NULL; ((el)=(tmp)), ((tmp)=DECLTYPE(el)((tmp!=NULL)?(tmp)->hh.next:NULL)))
#endif
/* obtain a count of items in the hash */
#define HASH_COUNT(head) HASH_CNT(hh,head)
#define HASH_CNT(hh,head) ((head != NULL)?((head)->hh.tbl->num_items):0U)
typedef struct UT_hash_bucket {
struct UT_hash_handle *hh_head;
unsigned count;
/* expand_mult is normally set to 0. In this situation, the max chain length
* threshold is enforced at its default value, HASH_BKT_CAPACITY_THRESH. (If
* the bucket's chain exceeds this length, bucket expansion is triggered).
* However, setting expand_mult to a non-zero value delays bucket expansion
* (that would be triggered by additions to this particular bucket)
* until its chain length reaches a *multiple* of HASH_BKT_CAPACITY_THRESH.
* (The multiplier is simply expand_mult+1). The whole idea of this
* multiplier is to reduce bucket expansions, since they are expensive, in
* situations where we know that a particular bucket tends to be overused.
* It is better to let its chain length grow to a longer yet-still-bounded
* value, than to do an O(n) bucket expansion too often.
*/
unsigned expand_mult;
} UT_hash_bucket;
/* random signature used only to find hash tables in external analysis */
#define HASH_SIGNATURE 0xa0111fe1u
#define HASH_BLOOM_SIGNATURE 0xb12220f2u
typedef struct UT_hash_table {
UT_hash_bucket *buckets;
unsigned num_buckets, log2_num_buckets;
unsigned num_items;
struct UT_hash_handle *tail; /* tail hh in app order, for fast append    */
ptrdiff_t hho; /* hash handle offset (byte pos of hash handle in element */
/* in an ideal situation (all buckets used equally), no bucket would have
* more than ceil(#items/#buckets) items. that's the ideal chain length. */
unsigned ideal_chain_maxlen;
/* nonideal_items is the number of items in the hash whose chain position
* exceeds the ideal chain maxlen. these items pay the penalty for an uneven
* hash distribution; reaching them in a chain traversal takes >ideal steps */
unsigned nonideal_items;
/* ineffective expands occur when a bucket doubling was performed, but
* afterward, more than half the items in the hash had nonideal chain
* positions. If this happens on two consecutive expansions we inhibit any
* further expansion, as it's not helping; this happens when the hash
* function isn't a good fit for the key domain. When expansion is inhibited
* the hash will still work, albeit no longer in constant time. */
unsigned ineff_expands, noexpand;
uint32_t signature; /* used only to find hash tables in external analysis */
#ifdef HASH_BLOOM
uint32_t bloom_sig; /* used only to test bloom exists in external analysis */
uint8_t *bloom_bv;
uint8_t bloom_nbits;
#endif
} UT_hash_table;
typedef struct UT_hash_handle {
struct UT_hash_table *tbl;
void *prev;                       /* prev element in app order      */
void *next;                       /* next element in app order      */
struct UT_hash_handle *hh_prev;   /* previous hh in bucket order    */
struct UT_hash_handle *hh_next;   /* next hh in bucket order        */
void *key;                        /* ptr to enclosing struct's key  */
unsigned keylen;                  /* enclosing struct's key len     */
unsigned hashv;                   /* result of hash-fcn(key)        */
} UT_hash_handle;
typedef struct vector_td vector_t;
typedef struct vertex_attribute_td vertex_attribute_t;
typedef struct vertex_buffer_td vertex_buffer_t;
typedef struct td_int32_option int32_option;
struct td_int32_option {
    bool isEmpty;
    int32_t value;
};
const int32_option int32_empty = { true };

typedef struct td_uint32_option uint32_option;
struct td_uint32_option {
    bool isEmpty;
    uint32_t value;
};
const uint32_option uint32_empty = { true };

typedef struct td_int64_option int64_option;
struct td_int64_option {
    bool isEmpty;
    int64_t value;
};
const int64_option int64_empty = { true };

typedef struct td_uint64_option uint64_option;
struct td_uint64_option {
    bool isEmpty;
    uint64_t value;
};
const uint64_option uint64_empty = { true };

typedef struct td_void_option void_option;
struct td_void_option {
    bool isEmpty;
    void* value;
};
const void_option void_empty = { true };

typedef struct td_char_option char_option;
struct td_char_option {
    bool isEmpty;
    char value;
};
const char_option char_empty = { true };

typedef struct td_float_option float_option;
struct td_float_option {
    bool isEmpty;
    float value;
};
const float_option float_empty = { true };

typedef struct td_double_option double_option;
struct td_double_option {
    bool isEmpty;
    double value;
};
const double_option double_empty = { true };

const char* sjg_string1 = "shaders/v3f-c4f.vert";
const char* sjg_string10 = "shaders/v3f-n3f-phong.frag";
const char* sjg_string11 = "shaders/v3f-t2f-n3f-phong.vert";
const char* sjg_string12 = "shaders/v3f-t2f-n3f-phong.frag";
const char* sjg_string13 = "shaders/v3f-t2f-c4f.vert";
const char* sjg_string14 = "shaders/v3f-t2f-c4f.frag";
const char* sjg_string15 = "vertex:3f,tex_coord:2f,normal:3f";
const char* sjg_string16 = "assets/clouds.png";
const char* sjg_string18 = "leaf";
const char* sjg_string19 = "assets/whitestar1.png";
const char* sjg_string2 = "shaders/v3f-c4f.frag";
const char* sjg_string20 = "assets/whitestar2.png";
const char* sjg_string21 = "assets/whitestar1.png";
const char* sjg_string22 = "assets/whitestar2.png";
const char* sjg_string23 = "assets/whitestar1.png";
const char* sjg_string24 = "assets/whitestar2.png";
const char* sjg_string25 = "assets/whitestar1.png";
const char* sjg_string26 = "assets/whitestar2.png";
const char* sjg_string27 = "grass6.2";
const char* sjg_string28 = "assets/grass.png";
const char* sjg_string29 = "grass6.2";
const char* sjg_string3 = "shaders/v3f-t2f-c4f.vert";
const char* sjg_string30 = "assets/grass.png";
const char* sjg_string31 = "grass4.2";
const char* sjg_string32 = "assets/grass.png";
const char* sjg_string33 = "grass4.2";
const char* sjg_string34 = "assets/grass.png";
const char* sjg_string35 = "grass2.2";
const char* sjg_string36 = "assets/grass.png";
const char* sjg_string37 = "grass2.2";
const char* sjg_string38 = "assets/grass.png";
const char* sjg_string39 = "grass0.2";
const char* sjg_string4 = "shaders/blur-horizontal.frag";
const char* sjg_string40 = "assets/grass.png";
const char* sjg_string41 = "grass0.2";
const char* sjg_string42 = "assets/grass.png";
const char* sjg_string43 = "grass-1.8";
const char* sjg_string44 = "assets/grass.png";
const char* sjg_string45 = "grass-1.8";
const char* sjg_string46 = "assets/grass.png";
const char* sjg_string5 = "shaders/v3f-t2f-c4f.vert";
const char* sjg_string6 = "shaders/blur-vertical.frag";
const char* sjg_string7 = "shaders/v3f-t2f.vert";
const char* sjg_string8 = "shaders/v3f-t2f.frag";
const char* sjg_string9 = "shaders/v3f-n3f-phong.vert";
const char* sjg_string91 = "viewModel";
const char* sjg_string92 = "normalMat";
const char* sjg_string93 = "projection";
const char* sjg_string94 = "lightPos";
const char* sjg_string95 = "diffuseColor";
const char* sjg_string96 = "specColor";

typedef struct pointer_td pointer;
struct pointer_td {
    void* ptr;
    int refCount;
    UT_hash_handle hh;
};
pointer* g_pointers = 0;
typedef struct {
    float x, y, z;    // position
    float r, g, b, a; // color
} vertex3_color4_t;	
typedef struct GLid_td GLid_s;
struct GLid_td {
    GLuint id;
    int refCount;
    UT_hash_handle hh;
};
GLid_s* g_GLids = 0;
typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
} vertex3_texture2_t;	
typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
} vertex3_texture2_color3_t;	
/**
* Tuple of 4 ints.
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>r</b>, <b>red</b> or <b>vstart</b>
*  - Second component: <b>y</b>, <b>g</b>, <b>green</b> or <b>vcount</b>
*  - Third component:  <b>z</b>, <b>b</b>, <b>blue</b>, <b>width</b> or <b>istart</b>
*  - Fourth component: <b>w</b>, <b>a</b>, <b>alpha</b>, <b>height</b> or <b>icount</b>
*
*/
typedef union
{
    int data[4];    /**< All compoments at once     */
    struct {
        int x;      /**< Alias for first component  */
        int y;      /**< Alias for second component */
        int z;      /**< Alias for third component  */
        int w;      /**< Alias for fourht component */
    };
    struct {
        int x_;     /**< Alias for first component  */
        int y_;     /**< Alias for second component */
        int width;  /**< Alias for third component  */
        int height; /**< Alias for fourth component */
    };
    struct {
        int r;      /**< Alias for first component  */
        int g;      /**< Alias for second component */
        int b;      /**< Alias for third component  */
        int a;      /**< Alias for fourth component */
    };
    struct {
        int red;    /**< Alias for first component  */
        int green;  /**< Alias for second component */
        int blue;   /**< Alias for third component  */
        int alpha;  /**< Alias for fourth component */
    };
    struct {
        int vstart; /**< Alias for first component  */
        int vcount; /**< Alias for second component */
        int istart; /**< Alias for third component  */
        int icount; /**< Alias for fourth component */
    };
} ivec4;
/**
* Tuple of 3 ints.
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>r</b> or <b>red</b>
*  - Second component: <b>y</b>, <b>g</b> or <b>green</b>
*  - Third component:  <b>z</b>, <b>b</b> or <b>blue</b>
*
*/
typedef union
{
    int data[3];    /**< All compoments at once     */
    struct {
        int x;      /**< Alias for first component  */
        int y;      /**< Alias for second component */
        int z;      /**< Alias for third component  */
    };
    struct {
        int r;      /**< Alias for first component  */
        int g;      /**< Alias for second component */
        int b;      /**< Alias for third component  */
    };
    struct {
        int red;    /**< Alias for first component  */
        int green;  /**< Alias for second component */
        int blue;   /**< Alias for third component  */
    };
} ivec3;
/**
* Tuple of 2 ints.
*
* Each field can be addressed using several aliases:
*  - First component: <b>x</b>, <b>s</b> or <b>start</b>
*  - Second component: <b>y</b>, <b>t</b> or <b>end</b>
*
*/
typedef union
{
    int data[2];    /**< All compoments at once     */
    struct {
        int x;      /**< Alias for first component  */
        int y;      /**< Alias for second component */
    };
    struct {
        int s;      /**< Alias for first component  */
        int t;      /**< Alias for second component */
    };
    struct {
        int start;  /**< Alias for first component  */
        int end;    /**< Alias for second component */
    };
} ivec2;
/**
* Tuple of 4 floats.
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>left</b>, <b>r</b> or <b>red</b>
*  - Second component: <b>y</b>, <b>top</b>, <b>g</b> or <b>green</b>
*  - Third component:  <b>z</b>, <b>width</b>, <b>b</b> or <b>blue</b>
*  - Fourth component: <b>w</b>, <b>height</b>, <b>a</b> or <b>alpha</b>
*/
typedef union
{
    float data[4];    /**< All compoments at once    */
    struct {
        float x;      /**< Alias for first component */
        float y;      /**< Alias for second component */
        float z;      /**< Alias for third component  */
        float w;      /**< Alias for fourth component */
    };
    struct {
        float left;   /**< Alias for first component */
        float top;    /**< Alias for second component */
        float width;  /**< Alias for third component  */
        float height; /**< Alias for fourth component */
    };
    struct {
        float r;      /**< Alias for first component */
        float g;      /**< Alias for second component */
        float b;      /**< Alias for third component  */
        float a;      /**< Alias for fourth component */
    };
    struct {
        float red;    /**< Alias for first component */
        float green;  /**< Alias for second component */
        float blue;   /**< Alias for third component  */
        float alpha;  /**< Alias for fourth component */
    };
} vec4;
/**
* Tuple of 3 floats
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b>, <b>r</b> or <b>red</b>
*  - Second component: <b>y</b>, <b>g</b> or <b>green</b>
*  - Third component:  <b>z</b>, <b>b</b> or <b>blue</b>
*/
typedef union
{
    float data[3];   /**< All compoments at once    */
    struct {
        float x;     /**< Alias for first component */
        float y;     /**< Alias fo second component */
        float z;     /**< Alias fo third component  */
    };
    struct {
        float r;     /**< Alias for first component */
        float g;     /**< Alias fo second component */
        float b;     /**< Alias fo third component  */
    };
    struct {
        float red;   /**< Alias for first component */
        float green; /**< Alias fo second component */
        float blue;  /**< Alias fo third component  */
    };
} vec3;
/**
* Tuple of 2 floats
*
* Each field can be addressed using several aliases:
*  - First component:  <b>x</b> or <b>s</b>
*  - Second component: <b>y</b> or <b>t</b>
*/
typedef union
{
    float data[2]; /**< All components at once     */
    struct {
        float x;   /**< Alias for first component  */
        float y;   /**< Alias for second component */
    };
    struct {
        float s;   /**< Alias for first component  */
        float t;   /**< Alias for second component */
    };
} vec2;
/**
* A texture atlas is used to pack several small regions into a single texture.
*/
typedef struct texture_atlas_t
{
    /**
    * Allocated nodes
    */
    vector_t * nodes;
    /**
    *  Width (in pixels) of the underlying texture
    */
    size_t width;
    /**
    * Height (in pixels) of the underlying texture
    */
    size_t height;
    /**
    * Depth (in bytes) of the underlying texture
    */
    size_t depth;
    /**
    * Allocated surface size
    */
    size_t used;
    /**
    * Texture identity (OpenGL)
    */
    unsigned int id;
    /**
    * Atlas data
    */
    unsigned char * data;
} texture_atlas_t;    
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };
const struct {
    int          code;
    const char*  message;
} FT_Errors[] =
#include FT_ERRORS_H    
/**
* A list of possible ways to render a glyph.
*/
typedef enum rendermode_t
{
    RENDER_NORMAL,
    RENDER_OUTLINE_EDGE,
    RENDER_OUTLINE_POSITIVE,
    RENDER_OUTLINE_NEGATIVE,
    RENDER_SIGNED_DISTANCE_FIELD
} rendermode_t;
/**
* A structure that hold a kerning value relatively to a Unicode
* codepoint.
*
* This structure cannot be used alone since the (necessary) right
* Unicode codepoint is implicitely held by the owner of this structure.
*/
typedef struct kerning_t
{
    /**
    * Left Unicode codepoint in the kern pair in UTF-32 LE encoding.
    */
    uint32_t codepoint;
    /**
    * Kerning value (in fractional pixels).
    */
    float kerning;
} kerning_t;
/*
* Glyph metrics:
* --------------
*
*                       xmin                     xmax
*                        |                         |
*                        |<-------- width -------->|
*                        |                         |
*              |         +-------------------------+----------------- ymax
*              |         |    ggggggggg   ggggg    |     ^        ^
*              |         |   g:::::::::ggg::::g    |     |        |
*              |         |  g:::::::::::::::::g    |     |        |
*              |         | g::::::ggggg::::::gg    |     |        |
*              |         | g:::::g     g:::::g     |     |        |
*    offset_x -|-------->| g:::::g     g:::::g     |  offset_y    |
*              |         | g:::::g     g:::::g     |     |        |
*              |         | g::::::g    g:::::g     |     |        |
*              |         | g:::::::ggggg:::::g     |     |        |
*              |         |  g::::::::::::::::g     |     |      height
*              |         |   gg::::::::::::::g     |     |        |
*  baseline ---*---------|---- gggggggg::::::g-----*--------      |
*            / |         |             g:::::g     |              |
*     origin   |         | gggggg      g:::::g     |              |
*              |         | g:::::gg   gg:::::g     |              |
*              |         |  g::::::ggg:::::::g     |              |
*              |         |   gg:::::::::::::g      |              |
*              |         |     ggg::::::ggg        |              |
*              |         |         gggggg          |              v
*              |         +-------------------------+----------------- ymin
*              |                                   |
*              |------------- advance_x ---------->|
*/
/**
* A structure that describe a glyph.
*/
typedef struct texture_glyph_t
{
    /**
    * Unicode codepoint this glyph represents in UTF-32 LE encoding.
    */
    uint32_t codepoint;
    /**
    * Glyph's width in pixels.
    */
    size_t width;
    /**
    * Glyph's height in pixels.
    */
    size_t height;
    /**
    * Glyph's left bearing expressed in integer pixels.
    */
    int offset_x;
    /**
    * Glyphs's top bearing expressed in integer pixels.
    *
    * Remember that this is the distance from the baseline to the top-most
    * glyph scanline, upwards y coordinates being positive.
    */
    int offset_y;
    /**
    * For horizontal text layouts, this is the horizontal distance (in
    * fractional pixels) used to increment the pen position when the glyph is
    * drawn as part of a string of text.
    */
    float advance_x;
    /**
    * For vertical text layouts, this is the vertical distance (in fractional
    * pixels) used to increment the pen position when the glyph is drawn as
    * part of a string of text.
    */
    float advance_y;
    /**
    * First normalized texture coordinate (x) of top-left corner
    */
    float s0;
    /**
    * Second normalized texture coordinate (y) of top-left corner
    */
    float t0;
    /**
    * First normalized texture coordinate (x) of bottom-right corner
    */
    float s1;
    /**
    * Second normalized texture coordinate (y) of bottom-right corner
    */
    float t1;
    /**
    * A vector of kerning pairs relative to this glyph.
    */
    vector_t * kerning;
    /**
    * Mode this glyph was rendered
    */
    rendermode_t rendermode;
    /**
    * Glyph outline thickness
    */
    float outline_thickness;
} texture_glyph_t;
typedef struct texture_atlas_t texture_atlas_td; 
/**
*  Texture font structure.
*/
typedef struct texture_font_t
{
    /**
    * Vector of glyphs contained in this font.
    */
    vector_t * glyphs;
    /**
    * Atlas structure to store glyphs data.
    */
    texture_atlas_td * atlas;
    /**
    * font location
    */
    enum {
        TEXTURE_FONT_FILE = 0,
        TEXTURE_FONT_MEMORY,
    } location;
    union {
        /**
        * Font filename, for when location == TEXTURE_FONT_FILE
        */
        char *filename;
        /**
        * Font memory address, for when location == TEXTURE_FONT_MEMORY
        */
        struct {
            const void *base;
            size_t size;
        } memory;
    };
    /**
    * Font size
    */
    float size;
    /**
    * Whether to use autohint when rendering font
    */
    int hinting;
    /**
    * Mode the font is rendering its next glyph
    */
    rendermode_t rendermode;
    /**
    * Outline thickness
    */
    float outline_thickness;
    /**
    * Whether to use our own lcd filter.
    */
    int filtering;
    /**
    * LCD filter weights
    */
    unsigned char lcd_weights[5];
    /**
    * Whether to use kerning if available
    */
    int kerning;
    /**
    * This field is simply used to compute a default line spacing (i.e., the
    * baseline-to-baseline distance) when writing text with this font. Note
    * that it usually is larger than the sum of the ascender and descender
    * taken as absolute values. There is also no guarantee that no glyphs
    * extend above or below subsequent baselines when using this distance.
    */
    float height;
    /**
    * This field is the distance that must be placed between two lines of
    * text. The baseline-to-baseline distance should be computed as:
    * ascender - descender + linegap
    */
    float linegap;
    /**
    * The ascender is the vertical distance from the horizontal baseline to
    * the highest 'character' coordinate in a font face. Unfortunately, font
    * formats define the ascender differently. For some, it represents the
    * ascent of all capital latin characters (without accents), for others it
    * is the ascent of the highest accented character, and finally, other
    * formats define it as being equal to bbox.yMax.
    */
    float ascender;
    /**
    * The descender is the vertical distance from the horizontal baseline to
    * the lowest 'character' coordinate in a font face. Unfortunately, font
    * formats define the descender differently. For some, it represents the
    * descent of all capital latin characters (without accents), for others it
    * is the ascent of the lowest accented character, and finally, other
    * formats define it as being equal to bbox.yMin. This field is negative
    * for values below the baseline.
    */
    float descender;
    /**
    * The position of the underline line for this face. It is the center of
    * the underlining stem. Only relevant for scalable formats.
    */
    float underline_position;
    /**
    * The thickness of the underline for this face. Only relevant for scalable
    * formats.
    */
    float underline_thickness;
} texture_font_t;
/**
*  Generic vector structure.
*
* @memberof vector
*/
struct vector_td
{
    /** Pointer to dynamically allocated items. */
    void * items;
    /** Number of items that can be held in currently allocated storage. */
    size_t capacity;
    /** Number of items. */
    size_t size;
    /** Size (in bytes) of a single item. */
    size_t item_size;
};
/**
*  Generic vertex attribute.
*/
struct vertex_attribute_td
{
    /**
    *  atribute name
    */
    GLchar * name;
    /**
    * index of the generic vertex attribute to be modified.
    */
    GLuint index;
    /**
    * Number of components per generic vertex attribute.
    *
    * Must be 1, 2, 3, or 4. The initial value is 4.
    */
    GLint size;
    /**
    *  data type of each component in the array.
    *
    *  Symbolic constants GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT,
    *  GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT, GL_FLOAT, or GL_DOUBLE are
    *  accepted. The initial value is GL_FLOAT.
    */
    GLenum type;
    /**
    *  whether fixed-point data values should be normalized (GL_TRUE) or
    *  converted directly as fixed-point values (GL_FALSE) when they are
    *  accessed.
    */
    GLboolean normalized;
    /**
    *  byte offset between consecutive generic vertex attributes.
    *
    *  If stride is 0, the generic vertex attributes are understood to be
    *  tightly packed in the array. The initial value is 0.
    */
    GLsizei stride;
    /**
    *  pointer to the first component of the first attribute element in the
    *  array.
    */
    GLvoid * pointer;
    /**
    * pointer to the function that enable this attribute.
    */
    void ( * enable )(void *);
};
/**
* Generic vertex buffer.
*/
struct vertex_buffer_td
{
    /** Format of the vertex buffer. */
    char * format;
    /** Vector of vertices. */
    vector_t * vertices;
    #ifdef FREETYPE_GL_USE_VAO
    /** GL identity of the Vertex Array Object */
    GLuint VAO_id;
    #endif
    /** GL identity of the vertices buffer. */
    GLuint vertices_id;
    /** Vector of indices. */
    vector_t * indices;
    /** GL identity of the indices buffer. */
    GLuint indices_id;
    /** Current size of the vertices buffer in GPU */
    size_t GPU_vsize;
    /** Current size of the indices buffer in GPU*/
    size_t GPU_isize;
    /** GL primitives to render. */
    GLenum mode;
    /** Whether the vertex buffer needs to be uploaded to GPU memory. */
    char state;
    /** Individual items */
    vector_t * items;
    /** Array of attributes. */
    vertex_attribute_t *attributes[MAX_VERTEX_ATTRIBUTE];
};
#define sjs_object_typeId 1
#define sjs_windowRenderer_typeId 2
#define sjs_windowRenderer_heap_typeId 3
#define sjs_size_typeId 4
#define sjs_size_heap_typeId 5
#define sjs_mat4_typeId 6
#define sjs_mat4_heap_typeId 7
#define sjs_scene2d_typeId 8
#define sjs_scene2d_heap_typeId 9
#define sjs_anon1_typeId 10
#define sjs_anon1_heap_typeId 11
#define sjs_array_heap_animation_typeId 12
#define sjs_array_heap_animation_heap_typeId 13
#define sjs_list_heap_animation_typeId 14
#define sjs_list_heap_animation_heap_typeId 15
#define sjs_anon2_typeId 16
#define sjs_anon2_heap_typeId 17
#define sji_anon2_animation_typeId 18
#define sjs_anon3_typeId 19
#define sjs_anon3_heap_typeId 20
#define sjs_anon4_typeId 21
#define sjs_anon4_heap_typeId 22
#define sjs_anon5_typeId 23
#define sjs_anon5_heap_typeId 24
#define sjs_array_char_typeId 25
#define sjs_array_char_heap_typeId 26
#define sjs_string_typeId 27
#define sjs_string_heap_typeId 28
#define sjs_shader_typeId 29
#define sjs_shader_heap_typeId 30
#define sjs_anon6_typeId 31
#define sjs_anon6_heap_typeId 32
#define sjs_array_heap_element_typeId 33
#define sjs_array_heap_element_heap_typeId 34
#define sjs_rect_typeId 35
#define sjs_rect_heap_typeId 36
#define sjs_fillElement_typeId 37
#define sjs_fillElement_heap_typeId 38
#define sjs_point_typeId 39
#define sjs_point_heap_typeId 40
#define sji_element_typeId 41
#define sjs_array_heap_model_typeId 42
#define sjs_array_heap_model_heap_typeId 43
#define sjs_vec3_typeId 44
#define sjs_vec3_heap_typeId 45
#define sjs_color_typeId 46
#define sjs_color_heap_typeId 47
#define sjs_light_typeId 48
#define sjs_light_heap_typeId 49
#define sjs_nauScene3dElement_typeId 50
#define sjs_nauScene3dElement_heap_typeId 51
#define sji_nauScene3dElement_model_typeId 52
#define sjs_list_heap_model_typeId 53
#define sjs_list_heap_model_heap_typeId 54
#define cb_heap_model_heap_model_i32_typeId 55
#define cb_heap_model_heap_model_i32_heap_typeId 56
#define sjs_array_i32_typeId 57
#define sjs_array_i32_heap_typeId 58
#define sjs_array_vertex_location_texture_normal_typeId 59
#define sjs_array_vertex_location_texture_normal_heap_typeId 60
#define sjs_vertexBuffer_vertex_location_texture_normal_typeId 61
#define sjs_vertexBuffer_vertex_location_texture_normal_heap_typeId 62
#define sjs_texture_typeId 63
#define sjs_texture_heap_typeId 64
#define sjs_model_typeId 65
#define sjs_model_heap_typeId 66
#define sjs_vec4_typeId 67
#define sjs_vec4_heap_typeId 68
#define sjs_vec2_typeId 69
#define sjs_vec2_heap_typeId 70
#define sjs_vertex_location_texture_normal_typeId 71
#define sjs_vertex_location_texture_normal_heap_typeId 72
#define sjs_array_texture_typeId 73
#define sjs_array_texture_heap_typeId 74
#define sjs_leafPanel_typeId 75
#define sjs_leafPanel_heap_typeId 76
#define cb_texture_heap_model_typeId 77
#define cb_texture_heap_model_heap_typeId 78
#define sjs_panel3d_typeId 79
#define sjs_panel3d_heap_typeId 80
#define sjs_boxRenderer_typeId 81
#define sjs_boxRenderer_heap_typeId 82
#define sjs_crossHairsElement_typeId 83
#define sjs_crossHairsElement_heap_typeId 84

typedef struct td_sjs_object sjs_object;
typedef struct td_sjs_windowRenderer sjs_windowRenderer;
typedef struct td_sjs_windowRenderer_heap sjs_windowRenderer_heap;
typedef struct td_sjs_size sjs_size;
typedef struct td_sjs_size_heap sjs_size_heap;
typedef struct td_sjs_mat4 sjs_mat4;
typedef struct td_sjs_mat4_heap sjs_mat4_heap;
typedef struct td_sjs_scene2d sjs_scene2d;
typedef struct td_sjs_scene2d_heap sjs_scene2d_heap;
typedef struct td_sjs_anon1 sjs_anon1;
typedef struct td_sjs_anon1_heap sjs_anon1_heap;
typedef struct td_sjs_array_heap_animation sjs_array_heap_animation;
typedef struct td_sjs_array_heap_animation_heap sjs_array_heap_animation_heap;
typedef struct td_sjs_list_heap_animation sjs_list_heap_animation;
typedef struct td_sjs_list_heap_animation_heap sjs_list_heap_animation_heap;
typedef struct td_sjs_anon2 sjs_anon2;
typedef struct td_sjs_anon2_heap sjs_anon2_heap;
typedef struct td_sji_anon2_animation sji_anon2_animation;
typedef struct td_sjs_anon3 sjs_anon3;
typedef struct td_sjs_anon3_heap sjs_anon3_heap;
typedef struct td_sjs_anon4 sjs_anon4;
typedef struct td_sjs_anon4_heap sjs_anon4_heap;
typedef struct td_sjs_anon5 sjs_anon5;
typedef struct td_sjs_anon5_heap sjs_anon5_heap;
typedef struct td_sjs_array_char sjs_array_char;
typedef struct td_sjs_array_char_heap sjs_array_char_heap;
typedef struct td_sjs_string sjs_string;
typedef struct td_sjs_string_heap sjs_string_heap;
typedef struct td_sjs_shader sjs_shader;
typedef struct td_sjs_shader_heap sjs_shader_heap;
typedef struct td_sjs_anon6 sjs_anon6;
typedef struct td_sjs_anon6_heap sjs_anon6_heap;
typedef struct td_sjs_array_heap_element sjs_array_heap_element;
typedef struct td_sjs_array_heap_element_heap sjs_array_heap_element_heap;
typedef struct td_sjs_rect sjs_rect;
typedef struct td_sjs_rect_heap sjs_rect_heap;
typedef struct td_sjs_fillElement sjs_fillElement;
typedef struct td_sjs_fillElement_heap sjs_fillElement_heap;
typedef struct td_sjs_point sjs_point;
typedef struct td_sjs_point_heap sjs_point_heap;
typedef struct td_sji_element sji_element;
typedef struct td_sjs_array_heap_model sjs_array_heap_model;
typedef struct td_sjs_array_heap_model_heap sjs_array_heap_model_heap;
typedef struct td_sjs_vec3 sjs_vec3;
typedef struct td_sjs_vec3_heap sjs_vec3_heap;
typedef struct td_sjs_color sjs_color;
typedef struct td_sjs_color_heap sjs_color_heap;
typedef struct td_sjs_light sjs_light;
typedef struct td_sjs_light_heap sjs_light_heap;
typedef struct td_sjs_nauScene3dElement sjs_nauScene3dElement;
typedef struct td_sjs_nauScene3dElement_heap sjs_nauScene3dElement_heap;
typedef struct td_sji_nauScene3dElement_model sji_nauScene3dElement_model;
typedef struct td_sjs_list_heap_model sjs_list_heap_model;
typedef struct td_sjs_list_heap_model_heap sjs_list_heap_model_heap;
typedef struct td_cb_heap_model_heap_model_i32 cb_heap_model_heap_model_i32;
typedef struct td_cb_heap_model_heap_model_i32_heap cb_heap_model_heap_model_i32_heap;
typedef struct td_sjs_array_i32 sjs_array_i32;
typedef struct td_sjs_array_i32_heap sjs_array_i32_heap;
typedef struct td_sjs_array_vertex_location_texture_normal sjs_array_vertex_location_texture_normal;
typedef struct td_sjs_array_vertex_location_texture_normal_heap sjs_array_vertex_location_texture_normal_heap;
typedef struct td_sjs_vertexBuffer_vertex_location_texture_normal sjs_vertexBuffer_vertex_location_texture_normal;
typedef struct td_sjs_vertexBuffer_vertex_location_texture_normal_heap sjs_vertexBuffer_vertex_location_texture_normal_heap;
typedef struct td_sjs_texture sjs_texture;
typedef struct td_sjs_texture_heap sjs_texture_heap;
typedef struct td_sjs_model sjs_model;
typedef struct td_sjs_model_heap sjs_model_heap;
typedef struct td_sjs_vec4 sjs_vec4;
typedef struct td_sjs_vec4_heap sjs_vec4_heap;
typedef struct td_sjs_vec2 sjs_vec2;
typedef struct td_sjs_vec2_heap sjs_vec2_heap;
typedef struct td_sjs_vertex_location_texture_normal sjs_vertex_location_texture_normal;
typedef struct td_sjs_vertex_location_texture_normal_heap sjs_vertex_location_texture_normal_heap;
typedef struct td_sjs_array_texture sjs_array_texture;
typedef struct td_sjs_array_texture_heap sjs_array_texture_heap;
typedef struct td_sjs_leafPanel sjs_leafPanel;
typedef struct td_sjs_leafPanel_heap sjs_leafPanel_heap;
typedef struct td_cb_texture_heap_model cb_texture_heap_model;
typedef struct td_cb_texture_heap_model_heap cb_texture_heap_model_heap;
typedef struct td_sjs_panel3d sjs_panel3d;
typedef struct td_sjs_panel3d_heap sjs_panel3d_heap;
typedef struct td_sjs_boxRenderer sjs_boxRenderer;
typedef struct td_sjs_boxRenderer_heap sjs_boxRenderer_heap;
typedef struct td_sjs_crossHairsElement sjs_crossHairsElement;
typedef struct td_sjs_crossHairsElement_heap sjs_crossHairsElement_heap;

struct td_sjs_object {
    intptr_t _refCount;
};

struct td_sjs_windowRenderer {
    SDL_Window* win;
    SDL_Renderer* ren;
    int structsNeedAValue;
};

struct td_sjs_windowRenderer_heap {
    intptr_t _refCount;
    SDL_Window* win;
    SDL_Renderer* ren;
};

struct td_sjs_size {
    int32_t w;
    int32_t h;
};

struct td_sjs_size_heap {
    intptr_t _refCount;
    int32_t w;
    int32_t h;
};

struct td_sjs_mat4 {
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float m30;
    float m31;
    float m32;
    float m33;
};

struct td_sjs_mat4_heap {
    intptr_t _refCount;
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float m30;
    float m31;
    float m32;
    float m33;
};

struct td_sjs_scene2d {
    sjs_size _size;
    sjs_mat4 model;
    sjs_mat4 view;
    sjs_mat4 projection;
};

struct td_sjs_scene2d_heap {
    intptr_t _refCount;
    sjs_size _size;
    sjs_mat4 model;
    sjs_mat4 view;
    sjs_mat4 projection;
};

struct td_sjs_anon1 {
    int structsNeedAValue;
};

struct td_sjs_anon1_heap {
    intptr_t _refCount;
};

struct td_sjs_array_heap_animation {
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_heap_animation_heap {
    intptr_t _refCount;
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_list_heap_animation {
    sjs_array_heap_animation array;
};

struct td_sjs_list_heap_animation_heap {
    intptr_t _refCount;
    sjs_array_heap_animation array;
};

struct td_sjs_anon2 {
    sjs_list_heap_animation animations;
    int32_t current;
};

struct td_sjs_anon2_heap {
    intptr_t _refCount;
    sjs_list_heap_animation animations;
    int32_t current;
};

struct td_sji_anon2_animation {
    intptr_t _refCount;
    sjs_object* _parent;
    void (*destroy)(void* _this);
    sjs_object* (*asInterface)(sjs_object* _this, int typeId);
    void (*nextFrame)(void* _parent, int32_t time, bool* _return);
};

struct td_sjs_anon3 {
    int32_t fill;
    int32_t left;
    int32_t right;
    int32_t top;
    int32_t bottom;
};

struct td_sjs_anon3_heap {
    intptr_t _refCount;
    int32_t fill;
    int32_t left;
    int32_t right;
    int32_t top;
    int32_t bottom;
};

struct td_sjs_anon4 {
    int32_t normal;
    int32_t hot;
    int32_t pressed;
};

struct td_sjs_anon4_heap {
    intptr_t _refCount;
    int32_t normal;
    int32_t hot;
    int32_t pressed;
};

struct td_sjs_anon5 {
    int structsNeedAValue;
};

struct td_sjs_anon5_heap {
    intptr_t _refCount;
};

struct td_sjs_array_char {
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_char_heap {
    intptr_t _refCount;
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_string {
    int32_t count;
    sjs_array_char data;
};

struct td_sjs_string_heap {
    intptr_t _refCount;
    int32_t count;
    sjs_array_char data;
};

struct td_sjs_shader {
    sjs_string vertex;
    sjs_string pixel;
    GLuint id;
};

struct td_sjs_shader_heap {
    intptr_t _refCount;
    sjs_string vertex;
    sjs_string pixel;
    GLuint id;
};

struct td_sjs_anon6 {
    int structsNeedAValue;
};

struct td_sjs_anon6_heap {
    intptr_t _refCount;
};

struct td_sjs_array_heap_element {
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_heap_element_heap {
    intptr_t _refCount;
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_rect {
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
};

struct td_sjs_rect_heap {
    intptr_t _refCount;
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
};

struct td_sjs_fillElement {
    sjs_array_heap_element children;
    sjs_rect _rect;
};

struct td_sjs_fillElement_heap {
    intptr_t _refCount;
    sjs_array_heap_element children;
    sjs_rect _rect;
};

struct td_sjs_point {
    int32_t x;
    int32_t y;
};

struct td_sjs_point_heap {
    intptr_t _refCount;
    int32_t x;
    int32_t y;
};

struct td_sji_element {
    intptr_t _refCount;
    sjs_object* _parent;
    void (*destroy)(void* _this);
    sjs_object* (*asInterface)(sjs_object* _this, int typeId);
    void (*getSize)(void* _parent, sjs_size* maxSize, sjs_size* _return);
    void (*getSize_heap)(void* _parent, sjs_size* maxSize, sjs_size_heap** _return);
    void (*getRect)(void* _parent, sjs_rect** _return);
    void (*setRect)(void* _parent, sjs_rect* rect);
    void (*render)(void* _parent, sjs_scene2d* scene);
    void (*fireMouseEvent)(void* _parent, sjs_point* point, int32_t eventId);
};

struct td_sjs_array_heap_model {
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_heap_model_heap {
    intptr_t _refCount;
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_vec3 {
    float x;
    float y;
    float z;
};

struct td_sjs_vec3_heap {
    intptr_t _refCount;
    float x;
    float y;
    float z;
};

struct td_sjs_color {
    float r;
    float g;
    float b;
    float a;
};

struct td_sjs_color_heap {
    intptr_t _refCount;
    float r;
    float g;
    float b;
    float a;
};

struct td_sjs_light {
    sjs_vec3 pos;
    sjs_color diffuseColor;
    sjs_color specColor;
};

struct td_sjs_light_heap {
    intptr_t _refCount;
    sjs_vec3 pos;
    sjs_color diffuseColor;
    sjs_color specColor;
};

struct td_sjs_nauScene3dElement {
    sjs_array_heap_model children;
    sjs_vec3 lookAtMin;
    sjs_vec3 lookAtMax;
    float fieldOfView;
    float zNear;
    float zFar;
    sjs_light light;
    sjs_mat4 projection;
    sjs_mat4 view;
    sjs_mat4 world;
    sjs_rect _rect;
    bool _isDragging;
    sjs_point _startDrag;
    sjs_vec3 _lookAt;
    sjs_vec3 _lookAtDrag;
};

struct td_sjs_nauScene3dElement_heap {
    intptr_t _refCount;
    sjs_array_heap_model children;
    sjs_vec3 lookAtMin;
    sjs_vec3 lookAtMax;
    float fieldOfView;
    float zNear;
    float zFar;
    sjs_light light;
    sjs_mat4 projection;
    sjs_mat4 view;
    sjs_mat4 world;
    sjs_rect _rect;
    bool _isDragging;
    sjs_point _startDrag;
    sjs_vec3 _lookAt;
    sjs_vec3 _lookAtDrag;
};

struct td_sji_nauScene3dElement_model {
    intptr_t _refCount;
    sjs_object* _parent;
    void (*destroy)(void* _this);
    sjs_object* (*asInterface)(sjs_object* _this, int typeId);
    void (*update)(void* _parent, sjs_rect* sceneRect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light);
    void (*getZ)(void* _parent, float* _return);
    void (*renderOrQueue)(void* _parent, sjs_list_heap_model* zqueue);
    void (*render)(void* _parent);
    void (*fireMouseEvent)(void* _parent, sjs_point* point, int32_t eventId);
};

struct td_sjs_list_heap_model {
    sjs_array_heap_model array;
};

struct td_sjs_list_heap_model_heap {
    intptr_t _refCount;
    sjs_array_heap_model array;
};

struct td_cb_heap_model_heap_model_i32 {
    void* _parent;
    void (*_cb)(void* _parent, sji_nauScene3dElement_model*, sji_nauScene3dElement_model*, int32_t* _return);
};

struct td_cb_heap_model_heap_model_i32_heap {
    cb_heap_model_heap_model_i32 inner;
    void (*_destroy)(void*);
};

struct td_sjs_array_i32 {
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_i32_heap {
    intptr_t _refCount;
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_vertex_location_texture_normal {
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_vertex_location_texture_normal_heap {
    intptr_t _refCount;
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_vertexBuffer_vertex_location_texture_normal {
    sjs_string format;
    sjs_array_i32 indices;
    sjs_array_vertex_location_texture_normal vertices;
    vertex_buffer_t* buffer;
};

struct td_sjs_vertexBuffer_vertex_location_texture_normal_heap {
    intptr_t _refCount;
    sjs_string format;
    sjs_array_i32 indices;
    sjs_array_vertex_location_texture_normal vertices;
    vertex_buffer_t* buffer;
};

struct td_sjs_texture {
    sjs_size size;
    uint32_t id;
};

struct td_sjs_texture_heap {
    intptr_t _refCount;
    sjs_size size;
    uint32_t id;
};

struct td_sjs_model {
    sjs_vertexBuffer_vertex_location_texture_normal vertexBuffer;
    sjs_shader shader;
    sjs_texture texture;
    sjs_mat4 model;
    sjs_vec3 center;
    bool hasAlpha;
    sjs_string id;
    sjs_mat4 _projection;
    sjs_mat4 _view;
    sjs_mat4 _world;
    sjs_light _light;
    sjs_vec3 _projectedCenter;
};

struct td_sjs_model_heap {
    intptr_t _refCount;
    sjs_vertexBuffer_vertex_location_texture_normal vertexBuffer;
    sjs_shader shader;
    sjs_texture texture;
    sjs_mat4 model;
    sjs_vec3 center;
    bool hasAlpha;
    sjs_string id;
    sjs_mat4 _projection;
    sjs_mat4 _view;
    sjs_mat4 _world;
    sjs_light _light;
    sjs_vec3 _projectedCenter;
};

struct td_sjs_vec4 {
    float x;
    float y;
    float z;
    float w;
};

struct td_sjs_vec4_heap {
    intptr_t _refCount;
    float x;
    float y;
    float z;
    float w;
};

struct td_sjs_vec2 {
    float x;
    float y;
};

struct td_sjs_vec2_heap {
    intptr_t _refCount;
    float x;
    float y;
};

struct td_sjs_vertex_location_texture_normal {
    sjs_vec3 location;
    sjs_vec2 texture;
    sjs_vec3 normal;
};

struct td_sjs_vertex_location_texture_normal_heap {
    intptr_t _refCount;
    sjs_vec3 location;
    sjs_vec2 texture;
    sjs_vec3 normal;
};

struct td_sjs_array_texture {
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_array_texture_heap {
    intptr_t _refCount;
    int32_t dataSize;
    void* data;
    bool _isGlobal;
    int32_t count;
};

struct td_sjs_leafPanel {
    sjs_array_texture textures;
    sjs_array_heap_model children;
    float _angle;
};

struct td_sjs_leafPanel_heap {
    intptr_t _refCount;
    sjs_array_texture textures;
    sjs_array_heap_model children;
    float _angle;
};

struct td_cb_texture_heap_model {
    void* _parent;
    void (*_cb_heap)(void* _parent, sjs_texture*, sji_nauScene3dElement_model** _return);
};

struct td_cb_texture_heap_model_heap {
    cb_texture_heap_model inner;
    void (*_destroy)(void*);
};

struct td_sjs_panel3d {
    sjs_mat4 model;
    sjs_array_heap_model children;
};

struct td_sjs_panel3d_heap {
    intptr_t _refCount;
    sjs_mat4 model;
    sjs_array_heap_model children;
};

struct td_sjs_boxRenderer {
    sjs_rect rect;
    sjs_color color;
    vertex_buffer_t* buffer;
};

struct td_sjs_boxRenderer_heap {
    intptr_t _refCount;
    sjs_rect rect;
    sjs_color color;
    vertex_buffer_t* buffer;
};

struct td_sjs_crossHairsElement {
    sjs_color color;
    sjs_rect _rect;
    sjs_boxRenderer_heap* _topDownRenderer;
    sjs_boxRenderer_heap* _leftRightRenderer;
    sjs_point _point;
};

struct td_sjs_crossHairsElement_heap {
    intptr_t _refCount;
    sjs_color color;
    sjs_rect _rect;
    sjs_boxRenderer_heap* _topDownRenderer;
    sjs_boxRenderer_heap* _leftRightRenderer;
    sjs_point _point;
};

void halt(const char * format, ...);
void _retain(void* ptr);
bool _release(void* ptr);
double *
make_distance_mapd( double *img,
unsigned int width, unsigned int height );
unsigned char *
make_distance_mapb( unsigned char *img,
unsigned int width, unsigned int height );    
/*
* Compute the local gradient at edge pixels using convolution filters.
* The gradient is computed only at edge pixels. At other places in the
* image, it is never used, and it's mostly zero anyway.
*/
void computegradient(double *img, int w, int h, double *gx, double *gy);
/*
* A somewhat tricky function to approximate the distance to an edge in a
* certain pixel, with consideration to either the local gradient (gx,gy)
* or the direction to the pixel (dx,dy) and the pixel greyscale value a.
* The latter alternative, using (dx,dy), is the metric used by edtaa2().
* Using a local estimate of the edge gradient (gx,gy) yields much better
* accuracy at and near edges, and reduces the error even at distant pixels
* provided that the gradient direction is accurately estimated.
*/
double edgedf(double gx, double gy, double a);
double distaa3(double *img, double *gximg, double *gyimg, int w, int c, int xc, int yc, int xi, int yi);
// Shorthand macro: add ubiquitous parameters dist, gx, gy, img and w and call distaa3()
#define DISTAA(c,xc,yc,xi,yi) (distaa3(img, gx, gy, w, c, xc, yc, xi, yi))
void edtaa3(double *img, double *gx, double *gy, int w, int h, short *distx, short *disty, double *dist);  
void _retainGLid(GLuint id);
bool _releaseGLid(GLuint id);
/* Freetype GL - A C OpenGL Freetype engine
*
* Distributed under the OSI-approved BSD 2-Clause License.  See accompanying
* file `LICENSE` for more details.
*/
/**
* Read a fragment or vertex shader from a file
*
* @param filename file to read shader from
* @return         a newly-allocated text buffer containing code. This buffer
*                 must be freed after usage.
*
*/
char *
shader_read( const char *filename );
/**
* Compile a shader from a text buffer.
*
* @param source code of the shader
* @param type   type of the shader
*
* @return a handle on the compiled program
*
*/
GLuint
shader_compile( const char* source,
const GLenum type );
/**
* Load a vertex and fragment shader sources and build program
*
* @param  vert_filename vertex shader filename
* @param  frag_filename fragment shader filename
*
* @return a handle on the built program
*
*/
GLuint
shader_load( const char * vert_filename,
const char * frag_filename );    
void add_text(vertex_buffer_t * buffer, texture_font_t * font, char *text, vec4 * color, vec2 * pen);	
vec2 get_text_size(texture_font_t * font, char *text);
/**
* Creates a new empty texture atlas.
*
* @param   width   width of the atlas
* @param   height  height of the atlas
* @param   depth   bit depth of the atlas
* @return          a new empty texture atlas.
*
*/
texture_atlas_t *
texture_atlas_new( const size_t width,
const size_t height,
const size_t depth );
/**
*  Deletes a texture atlas.
*
*  @param self a texture atlas structure
*
*/
void
texture_atlas_delete( texture_atlas_t * self );
/**
*  Allocate a new region in the atlas.
*
*  @param self   a texture atlas structure
*  @param width  width of the region to allocate
*  @param height height of the region to allocate
*  @return       Coordinates of the allocated region
*
*/
ivec4
texture_atlas_get_region( texture_atlas_t * self,
const size_t width,
const size_t height );
/**
*  Upload data to the specified atlas region.
*
*  @param self   a texture atlas structure
*  @param x      x coordinate the region
*  @param y      y coordinate the region
*  @param width  width of the region
*  @param height height of the region
*  @param data   data to be uploaded into the specified region
*  @param stride stride of the data
*
*/
void
texture_atlas_set_region( texture_atlas_t * self,
const size_t x,
const size_t y,
const size_t width,
const size_t height,
const unsigned char *data,
const size_t stride );
/**
*  Remove all allocated regions from the atlas.
*
*  @param self   a texture atlas structure
*/
void
texture_atlas_clear( texture_atlas_t * self );    
/**
* This function creates a new texture font from given filename and size.  The
* texture atlas is used to store glyph on demand. Note the depth of the atlas
* will determine if the font is rendered as alpha channel only (depth = 1) or
* RGB (depth = 3) that correspond to subpixel rendering (if available on your
* freetype implementation).
*
* @param atlas     A texture atlas
* @param pt_size   Size of font to be created (in points)
* @param filename  A font filename
*
* @return A new empty font (no glyph inside yet)
*
*/
texture_font_t *
texture_font_new_from_file( texture_atlas_t * atlas,
const float pt_size,
const char * filename );
/**
* This function creates a new texture font from a memory location and size.
* The texture atlas is used to store glyph on demand. Note the depth of the
* atlas will determine if the font is rendered as alpha channel only
* (depth = 1) or RGB (depth = 3) that correspond to subpixel rendering (if
* available on your freetype implementation).
*
* @param atlas       A texture atlas
* @param pt_size     Size of font to be created (in points)
* @param memory_base Start of the font file in memory
* @param memory_size Size of the font file memory region, in bytes
*
* @return A new empty font (no glyph inside yet)
*
*/
texture_font_t *
texture_font_new_from_memory( texture_atlas_t *atlas,
float pt_size,
const void *memory_base,
size_t memory_size );
/**
* Delete a texture font. Note that this does not delete the glyph from the
* texture atlas.
*
* @param self a valid texture font
*/
void
texture_font_delete( texture_font_t * self );
/**
* Request a new glyph from the font. If it has not been created yet, it will
* be.
*
* @param self      A valid texture font
* @param codepoint Character codepoint to be loaded in UTF-8 encoding.
*
* @return A pointer on the new glyph or 0 if the texture atlas is not big
*         enough
*
*/
texture_glyph_t *
texture_font_get_glyph( texture_font_t * self,
const char * codepoint );
/** 
* Request an already loaded glyph from the font. 
* 
* @param self      A valid texture font
* @param codepoint Character codepoint to be found in UTF-8 encoding.
*
* @return A pointer on the glyph or 0 if the glyph is not loaded
*/
texture_glyph_t *
texture_font_find_glyph( texture_font_t * self,
const char * codepoint );
/**
* Request the loading of a given glyph.
*
* @param self       A valid texture font
* @param codepoints Character codepoint to be loaded in UTF-8 encoding.
*
* @return One if the glyph could be loaded, zero if not.
*/
int
texture_font_load_glyph( texture_font_t * self,
const char * codepoint );
/**
* Request the loading of several glyphs at once.
*
* @param self       A valid texture font
* @param codepoints Character codepoints to be loaded in UTF-8 encoding. May
*                   contain duplicates.
*
* @return Number of missed glyph if the texture is not big enough to hold
*         every glyphs.
*/
size_t
texture_font_load_glyphs( texture_font_t * self,
const char * codepoints );
/*
*Increases the size of a fonts texture atlas
*Invalidates all pointers to font->atlas->data
*Changes the UV Coordinates of existing glyphs in the font
*
*@param self A valid texture font
*@param width_new Width of the texture atlas after resizing (must be bigger or equal to current width)
*@param height_new Height of the texture atlas after resizing (must be bigger or equal to current height)
*/
void
texture_font_enlarge_atlas( texture_font_t * self, size_t width_new,
size_t height_new);
/**
* Get the kerning between two horizontal glyphs.
*
* @param self      A valid texture glyph
* @param codepoint Character codepoint of the peceding character in UTF-8 encoding.
*
* @return x kerning value
*/
float
texture_glyph_get_kerning( const texture_glyph_t * self,
const char * codepoint );
/**
* Creates a new empty glyph
*
* @return a new empty glyph (not valid)
*/
texture_glyph_t *
texture_glyph_new( void );    
/**
* Returns the size in bytes of a given UTF-8 encoded character surrogate
*
* @param character  An UTF-8 encoded character
*
* @return  The length of the surrogate in bytes.
*/
size_t
utf8_surrogate_len( const char* character );
/**
* Return the length of the given UTF-8 encoded and
* NULL terminated string.
*
* @param string  An UTF-8 encoded string
*
* @return  The length of the string in characters.
*/
size_t
utf8_strlen( const char* string );
/**
* Converts a given UTF-8 encoded character to its UTF-32 LE equivalent
*
* @param character  An UTF-8 encoded character
*
* @return  The equivalent of the given character in UTF-32 LE
*          encoding.
*/
uint32_t
utf8_to_utf32( const char * character );
/**
* @file   vector.h
* @author Nicolas Rougier (Nicolas.Rougier@inria.fr)
*
* @defgroup vector Vector
*
* The vector structure and accompanying functions loosely mimic the STL C++
* vector class. It is used by @ref texture-atlas (for storing nodes), @ref
* texture-font (for storing glyphs) and @ref font-manager (for storing fonts).
* More information at http://www.cppreference.com/wiki/container/vector/start
*/
/**
* Creates a new empty vector.
*
* @param   item_size    item size in bytes
* @return               a new empty vector
*
*/
vector_t *
vector_new( size_t item_size );
/**
*  Deletes a vector.
*
*  @param self a vector structure
*
*/
void
vector_delete( vector_t *self );
/**
*  Returns a pointer to the item located at specified index.
*
*  @param  self  a vector structure
*  @param  index the index of the item to be returned
*  @return       pointer on the specified item
*/
const void *
vector_get( const vector_t *self,
size_t index );
/**
*  Returns a pointer to the first item.
*
*  @param  self  a vector structure
*  @return       pointer on the first item
*/
const void *
vector_front( const vector_t *self );
/**
*  Returns a pointer to the last item
*
*  @param  self  a vector structure
*  @return pointer on the last item
*/
const void *
vector_back( const vector_t *self );
/**
*  Check if an item is contained within the vector.
*
*  @param  self  a vector structure
*  @param  item  item to be searched in the vector
*  @param  cmp   a pointer a comparison function
*  @return       1 if item is contained within the vector, 0 otherwise
*/
int
vector_contains( const vector_t *self,
const void *item,
int (*cmp)(const void *, const void *) );
/**
*  Checks whether the vector is empty.
*
*  @param  self  a vector structure
*  @return       1 if the vector is empty, 0 otherwise
*/
int
vector_empty( const vector_t *self );
/**
*  Returns the number of items
*
*  @param  self  a vector structure
*  @return       number of items
*/
size_t
vector_size( const vector_t *self );
/**
*  Reserve storage such that it can hold at last size items.
*
*  @param  self  a vector structure
*  @param  size  the new storage capacity
*/
void
vector_reserve( vector_t *self,
const size_t size );
/**
*  Returns current storage capacity
*
*  @param  self  a vector structure
*  @return       storage capacity
*/
size_t
vector_capacity( const vector_t *self );
/**
*  Decrease capacity to fit actual size.
*
*  @param  self  a vector structure
*/
void
vector_shrink( vector_t *self );
/**
*  Removes all items.
*
*  @param  self  a vector structure
*/
void
vector_clear( vector_t *self );
/**
*  Replace an item.
*
*  @param  self  a vector structure
*  @param  index the index of the item to be replaced
*  @param  item  the new item
*/
void
vector_set( vector_t *self,
const size_t index,
const void *item );
/**
*  Erase an item.
*
*  @param  self  a vector structure
*  @param  index the index of the item to be erased
*/
void
vector_erase( vector_t *self,
const size_t index );
/**
*  Erase a range of items.
*
*  @param  self  a vector structure
*  @param  first the index of the first item to be erased
*  @param  last  the index of the last item to be erased
*/
void
vector_erase_range( vector_t *self,
const size_t first,
const size_t last );
/**
*  Appends given item to the end of the vector.
*
*  @param  self a vector structure
*  @param  item the item to be inserted
*/
void
vector_push_back( vector_t *self,
const void *item );
/**
*  Removes the last item of the vector.
*
*  @param  self a vector structure
*/
void
vector_pop_back( vector_t *self );
/**
*  Resizes the vector to contain size items
*
*  If the current size is less than size, additional items are appended and
*  initialized with value. If the current size is greater than size, the
*  vector is reduced to its first size elements.
*
*  @param  self a vector structure
*  @param  size the new size
*/
void
vector_resize( vector_t *self,
const size_t size );
/**
*  Insert a single item at specified index.
*
*  @param  self  a vector structure
*  @param  index location before which to insert item
*  @param  item  the item to be inserted
*/
void
vector_insert( vector_t *self,
const size_t index,
const void *item );
/**
*  Insert raw data at specified index.
*
*  @param  self  a vector structure
*  @param  index location before which to insert item
*  @param  data  a pointer to the items to be inserted
*  @param  count the number of items to be inserted
*/
void
vector_insert_data( vector_t *self,
const size_t index,
const void * data,
const size_t count );
/**
*  Append raw data to the end of the vector.
*
*  @param  self  a vector structure
*  @param  data  a pointer to the items to be inserted
*  @param  count the number of items to be inserted
*/
void
vector_push_back_data( vector_t *self,
const void * data,
const size_t count );
/**
*  Sort vector items according to cmp function.
*
*  @param  self  a vector structure
*  @param  cmp   a pointer a comparison function
*/
void
vector_sort( vector_t *self,
int (*cmp)(const void *, const void *) );    
/**
* Create an attribute from the given parameters.
*
* @param size       number of component
* @param type       data type
* @param normalized Whether fixed-point data values should be normalized
(GL_TRUE) or converted directly as fixed-point values
(GL_FALSE) when they are  accessed.
* @param stride     byte offset between consecutive attributes.
* @param pointer    pointer to the first component of the first attribute
*                   element in the array.
* @return           a new initialized vertex attribute.
*
* @private
*/
vertex_attribute_t *
vertex_attribute_new( GLchar * name,
GLint size,
GLenum type,
GLboolean normalized,
GLsizei stride,
GLvoid *pointer );
/**
* Delete a vertex attribute.
*
* @param  self a vertex attribute
*
*/
void
vertex_attribute_delete( vertex_attribute_t * self );
/**
* Create an attribute from the given description.
*
* @param  format Format string specifies the format of a vertex attribute.
* @return        an initialized vertex attribute
*
* @private
*/
vertex_attribute_t *
vertex_attribute_parse( char *format );
/**
* Enable a vertex attribute.
*
* @param attr  a vertex attribute
*
* @private
*/
void
vertex_attribute_enable( vertex_attribute_t *attr );    
#ifdef WIN32
// strndup() is not available on Windows
char *strndup( const char *s1, size_t n);
#endif
/**
* Creates an empty vertex buffer.
*
* @param  format a string describing vertex format.
* @return        an empty vertex buffer.
*/
vertex_buffer_t *
vertex_buffer_new( const char *format );
/**
* Deletes vertex buffer and releases GPU memory.
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_delete( vertex_buffer_t * self );
/**
*  Returns the number of items in the vertex buffer
*
*  @param  self  a vertex buffer
*  @return       number of items
*/
size_t
vertex_buffer_size( const vertex_buffer_t *self );
/**
*  Returns vertex format
*
*  @param  self  a vertex buffer
*  @return       vertex format
*/
const char *
vertex_buffer_format( const vertex_buffer_t *self );
/**
* Print information about a vertex buffer
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_print( vertex_buffer_t * self );
/**
* Prepare vertex buffer for render.
*
* @param  self  a vertex buffer
* @param  mode  render mode
*/
void
vertex_buffer_render_setup ( vertex_buffer_t *self,
GLenum mode );
/**
* Finish rendering by setting back modified states
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_render_finish ( vertex_buffer_t *self );
/**
* Render vertex buffer.
*
* @param  self  a vertex buffer
* @param  mode  render mode
*/
void
vertex_buffer_render ( vertex_buffer_t *self,
GLenum mode );
/**
* Render a specified item from the vertex buffer.
*
* @param  self   a vertex buffer
* @param  index index of the item to be rendered
*/
void
vertex_buffer_render_item ( vertex_buffer_t *self,
size_t index );
/**
* Upload buffer to GPU memory.
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_upload( vertex_buffer_t *self );
/**
* Clear all items.
*
* @param  self  a vertex buffer
*/
void
vertex_buffer_clear( vertex_buffer_t *self );
/**
* Appends indices at the end of the buffer.
*
* @param  self     a vertex buffer
* @param  indices  indices to be appended
* @param  icount   number of indices to be appended
*
* @private
*/
void
vertex_buffer_push_back_indices ( vertex_buffer_t *self,
const GLuint * indices,
const size_t icount );
/**
* Appends vertices at the end of the buffer.
*
* @note Internal use
*
* @param  self     a vertex buffer
* @param  vertices vertices to be appended
* @param  vcount   number of vertices to be appended
*
* @private
*/
void
vertex_buffer_push_back_vertices ( vertex_buffer_t *self,
const void * vertices,
const size_t vcount );
/**
* Insert indices in the buffer.
*
* @param  self    a vertex buffer
* @param  index   location before which to insert indices
* @param  indices indices to be appended
* @param  icount  number of indices to be appended
*
* @private
*/
void
vertex_buffer_insert_indices ( vertex_buffer_t *self,
const size_t index,
const GLuint *indices,
const size_t icount );
/**
* Insert vertices in the buffer.
*
* @param  self     a vertex buffer
* @param  index    location before which to insert vertices
* @param  vertices vertices to be appended
* @param  vcount   number of vertices to be appended
*
* @private
*/
void
vertex_buffer_insert_vertices ( vertex_buffer_t *self,
const size_t index,
const void *vertices,
const size_t vcount );
/**
* Erase indices in the buffer.
*
* @param  self   a vertex buffer
* @param  first  the index of the first index to be erased
* @param  last   the index of the last index to be erased
*
* @private
*/
void
vertex_buffer_erase_indices ( vertex_buffer_t *self,
const size_t first,
const size_t last );
/**
* Erase vertices in the buffer.
*
* @param  self   a vertex buffer
* @param  first  the index of the first vertex to be erased
* @param  last   the index of the last vertex to be erased
*
* @private
*/
void
vertex_buffer_erase_vertices ( vertex_buffer_t *self,
const size_t first,
const size_t last );
/**
* Append a new item to the collection.
*
* @param  self   a vertex buffer
* @param  vcount   number of vertices
* @param  vertices raw vertices data
* @param  icount   number of indices
* @param  indices  raw indices data
*/
size_t
vertex_buffer_push_back( vertex_buffer_t * self,
const void * vertices, const size_t vcount,
const GLuint * indices, const size_t icount );
/**
* Insert a new item into the vertex buffer.
*
* @param  self      a vertex buffer
* @param  index     location before which to insert item
* @param  vertices  raw vertices data
* @param  vcount    number of vertices
* @param  indices   raw indices data
* @param  icount    number of indices
*/
size_t
vertex_buffer_insert( vertex_buffer_t * self,
const size_t index,
const void * vertices, const size_t vcount,
const GLuint * indices, const size_t icount );
/**
* Erase an item from the vertex buffer.
*
* @param  self     a vertex buffer
* @param  index    index of the item to be deleted
*/
void
vertex_buffer_erase( vertex_buffer_t * self,
const size_t index );    
int32_t result1;
float result12;
float result13;
float result16;
float result17;
float result18;
float result19;
float result20;
float result21;
float result22;
float result23;
float result24;
float result25;
float result26;
float result27;
float result28;
float result29;
float result30;
float result31;
float result32;
float result33;
float result34;
float result35;
float result36;
float result37;
float result38;
float result39;
float result40;
float result41;
float result42;
float result43;
float result44;
float result45;
float result46;
sjs_string sjt_call27;
sjs_mat4 sjt_call28;
sjs_mat4 sjt_call29;
sjs_texture sjt_call34;
sjs_string sjt_call35;
sjs_texture sjt_call36;
sjs_string sjt_call37;
sjs_texture sjt_call38;
sjs_string sjt_call39;
sjs_texture sjt_call40;
sjs_string sjt_call41;
sjs_texture sjt_call42;
sjs_string sjt_call43;
sjs_texture sjt_call44;
sjs_string sjt_call45;
sjs_texture sjt_call46;
sjs_string sjt_call47;
sjs_texture sjt_call48;
sjs_string sjt_call49;
sjs_string sjt_call50;
sjs_mat4 sjt_call51;
sjs_mat4 sjt_call52;
sjs_string sjt_call53;
sjs_mat4 sjt_call54;
sjs_mat4 sjt_call55;
sjs_string sjt_call56;
sjs_mat4 sjt_call57;
sjs_mat4 sjt_call58;
sjs_string sjt_call59;
sjs_mat4 sjt_call60;
sjs_mat4 sjt_call61;
sjs_string sjt_call62;
sjs_mat4 sjt_call63;
sjs_mat4 sjt_call64;
sjs_string sjt_call65;
sjs_mat4 sjt_call66;
sjs_mat4 sjt_call67;
sjs_string sjt_call68;
sjs_mat4 sjt_call69;
sjs_mat4 sjt_call70;
sjs_string sjt_call71;
sjs_mat4 sjt_call72;
sjs_mat4 sjt_call73;
sjs_string sjt_call74;
sjs_mat4 sjt_call75;
sjs_mat4 sjt_call76;
sjs_string sjt_call77;
sjs_mat4 sjt_call78;
sjs_mat4 sjt_call79;
sjs_vec3 sjt_call80;
sjs_vec3 sjt_call81;
sjs_vec3 sjt_call82;
sjs_fillElement_heap* sjt_cast1;
sjs_leafPanel_heap* sjt_cast11;
sjs_panel3d_heap* sjt_cast17;
sjs_model_heap* sjt_cast18;
sjs_model_heap* sjt_cast19;
sjs_nauScene3dElement_heap* sjt_cast2;
sjs_model_heap* sjt_cast20;
sjs_model_heap* sjt_cast21;
sjs_model_heap* sjt_cast22;
sjs_model_heap* sjt_cast23;
sjs_model_heap* sjt_cast24;
sjs_model_heap* sjt_cast25;
sjs_model_heap* sjt_cast26;
sjs_model_heap* sjt_cast27;
sjs_crossHairsElement_heap* sjt_cast28;
sjs_model_heap* sjt_cast9;
sjs_shader* sjt_copy11;
sjs_shader* sjt_copy18;
sjs_shader* sjt_copy19;
sjs_shader* sjt_copy20;
sjs_shader* sjt_copy21;
sjs_shader* sjt_copy22;
sjs_shader* sjt_copy23;
sjs_shader* sjt_copy24;
sjs_shader* sjt_copy25;
sjs_shader* sjt_copy26;
sjs_shader* sjt_copy27;
sji_nauScene3dElement_model* sjt_functionParam100;
float sjt_functionParam181;
float sjt_functionParam182;
float sjt_functionParam183;
float sjt_functionParam184;
float sjt_functionParam185;
float sjt_functionParam186;
float sjt_functionParam187;
float sjt_functionParam188;
float sjt_functionParam189;
sjs_string* sjt_functionParam190;
float sjt_functionParam191;
float sjt_functionParam192;
float sjt_functionParam193;
sjs_mat4* sjt_functionParam194;
float sjt_functionParam195;
float sjt_functionParam196;
float sjt_functionParam197;
int32_t sjt_functionParam198;
sji_nauScene3dElement_model* sjt_functionParam199;
int32_t sjt_functionParam243;
sjs_texture* sjt_functionParam244;
sjs_string* sjt_functionParam245;
int32_t sjt_functionParam246;
sjs_texture* sjt_functionParam247;
sjs_string* sjt_functionParam248;
int32_t sjt_functionParam249;
sjs_texture* sjt_functionParam250;
sjs_string* sjt_functionParam251;
int32_t sjt_functionParam252;
sjs_texture* sjt_functionParam253;
sjs_string* sjt_functionParam254;
int32_t sjt_functionParam255;
sjs_texture* sjt_functionParam256;
sjs_string* sjt_functionParam257;
int32_t sjt_functionParam258;
sjs_texture* sjt_functionParam259;
sjs_string* sjt_functionParam260;
int32_t sjt_functionParam261;
sjs_texture* sjt_functionParam262;
sjs_string* sjt_functionParam263;
int32_t sjt_functionParam264;
sjs_texture* sjt_functionParam265;
sjs_string* sjt_functionParam266;
int32_t sjt_functionParam267;
sji_nauScene3dElement_model* sjt_functionParam268;
float sjt_functionParam273;
float sjt_functionParam274;
float sjt_functionParam275;
int32_t sjt_functionParam276;
sji_nauScene3dElement_model* sjt_functionParam277;
float sjt_functionParam278;
float sjt_functionParam279;
float sjt_functionParam280;
float sjt_functionParam281;
float sjt_functionParam282;
float sjt_functionParam283;
float sjt_functionParam284;
float sjt_functionParam285;
float sjt_functionParam286;
sjs_string* sjt_functionParam287;
float sjt_functionParam288;
float sjt_functionParam289;
float sjt_functionParam290;
sjs_mat4* sjt_functionParam291;
float sjt_functionParam292;
float sjt_functionParam293;
float sjt_functionParam294;
int32_t sjt_functionParam295;
sji_nauScene3dElement_model* sjt_functionParam296;
float sjt_functionParam297;
float sjt_functionParam298;
float sjt_functionParam299;
float sjt_functionParam300;
float sjt_functionParam301;
float sjt_functionParam302;
float sjt_functionParam303;
float sjt_functionParam304;
float sjt_functionParam305;
sjs_string* sjt_functionParam306;
float sjt_functionParam307;
float sjt_functionParam308;
float sjt_functionParam309;
sjs_mat4* sjt_functionParam310;
float sjt_functionParam311;
float sjt_functionParam312;
float sjt_functionParam313;
int32_t sjt_functionParam314;
sji_nauScene3dElement_model* sjt_functionParam315;
float sjt_functionParam316;
float sjt_functionParam317;
float sjt_functionParam318;
float sjt_functionParam319;
float sjt_functionParam320;
float sjt_functionParam321;
float sjt_functionParam322;
float sjt_functionParam323;
float sjt_functionParam324;
sjs_string* sjt_functionParam325;
float sjt_functionParam326;
float sjt_functionParam327;
float sjt_functionParam328;
sjs_mat4* sjt_functionParam329;
float sjt_functionParam330;
float sjt_functionParam331;
float sjt_functionParam332;
int32_t sjt_functionParam333;
sji_nauScene3dElement_model* sjt_functionParam334;
float sjt_functionParam335;
float sjt_functionParam336;
float sjt_functionParam337;
float sjt_functionParam338;
float sjt_functionParam339;
float sjt_functionParam340;
float sjt_functionParam341;
float sjt_functionParam342;
float sjt_functionParam343;
sjs_string* sjt_functionParam344;
float sjt_functionParam345;
float sjt_functionParam346;
float sjt_functionParam347;
sjs_mat4* sjt_functionParam348;
float sjt_functionParam349;
float sjt_functionParam350;
float sjt_functionParam351;
int32_t sjt_functionParam352;
sji_nauScene3dElement_model* sjt_functionParam353;
float sjt_functionParam354;
float sjt_functionParam355;
float sjt_functionParam356;
float sjt_functionParam357;
float sjt_functionParam358;
float sjt_functionParam359;
float sjt_functionParam360;
float sjt_functionParam361;
float sjt_functionParam362;
sjs_string* sjt_functionParam363;
float sjt_functionParam364;
float sjt_functionParam365;
float sjt_functionParam366;
sjs_mat4* sjt_functionParam367;
float sjt_functionParam368;
float sjt_functionParam369;
float sjt_functionParam370;
int32_t sjt_functionParam371;
sji_nauScene3dElement_model* sjt_functionParam372;
float sjt_functionParam373;
float sjt_functionParam374;
float sjt_functionParam375;
float sjt_functionParam376;
float sjt_functionParam377;
float sjt_functionParam378;
float sjt_functionParam379;
float sjt_functionParam380;
float sjt_functionParam381;
sjs_string* sjt_functionParam382;
float sjt_functionParam383;
float sjt_functionParam384;
float sjt_functionParam385;
sjs_mat4* sjt_functionParam386;
float sjt_functionParam387;
float sjt_functionParam388;
float sjt_functionParam389;
int32_t sjt_functionParam390;
sji_nauScene3dElement_model* sjt_functionParam391;
float sjt_functionParam392;
float sjt_functionParam393;
float sjt_functionParam394;
float sjt_functionParam395;
float sjt_functionParam396;
float sjt_functionParam397;
float sjt_functionParam398;
float sjt_functionParam399;
int32_t sjt_functionParam4;
float sjt_functionParam400;
sjs_string* sjt_functionParam401;
float sjt_functionParam402;
float sjt_functionParam403;
float sjt_functionParam404;
sjs_mat4* sjt_functionParam405;
float sjt_functionParam406;
float sjt_functionParam407;
float sjt_functionParam408;
int32_t sjt_functionParam409;
sji_nauScene3dElement_model* sjt_functionParam410;
float sjt_functionParam411;
float sjt_functionParam412;
float sjt_functionParam413;
float sjt_functionParam414;
float sjt_functionParam415;
float sjt_functionParam416;
float sjt_functionParam417;
float sjt_functionParam418;
float sjt_functionParam419;
sjs_string* sjt_functionParam420;
float sjt_functionParam421;
float sjt_functionParam422;
float sjt_functionParam423;
sjs_mat4* sjt_functionParam424;
float sjt_functionParam425;
float sjt_functionParam426;
float sjt_functionParam427;
int32_t sjt_functionParam428;
sji_nauScene3dElement_model* sjt_functionParam429;
float sjt_functionParam430;
float sjt_functionParam431;
float sjt_functionParam432;
float sjt_functionParam433;
float sjt_functionParam434;
float sjt_functionParam435;
float sjt_functionParam436;
float sjt_functionParam437;
float sjt_functionParam438;
sjs_string* sjt_functionParam439;
float sjt_functionParam440;
float sjt_functionParam441;
float sjt_functionParam442;
sjs_mat4* sjt_functionParam443;
float sjt_functionParam444;
float sjt_functionParam445;
float sjt_functionParam446;
int32_t sjt_functionParam447;
sji_nauScene3dElement_model* sjt_functionParam448;
float sjt_functionParam449;
float sjt_functionParam450;
float sjt_functionParam451;
float sjt_functionParam452;
float sjt_functionParam453;
float sjt_functionParam454;
float sjt_functionParam455;
float sjt_functionParam456;
float sjt_functionParam457;
sjs_string* sjt_functionParam458;
float sjt_functionParam459;
float sjt_functionParam460;
float sjt_functionParam461;
sjs_mat4* sjt_functionParam462;
float sjt_functionParam463;
float sjt_functionParam464;
float sjt_functionParam465;
sjs_vec3* sjt_functionParam466;
sjs_vec3* sjt_functionParam467;
sjs_vec3* sjt_functionParam468;
int32_t sjt_functionParam469;
sji_element* sjt_functionParam470;
sji_element* sjt_functionParam5;
int32_t sjt_functionParam99;
int32_t sjt_math1;
int32_t sjt_math2;
int32_t sjt_negate1;
float sjt_negate11;
float sjt_negate12;
float sjt_negate15;
float sjt_negate16;
float sjt_negate17;
float sjt_negate18;
float sjt_negate19;
float sjt_negate20;
float sjt_negate21;
float sjt_negate22;
float sjt_negate23;
float sjt_negate24;
float sjt_negate25;
float sjt_negate26;
float sjt_negate27;
float sjt_negate28;
float sjt_negate29;
float sjt_negate30;
float sjt_negate31;
float sjt_negate32;
float sjt_negate33;
float sjt_negate34;
float sjt_negate35;
float sjt_negate36;
float sjt_negate37;
float sjt_negate38;
float sjt_negate39;
float sjt_negate40;
float sjt_negate41;
float sjt_negate42;
float sjt_negate43;
float sjt_negate44;
float sjt_negate45;
sjs_array_texture* sjt_parent101;
sjs_array_texture* sjt_parent102;
sjs_array_texture* sjt_parent103;
sjs_array_texture* sjt_parent104;
sjs_array_texture* sjt_parent105;
sjs_array_texture* sjt_parent106;
sjs_array_texture* sjt_parent107;
sjs_array_texture* sjt_parent108;
sjs_array_heap_model* sjt_parent109;
sjs_array_heap_model* sjt_parent117;
sjs_mat4* sjt_parent118;
sjs_array_heap_model* sjt_parent119;
sjs_mat4* sjt_parent120;
sjs_array_heap_model* sjt_parent121;
sjs_mat4* sjt_parent122;
sjs_array_heap_model* sjt_parent123;
sjs_mat4* sjt_parent124;
sjs_array_heap_model* sjt_parent125;
sjs_mat4* sjt_parent126;
sjs_array_heap_model* sjt_parent127;
sjs_mat4* sjt_parent128;
sjs_array_heap_model* sjt_parent129;
sjs_mat4* sjt_parent130;
sjs_array_heap_model* sjt_parent131;
sjs_mat4* sjt_parent132;
sjs_array_heap_model* sjt_parent133;
sjs_mat4* sjt_parent134;
sjs_array_heap_model* sjt_parent135;
sjs_mat4* sjt_parent136;
sjs_array_heap_element* sjt_parent137;
sjs_anon5* sjt_parent142;
sjs_array_heap_model* sjt_parent41;
sjs_array_heap_element* sjt_parent7;
sjs_mat4* sjt_parent77;
sjs_array_heap_model* sjt_parent78;
sjs_anon2 sjv_animator;
sjs_shader sjv_blurHorizontalShader;
sjs_shader sjv_blurVerticalShader;
sjs_anon3 sjv_borderPosition;
sjs_shader sjv_boxShader;
sjs_anon4 sjv_buttonState;
sjs_anon5 sjv_colors;
sjs_anon1 sjv_console;
void* sjv_emptyStringData;
float sjv_f32_pi;
int32_t sjv_glFeature_GL_BLEND;
int32_t sjv_glFeature_GL_CULL_FACE;
int32_t sjv_glFeature_GL_DEPTH_TEST;
int32_t sjv_glFeature_GL_DITHER;
int32_t sjv_glFeature_GL_POLYGON_OFFSET_FILL;
int32_t sjv_glFeature_GL_SAMPLE_ALPHA_TO_COVERAGE;
int32_t sjv_glFeature_GL_SAMPLE_COVERAGE;
int32_t sjv_glFeature_GL_SCISSOR_TEST;
int32_t sjv_glFeature_GL_STENCIL_TEST;
int32_t sjv_glFramebufferAttachment_GL_COLOR_ATTACHMENT0;
int32_t sjv_glFramebufferAttachment_GL_DEPTH_ATTACHMENT;
int32_t sjv_glFramebufferAttachment_GL_STENCIL_ATTACHMENT;
int32_t sjv_glFramebufferStatus_GL_FRAMEBUFFER_COMPLETE;
int32_t sjv_glFramebufferStatus_GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
int32_t sjv_glFramebufferStatus_GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT;
int32_t sjv_glFramebufferStatus_GL_FRAMEBUFFER_UNSUPPORTED;
int32_t sjv_glFramebufferTexture_GL_TEXTURE_2D;
int32_t sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
int32_t sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
int32_t sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
int32_t sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_POSITIVE_X;
int32_t sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
int32_t sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
int32_t sjv_glRenderbufferFormat_GL_DEPTH_COMPONENT16;
int32_t sjv_glRenderbufferFormat_GL_RGB565;
int32_t sjv_glRenderbufferFormat_GL_RGB5_A1;
int32_t sjv_glRenderbufferFormat_GL_RGBA4;
int32_t sjv_glRenderbufferFormat_GL_STENCIL_INDEX8;
int32_t sjv_glTextureAttribute_GL_TEXTURE_MAG_FILTER;
int32_t sjv_glTextureAttribute_GL_TEXTURE_MIN_FILTER;
int32_t sjv_glTextureAttribute_GL_TEXTURE_WRAP_S;
int32_t sjv_glTextureAttribute_GL_TEXTURE_WRAP_T;
int32_t sjv_glTextureFormat_GL_ALPHA;
int32_t sjv_glTextureFormat_GL_LUMINANCE;
int32_t sjv_glTextureFormat_GL_LUMINANCE_ALPHA;
int32_t sjv_glTextureFormat_GL_RGB;
int32_t sjv_glTextureFormat_GL_RGBA;
int32_t sjv_glTextureType_GL_UNSIGNED_BYTE;
int32_t sjv_glTextureType_GL_UNSIGNED_SHORT_4_4_4_4;
int32_t sjv_glTextureType_GL_UNSIGNED_SHORT_5_5_5_1;
int32_t sjv_glTextureType_GL_UNSIGNED_SHORT_5_6_5;
int32_t sjv_glTextureValue_GL_CLAMP_TO_EDGE;
int32_t sjv_glTextureValue_GL_LINEAR;
int32_t sjv_glTextureValue_GL_LINEAR_MIPMAP_LINEAR;
int32_t sjv_glTextureValue_GL_LINEAR_MIPMAP_NEAREST;
int32_t sjv_glTextureValue_GL_MIRRORED_REPEAT;
int32_t sjv_glTextureValue_GL_NEAREST;
int32_t sjv_glTextureValue_GL_NEAREST_MIPMAP_LINEAR;
int32_t sjv_glTextureValue_GL_NEAREST_MIPMAP_NEAREST;
int32_t sjv_glTextureValue_GL_REPEAT;
int32_t sjv_glTexture_GL_TEXTURE_2D;
int32_t sjv_glTexture_GL_TEXTURE_CUBE_MAP;
int32_t sjv_i32_maxValue;
int32_t sjv_i32_minValue;
sjs_shader sjv_imageShader;
int32_t sjv_mouseEvent_down;
int32_t sjv_mouseEvent_move;
int32_t sjv_mouseEvent_up;
sjs_shader sjv_phongColorShader;
sjs_shader sjv_phongTextureShader;
sji_element* sjv_root;
sjs_scene2d sjv_rootScene;
sjs_windowRenderer sjv_rootWindowRenderer;
sjs_anon6 sjv_style;
sjs_shader sjv_textShader;
uint32_t sjv_u32_maxValue;
sjs_string sjv_vertex_location_texture_normal_format;

void sjf_anon1(sjs_anon1* _this);
void sjf_anon1_copy(sjs_anon1* _this, sjs_anon1* _from);
void sjf_anon1_destroy(sjs_anon1* _this);
void sjf_anon1_heap(sjs_anon1_heap* _this);
void sjf_anon2(sjs_anon2* _this);
void sjf_anon2_copy(sjs_anon2* _this, sjs_anon2* _from);
void sjf_anon2_destroy(sjs_anon2* _this);
void sjf_anon2_heap(sjs_anon2_heap* _this);
void sjf_anon2_nextFrame(sjs_anon2* _parent, int32_t time);
void sjf_anon3(sjs_anon3* _this);
void sjf_anon3_copy(sjs_anon3* _this, sjs_anon3* _from);
void sjf_anon3_destroy(sjs_anon3* _this);
void sjf_anon3_heap(sjs_anon3_heap* _this);
void sjf_anon4(sjs_anon4* _this);
void sjf_anon4_copy(sjs_anon4* _this, sjs_anon4* _from);
void sjf_anon4_destroy(sjs_anon4* _this);
void sjf_anon4_heap(sjs_anon4_heap* _this);
void sjf_anon5(sjs_anon5* _this);
void sjf_anon5_copy(sjs_anon5* _this, sjs_anon5* _from);
void sjf_anon5_destroy(sjs_anon5* _this);
void sjf_anon5_heap(sjs_anon5_heap* _this);
void sjf_anon5_red(sjs_anon5* _parent, sjs_color* _return);
void sjf_anon5_red_heap(sjs_anon5* _parent, sjs_color_heap** _return);
void sjf_anon6(sjs_anon6* _this);
void sjf_anon6_copy(sjs_anon6* _this, sjs_anon6* _from);
void sjf_anon6_destroy(sjs_anon6* _this);
void sjf_anon6_heap(sjs_anon6_heap* _this);
void sjf_array_char(sjs_array_char* _this);
void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from);
void sjf_array_char_destroy(sjs_array_char* _this);
void sjf_array_char_getAt(sjs_array_char* _parent, int32_t index, char* _return);
void sjf_array_char_grow(sjs_array_char* _parent, int32_t newSize, sjs_array_char* _return);
void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newSize, sjs_array_char_heap** _return);
void sjf_array_char_heap(sjs_array_char_heap* _this);
void sjf_array_char_initAt(sjs_array_char* _parent, int32_t index, char item);
void sjf_array_char_setAt(sjs_array_char* _parent, int32_t index, char item);
void sjf_array_heap_animation(sjs_array_heap_animation* _this);
void sjf_array_heap_animation_copy(sjs_array_heap_animation* _this, sjs_array_heap_animation* _from);
void sjf_array_heap_animation_destroy(sjs_array_heap_animation* _this);
void sjf_array_heap_animation_getAt_heap(sjs_array_heap_animation* _parent, int32_t index, sji_anon2_animation** _return);
void sjf_array_heap_animation_heap(sjs_array_heap_animation_heap* _this);
void sjf_array_heap_element(sjs_array_heap_element* _this);
void sjf_array_heap_element_copy(sjs_array_heap_element* _this, sjs_array_heap_element* _from);
void sjf_array_heap_element_destroy(sjs_array_heap_element* _this);
void sjf_array_heap_element_getAt_heap(sjs_array_heap_element* _parent, int32_t index, sji_element** _return);
void sjf_array_heap_element_heap(sjs_array_heap_element_heap* _this);
void sjf_array_heap_element_initAt(sjs_array_heap_element* _parent, int32_t index, sji_element* item);
void sjf_array_heap_model(sjs_array_heap_model* _this);
void sjf_array_heap_model__quickSortCallback(sjs_array_heap_model* _parent, int32_t left, int32_t right, cb_heap_model_heap_model_i32 cb);
void sjf_array_heap_model_copy(sjs_array_heap_model* _this, sjs_array_heap_model* _from);
void sjf_array_heap_model_destroy(sjs_array_heap_model* _this);
void sjf_array_heap_model_getAt_heap(sjs_array_heap_model* _parent, int32_t index, sji_nauScene3dElement_model** _return);
void sjf_array_heap_model_grow(sjs_array_heap_model* _parent, int32_t newSize, sjs_array_heap_model* _return);
void sjf_array_heap_model_grow_heap(sjs_array_heap_model* _parent, int32_t newSize, sjs_array_heap_model_heap** _return);
void sjf_array_heap_model_heap(sjs_array_heap_model_heap* _this);
void sjf_array_heap_model_initAt(sjs_array_heap_model* _parent, int32_t index, sji_nauScene3dElement_model* item);
void sjf_array_heap_model_setAt(sjs_array_heap_model* _parent, int32_t index, sji_nauScene3dElement_model* item);
void sjf_array_heap_model_sortcb(sjs_array_heap_model* _parent, cb_heap_model_heap_model_i32 cb);
void sjf_array_i32(sjs_array_i32* _this);
void sjf_array_i32_copy(sjs_array_i32* _this, sjs_array_i32* _from);
void sjf_array_i32_destroy(sjs_array_i32* _this);
void sjf_array_i32_heap(sjs_array_i32_heap* _this);
void sjf_array_i32_initAt(sjs_array_i32* _parent, int32_t index, int32_t item);
void sjf_array_texture(sjs_array_texture* _this);
void sjf_array_texture_copy(sjs_array_texture* _this, sjs_array_texture* _from);
void sjf_array_texture_destroy(sjs_array_texture* _this);
void sjf_array_texture_getAt(sjs_array_texture* _parent, int32_t index, sjs_texture* _return);
void sjf_array_texture_heap(sjs_array_texture_heap* _this);
void sjf_array_texture_initAt(sjs_array_texture* _parent, int32_t index, sjs_texture* item);
void sjf_array_texture_map_heap_model(sjs_array_texture* _parent, cb_texture_heap_model cb, sjs_array_heap_model* _return);
void sjf_array_texture_map_heap_model_heap(sjs_array_texture* _parent, cb_texture_heap_model cb, sjs_array_heap_model_heap** _return);
void sjf_array_vertex_location_texture_normal(sjs_array_vertex_location_texture_normal* _this);
void sjf_array_vertex_location_texture_normal_copy(sjs_array_vertex_location_texture_normal* _this, sjs_array_vertex_location_texture_normal* _from);
void sjf_array_vertex_location_texture_normal_destroy(sjs_array_vertex_location_texture_normal* _this);
void sjf_array_vertex_location_texture_normal_heap(sjs_array_vertex_location_texture_normal_heap* _this);
void sjf_array_vertex_location_texture_normal_initAt(sjs_array_vertex_location_texture_normal* _parent, int32_t index, sjs_vertex_location_texture_normal* item);
void sjf_boxRenderer(sjs_boxRenderer* _this);
void sjf_boxRenderer_copy(sjs_boxRenderer* _this, sjs_boxRenderer* _from);
void sjf_boxRenderer_destroy(sjs_boxRenderer* _this);
void sjf_boxRenderer_heap(sjs_boxRenderer_heap* _this);
void sjf_boxRenderer_render(sjs_boxRenderer* _parent, sjs_scene2d* scene);
void sjf_color(sjs_color* _this);
void sjf_color_asVec3(sjs_color* _parent, sjs_vec3* _return);
void sjf_color_asVec3_heap(sjs_color* _parent, sjs_vec3_heap** _return);
void sjf_color_copy(sjs_color* _this, sjs_color* _from);
void sjf_color_destroy(sjs_color* _this);
void sjf_color_heap(sjs_color_heap* _this);
void sjf_crossHairsElement(sjs_crossHairsElement* _this);
sjs_object* sjf_crossHairsElement_asInterface(sjs_crossHairsElement* _this, int typeId);
sji_element* sjf_crossHairsElement_as_sji_element(sjs_crossHairsElement* _this);
void sjf_crossHairsElement_copy(sjs_crossHairsElement* _this, sjs_crossHairsElement* _from);
void sjf_crossHairsElement_destroy(sjs_crossHairsElement* _this);
void sjf_crossHairsElement_fireMouseEvent(sjs_crossHairsElement* _parent, sjs_point* point, int32_t eventId);
void sjf_crossHairsElement_getRect(sjs_crossHairsElement* _parent, sjs_rect** _return);
void sjf_crossHairsElement_getSize(sjs_crossHairsElement* _parent, sjs_size* maxSize, sjs_size* _return);
void sjf_crossHairsElement_getSize_heap(sjs_crossHairsElement* _parent, sjs_size* maxSize, sjs_size_heap** _return);
void sjf_crossHairsElement_heap(sjs_crossHairsElement_heap* _this);
sjs_object* sjf_crossHairsElement_heap_asInterface(sjs_crossHairsElement_heap* _this, int typeId);
sji_element* sjf_crossHairsElement_heap_as_sji_element(sjs_crossHairsElement_heap* _this);
void sjf_crossHairsElement_render(sjs_crossHairsElement* _parent, sjs_scene2d* scene);
void sjf_crossHairsElement_setRect(sjs_crossHairsElement* _parent, sjs_rect* rect_);
void sjf_f32_compare(float l, float r, int32_t* _return);
void sjf_f32_cos(float v, float* _return);
void sjf_f32_max(float a, float b, float* _return);
void sjf_f32_min(float a, float b, float* _return);
void sjf_f32_random(float* _return);
void sjf_f32_sqrt(float v, float* _return);
void sjf_f32_tan(float v, float* _return);
void sjf_f32_toString(float val, sjs_string* _return);
void sjf_f32_toString_heap(float val, sjs_string_heap** _return);
void sjf_fillElement(sjs_fillElement* _this);
sjs_object* sjf_fillElement_asInterface(sjs_fillElement* _this, int typeId);
sji_element* sjf_fillElement_as_sji_element(sjs_fillElement* _this);
void sjf_fillElement_copy(sjs_fillElement* _this, sjs_fillElement* _from);
void sjf_fillElement_destroy(sjs_fillElement* _this);
void sjf_fillElement_fireMouseEvent(sjs_fillElement* _parent, sjs_point* point, int32_t eventId);
void sjf_fillElement_getRect(sjs_fillElement* _parent, sjs_rect** _return);
void sjf_fillElement_getSize(sjs_fillElement* _parent, sjs_size* maxSize, sjs_size* _return);
void sjf_fillElement_getSize_heap(sjs_fillElement* _parent, sjs_size* maxSize, sjs_size_heap** _return);
void sjf_fillElement_heap(sjs_fillElement_heap* _this);
sjs_object* sjf_fillElement_heap_asInterface(sjs_fillElement_heap* _this, int typeId);
sji_element* sjf_fillElement_heap_as_sji_element(sjs_fillElement_heap* _this);
void sjf_fillElement_render(sjs_fillElement* _parent, sjs_scene2d* scene);
void sjf_fillElement_setRect(sjs_fillElement* _parent, sjs_rect* rect_);
void sjf_glBindTexture(int32_t type, sjs_texture* texture);
void sjf_glDisable(int32_t feature);
void sjf_glEnable(int32_t feature);
void sjf_glGetUniformLocation(sjs_shader* shader, sjs_string* name, int32_t* _return);
void sjf_glUniformMat4(int32_t loc, sjs_mat4* m);
void sjf_glUniformVec3(int32_t loc, sjs_vec3* v);
void sjf_glUseProgram(sjs_shader* shader);
void sjf_i32_max(int32_t a, int32_t b, int32_t* _return);
void sjf_leafPanel(sjs_leafPanel* _this);
sjs_object* sjf_leafPanel_asInterface(sjs_leafPanel* _this, int typeId);
sji_nauScene3dElement_model* sjf_leafPanel_as_sji_nauScene3dElement_model(sjs_leafPanel* _this);
void sjf_leafPanel_copy(sjs_leafPanel* _this, sjs_leafPanel* _from);
void sjf_leafPanel_destroy(sjs_leafPanel* _this);
void sjf_leafPanel_fireMouseEvent(sjs_leafPanel* _parent, sjs_point* point, int32_t eventId);
void sjf_leafPanel_getZ(sjs_leafPanel* _parent, float* _return);
void sjf_leafPanel_heap(sjs_leafPanel_heap* _this);
sjs_object* sjf_leafPanel_heap_asInterface(sjs_leafPanel_heap* _this, int typeId);
sji_nauScene3dElement_model* sjf_leafPanel_heap_as_sji_nauScene3dElement_model(sjs_leafPanel_heap* _this);
void sjf_leafPanel_render(sjs_leafPanel* _parent);
void sjf_leafPanel_renderOrQueue(sjs_leafPanel* _parent, sjs_list_heap_model* zqueue);
void sjf_leafPanel_textureToModel_heap(sjs_leafPanel* _parent, sjs_texture* texture, sji_nauScene3dElement_model** _return);
void sjf_leafPanel_update(sjs_leafPanel* _parent, sjs_rect* sceneRect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light);
void sjf_light(sjs_light* _this);
void sjf_light_copy(sjs_light* _this, sjs_light* _from);
void sjf_light_destroy(sjs_light* _this);
void sjf_light_heap(sjs_light_heap* _this);
void sjf_list_heap_animation(sjs_list_heap_animation* _this);
void sjf_list_heap_animation_copy(sjs_list_heap_animation* _this, sjs_list_heap_animation* _from);
void sjf_list_heap_animation_destroy(sjs_list_heap_animation* _this);
void sjf_list_heap_animation_getAt_heap(sjs_list_heap_animation* _parent, int32_t index, sji_anon2_animation** _return);
void sjf_list_heap_animation_getCount(sjs_list_heap_animation* _parent, int32_t* _return);
void sjf_list_heap_animation_heap(sjs_list_heap_animation_heap* _this);
void sjf_list_heap_animation_removeAt(sjs_list_heap_animation* _parent, int32_t index);
void sjf_list_heap_model(sjs_list_heap_model* _this);
void sjf_list_heap_model_add(sjs_list_heap_model* _parent, sji_nauScene3dElement_model* item);
void sjf_list_heap_model_copy(sjs_list_heap_model* _this, sjs_list_heap_model* _from);
void sjf_list_heap_model_destroy(sjs_list_heap_model* _this);
void sjf_list_heap_model_getAt_heap(sjs_list_heap_model* _parent, int32_t index, sji_nauScene3dElement_model** _return);
void sjf_list_heap_model_getCount(sjs_list_heap_model* _parent, int32_t* _return);
void sjf_list_heap_model_heap(sjs_list_heap_model_heap* _this);
void sjf_list_heap_model_sortcb(sjs_list_heap_model* _parent, cb_heap_model_heap_model_i32 cb);
void sjf_mainLoop(void);
void sjf_mat4(sjs_mat4* _this);
void sjf_mat4_copy(sjs_mat4* _this, sjs_mat4* _from);
void sjf_mat4_destroy(sjs_mat4* _this);
void sjf_mat4_determinant(sjs_mat4* _parent, float* _return);
void sjf_mat4_heap(sjs_mat4_heap* _this);
void sjf_mat4_identity(sjs_mat4* _return);
void sjf_mat4_identity_heap(sjs_mat4_heap** _return);
void sjf_mat4_invert(sjs_mat4* _parent, sjs_mat4* _return);
void sjf_mat4_invert_heap(sjs_mat4* _parent, sjs_mat4_heap** _return);
void sjf_mat4_lookAtLH(sjs_vec3* camera, sjs_vec3* target, sjs_vec3* up, sjs_mat4* _return);
void sjf_mat4_lookAtLH_heap(sjs_vec3* camera, sjs_vec3* target, sjs_vec3* up, sjs_mat4_heap** _return);
void sjf_mat4_multiply(sjs_mat4* _parent, sjs_mat4* m, sjs_mat4* _return);
void sjf_mat4_multiplyVec4(sjs_mat4* _parent, sjs_vec4* v, sjs_vec4* _return);
void sjf_mat4_multiplyVec4_heap(sjs_mat4* _parent, sjs_vec4* v, sjs_vec4_heap** _return);
void sjf_mat4_multiply_f32(sjs_mat4* _parent, float x, sjs_mat4* _return);
void sjf_mat4_multiply_f32_heap(sjs_mat4* _parent, float x, sjs_mat4_heap** _return);
void sjf_mat4_multiply_heap(sjs_mat4* _parent, sjs_mat4* m, sjs_mat4_heap** _return);
void sjf_mat4_orthographic(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4* _return);
void sjf_mat4_orthographic_heap(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4_heap** _return);
void sjf_mat4_perspective(float fovy, float aspect, float znear, float zfar, sjs_mat4* _return);
void sjf_mat4_perspective_heap(float fovy, float aspect, float znear, float zfar, sjs_mat4_heap** _return);
void sjf_mat4_scale(float x, float y, float z, sjs_mat4* _return);
void sjf_mat4_scale_heap(float x, float y, float z, sjs_mat4_heap** _return);
void sjf_mat4_translate(float x, float y, float z, sjs_mat4* _return);
void sjf_mat4_translate_heap(float x, float y, float z, sjs_mat4_heap** _return);
void sjf_mat4_transpose(sjs_mat4* _parent, sjs_mat4* _return);
void sjf_mat4_transpose_heap(sjs_mat4* _parent, sjs_mat4_heap** _return);
void sjf_model(sjs_model* _this);
sjs_object* sjf_model_asInterface(sjs_model* _this, int typeId);
sji_nauScene3dElement_model* sjf_model_as_sji_nauScene3dElement_model(sjs_model* _this);
void sjf_model_copy(sjs_model* _this, sjs_model* _from);
void sjf_model_destroy(sjs_model* _this);
void sjf_model_fireMouseEvent(sjs_model* _parent, sjs_point* point, int32_t eventId);
void sjf_model_getZ(sjs_model* _parent, float* _return);
void sjf_model_heap(sjs_model_heap* _this);
sjs_object* sjf_model_heap_asInterface(sjs_model_heap* _this, int typeId);
sji_nauScene3dElement_model* sjf_model_heap_as_sji_nauScene3dElement_model(sjs_model_heap* _this);
void sjf_model_render(sjs_model* _parent);
void sjf_model_renderOrQueue(sjs_model* _parent, sjs_list_heap_model* zqueue);
void sjf_model_update(sjs_model* _parent, sjs_rect* sceneRect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light);
void sjf_model_zsort(sji_nauScene3dElement_model* l, sji_nauScene3dElement_model* r, int32_t* _return);
void sjf_model_zsort_callback(void * _parent, sji_nauScene3dElement_model* l, sji_nauScene3dElement_model* r, int32_t* _return);
void sjf_nauScene3dElement(sjs_nauScene3dElement* _this);
sjs_object* sjf_nauScene3dElement_asInterface(sjs_nauScene3dElement* _this, int typeId);
sji_element* sjf_nauScene3dElement_as_sji_element(sjs_nauScene3dElement* _this);
void sjf_nauScene3dElement_copy(sjs_nauScene3dElement* _this, sjs_nauScene3dElement* _from);
void sjf_nauScene3dElement_destroy(sjs_nauScene3dElement* _this);
void sjf_nauScene3dElement_fireMouseEvent(sjs_nauScene3dElement* _parent, sjs_point* point, int32_t eventId);
void sjf_nauScene3dElement_getRect(sjs_nauScene3dElement* _parent, sjs_rect** _return);
void sjf_nauScene3dElement_getSize(sjs_nauScene3dElement* _parent, sjs_size* maxSize, sjs_size* _return);
void sjf_nauScene3dElement_getSize_heap(sjs_nauScene3dElement* _parent, sjs_size* maxSize, sjs_size_heap** _return);
void sjf_nauScene3dElement_heap(sjs_nauScene3dElement_heap* _this);
sjs_object* sjf_nauScene3dElement_heap_asInterface(sjs_nauScene3dElement_heap* _this, int typeId);
sji_element* sjf_nauScene3dElement_heap_as_sji_element(sjs_nauScene3dElement_heap* _this);
void sjf_nauScene3dElement_render(sjs_nauScene3dElement* _parent, sjs_scene2d* scene);
void sjf_nauScene3dElement_setRect(sjs_nauScene3dElement* _parent, sjs_rect* rect_);
void sjf_panel3d(sjs_panel3d* _this);
sjs_object* sjf_panel3d_asInterface(sjs_panel3d* _this, int typeId);
sji_nauScene3dElement_model* sjf_panel3d_as_sji_nauScene3dElement_model(sjs_panel3d* _this);
void sjf_panel3d_copy(sjs_panel3d* _this, sjs_panel3d* _from);
void sjf_panel3d_destroy(sjs_panel3d* _this);
void sjf_panel3d_fireMouseEvent(sjs_panel3d* _parent, sjs_point* point, int32_t eventId);
void sjf_panel3d_getZ(sjs_panel3d* _parent, float* _return);
void sjf_panel3d_heap(sjs_panel3d_heap* _this);
sjs_object* sjf_panel3d_heap_asInterface(sjs_panel3d_heap* _this, int typeId);
sji_nauScene3dElement_model* sjf_panel3d_heap_as_sji_nauScene3dElement_model(sjs_panel3d_heap* _this);
void sjf_panel3d_render(sjs_panel3d* _parent);
void sjf_panel3d_renderOrQueue(sjs_panel3d* _parent, sjs_list_heap_model* zqueue);
void sjf_panel3d_update(sjs_panel3d* _parent, sjs_rect* sceneRect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light);
void sjf_planeVertexBuffer(float x0, float x1, float y0, float y1, float z0, float s0, float s1, float t0, float t1, sjs_vertexBuffer_vertex_location_texture_normal* _return);
void sjf_planeVertexBuffer_heap(float x0, float x1, float y0, float y1, float z0, float s0, float s1, float t0, float t1, sjs_vertexBuffer_vertex_location_texture_normal_heap** _return);
void sjf_point(sjs_point* _this);
void sjf_point_copy(sjs_point* _this, sjs_point* _from);
void sjf_point_destroy(sjs_point* _this);
void sjf_point_heap(sjs_point_heap* _this);
void sjf_rect(sjs_rect* _this);
void sjf_rect_containsPoint(sjs_rect* _parent, sjs_point* point, bool* _return);
void sjf_rect_copy(sjs_rect* _this, sjs_rect* _from);
void sjf_rect_destroy(sjs_rect* _this);
void sjf_rect_heap(sjs_rect_heap* _this);
void sjf_rect_isEqual(sjs_rect* _parent, sjs_rect* rect, bool* _return);
void sjf_runLoop(void);
void sjf_scene2d(sjs_scene2d* _this);
void sjf_scene2d_clear(sjs_scene2d* _parent);
void sjf_scene2d_copy(sjs_scene2d* _this, sjs_scene2d* _from);
void sjf_scene2d_destroy(sjs_scene2d* _this);
void sjf_scene2d_heap(sjs_scene2d_heap* _this);
void sjf_scene2d_setSize(sjs_scene2d* _parent, sjs_size* size);
void sjf_scene2d_updateViewport(sjs_scene2d* _parent);
void sjf_shader(sjs_shader* _this);
void sjf_shader_copy(sjs_shader* _this, sjs_shader* _from);
void sjf_shader_destroy(sjs_shader* _this);
void sjf_shader_heap(sjs_shader_heap* _this);
void sjf_size(sjs_size* _this);
void sjf_size_copy(sjs_size* _this, sjs_size* _from);
void sjf_size_destroy(sjs_size* _this);
void sjf_size_heap(sjs_size_heap* _this);
void sjf_size_isEqual(sjs_size* _parent, sjs_size* size, bool* _return);
void sjf_string(sjs_string* _this);
void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return);
void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string_heap** _return);
void sjf_string_copy(sjs_string* _this, sjs_string* _from);
void sjf_string_destroy(sjs_string* _this);
void sjf_string_getAt(sjs_string* _parent, int32_t index, char* _return);
void sjf_string_heap(sjs_string_heap* _this);
void sjf_texture(sjs_texture* _this);
void sjf_textureFromPng(sjs_string* fileName, sjs_texture* _return);
void sjf_textureFromPng_heap(sjs_string* fileName, sjs_texture_heap** _return);
void sjf_texture_copy(sjs_texture* _this, sjs_texture* _from);
void sjf_texture_destroy(sjs_texture* _this);
void sjf_texture_heap(sjs_texture_heap* _this);
void sjf_vec2(sjs_vec2* _this);
void sjf_vec2_copy(sjs_vec2* _this, sjs_vec2* _from);
void sjf_vec2_destroy(sjs_vec2* _this);
void sjf_vec2_heap(sjs_vec2_heap* _this);
void sjf_vec3(sjs_vec3* _this);
void sjf_vec3_add(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3* _return);
void sjf_vec3_add_heap(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3_heap** _return);
void sjf_vec3_copy(sjs_vec3* _this, sjs_vec3* _from);
void sjf_vec3_cross(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3* _return);
void sjf_vec3_cross_heap(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3_heap** _return);
void sjf_vec3_destroy(sjs_vec3* _this);
void sjf_vec3_dot(sjs_vec3* _parent, sjs_vec3* v, float* _return);
void sjf_vec3_heap(sjs_vec3_heap* _this);
void sjf_vec3_max(sjs_vec3* a, sjs_vec3* b, sjs_vec3* _return);
void sjf_vec3_max_heap(sjs_vec3* a, sjs_vec3* b, sjs_vec3_heap** _return);
void sjf_vec3_min(sjs_vec3* a, sjs_vec3* b, sjs_vec3* _return);
void sjf_vec3_min_heap(sjs_vec3* a, sjs_vec3* b, sjs_vec3_heap** _return);
void sjf_vec3_normalize(sjs_vec3* _parent, sjs_vec3* _return);
void sjf_vec3_normalize_heap(sjs_vec3* _parent, sjs_vec3_heap** _return);
void sjf_vec3_subtract(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3* _return);
void sjf_vec3_subtract_heap(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3_heap** _return);
void sjf_vec4(sjs_vec4* _this);
void sjf_vec4_copy(sjs_vec4* _this, sjs_vec4* _from);
void sjf_vec4_destroy(sjs_vec4* _this);
void sjf_vec4_heap(sjs_vec4_heap* _this);
void sjf_vertexBuffer_vertex_location_texture_normal(sjs_vertexBuffer_vertex_location_texture_normal* _this);
void sjf_vertexBuffer_vertex_location_texture_normal_copy(sjs_vertexBuffer_vertex_location_texture_normal* _this, sjs_vertexBuffer_vertex_location_texture_normal* _from);
void sjf_vertexBuffer_vertex_location_texture_normal_destroy(sjs_vertexBuffer_vertex_location_texture_normal* _this);
void sjf_vertexBuffer_vertex_location_texture_normal_heap(sjs_vertexBuffer_vertex_location_texture_normal_heap* _this);
void sjf_vertexBuffer_vertex_location_texture_normal_render(sjs_vertexBuffer_vertex_location_texture_normal* _parent);
void sjf_vertex_location_texture_normal(sjs_vertex_location_texture_normal* _this);
void sjf_vertex_location_texture_normal_copy(sjs_vertex_location_texture_normal* _this, sjs_vertex_location_texture_normal* _from);
void sjf_vertex_location_texture_normal_destroy(sjs_vertex_location_texture_normal* _this);
void sjf_vertex_location_texture_normal_heap(sjs_vertex_location_texture_normal_heap* _this);
void sjf_windowRenderer(sjs_windowRenderer* _this);
void sjf_windowRenderer_copy(sjs_windowRenderer* _this, sjs_windowRenderer* _from);
void sjf_windowRenderer_destroy(sjs_windowRenderer* _this);
void sjf_windowRenderer_getSize(sjs_windowRenderer* _parent, sjs_size* _return);
void sjf_windowRenderer_getSize_heap(sjs_windowRenderer* _parent, sjs_size_heap** _return);
void sjf_windowRenderer_heap(sjs_windowRenderer_heap* _this);
void sjf_windowRenderer_present(sjs_windowRenderer* _parent);
void sji_anon2_animation_copy(sji_anon2_animation* _this, sji_anon2_animation* _from);
void sji_anon2_animation_destroy(sji_anon2_animation* _this);
void sji_element_copy(sji_element* _this, sji_element* _from);
void sji_element_destroy(sji_element* _this);
void sji_nauScene3dElement_model_copy(sji_nauScene3dElement_model* _this, sji_nauScene3dElement_model* _from);
void sji_nauScene3dElement_model_destroy(sji_nauScene3dElement_model* _this);
void main_destroy(void);

void halt(const char * format, ...) {
    va_list args;
    va_start (args, format);
    vprintf (format, args);
    va_end (args);
    exit(-1);
}
void _retain(void* ptr) {
    pointer* p;
    HASH_FIND_PTR(g_pointers, &ptr, p);
    if (p) {
        p->refCount++;
    } else {
        p = (pointer*)malloc(sizeof(pointer));
        p->ptr = ptr;
        p->refCount = 1;
        HASH_ADD_PTR(g_pointers, ptr, p);    
    }
}
bool _release(void* ptr) {
    pointer* p;
    HASH_FIND_PTR(g_pointers, &ptr, p);
    if (p) {
        p->refCount--;
        if (p->refCount == 0) {
            HASH_DEL(g_pointers, p);
            free(p);
        }
        return false;
    }
    return true;
}
double *
make_distance_mapd( double *data, unsigned int width, unsigned int height )
{
    short * xdist = (short *)  malloc( width * height * sizeof(short) );
    short * ydist = (short *)  malloc( width * height * sizeof(short) );
    double * gx   = (double *) calloc( width * height, sizeof(double) );
    double * gy      = (double *) calloc( width * height, sizeof(double) );
    double * outside = (double *) calloc( width * height, sizeof(double) );
    double * inside  = (double *) calloc( width * height, sizeof(double) );
    double vmin = DBL_MAX;
    unsigned int i;
    // Compute outside = edtaa3(bitmap); % Transform background (0's)
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, outside);
    for( i=0; i<width*height; ++i)
    if( outside[i] < 0.0 )
    outside[i] = 0.0;
    // Compute inside = edtaa3(1-bitmap); % Transform foreground (1's)
    memset( gx, 0, sizeof(double)*width*height );
    memset( gy, 0, sizeof(double)*width*height );
    for( i=0; i<width*height; ++i)
    data[i] = 1 - data[i];
    computegradient( data, width, height, gx, gy );
    edtaa3( data, gx, gy, width, height, xdist, ydist, inside );
    for( i=0; i<width*height; ++i )
    if( inside[i] < 0 )
    inside[i] = 0.0;
    // distmap = outside - inside; % Bipolar distance field
    for( i=0; i<width*height; ++i)
    {
        outside[i] -= inside[i];
        if( outside[i] < vmin )
        vmin = outside[i];
    }
    vmin = fabs(vmin);
    for( i=0; i<width*height; ++i)
    {
        double v = outside[i];
        if     ( v < -vmin) outside[i] = -vmin;
        else if( v > +vmin) outside[i] = +vmin;
        data[i] = (outside[i]+vmin)/(2*vmin);
    }
    free( xdist );
    free( ydist );
    free( gx );
    free( gy );
    free( outside );
    free( inside );
    return data;
}
unsigned char *
make_distance_mapb( unsigned char *img,
unsigned int width, unsigned int height )
{
    double * data    = (double *) calloc( width * height, sizeof(double) );
    unsigned char *out = (unsigned char *) malloc( width * height * sizeof(unsigned char) );
    unsigned int i;
    // find minimimum and maximum values
    double img_min = DBL_MAX;
    double img_max = DBL_MIN;
    for( i=0; i<width*height; ++i)
    {
        double v = img[i];
        data[i] = v;
        if (v > img_max)
        img_max = v;
        if (v < img_min)
        img_min = v;
    }
    // Map values from 0 - 255 to 0.0 - 1.0
    for( i=0; i<width*height; ++i)
    data[i] = (img[i]-img_min)/img_max;
    data = make_distance_mapd(data, width, height);
    // map values from 0.0 - 1.0 to 0 - 255
    for( i=0; i<width*height; ++i)
    out[i] = (unsigned char)(255*(1-data[i]));
    free( data );
    return out;
}
/*
* Compute the local gradient at edge pixels using convolution filters.
* The gradient is computed only at edge pixels. At other places in the
* image, it is never used, and it's mostly zero anyway.
*/
void computegradient(double *img, int w, int h, double *gx, double *gy)
{
    int i,j,k;
    double glength;
    #define SQRT2 1.4142136
    // Avoid edges where the kernels would spill over
    for(i = 1; i < h-1; i++) {
        for(j = 1; j < w-1; j++) {
            k = i*w + j;
            // Compute gradient for edge pixels only
            if((img[k]>0.0) && (img[k]<1.0)) {
                gx[k] = -img[k-w-1] - SQRT2*img[k-1] - img[k+w-1] + img[k-w+1] + SQRT2*img[k+1] + img[k+w+1];
                gy[k] = -img[k-w-1] - SQRT2*img[k-w] - img[k-w+1] + img[k+w-1] + SQRT2*img[k+w] + img[k+w+1];
                glength = gx[k]*gx[k] + gy[k]*gy[k];
                if(glength > 0.0) {
                    // Avoid division by zero
                    glength = sqrt(glength);
                    gx[k]=gx[k]/glength;
                    gy[k]=gy[k]/glength;
                }
            }
        }
    }
    // TODO: Compute reasonable values for gx, gy also around the image edges.
    // (These are zero now, which reduces the accuracy for a 1-pixel wide region
    // around the image edge.) 2x2 kernels would be suitable for this.
}
/*
* A somewhat tricky function to approximate the distance to an edge in a
* certain pixel, with consideration to either the local gradient (gx,gy)
* or the direction to the pixel (dx,dy) and the pixel greyscale value a.
* The latter alternative, using (dx,dy), is the metric used by edtaa2().
* Using a local estimate of the edge gradient (gx,gy) yields much better
* accuracy at and near edges, and reduces the error even at distant pixels
* provided that the gradient direction is accurately estimated.
*/
double edgedf(double gx, double gy, double a)
{
    double df, glength, temp, a1;
    // Either A) gu or gv are zero, or B) both
    if ((gx == 0) || (gy == 0)) {
        // Linear approximation is A) correct or B) a fair guess
        df = 0.5-a;  
    } else {
        glength = sqrt(gx*gx + gy*gy);
        if(glength>0) {
            gx = gx/glength;
            gy = gy/glength;
        }
        /* Everything is symmetric wrt sign and transposition,
        * so move to first octant (gx>=0, gy>=0, gx>=gy) to
        * avoid handling all possible edge directions.
        */
        gx = fabs(gx);
        gy = fabs(gy);
        if(gx<gy) {
            temp = gx;
            gx = gy;
            gy = temp;
        }
        a1 = 0.5*gy/gx;
        if (a < a1) {
            // 0 <= a < a1
            df = 0.5*(gx + gy) - sqrt(2.0*gx*gy*a);
        } else if (a < (1.0-a1)) {
            // a1 <= a <= 1-a1
            df = (0.5-a)*gx;
        } else {
            // 1-a1 < a <= 1
            df = -0.5*(gx + gy) + sqrt(2.0*gx*gy*(1.0-a));
        }
    }
    return df;
}
double distaa3(double *img, double *gximg, double *gyimg, int w, int c, int xc, int yc, int xi, int yi)
{
    double di, df, dx, dy, gx, gy, a;
    int closest;
    closest = c-xc-yc*w; // Index to the edge pixel pointed to from c
    a = img[closest];    // Grayscale value at the edge pixel
    gx = gximg[closest]; // X gradient component at the edge pixel
    gy = gyimg[closest]; // Y gradient component at the edge pixel
    if(a > 1.0) a = 1.0;
    if(a < 0.0) a = 0.0; // Clip grayscale values outside the range [0,1]
    if(a == 0.0) return 1000000.0; // Not an object pixel, return "very far" ("don't know yet")
    dx = (double)xi;
    dy = (double)yi;
    di = sqrt(dx*dx + dy*dy); // Length of integer vector, like a traditional EDT
    if(di==0) {
        // Use local gradient only at edges
        // Estimate based on local gradient only
        df = edgedf(gx, gy, a);
    } else {
        // Estimate gradient based on direction to edge (accurate for large di)
        df = edgedf(dx, dy, a);
    }
    return di + df; // Same metric as edtaa2, except at edges (where di=0)
}
// Shorthand macro: add ubiquitous parameters dist, gx, gy, img and w and call distaa3()
#define DISTAA(c,xc,yc,xi,yi) (distaa3(img, gx, gy, w, c, xc, yc, xi, yi))
void edtaa3(double *img, double *gx, double *gy, int w, int h, short *distx, short *disty, double *dist)
{
    int x, y, i, c;
    int offset_u, offset_ur, offset_r, offset_rd,
    offset_d, offset_dl, offset_l, offset_lu;
    double olddist, newdist;
    int cdistx, cdisty, newdistx, newdisty;
    int changed;
    double epsilon = 1e-3;
    /* Initialize index offsets for the current image width */
    offset_u = -w;
    offset_ur = -w+1;
    offset_r = 1;
    offset_rd = w+1;
    offset_d = w;
    offset_dl = w-1;
    offset_l = -1;
    offset_lu = -w-1;
    /* Initialize the distance images */
    for(i=0; i<w*h; i++) {
        distx[i] = 0; // At first, all pixels point to
        disty[i] = 0; // themselves as the closest known.
        if(img[i] <= 0.0)
        {
            dist[i]= 1000000.0; // Big value, means "not set yet"
        }
        else if (img[i]<1.0) {
            dist[i] = edgedf(gx[i], gy[i], img[i]); // Gradient-assisted estimate
        }
        else {
            dist[i]= 0.0; // Inside the object
        }
    }
    /* Perform the transformation */
    do
    {
        changed = 0;
        /* Scan rows, except first row */
        for(y=1; y<h; y++)
        {
            /* move index to leftmost pixel of current row */
            i = y*w;
            /* scan right, propagate distances from above & left */
            /* Leftmost pixel is special, has no left neighbors */
            olddist = dist[i];
            if(olddist > 0) // If non-zero distance or not set yet
            {
                c = i + offset_u; // Index of candidate for testing
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_ur;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            i++;
            /* Middle pixels have all neighbors */
            for(x=1; x<w-1; x++, i++)
            {
                olddist = dist[i];
                if(olddist <= 0) continue; // No need to update further
                c = i+offset_l;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_lu;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_u;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_ur;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Rightmost pixel of row is special, has no right neighbors */
            olddist = dist[i];
            if(olddist > 0) // If not already zero distance
            {
                c = i+offset_l;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_lu;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_u;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty+1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Move index to second rightmost pixel of current row. */
            /* Rightmost pixel is skipped, it has no right neighbor. */
            i = y*w + w-2;
            /* scan left, propagate distance from right */
            for(x=w-2; x>=0; x--, i--)
            {
                olddist = dist[i];
                if(olddist <= 0) continue; // Already zero distance
                c = i+offset_r;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
        }
        /* Scan rows in reverse order, except last row */
        for(y=h-2; y>=0; y--)
        {
            /* move index to rightmost pixel of current row */
            i = y*w + w-1;
            /* Scan left, propagate distances from below & right */
            /* Rightmost pixel is special, has no right neighbors */
            olddist = dist[i];
            if(olddist > 0) // If not already zero distance
            {
                c = i+offset_d;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_dl;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            i--;
            /* Middle pixels have all neighbors */
            for(x=w-2; x>0; x--, i--)
            {
                olddist = dist[i];
                if(olddist <= 0) continue; // Already zero distance
                c = i+offset_r;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_rd;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_d;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_dl;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Leftmost pixel is special, has no left neighbors */
            olddist = dist[i];
            if(olddist > 0) // If not already zero distance
            {
                c = i+offset_r;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_rd;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx-1;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    olddist=newdist;
                    changed = 1;
                }
                c = i+offset_d;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx;
                newdisty = cdisty-1;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
            /* Move index to second leftmost pixel of current row. */
            /* Leftmost pixel is skipped, it has no left neighbor. */
            i = y*w + 1;
            for(x=1; x<w; x++, i++)
            {
                /* scan right, propagate distance from left */
                olddist = dist[i];
                if(olddist <= 0) continue; // Already zero distance
                c = i+offset_l;
                cdistx = distx[c];
                cdisty = disty[c];
                newdistx = cdistx+1;
                newdisty = cdisty;
                newdist = DISTAA(c, cdistx, cdisty, newdistx, newdisty);
                if(newdist < olddist-epsilon)
                {
                    distx[i]=newdistx;
                    disty[i]=newdisty;
                    dist[i]=newdist;
                    changed = 1;
                }
            }
        }
    }
    while(changed); // Sweep until no more updates are made
    /* The transformation is completed. */
}
void _retainGLid(GLuint id) {
    GLid_s* p;
    HASH_FIND_PTR(g_GLids, &id, p);
    if (p) {
        p->refCount++;
    } else {
        p = (GLid_s*)malloc(sizeof(GLid_s));
        p->id = id;
        p->refCount = 1;
        HASH_ADD_PTR(g_GLids, id, p);    
    }
}
bool _releaseGLid(GLuint id) {
    GLid_s* p;
    HASH_FIND_PTR(g_GLids, &id, p);
    if (p) {
        p->refCount--;
        if (p->refCount == 0) {
            HASH_DEL(g_GLids, p);
            free(p);
        }
        return false;
    }
    return true;
}
char *repl_str(const char *str, const char *from, const char *to) {
    /* Adjust each of the below values to suit your needs. */
    /* Increment positions cache size initially by this number. */
    size_t cache_sz_inc = 16;
    /* Thereafter, each time capacity needs to be increased,
    * multiply the increment by this factor. */
    const size_t cache_sz_inc_factor = 3;
    /* But never increment capacity by more than this number. */
    const size_t cache_sz_inc_max = 1048576;
    char *pret, *ret = NULL;
    const char *pstr2, *pstr = str;
    size_t i, count = 0;
    #if (__STDC_VERSION__ >= 199901L)
    uintptr_t *pos_cache_tmp, *pos_cache = NULL;
    #else
    ptrdiff_t *pos_cache_tmp, *pos_cache = NULL;
    #endif
    size_t cache_sz = 0;
    size_t cpylen, orglen, retlen, tolen = 0, fromlen = strlen(from);
    /* Find all matches and cache their positions. */
    while ((pstr2 = strstr(pstr, from)) != NULL) {
        count++;
        /* Increase the cache size when necessary. */
        if (cache_sz < count) {
            cache_sz += cache_sz_inc;
            pos_cache_tmp = realloc(pos_cache, sizeof(*pos_cache) * cache_sz);
            if (pos_cache_tmp == NULL) {
                goto end_repl_str;
            } else pos_cache = pos_cache_tmp;
            cache_sz_inc *= cache_sz_inc_factor;
            if (cache_sz_inc > cache_sz_inc_max) {
                cache_sz_inc = cache_sz_inc_max;
            }
        }
        pos_cache[count-1] = pstr2 - str;
        pstr = pstr2 + fromlen;
    }
    orglen = pstr - str + strlen(pstr);
    /* Allocate memory for the post-replacement string. */
    if (count > 0) {
        tolen = strlen(to);
        retlen = orglen + (tolen - fromlen) * count;
    } else  retlen = orglen;
    ret = malloc(retlen + 1);
    if (ret == NULL) {
        goto end_repl_str;
    }
    if (count == 0) {
        /* If no matches, then just duplicate the string. */
        strcpy(ret, str);
    } else {
        /* Otherwise, duplicate the string whilst performing
        * the replacements using the position cache. */
        pret = ret;
        memcpy(pret, str, pos_cache[0]);
        pret += pos_cache[0];
        for (i = 0; i < count; i++) {
            memcpy(pret, to, tolen);
            pret += tolen;
            pstr = str + pos_cache[i] + fromlen;
            cpylen = (i == count-1 ? orglen : pos_cache[i+1]) - pos_cache[i] - fromlen;
            memcpy(pret, pstr, cpylen);
            pret += cpylen;
        }
        ret[retlen] = '\0';
    }
    end_repl_str:
    /* Free the cache and return the post-replacement string,
    * which will be NULL in the event of an error. */
    free(pos_cache);
    return ret;
}
// ------------------------------------------------------------ shader_read ---
char *
shader_read( const char *filename )
{
    FILE * file;
    char * buffer;
    size_t size;
    #ifdef WIN32
    errno_t err;
    if( (err  = fopen_s( &file, filename, "rb" )) !=0 ) {
        #else
        file = fopen( filename, "rb" );
        if( !file ) {
            #endif
            fprintf( stderr, "Unable to open file \"%s\".\n", filename );
            return 0;
        }
        fseek( file, 0, SEEK_END );
        size = ftell( file );
        fseek(file, 0, SEEK_SET );
        buffer = (char *) malloc( (size+1) * sizeof( char *) );
        fread( buffer, sizeof(char), size, file );
        buffer[size] = 0;
        fclose( file );
        #ifdef __APPLE__
        char* prev = buffer;
        buffer = repl_str(buffer, "mediump", "");
        free(prev);
        #endif
        return buffer;
    }
    // --------------------------------------------------------- shader_compile ---
    GLuint
    shader_compile( const char* source,
    const GLenum type )
    {
        GLint compile_status;
        GLuint handle = glCreateShader( type );
        glShaderSource( handle, 1, &source, 0 );
        glCompileShader( handle );
        glGetShaderiv( handle, GL_COMPILE_STATUS, &compile_status );
        if( compile_status == GL_FALSE )
        {
            GLchar messages[256];
            glGetShaderInfoLog( handle, sizeof(messages), 0, &messages[0] );
            halt("%s: %s\n", source, messages);
        }
        return handle;
    }
    // ------------------------------------------------------------ shader_load ---
    GLuint
    shader_load( const char * vert_filename,
    const char * frag_filename )
    {
        GLuint handle = glCreateProgram( );
        GLint link_status;
        if( vert_filename && strlen( vert_filename ) )
        {
            char *vert_source = shader_read( vert_filename );
            GLuint vert_shader = shader_compile( vert_source, GL_VERTEX_SHADER);
            glAttachShader( handle, vert_shader);
            glDeleteShader( vert_shader );
            free( vert_source );
        }
        if( frag_filename && strlen( frag_filename ) )
        {
            char *frag_source = shader_read( frag_filename );
            GLuint frag_shader = shader_compile( frag_source, GL_FRAGMENT_SHADER);
            glAttachShader( handle, frag_shader);
            glDeleteShader( frag_shader );
            free( frag_source );
        }
        glLinkProgram( handle );
        glGetProgramiv( handle, GL_LINK_STATUS, &link_status );
        if (link_status == GL_FALSE)
        {
            GLchar messages[256];
            glGetProgramInfoLog( handle, sizeof(messages), 0, &messages[0] );
            halt("%s\n", messages );
        }
        return handle;
    }
    void add_text(vertex_buffer_t * buffer, texture_font_t * font, char *text, vec4 * color, vec2 * pen) {
        pen->y += (float)(int)font->ascender;
        size_t i;
        float r = color->red, g = color->green, b = color->blue, a = color->alpha;
        for (i = 0; i < strlen(text); ++i) {
            texture_glyph_t *glyph = texture_font_get_glyph( font, text + i );
            if (glyph != NULL) {
                float kerning = 0.0f;
                if( i > 0) {
                    kerning = texture_glyph_get_kerning( glyph, text + i - 1 );
                }
                pen->x += kerning;
                float x0 = (float)(int)( pen->x + glyph->offset_x );
                float y0 = (float)(int)( pen->y + glyph->height - glyph->offset_y );
                float x1 = (float)(int)( x0 + glyph->width );
                float y1 = (float)(int)( y0 - glyph->height );
                float s0 = glyph->s0;
                float t0 = glyph->t0;
                float s1 = glyph->s1;
                float t1 = glyph->t1;
                GLuint index = (GLuint)buffer->vertices->size;
                GLuint indices[] = { //
                index, index+1, index+2,
                index, index+2, index+3 };
                vertex3_texture2_color3_t vertices[] = { //
                { x0, y1, 0.0f,  s0,t0,  r,g,b,a },
                { x0, y0, 0.0f,  s0,t1,  r,g,b,a },
                { x1, y0, 0.0f,  s1,t1,  r,g,b,a },
                { x1, y1, 0.0f,  s1,t0,  r,g,b,a } };
                vertex_buffer_push_back_indices( buffer, indices, 6 );
                vertex_buffer_push_back_vertices( buffer, vertices, 4 );
                pen->x += glyph->advance_x;
            }
        }
    }	
    vec2 get_text_size(texture_font_t * font, char *text) {
        vec2 size = {{ 0, font->height }};
        size_t i;
        for( i = 0; i < strlen(text); ++i ) {
            texture_glyph_t *glyph = texture_font_get_glyph(font, text + i);
            if (glyph != NULL) {
                float kerning = 0.0f;
                if( i > 0) {
                    kerning = texture_glyph_get_kerning(glyph, text + i - 1);
                }
                size.x += kerning;
                size.x += glyph->advance_x;
            }
        }
        return size;
    }   
    GLuint png_texture_load(const char * file_name, int * width, int * height)
    {
        // This function was originally written by David Grayson for
        // https://github.com/DavidEGrayson/ahrs-visualizer
        png_byte header[8];
        FILE *fp = fopen(file_name, "rb");
        if (fp == 0)
        {
            perror(file_name);
            return 0;
        }
        // read the header
        fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
        {
            fprintf(stderr, "error: %s is not a PNG.\n", file_name);
            fclose(fp);
            return 0;
        }
        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr)
        {
            fprintf(stderr, "error: png_create_read_struct returned 0.\n");
            fclose(fp);
            return 0;
        }
        // create png info struct
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
        {
            fprintf(stderr, "error: png_create_info_struct returned 0.\n");
            png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
            fclose(fp);
            return 0;
        }
        // create png info struct
        png_infop end_info = png_create_info_struct(png_ptr);
        if (!end_info)
        {
            fprintf(stderr, "error: png_create_info_struct returned 0.\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
            fclose(fp);
            return 0;
        }
        // the code in this if statement gets called if libpng encounters an error
        if (setjmp(png_jmpbuf(png_ptr))) {
            fprintf(stderr, "error from libpng\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return 0;
        }
        // init png reading
        png_init_io(png_ptr, fp);
        // let libpng know you already read the first 8 bytes
        png_set_sig_bytes(png_ptr, 8);
        // read all the info up to the image data
        png_read_info(png_ptr, info_ptr);
        // variables to pass to get info
        int bit_depth, color_type;
        png_uint_32 temp_width, temp_height;
        // get info about png
        png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);
        if (width){ *width = temp_width; }
        if (height){ *height = temp_height; }
        //printf("%s: %lux%lu %d\n", file_name, temp_width, temp_height, color_type);
        if (bit_depth != 8)
        {
            fprintf(stderr, "%s: Unsupported bit depth %d.  Must be 8.\n", file_name, bit_depth);
            return 0;
        }
        GLint format;
        switch(color_type)
        {
            case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            break;
            case PNG_COLOR_TYPE_RGB_ALPHA:
            format = GL_RGBA;
            break;
            default:
            fprintf(stderr, "%s: Unknown libpng color type %d.\n", file_name, color_type);
            return 0;
        }
        // Update the png info struct.
        png_read_update_info(png_ptr, info_ptr);
        // Row size in bytes.
        int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
        // glTexImage2d requires rows to be 4-byte aligned
        rowbytes += 3 - ((rowbytes-1) % 4);
        // Allocate the image_data as a big block, to be given to opengl
        png_byte * image_data = (png_byte *)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
        if (image_data == NULL)
        {
            fprintf(stderr, "error: could not allocate memory for PNG image data\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            fclose(fp);
            return 0;
        }
        // row_pointers is for pointing to image_data for reading the png with libpng
        png_byte ** row_pointers = (png_byte **)malloc(temp_height * sizeof(png_byte *));
        if (row_pointers == NULL)
        {
            fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            free(image_data);
            fclose(fp);
            return 0;
        }
        // set the individual row_pointers to point at the correct offsets of image_data
        for (unsigned int i = 0; i < temp_height; i++)
        {
            row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
        }
        // read the png into image_data through row_pointers
        png_read_image(png_ptr, row_pointers);
        // Generate the OpenGL texture object
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexImage2D(GL_TEXTURE_2D, 0, format, temp_width, temp_height, 0, format, GL_UNSIGNED_BYTE, image_data);
        // clean up
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        free(row_pointers);
        fclose(fp);
        return texture;
    }
    // ------------------------------------------------------ texture_atlas_new ---
    texture_atlas_t *
    texture_atlas_new( const size_t width,
    const size_t height,
    const size_t depth )
    {
        texture_atlas_t *self = (texture_atlas_t *) malloc( sizeof(texture_atlas_t) );
        // We want a one pixel border around the whole atlas to avoid any artefact when
        // sampling texture
        ivec3 node = {{1,1,width-2}};
        assert( (depth == 1) || (depth == 3) || (depth == 4) );
        if( self == NULL)
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        self->nodes = vector_new( sizeof(ivec3) );
        self->used = 0;
        self->width = width;
        self->height = height;
        self->depth = depth;
        self->id = 0;
        vector_push_back( self->nodes, &node );
        self->data = (unsigned char *)
        calloc( width*height*depth, sizeof(unsigned char) );
        if( self->data == NULL)
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        return self;
    }
    // --------------------------------------------------- texture_atlas_delete ---
    void
    texture_atlas_delete( texture_atlas_t *self )
    {
        assert( self );
        vector_delete( self->nodes );
        if( self->data )
        {
            free( self->data );
        }
        free( self );
    }
    // ----------------------------------------------- texture_atlas_set_region ---
    void
    texture_atlas_set_region( texture_atlas_t * self,
    const size_t x,
    const size_t y,
    const size_t width,
    const size_t height,
    const unsigned char * data,
    const size_t stride )
    {
        size_t i;
        size_t depth;
        size_t charsize;
        assert( self );
        assert( x > 0);
        assert( y > 0);
        assert( x < (self->width-1));
        assert( (x + width) <= (self->width-1));
        assert( y < (self->height-1));
        assert( (y + height) <= (self->height-1));
        //prevent copying data from undefined position 
        //and prevent memcpy's undefined behavior when count is zero
        assert(height == 0 || (data != NULL && width > 0));
        depth = self->depth;
        charsize = sizeof(char);
        for( i=0; i<height; ++i )
        {
            memcpy( self->data+((y+i)*self->width + x ) * charsize * depth,
            data + (i*stride) * charsize, width * charsize * depth  );
        }
    }
    // ------------------------------------------------------ texture_atlas_fit ---
    int
    texture_atlas_fit( texture_atlas_t * self,
    const size_t index,
    const size_t width,
    const size_t height )
    {
        ivec3 *node;
        int x, y, width_left;
        size_t i;
        assert( self );
        node = (ivec3 *) (vector_get( self->nodes, index ));
        x = node->x;
        y = node->y;
        width_left = width;
        i = index;
        if ( (x + width) > (self->width-1) )
        {
            return -1;
        }
        y = node->y;
        while( width_left > 0 )
        {
            node = (ivec3 *) (vector_get( self->nodes, i ));
            if( node->y > y )
            {
                y = node->y;
            }
            if( (y + height) > (self->height-1) )
            {
                return -1;
            }
            width_left -= node->z;
            ++i;
        }
        return y;
    }
    // ---------------------------------------------------- texture_atlas_merge ---
    void
    texture_atlas_merge( texture_atlas_t * self )
    {
        ivec3 *node, *next;
        size_t i;
        assert( self );
        for( i=0; i< self->nodes->size-1; ++i )
        {
            node = (ivec3 *) (vector_get( self->nodes, i ));
            next = (ivec3 *) (vector_get( self->nodes, i+1 ));
            if( node->y == next->y )
            {
                node->z += next->z;
                vector_erase( self->nodes, i+1 );
                --i;
            }
        }
    }
    // ----------------------------------------------- texture_atlas_get_region ---
    ivec4
    texture_atlas_get_region( texture_atlas_t * self,
    const size_t width,
    const size_t height )
    {
        int y, best_index;
        size_t best_height, best_width;
        ivec3 *node, *prev;
        ivec4 region = {{0,0,width,height}};
        size_t i;
        assert( self );
        best_height = UINT_MAX;
        best_index  = -1;
        best_width = UINT_MAX;
        for( i=0; i<self->nodes->size; ++i )
        {
            y = texture_atlas_fit( self, i, width, height );
            if( y >= 0 )
            {
                node = (ivec3 *) vector_get( self->nodes, i );
                if( ( (y + height) < best_height ) ||
                ( ((y + height) == best_height) && (node->z > 0 && (size_t)node->z < best_width)) )
                {
                    best_height = y + height;
                    best_index = i;
                    best_width = node->z;
                    region.x = node->x;
                    region.y = y;
                }
            }
        }
        if( best_index == -1 )
        {
            region.x = -1;
            region.y = -1;
            region.width = 0;
            region.height = 0;
            return region;
        }
        node = (ivec3 *) malloc( sizeof(ivec3) );
        if( node == NULL)
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        node->x = region.x;
        node->y = region.y + height;
        node->z = width;
        vector_insert( self->nodes, best_index, node );
        free( node );
        for(i = best_index+1; i < self->nodes->size; ++i)
        {
            node = (ivec3 *) vector_get( self->nodes, i );
            prev = (ivec3 *) vector_get( self->nodes, i-1 );
            if (node->x < (prev->x + prev->z) )
            {
                int shrink = prev->x + prev->z - node->x;
                node->x += shrink;
                node->z -= shrink;
                if (node->z <= 0)
                {
                    vector_erase( self->nodes, i );
                    --i;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
        texture_atlas_merge( self );
        self->used += width * height;
        return region;
    }
    // ---------------------------------------------------- texture_atlas_clear ---
    void
    texture_atlas_clear( texture_atlas_t * self )
    {
        ivec3 node = {{1,1,1}};
        assert( self );
        assert( self->data );
        vector_clear( self->nodes );
        self->used = 0;
        // We want a one pixel border around the whole atlas to avoid any artefact when
        // sampling texture
        node.z = self->width-2;
        vector_push_back( self->nodes, &node );
        memset( self->data, 0, self->width*self->height*self->depth );
    }
    #define HRES  64
    #define HRESf 64.f
    #define DPI   72
    // ------------------------------------------------- texture_font_load_face ---
    static int
    texture_font_load_face(texture_font_t *self, float size,
    FT_Library *library, FT_Face *face)
    {
        FT_Error error;
        FT_Matrix matrix = { //
        (int)((1.0/HRES) * 0x10000L),
        (int)((0.0)      * 0x10000L),
        (int)((0.0)      * 0x10000L),
        (int)((1.0)      * 0x10000L)};
        assert(library);
        assert(size);
        /* Initialize library */
        error = FT_Init_FreeType(library);
        if(error) {
            fprintf(stderr, "FT_Error (0x%02x) : %s\n",
            FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup;
        }
        /* Load face */
        switch (self->location) {
            case TEXTURE_FONT_FILE:
            error = FT_New_Face(*library, self->filename, 0, face);
            break;
            case TEXTURE_FONT_MEMORY:
            error = FT_New_Memory_Face(*library,
            self->memory.base, self->memory.size, 0, face);
            break;
        }
        if(error) {
            fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup_library;
        }
        /* Select charmap */
        error = FT_Select_Charmap(*face, FT_ENCODING_UNICODE);
        if(error) {
            fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup_face;
        }
        /* Set char size */
        error = FT_Set_Char_Size(*face, (int)(size * HRES), 0, DPI * HRES, DPI);
        if(error) {
            fprintf(stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message);
            goto cleanup_face;
        }
        /* Set transform matrix */
        FT_Set_Transform(*face, &matrix, NULL);
        return 1;
        cleanup_face:
        FT_Done_Face( *face );
        cleanup_library:
        FT_Done_FreeType( *library );
        cleanup:
        return 0;
    }
    // ------------------------------------------------------ texture_glyph_new ---
    texture_glyph_t *
    texture_glyph_new(void)
    {
        texture_glyph_t *self = (texture_glyph_t *) malloc( sizeof(texture_glyph_t) );
        if(self == NULL) {
            fprintf( stderr,
            "line %d: No more memory for allocating data\n", __LINE__);
            return NULL;
        }
        self->codepoint  = -1;
        self->width     = 0;
        self->height    = 0;
        self->rendermode = RENDER_NORMAL;
        self->outline_thickness = 0.0;
        self->offset_x  = 0;
        self->offset_y  = 0;
        self->advance_x = 0.0;
        self->advance_y = 0.0;
        self->s0        = 0.0;
        self->t0        = 0.0;
        self->s1        = 0.0;
        self->t1        = 0.0;
        self->kerning   = vector_new( sizeof(kerning_t) );
        return self;
    }
    // --------------------------------------------------- texture_glyph_delete ---
    void
    texture_glyph_delete( texture_glyph_t *self )
    {
        assert( self );
        vector_delete( self->kerning );
        free( self );
    }
    // ---------------------------------------------- texture_glyph_get_kerning ---
    float
    texture_glyph_get_kerning( const texture_glyph_t * self,
    const char * codepoint )
    {
        size_t i;
        uint32_t ucodepoint = utf8_to_utf32( codepoint );
        assert( self );
        for( i=0; i<vector_size(self->kerning); ++i )
        {
            kerning_t * kerning = (kerning_t *) vector_get( self->kerning, i );
            if( kerning->codepoint == ucodepoint )
            {
                return kerning->kerning;
            }
        }
        return 0;
    }
    // ------------------------------------------ texture_font_generate_kerning ---
    void
    texture_font_generate_kerning( texture_font_t *self,
    FT_Library *library, FT_Face *face )
    {
        size_t i, j;
        FT_UInt glyph_index, prev_index;
        texture_glyph_t *glyph, *prev_glyph;
        FT_Vector kerning;
        assert( self );
        /* For each glyph couple combination, check if kerning is necessary */
        /* Starts at index 1 since 0 is for the special backgroudn glyph */
        for( i=1; i<self->glyphs->size; ++i )
        {
            glyph = *(texture_glyph_t **) vector_get( self->glyphs, i );
            glyph_index = FT_Get_Char_Index( *face, glyph->codepoint );
            vector_clear( glyph->kerning );
            for( j=1; j<self->glyphs->size; ++j )
            {
                prev_glyph = *(texture_glyph_t **) vector_get( self->glyphs, j );
                prev_index = FT_Get_Char_Index( *face, prev_glyph->codepoint );
                FT_Get_Kerning( *face, prev_index, glyph_index, FT_KERNING_UNFITTED, &kerning );
                // printf("%c(%d)-%c(%d): %ld\n",
                //       prev_glyph->codepoint, prev_glyph->codepoint,
                //       glyph_index, glyph_index, kerning.x);
                if( kerning.x )
                {
                    kerning_t k = {prev_glyph->codepoint, kerning.x / (float)(HRESf*HRESf)};
                    vector_push_back( glyph->kerning, &k );
                }
            }
        }
    }
    // ------------------------------------------------------ texture_font_init ---
    static int
    texture_font_init(texture_font_t *self)
    {
        FT_Library library;
        FT_Face face;
        FT_Size_Metrics metrics;
        assert(self->atlas);
        assert(self->size > 0);
        assert((self->location == TEXTURE_FONT_FILE && self->filename)
        || (self->location == TEXTURE_FONT_MEMORY
        && self->memory.base && self->memory.size));
        self->glyphs = vector_new(sizeof(texture_glyph_t *));
        self->height = 0;
        self->ascender = 0;
        self->descender = 0;
        self->rendermode = RENDER_NORMAL;
        self->outline_thickness = 0.0;
        self->hinting = 1;
        self->kerning = 1;
        self->filtering = 1;
        // FT_LCD_FILTER_LIGHT   is (0x00, 0x55, 0x56, 0x55, 0x00)
        // FT_LCD_FILTER_DEFAULT is (0x10, 0x40, 0x70, 0x40, 0x10)
        self->lcd_weights[0] = 0x10;
        self->lcd_weights[1] = 0x40;
        self->lcd_weights[2] = 0x70;
        self->lcd_weights[3] = 0x40;
        self->lcd_weights[4] = 0x10;
        if (!texture_font_load_face(self, self->size * 100.f, &library, &face))
        return -1;
        self->underline_position = face->underline_position / (float)(HRESf*HRESf) * self->size;
        self->underline_position = roundf( self->underline_position );
        if( self->underline_position > -2 )
        {
            self->underline_position = -2.0;
        }
        self->underline_thickness = face->underline_thickness / (float)(HRESf*HRESf) * self->size;
        self->underline_thickness = roundf( self->underline_thickness );
        if( self->underline_thickness < 1 )
        {
            self->underline_thickness = 1.0;
        }
        metrics = face->size->metrics;
        self->ascender = (metrics.ascender >> 6) / 100.0f;
        self->descender = (metrics.descender >> 6) / 100.0f;
        self->height = (metrics.height >> 6) / 100.0f;
        self->linegap = self->height - self->ascender + self->descender;
        FT_Done_Face( face );
        FT_Done_FreeType( library );
        /* NULL is a special glyph */
        texture_font_get_glyph( self, NULL );
        return 0;
    }
    // --------------------------------------------- texture_font_new_from_file ---
    texture_font_t *
    texture_font_new_from_file(texture_atlas_t *atlas, const float pt_size,
    const char *filename)
    {
        texture_font_t *self;
        assert(filename);
        self = calloc(1, sizeof(*self));
        if (!self) {
            fprintf(stderr,
            "line %d: No more memory for allocating data\n", __LINE__);
            return NULL;
        }
        self->atlas = atlas;
        self->size  = pt_size;
        self->location = TEXTURE_FONT_FILE;
        self->filename = strdup(filename);
        if (texture_font_init(self)) {
            texture_font_delete(self);
            return NULL;
        }
        return self;
    }
    // ------------------------------------------- texture_font_new_from_memory ---
    texture_font_t *
    texture_font_new_from_memory(texture_atlas_t *atlas, float pt_size,
    const void *memory_base, size_t memory_size)
    {
        texture_font_t *self;
        assert(memory_base);
        assert(memory_size);
        self = calloc(1, sizeof(*self));
        if (!self) {
            fprintf(stderr,
            "line %d: No more memory for allocating data\n", __LINE__);
            return NULL;
        }
        self->atlas = atlas;
        self->size  = pt_size;
        self->location = TEXTURE_FONT_MEMORY;
        self->memory.base = memory_base;
        self->memory.size = memory_size;
        if (texture_font_init(self)) {
            texture_font_delete(self);
            return NULL;
        }
        return self;
    }
    // ---------------------------------------------------- texture_font_delete ---
    void
    texture_font_delete( texture_font_t *self )
    {
        size_t i;
        texture_glyph_t *glyph;
        assert( self );
        if(self->location == TEXTURE_FONT_FILE && self->filename)
        free( self->filename );
        for( i=0; i<vector_size( self->glyphs ); ++i)
        {
            glyph = *(texture_glyph_t **) vector_get( self->glyphs, i );
            texture_glyph_delete( glyph);
        }
        vector_delete( self->glyphs );
        free( self );
    }
    texture_glyph_t *
    texture_font_find_glyph( texture_font_t * self,
    const char * codepoint )
    {
        size_t i;
        texture_glyph_t *glyph;
        uint32_t ucodepoint = utf8_to_utf32( codepoint );
        for( i = 0; i < self->glyphs->size; ++i )
        {
            glyph = *(texture_glyph_t **) vector_get( self->glyphs, i );
            // If codepoint is -1, we don't care about outline type or thickness
            if( (glyph->codepoint == ucodepoint) &&
            ((ucodepoint == -1) ||
            ((glyph->rendermode == self->rendermode) &&
            (glyph->outline_thickness == self->outline_thickness)) ))
            {
                return glyph;
            }
        }
        return NULL;
    }
    // ------------------------------------------------ texture_font_load_glyph ---
    int
    texture_font_load_glyph( texture_font_t * self,
    const char * codepoint )
    {
        size_t i, x, y;
        FT_Library library;
        FT_Error error;
        FT_Face face;
        FT_Glyph ft_glyph = { 0 };
        FT_GlyphSlot slot;
        FT_Bitmap ft_bitmap;
        FT_UInt glyph_index;
        texture_glyph_t *glyph;
        FT_Int32 flags = 0;
        int ft_glyph_top = 0;
        int ft_glyph_left = 0;
        ivec4 region;
        if (!texture_font_load_face(self, self->size, &library, &face))
        return 0;
        /* Check if codepoint has been already loaded */
        if (texture_font_find_glyph(self, codepoint)) {
            FT_Done_Face(face);
            FT_Done_FreeType(library);
            return 1;
        }
        /* codepoint NULL is special : it is used for line drawing (overline,
        * underline, strikethrough) and background.
        */
        if( !codepoint )
        {
            ivec4 region = texture_atlas_get_region( self->atlas, 5, 5 );
            texture_glyph_t * glyph = texture_glyph_new( );
            static unsigned char data[4*4*3] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
            if ( region.x < 0 )
            {
                fprintf( stderr, "Texture atlas is full (line %d)\n",  __LINE__ );
                FT_Done_Face( face );
                FT_Done_FreeType( library );
                return 0;
            }
            texture_atlas_set_region( self->atlas, region.x, region.y, 4, 4, data, 0 );
            glyph->codepoint = -1;
            glyph->s0 = (region.x+2)/(float)self->atlas->width;
            glyph->t0 = (region.y+2)/(float)self->atlas->height;
            glyph->s1 = (region.x+3)/(float)self->atlas->width;
            glyph->t1 = (region.y+3)/(float)self->atlas->height;
            vector_push_back( self->glyphs, &glyph );
            FT_Done_Face(face);
            FT_Done_FreeType(library);
            return 1;
        }
        flags = 0;
        ft_glyph_top = 0;
        ft_glyph_left = 0;
        glyph_index = FT_Get_Char_Index( face, (FT_ULong)utf8_to_utf32( codepoint ) );
        // WARNING: We use texture-atlas depth to guess if user wants
        //          LCD subpixel rendering
        if( self->rendermode != RENDER_NORMAL && self->rendermode != RENDER_SIGNED_DISTANCE_FIELD )
        {
            flags |= FT_LOAD_NO_BITMAP;
        }
        else
        {
            flags |= FT_LOAD_RENDER;
        }
        if( !self->hinting )
        {
            flags |= FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT;
        }
        else
        {
            flags |= FT_LOAD_FORCE_AUTOHINT;
        }
        if( self->atlas->depth == 3 )
        {
            FT_Library_SetLcdFilter( library, FT_LCD_FILTER_LIGHT );
            flags |= FT_LOAD_TARGET_LCD;
            if( self->filtering )
            {
                FT_Library_SetLcdFilterWeights( library, self->lcd_weights );
            }
        }
        error = FT_Load_Glyph( face, glyph_index, flags );
        if( error )
        {
            fprintf( stderr, "FT_Error (line %d, code 0x%02x) : %s\n",
            __LINE__, FT_Errors[error].code, FT_Errors[error].message );
            FT_Done_Face( face );
            FT_Done_FreeType( library );
            return 0;
        }
        if( self->rendermode == RENDER_NORMAL || self->rendermode == RENDER_SIGNED_DISTANCE_FIELD )
        {
            slot            = face->glyph;
            ft_bitmap       = slot->bitmap;
            ft_glyph_top    = slot->bitmap_top;
            ft_glyph_left   = slot->bitmap_left;
        }
        else
        {
            FT_Stroker stroker;
            FT_BitmapGlyph ft_bitmap_glyph;
            error = FT_Stroker_New( library, &stroker );
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            FT_Stroker_Set(stroker,
            (int)(self->outline_thickness * HRES),
            FT_STROKER_LINECAP_ROUND,
            FT_STROKER_LINEJOIN_ROUND,
            0);
            error = FT_Get_Glyph( face->glyph, &ft_glyph);
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            if( self->rendermode == RENDER_OUTLINE_EDGE )
            error = FT_Glyph_Stroke( &ft_glyph, stroker, 1 );
            else if ( self->rendermode == RENDER_OUTLINE_POSITIVE )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 0, 1 );
            else if ( self->rendermode == RENDER_OUTLINE_NEGATIVE )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 1, 1 );
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            if( self->atlas->depth == 1 )
            error = FT_Glyph_To_Bitmap( &ft_glyph, FT_RENDER_MODE_NORMAL, 0, 1);
            else
            error = FT_Glyph_To_Bitmap( &ft_glyph, FT_RENDER_MODE_LCD, 0, 1);
            if( error )
            {
                fprintf(stderr, "FT_Error (0x%02x) : %s\n",
                FT_Errors[error].code, FT_Errors[error].message);
                goto cleanup_stroker;
            }
            ft_bitmap_glyph = (FT_BitmapGlyph) ft_glyph;
            ft_bitmap       = ft_bitmap_glyph->bitmap;
            ft_glyph_top    = ft_bitmap_glyph->top;
            ft_glyph_left   = ft_bitmap_glyph->left;
            cleanup_stroker:
            FT_Stroker_Done( stroker );
            if( error )
            {
                FT_Done_Face( face );
                FT_Done_FreeType( library );
                return 0;
            }
        }
        struct {
            int left;
            int top;
            int right;
            int bottom;
        } padding = { 0, 0, 1, 1 };
        if( self->rendermode == RENDER_SIGNED_DISTANCE_FIELD )
        {
            padding.top = 1;
            padding.left = 1;
        }
        size_t src_w = ft_bitmap.width/self->atlas->depth;
        size_t src_h = ft_bitmap.rows;
        size_t tgt_w = src_w + padding.left + padding.right;
        size_t tgt_h = src_h + padding.top + padding.bottom;
        region = texture_atlas_get_region( self->atlas, tgt_w, tgt_h );
        if ( region.x < 0 )
        {
            fprintf( stderr, "Texture atlas is full (line %d)\n",  __LINE__ );
            FT_Done_Face( face );
            FT_Done_FreeType( library );
            return 0;
        }
        x = region.x;
        y = region.y;
        unsigned char *buffer = calloc( tgt_w * tgt_h * self->atlas->depth, sizeof(unsigned char) );
        unsigned char *dst_ptr = buffer + (padding.top * tgt_w + padding.left) * self->atlas->depth;
        unsigned char *src_ptr = ft_bitmap.buffer;
        for( i = 0; i < src_h; i++ )
        {
            //difference between width and pitch: https://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html
            memcpy( dst_ptr, src_ptr, ft_bitmap.width);
            dst_ptr += tgt_w * self->atlas->depth;
            src_ptr += ft_bitmap.pitch;
        }
        if( self->rendermode == RENDER_SIGNED_DISTANCE_FIELD )
        {
            unsigned char *sdf = make_distance_mapb( buffer, (unsigned int)tgt_w, (unsigned int)tgt_h );
            free( buffer );
            buffer = sdf;
        }
        texture_atlas_set_region( self->atlas, x, y, tgt_w, tgt_h, buffer, tgt_w * self->atlas->depth);
        free( buffer );
        glyph = texture_glyph_new( );
        glyph->codepoint = utf8_to_utf32( codepoint );
        glyph->width    = tgt_w;
        glyph->height   = tgt_h;
        glyph->rendermode = self->rendermode;
        glyph->outline_thickness = self->outline_thickness;
        glyph->offset_x = ft_glyph_left;
        glyph->offset_y = ft_glyph_top;
        glyph->s0       = x/(float)self->atlas->width;
        glyph->t0       = y/(float)self->atlas->height;
        glyph->s1       = (x + glyph->width)/(float)self->atlas->width;
        glyph->t1       = (y + glyph->height)/(float)self->atlas->height;
        // Discard hinting to get advance
        FT_Load_Glyph( face, glyph_index, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
        slot = face->glyph;
        glyph->advance_x = slot->advance.x / HRESf;
        glyph->advance_y = slot->advance.y / HRESf;
        vector_push_back( self->glyphs, &glyph );
        if( self->rendermode != RENDER_NORMAL && self->rendermode != RENDER_SIGNED_DISTANCE_FIELD )
        FT_Done_Glyph( ft_glyph );
        texture_font_generate_kerning( self, &library, &face );
        FT_Done_Face( face );
        FT_Done_FreeType( library );
        return 1;
    }
    // ----------------------------------------------- texture_font_load_glyphs ---
    size_t
    texture_font_load_glyphs( texture_font_t * self,
    const char * codepoints )
    {
        size_t i;
        /* Load each glyph */
        for( i = 0; i < strlen(codepoints); i += utf8_surrogate_len(codepoints + i) ) {
            if( !texture_font_load_glyph( self, codepoints + i ) )
            return utf8_strlen( codepoints + i );
        }
        return 0;
    }
    // ------------------------------------------------- texture_font_get_glyph ---
    texture_glyph_t *
    texture_font_get_glyph( texture_font_t * self,
    const char * codepoint )
    {
        texture_glyph_t *glyph;
        assert( self );
        assert( self->filename );
        assert( self->atlas );
        /* Check if codepoint has been already loaded */
        if( (glyph = texture_font_find_glyph( self, codepoint )) )
        return glyph;
        /* Glyph has not been already loaded */
        if( texture_font_load_glyph( self, codepoint ) )
        return texture_font_find_glyph( self, codepoint );
        return NULL;
    }
    // ------------------------------------------------- texture_font_enlarge_atlas ---
    void
    texture_font_enlarge_atlas( texture_font_t * self, size_t width_new,
    size_t height_new)
    {
        assert(self);
        assert(self->atlas);
        //ensure size increased
        assert(width_new >= self->atlas->width);
        assert(height_new >= self->atlas->height);
        assert(width_new + height_new > self->atlas->width + self->atlas->height);
        texture_atlas_t* ta = self->atlas;
        size_t width_old = ta->width;
        size_t height_old = ta->height;
        //allocate new buffer
        unsigned char* data_old = ta->data;
        ta->data = calloc(1,width_new*height_new * sizeof(char)*ta->depth);
        //update atlas size
        ta->width = width_new;
        ta->height = height_new;
        //add node reflecting the gained space on the right
        if(width_new>width_old){
            ivec3 node;
            node.x = width_old - 1;
            node.y = 1;
            node.z = width_new - width_old;
            vector_push_back(ta->nodes, &node);
        }
        //copy over data from the old buffer, skipping first row and column because of the margin
        size_t pixel_size = sizeof(char) * ta->depth;
        size_t old_row_size = width_old * pixel_size;
        texture_atlas_set_region(ta, 1, 1, width_old - 2, height_old - 2, data_old + old_row_size + pixel_size, old_row_size);
        free(data_old);
        //change uv coordinates of existing glyphs to reflect size change
        float mulw = (float)width_old / width_new;
        float mulh = (float)height_old / height_new;
        size_t i;
        for (i = 0; i < vector_size(self->glyphs); i++) {
            texture_glyph_t* g = *(texture_glyph_t**)vector_get(self->glyphs, i);
            g->s0 *= mulw;
            g->s1 *= mulw;
            g->t0 *= mulh;
            g->t1 *= mulh;
        }
    }
    // ----------------------------------------------------- utf8_surrogate_len ---
    size_t
    utf8_surrogate_len( const char* character )
    {
        size_t result = 0;
        char test_char;
        if (!character)
        return 0;
        test_char = character[0];
        if ((test_char & 0x80) == 0)
        return 1;
        while (test_char & 0x80)
        {
            test_char <<= 1;
            result++;
        }
        return result;
    }
    // ------------------------------------------------------------ utf8_strlen ---
    size_t
    utf8_strlen( const char* string )
    {
        const char* ptr = string;
        size_t result = 0;
        while (*ptr)
        {
            ptr += utf8_surrogate_len(ptr);
            result++;
        }
        return result;
    }
    uint32_t
    utf8_to_utf32( const char * character )
    {
        uint32_t result = -1;
        if( !character )
        {
            return result;
        }
        if( ( character[0] & 0x80 ) == 0x0 )
        {
            result = character[0];
        }
        if( ( character[0] & 0xC0 ) == 0xC0 )
        {
            result = ( ( character[0] & 0x3F ) << 6 ) | ( character[1] & 0x3F );
        }
        if( ( character[0] & 0xE0 ) == 0xE0 )
        {
            result = ( ( character[0] & 0x1F ) << ( 6 + 6 ) ) | ( ( character[1] & 0x3F ) << 6 ) | ( character[2] & 0x3F );
        }
        if( ( character[0] & 0xF0 ) == 0xF0 )
        {
            result = ( ( character[0] & 0x0F ) << ( 6 + 6 + 6 ) ) | ( ( character[1] & 0x3F ) << ( 6 + 6 ) ) | ( ( character[2] & 0x3F ) << 6 ) | ( character[3] & 0x3F );
        }
        if( ( character[0] & 0xF8 ) == 0xF8 )
        {
            result = ( ( character[0] & 0x07 ) << ( 6 + 6 + 6 + 6 ) ) | ( ( character[1] & 0x3F ) << ( 6 + 6 + 6 ) ) | ( ( character[2] & 0x3F ) << ( 6 + 6 ) ) | ( ( character[3] & 0x3F ) << 6 ) | ( character[4] & 0x3F );
        }
        return result;
    }
    // ------------------------------------------------------------- vector_new ---
    vector_t *
    vector_new( size_t item_size )
    {
        vector_t *self = (vector_t *) malloc( sizeof(vector_t) );
        assert( item_size );
        if( !self )
        {
            halt("line %d: No more memory for allocating data\n", __LINE__ );
        }
        self->item_size = item_size;
        self->size      = 0;
        self->capacity  = 1;
        self->items     = malloc( self->item_size * self->capacity );
        return self;
    }
    // ---------------------------------------------------------- vector_delete ---
    void
    vector_delete( vector_t *self )
    {
        assert( self );
        free( self->items );
        free( self );
    }
    // ------------------------------------------------------------- vector_get ---
    const void *
    vector_get( const vector_t *self,
    size_t index )
    {
        assert( self );
        assert( self->size );
        assert( index  < self->size );
        return (char*)(self->items) + index * self->item_size;
    }
    // ----------------------------------------------------------- vector_front ---
    const void *
    vector_front( const vector_t *self )
    {
        assert( self );
        assert( self->size );
        return vector_get( self, 0 );
    }
    // ------------------------------------------------------------ vector_back ---
    const void *
    vector_back( const vector_t *self )
    {
        assert( self );
        assert( self->size );
        return vector_get( self, self->size-1 );
    }
    // -------------------------------------------------------- vector_contains ---
    int
    vector_contains( const vector_t *self,
    const void *item,
    int (*cmp)(const void *, const void *) )
    {
        size_t i;
        assert( self );
        for( i=0; i<self->size; ++i )
        {
            if( (*cmp)(item, vector_get(self,i) ) == 0 )
            {
                return 1;
            }
        }
        return 0;
    }
    // ----------------------------------------------------------- vector_empty ---
    int
    vector_empty( const vector_t *self )
    {
        assert( self );
        return self->size == 0;
    }
    // ------------------------------------------------------------ vector_size ---
    size_t
    vector_size( const vector_t *self )
    {
        assert( self );
        return self->size;
    }
    // --------------------------------------------------------- vector_reserve ---
    void
    vector_reserve( vector_t *self,
    const size_t size )
    {
        assert( self );
        if( self->capacity < size)
        {
            self->items = realloc( self->items, size * self->item_size );
            self->capacity = size;
        }
    }
    // -------------------------------------------------------- vector_capacity ---
    size_t
    vector_capacity( const vector_t *self )
    {
        assert( self );
        return self->capacity;
    }
    // ---------------------------------------------------------- vector_shrink ---
    void
    vector_shrink( vector_t *self )
    {
        assert( self );
        if( self->capacity > self->size )
        {
            self->items = realloc( self->items, self->size * self->item_size );
        }
        self->capacity = self->size;
    }
    // ----------------------------------------------------------- vector_clear ---
    void
    vector_clear( vector_t *self )
    {
        assert( self );
        self->size = 0;
    }
    // ------------------------------------------------------------- vector_set ---
    void
    vector_set( vector_t *self,
    const size_t index,
    const void *item )
    {
        assert( self );
        assert( self->size );
        assert( index  < self->size );
        memcpy( (char *)(self->items) + index * self->item_size,
        item, self->item_size );
    }
    // ---------------------------------------------------------- vector_insert ---
    void
    vector_insert( vector_t *self,
    const size_t index,
    const void *item )
    {
        assert( self );
        assert( index <= self->size);
        if( self->capacity <= self->size )
        {
            vector_reserve(self, 2 * self->capacity );
        }
        if( index < self->size )
        {
            memmove( (char *)(self->items) + (index + 1) * self->item_size,
            (char *)(self->items) + (index + 0) * self->item_size,
            (self->size - index)  * self->item_size);
        }
        self->size++;
        vector_set( self, index, item );
    }
    // ----------------------------------------------------- vector_erase_range ---
    void
    vector_erase_range( vector_t *self,
    const size_t first,
    const size_t last )
    {
        assert( self );
        assert( first < self->size );
        assert( last  < self->size+1 );
        assert( first < last );
        memmove( (char *)(self->items) + first * self->item_size,
        (char *)(self->items) + last  * self->item_size,
        (self->size - last)   * self->item_size);
        self->size -= (last-first);
    }
    // ----------------------------------------------------------- vector_erase ---
    void
    vector_erase( vector_t *self,
    const size_t index )
    {
        assert( self );
        assert( index < self->size );
        vector_erase_range( self, index, index+1 );
    }
    // ------------------------------------------------------- vector_push_back ---
    void
    vector_push_back( vector_t *self,
    const void *item )
    {
        vector_insert( self, self->size, item );
    }
    // -------------------------------------------------------- vector_pop_back ---
    void
    vector_pop_back( vector_t *self )
    {
        assert( self );
        assert( self->size );
        self->size--;
    }
    // ---------------------------------------------------------- vector_resize ---
    void
    vector_resize( vector_t *self,
    const size_t size )
    {
        assert( self );
        if( size > self->capacity)
        {
            vector_reserve( self, size );
            self->size = self->capacity;
        }
        else
        {
            self->size = size;
        }
    }
    // -------------------------------------------------- vector_push_back_data ---
    void
    vector_push_back_data( vector_t *self,
    const void * data,
    const size_t count )
    {
        assert( self );
        assert( data );
        assert( count );
        if( self->capacity < (self->size+count) )
        {
            vector_reserve(self, self->size+count);
        }
        memmove( (char *)(self->items) + self->size * self->item_size, data,
        count*self->item_size );
        self->size += count;
    }
    // ----------------------------------------------------- vector_insert_data ---
    void
    vector_insert_data( vector_t *self,
    const size_t index,
    const void * data,
    const size_t count )
    {
        assert( self );
        assert( index < self->size );
        assert( data );
        assert( count );
        if( self->capacity < (self->size+count) )
        {
            vector_reserve(self, self->size+count);
        }
        memmove( (char *)(self->items) + (index + count ) * self->item_size,
        (char *)(self->items) + (index ) * self->item_size,
        count*self->item_size );
        memmove( (char *)(self->items) + index * self->item_size, data,
        count*self->item_size );
        self->size += count;
    }
    // ------------------------------------------------------------ vector_sort ---
    void
    vector_sort( vector_t *self,
    int (*cmp)(const void *, const void *) )
    {
        assert( self );
        assert( self->size );
        qsort(self->items, self->size, self->item_size, cmp);
    }
    // ----------------------------------------------------------------------------
    vertex_attribute_t *
    vertex_attribute_new( GLchar * name,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    GLvoid *pointer )
    {
        vertex_attribute_t *attribute =
        (vertex_attribute_t *) malloc (sizeof(vertex_attribute_t));
        assert( size > 0 );
        attribute->name       = (GLchar *) strdup( name );
        attribute->index      = -1;
        attribute->size       = size;
        attribute->type       = type;
        attribute->normalized = normalized;
        attribute->stride     = stride;
        attribute->pointer    = pointer;
        return attribute;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_attribute_delete( vertex_attribute_t * self )
    {
        assert( self );
        free( self->name );
        free( self );
    }
    // ----------------------------------------------------------------------------
    vertex_attribute_t *
    vertex_attribute_parse( char *format )
    {
        GLenum type = 0;
        int size;
        int normalized = 0;
        char ctype;
        char *name;
        vertex_attribute_t *attr;
        char *p = strchr(format, ':');
        if( p != NULL)
        {
            name = strndup(format, p-format);
            if( *(++p) == '\0' )
            {
                fprintf( stderr, "No size specified for '%s' attribute\n", name );
                free( name );
                return 0;
            }
            size = *p - '0';
            if( *(++p) == '\0' )
            {
                fprintf( stderr, "No format specified for '%s' attribute\n", name );
                free( name );
                return 0;
            }
            ctype = *p;
            if( *(++p) != '\0' )
            {
                if( *p == 'n' )
                {
                    normalized = 1;
                }
            }
        }
        else
        {
            fprintf(stderr, "Vertex attribute format not understood ('%s')\n", format );
            return 0;
        }
        switch( ctype )
        {
            case 'b': type = GL_BYTE;           break;
            case 'B': type = GL_UNSIGNED_BYTE;  break;
            case 's': type = GL_SHORT;          break;
            case 'S': type = GL_UNSIGNED_SHORT; break;
            case 'i': type = GL_INT;            break;
            case 'I': type = GL_UNSIGNED_INT;   break;
            case 'f': type = GL_FLOAT;          break;
            default:  type = 0;                 break;
        }
        attr = vertex_attribute_new( name, size, type, normalized, 0, 0 );
        free( name );
        return attr;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_attribute_enable( vertex_attribute_t *attr )
    {
        if( attr->index == -1 )
        {
            GLint program;
            glGetIntegerv( GL_CURRENT_PROGRAM, &program );
            if( program == 0)
            {
                return;
            }
            attr->index = glGetAttribLocation( program, attr->name );
            if( attr->index == -1 )
            {
                return;
            }
        }
        glEnableVertexAttribArray( attr->index );
        glVertexAttribPointer( attr->index, attr->size, attr->type,
        attr->normalized, attr->stride, attr->pointer );
    }
    #ifdef WIN32
    // strndup() is not available on Windows
    char *strndup( const char *s1, size_t n)
    {
        char *copy= (char*)malloc( n+1 );
        memcpy( copy, s1, n );
        copy[n] = 0;
        return copy;
    };
    #endif
    /**
    * Buffer status
    */
    #define CLEAN  (0)
    #define DIRTY  (1)
    #define FROZEN (2)
    // ----------------------------------------------------------------------------
    vertex_buffer_t *
    vertex_buffer_new( const char *format )
    {
        size_t i, index = 0, stride = 0;
        const char *start = 0, *end = 0;
        GLchar *pointer = 0;
        vertex_buffer_t *self = (vertex_buffer_t *) malloc (sizeof(vertex_buffer_t));
        if( !self )
        {
            return NULL;
        }
        self->format = strdup( format );
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            self->attributes[i] = 0;
        }
        start = format;
        do
        {
            char *desc = 0;
            vertex_attribute_t *attribute;
            GLuint attribute_size = 0;
            end = (char *) (strchr(start+1, ','));
            if (end == NULL)
            {
                desc = strdup( start );
            }
            else
            {
                desc = strndup( start, end-start );
            }
            attribute = vertex_attribute_parse( desc );
            start = end+1;
            free(desc);
            attribute->pointer = pointer;
            switch( attribute->type )
            {
                case GL_BOOL:           attribute_size = sizeof(GLboolean); break;
                case GL_BYTE:           attribute_size = sizeof(GLbyte); break;
                case GL_UNSIGNED_BYTE:  attribute_size = sizeof(GLubyte); break;
                case GL_SHORT:          attribute_size = sizeof(GLshort); break;
                case GL_UNSIGNED_SHORT: attribute_size = sizeof(GLushort); break;
                case GL_INT:            attribute_size = sizeof(GLint); break;
                case GL_UNSIGNED_INT:   attribute_size = sizeof(GLuint); break;
                case GL_FLOAT:          attribute_size = sizeof(GLfloat); break;
                default:                attribute_size = 0;
            }
            stride  += attribute->size*attribute_size;
            pointer += attribute->size*attribute_size;
            self->attributes[index] = attribute;
            index++;
        } while ( end && (index < MAX_VERTEX_ATTRIBUTE) );
        for( i=0; i<index; ++i )
        {
            self->attributes[i]->stride = stride;
        }
        #ifdef FREETYPE_GL_USE_VAO
        self->VAO_id = 0;
        #endif
        self->vertices = vector_new( stride );
        self->vertices_id  = 0;
        self->GPU_vsize = 0;
        self->indices = vector_new( sizeof(GLuint) );
        self->indices_id  = 0;
        self->GPU_isize = 0;
        self->items = vector_new( sizeof(ivec4) );
        self->state = DIRTY;
        self->mode = GL_TRIANGLES;
        return self;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_delete( vertex_buffer_t *self )
    {
        size_t i;
        assert( self );
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            if( self->attributes[i] )
            {
                vertex_attribute_delete( self->attributes[i] );
            }
        }
        #ifdef FREETYPE_GL_USE_VAO
        if( self->VAO_id )
        {
            glDeleteVertexArrays( 1, &self->VAO_id );
        }
        self->VAO_id = 0;
        #endif
        vector_delete( self->vertices );
        self->vertices = 0;
        if( self->vertices_id )
        {
            glDeleteBuffers( 1, &self->vertices_id );
        }
        self->vertices_id = 0;
        vector_delete( self->indices );
        self->indices = 0;
        if( self->indices_id )
        {
            glDeleteBuffers( 1, &self->indices_id );
        }
        self->indices_id = 0;
        vector_delete( self->items );
        if( self->format )
        {
            free( self->format );
        }
        self->format = 0;
        self->state = 0;
        free( self );
    }
    // ----------------------------------------------------------------------------
    const char *
    vertex_buffer_format( const vertex_buffer_t *self )
    {
        assert( self );
        return self->format;
    }
    // ----------------------------------------------------------------------------
    size_t
    vertex_buffer_size( const vertex_buffer_t *self )
    {
        assert( self );
        return vector_size( self->items );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_print( vertex_buffer_t * self )
    {
        int i = 0;
        static char *gltypes[9] = {
            "GL_BOOL",
            "GL_BYTE",
            "GL_UNSIGNED_BYTE",
            "GL_SHORT",
            "GL_UNSIGNED_SHORT",
            "GL_INT",
            "GL_UNSIGNED_INT",
            "GL_FLOAT",
            "GL_VOID"
        };
        assert(self);
        fprintf( stderr, "%zu vertices, %zu indices\n",
        vector_size( self->vertices ), vector_size( self->indices ) );
        while( self->attributes[i] )
        {
            int j = 8;
            switch( self->attributes[i]->type )
            {
                case GL_BOOL:           j=0; break;
                case GL_BYTE:           j=1; break;
                case GL_UNSIGNED_BYTE:  j=2; break;
                case GL_SHORT:          j=3; break;
                case GL_UNSIGNED_SHORT: j=4; break;
                case GL_INT:            j=5; break;
                case GL_UNSIGNED_INT:   j=6; break;
                case GL_FLOAT:          j=7; break;
                default:                j=8; break;
            }
            fprintf(stderr, "%s : %dx%s (+%p)\n",
            self->attributes[i]->name,
            self->attributes[i]->size,
            gltypes[j],
            self->attributes[i]->pointer);
            i += 1;
        }
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_upload ( vertex_buffer_t *self )
    {
        size_t vsize, isize;
        if( self->state == FROZEN )
        {
            return;
        }
        if( !self->vertices_id )
        {
            glGenBuffers( 1, &self->vertices_id );
        }
        if( !self->indices_id )
        {
            glGenBuffers( 1, &self->indices_id );
        }
        vsize = self->vertices->size*self->vertices->item_size;
        isize = self->indices->size*self->indices->item_size;
        // Always upload vertices first such that indices do not point to non
        // existing data (if we get interrupted in between for example).
        // Upload vertices
        glBindBuffer( GL_ARRAY_BUFFER, self->vertices_id );
        if( vsize != self->GPU_vsize )
        {
            glBufferData( GL_ARRAY_BUFFER,
            vsize, self->vertices->items, GL_DYNAMIC_DRAW );
            self->GPU_vsize = vsize;
        }
        else
        {
            glBufferSubData( GL_ARRAY_BUFFER,
            0, vsize, self->vertices->items );
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        // Upload indices
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, self->indices_id );
        if( isize != self->GPU_isize )
        {
            glBufferData( GL_ELEMENT_ARRAY_BUFFER,
            isize, self->indices->items, GL_DYNAMIC_DRAW );
            self->GPU_isize = isize;
        }
        else
        {
            glBufferSubData( GL_ELEMENT_ARRAY_BUFFER,
            0, isize, self->indices->items );
        }
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_clear( vertex_buffer_t *self )
    {
        assert( self );
        self->state = FROZEN;
        vector_clear( self->indices );
        vector_clear( self->vertices );
        vector_clear( self->items );
        self->state = DIRTY;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render_setup ( vertex_buffer_t *self, GLenum mode )
    {
        size_t i;
        #ifdef FREETYPE_GL_USE_VAO
        // Unbind so no existing VAO-state is overwritten,
        // (e.g. the GL_ELEMENT_ARRAY_BUFFER-binding).
        glBindVertexArray( 0 );
        #endif
        if( self->state != CLEAN )
        {
            vertex_buffer_upload( self );
            self->state = CLEAN;
        }
        #ifdef FREETYPE_GL_USE_VAO
        if( self->VAO_id == 0 )
        {
            // Generate and set up VAO
            glGenVertexArrays( 1, &self->VAO_id );
            glBindVertexArray( self->VAO_id );
            glBindBuffer( GL_ARRAY_BUFFER, self->vertices_id );
            for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
            {
                vertex_attribute_t *attribute = self->attributes[i];
                if( attribute == 0 )
                {
                    continue;
                }
                else
                {
                    vertex_attribute_enable( attribute );
                }
            }
            glBindBuffer( GL_ARRAY_BUFFER, 0 );
            if( self->indices->size )
            {
                glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, self->indices_id );
            }
        }
        // Bind VAO for drawing
        glBindVertexArray( self->VAO_id );
        #else
        glBindBuffer( GL_ARRAY_BUFFER, self->vertices_id );
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            vertex_attribute_t *attribute = self->attributes[i];
            if ( attribute == 0 )
            {
                continue;
            }
            else
            {
                vertex_attribute_enable( attribute );
            }
        }
        if( self->indices->size )
        {
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, self->indices_id );
        }
        #endif
        self->mode = mode;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render_finish ( vertex_buffer_t *self )
    {
        #ifdef FREETYPE_GL_USE_VAO
        glBindVertexArray( 0 );
        #else
        int i;
        for( i=0; i<MAX_VERTEX_ATTRIBUTE; ++i )
        {
            vertex_attribute_t *attribute = self->attributes[i];
            if( attribute == 0 )
            {
                continue;
            }
            else
            {
                glDisableVertexAttribArray( attribute->index );
            }
        }
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        #endif
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render_item ( vertex_buffer_t *self,
    size_t index )
    {
        ivec4 * item = (ivec4 *) vector_get( self->items, index );
        assert( self );
        assert( index < vector_size( self->items ) );
        if( self->indices->size )
        {
            size_t start = item->istart;
            size_t count = item->icount;
            glDrawElements( self->mode, count, GL_UNSIGNED_INT, (void *)(start*sizeof(GLuint)) );
        }
        else if( self->vertices->size )
        {
            size_t start = item->vstart;
            size_t count = item->vcount;
            glDrawArrays( self->mode, start*self->vertices->item_size, count);
        }
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_render ( vertex_buffer_t *self, GLenum mode )
    {
        size_t vcount = self->vertices->size;
        size_t icount = self->indices->size;
        vertex_buffer_render_setup( self, mode );
        if( icount )
        {
            glDrawElements( mode, icount, GL_UNSIGNED_INT, 0 );
        }
        else
        {
            glDrawArrays( mode, 0, vcount );
        }
        vertex_buffer_render_finish( self );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_push_back_indices ( vertex_buffer_t * self,
    const GLuint * indices,
    const size_t icount )
    {
        assert( self );
        self->state |= DIRTY;
        vector_push_back_data( self->indices, indices, icount );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_push_back_vertices ( vertex_buffer_t * self,
    const void * vertices,
    const size_t vcount )
    {
        assert( self );
        self->state |= DIRTY;
        vector_push_back_data( self->vertices, vertices, vcount );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_insert_indices ( vertex_buffer_t *self,
    const size_t index,
    const GLuint *indices,
    const size_t count )
    {
        assert( self );
        assert( self->indices );
        assert( index < self->indices->size+1 );
        self->state |= DIRTY;
        vector_insert_data( self->indices, index, indices, count );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_insert_vertices( vertex_buffer_t *self,
    const size_t index,
    const void *vertices,
    const size_t vcount )
    {
        size_t i;
        assert( self );
        assert( self->vertices );
        assert( index < self->vertices->size+1 );
        self->state |= DIRTY;
        for( i=0; i<self->indices->size; ++i )
        {
            if( *(GLuint *)(vector_get( self->indices, i )) > index )
            {
                *(GLuint *)(vector_get( self->indices, i )) += index;
            }
        }
        vector_insert_data( self->vertices, index, vertices, vcount );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_erase_indices( vertex_buffer_t *self,
    const size_t first,
    const size_t last )
    {
        assert( self );
        assert( self->indices );
        assert( first < self->indices->size );
        assert( (last) <= self->indices->size );
        self->state |= DIRTY;
        vector_erase_range( self->indices, first, last );
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_erase_vertices( vertex_buffer_t *self,
    const size_t first,
    const size_t last )
    {
        size_t i;
        assert( self );
        assert( self->vertices );
        assert( first < self->vertices->size );
        assert( last <= self->vertices->size );
        assert( last > first );
        self->state |= DIRTY;
        for( i=0; i<self->indices->size; ++i )
        {
            if( *(GLuint *)(vector_get( self->indices, i )) > first )
            {
                *(GLuint *)(vector_get( self->indices, i )) -= (last-first);
            }
        }
        vector_erase_range( self->vertices, first, last );
    }
    // ----------------------------------------------------------------------------
    size_t
    vertex_buffer_push_back( vertex_buffer_t * self,
    const void * vertices, const size_t vcount,
    const GLuint * indices, const size_t icount )
    {
        return vertex_buffer_insert( self, vector_size( self->items ),
        vertices, vcount, indices, icount );
    }
    // ----------------------------------------------------------------------------
    size_t
    vertex_buffer_insert( vertex_buffer_t * self, const size_t index,
    const void * vertices, const size_t vcount,
    const GLuint * indices, const size_t icount )
    {
        size_t vstart, istart, i;
        ivec4 item;
        assert( self );
        assert( vertices );
        assert( indices );
        self->state = FROZEN;
        // Push back vertices
        vstart = vector_size( self->vertices );
        vertex_buffer_push_back_vertices( self, vertices, vcount );
        // Push back indices
        istart = vector_size( self->indices );
        vertex_buffer_push_back_indices( self, indices, icount );
        // Update indices within the vertex buffer
        for( i=0; i<icount; ++i )
        {
            *(GLuint *)(vector_get( self->indices, istart+i )) += vstart;
        }
        // Insert item
        item.x = vstart;
        item.y = vcount;
        item.z = istart;
        item.w = icount;
        vector_insert( self->items, index, &item );
        self->state = DIRTY;
        return index;
    }
    // ----------------------------------------------------------------------------
    void
    vertex_buffer_erase( vertex_buffer_t * self,
    const size_t index )
    {
        ivec4 * item;
        int vstart;
        size_t vcount, istart, icount, i;
        assert( self );
        assert( index < vector_size( self->items ) );
        item = (ivec4 *) vector_get( self->items, index );
        vstart = item->vstart;
        vcount = item->vcount;
        istart = item->istart;
        icount = item->icount;
        // Update items
        for( i=0; i<vector_size(self->items); ++i )
        {
            ivec4 * item = (ivec4 *) vector_get( self->items, i );
            if( item->vstart > vstart)
            {
                item->vstart -= vcount;
                item->istart -= icount;
            }
        }
        self->state = FROZEN;
        vertex_buffer_erase_indices( self, istart, istart+icount );
        vertex_buffer_erase_vertices( self, vstart, vstart+vcount );
        vector_erase( self->items, index );
        self->state = DIRTY;
    }
void sjf_anon1(sjs_anon1* _this) {
}

void sjf_anon1_copy(sjs_anon1* _this, sjs_anon1* _from) {
}

void sjf_anon1_destroy(sjs_anon1* _this) {
}

void sjf_anon1_heap(sjs_anon1_heap* _this) {
}

void sjf_anon2(sjs_anon2* _this) {
}

void sjf_anon2_copy(sjs_anon2* _this, sjs_anon2* _from) {
#line 27 "lib/ui/animation.sj"
    sjf_list_heap_animation_copy(&_this->animations, &_from->animations);
#line 27
    _this->current = _from->current;
}

void sjf_anon2_destroy(sjs_anon2* _this) {
}

void sjf_anon2_heap(sjs_anon2_heap* _this) {
}

void sjf_anon2_nextFrame(sjs_anon2* _parent, int32_t time) {
    int32_t sjt_compare61;
    int32_t sjt_compare62;
    sjs_anon2* sjt_dot1409;
    sjs_anon2* sjt_dot1412;
    bool sjt_ifElse25;
    sjs_list_heap_animation* sjt_parent143;

#line 31 "lib/ui/animation.sj"
    sjt_dot1409 = _parent;
#line 31
    sjt_dot1409->current = time;
#line 31
    sjt_dot1412 = _parent;
#line 4 "lib/common/list.sj"
    sjt_parent143 = &(sjt_dot1412)->animations;
#line 4
    sjf_list_heap_animation_getCount(sjt_parent143, &sjt_compare61);
#line 33 "lib/ui/animation.sj"
    sjt_compare62 = 0;
#line 33
    sjt_ifElse25 = sjt_compare61 > sjt_compare62;
    if (sjt_ifElse25) {
        int32_t i;
        sjs_anon2* sjt_dot1413;
        int32_t sjt_forEnd18;
        int32_t sjt_forStart18;
        sjs_list_heap_animation* sjt_parent144;

#line 35 "lib/ui/animation.sj"
        sjt_forStart18 = 0;
#line 31
        sjt_dot1413 = _parent;
#line 4 "lib/common/list.sj"
        sjt_parent144 = &(sjt_dot1413)->animations;
#line 4
        sjf_list_heap_animation_getCount(sjt_parent144, &sjt_forEnd18);
#line 35 "lib/ui/animation.sj"
        i = sjt_forStart18;
        while (i < sjt_forEnd18) {
            sjs_anon2* sjt_dot1414;
            sjs_anon2* sjt_dot1416;
            int32_t sjt_functionParam476;
            bool sjt_ifElse26;
            int32_t sjt_interfaceParam29;
            int32_t sjt_math2153;
            int32_t sjt_math2154;
            int32_t sjt_math2155;
            int32_t sjt_math2156;
            sjs_list_heap_animation* sjt_parent145;
            sjs_list_heap_animation* sjt_parent147;
            sji_anon2_animation* sjt_parent148;
            sji_anon2_animation* sjv_a;
            int32_t sjv_index;

#line 31 "lib/ui/animation.sj"
            sjt_dot1414 = _parent;
#line 4 "lib/common/list.sj"
            sjt_parent145 = &(sjt_dot1414)->animations;
#line 4
            sjf_list_heap_animation_getCount(sjt_parent145, &sjt_math2155);
#line 36 "lib/ui/animation.sj"
            sjt_math2156 = 0;
#line 36
            sjt_math2153 = sjt_math2155 - sjt_math2156;
#line 36
            sjt_math2154 = 1;
#line 36
            sjv_index = sjt_math2153 - sjt_math2154;
#line 31
            sjt_dot1416 = _parent;
#line 8 "lib/common/list.sj"
            sjt_parent147 = &(sjt_dot1416)->animations;
#line 37 "lib/ui/animation.sj"
            sjt_functionParam476 = sjv_index;
#line 37
            sjf_list_heap_animation_getAt_heap(sjt_parent147, sjt_functionParam476, &sjv_a);
#line 2
            sjt_parent148 = sjv_a;
#line 31
            sjt_interfaceParam29 = time;
#line 38
            sjt_parent148->nextFrame((void*)(((char*)sjt_parent148->_parent) + sizeof(intptr_t)), sjt_interfaceParam29, &sjt_ifElse26);
            if (sjt_ifElse26) {
                sjs_anon2* sjt_dot1417;
                int32_t sjt_functionParam477;
                sjs_list_heap_animation* sjt_parent149;

#line 31 "lib/ui/animation.sj"
                sjt_dot1417 = _parent;
#line 53 "lib/common/list.sj"
                sjt_parent149 = &(sjt_dot1417)->animations;
#line 39 "lib/ui/animation.sj"
                sjt_functionParam477 = sjv_index;
#line 39
                sjf_list_heap_animation_removeAt(sjt_parent149, sjt_functionParam477);
            }

#line 35
            i++;

            sjv_a->_refCount--;
            if (sjv_a->_refCount <= 0) {
                sji_anon2_animation_destroy(sjv_a);
            }
        }
    }
}

void sjf_anon3(sjs_anon3* _this) {
}

void sjf_anon3_copy(sjs_anon3* _this, sjs_anon3* _from) {
#line 1 "lib/ui/borderLayout.sj"
    _this->fill = _from->fill;
#line 1
    _this->left = _from->left;
#line 1
    _this->right = _from->right;
#line 1
    _this->top = _from->top;
#line 1
    _this->bottom = _from->bottom;
}

void sjf_anon3_destroy(sjs_anon3* _this) {
}

void sjf_anon3_heap(sjs_anon3_heap* _this) {
}

void sjf_anon4(sjs_anon4* _this) {
}

void sjf_anon4_copy(sjs_anon4* _this, sjs_anon4* _from) {
#line 1 "lib/ui/buttonElement.sj"
    _this->normal = _from->normal;
#line 1
    _this->hot = _from->hot;
#line 1
    _this->pressed = _from->pressed;
}

void sjf_anon4_destroy(sjs_anon4* _this) {
}

void sjf_anon4_heap(sjs_anon4_heap* _this) {
}

void sjf_anon5(sjs_anon5* _this) {
}

void sjf_anon5_copy(sjs_anon5* _this, sjs_anon5* _from) {
}

void sjf_anon5_destroy(sjs_anon5* _this) {
}

void sjf_anon5_heap(sjs_anon5_heap* _this) {
}

void sjf_anon5_red(sjs_anon5* _parent, sjs_color* _return) {
#line 2 "lib/ui/color.sj"
    _return->r = 1.0f;
#line 2
    _return->g = 0.0f;
#line 2
    _return->b = 0.0f;
#line 13
    _return->a = 1.0f;
#line 13
    sjf_color(_return);
}

void sjf_anon5_red_heap(sjs_anon5* _parent, sjs_color_heap** _return) {
    (*_return) = (sjs_color_heap*)malloc(sizeof(sjs_color_heap));
    (*_return)->_refCount = 1;
#line 2 "lib/ui/color.sj"
    (*_return)->r = 1.0f;
#line 2
    (*_return)->g = 0.0f;
#line 2
    (*_return)->b = 0.0f;
#line 13
    (*_return)->a = 1.0f;
#line 13
    sjf_color_heap((*_return));
}

void sjf_anon6(sjs_anon6* _this) {
}

void sjf_anon6_copy(sjs_anon6* _this, sjs_anon6* _from) {
}

void sjf_anon6_destroy(sjs_anon6* _this) {
}

void sjf_anon6_heap(sjs_anon6_heap* _this) {
}

void sjf_array_char(sjs_array_char* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(char));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_char_copy(sjs_array_char* _this, sjs_array_char* _from) {
#line 1 "lib/common/array.sj"
    _this->dataSize = _from->dataSize;
#line 1
    _this->data = _from->data;
#line 1
    _this->_isGlobal = _from->_isGlobal;
#line 1
    _this->count = _from->count;
#line 280
    _this->data = _from->data;
#line 280
    if (!_this->_isGlobal && _this->data) {
#line 280
        _retain(_this->data);
#line 280
    }
}

void sjf_array_char_destroy(sjs_array_char* _this) {
#line 287 "lib/common/array.sj"
    if (!_this->_isGlobal && _this->data) {
#line 287
        if (_release(_this->data)) {
#line 287
            free((char*)_this->data);
#line 287
        }
#line 287
    }
}

void sjf_array_char_getAt(sjs_array_char* _parent, int32_t index, char* _return) {
#line 8 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 8
        halt("getAt: out of bounds\n");
#line 8
    }
#line 8
    char* p = (char*)_parent->data;
#line 8
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
;		
}

void sjf_array_char_grow(sjs_array_char* _parent, int32_t newSize, sjs_array_char* _return) {
    sjs_array_char* sjt_dot1328;
    void* sjv_newData;

#line 116 "lib/common/array.sj"
    sjv_newData = 0;
#line 117
    if (_parent->dataSize != newSize) {
#line 117
        if (newSize < _parent->dataSize) {
#line 117
            halt("grow: new size smaller than old _parent->dataSize %d:%d\n", newSize, _parent->dataSize);
#line 117
        }
#line 117
        sjv_newData = malloc(newSize * sizeof(char));
#line 117
        if (!_parent->data) {
#line 117
            halt("grow: out of memory\n");
#line 117
        }
#line 117
        memcpy(sjv_newData, _parent->data, _parent->dataSize * sizeof(char));
#line 117
    }
#line 115
    _return->dataSize = newSize;
#line 130
    _return->data = sjv_newData;
#line 4
    _return->_isGlobal = false;
#line 115
    sjt_dot1328 = _parent;
#line 130
    _return->count = (sjt_dot1328)->count;
#line 130
    sjf_array_char(_return);
}

void sjf_array_char_grow_heap(sjs_array_char* _parent, int32_t newSize, sjs_array_char_heap** _return) {
    sjs_array_char* sjt_dot1329;
    void* sjv_newData;

#line 116 "lib/common/array.sj"
    sjv_newData = 0;
#line 117
    if (_parent->dataSize != newSize) {
#line 117
        if (newSize < _parent->dataSize) {
#line 117
            halt("grow: new size smaller than old _parent->dataSize %d:%d\n", newSize, _parent->dataSize);
#line 117
        }
#line 117
        sjv_newData = malloc(newSize * sizeof(char));
#line 117
        if (!_parent->data) {
#line 117
            halt("grow: out of memory\n");
#line 117
        }
#line 117
        memcpy(sjv_newData, _parent->data, _parent->dataSize * sizeof(char));
#line 117
    }
#line 117
    (*_return) = (sjs_array_char_heap*)malloc(sizeof(sjs_array_char_heap));
#line 117
    (*_return)->_refCount = 1;
#line 115
    (*_return)->dataSize = newSize;
#line 130
    (*_return)->data = sjv_newData;
#line 4
    (*_return)->_isGlobal = false;
#line 115
    sjt_dot1329 = _parent;
#line 130
    (*_return)->count = (sjt_dot1329)->count;
#line 130
    sjf_array_char_heap((*_return));
}

void sjf_array_char_heap(sjs_array_char_heap* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(char));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_char_initAt(sjs_array_char* _parent, int32_t index, char item) {
#line 20 "lib/common/array.sj"
    if (index != _parent->count) {
#line 20
        halt("initAt: can only initialize last element\n");		
#line 20
    }
#line 20
    if (index >= _parent->dataSize || index < 0) {
#line 20
        halt("initAt: out of bounds %d:%d\n", index, _parent->dataSize);
#line 20
    }
#line 20
    char* p = (char*)_parent->data;
#line 20
    #line 19 "lib/common/array.sj"
p[index] = item;
;
#line 20
    _parent->count = index + 1;
}

void sjf_array_char_setAt(sjs_array_char* _parent, int32_t index, char item) {
#line 35 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 35
        halt("setAt: out of bounds %d:%d\n", index, _parent->count);
#line 35
    }
#line 35
    char* p = (char*)_parent->data;
#line 35
    ;
#line 35
    #line 34 "lib/common/array.sj"
p[index] = item;
;
}

void sjf_array_heap_animation(sjs_array_heap_animation* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sji_anon2_animation*));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_heap_animation_copy(sjs_array_heap_animation* _this, sjs_array_heap_animation* _from) {
#line 1 "lib/common/array.sj"
    _this->dataSize = _from->dataSize;
#line 1
    _this->data = _from->data;
#line 1
    _this->_isGlobal = _from->_isGlobal;
#line 1
    _this->count = _from->count;
#line 280
    _this->data = _from->data;
#line 280
    if (!_this->_isGlobal && _this->data) {
#line 280
        _retain(_this->data);
#line 280
    }
}

void sjf_array_heap_animation_destroy(sjs_array_heap_animation* _this) {
#line 287 "lib/common/array.sj"
    if (!_this->_isGlobal && _this->data) {
#line 287
        if (_release(_this->data)) {
#line 287
            free((sji_anon2_animation**)_this->data);
#line 287
        }
#line 287
    }
}

void sjf_array_heap_animation_getAt_heap(sjs_array_heap_animation* _parent, int32_t index, sji_anon2_animation** _return) {
#line 8 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 8
        halt("getAt: out of bounds\n");
#line 8
    }
#line 8
    sji_anon2_animation** p = (sji_anon2_animation**)_parent->data;
#line 8
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
#line 8
(*_return)->_refCount++;
;		
}

void sjf_array_heap_animation_heap(sjs_array_heap_animation_heap* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sji_anon2_animation*));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_heap_element(sjs_array_heap_element* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sji_element*));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_heap_element_copy(sjs_array_heap_element* _this, sjs_array_heap_element* _from) {
#line 1 "lib/common/array.sj"
    _this->dataSize = _from->dataSize;
#line 1
    _this->data = _from->data;
#line 1
    _this->_isGlobal = _from->_isGlobal;
#line 1
    _this->count = _from->count;
#line 280
    _this->data = _from->data;
#line 280
    if (!_this->_isGlobal && _this->data) {
#line 280
        _retain(_this->data);
#line 280
    }
}

void sjf_array_heap_element_destroy(sjs_array_heap_element* _this) {
#line 287 "lib/common/array.sj"
    if (!_this->_isGlobal && _this->data) {
#line 287
        if (_release(_this->data)) {
#line 287
            free((sji_element**)_this->data);
#line 287
        }
#line 287
    }
}

void sjf_array_heap_element_getAt_heap(sjs_array_heap_element* _parent, int32_t index, sji_element** _return) {
#line 8 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 8
        halt("getAt: out of bounds\n");
#line 8
    }
#line 8
    sji_element** p = (sji_element**)_parent->data;
#line 8
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
#line 8
(*_return)->_refCount++;
;		
}

void sjf_array_heap_element_heap(sjs_array_heap_element_heap* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sji_element*));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_heap_element_initAt(sjs_array_heap_element* _parent, int32_t index, sji_element* item) {
#line 20 "lib/common/array.sj"
    if (index != _parent->count) {
#line 20
        halt("initAt: can only initialize last element\n");		
#line 20
    }
#line 20
    if (index >= _parent->dataSize || index < 0) {
#line 20
        halt("initAt: out of bounds %d:%d\n", index, _parent->dataSize);
#line 20
    }
#line 20
    sji_element** p = (sji_element**)_parent->data;
#line 20
    #line 19 "lib/common/array.sj"
p[index] = item;
#line 19
p[index]->_refCount++;
;
#line 20
    _parent->count = index + 1;
}

void sjf_array_heap_model(sjs_array_heap_model* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sji_nauScene3dElement_model*));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_heap_model__quickSortCallback(sjs_array_heap_model* _parent, int32_t left, int32_t right, cb_heap_model_heap_model_i32 cb) {
    int32_t sjt_compare11;
    int32_t sjt_compare12;
    int32_t sjt_compare25;
    int32_t sjt_compare26;
    int32_t sjt_compare27;
    int32_t sjt_compare28;
    int32_t sjt_functionParam16;
    bool sjt_ifElse4;
    bool sjt_ifElse5;
    int32_t sjt_math45;
    int32_t sjt_math46;
    int32_t sjt_math47;
    int32_t sjt_math48;
    bool sjt_while1;
    int32_t sjv_i;
    int32_t sjv_j;
    sji_nauScene3dElement_model* sjv_pivot;

#line 164 "lib/common/array.sj"
    sjv_i = left;
#line 164
    sjv_j = right;
#line 164
    sjt_math47 = left;
#line 164
    sjt_math48 = right;
#line 168
    sjt_math45 = sjt_math47 + sjt_math48;
#line 168
    sjt_math46 = 2;
#line 168
    sjt_functionParam16 = sjt_math45 / sjt_math46;
#line 168
    sjf_array_heap_model_getAt_heap(_parent, sjt_functionParam16, &sjv_pivot);
#line 169
    sjt_compare11 = sjv_i;
#line 169
    sjt_compare12 = sjv_j;
#line 169
    sjt_while1 = sjt_compare11 <= sjt_compare12;
    while (sjt_while1) {
        cb_heap_model_heap_model_i32 sjt_callback1;
        cb_heap_model_heap_model_i32 sjt_callback3;
        int32_t sjt_compare13;
        int32_t sjt_compare14;
        int32_t sjt_compare17;
        int32_t sjt_compare18;
        int32_t sjt_compare21;
        int32_t sjt_compare22;
        int32_t sjt_compare23;
        int32_t sjt_compare24;
        sji_nauScene3dElement_model* sjt_functionParam17;
        int32_t sjt_functionParam18;
        sji_nauScene3dElement_model* sjt_functionParam19;
        sji_nauScene3dElement_model* sjt_functionParam23;
        int32_t sjt_functionParam24;
        sji_nauScene3dElement_model* sjt_functionParam25;
        bool sjt_ifElse3;
        bool sjt_while2;
        bool sjt_while3;

#line 164 "lib/common/array.sj"
        sjt_callback1 = cb;
#line 170
        sjt_functionParam18 = sjv_i;
#line 170
        sjf_array_heap_model_getAt_heap(_parent, sjt_functionParam18, &sjt_functionParam17);
#line 170
        sjt_functionParam19 = sjv_pivot;
#line 170
        sjt_functionParam19->_refCount++;
#line 170
        sjt_callback1._cb(sjt_callback1._parent, sjt_functionParam17, sjt_functionParam19, &sjt_compare13);
#line 170
        sjt_compare14 = 0;
#line 170
        sjt_while2 = sjt_compare13 < sjt_compare14;
        while (sjt_while2) {
            cb_heap_model_heap_model_i32 sjt_callback2;
            int32_t sjt_compare15;
            int32_t sjt_compare16;
            sji_nauScene3dElement_model* sjt_functionParam20;
            int32_t sjt_functionParam21;
            sji_nauScene3dElement_model* sjt_functionParam22;
            int32_t sjt_math49;
            int32_t sjt_math50;

#line 171 "lib/common/array.sj"
            sjt_math49 = sjv_i;
#line 171
            sjt_math50 = 1;
#line 171
            sjv_i = sjt_math49 + sjt_math50;
#line 164
            sjt_callback2 = cb;
#line 170
            sjt_functionParam21 = sjv_i;
#line 170
            sjf_array_heap_model_getAt_heap(_parent, sjt_functionParam21, &sjt_functionParam20);
#line 170
            sjt_functionParam22 = sjv_pivot;
#line 170
            sjt_functionParam22->_refCount++;
#line 170
            sjt_callback2._cb(sjt_callback2._parent, sjt_functionParam20, sjt_functionParam22, &sjt_compare15);
#line 170
            sjt_compare16 = 0;
#line 170
            sjt_while2 = sjt_compare15 < sjt_compare16;

            sjt_functionParam20->_refCount--;
            if (sjt_functionParam20->_refCount <= 0) {
                sji_nauScene3dElement_model_destroy(sjt_functionParam20);
            }
            sjt_functionParam22->_refCount--;
            if (sjt_functionParam22->_refCount <= 0) {
                sji_nauScene3dElement_model_destroy(sjt_functionParam22);
            }
        }

#line 164
        sjt_callback3 = cb;
#line 174
        sjt_functionParam24 = sjv_j;
#line 174
        sjf_array_heap_model_getAt_heap(_parent, sjt_functionParam24, &sjt_functionParam23);
#line 174
        sjt_functionParam25 = sjv_pivot;
#line 174
        sjt_functionParam25->_refCount++;
#line 174
        sjt_callback3._cb(sjt_callback3._parent, sjt_functionParam23, sjt_functionParam25, &sjt_compare17);
#line 174
        sjt_compare18 = 0;
#line 174
        sjt_while3 = sjt_compare17 > sjt_compare18;
        while (sjt_while3) {
            cb_heap_model_heap_model_i32 sjt_callback4;
            int32_t sjt_compare19;
            int32_t sjt_compare20;
            sji_nauScene3dElement_model* sjt_functionParam26;
            int32_t sjt_functionParam27;
            sji_nauScene3dElement_model* sjt_functionParam28;
            int32_t sjt_math51;
            int32_t sjt_math52;

#line 175 "lib/common/array.sj"
            sjt_math51 = sjv_j;
#line 175
            sjt_math52 = 1;
#line 175
            sjv_j = sjt_math51 - sjt_math52;
#line 164
            sjt_callback4 = cb;
#line 174
            sjt_functionParam27 = sjv_j;
#line 174
            sjf_array_heap_model_getAt_heap(_parent, sjt_functionParam27, &sjt_functionParam26);
#line 174
            sjt_functionParam28 = sjv_pivot;
#line 174
            sjt_functionParam28->_refCount++;
#line 174
            sjt_callback4._cb(sjt_callback4._parent, sjt_functionParam26, sjt_functionParam28, &sjt_compare19);
#line 174
            sjt_compare20 = 0;
#line 174
            sjt_while3 = sjt_compare19 > sjt_compare20;

            sjt_functionParam26->_refCount--;
            if (sjt_functionParam26->_refCount <= 0) {
                sji_nauScene3dElement_model_destroy(sjt_functionParam26);
            }
            sjt_functionParam28->_refCount--;
            if (sjt_functionParam28->_refCount <= 0) {
                sji_nauScene3dElement_model_destroy(sjt_functionParam28);
            }
        }

#line 178
        sjt_compare21 = sjv_i;
#line 178
        sjt_compare22 = sjv_j;
#line 178
        sjt_ifElse3 = sjt_compare21 <= sjt_compare22;
        if (sjt_ifElse3) {
            int32_t sjt_functionParam29;
            int32_t sjt_functionParam30;
            sji_nauScene3dElement_model* sjt_functionParam31;
            int32_t sjt_functionParam32;
            int32_t sjt_functionParam33;
            sji_nauScene3dElement_model* sjt_functionParam34;
            int32_t sjt_math53;
            int32_t sjt_math54;
            int32_t sjt_math55;
            int32_t sjt_math56;
            sji_nauScene3dElement_model* sjv_tmp;

#line 179 "lib/common/array.sj"
            sjt_functionParam29 = sjv_i;
#line 179
            sjf_array_heap_model_getAt_heap(_parent, sjt_functionParam29, &sjv_tmp);
#line 180
            sjt_functionParam30 = sjv_i;
#line 180
            sjt_functionParam32 = sjv_j;
#line 180
            sjf_array_heap_model_getAt_heap(_parent, sjt_functionParam32, &sjt_functionParam31);
#line 180
            sjf_array_heap_model_setAt(_parent, sjt_functionParam30, sjt_functionParam31);
#line 181
            sjt_functionParam33 = sjv_j;
#line 181
            sjt_functionParam34 = sjv_tmp;
#line 181
            sjt_functionParam34->_refCount++;
#line 181
            sjf_array_heap_model_setAt(_parent, sjt_functionParam33, sjt_functionParam34);
#line 182
            sjt_math53 = sjv_i;
#line 182
            sjt_math54 = 1;
#line 182
            sjv_i = sjt_math53 + sjt_math54;
#line 183
            sjt_math55 = sjv_j;
#line 183
            sjt_math56 = 1;
#line 183
            sjv_j = sjt_math55 - sjt_math56;

            sjt_functionParam31->_refCount--;
            if (sjt_functionParam31->_refCount <= 0) {
                sji_nauScene3dElement_model_destroy(sjt_functionParam31);
            }
            sjt_functionParam34->_refCount--;
            if (sjt_functionParam34->_refCount <= 0) {
                sji_nauScene3dElement_model_destroy(sjt_functionParam34);
            }
            sjv_tmp->_refCount--;
            if (sjv_tmp->_refCount <= 0) {
                sji_nauScene3dElement_model_destroy(sjv_tmp);
            }
        }

#line 169
        sjt_compare23 = sjv_i;
#line 169
        sjt_compare24 = sjv_j;
#line 169
        sjt_while1 = sjt_compare23 <= sjt_compare24;

        sjt_functionParam17->_refCount--;
        if (sjt_functionParam17->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjt_functionParam17);
        }
        sjt_functionParam19->_refCount--;
        if (sjt_functionParam19->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjt_functionParam19);
        }
        sjt_functionParam23->_refCount--;
        if (sjt_functionParam23->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjt_functionParam23);
        }
        sjt_functionParam25->_refCount--;
        if (sjt_functionParam25->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjt_functionParam25);
        }
    }

#line 164
    sjt_compare25 = left;
#line 187
    sjt_compare26 = sjv_j;
#line 187
    sjt_ifElse4 = sjt_compare25 < sjt_compare26;
    if (sjt_ifElse4) {
        int32_t sjt_functionParam35;
        int32_t sjt_functionParam36;
        cb_heap_model_heap_model_i32 sjt_functionParam37;

#line 164 "lib/common/array.sj"
        sjt_functionParam35 = left;
#line 188
        sjt_functionParam36 = sjv_j;
#line 164
        sjt_functionParam37 = cb;
#line 164
        sjf_array_heap_model__quickSortCallback(_parent, sjt_functionParam35, sjt_functionParam36, sjt_functionParam37);
    }

#line 190
    sjt_compare27 = sjv_i;
#line 164
    sjt_compare28 = right;
#line 190
    sjt_ifElse5 = sjt_compare27 < sjt_compare28;
    if (sjt_ifElse5) {
        int32_t sjt_functionParam38;
        int32_t sjt_functionParam39;
        cb_heap_model_heap_model_i32 sjt_functionParam40;

#line 191 "lib/common/array.sj"
        sjt_functionParam38 = sjv_i;
#line 164
        sjt_functionParam39 = right;
#line 164
        sjt_functionParam40 = cb;
#line 164
        sjf_array_heap_model__quickSortCallback(_parent, sjt_functionParam38, sjt_functionParam39, sjt_functionParam40);
    }

    sjv_pivot->_refCount--;
    if (sjv_pivot->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjv_pivot);
    }
}

void sjf_array_heap_model_copy(sjs_array_heap_model* _this, sjs_array_heap_model* _from) {
#line 1 "lib/common/array.sj"
    _this->dataSize = _from->dataSize;
#line 1
    _this->data = _from->data;
#line 1
    _this->_isGlobal = _from->_isGlobal;
#line 1
    _this->count = _from->count;
#line 280
    _this->data = _from->data;
#line 280
    if (!_this->_isGlobal && _this->data) {
#line 280
        _retain(_this->data);
#line 280
    }
}

void sjf_array_heap_model_destroy(sjs_array_heap_model* _this) {
#line 287 "lib/common/array.sj"
    if (!_this->_isGlobal && _this->data) {
#line 287
        if (_release(_this->data)) {
#line 287
            free((sji_nauScene3dElement_model**)_this->data);
#line 287
        }
#line 287
    }
}

void sjf_array_heap_model_getAt_heap(sjs_array_heap_model* _parent, int32_t index, sji_nauScene3dElement_model** _return) {
#line 8 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 8
        halt("getAt: out of bounds\n");
#line 8
    }
#line 8
    sji_nauScene3dElement_model** p = (sji_nauScene3dElement_model**)_parent->data;
#line 8
    #line 8 "lib/common/array.sj"
(*_return) = p[index];
#line 8
(*_return)->_refCount++;
;		
}

void sjf_array_heap_model_grow(sjs_array_heap_model* _parent, int32_t newSize, sjs_array_heap_model* _return) {
    sjs_array_heap_model* sjt_dot545;
    void* sjv_newData;

#line 116 "lib/common/array.sj"
    sjv_newData = 0;
#line 117
    if (_parent->dataSize != newSize) {
#line 117
        if (newSize < _parent->dataSize) {
#line 117
            halt("grow: new size smaller than old _parent->dataSize %d:%d\n", newSize, _parent->dataSize);
#line 117
        }
#line 117
        sjv_newData = malloc(newSize * sizeof(sji_nauScene3dElement_model*));
#line 117
        if (!_parent->data) {
#line 117
            halt("grow: out of memory\n");
#line 117
        }
#line 117
        memcpy(sjv_newData, _parent->data, _parent->dataSize * sizeof(sji_nauScene3dElement_model*));
#line 117
    }
#line 115
    _return->dataSize = newSize;
#line 130
    _return->data = sjv_newData;
#line 4
    _return->_isGlobal = false;
#line 115
    sjt_dot545 = _parent;
#line 130
    _return->count = (sjt_dot545)->count;
#line 130
    sjf_array_heap_model(_return);
}

void sjf_array_heap_model_grow_heap(sjs_array_heap_model* _parent, int32_t newSize, sjs_array_heap_model_heap** _return) {
    sjs_array_heap_model* sjt_dot546;
    void* sjv_newData;

#line 116 "lib/common/array.sj"
    sjv_newData = 0;
#line 117
    if (_parent->dataSize != newSize) {
#line 117
        if (newSize < _parent->dataSize) {
#line 117
            halt("grow: new size smaller than old _parent->dataSize %d:%d\n", newSize, _parent->dataSize);
#line 117
        }
#line 117
        sjv_newData = malloc(newSize * sizeof(sji_nauScene3dElement_model*));
#line 117
        if (!_parent->data) {
#line 117
            halt("grow: out of memory\n");
#line 117
        }
#line 117
        memcpy(sjv_newData, _parent->data, _parent->dataSize * sizeof(sji_nauScene3dElement_model*));
#line 117
    }
#line 117
    (*_return) = (sjs_array_heap_model_heap*)malloc(sizeof(sjs_array_heap_model_heap));
#line 117
    (*_return)->_refCount = 1;
#line 115
    (*_return)->dataSize = newSize;
#line 130
    (*_return)->data = sjv_newData;
#line 4
    (*_return)->_isGlobal = false;
#line 115
    sjt_dot546 = _parent;
#line 130
    (*_return)->count = (sjt_dot546)->count;
#line 130
    sjf_array_heap_model_heap((*_return));
}

void sjf_array_heap_model_heap(sjs_array_heap_model_heap* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sji_nauScene3dElement_model*));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_heap_model_initAt(sjs_array_heap_model* _parent, int32_t index, sji_nauScene3dElement_model* item) {
#line 20 "lib/common/array.sj"
    if (index != _parent->count) {
#line 20
        halt("initAt: can only initialize last element\n");		
#line 20
    }
#line 20
    if (index >= _parent->dataSize || index < 0) {
#line 20
        halt("initAt: out of bounds %d:%d\n", index, _parent->dataSize);
#line 20
    }
#line 20
    sji_nauScene3dElement_model** p = (sji_nauScene3dElement_model**)_parent->data;
#line 20
    #line 19 "lib/common/array.sj"
p[index] = item;
#line 19
p[index]->_refCount++;
;
#line 20
    _parent->count = index + 1;
}

void sjf_array_heap_model_setAt(sjs_array_heap_model* _parent, int32_t index, sji_nauScene3dElement_model* item) {
#line 35 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 35
        halt("setAt: out of bounds %d:%d\n", index, _parent->count);
#line 35
    }
#line 35
    sji_nauScene3dElement_model** p = (sji_nauScene3dElement_model**)_parent->data;
#line 35
    p[index]->_refCount--;
if (p[index]->_refCount <= 0) {
    sji_nauScene3dElement_model_destroy(p[index]);
}
;
#line 35
    #line 34 "lib/common/array.sj"
p[index] = item;
#line 34
p[index]->_refCount++;
;
}

void sjf_array_heap_model_sortcb(sjs_array_heap_model* _parent, cb_heap_model_heap_model_i32 cb) {
    int32_t sjt_compare10;
    int32_t sjt_compare9;
    sjs_array_heap_model* sjt_dot51;
    bool sjt_ifElse2;

#line 201 "lib/common/array.sj"
    sjt_dot51 = _parent;
#line 202
    sjt_compare9 = (sjt_dot51)->count;
#line 202
    sjt_compare10 = 1;
#line 202
    sjt_ifElse2 = sjt_compare9 > sjt_compare10;
    if (sjt_ifElse2) {
        sjs_array_heap_model* sjt_dot52;
        int32_t sjt_functionParam41;
        int32_t sjt_functionParam42;
        cb_heap_model_heap_model_i32 sjt_functionParam43;
        int32_t sjt_math57;
        int32_t sjt_math58;

#line 203 "lib/common/array.sj"
        sjt_functionParam41 = 0;
#line 201
        sjt_dot52 = _parent;
#line 203
        sjt_math57 = (sjt_dot52)->count;
#line 203
        sjt_math58 = 1;
#line 203
        sjt_functionParam42 = sjt_math57 - sjt_math58;
#line 201
        sjt_functionParam43 = cb;
#line 201
        sjf_array_heap_model__quickSortCallback(_parent, sjt_functionParam41, sjt_functionParam42, sjt_functionParam43);
    }
}

void sjf_array_i32(sjs_array_i32* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(int32_t));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_i32_copy(sjs_array_i32* _this, sjs_array_i32* _from) {
#line 1 "lib/common/array.sj"
    _this->dataSize = _from->dataSize;
#line 1
    _this->data = _from->data;
#line 1
    _this->_isGlobal = _from->_isGlobal;
#line 1
    _this->count = _from->count;
#line 280
    _this->data = _from->data;
#line 280
    if (!_this->_isGlobal && _this->data) {
#line 280
        _retain(_this->data);
#line 280
    }
}

void sjf_array_i32_destroy(sjs_array_i32* _this) {
#line 287 "lib/common/array.sj"
    if (!_this->_isGlobal && _this->data) {
#line 287
        if (_release(_this->data)) {
#line 287
            free((int32_t*)_this->data);
#line 287
        }
#line 287
    }
}

void sjf_array_i32_heap(sjs_array_i32_heap* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(int32_t));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_i32_initAt(sjs_array_i32* _parent, int32_t index, int32_t item) {
#line 20 "lib/common/array.sj"
    if (index != _parent->count) {
#line 20
        halt("initAt: can only initialize last element\n");		
#line 20
    }
#line 20
    if (index >= _parent->dataSize || index < 0) {
#line 20
        halt("initAt: out of bounds %d:%d\n", index, _parent->dataSize);
#line 20
    }
#line 20
    int32_t* p = (int32_t*)_parent->data;
#line 20
    #line 19 "lib/common/array.sj"
p[index] = item;
;
#line 20
    _parent->count = index + 1;
}

void sjf_array_texture(sjs_array_texture* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sjs_texture));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_texture_copy(sjs_array_texture* _this, sjs_array_texture* _from) {
#line 1 "lib/common/array.sj"
    _this->dataSize = _from->dataSize;
#line 1
    _this->data = _from->data;
#line 1
    _this->_isGlobal = _from->_isGlobal;
#line 1
    _this->count = _from->count;
#line 280
    _this->data = _from->data;
#line 280
    if (!_this->_isGlobal && _this->data) {
#line 280
        _retain(_this->data);
#line 280
    }
}

void sjf_array_texture_destroy(sjs_array_texture* _this) {
#line 287 "lib/common/array.sj"
    if (!_this->_isGlobal && _this->data) {
#line 287
        if (_release(_this->data)) {
#line 287
            free((sjs_texture*)_this->data);
#line 287
        }
#line 287
    }
}

void sjf_array_texture_getAt(sjs_array_texture* _parent, int32_t index, sjs_texture* _return) {
#line 8 "lib/common/array.sj"
    if (index >= _parent->count || index < 0) {
#line 8
        halt("getAt: out of bounds\n");
#line 8
    }
#line 8
    sjs_texture* p = (sjs_texture*)_parent->data;
#line 8
    #line 8 "lib/common/array.sj"
sjf_texture_copy(_return, &p[index]);
;		
}

void sjf_array_texture_heap(sjs_array_texture_heap* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sjs_texture));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_texture_initAt(sjs_array_texture* _parent, int32_t index, sjs_texture* item) {
#line 20 "lib/common/array.sj"
    if (index != _parent->count) {
#line 20
        halt("initAt: can only initialize last element\n");		
#line 20
    }
#line 20
    if (index >= _parent->dataSize || index < 0) {
#line 20
        halt("initAt: out of bounds %d:%d\n", index, _parent->dataSize);
#line 20
    }
#line 20
    sjs_texture* p = (sjs_texture*)_parent->data;
#line 20
    #line 19 "lib/common/array.sj"
sjf_texture_copy(&p[index], item);
;
#line 20
    _parent->count = index + 1;
}

void sjf_array_texture_map_heap_model(sjs_array_texture* _parent, cb_texture_heap_model cb, sjs_array_heap_model* _return) {
    int32_t i;
    sjs_array_texture* sjt_dot1315;
    sjs_array_texture* sjt_dot1316;
    sjs_array_texture* sjt_dot1317;
    int32_t sjt_forEnd8;
    int32_t sjt_forStart8;
    void* sjv_newData;

#line 66 "lib/common/array.sj"
    sjv_newData = 0;
#line 67
    sjv_newData = malloc(_parent->count * sizeof(sji_nauScene3dElement_model*));
#line 70
    sjt_forStart8 = 0;
#line 65
    sjt_dot1315 = _parent;
#line 70
    sjt_forEnd8 = (sjt_dot1315)->count;
#line 70
    i = sjt_forStart8;
    while (i < sjt_forEnd8) {
        sjs_texture sjt_call30;
        cb_texture_heap_model sjt_callback5;
        sjs_texture* sjt_functionParam200;
        int32_t sjt_functionParam201;
        sji_nauScene3dElement_model* sjv_newItem;

#line 65 "lib/common/array.sj"
        sjt_callback5 = cb;
#line 70
        sjt_functionParam201 = i;
#line 70
        sjf_array_texture_getAt(_parent, sjt_functionParam201, &sjt_call30);
#line 71
        sjt_functionParam200 = &sjt_call30;
#line 71
        sjt_callback5._cb_heap(sjt_callback5._parent, sjt_functionParam200, &sjv_newItem);
#line 72
        sji_nauScene3dElement_model** p = (sji_nauScene3dElement_model**)sjv_newData;
#line 72
        #line 72 "lib/common/array.sj"
p[i] = sjv_newItem;
#line 72
p[i]->_refCount++;
;
#line 70
        i++;

        sjv_newItem->_refCount--;
        if (sjv_newItem->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_newItem);
        }
        sjf_texture_destroy(&sjt_call30);
    }

#line 65
    sjt_dot1316 = _parent;
#line 77
    _return->dataSize = (sjt_dot1316)->count;
#line 77
    _return->data = sjv_newData;
#line 4
    _return->_isGlobal = false;
#line 65
    sjt_dot1317 = _parent;
#line 77
    _return->count = (sjt_dot1317)->count;
#line 77
    sjf_array_heap_model(_return);
}

void sjf_array_texture_map_heap_model_heap(sjs_array_texture* _parent, cb_texture_heap_model cb, sjs_array_heap_model_heap** _return) {
    int32_t i;
    sjs_array_texture* sjt_dot1318;
    sjs_array_texture* sjt_dot1319;
    sjs_array_texture* sjt_dot1320;
    int32_t sjt_forEnd9;
    int32_t sjt_forStart9;
    void* sjv_newData;

#line 66 "lib/common/array.sj"
    sjv_newData = 0;
#line 67
    sjv_newData = malloc(_parent->count * sizeof(sji_nauScene3dElement_model*));
#line 70
    sjt_forStart9 = 0;
#line 65
    sjt_dot1318 = _parent;
#line 70
    sjt_forEnd9 = (sjt_dot1318)->count;
#line 70
    i = sjt_forStart9;
    while (i < sjt_forEnd9) {
        sjs_texture sjt_call31;
        cb_texture_heap_model sjt_callback6;
        sjs_texture* sjt_functionParam202;
        int32_t sjt_functionParam203;
        sji_nauScene3dElement_model* sjv_newItem;

#line 65 "lib/common/array.sj"
        sjt_callback6 = cb;
#line 70
        sjt_functionParam203 = i;
#line 70
        sjf_array_texture_getAt(_parent, sjt_functionParam203, &sjt_call31);
#line 71
        sjt_functionParam202 = &sjt_call31;
#line 71
        sjt_callback6._cb_heap(sjt_callback6._parent, sjt_functionParam202, &sjv_newItem);
#line 72
        sji_nauScene3dElement_model** p = (sji_nauScene3dElement_model**)sjv_newData;
#line 72
        #line 72 "lib/common/array.sj"
p[i] = sjv_newItem;
#line 72
p[i]->_refCount++;
;
#line 70
        i++;

        sjv_newItem->_refCount--;
        if (sjv_newItem->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_newItem);
        }
        sjf_texture_destroy(&sjt_call31);
    }

#line 70
    (*_return) = (sjs_array_heap_model_heap*)malloc(sizeof(sjs_array_heap_model_heap));
#line 70
    (*_return)->_refCount = 1;
#line 65
    sjt_dot1319 = _parent;
#line 77
    (*_return)->dataSize = (sjt_dot1319)->count;
#line 77
    (*_return)->data = sjv_newData;
#line 4
    (*_return)->_isGlobal = false;
#line 65
    sjt_dot1320 = _parent;
#line 77
    (*_return)->count = (sjt_dot1320)->count;
#line 77
    sjf_array_heap_model_heap((*_return));
}

void sjf_array_vertex_location_texture_normal(sjs_array_vertex_location_texture_normal* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sjs_vertex_location_texture_normal));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_vertex_location_texture_normal_copy(sjs_array_vertex_location_texture_normal* _this, sjs_array_vertex_location_texture_normal* _from) {
#line 1 "lib/common/array.sj"
    _this->dataSize = _from->dataSize;
#line 1
    _this->data = _from->data;
#line 1
    _this->_isGlobal = _from->_isGlobal;
#line 1
    _this->count = _from->count;
#line 280
    _this->data = _from->data;
#line 280
    if (!_this->_isGlobal && _this->data) {
#line 280
        _retain(_this->data);
#line 280
    }
}

void sjf_array_vertex_location_texture_normal_destroy(sjs_array_vertex_location_texture_normal* _this) {
#line 287 "lib/common/array.sj"
    if (!_this->_isGlobal && _this->data) {
#line 287
        if (_release(_this->data)) {
#line 287
            free((sjs_vertex_location_texture_normal*)_this->data);
#line 287
        }
#line 287
    }
}

void sjf_array_vertex_location_texture_normal_heap(sjs_array_vertex_location_texture_normal_heap* _this) {
#line 266 "lib/common/array.sj"
    if (_this->dataSize < 0) {
#line 266
        halt("size is less than zero");
#line 266
    }
#line 266
    if (!_this->data) {
#line 266
        _this->data = malloc(_this->dataSize * sizeof(sjs_vertex_location_texture_normal));
#line 266
        if (!_this->data) {
#line 266
            halt("grow: out of memory\n");
#line 266
        }
#line 266
    }
}

void sjf_array_vertex_location_texture_normal_initAt(sjs_array_vertex_location_texture_normal* _parent, int32_t index, sjs_vertex_location_texture_normal* item) {
#line 20 "lib/common/array.sj"
    if (index != _parent->count) {
#line 20
        halt("initAt: can only initialize last element\n");		
#line 20
    }
#line 20
    if (index >= _parent->dataSize || index < 0) {
#line 20
        halt("initAt: out of bounds %d:%d\n", index, _parent->dataSize);
#line 20
    }
#line 20
    sjs_vertex_location_texture_normal* p = (sjs_vertex_location_texture_normal*)_parent->data;
#line 20
    #line 19 "lib/common/array.sj"
sjf_vertex_location_texture_normal_copy(&p[index], item);
;
#line 20
    _parent->count = index + 1;
}

void sjf_boxRenderer(sjs_boxRenderer* _this) {
#line 19 "lib/ui/boxRenderer.sj"
    _this->buffer = vertex_buffer_new("vertex:3f,color:4f");
#line 19
    float x0 = (float)_this->rect.x;
#line 19
    float y0 = (float)(_this->rect.y + _this->rect.h);
#line 19
    float x1 = (float)(_this->rect.x + _this->rect.w);
#line 19
    float y1 = (float)_this->rect.y;
#line 19
    GLuint index = (GLuint)_this->buffer->vertices->size;
#line 19
    GLuint indices[] = { //
#line 19
    index, index+1, index+2,
#line 19
    index, index+2, index+3 };
#line 19
    vertex3_color4_t vertices[] = { //
#line 19
    { x0, y1, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a },
#line 19
    { x0, y0, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a },
#line 19
    { x1, y0, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a },
#line 19
    { x1, y1, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a } };
#line 19
    vertex_buffer_push_back_indices( _this->buffer, indices, 6 );
#line 19
    vertex_buffer_push_back_vertices( _this->buffer, vertices, 4 );
}

void sjf_boxRenderer_copy(sjs_boxRenderer* _this, sjs_boxRenderer* _from) {
#line 1 "lib/ui/boxRenderer.sj"
    sjf_rect_copy(&_this->rect, &_from->rect);
#line 1
    sjf_color_copy(&_this->color, &_from->color);
#line 39
    _this->buffer = _from->buffer;
#line 39
    _retain(_this->buffer);
}

void sjf_boxRenderer_destroy(sjs_boxRenderer* _this) {
#line 44 "lib/ui/boxRenderer.sj"
    if (_release(_this->buffer)) {
#line 44
        vertex_buffer_delete(_this->buffer);
#line 44
    }  
}

void sjf_boxRenderer_heap(sjs_boxRenderer_heap* _this) {
#line 19 "lib/ui/boxRenderer.sj"
    _this->buffer = vertex_buffer_new("vertex:3f,color:4f");
#line 19
    float x0 = (float)_this->rect.x;
#line 19
    float y0 = (float)(_this->rect.y + _this->rect.h);
#line 19
    float x1 = (float)(_this->rect.x + _this->rect.w);
#line 19
    float y1 = (float)_this->rect.y;
#line 19
    GLuint index = (GLuint)_this->buffer->vertices->size;
#line 19
    GLuint indices[] = { //
#line 19
    index, index+1, index+2,
#line 19
    index, index+2, index+3 };
#line 19
    vertex3_color4_t vertices[] = { //
#line 19
    { x0, y1, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a },
#line 19
    { x0, y0, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a },
#line 19
    { x1, y0, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a },
#line 19
    { x1, y1, 0.0f,  _this->color.r, _this->color.g, _this->color.b, _this->color.a } };
#line 19
    vertex_buffer_push_back_indices( _this->buffer, indices, 6 );
#line 19
    vertex_buffer_push_back_vertices( _this->buffer, vertices, 4 );
}

void sjf_boxRenderer_render(sjs_boxRenderer* _parent, sjs_scene2d* scene) {
#line 9 "lib/ui/boxRenderer.sj"
    glUseProgram(sjv_boxShader.id);
#line 9
    glUniformMatrix4fv(glGetUniformLocation(sjv_boxShader.id, "model" ), 1, 0, (GLfloat*)&scene->model);
#line 9
    glUniformMatrix4fv(glGetUniformLocation(sjv_boxShader.id, "view" ), 1, 0, (GLfloat*)&scene->view);
#line 9
    glUniformMatrix4fv(glGetUniformLocation(sjv_boxShader.id, "projection" ), 1, 0, (GLfloat*)&scene->projection);
#line 9
    vertex_buffer_render(_parent->buffer, GL_TRIANGLES);
}

void sjf_color(sjs_color* _this) {
}

void sjf_color_asVec3(sjs_color* _parent, sjs_vec3* _return) {
    sjs_color* sjt_dot1302;
    sjs_color* sjt_dot1303;
    sjs_color* sjt_dot1304;

#line 19 "lib/ui/color.sj"
    sjt_dot1302 = _parent;
#line 20
    _return->x = (sjt_dot1302)->r;
#line 19
    sjt_dot1303 = _parent;
#line 20
    _return->y = (sjt_dot1303)->g;
#line 19
    sjt_dot1304 = _parent;
#line 20
    _return->z = (sjt_dot1304)->b;
#line 20
    sjf_vec3(_return);
}

void sjf_color_asVec3_heap(sjs_color* _parent, sjs_vec3_heap** _return) {
    sjs_color* sjt_dot1305;
    sjs_color* sjt_dot1306;
    sjs_color* sjt_dot1307;

    (*_return) = (sjs_vec3_heap*)malloc(sizeof(sjs_vec3_heap));
    (*_return)->_refCount = 1;
#line 19 "lib/ui/color.sj"
    sjt_dot1305 = _parent;
#line 20
    (*_return)->x = (sjt_dot1305)->r;
#line 19
    sjt_dot1306 = _parent;
#line 20
    (*_return)->y = (sjt_dot1306)->g;
#line 19
    sjt_dot1307 = _parent;
#line 20
    (*_return)->z = (sjt_dot1307)->b;
#line 20
    sjf_vec3_heap((*_return));
}

void sjf_color_copy(sjs_color* _this, sjs_color* _from) {
#line 9 "lib/ui/color.sj"
    _this->r = _from->r;
#line 9
    _this->g = _from->g;
#line 9
    _this->b = _from->b;
#line 9
    _this->a = _from->a;
}

void sjf_color_destroy(sjs_color* _this) {
}

void sjf_color_heap(sjs_color_heap* _this) {
}

void sjf_crossHairsElement(sjs_crossHairsElement* _this) {
}

sjs_object* sjf_crossHairsElement_asInterface(sjs_crossHairsElement* _this, int typeId) {
    switch (typeId) {
        case sji_element_typeId:  {
            return (sjs_object*)sjf_crossHairsElement_as_sji_element(_this);
        }
    }

    return 0;
}

sji_element* sjf_crossHairsElement_as_sji_element(sjs_crossHairsElement* _this) {
    sji_element* _interface;
    _interface = (sji_element*)malloc(sizeof(sji_element));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_crossHairsElement_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_crossHairsElement_asInterface;
    _interface->getSize = (void(*)(void*,sjs_size*, sjs_size*))sjf_crossHairsElement_getSize;
    _interface->getSize_heap = (void(*)(void*,sjs_size*, sjs_size_heap**))sjf_crossHairsElement_getSize_heap;
    _interface->getRect = (void(*)(void*, sjs_rect**))sjf_crossHairsElement_getRect;
    _interface->setRect = (void(*)(void*,sjs_rect*))sjf_crossHairsElement_setRect;
    _interface->render = (void(*)(void*,sjs_scene2d*))sjf_crossHairsElement_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_crossHairsElement_fireMouseEvent;

    return _interface;
}

void sjf_crossHairsElement_copy(sjs_crossHairsElement* _this, sjs_crossHairsElement* _from) {
#line 1 "lib/ui/crossHairsElement.sj"
    sjf_color_copy(&_this->color, &_from->color);
#line 1
    sjf_rect_copy(&_this->_rect, &_from->_rect);
#line 1
    _this->_topDownRenderer = 0;
#line 1
    sjf_boxRenderer_copy((sjs_boxRenderer*)(((char*)_this->_topDownRenderer) + sizeof(intptr_t)), (sjs_boxRenderer*)(((char*)_from->_topDownRenderer) + sizeof(intptr_t)));
#line 1
    _this->_leftRightRenderer = 0;
#line 1
    sjf_boxRenderer_copy((sjs_boxRenderer*)(((char*)_this->_leftRightRenderer) + sizeof(intptr_t)), (sjs_boxRenderer*)(((char*)_from->_leftRightRenderer) + sizeof(intptr_t)));
#line 1
    sjf_point_copy(&_this->_point, &_from->_point);
}

void sjf_crossHairsElement_destroy(sjs_crossHairsElement* _this) {
    if (_this->_topDownRenderer != 0) {
        _this->_topDownRenderer->_refCount--;
        if (_this->_topDownRenderer->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)_this->_topDownRenderer) + sizeof(intptr_t)));
        }
    }

    if (_this->_leftRightRenderer != 0) {
        _this->_leftRightRenderer->_refCount--;
        if (_this->_leftRightRenderer->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)_this->_leftRightRenderer) + sizeof(intptr_t)));
        }
    }
}

void sjf_crossHairsElement_fireMouseEvent(sjs_crossHairsElement* _parent, sjs_point* point, int32_t eventId) {
    sjs_crossHairsElement* sjt_dot1405;
    sjs_point* sjt_functionParam474;
    bool sjt_ifElse23;
    sjs_rect* sjt_parent141;

#line 44 "lib/ui/crossHairsElement.sj"
    sjt_dot1405 = _parent;
#line 11 "lib/ui/rect.sj"
    sjt_parent141 = &(sjt_dot1405)->_rect;
#line 44 "lib/ui/crossHairsElement.sj"
    sjt_functionParam474 = point;
#line 44
    sjf_rect_containsPoint(sjt_parent141, sjt_functionParam474, &sjt_ifElse23);
    if (sjt_ifElse23) {
        int32_t sjt_compare59;
        int32_t sjt_compare60;
        bool sjt_ifElse24;

#line 44 "lib/ui/crossHairsElement.sj"
        sjt_compare59 = eventId;
#line 46
        sjt_compare60 = sjv_mouseEvent_move;
#line 46
        sjt_ifElse24 = sjt_compare59 == sjt_compare60;
        if (sjt_ifElse24) {
            sjs_point* sjt_copy31;
            sjs_crossHairsElement* sjt_dot1406;
            sjs_crossHairsElement* sjt_dot1407;
            sjs_crossHairsElement* sjt_dot1408;

#line 44 "lib/ui/crossHairsElement.sj"
            sjt_dot1406 = _parent;
#line 44
            sjt_copy31 = point;
#line 47
            sjf_point_copy(&sjt_dot1406->_point, sjt_copy31);
#line 44
            sjt_dot1407 = _parent;
            if (sjt_dot1407->_topDownRenderer != 0) {
                sjt_dot1407->_topDownRenderer->_refCount--;
                if (sjt_dot1407->_topDownRenderer->_refCount <= 0) {
                    sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_dot1407->_topDownRenderer) + sizeof(intptr_t)));
                }
            }

#line 48
            sjt_dot1407->_topDownRenderer = 0;
            if (sjt_dot1407->_topDownRenderer != 0) {
                sjt_dot1407->_topDownRenderer->_refCount++;
            }

#line 44
            sjt_dot1408 = _parent;
            if (sjt_dot1408->_leftRightRenderer != 0) {
                sjt_dot1408->_leftRightRenderer->_refCount--;
                if (sjt_dot1408->_leftRightRenderer->_refCount <= 0) {
                    sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_dot1408->_leftRightRenderer) + sizeof(intptr_t)));
                }
            }

#line 49
            sjt_dot1408->_leftRightRenderer = 0;
            if (sjt_dot1408->_leftRightRenderer != 0) {
                sjt_dot1408->_leftRightRenderer->_refCount++;
            }
        }
    }
}

void sjf_crossHairsElement_getRect(sjs_crossHairsElement* _parent, sjs_rect** _return) {
    sjs_crossHairsElement* sjt_dot1368;

#line 12 "lib/ui/crossHairsElement.sj"
    sjt_dot1368 = _parent;
#line 12
    (*_return) = &(sjt_dot1368)->_rect;
}

void sjf_crossHairsElement_getSize(sjs_crossHairsElement* _parent, sjs_size* maxSize, sjs_size* _return) {
    sjs_size* sjt_dot1364;
    sjs_size* sjt_dot1365;

#line 8 "lib/ui/crossHairsElement.sj"
    sjt_dot1364 = maxSize;
#line 9
    _return->w = (sjt_dot1364)->w;
#line 8
    sjt_dot1365 = maxSize;
#line 9
    _return->h = (sjt_dot1365)->h;
#line 9
    sjf_size(_return);
}

void sjf_crossHairsElement_getSize_heap(sjs_crossHairsElement* _parent, sjs_size* maxSize, sjs_size_heap** _return) {
    sjs_size* sjt_dot1366;
    sjs_size* sjt_dot1367;

    (*_return) = (sjs_size_heap*)malloc(sizeof(sjs_size_heap));
    (*_return)->_refCount = 1;
#line 8 "lib/ui/crossHairsElement.sj"
    sjt_dot1366 = maxSize;
#line 9
    (*_return)->w = (sjt_dot1366)->w;
#line 8
    sjt_dot1367 = maxSize;
#line 9
    (*_return)->h = (sjt_dot1367)->h;
#line 9
    sjf_size_heap((*_return));
}

void sjf_crossHairsElement_heap(sjs_crossHairsElement_heap* _this) {
}

sjs_object* sjf_crossHairsElement_heap_asInterface(sjs_crossHairsElement_heap* _this, int typeId) {
    switch (typeId) {
        case sji_element_typeId:  {
            return (sjs_object*)sjf_crossHairsElement_heap_as_sji_element(_this);
        }
    }

    return 0;
}

sji_element* sjf_crossHairsElement_heap_as_sji_element(sjs_crossHairsElement_heap* _this) {
    sji_element* _interface;
    _interface = (sji_element*)malloc(sizeof(sji_element));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_crossHairsElement_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_crossHairsElement_heap_asInterface;
    _interface->getSize = (void(*)(void*,sjs_size*, sjs_size*))sjf_crossHairsElement_getSize;
    _interface->getSize_heap = (void(*)(void*,sjs_size*, sjs_size_heap**))sjf_crossHairsElement_getSize_heap;
    _interface->getRect = (void(*)(void*, sjs_rect**))sjf_crossHairsElement_getRect;
    _interface->setRect = (void(*)(void*,sjs_rect*))sjf_crossHairsElement_setRect;
    _interface->render = (void(*)(void*,sjs_scene2d*))sjf_crossHairsElement_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_crossHairsElement_fireMouseEvent;

    return _interface;
}

void sjf_crossHairsElement_render(sjs_crossHairsElement* _parent, sjs_scene2d* scene) {
    bool result48;
    bool result49;
    sjs_crossHairsElement* sjt_dot1373;
    sjs_crossHairsElement* sjt_dot1382;
    sjs_crossHairsElement* sjt_dot1391;
    sjs_crossHairsElement* sjt_dot1393;
    bool sjt_ifElse19;
    bool sjt_ifElse20;
    bool sjt_ifElse21;
    bool sjt_ifElse22;
    sjs_boxRenderer_heap* sjt_isEmpty1;
    sjs_boxRenderer_heap* sjt_isEmpty2;
    sjs_boxRenderer_heap* sjt_isEmpty3;
    sjs_boxRenderer_heap* sjt_isEmpty4;
    bool sjt_not3;
    bool sjt_not4;

#line 23 "lib/ui/crossHairsElement.sj"
    sjt_dot1373 = _parent;
#line 24
    sjt_isEmpty1 = (sjt_dot1373)->_topDownRenderer;
    if (sjt_isEmpty1 != 0) {
        sjt_isEmpty1->_refCount++;
    }

#line 24
    sjt_ifElse19 = (sjt_isEmpty1 == 0);
    if (sjt_ifElse19) {
        sjs_color* sjt_copy29;
        sjs_crossHairsElement* sjt_dot1374;
        sjs_point* sjt_dot1375;
        sjs_crossHairsElement* sjt_dot1376;
        sjs_rect* sjt_dot1377;
        sjs_crossHairsElement* sjt_dot1378;
        sjs_rect* sjt_dot1379;
        sjs_crossHairsElement* sjt_dot1380;
        sjs_crossHairsElement* sjt_dot1381;
        sjs_boxRenderer_heap* sjt_value1;

#line 23 "lib/ui/crossHairsElement.sj"
        sjt_dot1374 = _parent;
#line 23
        sjt_value1 = (sjs_boxRenderer_heap*)malloc(sizeof(sjs_boxRenderer_heap));
#line 23
        sjt_value1->_refCount = 1;
#line 23
        sjt_dot1376 = _parent;
#line 1 "lib/ui/point.sj"
        sjt_dot1375 = &(sjt_dot1376)->_point;
#line 26 "lib/ui/crossHairsElement.sj"
        sjt_value1->rect.x = (sjt_dot1375)->x;
#line 23
        sjt_dot1378 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot1377 = &(sjt_dot1378)->_rect;
#line 26 "lib/ui/crossHairsElement.sj"
        sjt_value1->rect.y = (sjt_dot1377)->y;
#line 26
        sjt_value1->rect.w = 1;
#line 23
        sjt_dot1380 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot1379 = &(sjt_dot1380)->_rect;
#line 26 "lib/ui/crossHairsElement.sj"
        sjt_value1->rect.h = (sjt_dot1379)->h;
#line 26
        sjf_rect(&sjt_value1->rect);
#line 23
        sjt_dot1381 = _parent;
#line 27
        sjt_copy29 = &(sjt_dot1381)->color;
#line 27
        sjf_color_copy(&sjt_value1->color, sjt_copy29);
#line 27
        sjf_boxRenderer_heap(sjt_value1);
        if (sjt_dot1374->_topDownRenderer != 0) {
            sjt_dot1374->_topDownRenderer->_refCount--;
            if (sjt_dot1374->_topDownRenderer->_refCount <= 0) {
                sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_dot1374->_topDownRenderer) + sizeof(intptr_t)));
            }
        }

#line 25
        sjt_dot1374->_topDownRenderer = sjt_value1;
        if (sjt_dot1374->_topDownRenderer != 0) {
            sjt_dot1374->_topDownRenderer->_refCount++;
        }

        sjt_value1->_refCount--;
        if (sjt_value1->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_value1) + sizeof(intptr_t)));
        }
    }

#line 23
    sjt_dot1382 = _parent;
#line 30
    sjt_isEmpty2 = (sjt_dot1382)->_leftRightRenderer;
    if (sjt_isEmpty2 != 0) {
        sjt_isEmpty2->_refCount++;
    }

#line 30
    sjt_ifElse20 = (sjt_isEmpty2 == 0);
    if (sjt_ifElse20) {
        sjs_color* sjt_copy30;
        sjs_crossHairsElement* sjt_dot1383;
        sjs_rect* sjt_dot1384;
        sjs_crossHairsElement* sjt_dot1385;
        sjs_point* sjt_dot1386;
        sjs_crossHairsElement* sjt_dot1387;
        sjs_rect* sjt_dot1388;
        sjs_crossHairsElement* sjt_dot1389;
        sjs_crossHairsElement* sjt_dot1390;
        sjs_boxRenderer_heap* sjt_value2;

#line 23 "lib/ui/crossHairsElement.sj"
        sjt_dot1383 = _parent;
#line 23
        sjt_value2 = (sjs_boxRenderer_heap*)malloc(sizeof(sjs_boxRenderer_heap));
#line 23
        sjt_value2->_refCount = 1;
#line 23
        sjt_dot1385 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot1384 = &(sjt_dot1385)->_rect;
#line 32 "lib/ui/crossHairsElement.sj"
        sjt_value2->rect.x = (sjt_dot1384)->x;
#line 23
        sjt_dot1387 = _parent;
#line 1 "lib/ui/point.sj"
        sjt_dot1386 = &(sjt_dot1387)->_point;
#line 32 "lib/ui/crossHairsElement.sj"
        sjt_value2->rect.y = (sjt_dot1386)->y;
#line 23
        sjt_dot1389 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot1388 = &(sjt_dot1389)->_rect;
#line 32 "lib/ui/crossHairsElement.sj"
        sjt_value2->rect.w = (sjt_dot1388)->w;
#line 32
        sjt_value2->rect.h = 1;
#line 32
        sjf_rect(&sjt_value2->rect);
#line 23
        sjt_dot1390 = _parent;
#line 33
        sjt_copy30 = &(sjt_dot1390)->color;
#line 33
        sjf_color_copy(&sjt_value2->color, sjt_copy30);
#line 33
        sjf_boxRenderer_heap(sjt_value2);
        if (sjt_dot1383->_leftRightRenderer != 0) {
            sjt_dot1383->_leftRightRenderer->_refCount--;
            if (sjt_dot1383->_leftRightRenderer->_refCount <= 0) {
                sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_dot1383->_leftRightRenderer) + sizeof(intptr_t)));
            }
        }

#line 31
        sjt_dot1383->_leftRightRenderer = sjt_value2;
        if (sjt_dot1383->_leftRightRenderer != 0) {
            sjt_dot1383->_leftRightRenderer->_refCount++;
        }

        sjt_value2->_refCount--;
        if (sjt_value2->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_value2) + sizeof(intptr_t)));
        }
    }

#line 23
    sjt_dot1391 = _parent;
#line 36
    sjt_isEmpty3 = (sjt_dot1391)->_topDownRenderer;
    if (sjt_isEmpty3 != 0) {
        sjt_isEmpty3->_refCount++;
    }

#line 36
    sjt_not3 = (sjt_isEmpty3 == 0);
#line 36
    result48 = !sjt_not3;
#line 36
    sjt_ifElse21 = result48;
    if (sjt_ifElse21) {
        sjs_crossHairsElement* sjt_dot1392;
        sjs_scene2d* sjt_functionParam472;
        sjs_boxRenderer_heap* sjt_getValue1;
        sjs_boxRenderer* sjt_parent139;

#line 23 "lib/ui/crossHairsElement.sj"
        sjt_dot1392 = _parent;
#line 36
        sjt_getValue1 = (sjt_dot1392)->_topDownRenderer;
        if (sjt_getValue1 != 0) {
            sjt_getValue1->_refCount++;
        }

#line 36
        sjt_parent139 = (sjs_boxRenderer*)(((char*)sjt_getValue1) + sizeof(intptr_t));
#line 23
        sjt_functionParam472 = scene;
#line 23
        sjf_boxRenderer_render(sjt_parent139, sjt_functionParam472);

        if (sjt_getValue1 != 0) {
            sjt_getValue1->_refCount--;
            if (sjt_getValue1->_refCount <= 0) {
                sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_getValue1) + sizeof(intptr_t)));
            }
        }
    }

#line 23
    sjt_dot1393 = _parent;
#line 37
    sjt_isEmpty4 = (sjt_dot1393)->_leftRightRenderer;
    if (sjt_isEmpty4 != 0) {
        sjt_isEmpty4->_refCount++;
    }

#line 37
    sjt_not4 = (sjt_isEmpty4 == 0);
#line 37
    result49 = !sjt_not4;
#line 37
    sjt_ifElse22 = result49;
    if (sjt_ifElse22) {
        sjs_crossHairsElement* sjt_dot1394;
        sjs_scene2d* sjt_functionParam473;
        sjs_boxRenderer_heap* sjt_getValue2;
        sjs_boxRenderer* sjt_parent140;

#line 23 "lib/ui/crossHairsElement.sj"
        sjt_dot1394 = _parent;
#line 37
        sjt_getValue2 = (sjt_dot1394)->_leftRightRenderer;
        if (sjt_getValue2 != 0) {
            sjt_getValue2->_refCount++;
        }

#line 37
        sjt_parent140 = (sjs_boxRenderer*)(((char*)sjt_getValue2) + sizeof(intptr_t));
#line 23
        sjt_functionParam473 = scene;
#line 23
        sjf_boxRenderer_render(sjt_parent140, sjt_functionParam473);

        if (sjt_getValue2 != 0) {
            sjt_getValue2->_refCount--;
            if (sjt_getValue2->_refCount <= 0) {
                sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_getValue2) + sizeof(intptr_t)));
            }
        }
    }

    if (sjt_isEmpty1 != 0) {
        sjt_isEmpty1->_refCount--;
        if (sjt_isEmpty1->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_isEmpty1) + sizeof(intptr_t)));
        }
    }
    if (sjt_isEmpty2 != 0) {
        sjt_isEmpty2->_refCount--;
        if (sjt_isEmpty2->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_isEmpty2) + sizeof(intptr_t)));
        }
    }
    if (sjt_isEmpty3 != 0) {
        sjt_isEmpty3->_refCount--;
        if (sjt_isEmpty3->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_isEmpty3) + sizeof(intptr_t)));
        }
    }
    if (sjt_isEmpty4 != 0) {
        sjt_isEmpty4->_refCount--;
        if (sjt_isEmpty4->_refCount <= 0) {
            sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_isEmpty4) + sizeof(intptr_t)));
        }
    }
}

void sjf_crossHairsElement_setRect(sjs_crossHairsElement* _parent, sjs_rect* rect_) {
    bool result47;
    sjs_crossHairsElement* sjt_dot1369;
    sjs_rect* sjt_functionParam471;
    bool sjt_ifElse18;
    bool sjt_not2;
    sjs_rect* sjt_parent138;

#line 14 "lib/ui/crossHairsElement.sj"
    sjt_dot1369 = _parent;
#line 15 "lib/ui/rect.sj"
    sjt_parent138 = &(sjt_dot1369)->_rect;
#line 14 "lib/ui/crossHairsElement.sj"
    sjt_functionParam471 = rect_;
#line 14
    sjf_rect_isEqual(sjt_parent138, sjt_functionParam471, &sjt_not2);
#line 15
    result47 = !sjt_not2;
#line 15
    sjt_ifElse18 = result47;
    if (sjt_ifElse18) {
        sjs_rect* sjt_copy28;
        sjs_crossHairsElement* sjt_dot1370;
        sjs_crossHairsElement* sjt_dot1371;
        sjs_crossHairsElement* sjt_dot1372;

#line 14 "lib/ui/crossHairsElement.sj"
        sjt_dot1370 = _parent;
#line 14
        sjt_copy28 = rect_;
#line 16
        sjf_rect_copy(&sjt_dot1370->_rect, sjt_copy28);
#line 14
        sjt_dot1371 = _parent;
        if (sjt_dot1371->_topDownRenderer != 0) {
            sjt_dot1371->_topDownRenderer->_refCount--;
            if (sjt_dot1371->_topDownRenderer->_refCount <= 0) {
                sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_dot1371->_topDownRenderer) + sizeof(intptr_t)));
            }
        }

#line 17
        sjt_dot1371->_topDownRenderer = 0;
        if (sjt_dot1371->_topDownRenderer != 0) {
            sjt_dot1371->_topDownRenderer->_refCount++;
        }

#line 14
        sjt_dot1372 = _parent;
        if (sjt_dot1372->_leftRightRenderer != 0) {
            sjt_dot1372->_leftRightRenderer->_refCount--;
            if (sjt_dot1372->_leftRightRenderer->_refCount <= 0) {
                sjf_boxRenderer_destroy((sjs_boxRenderer*)(((char*)sjt_dot1372->_leftRightRenderer) + sizeof(intptr_t)));
            }
        }

#line 18
        sjt_dot1372->_leftRightRenderer = 0;
        if (sjt_dot1372->_leftRightRenderer != 0) {
            sjt_dot1372->_leftRightRenderer->_refCount++;
        }
    }
}

void sjf_f32_compare(float l, float r, int32_t* _return) {
    float sjt_compare29;
    float sjt_compare30;
    bool sjt_ifElse6;

#line 62 "lib/common/f32.sj"
    sjt_compare29 = l;
#line 62
    sjt_compare30 = r;
#line 63
    sjt_ifElse6 = sjt_compare29 == sjt_compare30;
    if (sjt_ifElse6) {
#line 64 "lib/common/f32.sj"
        (*_return) = 0;
    } else {
        float sjt_compare31;
        float sjt_compare32;
        bool sjt_ifElse7;

#line 62 "lib/common/f32.sj"
        sjt_compare31 = l;
#line 62
        sjt_compare32 = r;
#line 65
        sjt_ifElse7 = sjt_compare31 < sjt_compare32;
        if (sjt_ifElse7) {
            int32_t result3;
            int32_t sjt_negate2;

#line 66 "lib/common/f32.sj"
            sjt_negate2 = 1;
#line 66
            result3 = -sjt_negate2;
#line 66
            (*_return) = result3;
        } else {
#line 68 "lib/common/f32.sj"
            (*_return) = 1;
        }
    }
}

void sjf_f32_cos(float v, float* _return) {
    float sjv_result;

#line 12 "lib/common/f32.sj"
    sjv_result = 0.0f;
#line 13
    sjv_result = cosf(v);
#line 11
    (*_return) = sjv_result;
}

void sjf_f32_max(float a, float b, float* _return) {
    float sjt_compare39;
    float sjt_compare40;
    bool sjt_ifElse11;

#line 35 "lib/common/f32.sj"
    sjt_compare39 = a;
#line 35
    sjt_compare40 = b;
#line 36
    sjt_ifElse11 = sjt_compare39 < sjt_compare40;
    if (sjt_ifElse11) {
#line 35 "lib/common/f32.sj"
        (*_return) = b;
    } else {
#line 35 "lib/common/f32.sj"
        (*_return) = a;
    }
}

void sjf_f32_min(float a, float b, float* _return) {
    float sjt_compare37;
    float sjt_compare38;
    bool sjt_ifElse10;

#line 39 "lib/common/f32.sj"
    sjt_compare37 = a;
#line 39
    sjt_compare38 = b;
#line 40
    sjt_ifElse10 = sjt_compare37 < sjt_compare38;
    if (sjt_ifElse10) {
#line 39 "lib/common/f32.sj"
        (*_return) = a;
    } else {
#line 39 "lib/common/f32.sj"
        (*_return) = b;
    }
}

void sjf_f32_random(float* _return) {
    float sjv_x;

#line 44 "lib/common/f32.sj"
    sjv_x = 0.0f;
#line 45
    sjv_x = (float)rand() / (float)RAND_MAX;
#line 43
    (*_return) = sjv_x;
}

void sjf_f32_sqrt(float v, float* _return) {
    float sjv_result;

#line 4 "lib/common/f32.sj"
    sjv_result = 0.0f;
#line 5
    sjv_result = sqrtf(v);
#line 3
    (*_return) = sjv_result;
}

void sjf_f32_tan(float v, float* _return) {
    float sjv_result;

#line 28 "lib/common/f32.sj"
    sjv_result = 0.0f;
#line 29
    sjv_result = tanf(v);
#line 27
    (*_return) = sjv_result;
}

void sjf_f32_toString(float val, sjs_string* _return) {
    int32_t sjt_math2137;
    int32_t sjt_math2138;
    int32_t sjt_math2139;
    int32_t sjt_math2140;
    int32_t sjv_count;
    void* sjv_data;

#line 52 "lib/common/f32.sj"
    sjv_count = 0;
#line 53
    sjv_data = 0;
#line 54
    sjv_data = malloc(sizeof(char) * 50);
#line 54
    snprintf((char*)sjv_data, 50, "%f", val);
#line 54
    sjv_count = strlen((char*)sjv_data);
#line 59
    _return->count = sjv_count;
#line 59
    sjt_math2137 = sjv_count;
#line 59
    sjt_math2138 = 1;
#line 59
    _return->data.dataSize = sjt_math2137 + sjt_math2138;
#line 59
    _return->data.data = sjv_data;
#line 4 "lib/common/array.sj"
    _return->data._isGlobal = false;
#line 59 "lib/common/f32.sj"
    sjt_math2139 = sjv_count;
#line 59
    sjt_math2140 = 1;
#line 59
    _return->data.count = sjt_math2139 + sjt_math2140;
#line 59
    sjf_array_char(&_return->data);
#line 59
    sjf_string(_return);
}

void sjf_f32_toString_heap(float val, sjs_string_heap** _return) {
    int32_t sjt_math2141;
    int32_t sjt_math2142;
    int32_t sjt_math2143;
    int32_t sjt_math2144;
    int32_t sjv_count;
    void* sjv_data;

#line 52 "lib/common/f32.sj"
    sjv_count = 0;
#line 53
    sjv_data = 0;
#line 54
    sjv_data = malloc(sizeof(char) * 50);
#line 54
    snprintf((char*)sjv_data, 50, "%f", val);
#line 54
    sjv_count = strlen((char*)sjv_data);
#line 54
    (*_return) = (sjs_string_heap*)malloc(sizeof(sjs_string_heap));
#line 54
    (*_return)->_refCount = 1;
#line 59
    (*_return)->count = sjv_count;
#line 59
    sjt_math2141 = sjv_count;
#line 59
    sjt_math2142 = 1;
#line 59
    (*_return)->data.dataSize = sjt_math2141 + sjt_math2142;
#line 59
    (*_return)->data.data = sjv_data;
#line 4 "lib/common/array.sj"
    (*_return)->data._isGlobal = false;
#line 59 "lib/common/f32.sj"
    sjt_math2143 = sjv_count;
#line 59
    sjt_math2144 = 1;
#line 59
    (*_return)->data.count = sjt_math2143 + sjt_math2144;
#line 59
    sjf_array_char(&(*_return)->data);
#line 59
    sjf_string_heap((*_return));
}

void sjf_fillElement(sjs_fillElement* _this) {
}

sjs_object* sjf_fillElement_asInterface(sjs_fillElement* _this, int typeId) {
    switch (typeId) {
        case sji_element_typeId:  {
            return (sjs_object*)sjf_fillElement_as_sji_element(_this);
        }
    }

    return 0;
}

sji_element* sjf_fillElement_as_sji_element(sjs_fillElement* _this) {
    sji_element* _interface;
    _interface = (sji_element*)malloc(sizeof(sji_element));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_fillElement_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_fillElement_asInterface;
    _interface->getSize = (void(*)(void*,sjs_size*, sjs_size*))sjf_fillElement_getSize;
    _interface->getSize_heap = (void(*)(void*,sjs_size*, sjs_size_heap**))sjf_fillElement_getSize_heap;
    _interface->getRect = (void(*)(void*, sjs_rect**))sjf_fillElement_getRect;
    _interface->setRect = (void(*)(void*,sjs_rect*))sjf_fillElement_setRect;
    _interface->render = (void(*)(void*,sjs_scene2d*))sjf_fillElement_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_fillElement_fireMouseEvent;

    return _interface;
}

void sjf_fillElement_copy(sjs_fillElement* _this, sjs_fillElement* _from) {
#line 1 "lib/ui/fillElement.sj"
    sjf_array_heap_element_copy(&_this->children, &_from->children);
#line 1
    sjf_rect_copy(&_this->_rect, &_from->_rect);
}

void sjf_fillElement_destroy(sjs_fillElement* _this) {
}

void sjf_fillElement_fireMouseEvent(sjs_fillElement* _parent, sjs_point* point, int32_t eventId) {
    int32_t i;
    sjs_array_heap_element* sjt_dot14;
    sjs_fillElement* sjt_dot15;
    int32_t sjt_forEnd3;
    int32_t sjt_forStart3;

#line 33 "lib/ui/fillElement.sj"
    sjt_forStart3 = 0;
#line 32
    sjt_dot15 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot14 = &(sjt_dot15)->children;
#line 33 "lib/ui/fillElement.sj"
    sjt_forEnd3 = (sjt_dot14)->count;
#line 33
    i = sjt_forStart3;
    while (i < sjt_forEnd3) {
        sjs_fillElement* sjt_dot16;
        int32_t sjt_functionParam3;
        sjs_point* sjt_interfaceParam3;
        int32_t sjt_interfaceParam4;
        sjs_array_heap_element* sjt_parent5;
        sji_element* sjt_parent6;
        sji_element* sjv_child;

#line 32 "lib/ui/fillElement.sj"
        sjt_dot16 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent5 = &(sjt_dot16)->children;
#line 33 "lib/ui/fillElement.sj"
        sjt_functionParam3 = i;
#line 33
        sjf_array_heap_element_getAt_heap(sjt_parent5, sjt_functionParam3, &sjv_child);
#line 6 "lib/ui/element.sj"
        sjt_parent6 = sjv_child;
#line 32 "lib/ui/fillElement.sj"
        sjt_interfaceParam3 = point;
#line 32
        sjt_interfaceParam4 = eventId;
#line 35
        sjt_parent6->fireMouseEvent((void*)(((char*)sjt_parent6->_parent) + sizeof(intptr_t)), sjt_interfaceParam3, sjt_interfaceParam4);
#line 33
        i++;

        sjv_child->_refCount--;
        if (sjv_child->_refCount <= 0) {
            sji_element_destroy(sjv_child);
        }
    }
}

void sjf_fillElement_getRect(sjs_fillElement* _parent, sjs_rect** _return) {
    sjs_fillElement* sjt_dot5;

#line 9 "lib/ui/fillElement.sj"
    sjt_dot5 = _parent;
#line 9
    (*_return) = &(sjt_dot5)->_rect;
}

void sjf_fillElement_getSize(sjs_fillElement* _parent, sjs_size* maxSize, sjs_size* _return) {
    sjs_size* sjt_dot1;
    sjs_size* sjt_dot2;

#line 5 "lib/ui/fillElement.sj"
    sjt_dot1 = maxSize;
#line 6
    _return->w = (sjt_dot1)->w;
#line 5
    sjt_dot2 = maxSize;
#line 6
    _return->h = (sjt_dot2)->h;
#line 6
    sjf_size(_return);
}

void sjf_fillElement_getSize_heap(sjs_fillElement* _parent, sjs_size* maxSize, sjs_size_heap** _return) {
    sjs_size* sjt_dot3;
    sjs_size* sjt_dot4;

    (*_return) = (sjs_size_heap*)malloc(sizeof(sjs_size_heap));
    (*_return)->_refCount = 1;
#line 5 "lib/ui/fillElement.sj"
    sjt_dot3 = maxSize;
#line 6
    (*_return)->w = (sjt_dot3)->w;
#line 5
    sjt_dot4 = maxSize;
#line 6
    (*_return)->h = (sjt_dot4)->h;
#line 6
    sjf_size_heap((*_return));
}

void sjf_fillElement_heap(sjs_fillElement_heap* _this) {
}

sjs_object* sjf_fillElement_heap_asInterface(sjs_fillElement_heap* _this, int typeId) {
    switch (typeId) {
        case sji_element_typeId:  {
            return (sjs_object*)sjf_fillElement_heap_as_sji_element(_this);
        }
    }

    return 0;
}

sji_element* sjf_fillElement_heap_as_sji_element(sjs_fillElement_heap* _this) {
    sji_element* _interface;
    _interface = (sji_element*)malloc(sizeof(sji_element));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_fillElement_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_fillElement_heap_asInterface;
    _interface->getSize = (void(*)(void*,sjs_size*, sjs_size*))sjf_fillElement_getSize;
    _interface->getSize_heap = (void(*)(void*,sjs_size*, sjs_size_heap**))sjf_fillElement_getSize_heap;
    _interface->getRect = (void(*)(void*, sjs_rect**))sjf_fillElement_getRect;
    _interface->setRect = (void(*)(void*,sjs_rect*))sjf_fillElement_setRect;
    _interface->render = (void(*)(void*,sjs_scene2d*))sjf_fillElement_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_fillElement_fireMouseEvent;

    return _interface;
}

void sjf_fillElement_render(sjs_fillElement* _parent, sjs_scene2d* scene) {
    int32_t i;
    sjs_array_heap_element* sjt_dot11;
    sjs_fillElement* sjt_dot12;
    int32_t sjt_forEnd2;
    int32_t sjt_forStart2;

#line 21 "lib/ui/fillElement.sj"
    sjt_forStart2 = 0;
#line 20
    sjt_dot12 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot11 = &(sjt_dot12)->children;
#line 21 "lib/ui/fillElement.sj"
    sjt_forEnd2 = (sjt_dot11)->count;
#line 21
    i = sjt_forStart2;
    while (i < sjt_forEnd2) {
        sjs_fillElement* sjt_dot13;
        int32_t sjt_functionParam2;
        sjs_scene2d* sjt_interfaceParam2;
        sjs_array_heap_element* sjt_parent3;
        sji_element* sjt_parent4;
        sji_element* sjv_child;

#line 20 "lib/ui/fillElement.sj"
        sjt_dot13 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent3 = &(sjt_dot13)->children;
#line 21 "lib/ui/fillElement.sj"
        sjt_functionParam2 = i;
#line 21
        sjf_array_heap_element_getAt_heap(sjt_parent3, sjt_functionParam2, &sjv_child);
#line 5 "lib/ui/element.sj"
        sjt_parent4 = sjv_child;
#line 20 "lib/ui/fillElement.sj"
        sjt_interfaceParam2 = scene;
#line 23
        sjt_parent4->render((void*)(((char*)sjt_parent4->_parent) + sizeof(intptr_t)), sjt_interfaceParam2);
#line 21
        i++;

        sjv_child->_refCount--;
        if (sjv_child->_refCount <= 0) {
            sji_element_destroy(sjv_child);
        }
    }
}

void sjf_fillElement_setRect(sjs_fillElement* _parent, sjs_rect* rect_) {
    int32_t i;
    sjs_rect* sjt_copy1;
    sjs_fillElement* sjt_dot6;
    sjs_array_heap_element* sjt_dot7;
    sjs_fillElement* sjt_dot8;
    int32_t sjt_forEnd1;
    int32_t sjt_forStart1;

#line 11 "lib/ui/fillElement.sj"
    sjt_dot6 = _parent;
#line 11
    sjt_copy1 = rect_;
#line 12
    sjf_rect_copy(&sjt_dot6->_rect, sjt_copy1);
#line 13
    sjt_forStart1 = 0;
#line 11
    sjt_dot8 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot7 = &(sjt_dot8)->children;
#line 13 "lib/ui/fillElement.sj"
    sjt_forEnd1 = (sjt_dot7)->count;
#line 13
    i = sjt_forStart1;
    while (i < sjt_forEnd1) {
        sjs_fillElement* sjt_dot10;
        sjs_fillElement* sjt_dot9;
        int32_t sjt_functionParam1;
        sjs_rect* sjt_interfaceParam1;
        sjs_array_heap_element* sjt_parent1;
        sji_element* sjt_parent2;
        sji_element* sjv_child;

#line 11 "lib/ui/fillElement.sj"
        sjt_dot9 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent1 = &(sjt_dot9)->children;
#line 13 "lib/ui/fillElement.sj"
        sjt_functionParam1 = i;
#line 13
        sjf_array_heap_element_getAt_heap(sjt_parent1, sjt_functionParam1, &sjv_child);
#line 4 "lib/ui/element.sj"
        sjt_parent2 = sjv_child;
#line 11 "lib/ui/fillElement.sj"
        sjt_dot10 = _parent;
#line 15
        sjt_interfaceParam1 = &(sjt_dot10)->_rect;
#line 15
        sjt_parent2->setRect((void*)(((char*)sjt_parent2->_parent) + sizeof(intptr_t)), sjt_interfaceParam1);
#line 13
        i++;

        sjv_child->_refCount--;
        if (sjv_child->_refCount <= 0) {
            sji_element_destroy(sjv_child);
        }
    }
}

void sjf_glBindTexture(int32_t type, sjs_texture* texture) {
#line 120 "lib/ui/gl.sj"
    glBindTexture(type, texture->id);
}

void sjf_glDisable(int32_t feature) {
#line 90 "lib/ui/gl.sj"
    glDisable(feature);
}

void sjf_glEnable(int32_t feature) {
#line 84 "lib/ui/gl.sj"
    glEnable(feature);
}

void sjf_glGetUniformLocation(sjs_shader* shader, sjs_string* name, int32_t* _return) {
#line 126 "lib/ui/gl.sj"
    int result = glGetUniformLocation(shader->id, (char*)name->data.data);
#line 126
    #line 126 "lib/ui/gl.sj"
(*_return) = result;
;
}

void sjf_glUniformMat4(int32_t loc, sjs_mat4* m) {
#line 133 "lib/ui/gl.sj"
    glUniformMatrix4fv(loc, 1, 0, (GLfloat*)m);
}

void sjf_glUniformVec3(int32_t loc, sjs_vec3* v) {
#line 139 "lib/ui/gl.sj"
    glUniform3fv(loc, 1, (GLfloat*)v);
}

void sjf_glUseProgram(sjs_shader* shader) {
#line 114 "lib/ui/gl.sj"
    glUseProgram(shader->id);
}

void sjf_i32_max(int32_t a, int32_t b, int32_t* _return) {
    int32_t sjt_compare45;
    int32_t sjt_compare46;
    bool sjt_ifElse15;

#line 6 "lib/common/i32.sj"
    sjt_compare45 = a;
#line 6
    sjt_compare46 = b;
#line 7
    sjt_ifElse15 = sjt_compare45 < sjt_compare46;
    if (sjt_ifElse15) {
#line 6 "lib/common/i32.sj"
        (*_return) = b;
    } else {
#line 6 "lib/common/i32.sj"
        (*_return) = a;
    }
}

void sjf_leafPanel(sjs_leafPanel* _this) {
    int32_t sjt_cast12;
    sjs_array_texture* sjt_dot1314;
    cb_texture_heap_model sjt_functionParam204;
    float sjt_math2099;
    float sjt_math2100;
    float sjt_math2101;
    float sjt_math2102;
    sjs_array_texture* sjt_parent79;

#line 1 "nau/leafPanel.sj"
    sjt_dot1314 = &_this->textures;
#line 54
    sjt_cast12 = (sjt_dot1314)->count;
#line 54
    sjt_math2101 = (float)sjt_cast12;
#line 54
    sjt_math2102 = 0.8f;
#line 54
    sjt_math2099 = sjt_math2101 * sjt_math2102;
#line 54
    sjt_math2100 = 2.0f;
#line 54
    _this->_angle = sjt_math2099 / sjt_math2100;
#line 1
    sjt_parent79 = &_this->textures;
#line 1
    sjt_functionParam204._parent = &_this;
#line 55
    sjt_functionParam204._cb_heap = (void(*)(void*,sjs_texture*, sji_nauScene3dElement_model**))sjf_leafPanel_textureToModel_heap;
#line 55
    sjf_array_texture_map_heap_model(sjt_parent79, sjt_functionParam204, &_this->children);
}

sjs_object* sjf_leafPanel_asInterface(sjs_leafPanel* _this, int typeId) {
    switch (typeId) {
        case sji_nauScene3dElement_model_typeId:  {
            return (sjs_object*)sjf_leafPanel_as_sji_nauScene3dElement_model(_this);
        }
    }

    return 0;
}

sji_nauScene3dElement_model* sjf_leafPanel_as_sji_nauScene3dElement_model(sjs_leafPanel* _this) {
    sji_nauScene3dElement_model* _interface;
    _interface = (sji_nauScene3dElement_model*)malloc(sizeof(sji_nauScene3dElement_model));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_leafPanel_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_leafPanel_asInterface;
    _interface->update = (void(*)(void*,sjs_rect*,sjs_mat4*,sjs_mat4*,sjs_mat4*,sjs_light*))sjf_leafPanel_update;
    _interface->getZ = (void(*)(void*, float*))sjf_leafPanel_getZ;
    _interface->renderOrQueue = (void(*)(void*,sjs_list_heap_model*))sjf_leafPanel_renderOrQueue;
    _interface->render = (void(*)(void*))sjf_leafPanel_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_leafPanel_fireMouseEvent;

    return _interface;
}

void sjf_leafPanel_copy(sjs_leafPanel* _this, sjs_leafPanel* _from) {
#line 1 "nau/leafPanel.sj"
    sjf_array_texture_copy(&_this->textures, &_from->textures);
#line 1
    sjf_array_heap_model_copy(&_this->children, &_from->children);
#line 1
    _this->_angle = _from->_angle;
}

void sjf_leafPanel_destroy(sjs_leafPanel* _this) {
}

void sjf_leafPanel_fireMouseEvent(sjs_leafPanel* _parent, sjs_point* point, int32_t eventId) {
    int32_t i;
    sjs_array_heap_model* sjt_dot1350;
    sjs_leafPanel* sjt_dot1351;
    int32_t sjt_forEnd14;
    int32_t sjt_forStart14;

#line 29 "nau/leafPanel.sj"
    sjt_forStart14 = 0;
#line 28
    sjt_dot1351 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot1350 = &(sjt_dot1351)->children;
#line 29 "nau/leafPanel.sj"
    sjt_forEnd14 = (sjt_dot1350)->count;
#line 29
    i = sjt_forStart14;
    while (i < sjt_forEnd14) {
        sjs_leafPanel* sjt_dot1352;
        int32_t sjt_functionParam241;
        sjs_point* sjt_interfaceParam19;
        int32_t sjt_interfaceParam20;
        sjs_array_heap_model* sjt_parent98;
        sji_nauScene3dElement_model* sjt_parent99;
        sji_nauScene3dElement_model* sjv_c;

#line 28 "nau/leafPanel.sj"
        sjt_dot1352 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent98 = &(sjt_dot1352)->children;
#line 29 "nau/leafPanel.sj"
        sjt_functionParam241 = i;
#line 29
        sjf_array_heap_model_getAt_heap(sjt_parent98, sjt_functionParam241, &sjv_c);
#line 6 "lib/ui/model.sj"
        sjt_parent99 = sjv_c;
#line 28 "nau/leafPanel.sj"
        sjt_interfaceParam19 = point;
#line 28
        sjt_interfaceParam20 = eventId;
#line 31
        sjt_parent99->fireMouseEvent((void*)(((char*)sjt_parent99->_parent) + sizeof(intptr_t)), sjt_interfaceParam19, sjt_interfaceParam20);
#line 29
        i++;

        sjv_c->_refCount--;
        if (sjv_c->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_c);
        }
    }
}

void sjf_leafPanel_getZ(sjs_leafPanel* _parent, float* _return) {
#line 14 "nau/leafPanel.sj"
    (*_return) = 0.0f;
}

void sjf_leafPanel_heap(sjs_leafPanel_heap* _this) {
    int32_t sjt_cast16;
    sjs_array_texture* sjt_dot1353;
    cb_texture_heap_model sjt_functionParam242;
    float sjt_math2145;
    float sjt_math2146;
    float sjt_math2147;
    float sjt_math2148;
    sjs_array_texture* sjt_parent100;

#line 1 "lib/common/array.sj"
    sjt_dot1353 = &_this->textures;
#line 54 "nau/leafPanel.sj"
    sjt_cast16 = (sjt_dot1353)->count;
#line 54
    sjt_math2147 = (float)sjt_cast16;
#line 54
    sjt_math2148 = 0.8f;
#line 54
    sjt_math2145 = sjt_math2147 * sjt_math2148;
#line 54
    sjt_math2146 = 2.0f;
#line 54
    _this->_angle = sjt_math2145 / sjt_math2146;
#line 65 "lib/common/array.sj"
    sjt_parent100 = &_this->textures;
#line 1 "nau/leafPanel.sj"
    sjt_functionParam242._parent = (sjs_leafPanel*)(((char*)_this) + sizeof(intptr_t));
#line 55
    sjt_functionParam242._cb_heap = (void(*)(void*,sjs_texture*, sji_nauScene3dElement_model**))sjf_leafPanel_textureToModel_heap;
#line 55
    sjf_array_texture_map_heap_model(sjt_parent100, sjt_functionParam242, &_this->children);
}

sjs_object* sjf_leafPanel_heap_asInterface(sjs_leafPanel_heap* _this, int typeId) {
    switch (typeId) {
        case sji_nauScene3dElement_model_typeId:  {
            return (sjs_object*)sjf_leafPanel_heap_as_sji_nauScene3dElement_model(_this);
        }
    }

    return 0;
}

sji_nauScene3dElement_model* sjf_leafPanel_heap_as_sji_nauScene3dElement_model(sjs_leafPanel_heap* _this) {
    sji_nauScene3dElement_model* _interface;
    _interface = (sji_nauScene3dElement_model*)malloc(sizeof(sji_nauScene3dElement_model));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_leafPanel_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_leafPanel_heap_asInterface;
    _interface->update = (void(*)(void*,sjs_rect*,sjs_mat4*,sjs_mat4*,sjs_mat4*,sjs_light*))sjf_leafPanel_update;
    _interface->getZ = (void(*)(void*, float*))sjf_leafPanel_getZ;
    _interface->renderOrQueue = (void(*)(void*,sjs_list_heap_model*))sjf_leafPanel_renderOrQueue;
    _interface->render = (void(*)(void*))sjf_leafPanel_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_leafPanel_fireMouseEvent;

    return _interface;
}

void sjf_leafPanel_render(sjs_leafPanel* _parent) {
}

void sjf_leafPanel_renderOrQueue(sjs_leafPanel* _parent, sjs_list_heap_model* zqueue) {
    int32_t i;
    sjs_array_heap_model* sjt_dot1347;
    sjs_leafPanel* sjt_dot1348;
    int32_t sjt_forEnd13;
    int32_t sjt_forStart13;

#line 18 "nau/leafPanel.sj"
    sjt_forStart13 = 0;
#line 17
    sjt_dot1348 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot1347 = &(sjt_dot1348)->children;
#line 18 "nau/leafPanel.sj"
    sjt_forEnd13 = (sjt_dot1347)->count;
#line 18
    i = sjt_forStart13;
    while (i < sjt_forEnd13) {
        sjs_leafPanel* sjt_dot1349;
        int32_t sjt_functionParam240;
        sjs_list_heap_model* sjt_interfaceParam18;
        sjs_array_heap_model* sjt_parent96;
        sji_nauScene3dElement_model* sjt_parent97;
        sji_nauScene3dElement_model* sjv_c;

#line 17 "nau/leafPanel.sj"
        sjt_dot1349 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent96 = &(sjt_dot1349)->children;
#line 18 "nau/leafPanel.sj"
        sjt_functionParam240 = i;
#line 18
        sjf_array_heap_model_getAt_heap(sjt_parent96, sjt_functionParam240, &sjv_c);
#line 4 "lib/ui/model.sj"
        sjt_parent97 = sjv_c;
#line 17 "nau/leafPanel.sj"
        sjt_interfaceParam18 = zqueue;
#line 20
        sjt_parent97->renderOrQueue((void*)(((char*)sjt_parent97->_parent) + sizeof(intptr_t)), sjt_interfaceParam18);
#line 18
        i++;

        sjv_c->_refCount--;
        if (sjv_c->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_c);
        }
    }
}

void sjf_leafPanel_textureToModel_heap(sjs_leafPanel* _parent, sjs_texture* texture, sji_nauScene3dElement_model** _return) {
    float result14;
    float result15;
    sjs_string sjt_call32;
    sjs_string sjt_call33;
    sjs_model_heap* sjt_cast13;
    sjs_shader* sjt_copy12;
    sjs_texture* sjt_copy13;
    sjs_leafPanel* sjt_dot1321;
    sjs_leafPanel* sjt_dot1322;
    sjs_leafPanel* sjt_dot1323;
    sjs_leafPanel* sjt_dot1324;
    float sjt_functionParam205;
    float sjt_functionParam206;
    float sjt_functionParam207;
    float sjt_functionParam208;
    float sjt_functionParam209;
    float sjt_functionParam210;
    float sjt_functionParam211;
    float sjt_functionParam212;
    float sjt_functionParam213;
    float sjt_functionParam214;
    float sjt_functionParam215;
    float sjt_functionParam216;
    float sjt_functionParam217;
    sjs_string* sjt_functionParam237;
    float sjt_functionParam238;
    float sjt_math2103;
    float sjt_math2104;
    float sjt_math2105;
    float sjt_math2106;
    float sjt_math2107;
    float sjt_math2108;
    float sjt_math2109;
    float sjt_math2110;
    float sjt_math2111;
    float sjt_math2112;
    float sjt_math2113;
    float sjt_math2114;
    float sjt_math2115;
    float sjt_math2116;
    float sjt_math2117;
    float sjt_math2118;
    float sjt_math2119;
    float sjt_math2120;
    float sjt_negate13;
    float sjt_negate14;
    sjs_string* sjt_parent93;
    float sjv_noise;
    float sjv_x;
    float sjv_y;
    float sjv_z;

    sjf_f32_random(&sjt_math2103);
#line 38 "nau/leafPanel.sj"
    sjt_math2104 = 0.5f;
#line 38
    sjv_noise = sjt_math2103 - sjt_math2104;
#line 37
    sjt_dot1321 = _parent;
#line 39
    sjt_math2107 = (sjt_dot1321)->_angle;
#line 39
    sjt_math2108 = 2.0f;
#line 39
    sjt_math2105 = sjt_math2107 * sjt_math2108;
#line 39
    sjt_math2109 = sjv_noise;
#line 39
    sjt_math2110 = 0.2f;
#line 39
    sjt_math2106 = sjt_math2109 * sjt_math2110;
#line 39
    sjv_x = sjt_math2105 + sjt_math2106;
#line 40
    sjt_math2111 = sjv_noise;
#line 40
    sjt_math2112 = 3.0f;
#line 40
    sjv_y = sjt_math2111 * sjt_math2112;
#line 37
    sjt_dot1322 = _parent;
#line 41
    sjt_math2115 = (sjt_dot1322)->_angle;
#line 41
    sjt_math2117 = sjv_noise;
#line 41
    sjt_math2118 = 0.2f;
#line 41
    sjt_math2116 = sjt_math2117 * sjt_math2118;
#line 41
    sjt_functionParam205 = sjt_math2115 + sjt_math2116;
#line 41
    sjf_f32_cos(sjt_functionParam205, &sjt_math2113);
#line 41
    sjt_math2114 = 2.0f;
#line 41
    sjv_z = sjt_math2113 * sjt_math2114;
#line 37
    sjt_dot1323 = _parent;
#line 37
    sjt_dot1324 = _parent;
#line 42
    sjt_math2119 = (sjt_dot1324)->_angle;
#line 42
    sjt_math2120 = 0.8f;
#line 42
    sjt_dot1323->_angle = sjt_math2119 + sjt_math2120;
#line 42
    sjt_cast13 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 42
    sjt_cast13->_refCount = 1;
#line 66 "lib/ui/vertexBufferBuilders.sj"
    sjt_negate13 = 1.0f;
#line 66
    result14 = -sjt_negate13;
#line 66
    sjt_functionParam206 = result14;
#line 67
    sjt_functionParam207 = 1.0f;
#line 68
    sjt_negate14 = 1.0f;
#line 68
    result15 = -sjt_negate14;
#line 68
    sjt_functionParam208 = result15;
#line 69
    sjt_functionParam209 = 1.0f;
#line 70
    sjt_functionParam210 = 0.0f;
#line 71
    sjt_functionParam211 = 0.0f;
#line 72
    sjt_functionParam212 = 1.0f;
#line 73
    sjt_functionParam213 = 0.0f;
#line 74
    sjt_functionParam214 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam206, sjt_functionParam207, sjt_functionParam208, sjt_functionParam209, sjt_functionParam210, sjt_functionParam211, sjt_functionParam212, sjt_functionParam213, sjt_functionParam214, &sjt_cast13->vertexBuffer);
#line 47 "nau/leafPanel.sj"
    sjt_copy12 = &sjv_phongTextureShader;
#line 47
    sjf_shader_copy(&sjt_cast13->shader, sjt_copy12);
#line 37
    sjt_copy13 = texture;
#line 46
    sjf_texture_copy(&sjt_cast13->texture, sjt_copy13);
#line 48
    sjt_functionParam215 = sjv_x;
#line 48
    sjt_functionParam216 = sjv_y;
#line 48
    sjt_functionParam217 = sjv_z;
#line 48
    sjf_mat4_translate(sjt_functionParam215, sjt_functionParam216, sjt_functionParam217, &sjt_cast13->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast13->center.x = 0.0f;
#line 3
    sjt_cast13->center.y = 0.0f;
#line 4
    sjt_cast13->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast13->center);
#line 50 "nau/leafPanel.sj"
    sjt_cast13->hasAlpha = true;
#line 45
    sjt_call32.count = 4;
#line 45
    sjt_call32.data.dataSize = 5;
#line 45
    sjt_call32.data.data = (void*)sjg_string18;
#line 45
    sjt_call32.data._isGlobal = true;
#line 45
    sjt_call32.data.count = 5;
#line 45
    sjf_array_char(&sjt_call32.data);
#line 45
    sjf_string(&sjt_call32);
#line 45
    sjt_parent93 = &sjt_call32;
#line 45
    sjt_functionParam238 = sjv_z;
#line 45
    sjf_f32_toString(sjt_functionParam238, &sjt_call33);
#line 45
    sjt_functionParam237 = &sjt_call33;
#line 45
    sjf_string_add(sjt_parent93, sjt_functionParam237, &sjt_cast13->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast13->_projection.m00 = 0.0f;
#line 3
    sjt_cast13->_projection.m01 = 0.0f;
#line 4
    sjt_cast13->_projection.m02 = 0.0f;
#line 5
    sjt_cast13->_projection.m03 = 0.0f;
#line 6
    sjt_cast13->_projection.m10 = 0.0f;
#line 7
    sjt_cast13->_projection.m11 = 0.0f;
#line 8
    sjt_cast13->_projection.m12 = 0.0f;
#line 9
    sjt_cast13->_projection.m13 = 0.0f;
#line 10
    sjt_cast13->_projection.m20 = 0.0f;
#line 11
    sjt_cast13->_projection.m21 = 0.0f;
#line 12
    sjt_cast13->_projection.m22 = 0.0f;
#line 13
    sjt_cast13->_projection.m23 = 0.0f;
#line 14
    sjt_cast13->_projection.m30 = 0.0f;
#line 15
    sjt_cast13->_projection.m31 = 0.0f;
#line 16
    sjt_cast13->_projection.m32 = 0.0f;
#line 17
    sjt_cast13->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast13->_projection);
#line 2
    sjt_cast13->_view.m00 = 0.0f;
#line 3
    sjt_cast13->_view.m01 = 0.0f;
#line 4
    sjt_cast13->_view.m02 = 0.0f;
#line 5
    sjt_cast13->_view.m03 = 0.0f;
#line 6
    sjt_cast13->_view.m10 = 0.0f;
#line 7
    sjt_cast13->_view.m11 = 0.0f;
#line 8
    sjt_cast13->_view.m12 = 0.0f;
#line 9
    sjt_cast13->_view.m13 = 0.0f;
#line 10
    sjt_cast13->_view.m20 = 0.0f;
#line 11
    sjt_cast13->_view.m21 = 0.0f;
#line 12
    sjt_cast13->_view.m22 = 0.0f;
#line 13
    sjt_cast13->_view.m23 = 0.0f;
#line 14
    sjt_cast13->_view.m30 = 0.0f;
#line 15
    sjt_cast13->_view.m31 = 0.0f;
#line 16
    sjt_cast13->_view.m32 = 0.0f;
#line 17
    sjt_cast13->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast13->_view);
#line 2
    sjt_cast13->_world.m00 = 0.0f;
#line 3
    sjt_cast13->_world.m01 = 0.0f;
#line 4
    sjt_cast13->_world.m02 = 0.0f;
#line 5
    sjt_cast13->_world.m03 = 0.0f;
#line 6
    sjt_cast13->_world.m10 = 0.0f;
#line 7
    sjt_cast13->_world.m11 = 0.0f;
#line 8
    sjt_cast13->_world.m12 = 0.0f;
#line 9
    sjt_cast13->_world.m13 = 0.0f;
#line 10
    sjt_cast13->_world.m20 = 0.0f;
#line 11
    sjt_cast13->_world.m21 = 0.0f;
#line 12
    sjt_cast13->_world.m22 = 0.0f;
#line 13
    sjt_cast13->_world.m23 = 0.0f;
#line 14
    sjt_cast13->_world.m30 = 0.0f;
#line 15
    sjt_cast13->_world.m31 = 0.0f;
#line 16
    sjt_cast13->_world.m32 = 0.0f;
#line 17
    sjt_cast13->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast13->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast13->_light.pos.x = 1.0f;
#line 2
    sjt_cast13->_light.pos.y = 1.0f;
#line 2
    sjt_cast13->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast13->_light.pos);
#line 3
    sjt_cast13->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast13->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast13->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast13->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast13->_light.diffuseColor);
#line 4
    sjt_cast13->_light.specColor.r = 1.0f;
#line 4
    sjt_cast13->_light.specColor.g = 1.0f;
#line 4
    sjt_cast13->_light.specColor.b = 1.0f;
#line 4
    sjt_cast13->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast13->_light.specColor);
#line 4
    sjf_light(&sjt_cast13->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast13->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast13->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast13->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast13->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast13);
#line 1 "lib/ui/model.sj"
    (*_return) = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast13);

    sjt_cast13->_refCount--;
    if (sjt_cast13->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast13) + sizeof(intptr_t)));
    }
    sjf_string_destroy(&sjt_call32);
    sjf_string_destroy(&sjt_call33);
}

void sjf_leafPanel_update(sjs_leafPanel* _parent, sjs_rect* sceneRect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light) {
    int32_t i;
    sjs_array_heap_model* sjt_dot1344;
    sjs_leafPanel* sjt_dot1345;
    int32_t sjt_forEnd12;
    int32_t sjt_forStart12;

#line 6 "nau/leafPanel.sj"
    sjt_forStart12 = 0;
#line 5
    sjt_dot1345 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot1344 = &(sjt_dot1345)->children;
#line 6 "nau/leafPanel.sj"
    sjt_forEnd12 = (sjt_dot1344)->count;
#line 6
    i = sjt_forStart12;
    while (i < sjt_forEnd12) {
        sjs_leafPanel* sjt_dot1346;
        int32_t sjt_functionParam239;
        sjs_rect* sjt_interfaceParam13;
        sjs_mat4* sjt_interfaceParam14;
        sjs_mat4* sjt_interfaceParam15;
        sjs_mat4* sjt_interfaceParam16;
        sjs_light* sjt_interfaceParam17;
        sjs_array_heap_model* sjt_parent94;
        sji_nauScene3dElement_model* sjt_parent95;
        sji_nauScene3dElement_model* sjv_c;

#line 5 "nau/leafPanel.sj"
        sjt_dot1346 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent94 = &(sjt_dot1346)->children;
#line 6 "nau/leafPanel.sj"
        sjt_functionParam239 = i;
#line 6
        sjf_array_heap_model_getAt_heap(sjt_parent94, sjt_functionParam239, &sjv_c);
#line 2 "lib/ui/model.sj"
        sjt_parent95 = sjv_c;
#line 5 "nau/leafPanel.sj"
        sjt_interfaceParam13 = sceneRect;
#line 5
        sjt_interfaceParam14 = projection;
#line 5
        sjt_interfaceParam15 = view;
#line 5
        sjt_interfaceParam16 = world;
#line 5
        sjt_interfaceParam17 = light;
#line 8
        sjt_parent95->update((void*)(((char*)sjt_parent95->_parent) + sizeof(intptr_t)), sjt_interfaceParam13, sjt_interfaceParam14, sjt_interfaceParam15, sjt_interfaceParam16, sjt_interfaceParam17);
#line 6
        i++;

        sjv_c->_refCount--;
        if (sjv_c->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_c);
        }
    }
}

void sjf_light(sjs_light* _this) {
}

void sjf_light_copy(sjs_light* _this, sjs_light* _from) {
#line 1 "lib/ui/scene3dElement.sj"
    sjf_vec3_copy(&_this->pos, &_from->pos);
#line 1
    sjf_color_copy(&_this->diffuseColor, &_from->diffuseColor);
#line 1
    sjf_color_copy(&_this->specColor, &_from->specColor);
}

void sjf_light_destroy(sjs_light* _this) {
}

void sjf_light_heap(sjs_light_heap* _this) {
}

void sjf_list_heap_animation(sjs_list_heap_animation* _this) {
}

void sjf_list_heap_animation_copy(sjs_list_heap_animation* _this, sjs_list_heap_animation* _from) {
#line 1 "lib/common/list.sj"
    sjf_array_heap_animation_copy(&_this->array, &_from->array);
}

void sjf_list_heap_animation_destroy(sjs_list_heap_animation* _this) {
}

void sjf_list_heap_animation_getAt_heap(sjs_list_heap_animation* _parent, int32_t index, sji_anon2_animation** _return) {
    sjs_list_heap_animation* sjt_dot1415;
    int32_t sjt_functionParam475;
    sjs_array_heap_animation* sjt_parent146;

#line 8 "lib/common/list.sj"
    sjt_dot1415 = _parent;
#line 7 "lib/common/array.sj"
    sjt_parent146 = &(sjt_dot1415)->array;
#line 8 "lib/common/list.sj"
    sjt_functionParam475 = index;
#line 8
    sjf_array_heap_animation_getAt_heap(sjt_parent146, sjt_functionParam475, _return);
}

void sjf_list_heap_animation_getCount(sjs_list_heap_animation* _parent, int32_t* _return) {
    sjs_array_heap_animation* sjt_dot1410;
    sjs_list_heap_animation* sjt_dot1411;

#line 4 "lib/common/list.sj"
    sjt_dot1411 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot1410 = &(sjt_dot1411)->array;
#line 4 "lib/common/list.sj"
    (*_return) = (sjt_dot1410)->count;
}

void sjf_list_heap_animation_heap(sjs_list_heap_animation_heap* _this) {
}

void sjf_list_heap_animation_removeAt(sjs_list_heap_animation* _parent, int32_t index) {
#line 54 "lib/common/list.sj"
    if (index < 0 || index >= _parent->array.count) {
#line 54
        halt("removeAt: out of bounds %d:%d\n", index, _parent->array.count);
#line 54
    }
#line 54
    sji_anon2_animation** p = (sji_anon2_animation**)_parent->array.data;
#line 54
    if (index != _parent->array.count - 1) {
#line 54
        memcpy(p + index, p + index + 1, _parent->array.count - index - 1);
#line 54
    }
#line 54
    _parent->array.count--;
}

void sjf_list_heap_model(sjs_list_heap_model* _this) {
}

void sjf_list_heap_model_add(sjs_list_heap_model* _parent, sji_nauScene3dElement_model* item) {
    int32_t sjt_compare43;
    int32_t sjt_compare44;
    sjs_array_heap_model* sjt_dot540;
    sjs_list_heap_model* sjt_dot541;
    sjs_array_heap_model* sjt_dot542;
    sjs_list_heap_model* sjt_dot543;
    sjs_list_heap_model* sjt_dot550;
    sjs_array_heap_model* sjt_dot551;
    sjs_list_heap_model* sjt_dot552;
    int32_t sjt_functionParam107;
    sji_nauScene3dElement_model* sjt_functionParam108;
    bool sjt_ifElse14;
    sjs_array_heap_model* sjt_parent46;

#line 44 "lib/common/list.sj"
    sjt_dot541 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot540 = &(sjt_dot541)->array;
#line 45 "lib/common/list.sj"
    sjt_compare43 = (sjt_dot540)->count;
#line 44
    sjt_dot543 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot542 = &(sjt_dot543)->array;
#line 45 "lib/common/list.sj"
    sjt_compare44 = (sjt_dot542)->dataSize;
#line 45
    sjt_ifElse14 = sjt_compare43 >= sjt_compare44;
    if (sjt_ifElse14) {
        sjs_list_heap_model* sjt_dot544;
        sjs_list_heap_model* sjt_dot547;
        sjs_array_heap_model* sjt_dot548;
        sjs_list_heap_model* sjt_dot549;
        int32_t sjt_functionParam104;
        int32_t sjt_functionParam105;
        int32_t sjt_functionParam106;
        int32_t sjt_math751;
        int32_t sjt_math752;
        sjs_array_heap_model* sjt_parent45;

#line 44 "lib/common/list.sj"
        sjt_dot544 = _parent;
#line 44
        sjt_dot547 = _parent;
#line 115 "lib/common/array.sj"
        sjt_parent45 = &(sjt_dot547)->array;
#line 46 "lib/common/list.sj"
        sjt_functionParam105 = 10;
#line 44
        sjt_dot549 = _parent;
#line 1 "lib/common/array.sj"
        sjt_dot548 = &(sjt_dot549)->array;
#line 46 "lib/common/list.sj"
        sjt_math751 = (sjt_dot548)->dataSize;
#line 46
        sjt_math752 = 2;
#line 46
        sjt_functionParam106 = sjt_math751 * sjt_math752;
#line 46
        sjf_i32_max(sjt_functionParam105, sjt_functionParam106, &sjt_functionParam104);
#line 46
        sjf_array_heap_model_grow(sjt_parent45, sjt_functionParam104, &sjt_dot544->array);
    }

#line 44
    sjt_dot550 = _parent;
#line 19 "lib/common/array.sj"
    sjt_parent46 = &(sjt_dot550)->array;
#line 44 "lib/common/list.sj"
    sjt_dot552 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot551 = &(sjt_dot552)->array;
#line 50 "lib/common/list.sj"
    sjt_functionParam107 = (sjt_dot551)->count;
#line 44
    sjt_functionParam108 = item;
#line 44
    sjt_functionParam108->_refCount++;
#line 44
    sjf_array_heap_model_initAt(sjt_parent46, sjt_functionParam107, sjt_functionParam108);

    sjt_functionParam108->_refCount--;
    if (sjt_functionParam108->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam108);
    }
}

void sjf_list_heap_model_copy(sjs_list_heap_model* _this, sjs_list_heap_model* _from) {
#line 1 "lib/common/list.sj"
    sjf_array_heap_model_copy(&_this->array, &_from->array);
}

void sjf_list_heap_model_destroy(sjs_list_heap_model* _this) {
}

void sjf_list_heap_model_getAt_heap(sjs_list_heap_model* _parent, int32_t index, sji_nauScene3dElement_model** _return) {
    sjs_list_heap_model* sjt_dot56;
    int32_t sjt_functionParam48;
    sjs_array_heap_model* sjt_parent18;

#line 8 "lib/common/list.sj"
    sjt_dot56 = _parent;
#line 7 "lib/common/array.sj"
    sjt_parent18 = &(sjt_dot56)->array;
#line 8 "lib/common/list.sj"
    sjt_functionParam48 = index;
#line 8
    sjf_array_heap_model_getAt_heap(sjt_parent18, sjt_functionParam48, _return);
}

void sjf_list_heap_model_getCount(sjs_list_heap_model* _parent, int32_t* _return) {
    sjs_array_heap_model* sjt_dot54;
    sjs_list_heap_model* sjt_dot55;

#line 4 "lib/common/list.sj"
    sjt_dot55 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot54 = &(sjt_dot55)->array;
#line 4 "lib/common/list.sj"
    (*_return) = (sjt_dot54)->count;
}

void sjf_list_heap_model_heap(sjs_list_heap_model_heap* _this) {
}

void sjf_list_heap_model_sortcb(sjs_list_heap_model* _parent, cb_heap_model_heap_model_i32 cb) {
    sjs_list_heap_model* sjt_dot53;
    cb_heap_model_heap_model_i32 sjt_functionParam44;
    sjs_array_heap_model* sjt_parent13;

#line 28 "lib/common/list.sj"
    sjt_dot53 = _parent;
#line 201 "lib/common/array.sj"
    sjt_parent13 = &(sjt_dot53)->array;
#line 28 "lib/common/list.sj"
    sjt_functionParam44 = cb;
#line 28
    sjf_array_heap_model_sortcb(sjt_parent13, sjt_functionParam44);
}

void sjf_mainLoop(void) {
    int32_t result55;
    int32_t result56;
    int32_t sjt_compare67;
    int32_t sjt_compare68;
    sjs_size* sjt_dot1431;
    sjs_size* sjt_dot1432;
    int32_t sjt_functionParam478;
    sjs_size* sjt_functionParam489;
    bool sjt_ifElse28;
    sjs_rect* sjt_interfaceParam30;
    sjs_scene2d* sjt_interfaceParam31;
    int32_t sjt_negate50;
    int32_t sjt_negate51;
    sjs_anon2* sjt_parent150;
    sjs_windowRenderer* sjt_parent151;
    sjs_scene2d* sjt_parent153;
    sjs_scene2d* sjt_parent154;
    sji_element* sjt_parent155;
    sji_element* sjt_parent156;
    sjs_windowRenderer* sjt_parent157;
    int32_t sjv_mouseEvent;
    sjs_rect sjv_rect;
    sjs_size sjv_size;
    int32_t sjv_ticks;
    int32_t sjv_x;
    int32_t sjv_y;

#line 6 "lib/ui/loop.sj"
    sjv_ticks = 0;
#line 7
    sjv_ticks = SDL_GetTicks();
#line 31 "lib/ui/animation.sj"
    sjt_parent150 = &sjv_animator;
#line 10 "lib/ui/loop.sj"
    sjt_functionParam478 = sjv_ticks;
#line 10
    sjf_anon2_nextFrame(sjt_parent150, sjt_functionParam478);
#line 7 "lib/ui/windowRenderer.sj"
    sjt_parent151 = &sjv_rootWindowRenderer;
#line 7
    sjf_windowRenderer_getSize(sjt_parent151, &sjv_size);
#line 27 "lib/ui/scene2d.sj"
    sjt_parent153 = &sjv_rootScene;
#line 13 "lib/ui/loop.sj"
    sjt_functionParam489 = &sjv_size;
#line 13
    sjf_scene2d_setSize(sjt_parent153, sjt_functionParam489);
#line 7 "lib/ui/scene2d.sj"
    sjt_parent154 = &sjv_rootScene;
#line 7
    sjf_scene2d_clear(sjt_parent154);
#line 15 "lib/ui/loop.sj"
    sjv_rect.x = 0;
#line 15
    sjv_rect.y = 0;
#line 1 "lib/ui/size.sj"
    sjt_dot1431 = &sjv_size;
#line 15 "lib/ui/loop.sj"
    sjv_rect.w = (sjt_dot1431)->w;
#line 1 "lib/ui/size.sj"
    sjt_dot1432 = &sjv_size;
#line 15 "lib/ui/loop.sj"
    sjv_rect.h = (sjt_dot1432)->h;
#line 15
    sjf_rect(&sjv_rect);
#line 4 "lib/ui/element.sj"
    sjt_parent155 = sjv_root;
#line 16 "lib/ui/loop.sj"
    sjt_interfaceParam30 = &sjv_rect;
#line 16
    sjt_parent155->setRect((void*)(((char*)sjt_parent155->_parent) + sizeof(intptr_t)), sjt_interfaceParam30);
#line 5 "lib/ui/element.sj"
    sjt_parent156 = sjv_root;
#line 17 "lib/ui/loop.sj"
    sjt_interfaceParam31 = &sjv_rootScene;
#line 17
    sjt_parent156->render((void*)(((char*)sjt_parent156->_parent) + sizeof(intptr_t)), sjt_interfaceParam31);
#line 16 "lib/ui/windowRenderer.sj"
    sjt_parent157 = &sjv_rootWindowRenderer;
#line 16
    sjf_windowRenderer_present(sjt_parent157);
#line 20 "lib/ui/loop.sj"
    sjt_negate50 = 1;
#line 20
    result55 = -sjt_negate50;
#line 20
    sjv_mouseEvent = result55;
#line 21
    sjv_x = 0;
#line 22
    sjv_y = 0;
#line 23
    SDL_Event e;
#line 23
    while(SDL_PollEvent( &e ) != 0) {
#line 23
        switch (e.type) {
#line 23
            case SDL_QUIT:
#line 23
            exit(0);
#line 23
            break;
#line 23
            case SDL_MOUSEBUTTONDOWN:
#line 23
            printf("SDL_MOUSEBUTTONDOWN\n");
#line 23
            sjv_mouseEvent = sjv_mouseEvent_down;
#line 23
            sjv_x = e.button.x;
#line 23
            sjv_y = e.button.y;
#line 23
            break;
#line 23
            case SDL_MOUSEBUTTONUP:
#line 23
            printf("SDL_MOUSEBUTTONUP\n");
#line 23
            sjv_mouseEvent = sjv_mouseEvent_up;
#line 23
            sjv_x = e.button.x;
#line 23
            sjv_y = e.button.y;
#line 23
            break;
#line 23
            case SDL_MOUSEMOTION:
#line 23
            printf("SDL_MOUSEMOTION\n");
#line 23
            sjv_mouseEvent = sjv_mouseEvent_move;
#line 23
            sjv_x = e.motion.x;
#line 23
            sjv_y = e.motion.y;
#line 23
            break;
#line 23
        }
#line 23
    }
#line 52
    sjt_compare67 = sjv_mouseEvent;
#line 52
    sjt_negate51 = 1;
#line 52
    result56 = -sjt_negate51;
#line 52
    sjt_compare68 = result56;
#line 52
    sjt_ifElse28 = sjt_compare67 != sjt_compare68;
    if (sjt_ifElse28) {
        sjs_point sjt_call83;
        sjs_point* sjt_interfaceParam32;
        int32_t sjt_interfaceParam33;
        sji_element* sjt_parent158;

#line 6 "lib/ui/element.sj"
        sjt_parent158 = sjv_root;
#line 53 "lib/ui/loop.sj"
        sjt_call83.x = sjv_x;
#line 53
        sjt_call83.y = sjv_y;
#line 53
        sjf_point(&sjt_call83);
#line 53
        sjt_interfaceParam32 = &sjt_call83;
#line 53
        sjt_interfaceParam33 = sjv_mouseEvent;
#line 53
        sjt_parent158->fireMouseEvent((void*)(((char*)sjt_parent158->_parent) + sizeof(intptr_t)), sjt_interfaceParam32, sjt_interfaceParam33);

        sjf_point_destroy(&sjt_call83);
    }

    sjf_rect_destroy(&sjv_rect);
    sjf_size_destroy(&sjv_size);
}

void sjf_mat4(sjs_mat4* _this) {
}

void sjf_mat4_copy(sjs_mat4* _this, sjs_mat4* _from) {
#line 1 "lib/ui/mat4.sj"
    _this->m00 = _from->m00;
#line 1
    _this->m01 = _from->m01;
#line 1
    _this->m02 = _from->m02;
#line 1
    _this->m03 = _from->m03;
#line 1
    _this->m10 = _from->m10;
#line 1
    _this->m11 = _from->m11;
#line 1
    _this->m12 = _from->m12;
#line 1
    _this->m13 = _from->m13;
#line 1
    _this->m20 = _from->m20;
#line 1
    _this->m21 = _from->m21;
#line 1
    _this->m22 = _from->m22;
#line 1
    _this->m23 = _from->m23;
#line 1
    _this->m30 = _from->m30;
#line 1
    _this->m31 = _from->m31;
#line 1
    _this->m32 = _from->m32;
#line 1
    _this->m33 = _from->m33;
}

void sjf_mat4_destroy(sjs_mat4* _this) {
}

void sjf_mat4_determinant(sjs_mat4* _parent, float* _return) {
    sjs_mat4* sjt_dot1000;
    sjs_mat4* sjt_dot1001;
    sjs_mat4* sjt_dot1002;
    sjs_mat4* sjt_dot1003;
    sjs_mat4* sjt_dot908;
    sjs_mat4* sjt_dot909;
    sjs_mat4* sjt_dot910;
    sjs_mat4* sjt_dot911;
    sjs_mat4* sjt_dot912;
    sjs_mat4* sjt_dot913;
    sjs_mat4* sjt_dot914;
    sjs_mat4* sjt_dot915;
    sjs_mat4* sjt_dot916;
    sjs_mat4* sjt_dot917;
    sjs_mat4* sjt_dot918;
    sjs_mat4* sjt_dot919;
    sjs_mat4* sjt_dot920;
    sjs_mat4* sjt_dot921;
    sjs_mat4* sjt_dot922;
    sjs_mat4* sjt_dot923;
    sjs_mat4* sjt_dot924;
    sjs_mat4* sjt_dot925;
    sjs_mat4* sjt_dot926;
    sjs_mat4* sjt_dot927;
    sjs_mat4* sjt_dot928;
    sjs_mat4* sjt_dot929;
    sjs_mat4* sjt_dot930;
    sjs_mat4* sjt_dot931;
    sjs_mat4* sjt_dot932;
    sjs_mat4* sjt_dot933;
    sjs_mat4* sjt_dot934;
    sjs_mat4* sjt_dot935;
    sjs_mat4* sjt_dot936;
    sjs_mat4* sjt_dot937;
    sjs_mat4* sjt_dot938;
    sjs_mat4* sjt_dot939;
    sjs_mat4* sjt_dot940;
    sjs_mat4* sjt_dot941;
    sjs_mat4* sjt_dot942;
    sjs_mat4* sjt_dot943;
    sjs_mat4* sjt_dot944;
    sjs_mat4* sjt_dot945;
    sjs_mat4* sjt_dot946;
    sjs_mat4* sjt_dot947;
    sjs_mat4* sjt_dot948;
    sjs_mat4* sjt_dot949;
    sjs_mat4* sjt_dot950;
    sjs_mat4* sjt_dot951;
    sjs_mat4* sjt_dot952;
    sjs_mat4* sjt_dot953;
    sjs_mat4* sjt_dot954;
    sjs_mat4* sjt_dot955;
    sjs_mat4* sjt_dot956;
    sjs_mat4* sjt_dot957;
    sjs_mat4* sjt_dot958;
    sjs_mat4* sjt_dot959;
    sjs_mat4* sjt_dot960;
    sjs_mat4* sjt_dot961;
    sjs_mat4* sjt_dot962;
    sjs_mat4* sjt_dot963;
    sjs_mat4* sjt_dot964;
    sjs_mat4* sjt_dot965;
    sjs_mat4* sjt_dot966;
    sjs_mat4* sjt_dot967;
    sjs_mat4* sjt_dot968;
    sjs_mat4* sjt_dot969;
    sjs_mat4* sjt_dot970;
    sjs_mat4* sjt_dot971;
    sjs_mat4* sjt_dot972;
    sjs_mat4* sjt_dot973;
    sjs_mat4* sjt_dot974;
    sjs_mat4* sjt_dot975;
    sjs_mat4* sjt_dot976;
    sjs_mat4* sjt_dot977;
    sjs_mat4* sjt_dot978;
    sjs_mat4* sjt_dot979;
    sjs_mat4* sjt_dot980;
    sjs_mat4* sjt_dot981;
    sjs_mat4* sjt_dot982;
    sjs_mat4* sjt_dot983;
    sjs_mat4* sjt_dot984;
    sjs_mat4* sjt_dot985;
    sjs_mat4* sjt_dot986;
    sjs_mat4* sjt_dot987;
    sjs_mat4* sjt_dot988;
    sjs_mat4* sjt_dot989;
    sjs_mat4* sjt_dot990;
    sjs_mat4* sjt_dot991;
    sjs_mat4* sjt_dot992;
    sjs_mat4* sjt_dot993;
    sjs_mat4* sjt_dot994;
    sjs_mat4* sjt_dot995;
    sjs_mat4* sjt_dot996;
    sjs_mat4* sjt_dot997;
    sjs_mat4* sjt_dot998;
    sjs_mat4* sjt_dot999;
    float sjt_math1363;
    float sjt_math1364;
    float sjt_math1365;
    float sjt_math1366;
    float sjt_math1367;
    float sjt_math1368;
    float sjt_math1369;
    float sjt_math1370;
    float sjt_math1371;
    float sjt_math1372;
    float sjt_math1373;
    float sjt_math1374;
    float sjt_math1375;
    float sjt_math1376;
    float sjt_math1377;
    float sjt_math1378;
    float sjt_math1379;
    float sjt_math1380;
    float sjt_math1381;
    float sjt_math1382;
    float sjt_math1383;
    float sjt_math1384;
    float sjt_math1385;
    float sjt_math1386;
    float sjt_math1387;
    float sjt_math1388;
    float sjt_math1389;
    float sjt_math1390;
    float sjt_math1391;
    float sjt_math1392;
    float sjt_math1393;
    float sjt_math1394;
    float sjt_math1395;
    float sjt_math1396;
    float sjt_math1397;
    float sjt_math1398;
    float sjt_math1399;
    float sjt_math1400;
    float sjt_math1401;
    float sjt_math1402;
    float sjt_math1403;
    float sjt_math1404;
    float sjt_math1405;
    float sjt_math1406;
    float sjt_math1407;
    float sjt_math1408;
    float sjt_math1409;
    float sjt_math1410;
    float sjt_math1411;
    float sjt_math1412;
    float sjt_math1413;
    float sjt_math1414;
    float sjt_math1415;
    float sjt_math1416;
    float sjt_math1417;
    float sjt_math1418;
    float sjt_math1419;
    float sjt_math1420;
    float sjt_math1421;
    float sjt_math1422;
    float sjt_math1423;
    float sjt_math1424;
    float sjt_math1425;
    float sjt_math1426;
    float sjt_math1427;
    float sjt_math1428;
    float sjt_math1429;
    float sjt_math1430;
    float sjt_math1431;
    float sjt_math1432;
    float sjt_math1433;
    float sjt_math1434;
    float sjt_math1435;
    float sjt_math1436;
    float sjt_math1437;
    float sjt_math1438;
    float sjt_math1439;
    float sjt_math1440;
    float sjt_math1441;
    float sjt_math1442;
    float sjt_math1443;
    float sjt_math1444;
    float sjt_math1445;
    float sjt_math1446;
    float sjt_math1447;
    float sjt_math1448;
    float sjt_math1449;
    float sjt_math1450;
    float sjt_math1451;
    float sjt_math1452;
    float sjt_math1453;
    float sjt_math1454;
    float sjt_math1455;
    float sjt_math1456;
    float sjt_math1457;
    float sjt_math1458;
    float sjt_math1459;
    float sjt_math1460;
    float sjt_math1461;
    float sjt_math1462;
    float sjt_math1463;
    float sjt_math1464;
    float sjt_math1465;
    float sjt_math1466;
    float sjt_math1467;
    float sjt_math1468;
    float sjt_math1469;
    float sjt_math1470;
    float sjt_math1471;
    float sjt_math1472;
    float sjt_math1473;
    float sjt_math1474;
    float sjt_math1475;
    float sjt_math1476;
    float sjt_math1477;
    float sjt_math1478;
    float sjt_math1479;
    float sjt_math1480;
    float sjt_math1481;
    float sjt_math1482;
    float sjt_math1483;
    float sjt_math1484;
    float sjt_math1485;
    float sjt_math1486;
    float sjt_math1487;
    float sjt_math1488;
    float sjt_math1489;
    float sjt_math1490;
    float sjt_math1491;
    float sjt_math1492;
    float sjt_math1493;
    float sjt_math1494;
    float sjt_math1495;
    float sjt_math1496;
    float sjt_math1497;
    float sjt_math1498;
    float sjt_math1499;
    float sjt_math1500;
    float sjt_math1501;
    float sjt_math1502;
    float sjt_math1503;
    float sjt_math1504;
    float sjt_math1505;
    float sjt_math1506;
    float sjt_math1507;
    float sjt_math1508;
    float sjt_math1509;
    float sjt_math1510;
    float sjt_math1511;
    float sjt_math1512;
    float sjt_math1513;
    float sjt_math1514;
    float sjt_math1515;
    float sjt_math1516;
    float sjt_math1517;
    float sjt_math1518;
    float sjt_math1519;
    float sjt_math1520;
    float sjt_math1521;
    float sjt_math1522;
    float sjt_math1523;
    float sjt_math1524;
    float sjt_math1525;
    float sjt_math1526;
    float sjt_math1527;
    float sjt_math1528;
    float sjt_math1529;
    float sjt_math1530;
    float sjt_math1531;
    float sjt_math1532;
    float sjt_math1533;
    float sjt_math1534;
    float sjt_math1535;
    float sjt_math1536;
    float sjt_math1537;
    float sjt_math1538;
    float sjt_math1539;
    float sjt_math1540;
    float sjt_math1541;
    float sjt_math1542;
    float sjt_math1543;
    float sjt_math1544;
    float sjt_math1545;
    float sjt_math1546;
    float sjt_math1547;
    float sjt_math1548;
    float sjt_math1549;
    float sjt_math1550;
    float sjt_math1551;
    float sjt_math1552;

#line 104 "lib/ui/mat4.sj"
    sjt_dot908 = _parent;
#line 105
    sjt_math1413 = (sjt_dot908)->m03;
#line 104
    sjt_dot909 = _parent;
#line 105
    sjt_math1414 = (sjt_dot909)->m12;
#line 105
    sjt_math1411 = sjt_math1413 * sjt_math1414;
#line 104
    sjt_dot910 = _parent;
#line 105
    sjt_math1412 = (sjt_dot910)->m21;
#line 105
    sjt_math1409 = sjt_math1411 * sjt_math1412;
#line 104
    sjt_dot911 = _parent;
#line 105
    sjt_math1410 = (sjt_dot911)->m30;
#line 105
    sjt_math1407 = sjt_math1409 * sjt_math1410;
#line 104
    sjt_dot912 = _parent;
#line 105
    sjt_math1419 = (sjt_dot912)->m02;
#line 104
    sjt_dot913 = _parent;
#line 105
    sjt_math1420 = (sjt_dot913)->m13;
#line 105
    sjt_math1417 = sjt_math1419 * sjt_math1420;
#line 104
    sjt_dot914 = _parent;
#line 105
    sjt_math1418 = (sjt_dot914)->m21;
#line 105
    sjt_math1415 = sjt_math1417 * sjt_math1418;
#line 104
    sjt_dot915 = _parent;
#line 105
    sjt_math1416 = (sjt_dot915)->m30;
#line 105
    sjt_math1408 = sjt_math1415 * sjt_math1416;
#line 105
    sjt_math1405 = sjt_math1407 - sjt_math1408;
#line 104
    sjt_dot916 = _parent;
#line 105
    sjt_math1425 = (sjt_dot916)->m03;
#line 104
    sjt_dot917 = _parent;
#line 105
    sjt_math1426 = (sjt_dot917)->m11;
#line 105
    sjt_math1423 = sjt_math1425 * sjt_math1426;
#line 104
    sjt_dot918 = _parent;
#line 105
    sjt_math1424 = (sjt_dot918)->m22;
#line 105
    sjt_math1421 = sjt_math1423 * sjt_math1424;
#line 104
    sjt_dot919 = _parent;
#line 105
    sjt_math1422 = (sjt_dot919)->m30;
#line 105
    sjt_math1406 = sjt_math1421 * sjt_math1422;
#line 105
    sjt_math1403 = sjt_math1405 - sjt_math1406;
#line 104
    sjt_dot920 = _parent;
#line 105
    sjt_math1431 = (sjt_dot920)->m01;
#line 104
    sjt_dot921 = _parent;
#line 105
    sjt_math1432 = (sjt_dot921)->m13;
#line 105
    sjt_math1429 = sjt_math1431 * sjt_math1432;
#line 104
    sjt_dot922 = _parent;
#line 105
    sjt_math1430 = (sjt_dot922)->m22;
#line 105
    sjt_math1427 = sjt_math1429 * sjt_math1430;
#line 104
    sjt_dot923 = _parent;
#line 105
    sjt_math1428 = (sjt_dot923)->m30;
#line 105
    sjt_math1404 = sjt_math1427 * sjt_math1428;
#line 105
    sjt_math1401 = sjt_math1403 + sjt_math1404;
#line 104
    sjt_dot924 = _parent;
#line 105
    sjt_math1437 = (sjt_dot924)->m02;
#line 104
    sjt_dot925 = _parent;
#line 105
    sjt_math1438 = (sjt_dot925)->m11;
#line 105
    sjt_math1435 = sjt_math1437 * sjt_math1438;
#line 104
    sjt_dot926 = _parent;
#line 105
    sjt_math1436 = (sjt_dot926)->m23;
#line 105
    sjt_math1433 = sjt_math1435 * sjt_math1436;
#line 104
    sjt_dot927 = _parent;
#line 105
    sjt_math1434 = (sjt_dot927)->m30;
#line 105
    sjt_math1402 = sjt_math1433 * sjt_math1434;
#line 105
    sjt_math1399 = sjt_math1401 + sjt_math1402;
#line 104
    sjt_dot928 = _parent;
#line 105
    sjt_math1443 = (sjt_dot928)->m01;
#line 104
    sjt_dot929 = _parent;
#line 105
    sjt_math1444 = (sjt_dot929)->m12;
#line 105
    sjt_math1441 = sjt_math1443 * sjt_math1444;
#line 104
    sjt_dot930 = _parent;
#line 105
    sjt_math1442 = (sjt_dot930)->m23;
#line 105
    sjt_math1439 = sjt_math1441 * sjt_math1442;
#line 104
    sjt_dot931 = _parent;
#line 105
    sjt_math1440 = (sjt_dot931)->m30;
#line 105
    sjt_math1400 = sjt_math1439 * sjt_math1440;
#line 105
    sjt_math1397 = sjt_math1399 - sjt_math1400;
#line 104
    sjt_dot932 = _parent;
#line 105
    sjt_math1449 = (sjt_dot932)->m03;
#line 104
    sjt_dot933 = _parent;
#line 105
    sjt_math1450 = (sjt_dot933)->m12;
#line 105
    sjt_math1447 = sjt_math1449 * sjt_math1450;
#line 104
    sjt_dot934 = _parent;
#line 105
    sjt_math1448 = (sjt_dot934)->m20;
#line 105
    sjt_math1445 = sjt_math1447 * sjt_math1448;
#line 104
    sjt_dot935 = _parent;
#line 105
    sjt_math1446 = (sjt_dot935)->m31;
#line 105
    sjt_math1398 = sjt_math1445 * sjt_math1446;
#line 105
    sjt_math1395 = sjt_math1397 - sjt_math1398;
#line 104
    sjt_dot936 = _parent;
#line 105
    sjt_math1455 = (sjt_dot936)->m02;
#line 104
    sjt_dot937 = _parent;
#line 105
    sjt_math1456 = (sjt_dot937)->m13;
#line 105
    sjt_math1453 = sjt_math1455 * sjt_math1456;
#line 104
    sjt_dot938 = _parent;
#line 105
    sjt_math1454 = (sjt_dot938)->m20;
#line 105
    sjt_math1451 = sjt_math1453 * sjt_math1454;
#line 104
    sjt_dot939 = _parent;
#line 105
    sjt_math1452 = (sjt_dot939)->m31;
#line 105
    sjt_math1396 = sjt_math1451 * sjt_math1452;
#line 105
    sjt_math1393 = sjt_math1395 + sjt_math1396;
#line 104
    sjt_dot940 = _parent;
#line 105
    sjt_math1461 = (sjt_dot940)->m03;
#line 104
    sjt_dot941 = _parent;
#line 105
    sjt_math1462 = (sjt_dot941)->m10;
#line 105
    sjt_math1459 = sjt_math1461 * sjt_math1462;
#line 104
    sjt_dot942 = _parent;
#line 105
    sjt_math1460 = (sjt_dot942)->m22;
#line 105
    sjt_math1457 = sjt_math1459 * sjt_math1460;
#line 104
    sjt_dot943 = _parent;
#line 105
    sjt_math1458 = (sjt_dot943)->m31;
#line 105
    sjt_math1394 = sjt_math1457 * sjt_math1458;
#line 105
    sjt_math1391 = sjt_math1393 + sjt_math1394;
#line 104
    sjt_dot944 = _parent;
#line 105
    sjt_math1467 = (sjt_dot944)->m00;
#line 104
    sjt_dot945 = _parent;
#line 105
    sjt_math1468 = (sjt_dot945)->m13;
#line 105
    sjt_math1465 = sjt_math1467 * sjt_math1468;
#line 104
    sjt_dot946 = _parent;
#line 105
    sjt_math1466 = (sjt_dot946)->m22;
#line 105
    sjt_math1463 = sjt_math1465 * sjt_math1466;
#line 104
    sjt_dot947 = _parent;
#line 105
    sjt_math1464 = (sjt_dot947)->m31;
#line 105
    sjt_math1392 = sjt_math1463 * sjt_math1464;
#line 105
    sjt_math1389 = sjt_math1391 - sjt_math1392;
#line 104
    sjt_dot948 = _parent;
#line 105
    sjt_math1473 = (sjt_dot948)->m02;
#line 104
    sjt_dot949 = _parent;
#line 105
    sjt_math1474 = (sjt_dot949)->m10;
#line 105
    sjt_math1471 = sjt_math1473 * sjt_math1474;
#line 104
    sjt_dot950 = _parent;
#line 105
    sjt_math1472 = (sjt_dot950)->m23;
#line 105
    sjt_math1469 = sjt_math1471 * sjt_math1472;
#line 104
    sjt_dot951 = _parent;
#line 105
    sjt_math1470 = (sjt_dot951)->m31;
#line 105
    sjt_math1390 = sjt_math1469 * sjt_math1470;
#line 105
    sjt_math1387 = sjt_math1389 - sjt_math1390;
#line 104
    sjt_dot952 = _parent;
#line 105
    sjt_math1479 = (sjt_dot952)->m00;
#line 104
    sjt_dot953 = _parent;
#line 105
    sjt_math1480 = (sjt_dot953)->m12;
#line 105
    sjt_math1477 = sjt_math1479 * sjt_math1480;
#line 104
    sjt_dot954 = _parent;
#line 105
    sjt_math1478 = (sjt_dot954)->m23;
#line 105
    sjt_math1475 = sjt_math1477 * sjt_math1478;
#line 104
    sjt_dot955 = _parent;
#line 105
    sjt_math1476 = (sjt_dot955)->m31;
#line 105
    sjt_math1388 = sjt_math1475 * sjt_math1476;
#line 105
    sjt_math1385 = sjt_math1387 + sjt_math1388;
#line 104
    sjt_dot956 = _parent;
#line 105
    sjt_math1485 = (sjt_dot956)->m03;
#line 104
    sjt_dot957 = _parent;
#line 105
    sjt_math1486 = (sjt_dot957)->m11;
#line 105
    sjt_math1483 = sjt_math1485 * sjt_math1486;
#line 104
    sjt_dot958 = _parent;
#line 105
    sjt_math1484 = (sjt_dot958)->m20;
#line 105
    sjt_math1481 = sjt_math1483 * sjt_math1484;
#line 104
    sjt_dot959 = _parent;
#line 105
    sjt_math1482 = (sjt_dot959)->m32;
#line 105
    sjt_math1386 = sjt_math1481 * sjt_math1482;
#line 105
    sjt_math1383 = sjt_math1385 + sjt_math1386;
#line 104
    sjt_dot960 = _parent;
#line 105
    sjt_math1491 = (sjt_dot960)->m01;
#line 104
    sjt_dot961 = _parent;
#line 105
    sjt_math1492 = (sjt_dot961)->m13;
#line 105
    sjt_math1489 = sjt_math1491 * sjt_math1492;
#line 104
    sjt_dot962 = _parent;
#line 105
    sjt_math1490 = (sjt_dot962)->m20;
#line 105
    sjt_math1487 = sjt_math1489 * sjt_math1490;
#line 104
    sjt_dot963 = _parent;
#line 105
    sjt_math1488 = (sjt_dot963)->m32;
#line 105
    sjt_math1384 = sjt_math1487 * sjt_math1488;
#line 105
    sjt_math1381 = sjt_math1383 - sjt_math1384;
#line 104
    sjt_dot964 = _parent;
#line 105
    sjt_math1497 = (sjt_dot964)->m03;
#line 104
    sjt_dot965 = _parent;
#line 105
    sjt_math1498 = (sjt_dot965)->m10;
#line 105
    sjt_math1495 = sjt_math1497 * sjt_math1498;
#line 104
    sjt_dot966 = _parent;
#line 105
    sjt_math1496 = (sjt_dot966)->m21;
#line 105
    sjt_math1493 = sjt_math1495 * sjt_math1496;
#line 104
    sjt_dot967 = _parent;
#line 105
    sjt_math1494 = (sjt_dot967)->m32;
#line 105
    sjt_math1382 = sjt_math1493 * sjt_math1494;
#line 105
    sjt_math1379 = sjt_math1381 - sjt_math1382;
#line 104
    sjt_dot968 = _parent;
#line 105
    sjt_math1503 = (sjt_dot968)->m00;
#line 104
    sjt_dot969 = _parent;
#line 105
    sjt_math1504 = (sjt_dot969)->m13;
#line 105
    sjt_math1501 = sjt_math1503 * sjt_math1504;
#line 104
    sjt_dot970 = _parent;
#line 105
    sjt_math1502 = (sjt_dot970)->m21;
#line 105
    sjt_math1499 = sjt_math1501 * sjt_math1502;
#line 104
    sjt_dot971 = _parent;
#line 105
    sjt_math1500 = (sjt_dot971)->m32;
#line 105
    sjt_math1380 = sjt_math1499 * sjt_math1500;
#line 105
    sjt_math1377 = sjt_math1379 + sjt_math1380;
#line 104
    sjt_dot972 = _parent;
#line 105
    sjt_math1509 = (sjt_dot972)->m01;
#line 104
    sjt_dot973 = _parent;
#line 105
    sjt_math1510 = (sjt_dot973)->m10;
#line 105
    sjt_math1507 = sjt_math1509 * sjt_math1510;
#line 104
    sjt_dot974 = _parent;
#line 105
    sjt_math1508 = (sjt_dot974)->m23;
#line 105
    sjt_math1505 = sjt_math1507 * sjt_math1508;
#line 104
    sjt_dot975 = _parent;
#line 105
    sjt_math1506 = (sjt_dot975)->m32;
#line 105
    sjt_math1378 = sjt_math1505 * sjt_math1506;
#line 105
    sjt_math1375 = sjt_math1377 + sjt_math1378;
#line 104
    sjt_dot976 = _parent;
#line 105
    sjt_math1515 = (sjt_dot976)->m00;
#line 104
    sjt_dot977 = _parent;
#line 105
    sjt_math1516 = (sjt_dot977)->m11;
#line 105
    sjt_math1513 = sjt_math1515 * sjt_math1516;
#line 104
    sjt_dot978 = _parent;
#line 105
    sjt_math1514 = (sjt_dot978)->m23;
#line 105
    sjt_math1511 = sjt_math1513 * sjt_math1514;
#line 104
    sjt_dot979 = _parent;
#line 105
    sjt_math1512 = (sjt_dot979)->m32;
#line 105
    sjt_math1376 = sjt_math1511 * sjt_math1512;
#line 105
    sjt_math1373 = sjt_math1375 - sjt_math1376;
#line 104
    sjt_dot980 = _parent;
#line 105
    sjt_math1521 = (sjt_dot980)->m02;
#line 104
    sjt_dot981 = _parent;
#line 105
    sjt_math1522 = (sjt_dot981)->m11;
#line 105
    sjt_math1519 = sjt_math1521 * sjt_math1522;
#line 104
    sjt_dot982 = _parent;
#line 105
    sjt_math1520 = (sjt_dot982)->m20;
#line 105
    sjt_math1517 = sjt_math1519 * sjt_math1520;
#line 104
    sjt_dot983 = _parent;
#line 105
    sjt_math1518 = (sjt_dot983)->m33;
#line 105
    sjt_math1374 = sjt_math1517 * sjt_math1518;
#line 105
    sjt_math1371 = sjt_math1373 - sjt_math1374;
#line 104
    sjt_dot984 = _parent;
#line 105
    sjt_math1527 = (sjt_dot984)->m01;
#line 104
    sjt_dot985 = _parent;
#line 105
    sjt_math1528 = (sjt_dot985)->m12;
#line 105
    sjt_math1525 = sjt_math1527 * sjt_math1528;
#line 104
    sjt_dot986 = _parent;
#line 105
    sjt_math1526 = (sjt_dot986)->m20;
#line 105
    sjt_math1523 = sjt_math1525 * sjt_math1526;
#line 104
    sjt_dot987 = _parent;
#line 105
    sjt_math1524 = (sjt_dot987)->m33;
#line 105
    sjt_math1372 = sjt_math1523 * sjt_math1524;
#line 105
    sjt_math1369 = sjt_math1371 + sjt_math1372;
#line 104
    sjt_dot988 = _parent;
#line 105
    sjt_math1533 = (sjt_dot988)->m02;
#line 104
    sjt_dot989 = _parent;
#line 105
    sjt_math1534 = (sjt_dot989)->m10;
#line 105
    sjt_math1531 = sjt_math1533 * sjt_math1534;
#line 104
    sjt_dot990 = _parent;
#line 105
    sjt_math1532 = (sjt_dot990)->m21;
#line 105
    sjt_math1529 = sjt_math1531 * sjt_math1532;
#line 104
    sjt_dot991 = _parent;
#line 105
    sjt_math1530 = (sjt_dot991)->m33;
#line 105
    sjt_math1370 = sjt_math1529 * sjt_math1530;
#line 105
    sjt_math1367 = sjt_math1369 + sjt_math1370;
#line 104
    sjt_dot992 = _parent;
#line 105
    sjt_math1539 = (sjt_dot992)->m00;
#line 104
    sjt_dot993 = _parent;
#line 105
    sjt_math1540 = (sjt_dot993)->m12;
#line 105
    sjt_math1537 = sjt_math1539 * sjt_math1540;
#line 104
    sjt_dot994 = _parent;
#line 105
    sjt_math1538 = (sjt_dot994)->m21;
#line 105
    sjt_math1535 = sjt_math1537 * sjt_math1538;
#line 104
    sjt_dot995 = _parent;
#line 105
    sjt_math1536 = (sjt_dot995)->m33;
#line 105
    sjt_math1368 = sjt_math1535 * sjt_math1536;
#line 105
    sjt_math1365 = sjt_math1367 - sjt_math1368;
#line 104
    sjt_dot996 = _parent;
#line 105
    sjt_math1545 = (sjt_dot996)->m01;
#line 104
    sjt_dot997 = _parent;
#line 105
    sjt_math1546 = (sjt_dot997)->m10;
#line 105
    sjt_math1543 = sjt_math1545 * sjt_math1546;
#line 104
    sjt_dot998 = _parent;
#line 105
    sjt_math1544 = (sjt_dot998)->m22;
#line 105
    sjt_math1541 = sjt_math1543 * sjt_math1544;
#line 104
    sjt_dot999 = _parent;
#line 105
    sjt_math1542 = (sjt_dot999)->m33;
#line 105
    sjt_math1366 = sjt_math1541 * sjt_math1542;
#line 105
    sjt_math1363 = sjt_math1365 - sjt_math1366;
#line 104
    sjt_dot1000 = _parent;
#line 105
    sjt_math1551 = (sjt_dot1000)->m00;
#line 104
    sjt_dot1001 = _parent;
#line 105
    sjt_math1552 = (sjt_dot1001)->m11;
#line 105
    sjt_math1549 = sjt_math1551 * sjt_math1552;
#line 104
    sjt_dot1002 = _parent;
#line 105
    sjt_math1550 = (sjt_dot1002)->m22;
#line 105
    sjt_math1547 = sjt_math1549 * sjt_math1550;
#line 104
    sjt_dot1003 = _parent;
#line 105
    sjt_math1548 = (sjt_dot1003)->m33;
#line 105
    sjt_math1364 = sjt_math1547 * sjt_math1548;
#line 105
    (*_return) = sjt_math1363 + sjt_math1364;
}

void sjf_mat4_heap(sjs_mat4_heap* _this) {
}

void sjf_mat4_identity(sjs_mat4* _return) {
#line 136 "lib/ui/mat4.sj"
    _return->m00 = 1.0f;
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 137
    _return->m11 = 1.0f;
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 138
    _return->m22 = 1.0f;
#line 13
    _return->m23 = 0.0f;
#line 14
    _return->m30 = 0.0f;
#line 15
    _return->m31 = 0.0f;
#line 16
    _return->m32 = 0.0f;
#line 139
    _return->m33 = 1.0f;
#line 139
    sjf_mat4(_return);
}

void sjf_mat4_identity_heap(sjs_mat4_heap** _return) {
    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
    (*_return)->_refCount = 1;
#line 136 "lib/ui/mat4.sj"
    (*_return)->m00 = 1.0f;
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 137
    (*_return)->m11 = 1.0f;
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 138
    (*_return)->m22 = 1.0f;
#line 13
    (*_return)->m23 = 0.0f;
#line 14
    (*_return)->m30 = 0.0f;
#line 15
    (*_return)->m31 = 0.0f;
#line 16
    (*_return)->m32 = 0.0f;
#line 139
    (*_return)->m33 = 1.0f;
#line 139
    sjf_mat4_heap((*_return));
}

void sjf_mat4_invert(sjs_mat4* _parent, sjs_mat4* _return) {
    sjs_mat4* sjt_dot588;
    sjs_mat4* sjt_dot589;
    sjs_mat4* sjt_dot590;
    sjs_mat4* sjt_dot591;
    sjs_mat4* sjt_dot592;
    sjs_mat4* sjt_dot593;
    sjs_mat4* sjt_dot594;
    sjs_mat4* sjt_dot595;
    sjs_mat4* sjt_dot596;
    sjs_mat4* sjt_dot597;
    sjs_mat4* sjt_dot598;
    sjs_mat4* sjt_dot599;
    sjs_mat4* sjt_dot600;
    sjs_mat4* sjt_dot601;
    sjs_mat4* sjt_dot602;
    sjs_mat4* sjt_dot603;
    sjs_mat4* sjt_dot604;
    sjs_mat4* sjt_dot605;
    sjs_mat4* sjt_dot606;
    sjs_mat4* sjt_dot607;
    sjs_mat4* sjt_dot608;
    sjs_mat4* sjt_dot609;
    sjs_mat4* sjt_dot610;
    sjs_mat4* sjt_dot611;
    sjs_mat4* sjt_dot612;
    sjs_mat4* sjt_dot613;
    sjs_mat4* sjt_dot614;
    sjs_mat4* sjt_dot615;
    sjs_mat4* sjt_dot616;
    sjs_mat4* sjt_dot617;
    sjs_mat4* sjt_dot618;
    sjs_mat4* sjt_dot619;
    sjs_mat4* sjt_dot620;
    sjs_mat4* sjt_dot621;
    sjs_mat4* sjt_dot622;
    sjs_mat4* sjt_dot623;
    sjs_mat4* sjt_dot624;
    sjs_mat4* sjt_dot625;
    sjs_mat4* sjt_dot626;
    sjs_mat4* sjt_dot627;
    sjs_mat4* sjt_dot628;
    sjs_mat4* sjt_dot629;
    sjs_mat4* sjt_dot630;
    sjs_mat4* sjt_dot631;
    sjs_mat4* sjt_dot632;
    sjs_mat4* sjt_dot633;
    sjs_mat4* sjt_dot634;
    sjs_mat4* sjt_dot635;
    sjs_mat4* sjt_dot636;
    sjs_mat4* sjt_dot637;
    sjs_mat4* sjt_dot638;
    sjs_mat4* sjt_dot639;
    sjs_mat4* sjt_dot640;
    sjs_mat4* sjt_dot641;
    sjs_mat4* sjt_dot642;
    sjs_mat4* sjt_dot643;
    sjs_mat4* sjt_dot644;
    sjs_mat4* sjt_dot645;
    sjs_mat4* sjt_dot646;
    sjs_mat4* sjt_dot647;
    sjs_mat4* sjt_dot648;
    sjs_mat4* sjt_dot649;
    sjs_mat4* sjt_dot650;
    sjs_mat4* sjt_dot651;
    sjs_mat4* sjt_dot652;
    sjs_mat4* sjt_dot653;
    sjs_mat4* sjt_dot654;
    sjs_mat4* sjt_dot655;
    sjs_mat4* sjt_dot656;
    sjs_mat4* sjt_dot657;
    sjs_mat4* sjt_dot658;
    sjs_mat4* sjt_dot659;
    sjs_mat4* sjt_dot660;
    sjs_mat4* sjt_dot661;
    sjs_mat4* sjt_dot662;
    sjs_mat4* sjt_dot663;
    sjs_mat4* sjt_dot664;
    sjs_mat4* sjt_dot665;
    sjs_mat4* sjt_dot666;
    sjs_mat4* sjt_dot667;
    sjs_mat4* sjt_dot668;
    sjs_mat4* sjt_dot669;
    sjs_mat4* sjt_dot670;
    sjs_mat4* sjt_dot671;
    sjs_mat4* sjt_dot672;
    sjs_mat4* sjt_dot673;
    sjs_mat4* sjt_dot674;
    sjs_mat4* sjt_dot675;
    sjs_mat4* sjt_dot676;
    sjs_mat4* sjt_dot677;
    sjs_mat4* sjt_dot678;
    sjs_mat4* sjt_dot679;
    sjs_mat4* sjt_dot680;
    sjs_mat4* sjt_dot681;
    sjs_mat4* sjt_dot682;
    sjs_mat4* sjt_dot683;
    sjs_mat4* sjt_dot684;
    sjs_mat4* sjt_dot685;
    sjs_mat4* sjt_dot686;
    sjs_mat4* sjt_dot687;
    sjs_mat4* sjt_dot688;
    sjs_mat4* sjt_dot689;
    sjs_mat4* sjt_dot690;
    sjs_mat4* sjt_dot691;
    sjs_mat4* sjt_dot692;
    sjs_mat4* sjt_dot693;
    sjs_mat4* sjt_dot694;
    sjs_mat4* sjt_dot695;
    sjs_mat4* sjt_dot696;
    sjs_mat4* sjt_dot697;
    sjs_mat4* sjt_dot698;
    sjs_mat4* sjt_dot699;
    sjs_mat4* sjt_dot700;
    sjs_mat4* sjt_dot701;
    sjs_mat4* sjt_dot702;
    sjs_mat4* sjt_dot703;
    sjs_mat4* sjt_dot704;
    sjs_mat4* sjt_dot705;
    sjs_mat4* sjt_dot706;
    sjs_mat4* sjt_dot707;
    sjs_mat4* sjt_dot708;
    sjs_mat4* sjt_dot709;
    sjs_mat4* sjt_dot710;
    sjs_mat4* sjt_dot711;
    sjs_mat4* sjt_dot712;
    sjs_mat4* sjt_dot713;
    sjs_mat4* sjt_dot714;
    sjs_mat4* sjt_dot715;
    sjs_mat4* sjt_dot716;
    sjs_mat4* sjt_dot717;
    sjs_mat4* sjt_dot718;
    sjs_mat4* sjt_dot719;
    sjs_mat4* sjt_dot720;
    sjs_mat4* sjt_dot721;
    sjs_mat4* sjt_dot722;
    sjs_mat4* sjt_dot723;
    sjs_mat4* sjt_dot724;
    sjs_mat4* sjt_dot725;
    sjs_mat4* sjt_dot726;
    sjs_mat4* sjt_dot727;
    sjs_mat4* sjt_dot728;
    sjs_mat4* sjt_dot729;
    sjs_mat4* sjt_dot730;
    sjs_mat4* sjt_dot731;
    sjs_mat4* sjt_dot732;
    sjs_mat4* sjt_dot733;
    sjs_mat4* sjt_dot734;
    sjs_mat4* sjt_dot735;
    sjs_mat4* sjt_dot736;
    sjs_mat4* sjt_dot737;
    sjs_mat4* sjt_dot738;
    sjs_mat4* sjt_dot739;
    sjs_mat4* sjt_dot740;
    sjs_mat4* sjt_dot741;
    sjs_mat4* sjt_dot742;
    sjs_mat4* sjt_dot743;
    sjs_mat4* sjt_dot744;
    sjs_mat4* sjt_dot745;
    sjs_mat4* sjt_dot746;
    sjs_mat4* sjt_dot747;
    sjs_mat4* sjt_dot748;
    sjs_mat4* sjt_dot749;
    sjs_mat4* sjt_dot750;
    sjs_mat4* sjt_dot751;
    sjs_mat4* sjt_dot752;
    sjs_mat4* sjt_dot753;
    sjs_mat4* sjt_dot754;
    sjs_mat4* sjt_dot755;
    sjs_mat4* sjt_dot756;
    sjs_mat4* sjt_dot757;
    sjs_mat4* sjt_dot758;
    sjs_mat4* sjt_dot759;
    sjs_mat4* sjt_dot760;
    sjs_mat4* sjt_dot761;
    sjs_mat4* sjt_dot762;
    sjs_mat4* sjt_dot763;
    sjs_mat4* sjt_dot764;
    sjs_mat4* sjt_dot765;
    sjs_mat4* sjt_dot766;
    sjs_mat4* sjt_dot767;
    sjs_mat4* sjt_dot768;
    sjs_mat4* sjt_dot769;
    sjs_mat4* sjt_dot770;
    sjs_mat4* sjt_dot771;
    sjs_mat4* sjt_dot772;
    sjs_mat4* sjt_dot773;
    sjs_mat4* sjt_dot774;
    sjs_mat4* sjt_dot775;
    sjs_mat4* sjt_dot776;
    sjs_mat4* sjt_dot777;
    sjs_mat4* sjt_dot778;
    sjs_mat4* sjt_dot779;
    sjs_mat4* sjt_dot780;
    sjs_mat4* sjt_dot781;
    sjs_mat4* sjt_dot782;
    sjs_mat4* sjt_dot783;
    sjs_mat4* sjt_dot784;
    sjs_mat4* sjt_dot785;
    sjs_mat4* sjt_dot786;
    sjs_mat4* sjt_dot787;
    sjs_mat4* sjt_dot788;
    sjs_mat4* sjt_dot789;
    sjs_mat4* sjt_dot790;
    sjs_mat4* sjt_dot791;
    sjs_mat4* sjt_dot792;
    sjs_mat4* sjt_dot793;
    sjs_mat4* sjt_dot794;
    sjs_mat4* sjt_dot795;
    sjs_mat4* sjt_dot796;
    sjs_mat4* sjt_dot797;
    sjs_mat4* sjt_dot798;
    sjs_mat4* sjt_dot799;
    sjs_mat4* sjt_dot800;
    sjs_mat4* sjt_dot801;
    sjs_mat4* sjt_dot802;
    sjs_mat4* sjt_dot803;
    sjs_mat4* sjt_dot804;
    sjs_mat4* sjt_dot805;
    sjs_mat4* sjt_dot806;
    sjs_mat4* sjt_dot807;
    sjs_mat4* sjt_dot808;
    sjs_mat4* sjt_dot809;
    sjs_mat4* sjt_dot810;
    sjs_mat4* sjt_dot811;
    sjs_mat4* sjt_dot812;
    sjs_mat4* sjt_dot813;
    sjs_mat4* sjt_dot814;
    sjs_mat4* sjt_dot815;
    sjs_mat4* sjt_dot816;
    sjs_mat4* sjt_dot817;
    sjs_mat4* sjt_dot818;
    sjs_mat4* sjt_dot819;
    sjs_mat4* sjt_dot820;
    sjs_mat4* sjt_dot821;
    sjs_mat4* sjt_dot822;
    sjs_mat4* sjt_dot823;
    sjs_mat4* sjt_dot824;
    sjs_mat4* sjt_dot825;
    sjs_mat4* sjt_dot826;
    sjs_mat4* sjt_dot827;
    sjs_mat4* sjt_dot828;
    sjs_mat4* sjt_dot829;
    sjs_mat4* sjt_dot830;
    sjs_mat4* sjt_dot831;
    sjs_mat4* sjt_dot832;
    sjs_mat4* sjt_dot833;
    sjs_mat4* sjt_dot834;
    sjs_mat4* sjt_dot835;
    sjs_mat4* sjt_dot836;
    sjs_mat4* sjt_dot837;
    sjs_mat4* sjt_dot838;
    sjs_mat4* sjt_dot839;
    sjs_mat4* sjt_dot840;
    sjs_mat4* sjt_dot841;
    sjs_mat4* sjt_dot842;
    sjs_mat4* sjt_dot843;
    sjs_mat4* sjt_dot844;
    sjs_mat4* sjt_dot845;
    sjs_mat4* sjt_dot846;
    sjs_mat4* sjt_dot847;
    sjs_mat4* sjt_dot848;
    sjs_mat4* sjt_dot849;
    sjs_mat4* sjt_dot850;
    sjs_mat4* sjt_dot851;
    sjs_mat4* sjt_dot852;
    sjs_mat4* sjt_dot853;
    sjs_mat4* sjt_dot854;
    sjs_mat4* sjt_dot855;
    sjs_mat4* sjt_dot856;
    sjs_mat4* sjt_dot857;
    sjs_mat4* sjt_dot858;
    sjs_mat4* sjt_dot859;
    sjs_mat4* sjt_dot860;
    sjs_mat4* sjt_dot861;
    sjs_mat4* sjt_dot862;
    sjs_mat4* sjt_dot863;
    sjs_mat4* sjt_dot864;
    sjs_mat4* sjt_dot865;
    sjs_mat4* sjt_dot866;
    sjs_mat4* sjt_dot867;
    sjs_mat4* sjt_dot868;
    sjs_mat4* sjt_dot869;
    sjs_mat4* sjt_dot870;
    sjs_mat4* sjt_dot871;
    sjs_mat4* sjt_dot872;
    sjs_mat4* sjt_dot873;
    sjs_mat4* sjt_dot874;
    sjs_mat4* sjt_dot875;
    float sjt_functionParam112;
    float sjt_math1000;
    float sjt_math1001;
    float sjt_math1002;
    float sjt_math1003;
    float sjt_math1004;
    float sjt_math1005;
    float sjt_math1006;
    float sjt_math1007;
    float sjt_math1008;
    float sjt_math1009;
    float sjt_math1010;
    float sjt_math1011;
    float sjt_math1012;
    float sjt_math1013;
    float sjt_math1014;
    float sjt_math1015;
    float sjt_math1016;
    float sjt_math1017;
    float sjt_math1018;
    float sjt_math1019;
    float sjt_math1020;
    float sjt_math1021;
    float sjt_math1022;
    float sjt_math1023;
    float sjt_math1024;
    float sjt_math1025;
    float sjt_math1026;
    float sjt_math1027;
    float sjt_math1028;
    float sjt_math1029;
    float sjt_math1030;
    float sjt_math1031;
    float sjt_math1032;
    float sjt_math1033;
    float sjt_math1034;
    float sjt_math1035;
    float sjt_math1036;
    float sjt_math1037;
    float sjt_math1038;
    float sjt_math1039;
    float sjt_math1040;
    float sjt_math1041;
    float sjt_math1042;
    float sjt_math1043;
    float sjt_math1044;
    float sjt_math1045;
    float sjt_math1046;
    float sjt_math1047;
    float sjt_math1048;
    float sjt_math1049;
    float sjt_math1050;
    float sjt_math1051;
    float sjt_math1052;
    float sjt_math1053;
    float sjt_math1054;
    float sjt_math1055;
    float sjt_math1056;
    float sjt_math1057;
    float sjt_math1058;
    float sjt_math1059;
    float sjt_math1060;
    float sjt_math1061;
    float sjt_math1062;
    float sjt_math1063;
    float sjt_math1064;
    float sjt_math1065;
    float sjt_math1066;
    float sjt_math1067;
    float sjt_math1068;
    float sjt_math1069;
    float sjt_math1070;
    float sjt_math1071;
    float sjt_math1072;
    float sjt_math1073;
    float sjt_math1074;
    float sjt_math1075;
    float sjt_math1076;
    float sjt_math1077;
    float sjt_math1078;
    float sjt_math1079;
    float sjt_math1080;
    float sjt_math1081;
    float sjt_math1082;
    float sjt_math1083;
    float sjt_math1084;
    float sjt_math1085;
    float sjt_math1086;
    float sjt_math1087;
    float sjt_math1088;
    float sjt_math1089;
    float sjt_math1090;
    float sjt_math1091;
    float sjt_math1092;
    float sjt_math1093;
    float sjt_math1094;
    float sjt_math1095;
    float sjt_math1096;
    float sjt_math1097;
    float sjt_math1098;
    float sjt_math1099;
    float sjt_math1100;
    float sjt_math1101;
    float sjt_math1102;
    float sjt_math1103;
    float sjt_math1104;
    float sjt_math1105;
    float sjt_math1106;
    float sjt_math1107;
    float sjt_math1108;
    float sjt_math1109;
    float sjt_math1110;
    float sjt_math1111;
    float sjt_math1112;
    float sjt_math1113;
    float sjt_math1114;
    float sjt_math1115;
    float sjt_math1116;
    float sjt_math1117;
    float sjt_math1118;
    float sjt_math1119;
    float sjt_math1120;
    float sjt_math1121;
    float sjt_math1122;
    float sjt_math1123;
    float sjt_math1124;
    float sjt_math1125;
    float sjt_math1126;
    float sjt_math1127;
    float sjt_math1128;
    float sjt_math1129;
    float sjt_math1130;
    float sjt_math1131;
    float sjt_math1132;
    float sjt_math1133;
    float sjt_math1134;
    float sjt_math1135;
    float sjt_math1136;
    float sjt_math1137;
    float sjt_math1138;
    float sjt_math1139;
    float sjt_math1140;
    float sjt_math1141;
    float sjt_math1142;
    float sjt_math1143;
    float sjt_math1144;
    float sjt_math1145;
    float sjt_math1146;
    float sjt_math1147;
    float sjt_math1148;
    float sjt_math1149;
    float sjt_math1150;
    float sjt_math1151;
    float sjt_math1152;
    float sjt_math1153;
    float sjt_math1154;
    float sjt_math1155;
    float sjt_math1156;
    float sjt_math1157;
    float sjt_math1158;
    float sjt_math1159;
    float sjt_math1160;
    float sjt_math1161;
    float sjt_math1162;
    float sjt_math1163;
    float sjt_math1164;
    float sjt_math1165;
    float sjt_math1166;
    float sjt_math1167;
    float sjt_math1168;
    float sjt_math1169;
    float sjt_math1170;
    float sjt_math1171;
    float sjt_math1172;
    float sjt_math1173;
    float sjt_math1174;
    float sjt_math1175;
    float sjt_math1176;
    float sjt_math1177;
    float sjt_math1178;
    float sjt_math1179;
    float sjt_math1180;
    float sjt_math1181;
    float sjt_math1182;
    float sjt_math1183;
    float sjt_math1184;
    float sjt_math1185;
    float sjt_math1186;
    float sjt_math1187;
    float sjt_math1188;
    float sjt_math1189;
    float sjt_math1190;
    float sjt_math1191;
    float sjt_math1192;
    float sjt_math1193;
    float sjt_math1194;
    float sjt_math1195;
    float sjt_math1196;
    float sjt_math1197;
    float sjt_math1198;
    float sjt_math1199;
    float sjt_math1200;
    float sjt_math1201;
    float sjt_math1202;
    float sjt_math1203;
    float sjt_math1204;
    float sjt_math1205;
    float sjt_math1206;
    float sjt_math1207;
    float sjt_math1208;
    float sjt_math1209;
    float sjt_math1210;
    float sjt_math1211;
    float sjt_math1212;
    float sjt_math1213;
    float sjt_math1214;
    float sjt_math1215;
    float sjt_math1216;
    float sjt_math1217;
    float sjt_math1218;
    float sjt_math1219;
    float sjt_math1220;
    float sjt_math1221;
    float sjt_math1222;
    float sjt_math1223;
    float sjt_math1224;
    float sjt_math1225;
    float sjt_math1226;
    float sjt_math1227;
    float sjt_math1228;
    float sjt_math1229;
    float sjt_math1230;
    float sjt_math1231;
    float sjt_math1232;
    float sjt_math1233;
    float sjt_math1234;
    float sjt_math1235;
    float sjt_math1236;
    float sjt_math1237;
    float sjt_math1238;
    float sjt_math1239;
    float sjt_math1240;
    float sjt_math1241;
    float sjt_math1242;
    float sjt_math1243;
    float sjt_math1244;
    float sjt_math1245;
    float sjt_math1246;
    float sjt_math1247;
    float sjt_math1248;
    float sjt_math1249;
    float sjt_math1250;
    float sjt_math1251;
    float sjt_math1252;
    float sjt_math1253;
    float sjt_math1254;
    float sjt_math1255;
    float sjt_math1256;
    float sjt_math1257;
    float sjt_math1258;
    float sjt_math1259;
    float sjt_math1260;
    float sjt_math1261;
    float sjt_math1262;
    float sjt_math1263;
    float sjt_math1264;
    float sjt_math1265;
    float sjt_math1266;
    float sjt_math1267;
    float sjt_math1268;
    float sjt_math1269;
    float sjt_math1270;
    float sjt_math1271;
    float sjt_math1272;
    float sjt_math1273;
    float sjt_math1274;
    float sjt_math1275;
    float sjt_math1276;
    float sjt_math1277;
    float sjt_math1278;
    float sjt_math1279;
    float sjt_math1280;
    float sjt_math1281;
    float sjt_math1282;
    float sjt_math1283;
    float sjt_math1284;
    float sjt_math1285;
    float sjt_math1286;
    float sjt_math1287;
    float sjt_math1288;
    float sjt_math1289;
    float sjt_math1290;
    float sjt_math1291;
    float sjt_math1292;
    float sjt_math1293;
    float sjt_math1294;
    float sjt_math1295;
    float sjt_math1296;
    float sjt_math1361;
    float sjt_math1362;
    float sjt_math753;
    float sjt_math754;
    float sjt_math755;
    float sjt_math756;
    float sjt_math757;
    float sjt_math758;
    float sjt_math759;
    float sjt_math760;
    float sjt_math761;
    float sjt_math762;
    float sjt_math763;
    float sjt_math764;
    float sjt_math765;
    float sjt_math766;
    float sjt_math767;
    float sjt_math768;
    float sjt_math769;
    float sjt_math770;
    float sjt_math771;
    float sjt_math772;
    float sjt_math773;
    float sjt_math774;
    float sjt_math775;
    float sjt_math776;
    float sjt_math777;
    float sjt_math778;
    float sjt_math779;
    float sjt_math780;
    float sjt_math781;
    float sjt_math782;
    float sjt_math783;
    float sjt_math784;
    float sjt_math785;
    float sjt_math786;
    float sjt_math787;
    float sjt_math788;
    float sjt_math789;
    float sjt_math790;
    float sjt_math791;
    float sjt_math792;
    float sjt_math793;
    float sjt_math794;
    float sjt_math795;
    float sjt_math796;
    float sjt_math797;
    float sjt_math798;
    float sjt_math799;
    float sjt_math800;
    float sjt_math801;
    float sjt_math802;
    float sjt_math803;
    float sjt_math804;
    float sjt_math805;
    float sjt_math806;
    float sjt_math807;
    float sjt_math808;
    float sjt_math809;
    float sjt_math810;
    float sjt_math811;
    float sjt_math812;
    float sjt_math813;
    float sjt_math814;
    float sjt_math815;
    float sjt_math816;
    float sjt_math817;
    float sjt_math818;
    float sjt_math819;
    float sjt_math820;
    float sjt_math821;
    float sjt_math822;
    float sjt_math823;
    float sjt_math824;
    float sjt_math825;
    float sjt_math826;
    float sjt_math827;
    float sjt_math828;
    float sjt_math829;
    float sjt_math830;
    float sjt_math831;
    float sjt_math832;
    float sjt_math833;
    float sjt_math834;
    float sjt_math835;
    float sjt_math836;
    float sjt_math837;
    float sjt_math838;
    float sjt_math839;
    float sjt_math840;
    float sjt_math841;
    float sjt_math842;
    float sjt_math843;
    float sjt_math844;
    float sjt_math845;
    float sjt_math846;
    float sjt_math847;
    float sjt_math848;
    float sjt_math849;
    float sjt_math850;
    float sjt_math851;
    float sjt_math852;
    float sjt_math853;
    float sjt_math854;
    float sjt_math855;
    float sjt_math856;
    float sjt_math857;
    float sjt_math858;
    float sjt_math859;
    float sjt_math860;
    float sjt_math861;
    float sjt_math862;
    float sjt_math863;
    float sjt_math864;
    float sjt_math865;
    float sjt_math866;
    float sjt_math867;
    float sjt_math868;
    float sjt_math869;
    float sjt_math870;
    float sjt_math871;
    float sjt_math872;
    float sjt_math873;
    float sjt_math874;
    float sjt_math875;
    float sjt_math876;
    float sjt_math877;
    float sjt_math878;
    float sjt_math879;
    float sjt_math880;
    float sjt_math881;
    float sjt_math882;
    float sjt_math883;
    float sjt_math884;
    float sjt_math885;
    float sjt_math886;
    float sjt_math887;
    float sjt_math888;
    float sjt_math889;
    float sjt_math890;
    float sjt_math891;
    float sjt_math892;
    float sjt_math893;
    float sjt_math894;
    float sjt_math895;
    float sjt_math896;
    float sjt_math897;
    float sjt_math898;
    float sjt_math899;
    float sjt_math900;
    float sjt_math901;
    float sjt_math902;
    float sjt_math903;
    float sjt_math904;
    float sjt_math905;
    float sjt_math906;
    float sjt_math907;
    float sjt_math908;
    float sjt_math909;
    float sjt_math910;
    float sjt_math911;
    float sjt_math912;
    float sjt_math913;
    float sjt_math914;
    float sjt_math915;
    float sjt_math916;
    float sjt_math917;
    float sjt_math918;
    float sjt_math919;
    float sjt_math920;
    float sjt_math921;
    float sjt_math922;
    float sjt_math923;
    float sjt_math924;
    float sjt_math925;
    float sjt_math926;
    float sjt_math927;
    float sjt_math928;
    float sjt_math929;
    float sjt_math930;
    float sjt_math931;
    float sjt_math932;
    float sjt_math933;
    float sjt_math934;
    float sjt_math935;
    float sjt_math936;
    float sjt_math937;
    float sjt_math938;
    float sjt_math939;
    float sjt_math940;
    float sjt_math941;
    float sjt_math942;
    float sjt_math943;
    float sjt_math944;
    float sjt_math945;
    float sjt_math946;
    float sjt_math947;
    float sjt_math948;
    float sjt_math949;
    float sjt_math950;
    float sjt_math951;
    float sjt_math952;
    float sjt_math953;
    float sjt_math954;
    float sjt_math955;
    float sjt_math956;
    float sjt_math957;
    float sjt_math958;
    float sjt_math959;
    float sjt_math960;
    float sjt_math961;
    float sjt_math962;
    float sjt_math963;
    float sjt_math964;
    float sjt_math965;
    float sjt_math966;
    float sjt_math967;
    float sjt_math968;
    float sjt_math969;
    float sjt_math970;
    float sjt_math971;
    float sjt_math972;
    float sjt_math973;
    float sjt_math974;
    float sjt_math975;
    float sjt_math976;
    float sjt_math977;
    float sjt_math978;
    float sjt_math979;
    float sjt_math980;
    float sjt_math981;
    float sjt_math982;
    float sjt_math983;
    float sjt_math984;
    float sjt_math985;
    float sjt_math986;
    float sjt_math987;
    float sjt_math988;
    float sjt_math989;
    float sjt_math990;
    float sjt_math991;
    float sjt_math992;
    float sjt_math993;
    float sjt_math994;
    float sjt_math995;
    float sjt_math996;
    float sjt_math997;
    float sjt_math998;
    float sjt_math999;
    sjs_mat4* sjt_parent51;
    sjs_mat4 sjv_t;

#line 81 "lib/ui/mat4.sj"
    sjt_dot588 = _parent;
#line 83
    sjt_math765 = (sjt_dot588)->m12;
#line 81
    sjt_dot589 = _parent;
#line 83
    sjt_math766 = (sjt_dot589)->m23;
#line 83
    sjt_math763 = sjt_math765 * sjt_math766;
#line 81
    sjt_dot590 = _parent;
#line 83
    sjt_math764 = (sjt_dot590)->m31;
#line 83
    sjt_math761 = sjt_math763 * sjt_math764;
#line 81
    sjt_dot591 = _parent;
#line 83
    sjt_math769 = (sjt_dot591)->m13;
#line 81
    sjt_dot592 = _parent;
#line 83
    sjt_math770 = (sjt_dot592)->m22;
#line 83
    sjt_math767 = sjt_math769 * sjt_math770;
#line 81
    sjt_dot593 = _parent;
#line 83
    sjt_math768 = (sjt_dot593)->m31;
#line 83
    sjt_math762 = sjt_math767 * sjt_math768;
#line 83
    sjt_math759 = sjt_math761 - sjt_math762;
#line 81
    sjt_dot594 = _parent;
#line 83
    sjt_math773 = (sjt_dot594)->m13;
#line 81
    sjt_dot595 = _parent;
#line 83
    sjt_math774 = (sjt_dot595)->m21;
#line 83
    sjt_math771 = sjt_math773 * sjt_math774;
#line 81
    sjt_dot596 = _parent;
#line 83
    sjt_math772 = (sjt_dot596)->m32;
#line 83
    sjt_math760 = sjt_math771 * sjt_math772;
#line 83
    sjt_math757 = sjt_math759 + sjt_math760;
#line 81
    sjt_dot597 = _parent;
#line 83
    sjt_math777 = (sjt_dot597)->m11;
#line 81
    sjt_dot598 = _parent;
#line 83
    sjt_math778 = (sjt_dot598)->m23;
#line 83
    sjt_math775 = sjt_math777 * sjt_math778;
#line 81
    sjt_dot599 = _parent;
#line 83
    sjt_math776 = (sjt_dot599)->m32;
#line 83
    sjt_math758 = sjt_math775 * sjt_math776;
#line 83
    sjt_math755 = sjt_math757 - sjt_math758;
#line 81
    sjt_dot600 = _parent;
#line 83
    sjt_math781 = (sjt_dot600)->m12;
#line 81
    sjt_dot601 = _parent;
#line 83
    sjt_math782 = (sjt_dot601)->m21;
#line 83
    sjt_math779 = sjt_math781 * sjt_math782;
#line 81
    sjt_dot602 = _parent;
#line 83
    sjt_math780 = (sjt_dot602)->m33;
#line 83
    sjt_math756 = sjt_math779 * sjt_math780;
#line 83
    sjt_math753 = sjt_math755 - sjt_math756;
#line 81
    sjt_dot603 = _parent;
#line 83
    sjt_math785 = (sjt_dot603)->m11;
#line 81
    sjt_dot604 = _parent;
#line 83
    sjt_math786 = (sjt_dot604)->m22;
#line 83
    sjt_math783 = sjt_math785 * sjt_math786;
#line 81
    sjt_dot605 = _parent;
#line 83
    sjt_math784 = (sjt_dot605)->m33;
#line 83
    sjt_math754 = sjt_math783 * sjt_math784;
#line 83
    sjv_t.m00 = sjt_math753 + sjt_math754;
#line 81
    sjt_dot606 = _parent;
#line 84
    sjt_math799 = (sjt_dot606)->m03;
#line 81
    sjt_dot607 = _parent;
#line 84
    sjt_math800 = (sjt_dot607)->m22;
#line 84
    sjt_math797 = sjt_math799 * sjt_math800;
#line 81
    sjt_dot608 = _parent;
#line 84
    sjt_math798 = (sjt_dot608)->m31;
#line 84
    sjt_math795 = sjt_math797 * sjt_math798;
#line 81
    sjt_dot609 = _parent;
#line 84
    sjt_math803 = (sjt_dot609)->m02;
#line 81
    sjt_dot610 = _parent;
#line 84
    sjt_math804 = (sjt_dot610)->m23;
#line 84
    sjt_math801 = sjt_math803 * sjt_math804;
#line 81
    sjt_dot611 = _parent;
#line 84
    sjt_math802 = (sjt_dot611)->m31;
#line 84
    sjt_math796 = sjt_math801 * sjt_math802;
#line 84
    sjt_math793 = sjt_math795 - sjt_math796;
#line 81
    sjt_dot612 = _parent;
#line 84
    sjt_math807 = (sjt_dot612)->m03;
#line 81
    sjt_dot613 = _parent;
#line 84
    sjt_math808 = (sjt_dot613)->m21;
#line 84
    sjt_math805 = sjt_math807 * sjt_math808;
#line 81
    sjt_dot614 = _parent;
#line 84
    sjt_math806 = (sjt_dot614)->m32;
#line 84
    sjt_math794 = sjt_math805 * sjt_math806;
#line 84
    sjt_math791 = sjt_math793 - sjt_math794;
#line 81
    sjt_dot615 = _parent;
#line 84
    sjt_math811 = (sjt_dot615)->m01;
#line 81
    sjt_dot616 = _parent;
#line 84
    sjt_math812 = (sjt_dot616)->m23;
#line 84
    sjt_math809 = sjt_math811 * sjt_math812;
#line 81
    sjt_dot617 = _parent;
#line 84
    sjt_math810 = (sjt_dot617)->m32;
#line 84
    sjt_math792 = sjt_math809 * sjt_math810;
#line 84
    sjt_math789 = sjt_math791 + sjt_math792;
#line 81
    sjt_dot618 = _parent;
#line 84
    sjt_math815 = (sjt_dot618)->m02;
#line 81
    sjt_dot619 = _parent;
#line 84
    sjt_math816 = (sjt_dot619)->m21;
#line 84
    sjt_math813 = sjt_math815 * sjt_math816;
#line 81
    sjt_dot620 = _parent;
#line 84
    sjt_math814 = (sjt_dot620)->m33;
#line 84
    sjt_math790 = sjt_math813 * sjt_math814;
#line 84
    sjt_math787 = sjt_math789 + sjt_math790;
#line 81
    sjt_dot621 = _parent;
#line 84
    sjt_math819 = (sjt_dot621)->m01;
#line 81
    sjt_dot622 = _parent;
#line 84
    sjt_math820 = (sjt_dot622)->m22;
#line 84
    sjt_math817 = sjt_math819 * sjt_math820;
#line 81
    sjt_dot623 = _parent;
#line 84
    sjt_math818 = (sjt_dot623)->m33;
#line 84
    sjt_math788 = sjt_math817 * sjt_math818;
#line 84
    sjv_t.m01 = sjt_math787 - sjt_math788;
#line 81
    sjt_dot624 = _parent;
#line 85
    sjt_math833 = (sjt_dot624)->m02;
#line 81
    sjt_dot625 = _parent;
#line 85
    sjt_math834 = (sjt_dot625)->m13;
#line 85
    sjt_math831 = sjt_math833 * sjt_math834;
#line 81
    sjt_dot626 = _parent;
#line 85
    sjt_math832 = (sjt_dot626)->m31;
#line 85
    sjt_math829 = sjt_math831 * sjt_math832;
#line 81
    sjt_dot627 = _parent;
#line 85
    sjt_math837 = (sjt_dot627)->m03;
#line 81
    sjt_dot628 = _parent;
#line 85
    sjt_math838 = (sjt_dot628)->m12;
#line 85
    sjt_math835 = sjt_math837 * sjt_math838;
#line 81
    sjt_dot629 = _parent;
#line 85
    sjt_math836 = (sjt_dot629)->m31;
#line 85
    sjt_math830 = sjt_math835 * sjt_math836;
#line 85
    sjt_math827 = sjt_math829 - sjt_math830;
#line 81
    sjt_dot630 = _parent;
#line 85
    sjt_math841 = (sjt_dot630)->m03;
#line 81
    sjt_dot631 = _parent;
#line 85
    sjt_math842 = (sjt_dot631)->m11;
#line 85
    sjt_math839 = sjt_math841 * sjt_math842;
#line 81
    sjt_dot632 = _parent;
#line 85
    sjt_math840 = (sjt_dot632)->m32;
#line 85
    sjt_math828 = sjt_math839 * sjt_math840;
#line 85
    sjt_math825 = sjt_math827 + sjt_math828;
#line 81
    sjt_dot633 = _parent;
#line 85
    sjt_math845 = (sjt_dot633)->m01;
#line 81
    sjt_dot634 = _parent;
#line 85
    sjt_math846 = (sjt_dot634)->m13;
#line 85
    sjt_math843 = sjt_math845 * sjt_math846;
#line 81
    sjt_dot635 = _parent;
#line 85
    sjt_math844 = (sjt_dot635)->m32;
#line 85
    sjt_math826 = sjt_math843 * sjt_math844;
#line 85
    sjt_math823 = sjt_math825 - sjt_math826;
#line 81
    sjt_dot636 = _parent;
#line 85
    sjt_math849 = (sjt_dot636)->m02;
#line 81
    sjt_dot637 = _parent;
#line 85
    sjt_math850 = (sjt_dot637)->m11;
#line 85
    sjt_math847 = sjt_math849 * sjt_math850;
#line 81
    sjt_dot638 = _parent;
#line 85
    sjt_math848 = (sjt_dot638)->m33;
#line 85
    sjt_math824 = sjt_math847 * sjt_math848;
#line 85
    sjt_math821 = sjt_math823 - sjt_math824;
#line 81
    sjt_dot639 = _parent;
#line 85
    sjt_math853 = (sjt_dot639)->m01;
#line 81
    sjt_dot640 = _parent;
#line 85
    sjt_math854 = (sjt_dot640)->m12;
#line 85
    sjt_math851 = sjt_math853 * sjt_math854;
#line 81
    sjt_dot641 = _parent;
#line 85
    sjt_math852 = (sjt_dot641)->m33;
#line 85
    sjt_math822 = sjt_math851 * sjt_math852;
#line 85
    sjv_t.m02 = sjt_math821 + sjt_math822;
#line 81
    sjt_dot642 = _parent;
#line 86
    sjt_math867 = (sjt_dot642)->m03;
#line 81
    sjt_dot643 = _parent;
#line 86
    sjt_math868 = (sjt_dot643)->m12;
#line 86
    sjt_math865 = sjt_math867 * sjt_math868;
#line 81
    sjt_dot644 = _parent;
#line 86
    sjt_math866 = (sjt_dot644)->m21;
#line 86
    sjt_math863 = sjt_math865 * sjt_math866;
#line 81
    sjt_dot645 = _parent;
#line 86
    sjt_math871 = (sjt_dot645)->m02;
#line 81
    sjt_dot646 = _parent;
#line 86
    sjt_math872 = (sjt_dot646)->m13;
#line 86
    sjt_math869 = sjt_math871 * sjt_math872;
#line 81
    sjt_dot647 = _parent;
#line 86
    sjt_math870 = (sjt_dot647)->m21;
#line 86
    sjt_math864 = sjt_math869 * sjt_math870;
#line 86
    sjt_math861 = sjt_math863 - sjt_math864;
#line 81
    sjt_dot648 = _parent;
#line 86
    sjt_math875 = (sjt_dot648)->m03;
#line 81
    sjt_dot649 = _parent;
#line 86
    sjt_math876 = (sjt_dot649)->m11;
#line 86
    sjt_math873 = sjt_math875 * sjt_math876;
#line 81
    sjt_dot650 = _parent;
#line 86
    sjt_math874 = (sjt_dot650)->m22;
#line 86
    sjt_math862 = sjt_math873 * sjt_math874;
#line 86
    sjt_math859 = sjt_math861 - sjt_math862;
#line 81
    sjt_dot651 = _parent;
#line 86
    sjt_math879 = (sjt_dot651)->m01;
#line 81
    sjt_dot652 = _parent;
#line 86
    sjt_math880 = (sjt_dot652)->m13;
#line 86
    sjt_math877 = sjt_math879 * sjt_math880;
#line 81
    sjt_dot653 = _parent;
#line 86
    sjt_math878 = (sjt_dot653)->m22;
#line 86
    sjt_math860 = sjt_math877 * sjt_math878;
#line 86
    sjt_math857 = sjt_math859 + sjt_math860;
#line 81
    sjt_dot654 = _parent;
#line 86
    sjt_math883 = (sjt_dot654)->m02;
#line 81
    sjt_dot655 = _parent;
#line 86
    sjt_math884 = (sjt_dot655)->m11;
#line 86
    sjt_math881 = sjt_math883 * sjt_math884;
#line 81
    sjt_dot656 = _parent;
#line 86
    sjt_math882 = (sjt_dot656)->m23;
#line 86
    sjt_math858 = sjt_math881 * sjt_math882;
#line 86
    sjt_math855 = sjt_math857 + sjt_math858;
#line 81
    sjt_dot657 = _parent;
#line 86
    sjt_math887 = (sjt_dot657)->m01;
#line 81
    sjt_dot658 = _parent;
#line 86
    sjt_math888 = (sjt_dot658)->m12;
#line 86
    sjt_math885 = sjt_math887 * sjt_math888;
#line 81
    sjt_dot659 = _parent;
#line 86
    sjt_math886 = (sjt_dot659)->m23;
#line 86
    sjt_math856 = sjt_math885 * sjt_math886;
#line 86
    sjv_t.m03 = sjt_math855 - sjt_math856;
#line 81
    sjt_dot660 = _parent;
#line 87
    sjt_math901 = (sjt_dot660)->m13;
#line 81
    sjt_dot661 = _parent;
#line 87
    sjt_math902 = (sjt_dot661)->m22;
#line 87
    sjt_math899 = sjt_math901 * sjt_math902;
#line 81
    sjt_dot662 = _parent;
#line 87
    sjt_math900 = (sjt_dot662)->m30;
#line 87
    sjt_math897 = sjt_math899 * sjt_math900;
#line 81
    sjt_dot663 = _parent;
#line 87
    sjt_math905 = (sjt_dot663)->m12;
#line 81
    sjt_dot664 = _parent;
#line 87
    sjt_math906 = (sjt_dot664)->m23;
#line 87
    sjt_math903 = sjt_math905 * sjt_math906;
#line 81
    sjt_dot665 = _parent;
#line 87
    sjt_math904 = (sjt_dot665)->m30;
#line 87
    sjt_math898 = sjt_math903 * sjt_math904;
#line 87
    sjt_math895 = sjt_math897 - sjt_math898;
#line 81
    sjt_dot666 = _parent;
#line 87
    sjt_math909 = (sjt_dot666)->m13;
#line 81
    sjt_dot667 = _parent;
#line 87
    sjt_math910 = (sjt_dot667)->m20;
#line 87
    sjt_math907 = sjt_math909 * sjt_math910;
#line 81
    sjt_dot668 = _parent;
#line 87
    sjt_math908 = (sjt_dot668)->m32;
#line 87
    sjt_math896 = sjt_math907 * sjt_math908;
#line 87
    sjt_math893 = sjt_math895 - sjt_math896;
#line 81
    sjt_dot669 = _parent;
#line 87
    sjt_math913 = (sjt_dot669)->m10;
#line 81
    sjt_dot670 = _parent;
#line 87
    sjt_math914 = (sjt_dot670)->m23;
#line 87
    sjt_math911 = sjt_math913 * sjt_math914;
#line 81
    sjt_dot671 = _parent;
#line 87
    sjt_math912 = (sjt_dot671)->m32;
#line 87
    sjt_math894 = sjt_math911 * sjt_math912;
#line 87
    sjt_math891 = sjt_math893 + sjt_math894;
#line 81
    sjt_dot672 = _parent;
#line 87
    sjt_math917 = (sjt_dot672)->m12;
#line 81
    sjt_dot673 = _parent;
#line 87
    sjt_math918 = (sjt_dot673)->m20;
#line 87
    sjt_math915 = sjt_math917 * sjt_math918;
#line 81
    sjt_dot674 = _parent;
#line 87
    sjt_math916 = (sjt_dot674)->m33;
#line 87
    sjt_math892 = sjt_math915 * sjt_math916;
#line 87
    sjt_math889 = sjt_math891 + sjt_math892;
#line 81
    sjt_dot675 = _parent;
#line 87
    sjt_math921 = (sjt_dot675)->m10;
#line 81
    sjt_dot676 = _parent;
#line 87
    sjt_math922 = (sjt_dot676)->m22;
#line 87
    sjt_math919 = sjt_math921 * sjt_math922;
#line 81
    sjt_dot677 = _parent;
#line 87
    sjt_math920 = (sjt_dot677)->m33;
#line 87
    sjt_math890 = sjt_math919 * sjt_math920;
#line 87
    sjv_t.m10 = sjt_math889 - sjt_math890;
#line 81
    sjt_dot678 = _parent;
#line 88
    sjt_math935 = (sjt_dot678)->m02;
#line 81
    sjt_dot679 = _parent;
#line 88
    sjt_math936 = (sjt_dot679)->m23;
#line 88
    sjt_math933 = sjt_math935 * sjt_math936;
#line 81
    sjt_dot680 = _parent;
#line 88
    sjt_math934 = (sjt_dot680)->m30;
#line 88
    sjt_math931 = sjt_math933 * sjt_math934;
#line 81
    sjt_dot681 = _parent;
#line 88
    sjt_math939 = (sjt_dot681)->m03;
#line 81
    sjt_dot682 = _parent;
#line 88
    sjt_math940 = (sjt_dot682)->m22;
#line 88
    sjt_math937 = sjt_math939 * sjt_math940;
#line 81
    sjt_dot683 = _parent;
#line 88
    sjt_math938 = (sjt_dot683)->m30;
#line 88
    sjt_math932 = sjt_math937 * sjt_math938;
#line 88
    sjt_math929 = sjt_math931 - sjt_math932;
#line 81
    sjt_dot684 = _parent;
#line 88
    sjt_math943 = (sjt_dot684)->m03;
#line 81
    sjt_dot685 = _parent;
#line 88
    sjt_math944 = (sjt_dot685)->m20;
#line 88
    sjt_math941 = sjt_math943 * sjt_math944;
#line 81
    sjt_dot686 = _parent;
#line 88
    sjt_math942 = (sjt_dot686)->m32;
#line 88
    sjt_math930 = sjt_math941 * sjt_math942;
#line 88
    sjt_math927 = sjt_math929 + sjt_math930;
#line 81
    sjt_dot687 = _parent;
#line 88
    sjt_math947 = (sjt_dot687)->m00;
#line 81
    sjt_dot688 = _parent;
#line 88
    sjt_math948 = (sjt_dot688)->m23;
#line 88
    sjt_math945 = sjt_math947 * sjt_math948;
#line 81
    sjt_dot689 = _parent;
#line 88
    sjt_math946 = (sjt_dot689)->m32;
#line 88
    sjt_math928 = sjt_math945 * sjt_math946;
#line 88
    sjt_math925 = sjt_math927 - sjt_math928;
#line 81
    sjt_dot690 = _parent;
#line 88
    sjt_math951 = (sjt_dot690)->m02;
#line 81
    sjt_dot691 = _parent;
#line 88
    sjt_math952 = (sjt_dot691)->m20;
#line 88
    sjt_math949 = sjt_math951 * sjt_math952;
#line 81
    sjt_dot692 = _parent;
#line 88
    sjt_math950 = (sjt_dot692)->m33;
#line 88
    sjt_math926 = sjt_math949 * sjt_math950;
#line 88
    sjt_math923 = sjt_math925 - sjt_math926;
#line 81
    sjt_dot693 = _parent;
#line 88
    sjt_math955 = (sjt_dot693)->m00;
#line 81
    sjt_dot694 = _parent;
#line 88
    sjt_math956 = (sjt_dot694)->m22;
#line 88
    sjt_math953 = sjt_math955 * sjt_math956;
#line 81
    sjt_dot695 = _parent;
#line 88
    sjt_math954 = (sjt_dot695)->m33;
#line 88
    sjt_math924 = sjt_math953 * sjt_math954;
#line 88
    sjv_t.m11 = sjt_math923 + sjt_math924;
#line 81
    sjt_dot696 = _parent;
#line 89
    sjt_math969 = (sjt_dot696)->m03;
#line 81
    sjt_dot697 = _parent;
#line 89
    sjt_math970 = (sjt_dot697)->m12;
#line 89
    sjt_math967 = sjt_math969 * sjt_math970;
#line 81
    sjt_dot698 = _parent;
#line 89
    sjt_math968 = (sjt_dot698)->m30;
#line 89
    sjt_math965 = sjt_math967 * sjt_math968;
#line 81
    sjt_dot699 = _parent;
#line 89
    sjt_math973 = (sjt_dot699)->m02;
#line 81
    sjt_dot700 = _parent;
#line 89
    sjt_math974 = (sjt_dot700)->m13;
#line 89
    sjt_math971 = sjt_math973 * sjt_math974;
#line 81
    sjt_dot701 = _parent;
#line 89
    sjt_math972 = (sjt_dot701)->m30;
#line 89
    sjt_math966 = sjt_math971 * sjt_math972;
#line 89
    sjt_math963 = sjt_math965 - sjt_math966;
#line 81
    sjt_dot702 = _parent;
#line 89
    sjt_math977 = (sjt_dot702)->m03;
#line 81
    sjt_dot703 = _parent;
#line 89
    sjt_math978 = (sjt_dot703)->m10;
#line 89
    sjt_math975 = sjt_math977 * sjt_math978;
#line 81
    sjt_dot704 = _parent;
#line 89
    sjt_math976 = (sjt_dot704)->m32;
#line 89
    sjt_math964 = sjt_math975 * sjt_math976;
#line 89
    sjt_math961 = sjt_math963 - sjt_math964;
#line 81
    sjt_dot705 = _parent;
#line 89
    sjt_math981 = (sjt_dot705)->m00;
#line 81
    sjt_dot706 = _parent;
#line 89
    sjt_math982 = (sjt_dot706)->m13;
#line 89
    sjt_math979 = sjt_math981 * sjt_math982;
#line 81
    sjt_dot707 = _parent;
#line 89
    sjt_math980 = (sjt_dot707)->m32;
#line 89
    sjt_math962 = sjt_math979 * sjt_math980;
#line 89
    sjt_math959 = sjt_math961 + sjt_math962;
#line 81
    sjt_dot708 = _parent;
#line 89
    sjt_math985 = (sjt_dot708)->m02;
#line 81
    sjt_dot709 = _parent;
#line 89
    sjt_math986 = (sjt_dot709)->m10;
#line 89
    sjt_math983 = sjt_math985 * sjt_math986;
#line 81
    sjt_dot710 = _parent;
#line 89
    sjt_math984 = (sjt_dot710)->m33;
#line 89
    sjt_math960 = sjt_math983 * sjt_math984;
#line 89
    sjt_math957 = sjt_math959 + sjt_math960;
#line 81
    sjt_dot711 = _parent;
#line 89
    sjt_math989 = (sjt_dot711)->m00;
#line 81
    sjt_dot712 = _parent;
#line 89
    sjt_math990 = (sjt_dot712)->m12;
#line 89
    sjt_math987 = sjt_math989 * sjt_math990;
#line 81
    sjt_dot713 = _parent;
#line 89
    sjt_math988 = (sjt_dot713)->m33;
#line 89
    sjt_math958 = sjt_math987 * sjt_math988;
#line 89
    sjv_t.m12 = sjt_math957 - sjt_math958;
#line 81
    sjt_dot714 = _parent;
#line 90
    sjt_math1003 = (sjt_dot714)->m02;
#line 81
    sjt_dot715 = _parent;
#line 90
    sjt_math1004 = (sjt_dot715)->m13;
#line 90
    sjt_math1001 = sjt_math1003 * sjt_math1004;
#line 81
    sjt_dot716 = _parent;
#line 90
    sjt_math1002 = (sjt_dot716)->m20;
#line 90
    sjt_math999 = sjt_math1001 * sjt_math1002;
#line 81
    sjt_dot717 = _parent;
#line 90
    sjt_math1007 = (sjt_dot717)->m03;
#line 81
    sjt_dot718 = _parent;
#line 90
    sjt_math1008 = (sjt_dot718)->m12;
#line 90
    sjt_math1005 = sjt_math1007 * sjt_math1008;
#line 81
    sjt_dot719 = _parent;
#line 90
    sjt_math1006 = (sjt_dot719)->m20;
#line 90
    sjt_math1000 = sjt_math1005 * sjt_math1006;
#line 90
    sjt_math997 = sjt_math999 - sjt_math1000;
#line 81
    sjt_dot720 = _parent;
#line 90
    sjt_math1011 = (sjt_dot720)->m03;
#line 81
    sjt_dot721 = _parent;
#line 90
    sjt_math1012 = (sjt_dot721)->m10;
#line 90
    sjt_math1009 = sjt_math1011 * sjt_math1012;
#line 81
    sjt_dot722 = _parent;
#line 90
    sjt_math1010 = (sjt_dot722)->m22;
#line 90
    sjt_math998 = sjt_math1009 * sjt_math1010;
#line 90
    sjt_math995 = sjt_math997 + sjt_math998;
#line 81
    sjt_dot723 = _parent;
#line 90
    sjt_math1015 = (sjt_dot723)->m00;
#line 81
    sjt_dot724 = _parent;
#line 90
    sjt_math1016 = (sjt_dot724)->m13;
#line 90
    sjt_math1013 = sjt_math1015 * sjt_math1016;
#line 81
    sjt_dot725 = _parent;
#line 90
    sjt_math1014 = (sjt_dot725)->m22;
#line 90
    sjt_math996 = sjt_math1013 * sjt_math1014;
#line 90
    sjt_math993 = sjt_math995 - sjt_math996;
#line 81
    sjt_dot726 = _parent;
#line 90
    sjt_math1019 = (sjt_dot726)->m02;
#line 81
    sjt_dot727 = _parent;
#line 90
    sjt_math1020 = (sjt_dot727)->m10;
#line 90
    sjt_math1017 = sjt_math1019 * sjt_math1020;
#line 81
    sjt_dot728 = _parent;
#line 90
    sjt_math1018 = (sjt_dot728)->m23;
#line 90
    sjt_math994 = sjt_math1017 * sjt_math1018;
#line 90
    sjt_math991 = sjt_math993 - sjt_math994;
#line 81
    sjt_dot729 = _parent;
#line 90
    sjt_math1023 = (sjt_dot729)->m00;
#line 81
    sjt_dot730 = _parent;
#line 90
    sjt_math1024 = (sjt_dot730)->m12;
#line 90
    sjt_math1021 = sjt_math1023 * sjt_math1024;
#line 81
    sjt_dot731 = _parent;
#line 90
    sjt_math1022 = (sjt_dot731)->m23;
#line 90
    sjt_math992 = sjt_math1021 * sjt_math1022;
#line 90
    sjv_t.m13 = sjt_math991 + sjt_math992;
#line 81
    sjt_dot732 = _parent;
#line 91
    sjt_math1037 = (sjt_dot732)->m11;
#line 81
    sjt_dot733 = _parent;
#line 91
    sjt_math1038 = (sjt_dot733)->m23;
#line 91
    sjt_math1035 = sjt_math1037 * sjt_math1038;
#line 81
    sjt_dot734 = _parent;
#line 91
    sjt_math1036 = (sjt_dot734)->m30;
#line 91
    sjt_math1033 = sjt_math1035 * sjt_math1036;
#line 81
    sjt_dot735 = _parent;
#line 91
    sjt_math1041 = (sjt_dot735)->m13;
#line 81
    sjt_dot736 = _parent;
#line 91
    sjt_math1042 = (sjt_dot736)->m21;
#line 91
    sjt_math1039 = sjt_math1041 * sjt_math1042;
#line 81
    sjt_dot737 = _parent;
#line 91
    sjt_math1040 = (sjt_dot737)->m30;
#line 91
    sjt_math1034 = sjt_math1039 * sjt_math1040;
#line 91
    sjt_math1031 = sjt_math1033 - sjt_math1034;
#line 81
    sjt_dot738 = _parent;
#line 91
    sjt_math1045 = (sjt_dot738)->m13;
#line 81
    sjt_dot739 = _parent;
#line 91
    sjt_math1046 = (sjt_dot739)->m20;
#line 91
    sjt_math1043 = sjt_math1045 * sjt_math1046;
#line 81
    sjt_dot740 = _parent;
#line 91
    sjt_math1044 = (sjt_dot740)->m31;
#line 91
    sjt_math1032 = sjt_math1043 * sjt_math1044;
#line 91
    sjt_math1029 = sjt_math1031 + sjt_math1032;
#line 81
    sjt_dot741 = _parent;
#line 91
    sjt_math1049 = (sjt_dot741)->m10;
#line 81
    sjt_dot742 = _parent;
#line 91
    sjt_math1050 = (sjt_dot742)->m23;
#line 91
    sjt_math1047 = sjt_math1049 * sjt_math1050;
#line 81
    sjt_dot743 = _parent;
#line 91
    sjt_math1048 = (sjt_dot743)->m31;
#line 91
    sjt_math1030 = sjt_math1047 * sjt_math1048;
#line 91
    sjt_math1027 = sjt_math1029 - sjt_math1030;
#line 81
    sjt_dot744 = _parent;
#line 91
    sjt_math1053 = (sjt_dot744)->m11;
#line 81
    sjt_dot745 = _parent;
#line 91
    sjt_math1054 = (sjt_dot745)->m20;
#line 91
    sjt_math1051 = sjt_math1053 * sjt_math1054;
#line 81
    sjt_dot746 = _parent;
#line 91
    sjt_math1052 = (sjt_dot746)->m33;
#line 91
    sjt_math1028 = sjt_math1051 * sjt_math1052;
#line 91
    sjt_math1025 = sjt_math1027 - sjt_math1028;
#line 81
    sjt_dot747 = _parent;
#line 91
    sjt_math1057 = (sjt_dot747)->m10;
#line 81
    sjt_dot748 = _parent;
#line 91
    sjt_math1058 = (sjt_dot748)->m21;
#line 91
    sjt_math1055 = sjt_math1057 * sjt_math1058;
#line 81
    sjt_dot749 = _parent;
#line 91
    sjt_math1056 = (sjt_dot749)->m33;
#line 91
    sjt_math1026 = sjt_math1055 * sjt_math1056;
#line 91
    sjv_t.m20 = sjt_math1025 + sjt_math1026;
#line 81
    sjt_dot750 = _parent;
#line 92
    sjt_math1071 = (sjt_dot750)->m03;
#line 81
    sjt_dot751 = _parent;
#line 92
    sjt_math1072 = (sjt_dot751)->m21;
#line 92
    sjt_math1069 = sjt_math1071 * sjt_math1072;
#line 81
    sjt_dot752 = _parent;
#line 92
    sjt_math1070 = (sjt_dot752)->m30;
#line 92
    sjt_math1067 = sjt_math1069 * sjt_math1070;
#line 81
    sjt_dot753 = _parent;
#line 92
    sjt_math1075 = (sjt_dot753)->m01;
#line 81
    sjt_dot754 = _parent;
#line 92
    sjt_math1076 = (sjt_dot754)->m23;
#line 92
    sjt_math1073 = sjt_math1075 * sjt_math1076;
#line 81
    sjt_dot755 = _parent;
#line 92
    sjt_math1074 = (sjt_dot755)->m30;
#line 92
    sjt_math1068 = sjt_math1073 * sjt_math1074;
#line 92
    sjt_math1065 = sjt_math1067 - sjt_math1068;
#line 81
    sjt_dot756 = _parent;
#line 92
    sjt_math1079 = (sjt_dot756)->m03;
#line 81
    sjt_dot757 = _parent;
#line 92
    sjt_math1080 = (sjt_dot757)->m20;
#line 92
    sjt_math1077 = sjt_math1079 * sjt_math1080;
#line 81
    sjt_dot758 = _parent;
#line 92
    sjt_math1078 = (sjt_dot758)->m31;
#line 92
    sjt_math1066 = sjt_math1077 * sjt_math1078;
#line 92
    sjt_math1063 = sjt_math1065 - sjt_math1066;
#line 81
    sjt_dot759 = _parent;
#line 92
    sjt_math1083 = (sjt_dot759)->m00;
#line 81
    sjt_dot760 = _parent;
#line 92
    sjt_math1084 = (sjt_dot760)->m23;
#line 92
    sjt_math1081 = sjt_math1083 * sjt_math1084;
#line 81
    sjt_dot761 = _parent;
#line 92
    sjt_math1082 = (sjt_dot761)->m31;
#line 92
    sjt_math1064 = sjt_math1081 * sjt_math1082;
#line 92
    sjt_math1061 = sjt_math1063 + sjt_math1064;
#line 81
    sjt_dot762 = _parent;
#line 92
    sjt_math1087 = (sjt_dot762)->m01;
#line 81
    sjt_dot763 = _parent;
#line 92
    sjt_math1088 = (sjt_dot763)->m20;
#line 92
    sjt_math1085 = sjt_math1087 * sjt_math1088;
#line 81
    sjt_dot764 = _parent;
#line 92
    sjt_math1086 = (sjt_dot764)->m33;
#line 92
    sjt_math1062 = sjt_math1085 * sjt_math1086;
#line 92
    sjt_math1059 = sjt_math1061 + sjt_math1062;
#line 81
    sjt_dot765 = _parent;
#line 92
    sjt_math1091 = (sjt_dot765)->m00;
#line 81
    sjt_dot766 = _parent;
#line 92
    sjt_math1092 = (sjt_dot766)->m21;
#line 92
    sjt_math1089 = sjt_math1091 * sjt_math1092;
#line 81
    sjt_dot767 = _parent;
#line 92
    sjt_math1090 = (sjt_dot767)->m33;
#line 92
    sjt_math1060 = sjt_math1089 * sjt_math1090;
#line 92
    sjv_t.m21 = sjt_math1059 - sjt_math1060;
#line 81
    sjt_dot768 = _parent;
#line 93
    sjt_math1105 = (sjt_dot768)->m01;
#line 81
    sjt_dot769 = _parent;
#line 93
    sjt_math1106 = (sjt_dot769)->m13;
#line 93
    sjt_math1103 = sjt_math1105 * sjt_math1106;
#line 81
    sjt_dot770 = _parent;
#line 93
    sjt_math1104 = (sjt_dot770)->m30;
#line 93
    sjt_math1101 = sjt_math1103 * sjt_math1104;
#line 81
    sjt_dot771 = _parent;
#line 93
    sjt_math1109 = (sjt_dot771)->m03;
#line 81
    sjt_dot772 = _parent;
#line 93
    sjt_math1110 = (sjt_dot772)->m11;
#line 93
    sjt_math1107 = sjt_math1109 * sjt_math1110;
#line 81
    sjt_dot773 = _parent;
#line 93
    sjt_math1108 = (sjt_dot773)->m30;
#line 93
    sjt_math1102 = sjt_math1107 * sjt_math1108;
#line 93
    sjt_math1099 = sjt_math1101 - sjt_math1102;
#line 81
    sjt_dot774 = _parent;
#line 93
    sjt_math1113 = (sjt_dot774)->m03;
#line 81
    sjt_dot775 = _parent;
#line 93
    sjt_math1114 = (sjt_dot775)->m10;
#line 93
    sjt_math1111 = sjt_math1113 * sjt_math1114;
#line 81
    sjt_dot776 = _parent;
#line 93
    sjt_math1112 = (sjt_dot776)->m31;
#line 93
    sjt_math1100 = sjt_math1111 * sjt_math1112;
#line 93
    sjt_math1097 = sjt_math1099 + sjt_math1100;
#line 81
    sjt_dot777 = _parent;
#line 93
    sjt_math1117 = (sjt_dot777)->m00;
#line 81
    sjt_dot778 = _parent;
#line 93
    sjt_math1118 = (sjt_dot778)->m13;
#line 93
    sjt_math1115 = sjt_math1117 * sjt_math1118;
#line 81
    sjt_dot779 = _parent;
#line 93
    sjt_math1116 = (sjt_dot779)->m31;
#line 93
    sjt_math1098 = sjt_math1115 * sjt_math1116;
#line 93
    sjt_math1095 = sjt_math1097 - sjt_math1098;
#line 81
    sjt_dot780 = _parent;
#line 93
    sjt_math1121 = (sjt_dot780)->m01;
#line 81
    sjt_dot781 = _parent;
#line 93
    sjt_math1122 = (sjt_dot781)->m10;
#line 93
    sjt_math1119 = sjt_math1121 * sjt_math1122;
#line 81
    sjt_dot782 = _parent;
#line 93
    sjt_math1120 = (sjt_dot782)->m33;
#line 93
    sjt_math1096 = sjt_math1119 * sjt_math1120;
#line 93
    sjt_math1093 = sjt_math1095 - sjt_math1096;
#line 81
    sjt_dot783 = _parent;
#line 93
    sjt_math1125 = (sjt_dot783)->m00;
#line 81
    sjt_dot784 = _parent;
#line 93
    sjt_math1126 = (sjt_dot784)->m11;
#line 93
    sjt_math1123 = sjt_math1125 * sjt_math1126;
#line 81
    sjt_dot785 = _parent;
#line 93
    sjt_math1124 = (sjt_dot785)->m33;
#line 93
    sjt_math1094 = sjt_math1123 * sjt_math1124;
#line 93
    sjv_t.m22 = sjt_math1093 + sjt_math1094;
#line 81
    sjt_dot786 = _parent;
#line 94
    sjt_math1139 = (sjt_dot786)->m03;
#line 81
    sjt_dot787 = _parent;
#line 94
    sjt_math1140 = (sjt_dot787)->m11;
#line 94
    sjt_math1137 = sjt_math1139 * sjt_math1140;
#line 81
    sjt_dot788 = _parent;
#line 94
    sjt_math1138 = (sjt_dot788)->m20;
#line 94
    sjt_math1135 = sjt_math1137 * sjt_math1138;
#line 81
    sjt_dot789 = _parent;
#line 94
    sjt_math1143 = (sjt_dot789)->m01;
#line 81
    sjt_dot790 = _parent;
#line 94
    sjt_math1144 = (sjt_dot790)->m13;
#line 94
    sjt_math1141 = sjt_math1143 * sjt_math1144;
#line 81
    sjt_dot791 = _parent;
#line 94
    sjt_math1142 = (sjt_dot791)->m20;
#line 94
    sjt_math1136 = sjt_math1141 * sjt_math1142;
#line 94
    sjt_math1133 = sjt_math1135 - sjt_math1136;
#line 81
    sjt_dot792 = _parent;
#line 94
    sjt_math1147 = (sjt_dot792)->m03;
#line 81
    sjt_dot793 = _parent;
#line 94
    sjt_math1148 = (sjt_dot793)->m10;
#line 94
    sjt_math1145 = sjt_math1147 * sjt_math1148;
#line 81
    sjt_dot794 = _parent;
#line 94
    sjt_math1146 = (sjt_dot794)->m21;
#line 94
    sjt_math1134 = sjt_math1145 * sjt_math1146;
#line 94
    sjt_math1131 = sjt_math1133 - sjt_math1134;
#line 81
    sjt_dot795 = _parent;
#line 94
    sjt_math1151 = (sjt_dot795)->m00;
#line 81
    sjt_dot796 = _parent;
#line 94
    sjt_math1152 = (sjt_dot796)->m13;
#line 94
    sjt_math1149 = sjt_math1151 * sjt_math1152;
#line 81
    sjt_dot797 = _parent;
#line 94
    sjt_math1150 = (sjt_dot797)->m21;
#line 94
    sjt_math1132 = sjt_math1149 * sjt_math1150;
#line 94
    sjt_math1129 = sjt_math1131 + sjt_math1132;
#line 81
    sjt_dot798 = _parent;
#line 94
    sjt_math1155 = (sjt_dot798)->m01;
#line 81
    sjt_dot799 = _parent;
#line 94
    sjt_math1156 = (sjt_dot799)->m10;
#line 94
    sjt_math1153 = sjt_math1155 * sjt_math1156;
#line 81
    sjt_dot800 = _parent;
#line 94
    sjt_math1154 = (sjt_dot800)->m23;
#line 94
    sjt_math1130 = sjt_math1153 * sjt_math1154;
#line 94
    sjt_math1127 = sjt_math1129 + sjt_math1130;
#line 81
    sjt_dot801 = _parent;
#line 94
    sjt_math1159 = (sjt_dot801)->m00;
#line 81
    sjt_dot802 = _parent;
#line 94
    sjt_math1160 = (sjt_dot802)->m11;
#line 94
    sjt_math1157 = sjt_math1159 * sjt_math1160;
#line 81
    sjt_dot803 = _parent;
#line 94
    sjt_math1158 = (sjt_dot803)->m23;
#line 94
    sjt_math1128 = sjt_math1157 * sjt_math1158;
#line 94
    sjv_t.m23 = sjt_math1127 - sjt_math1128;
#line 81
    sjt_dot804 = _parent;
#line 95
    sjt_math1173 = (sjt_dot804)->m12;
#line 81
    sjt_dot805 = _parent;
#line 95
    sjt_math1174 = (sjt_dot805)->m21;
#line 95
    sjt_math1171 = sjt_math1173 * sjt_math1174;
#line 81
    sjt_dot806 = _parent;
#line 95
    sjt_math1172 = (sjt_dot806)->m30;
#line 95
    sjt_math1169 = sjt_math1171 * sjt_math1172;
#line 81
    sjt_dot807 = _parent;
#line 95
    sjt_math1177 = (sjt_dot807)->m11;
#line 81
    sjt_dot808 = _parent;
#line 95
    sjt_math1178 = (sjt_dot808)->m22;
#line 95
    sjt_math1175 = sjt_math1177 * sjt_math1178;
#line 81
    sjt_dot809 = _parent;
#line 95
    sjt_math1176 = (sjt_dot809)->m30;
#line 95
    sjt_math1170 = sjt_math1175 * sjt_math1176;
#line 95
    sjt_math1167 = sjt_math1169 - sjt_math1170;
#line 81
    sjt_dot810 = _parent;
#line 95
    sjt_math1181 = (sjt_dot810)->m12;
#line 81
    sjt_dot811 = _parent;
#line 95
    sjt_math1182 = (sjt_dot811)->m20;
#line 95
    sjt_math1179 = sjt_math1181 * sjt_math1182;
#line 81
    sjt_dot812 = _parent;
#line 95
    sjt_math1180 = (sjt_dot812)->m31;
#line 95
    sjt_math1168 = sjt_math1179 * sjt_math1180;
#line 95
    sjt_math1165 = sjt_math1167 - sjt_math1168;
#line 81
    sjt_dot813 = _parent;
#line 95
    sjt_math1185 = (sjt_dot813)->m10;
#line 81
    sjt_dot814 = _parent;
#line 95
    sjt_math1186 = (sjt_dot814)->m22;
#line 95
    sjt_math1183 = sjt_math1185 * sjt_math1186;
#line 81
    sjt_dot815 = _parent;
#line 95
    sjt_math1184 = (sjt_dot815)->m31;
#line 95
    sjt_math1166 = sjt_math1183 * sjt_math1184;
#line 95
    sjt_math1163 = sjt_math1165 + sjt_math1166;
#line 81
    sjt_dot816 = _parent;
#line 95
    sjt_math1189 = (sjt_dot816)->m11;
#line 81
    sjt_dot817 = _parent;
#line 95
    sjt_math1190 = (sjt_dot817)->m20;
#line 95
    sjt_math1187 = sjt_math1189 * sjt_math1190;
#line 81
    sjt_dot818 = _parent;
#line 95
    sjt_math1188 = (sjt_dot818)->m32;
#line 95
    sjt_math1164 = sjt_math1187 * sjt_math1188;
#line 95
    sjt_math1161 = sjt_math1163 + sjt_math1164;
#line 81
    sjt_dot819 = _parent;
#line 95
    sjt_math1193 = (sjt_dot819)->m10;
#line 81
    sjt_dot820 = _parent;
#line 95
    sjt_math1194 = (sjt_dot820)->m21;
#line 95
    sjt_math1191 = sjt_math1193 * sjt_math1194;
#line 81
    sjt_dot821 = _parent;
#line 95
    sjt_math1192 = (sjt_dot821)->m32;
#line 95
    sjt_math1162 = sjt_math1191 * sjt_math1192;
#line 95
    sjv_t.m30 = sjt_math1161 - sjt_math1162;
#line 81
    sjt_dot822 = _parent;
#line 96
    sjt_math1207 = (sjt_dot822)->m01;
#line 81
    sjt_dot823 = _parent;
#line 96
    sjt_math1208 = (sjt_dot823)->m22;
#line 96
    sjt_math1205 = sjt_math1207 * sjt_math1208;
#line 81
    sjt_dot824 = _parent;
#line 96
    sjt_math1206 = (sjt_dot824)->m30;
#line 96
    sjt_math1203 = sjt_math1205 * sjt_math1206;
#line 81
    sjt_dot825 = _parent;
#line 96
    sjt_math1211 = (sjt_dot825)->m02;
#line 81
    sjt_dot826 = _parent;
#line 96
    sjt_math1212 = (sjt_dot826)->m21;
#line 96
    sjt_math1209 = sjt_math1211 * sjt_math1212;
#line 81
    sjt_dot827 = _parent;
#line 96
    sjt_math1210 = (sjt_dot827)->m30;
#line 96
    sjt_math1204 = sjt_math1209 * sjt_math1210;
#line 96
    sjt_math1201 = sjt_math1203 - sjt_math1204;
#line 81
    sjt_dot828 = _parent;
#line 96
    sjt_math1215 = (sjt_dot828)->m02;
#line 81
    sjt_dot829 = _parent;
#line 96
    sjt_math1216 = (sjt_dot829)->m20;
#line 96
    sjt_math1213 = sjt_math1215 * sjt_math1216;
#line 81
    sjt_dot830 = _parent;
#line 96
    sjt_math1214 = (sjt_dot830)->m31;
#line 96
    sjt_math1202 = sjt_math1213 * sjt_math1214;
#line 96
    sjt_math1199 = sjt_math1201 + sjt_math1202;
#line 81
    sjt_dot831 = _parent;
#line 96
    sjt_math1219 = (sjt_dot831)->m00;
#line 81
    sjt_dot832 = _parent;
#line 96
    sjt_math1220 = (sjt_dot832)->m22;
#line 96
    sjt_math1217 = sjt_math1219 * sjt_math1220;
#line 81
    sjt_dot833 = _parent;
#line 96
    sjt_math1218 = (sjt_dot833)->m31;
#line 96
    sjt_math1200 = sjt_math1217 * sjt_math1218;
#line 96
    sjt_math1197 = sjt_math1199 - sjt_math1200;
#line 81
    sjt_dot834 = _parent;
#line 96
    sjt_math1223 = (sjt_dot834)->m01;
#line 81
    sjt_dot835 = _parent;
#line 96
    sjt_math1224 = (sjt_dot835)->m20;
#line 96
    sjt_math1221 = sjt_math1223 * sjt_math1224;
#line 81
    sjt_dot836 = _parent;
#line 96
    sjt_math1222 = (sjt_dot836)->m32;
#line 96
    sjt_math1198 = sjt_math1221 * sjt_math1222;
#line 96
    sjt_math1195 = sjt_math1197 - sjt_math1198;
#line 81
    sjt_dot837 = _parent;
#line 96
    sjt_math1227 = (sjt_dot837)->m00;
#line 81
    sjt_dot838 = _parent;
#line 96
    sjt_math1228 = (sjt_dot838)->m21;
#line 96
    sjt_math1225 = sjt_math1227 * sjt_math1228;
#line 81
    sjt_dot839 = _parent;
#line 96
    sjt_math1226 = (sjt_dot839)->m32;
#line 96
    sjt_math1196 = sjt_math1225 * sjt_math1226;
#line 96
    sjv_t.m31 = sjt_math1195 + sjt_math1196;
#line 81
    sjt_dot840 = _parent;
#line 97
    sjt_math1241 = (sjt_dot840)->m02;
#line 81
    sjt_dot841 = _parent;
#line 97
    sjt_math1242 = (sjt_dot841)->m11;
#line 97
    sjt_math1239 = sjt_math1241 * sjt_math1242;
#line 81
    sjt_dot842 = _parent;
#line 97
    sjt_math1240 = (sjt_dot842)->m30;
#line 97
    sjt_math1237 = sjt_math1239 * sjt_math1240;
#line 81
    sjt_dot843 = _parent;
#line 97
    sjt_math1245 = (sjt_dot843)->m01;
#line 81
    sjt_dot844 = _parent;
#line 97
    sjt_math1246 = (sjt_dot844)->m12;
#line 97
    sjt_math1243 = sjt_math1245 * sjt_math1246;
#line 81
    sjt_dot845 = _parent;
#line 97
    sjt_math1244 = (sjt_dot845)->m30;
#line 97
    sjt_math1238 = sjt_math1243 * sjt_math1244;
#line 97
    sjt_math1235 = sjt_math1237 - sjt_math1238;
#line 81
    sjt_dot846 = _parent;
#line 97
    sjt_math1249 = (sjt_dot846)->m02;
#line 81
    sjt_dot847 = _parent;
#line 97
    sjt_math1250 = (sjt_dot847)->m10;
#line 97
    sjt_math1247 = sjt_math1249 * sjt_math1250;
#line 81
    sjt_dot848 = _parent;
#line 97
    sjt_math1248 = (sjt_dot848)->m31;
#line 97
    sjt_math1236 = sjt_math1247 * sjt_math1248;
#line 97
    sjt_math1233 = sjt_math1235 - sjt_math1236;
#line 81
    sjt_dot849 = _parent;
#line 97
    sjt_math1253 = (sjt_dot849)->m00;
#line 81
    sjt_dot850 = _parent;
#line 97
    sjt_math1254 = (sjt_dot850)->m12;
#line 97
    sjt_math1251 = sjt_math1253 * sjt_math1254;
#line 81
    sjt_dot851 = _parent;
#line 97
    sjt_math1252 = (sjt_dot851)->m31;
#line 97
    sjt_math1234 = sjt_math1251 * sjt_math1252;
#line 97
    sjt_math1231 = sjt_math1233 + sjt_math1234;
#line 81
    sjt_dot852 = _parent;
#line 97
    sjt_math1257 = (sjt_dot852)->m01;
#line 81
    sjt_dot853 = _parent;
#line 97
    sjt_math1258 = (sjt_dot853)->m10;
#line 97
    sjt_math1255 = sjt_math1257 * sjt_math1258;
#line 81
    sjt_dot854 = _parent;
#line 97
    sjt_math1256 = (sjt_dot854)->m32;
#line 97
    sjt_math1232 = sjt_math1255 * sjt_math1256;
#line 97
    sjt_math1229 = sjt_math1231 + sjt_math1232;
#line 81
    sjt_dot855 = _parent;
#line 97
    sjt_math1261 = (sjt_dot855)->m00;
#line 81
    sjt_dot856 = _parent;
#line 97
    sjt_math1262 = (sjt_dot856)->m11;
#line 97
    sjt_math1259 = sjt_math1261 * sjt_math1262;
#line 81
    sjt_dot857 = _parent;
#line 97
    sjt_math1260 = (sjt_dot857)->m32;
#line 97
    sjt_math1230 = sjt_math1259 * sjt_math1260;
#line 97
    sjv_t.m32 = sjt_math1229 - sjt_math1230;
#line 81
    sjt_dot858 = _parent;
#line 98
    sjt_math1275 = (sjt_dot858)->m01;
#line 81
    sjt_dot859 = _parent;
#line 98
    sjt_math1276 = (sjt_dot859)->m12;
#line 98
    sjt_math1273 = sjt_math1275 * sjt_math1276;
#line 81
    sjt_dot860 = _parent;
#line 98
    sjt_math1274 = (sjt_dot860)->m20;
#line 98
    sjt_math1271 = sjt_math1273 * sjt_math1274;
#line 81
    sjt_dot861 = _parent;
#line 98
    sjt_math1279 = (sjt_dot861)->m02;
#line 81
    sjt_dot862 = _parent;
#line 98
    sjt_math1280 = (sjt_dot862)->m11;
#line 98
    sjt_math1277 = sjt_math1279 * sjt_math1280;
#line 81
    sjt_dot863 = _parent;
#line 98
    sjt_math1278 = (sjt_dot863)->m20;
#line 98
    sjt_math1272 = sjt_math1277 * sjt_math1278;
#line 98
    sjt_math1269 = sjt_math1271 - sjt_math1272;
#line 81
    sjt_dot864 = _parent;
#line 98
    sjt_math1283 = (sjt_dot864)->m02;
#line 81
    sjt_dot865 = _parent;
#line 98
    sjt_math1284 = (sjt_dot865)->m10;
#line 98
    sjt_math1281 = sjt_math1283 * sjt_math1284;
#line 81
    sjt_dot866 = _parent;
#line 98
    sjt_math1282 = (sjt_dot866)->m21;
#line 98
    sjt_math1270 = sjt_math1281 * sjt_math1282;
#line 98
    sjt_math1267 = sjt_math1269 + sjt_math1270;
#line 81
    sjt_dot867 = _parent;
#line 98
    sjt_math1287 = (sjt_dot867)->m00;
#line 81
    sjt_dot868 = _parent;
#line 98
    sjt_math1288 = (sjt_dot868)->m12;
#line 98
    sjt_math1285 = sjt_math1287 * sjt_math1288;
#line 81
    sjt_dot869 = _parent;
#line 98
    sjt_math1286 = (sjt_dot869)->m21;
#line 98
    sjt_math1268 = sjt_math1285 * sjt_math1286;
#line 98
    sjt_math1265 = sjt_math1267 - sjt_math1268;
#line 81
    sjt_dot870 = _parent;
#line 98
    sjt_math1291 = (sjt_dot870)->m01;
#line 81
    sjt_dot871 = _parent;
#line 98
    sjt_math1292 = (sjt_dot871)->m10;
#line 98
    sjt_math1289 = sjt_math1291 * sjt_math1292;
#line 81
    sjt_dot872 = _parent;
#line 98
    sjt_math1290 = (sjt_dot872)->m22;
#line 98
    sjt_math1266 = sjt_math1289 * sjt_math1290;
#line 98
    sjt_math1263 = sjt_math1265 - sjt_math1266;
#line 81
    sjt_dot873 = _parent;
#line 98
    sjt_math1295 = (sjt_dot873)->m00;
#line 81
    sjt_dot874 = _parent;
#line 98
    sjt_math1296 = (sjt_dot874)->m11;
#line 98
    sjt_math1293 = sjt_math1295 * sjt_math1296;
#line 81
    sjt_dot875 = _parent;
#line 98
    sjt_math1294 = (sjt_dot875)->m22;
#line 98
    sjt_math1264 = sjt_math1293 * sjt_math1294;
#line 98
    sjv_t.m33 = sjt_math1263 + sjt_math1264;
#line 98
    sjf_mat4(&sjv_t);
#line 40
    sjt_parent51 = &sjv_t;
#line 101
    sjt_math1361 = 1.0f;
#line 101
    sjf_mat4_determinant(_parent, &sjt_math1362);
#line 101
    sjt_functionParam112 = sjt_math1361 / sjt_math1362;
#line 101
    sjf_mat4_multiply_f32(sjt_parent51, sjt_functionParam112, _return);

    sjf_mat4_destroy(&sjv_t);
}

void sjf_mat4_invert_heap(sjs_mat4* _parent, sjs_mat4_heap** _return) {
    sjs_mat4* sjt_dot1004;
    sjs_mat4* sjt_dot1005;
    sjs_mat4* sjt_dot1006;
    sjs_mat4* sjt_dot1007;
    sjs_mat4* sjt_dot1008;
    sjs_mat4* sjt_dot1009;
    sjs_mat4* sjt_dot1010;
    sjs_mat4* sjt_dot1011;
    sjs_mat4* sjt_dot1012;
    sjs_mat4* sjt_dot1013;
    sjs_mat4* sjt_dot1014;
    sjs_mat4* sjt_dot1015;
    sjs_mat4* sjt_dot1016;
    sjs_mat4* sjt_dot1017;
    sjs_mat4* sjt_dot1018;
    sjs_mat4* sjt_dot1019;
    sjs_mat4* sjt_dot1020;
    sjs_mat4* sjt_dot1021;
    sjs_mat4* sjt_dot1022;
    sjs_mat4* sjt_dot1023;
    sjs_mat4* sjt_dot1024;
    sjs_mat4* sjt_dot1025;
    sjs_mat4* sjt_dot1026;
    sjs_mat4* sjt_dot1027;
    sjs_mat4* sjt_dot1028;
    sjs_mat4* sjt_dot1029;
    sjs_mat4* sjt_dot1030;
    sjs_mat4* sjt_dot1031;
    sjs_mat4* sjt_dot1032;
    sjs_mat4* sjt_dot1033;
    sjs_mat4* sjt_dot1034;
    sjs_mat4* sjt_dot1035;
    sjs_mat4* sjt_dot1036;
    sjs_mat4* sjt_dot1037;
    sjs_mat4* sjt_dot1038;
    sjs_mat4* sjt_dot1039;
    sjs_mat4* sjt_dot1040;
    sjs_mat4* sjt_dot1041;
    sjs_mat4* sjt_dot1042;
    sjs_mat4* sjt_dot1043;
    sjs_mat4* sjt_dot1044;
    sjs_mat4* sjt_dot1045;
    sjs_mat4* sjt_dot1046;
    sjs_mat4* sjt_dot1047;
    sjs_mat4* sjt_dot1048;
    sjs_mat4* sjt_dot1049;
    sjs_mat4* sjt_dot1050;
    sjs_mat4* sjt_dot1051;
    sjs_mat4* sjt_dot1052;
    sjs_mat4* sjt_dot1053;
    sjs_mat4* sjt_dot1054;
    sjs_mat4* sjt_dot1055;
    sjs_mat4* sjt_dot1056;
    sjs_mat4* sjt_dot1057;
    sjs_mat4* sjt_dot1058;
    sjs_mat4* sjt_dot1059;
    sjs_mat4* sjt_dot1060;
    sjs_mat4* sjt_dot1061;
    sjs_mat4* sjt_dot1062;
    sjs_mat4* sjt_dot1063;
    sjs_mat4* sjt_dot1064;
    sjs_mat4* sjt_dot1065;
    sjs_mat4* sjt_dot1066;
    sjs_mat4* sjt_dot1067;
    sjs_mat4* sjt_dot1068;
    sjs_mat4* sjt_dot1069;
    sjs_mat4* sjt_dot1070;
    sjs_mat4* sjt_dot1071;
    sjs_mat4* sjt_dot1072;
    sjs_mat4* sjt_dot1073;
    sjs_mat4* sjt_dot1074;
    sjs_mat4* sjt_dot1075;
    sjs_mat4* sjt_dot1076;
    sjs_mat4* sjt_dot1077;
    sjs_mat4* sjt_dot1078;
    sjs_mat4* sjt_dot1079;
    sjs_mat4* sjt_dot1080;
    sjs_mat4* sjt_dot1081;
    sjs_mat4* sjt_dot1082;
    sjs_mat4* sjt_dot1083;
    sjs_mat4* sjt_dot1084;
    sjs_mat4* sjt_dot1085;
    sjs_mat4* sjt_dot1086;
    sjs_mat4* sjt_dot1087;
    sjs_mat4* sjt_dot1088;
    sjs_mat4* sjt_dot1089;
    sjs_mat4* sjt_dot1090;
    sjs_mat4* sjt_dot1091;
    sjs_mat4* sjt_dot1092;
    sjs_mat4* sjt_dot1093;
    sjs_mat4* sjt_dot1094;
    sjs_mat4* sjt_dot1095;
    sjs_mat4* sjt_dot1096;
    sjs_mat4* sjt_dot1097;
    sjs_mat4* sjt_dot1098;
    sjs_mat4* sjt_dot1099;
    sjs_mat4* sjt_dot1100;
    sjs_mat4* sjt_dot1101;
    sjs_mat4* sjt_dot1102;
    sjs_mat4* sjt_dot1103;
    sjs_mat4* sjt_dot1104;
    sjs_mat4* sjt_dot1105;
    sjs_mat4* sjt_dot1106;
    sjs_mat4* sjt_dot1107;
    sjs_mat4* sjt_dot1108;
    sjs_mat4* sjt_dot1109;
    sjs_mat4* sjt_dot1110;
    sjs_mat4* sjt_dot1111;
    sjs_mat4* sjt_dot1112;
    sjs_mat4* sjt_dot1113;
    sjs_mat4* sjt_dot1114;
    sjs_mat4* sjt_dot1115;
    sjs_mat4* sjt_dot1116;
    sjs_mat4* sjt_dot1117;
    sjs_mat4* sjt_dot1118;
    sjs_mat4* sjt_dot1119;
    sjs_mat4* sjt_dot1120;
    sjs_mat4* sjt_dot1121;
    sjs_mat4* sjt_dot1122;
    sjs_mat4* sjt_dot1123;
    sjs_mat4* sjt_dot1124;
    sjs_mat4* sjt_dot1125;
    sjs_mat4* sjt_dot1126;
    sjs_mat4* sjt_dot1127;
    sjs_mat4* sjt_dot1128;
    sjs_mat4* sjt_dot1129;
    sjs_mat4* sjt_dot1130;
    sjs_mat4* sjt_dot1131;
    sjs_mat4* sjt_dot1132;
    sjs_mat4* sjt_dot1133;
    sjs_mat4* sjt_dot1134;
    sjs_mat4* sjt_dot1135;
    sjs_mat4* sjt_dot1136;
    sjs_mat4* sjt_dot1137;
    sjs_mat4* sjt_dot1138;
    sjs_mat4* sjt_dot1139;
    sjs_mat4* sjt_dot1140;
    sjs_mat4* sjt_dot1141;
    sjs_mat4* sjt_dot1142;
    sjs_mat4* sjt_dot1143;
    sjs_mat4* sjt_dot1144;
    sjs_mat4* sjt_dot1145;
    sjs_mat4* sjt_dot1146;
    sjs_mat4* sjt_dot1147;
    sjs_mat4* sjt_dot1148;
    sjs_mat4* sjt_dot1149;
    sjs_mat4* sjt_dot1150;
    sjs_mat4* sjt_dot1151;
    sjs_mat4* sjt_dot1152;
    sjs_mat4* sjt_dot1153;
    sjs_mat4* sjt_dot1154;
    sjs_mat4* sjt_dot1155;
    sjs_mat4* sjt_dot1156;
    sjs_mat4* sjt_dot1157;
    sjs_mat4* sjt_dot1158;
    sjs_mat4* sjt_dot1159;
    sjs_mat4* sjt_dot1160;
    sjs_mat4* sjt_dot1161;
    sjs_mat4* sjt_dot1162;
    sjs_mat4* sjt_dot1163;
    sjs_mat4* sjt_dot1164;
    sjs_mat4* sjt_dot1165;
    sjs_mat4* sjt_dot1166;
    sjs_mat4* sjt_dot1167;
    sjs_mat4* sjt_dot1168;
    sjs_mat4* sjt_dot1169;
    sjs_mat4* sjt_dot1170;
    sjs_mat4* sjt_dot1171;
    sjs_mat4* sjt_dot1172;
    sjs_mat4* sjt_dot1173;
    sjs_mat4* sjt_dot1174;
    sjs_mat4* sjt_dot1175;
    sjs_mat4* sjt_dot1176;
    sjs_mat4* sjt_dot1177;
    sjs_mat4* sjt_dot1178;
    sjs_mat4* sjt_dot1179;
    sjs_mat4* sjt_dot1180;
    sjs_mat4* sjt_dot1181;
    sjs_mat4* sjt_dot1182;
    sjs_mat4* sjt_dot1183;
    sjs_mat4* sjt_dot1184;
    sjs_mat4* sjt_dot1185;
    sjs_mat4* sjt_dot1186;
    sjs_mat4* sjt_dot1187;
    sjs_mat4* sjt_dot1188;
    sjs_mat4* sjt_dot1189;
    sjs_mat4* sjt_dot1190;
    sjs_mat4* sjt_dot1191;
    sjs_mat4* sjt_dot1192;
    sjs_mat4* sjt_dot1193;
    sjs_mat4* sjt_dot1194;
    sjs_mat4* sjt_dot1195;
    sjs_mat4* sjt_dot1196;
    sjs_mat4* sjt_dot1197;
    sjs_mat4* sjt_dot1198;
    sjs_mat4* sjt_dot1199;
    sjs_mat4* sjt_dot1200;
    sjs_mat4* sjt_dot1201;
    sjs_mat4* sjt_dot1202;
    sjs_mat4* sjt_dot1203;
    sjs_mat4* sjt_dot1204;
    sjs_mat4* sjt_dot1205;
    sjs_mat4* sjt_dot1206;
    sjs_mat4* sjt_dot1207;
    sjs_mat4* sjt_dot1208;
    sjs_mat4* sjt_dot1209;
    sjs_mat4* sjt_dot1210;
    sjs_mat4* sjt_dot1211;
    sjs_mat4* sjt_dot1212;
    sjs_mat4* sjt_dot1213;
    sjs_mat4* sjt_dot1214;
    sjs_mat4* sjt_dot1215;
    sjs_mat4* sjt_dot1216;
    sjs_mat4* sjt_dot1217;
    sjs_mat4* sjt_dot1218;
    sjs_mat4* sjt_dot1219;
    sjs_mat4* sjt_dot1220;
    sjs_mat4* sjt_dot1221;
    sjs_mat4* sjt_dot1222;
    sjs_mat4* sjt_dot1223;
    sjs_mat4* sjt_dot1224;
    sjs_mat4* sjt_dot1225;
    sjs_mat4* sjt_dot1226;
    sjs_mat4* sjt_dot1227;
    sjs_mat4* sjt_dot1228;
    sjs_mat4* sjt_dot1229;
    sjs_mat4* sjt_dot1230;
    sjs_mat4* sjt_dot1231;
    sjs_mat4* sjt_dot1232;
    sjs_mat4* sjt_dot1233;
    sjs_mat4* sjt_dot1234;
    sjs_mat4* sjt_dot1235;
    sjs_mat4* sjt_dot1236;
    sjs_mat4* sjt_dot1237;
    sjs_mat4* sjt_dot1238;
    sjs_mat4* sjt_dot1239;
    sjs_mat4* sjt_dot1240;
    sjs_mat4* sjt_dot1241;
    sjs_mat4* sjt_dot1242;
    sjs_mat4* sjt_dot1243;
    sjs_mat4* sjt_dot1244;
    sjs_mat4* sjt_dot1245;
    sjs_mat4* sjt_dot1246;
    sjs_mat4* sjt_dot1247;
    sjs_mat4* sjt_dot1248;
    sjs_mat4* sjt_dot1249;
    sjs_mat4* sjt_dot1250;
    sjs_mat4* sjt_dot1251;
    sjs_mat4* sjt_dot1252;
    sjs_mat4* sjt_dot1253;
    sjs_mat4* sjt_dot1254;
    sjs_mat4* sjt_dot1255;
    sjs_mat4* sjt_dot1256;
    sjs_mat4* sjt_dot1257;
    sjs_mat4* sjt_dot1258;
    sjs_mat4* sjt_dot1259;
    sjs_mat4* sjt_dot1260;
    sjs_mat4* sjt_dot1261;
    sjs_mat4* sjt_dot1262;
    sjs_mat4* sjt_dot1263;
    sjs_mat4* sjt_dot1264;
    sjs_mat4* sjt_dot1265;
    sjs_mat4* sjt_dot1266;
    sjs_mat4* sjt_dot1267;
    sjs_mat4* sjt_dot1268;
    sjs_mat4* sjt_dot1269;
    sjs_mat4* sjt_dot1270;
    sjs_mat4* sjt_dot1271;
    sjs_mat4* sjt_dot1272;
    sjs_mat4* sjt_dot1273;
    sjs_mat4* sjt_dot1274;
    sjs_mat4* sjt_dot1275;
    sjs_mat4* sjt_dot1276;
    sjs_mat4* sjt_dot1277;
    sjs_mat4* sjt_dot1278;
    sjs_mat4* sjt_dot1279;
    sjs_mat4* sjt_dot1280;
    sjs_mat4* sjt_dot1281;
    sjs_mat4* sjt_dot1282;
    sjs_mat4* sjt_dot1283;
    sjs_mat4* sjt_dot1284;
    sjs_mat4* sjt_dot1285;
    sjs_mat4* sjt_dot1286;
    sjs_mat4* sjt_dot1287;
    sjs_mat4* sjt_dot1288;
    sjs_mat4* sjt_dot1289;
    sjs_mat4* sjt_dot1290;
    sjs_mat4* sjt_dot1291;
    float sjt_functionParam113;
    float sjt_math1553;
    float sjt_math1554;
    float sjt_math1555;
    float sjt_math1556;
    float sjt_math1557;
    float sjt_math1558;
    float sjt_math1559;
    float sjt_math1560;
    float sjt_math1561;
    float sjt_math1562;
    float sjt_math1563;
    float sjt_math1564;
    float sjt_math1565;
    float sjt_math1566;
    float sjt_math1567;
    float sjt_math1568;
    float sjt_math1569;
    float sjt_math1570;
    float sjt_math1571;
    float sjt_math1572;
    float sjt_math1573;
    float sjt_math1574;
    float sjt_math1575;
    float sjt_math1576;
    float sjt_math1577;
    float sjt_math1578;
    float sjt_math1579;
    float sjt_math1580;
    float sjt_math1581;
    float sjt_math1582;
    float sjt_math1583;
    float sjt_math1584;
    float sjt_math1585;
    float sjt_math1586;
    float sjt_math1587;
    float sjt_math1588;
    float sjt_math1589;
    float sjt_math1590;
    float sjt_math1591;
    float sjt_math1592;
    float sjt_math1593;
    float sjt_math1594;
    float sjt_math1595;
    float sjt_math1596;
    float sjt_math1597;
    float sjt_math1598;
    float sjt_math1599;
    float sjt_math1600;
    float sjt_math1601;
    float sjt_math1602;
    float sjt_math1603;
    float sjt_math1604;
    float sjt_math1605;
    float sjt_math1606;
    float sjt_math1607;
    float sjt_math1608;
    float sjt_math1609;
    float sjt_math1610;
    float sjt_math1611;
    float sjt_math1612;
    float sjt_math1613;
    float sjt_math1614;
    float sjt_math1615;
    float sjt_math1616;
    float sjt_math1617;
    float sjt_math1618;
    float sjt_math1619;
    float sjt_math1620;
    float sjt_math1621;
    float sjt_math1622;
    float sjt_math1623;
    float sjt_math1624;
    float sjt_math1625;
    float sjt_math1626;
    float sjt_math1627;
    float sjt_math1628;
    float sjt_math1629;
    float sjt_math1630;
    float sjt_math1631;
    float sjt_math1632;
    float sjt_math1633;
    float sjt_math1634;
    float sjt_math1635;
    float sjt_math1636;
    float sjt_math1637;
    float sjt_math1638;
    float sjt_math1639;
    float sjt_math1640;
    float sjt_math1641;
    float sjt_math1642;
    float sjt_math1643;
    float sjt_math1644;
    float sjt_math1645;
    float sjt_math1646;
    float sjt_math1647;
    float sjt_math1648;
    float sjt_math1649;
    float sjt_math1650;
    float sjt_math1651;
    float sjt_math1652;
    float sjt_math1653;
    float sjt_math1654;
    float sjt_math1655;
    float sjt_math1656;
    float sjt_math1657;
    float sjt_math1658;
    float sjt_math1659;
    float sjt_math1660;
    float sjt_math1661;
    float sjt_math1662;
    float sjt_math1663;
    float sjt_math1664;
    float sjt_math1665;
    float sjt_math1666;
    float sjt_math1667;
    float sjt_math1668;
    float sjt_math1669;
    float sjt_math1670;
    float sjt_math1671;
    float sjt_math1672;
    float sjt_math1673;
    float sjt_math1674;
    float sjt_math1675;
    float sjt_math1676;
    float sjt_math1677;
    float sjt_math1678;
    float sjt_math1679;
    float sjt_math1680;
    float sjt_math1681;
    float sjt_math1682;
    float sjt_math1683;
    float sjt_math1684;
    float sjt_math1685;
    float sjt_math1686;
    float sjt_math1687;
    float sjt_math1688;
    float sjt_math1689;
    float sjt_math1690;
    float sjt_math1691;
    float sjt_math1692;
    float sjt_math1693;
    float sjt_math1694;
    float sjt_math1695;
    float sjt_math1696;
    float sjt_math1697;
    float sjt_math1698;
    float sjt_math1699;
    float sjt_math1700;
    float sjt_math1701;
    float sjt_math1702;
    float sjt_math1703;
    float sjt_math1704;
    float sjt_math1705;
    float sjt_math1706;
    float sjt_math1707;
    float sjt_math1708;
    float sjt_math1709;
    float sjt_math1710;
    float sjt_math1711;
    float sjt_math1712;
    float sjt_math1713;
    float sjt_math1714;
    float sjt_math1715;
    float sjt_math1716;
    float sjt_math1717;
    float sjt_math1718;
    float sjt_math1719;
    float sjt_math1720;
    float sjt_math1721;
    float sjt_math1722;
    float sjt_math1723;
    float sjt_math1724;
    float sjt_math1725;
    float sjt_math1726;
    float sjt_math1727;
    float sjt_math1728;
    float sjt_math1729;
    float sjt_math1730;
    float sjt_math1731;
    float sjt_math1732;
    float sjt_math1733;
    float sjt_math1734;
    float sjt_math1735;
    float sjt_math1736;
    float sjt_math1737;
    float sjt_math1738;
    float sjt_math1739;
    float sjt_math1740;
    float sjt_math1741;
    float sjt_math1742;
    float sjt_math1743;
    float sjt_math1744;
    float sjt_math1745;
    float sjt_math1746;
    float sjt_math1747;
    float sjt_math1748;
    float sjt_math1749;
    float sjt_math1750;
    float sjt_math1751;
    float sjt_math1752;
    float sjt_math1753;
    float sjt_math1754;
    float sjt_math1755;
    float sjt_math1756;
    float sjt_math1757;
    float sjt_math1758;
    float sjt_math1759;
    float sjt_math1760;
    float sjt_math1761;
    float sjt_math1762;
    float sjt_math1763;
    float sjt_math1764;
    float sjt_math1765;
    float sjt_math1766;
    float sjt_math1767;
    float sjt_math1768;
    float sjt_math1769;
    float sjt_math1770;
    float sjt_math1771;
    float sjt_math1772;
    float sjt_math1773;
    float sjt_math1774;
    float sjt_math1775;
    float sjt_math1776;
    float sjt_math1777;
    float sjt_math1778;
    float sjt_math1779;
    float sjt_math1780;
    float sjt_math1781;
    float sjt_math1782;
    float sjt_math1783;
    float sjt_math1784;
    float sjt_math1785;
    float sjt_math1786;
    float sjt_math1787;
    float sjt_math1788;
    float sjt_math1789;
    float sjt_math1790;
    float sjt_math1791;
    float sjt_math1792;
    float sjt_math1793;
    float sjt_math1794;
    float sjt_math1795;
    float sjt_math1796;
    float sjt_math1797;
    float sjt_math1798;
    float sjt_math1799;
    float sjt_math1800;
    float sjt_math1801;
    float sjt_math1802;
    float sjt_math1803;
    float sjt_math1804;
    float sjt_math1805;
    float sjt_math1806;
    float sjt_math1807;
    float sjt_math1808;
    float sjt_math1809;
    float sjt_math1810;
    float sjt_math1811;
    float sjt_math1812;
    float sjt_math1813;
    float sjt_math1814;
    float sjt_math1815;
    float sjt_math1816;
    float sjt_math1817;
    float sjt_math1818;
    float sjt_math1819;
    float sjt_math1820;
    float sjt_math1821;
    float sjt_math1822;
    float sjt_math1823;
    float sjt_math1824;
    float sjt_math1825;
    float sjt_math1826;
    float sjt_math1827;
    float sjt_math1828;
    float sjt_math1829;
    float sjt_math1830;
    float sjt_math1831;
    float sjt_math1832;
    float sjt_math1833;
    float sjt_math1834;
    float sjt_math1835;
    float sjt_math1836;
    float sjt_math1837;
    float sjt_math1838;
    float sjt_math1839;
    float sjt_math1840;
    float sjt_math1841;
    float sjt_math1842;
    float sjt_math1843;
    float sjt_math1844;
    float sjt_math1845;
    float sjt_math1846;
    float sjt_math1847;
    float sjt_math1848;
    float sjt_math1849;
    float sjt_math1850;
    float sjt_math1851;
    float sjt_math1852;
    float sjt_math1853;
    float sjt_math1854;
    float sjt_math1855;
    float sjt_math1856;
    float sjt_math1857;
    float sjt_math1858;
    float sjt_math1859;
    float sjt_math1860;
    float sjt_math1861;
    float sjt_math1862;
    float sjt_math1863;
    float sjt_math1864;
    float sjt_math1865;
    float sjt_math1866;
    float sjt_math1867;
    float sjt_math1868;
    float sjt_math1869;
    float sjt_math1870;
    float sjt_math1871;
    float sjt_math1872;
    float sjt_math1873;
    float sjt_math1874;
    float sjt_math1875;
    float sjt_math1876;
    float sjt_math1877;
    float sjt_math1878;
    float sjt_math1879;
    float sjt_math1880;
    float sjt_math1881;
    float sjt_math1882;
    float sjt_math1883;
    float sjt_math1884;
    float sjt_math1885;
    float sjt_math1886;
    float sjt_math1887;
    float sjt_math1888;
    float sjt_math1889;
    float sjt_math1890;
    float sjt_math1891;
    float sjt_math1892;
    float sjt_math1893;
    float sjt_math1894;
    float sjt_math1895;
    float sjt_math1896;
    float sjt_math1897;
    float sjt_math1898;
    float sjt_math1899;
    float sjt_math1900;
    float sjt_math1901;
    float sjt_math1902;
    float sjt_math1903;
    float sjt_math1904;
    float sjt_math1905;
    float sjt_math1906;
    float sjt_math1907;
    float sjt_math1908;
    float sjt_math1909;
    float sjt_math1910;
    float sjt_math1911;
    float sjt_math1912;
    float sjt_math1913;
    float sjt_math1914;
    float sjt_math1915;
    float sjt_math1916;
    float sjt_math1917;
    float sjt_math1918;
    float sjt_math1919;
    float sjt_math1920;
    float sjt_math1921;
    float sjt_math1922;
    float sjt_math1923;
    float sjt_math1924;
    float sjt_math1925;
    float sjt_math1926;
    float sjt_math1927;
    float sjt_math1928;
    float sjt_math1929;
    float sjt_math1930;
    float sjt_math1931;
    float sjt_math1932;
    float sjt_math1933;
    float sjt_math1934;
    float sjt_math1935;
    float sjt_math1936;
    float sjt_math1937;
    float sjt_math1938;
    float sjt_math1939;
    float sjt_math1940;
    float sjt_math1941;
    float sjt_math1942;
    float sjt_math1943;
    float sjt_math1944;
    float sjt_math1945;
    float sjt_math1946;
    float sjt_math1947;
    float sjt_math1948;
    float sjt_math1949;
    float sjt_math1950;
    float sjt_math1951;
    float sjt_math1952;
    float sjt_math1953;
    float sjt_math1954;
    float sjt_math1955;
    float sjt_math1956;
    float sjt_math1957;
    float sjt_math1958;
    float sjt_math1959;
    float sjt_math1960;
    float sjt_math1961;
    float sjt_math1962;
    float sjt_math1963;
    float sjt_math1964;
    float sjt_math1965;
    float sjt_math1966;
    float sjt_math1967;
    float sjt_math1968;
    float sjt_math1969;
    float sjt_math1970;
    float sjt_math1971;
    float sjt_math1972;
    float sjt_math1973;
    float sjt_math1974;
    float sjt_math1975;
    float sjt_math1976;
    float sjt_math1977;
    float sjt_math1978;
    float sjt_math1979;
    float sjt_math1980;
    float sjt_math1981;
    float sjt_math1982;
    float sjt_math1983;
    float sjt_math1984;
    float sjt_math1985;
    float sjt_math1986;
    float sjt_math1987;
    float sjt_math1988;
    float sjt_math1989;
    float sjt_math1990;
    float sjt_math1991;
    float sjt_math1992;
    float sjt_math1993;
    float sjt_math1994;
    float sjt_math1995;
    float sjt_math1996;
    float sjt_math1997;
    float sjt_math1998;
    float sjt_math1999;
    float sjt_math2000;
    float sjt_math2001;
    float sjt_math2002;
    float sjt_math2003;
    float sjt_math2004;
    float sjt_math2005;
    float sjt_math2006;
    float sjt_math2007;
    float sjt_math2008;
    float sjt_math2009;
    float sjt_math2010;
    float sjt_math2011;
    float sjt_math2012;
    float sjt_math2013;
    float sjt_math2014;
    float sjt_math2015;
    float sjt_math2016;
    float sjt_math2017;
    float sjt_math2018;
    float sjt_math2019;
    float sjt_math2020;
    float sjt_math2021;
    float sjt_math2022;
    float sjt_math2023;
    float sjt_math2024;
    float sjt_math2025;
    float sjt_math2026;
    float sjt_math2027;
    float sjt_math2028;
    float sjt_math2029;
    float sjt_math2030;
    float sjt_math2031;
    float sjt_math2032;
    float sjt_math2033;
    float sjt_math2034;
    float sjt_math2035;
    float sjt_math2036;
    float sjt_math2037;
    float sjt_math2038;
    float sjt_math2039;
    float sjt_math2040;
    float sjt_math2041;
    float sjt_math2042;
    float sjt_math2043;
    float sjt_math2044;
    float sjt_math2045;
    float sjt_math2046;
    float sjt_math2047;
    float sjt_math2048;
    float sjt_math2049;
    float sjt_math2050;
    float sjt_math2051;
    float sjt_math2052;
    float sjt_math2053;
    float sjt_math2054;
    float sjt_math2055;
    float sjt_math2056;
    float sjt_math2057;
    float sjt_math2058;
    float sjt_math2059;
    float sjt_math2060;
    float sjt_math2061;
    float sjt_math2062;
    float sjt_math2063;
    float sjt_math2064;
    float sjt_math2065;
    float sjt_math2066;
    float sjt_math2067;
    float sjt_math2068;
    float sjt_math2069;
    float sjt_math2070;
    float sjt_math2071;
    float sjt_math2072;
    float sjt_math2073;
    float sjt_math2074;
    float sjt_math2075;
    float sjt_math2076;
    float sjt_math2077;
    float sjt_math2078;
    float sjt_math2079;
    float sjt_math2080;
    float sjt_math2081;
    float sjt_math2082;
    float sjt_math2083;
    float sjt_math2084;
    float sjt_math2085;
    float sjt_math2086;
    float sjt_math2087;
    float sjt_math2088;
    float sjt_math2089;
    float sjt_math2090;
    float sjt_math2091;
    float sjt_math2092;
    float sjt_math2093;
    float sjt_math2094;
    float sjt_math2095;
    float sjt_math2096;
    float sjt_math2097;
    float sjt_math2098;
    sjs_mat4* sjt_parent52;
    sjs_mat4 sjv_t;

#line 81 "lib/ui/mat4.sj"
    sjt_dot1004 = _parent;
#line 83
    sjt_math1565 = (sjt_dot1004)->m12;
#line 81
    sjt_dot1005 = _parent;
#line 83
    sjt_math1566 = (sjt_dot1005)->m23;
#line 83
    sjt_math1563 = sjt_math1565 * sjt_math1566;
#line 81
    sjt_dot1006 = _parent;
#line 83
    sjt_math1564 = (sjt_dot1006)->m31;
#line 83
    sjt_math1561 = sjt_math1563 * sjt_math1564;
#line 81
    sjt_dot1007 = _parent;
#line 83
    sjt_math1569 = (sjt_dot1007)->m13;
#line 81
    sjt_dot1008 = _parent;
#line 83
    sjt_math1570 = (sjt_dot1008)->m22;
#line 83
    sjt_math1567 = sjt_math1569 * sjt_math1570;
#line 81
    sjt_dot1009 = _parent;
#line 83
    sjt_math1568 = (sjt_dot1009)->m31;
#line 83
    sjt_math1562 = sjt_math1567 * sjt_math1568;
#line 83
    sjt_math1559 = sjt_math1561 - sjt_math1562;
#line 81
    sjt_dot1010 = _parent;
#line 83
    sjt_math1573 = (sjt_dot1010)->m13;
#line 81
    sjt_dot1011 = _parent;
#line 83
    sjt_math1574 = (sjt_dot1011)->m21;
#line 83
    sjt_math1571 = sjt_math1573 * sjt_math1574;
#line 81
    sjt_dot1012 = _parent;
#line 83
    sjt_math1572 = (sjt_dot1012)->m32;
#line 83
    sjt_math1560 = sjt_math1571 * sjt_math1572;
#line 83
    sjt_math1557 = sjt_math1559 + sjt_math1560;
#line 81
    sjt_dot1013 = _parent;
#line 83
    sjt_math1577 = (sjt_dot1013)->m11;
#line 81
    sjt_dot1014 = _parent;
#line 83
    sjt_math1578 = (sjt_dot1014)->m23;
#line 83
    sjt_math1575 = sjt_math1577 * sjt_math1578;
#line 81
    sjt_dot1015 = _parent;
#line 83
    sjt_math1576 = (sjt_dot1015)->m32;
#line 83
    sjt_math1558 = sjt_math1575 * sjt_math1576;
#line 83
    sjt_math1555 = sjt_math1557 - sjt_math1558;
#line 81
    sjt_dot1016 = _parent;
#line 83
    sjt_math1581 = (sjt_dot1016)->m12;
#line 81
    sjt_dot1017 = _parent;
#line 83
    sjt_math1582 = (sjt_dot1017)->m21;
#line 83
    sjt_math1579 = sjt_math1581 * sjt_math1582;
#line 81
    sjt_dot1018 = _parent;
#line 83
    sjt_math1580 = (sjt_dot1018)->m33;
#line 83
    sjt_math1556 = sjt_math1579 * sjt_math1580;
#line 83
    sjt_math1553 = sjt_math1555 - sjt_math1556;
#line 81
    sjt_dot1019 = _parent;
#line 83
    sjt_math1585 = (sjt_dot1019)->m11;
#line 81
    sjt_dot1020 = _parent;
#line 83
    sjt_math1586 = (sjt_dot1020)->m22;
#line 83
    sjt_math1583 = sjt_math1585 * sjt_math1586;
#line 81
    sjt_dot1021 = _parent;
#line 83
    sjt_math1584 = (sjt_dot1021)->m33;
#line 83
    sjt_math1554 = sjt_math1583 * sjt_math1584;
#line 83
    sjv_t.m00 = sjt_math1553 + sjt_math1554;
#line 81
    sjt_dot1022 = _parent;
#line 84
    sjt_math1599 = (sjt_dot1022)->m03;
#line 81
    sjt_dot1023 = _parent;
#line 84
    sjt_math1600 = (sjt_dot1023)->m22;
#line 84
    sjt_math1597 = sjt_math1599 * sjt_math1600;
#line 81
    sjt_dot1024 = _parent;
#line 84
    sjt_math1598 = (sjt_dot1024)->m31;
#line 84
    sjt_math1595 = sjt_math1597 * sjt_math1598;
#line 81
    sjt_dot1025 = _parent;
#line 84
    sjt_math1603 = (sjt_dot1025)->m02;
#line 81
    sjt_dot1026 = _parent;
#line 84
    sjt_math1604 = (sjt_dot1026)->m23;
#line 84
    sjt_math1601 = sjt_math1603 * sjt_math1604;
#line 81
    sjt_dot1027 = _parent;
#line 84
    sjt_math1602 = (sjt_dot1027)->m31;
#line 84
    sjt_math1596 = sjt_math1601 * sjt_math1602;
#line 84
    sjt_math1593 = sjt_math1595 - sjt_math1596;
#line 81
    sjt_dot1028 = _parent;
#line 84
    sjt_math1607 = (sjt_dot1028)->m03;
#line 81
    sjt_dot1029 = _parent;
#line 84
    sjt_math1608 = (sjt_dot1029)->m21;
#line 84
    sjt_math1605 = sjt_math1607 * sjt_math1608;
#line 81
    sjt_dot1030 = _parent;
#line 84
    sjt_math1606 = (sjt_dot1030)->m32;
#line 84
    sjt_math1594 = sjt_math1605 * sjt_math1606;
#line 84
    sjt_math1591 = sjt_math1593 - sjt_math1594;
#line 81
    sjt_dot1031 = _parent;
#line 84
    sjt_math1611 = (sjt_dot1031)->m01;
#line 81
    sjt_dot1032 = _parent;
#line 84
    sjt_math1612 = (sjt_dot1032)->m23;
#line 84
    sjt_math1609 = sjt_math1611 * sjt_math1612;
#line 81
    sjt_dot1033 = _parent;
#line 84
    sjt_math1610 = (sjt_dot1033)->m32;
#line 84
    sjt_math1592 = sjt_math1609 * sjt_math1610;
#line 84
    sjt_math1589 = sjt_math1591 + sjt_math1592;
#line 81
    sjt_dot1034 = _parent;
#line 84
    sjt_math1615 = (sjt_dot1034)->m02;
#line 81
    sjt_dot1035 = _parent;
#line 84
    sjt_math1616 = (sjt_dot1035)->m21;
#line 84
    sjt_math1613 = sjt_math1615 * sjt_math1616;
#line 81
    sjt_dot1036 = _parent;
#line 84
    sjt_math1614 = (sjt_dot1036)->m33;
#line 84
    sjt_math1590 = sjt_math1613 * sjt_math1614;
#line 84
    sjt_math1587 = sjt_math1589 + sjt_math1590;
#line 81
    sjt_dot1037 = _parent;
#line 84
    sjt_math1619 = (sjt_dot1037)->m01;
#line 81
    sjt_dot1038 = _parent;
#line 84
    sjt_math1620 = (sjt_dot1038)->m22;
#line 84
    sjt_math1617 = sjt_math1619 * sjt_math1620;
#line 81
    sjt_dot1039 = _parent;
#line 84
    sjt_math1618 = (sjt_dot1039)->m33;
#line 84
    sjt_math1588 = sjt_math1617 * sjt_math1618;
#line 84
    sjv_t.m01 = sjt_math1587 - sjt_math1588;
#line 81
    sjt_dot1040 = _parent;
#line 85
    sjt_math1633 = (sjt_dot1040)->m02;
#line 81
    sjt_dot1041 = _parent;
#line 85
    sjt_math1634 = (sjt_dot1041)->m13;
#line 85
    sjt_math1631 = sjt_math1633 * sjt_math1634;
#line 81
    sjt_dot1042 = _parent;
#line 85
    sjt_math1632 = (sjt_dot1042)->m31;
#line 85
    sjt_math1629 = sjt_math1631 * sjt_math1632;
#line 81
    sjt_dot1043 = _parent;
#line 85
    sjt_math1637 = (sjt_dot1043)->m03;
#line 81
    sjt_dot1044 = _parent;
#line 85
    sjt_math1638 = (sjt_dot1044)->m12;
#line 85
    sjt_math1635 = sjt_math1637 * sjt_math1638;
#line 81
    sjt_dot1045 = _parent;
#line 85
    sjt_math1636 = (sjt_dot1045)->m31;
#line 85
    sjt_math1630 = sjt_math1635 * sjt_math1636;
#line 85
    sjt_math1627 = sjt_math1629 - sjt_math1630;
#line 81
    sjt_dot1046 = _parent;
#line 85
    sjt_math1641 = (sjt_dot1046)->m03;
#line 81
    sjt_dot1047 = _parent;
#line 85
    sjt_math1642 = (sjt_dot1047)->m11;
#line 85
    sjt_math1639 = sjt_math1641 * sjt_math1642;
#line 81
    sjt_dot1048 = _parent;
#line 85
    sjt_math1640 = (sjt_dot1048)->m32;
#line 85
    sjt_math1628 = sjt_math1639 * sjt_math1640;
#line 85
    sjt_math1625 = sjt_math1627 + sjt_math1628;
#line 81
    sjt_dot1049 = _parent;
#line 85
    sjt_math1645 = (sjt_dot1049)->m01;
#line 81
    sjt_dot1050 = _parent;
#line 85
    sjt_math1646 = (sjt_dot1050)->m13;
#line 85
    sjt_math1643 = sjt_math1645 * sjt_math1646;
#line 81
    sjt_dot1051 = _parent;
#line 85
    sjt_math1644 = (sjt_dot1051)->m32;
#line 85
    sjt_math1626 = sjt_math1643 * sjt_math1644;
#line 85
    sjt_math1623 = sjt_math1625 - sjt_math1626;
#line 81
    sjt_dot1052 = _parent;
#line 85
    sjt_math1649 = (sjt_dot1052)->m02;
#line 81
    sjt_dot1053 = _parent;
#line 85
    sjt_math1650 = (sjt_dot1053)->m11;
#line 85
    sjt_math1647 = sjt_math1649 * sjt_math1650;
#line 81
    sjt_dot1054 = _parent;
#line 85
    sjt_math1648 = (sjt_dot1054)->m33;
#line 85
    sjt_math1624 = sjt_math1647 * sjt_math1648;
#line 85
    sjt_math1621 = sjt_math1623 - sjt_math1624;
#line 81
    sjt_dot1055 = _parent;
#line 85
    sjt_math1653 = (sjt_dot1055)->m01;
#line 81
    sjt_dot1056 = _parent;
#line 85
    sjt_math1654 = (sjt_dot1056)->m12;
#line 85
    sjt_math1651 = sjt_math1653 * sjt_math1654;
#line 81
    sjt_dot1057 = _parent;
#line 85
    sjt_math1652 = (sjt_dot1057)->m33;
#line 85
    sjt_math1622 = sjt_math1651 * sjt_math1652;
#line 85
    sjv_t.m02 = sjt_math1621 + sjt_math1622;
#line 81
    sjt_dot1058 = _parent;
#line 86
    sjt_math1667 = (sjt_dot1058)->m03;
#line 81
    sjt_dot1059 = _parent;
#line 86
    sjt_math1668 = (sjt_dot1059)->m12;
#line 86
    sjt_math1665 = sjt_math1667 * sjt_math1668;
#line 81
    sjt_dot1060 = _parent;
#line 86
    sjt_math1666 = (sjt_dot1060)->m21;
#line 86
    sjt_math1663 = sjt_math1665 * sjt_math1666;
#line 81
    sjt_dot1061 = _parent;
#line 86
    sjt_math1671 = (sjt_dot1061)->m02;
#line 81
    sjt_dot1062 = _parent;
#line 86
    sjt_math1672 = (sjt_dot1062)->m13;
#line 86
    sjt_math1669 = sjt_math1671 * sjt_math1672;
#line 81
    sjt_dot1063 = _parent;
#line 86
    sjt_math1670 = (sjt_dot1063)->m21;
#line 86
    sjt_math1664 = sjt_math1669 * sjt_math1670;
#line 86
    sjt_math1661 = sjt_math1663 - sjt_math1664;
#line 81
    sjt_dot1064 = _parent;
#line 86
    sjt_math1675 = (sjt_dot1064)->m03;
#line 81
    sjt_dot1065 = _parent;
#line 86
    sjt_math1676 = (sjt_dot1065)->m11;
#line 86
    sjt_math1673 = sjt_math1675 * sjt_math1676;
#line 81
    sjt_dot1066 = _parent;
#line 86
    sjt_math1674 = (sjt_dot1066)->m22;
#line 86
    sjt_math1662 = sjt_math1673 * sjt_math1674;
#line 86
    sjt_math1659 = sjt_math1661 - sjt_math1662;
#line 81
    sjt_dot1067 = _parent;
#line 86
    sjt_math1679 = (sjt_dot1067)->m01;
#line 81
    sjt_dot1068 = _parent;
#line 86
    sjt_math1680 = (sjt_dot1068)->m13;
#line 86
    sjt_math1677 = sjt_math1679 * sjt_math1680;
#line 81
    sjt_dot1069 = _parent;
#line 86
    sjt_math1678 = (sjt_dot1069)->m22;
#line 86
    sjt_math1660 = sjt_math1677 * sjt_math1678;
#line 86
    sjt_math1657 = sjt_math1659 + sjt_math1660;
#line 81
    sjt_dot1070 = _parent;
#line 86
    sjt_math1683 = (sjt_dot1070)->m02;
#line 81
    sjt_dot1071 = _parent;
#line 86
    sjt_math1684 = (sjt_dot1071)->m11;
#line 86
    sjt_math1681 = sjt_math1683 * sjt_math1684;
#line 81
    sjt_dot1072 = _parent;
#line 86
    sjt_math1682 = (sjt_dot1072)->m23;
#line 86
    sjt_math1658 = sjt_math1681 * sjt_math1682;
#line 86
    sjt_math1655 = sjt_math1657 + sjt_math1658;
#line 81
    sjt_dot1073 = _parent;
#line 86
    sjt_math1687 = (sjt_dot1073)->m01;
#line 81
    sjt_dot1074 = _parent;
#line 86
    sjt_math1688 = (sjt_dot1074)->m12;
#line 86
    sjt_math1685 = sjt_math1687 * sjt_math1688;
#line 81
    sjt_dot1075 = _parent;
#line 86
    sjt_math1686 = (sjt_dot1075)->m23;
#line 86
    sjt_math1656 = sjt_math1685 * sjt_math1686;
#line 86
    sjv_t.m03 = sjt_math1655 - sjt_math1656;
#line 81
    sjt_dot1076 = _parent;
#line 87
    sjt_math1701 = (sjt_dot1076)->m13;
#line 81
    sjt_dot1077 = _parent;
#line 87
    sjt_math1702 = (sjt_dot1077)->m22;
#line 87
    sjt_math1699 = sjt_math1701 * sjt_math1702;
#line 81
    sjt_dot1078 = _parent;
#line 87
    sjt_math1700 = (sjt_dot1078)->m30;
#line 87
    sjt_math1697 = sjt_math1699 * sjt_math1700;
#line 81
    sjt_dot1079 = _parent;
#line 87
    sjt_math1705 = (sjt_dot1079)->m12;
#line 81
    sjt_dot1080 = _parent;
#line 87
    sjt_math1706 = (sjt_dot1080)->m23;
#line 87
    sjt_math1703 = sjt_math1705 * sjt_math1706;
#line 81
    sjt_dot1081 = _parent;
#line 87
    sjt_math1704 = (sjt_dot1081)->m30;
#line 87
    sjt_math1698 = sjt_math1703 * sjt_math1704;
#line 87
    sjt_math1695 = sjt_math1697 - sjt_math1698;
#line 81
    sjt_dot1082 = _parent;
#line 87
    sjt_math1709 = (sjt_dot1082)->m13;
#line 81
    sjt_dot1083 = _parent;
#line 87
    sjt_math1710 = (sjt_dot1083)->m20;
#line 87
    sjt_math1707 = sjt_math1709 * sjt_math1710;
#line 81
    sjt_dot1084 = _parent;
#line 87
    sjt_math1708 = (sjt_dot1084)->m32;
#line 87
    sjt_math1696 = sjt_math1707 * sjt_math1708;
#line 87
    sjt_math1693 = sjt_math1695 - sjt_math1696;
#line 81
    sjt_dot1085 = _parent;
#line 87
    sjt_math1713 = (sjt_dot1085)->m10;
#line 81
    sjt_dot1086 = _parent;
#line 87
    sjt_math1714 = (sjt_dot1086)->m23;
#line 87
    sjt_math1711 = sjt_math1713 * sjt_math1714;
#line 81
    sjt_dot1087 = _parent;
#line 87
    sjt_math1712 = (sjt_dot1087)->m32;
#line 87
    sjt_math1694 = sjt_math1711 * sjt_math1712;
#line 87
    sjt_math1691 = sjt_math1693 + sjt_math1694;
#line 81
    sjt_dot1088 = _parent;
#line 87
    sjt_math1717 = (sjt_dot1088)->m12;
#line 81
    sjt_dot1089 = _parent;
#line 87
    sjt_math1718 = (sjt_dot1089)->m20;
#line 87
    sjt_math1715 = sjt_math1717 * sjt_math1718;
#line 81
    sjt_dot1090 = _parent;
#line 87
    sjt_math1716 = (sjt_dot1090)->m33;
#line 87
    sjt_math1692 = sjt_math1715 * sjt_math1716;
#line 87
    sjt_math1689 = sjt_math1691 + sjt_math1692;
#line 81
    sjt_dot1091 = _parent;
#line 87
    sjt_math1721 = (sjt_dot1091)->m10;
#line 81
    sjt_dot1092 = _parent;
#line 87
    sjt_math1722 = (sjt_dot1092)->m22;
#line 87
    sjt_math1719 = sjt_math1721 * sjt_math1722;
#line 81
    sjt_dot1093 = _parent;
#line 87
    sjt_math1720 = (sjt_dot1093)->m33;
#line 87
    sjt_math1690 = sjt_math1719 * sjt_math1720;
#line 87
    sjv_t.m10 = sjt_math1689 - sjt_math1690;
#line 81
    sjt_dot1094 = _parent;
#line 88
    sjt_math1735 = (sjt_dot1094)->m02;
#line 81
    sjt_dot1095 = _parent;
#line 88
    sjt_math1736 = (sjt_dot1095)->m23;
#line 88
    sjt_math1733 = sjt_math1735 * sjt_math1736;
#line 81
    sjt_dot1096 = _parent;
#line 88
    sjt_math1734 = (sjt_dot1096)->m30;
#line 88
    sjt_math1731 = sjt_math1733 * sjt_math1734;
#line 81
    sjt_dot1097 = _parent;
#line 88
    sjt_math1739 = (sjt_dot1097)->m03;
#line 81
    sjt_dot1098 = _parent;
#line 88
    sjt_math1740 = (sjt_dot1098)->m22;
#line 88
    sjt_math1737 = sjt_math1739 * sjt_math1740;
#line 81
    sjt_dot1099 = _parent;
#line 88
    sjt_math1738 = (sjt_dot1099)->m30;
#line 88
    sjt_math1732 = sjt_math1737 * sjt_math1738;
#line 88
    sjt_math1729 = sjt_math1731 - sjt_math1732;
#line 81
    sjt_dot1100 = _parent;
#line 88
    sjt_math1743 = (sjt_dot1100)->m03;
#line 81
    sjt_dot1101 = _parent;
#line 88
    sjt_math1744 = (sjt_dot1101)->m20;
#line 88
    sjt_math1741 = sjt_math1743 * sjt_math1744;
#line 81
    sjt_dot1102 = _parent;
#line 88
    sjt_math1742 = (sjt_dot1102)->m32;
#line 88
    sjt_math1730 = sjt_math1741 * sjt_math1742;
#line 88
    sjt_math1727 = sjt_math1729 + sjt_math1730;
#line 81
    sjt_dot1103 = _parent;
#line 88
    sjt_math1747 = (sjt_dot1103)->m00;
#line 81
    sjt_dot1104 = _parent;
#line 88
    sjt_math1748 = (sjt_dot1104)->m23;
#line 88
    sjt_math1745 = sjt_math1747 * sjt_math1748;
#line 81
    sjt_dot1105 = _parent;
#line 88
    sjt_math1746 = (sjt_dot1105)->m32;
#line 88
    sjt_math1728 = sjt_math1745 * sjt_math1746;
#line 88
    sjt_math1725 = sjt_math1727 - sjt_math1728;
#line 81
    sjt_dot1106 = _parent;
#line 88
    sjt_math1751 = (sjt_dot1106)->m02;
#line 81
    sjt_dot1107 = _parent;
#line 88
    sjt_math1752 = (sjt_dot1107)->m20;
#line 88
    sjt_math1749 = sjt_math1751 * sjt_math1752;
#line 81
    sjt_dot1108 = _parent;
#line 88
    sjt_math1750 = (sjt_dot1108)->m33;
#line 88
    sjt_math1726 = sjt_math1749 * sjt_math1750;
#line 88
    sjt_math1723 = sjt_math1725 - sjt_math1726;
#line 81
    sjt_dot1109 = _parent;
#line 88
    sjt_math1755 = (sjt_dot1109)->m00;
#line 81
    sjt_dot1110 = _parent;
#line 88
    sjt_math1756 = (sjt_dot1110)->m22;
#line 88
    sjt_math1753 = sjt_math1755 * sjt_math1756;
#line 81
    sjt_dot1111 = _parent;
#line 88
    sjt_math1754 = (sjt_dot1111)->m33;
#line 88
    sjt_math1724 = sjt_math1753 * sjt_math1754;
#line 88
    sjv_t.m11 = sjt_math1723 + sjt_math1724;
#line 81
    sjt_dot1112 = _parent;
#line 89
    sjt_math1769 = (sjt_dot1112)->m03;
#line 81
    sjt_dot1113 = _parent;
#line 89
    sjt_math1770 = (sjt_dot1113)->m12;
#line 89
    sjt_math1767 = sjt_math1769 * sjt_math1770;
#line 81
    sjt_dot1114 = _parent;
#line 89
    sjt_math1768 = (sjt_dot1114)->m30;
#line 89
    sjt_math1765 = sjt_math1767 * sjt_math1768;
#line 81
    sjt_dot1115 = _parent;
#line 89
    sjt_math1773 = (sjt_dot1115)->m02;
#line 81
    sjt_dot1116 = _parent;
#line 89
    sjt_math1774 = (sjt_dot1116)->m13;
#line 89
    sjt_math1771 = sjt_math1773 * sjt_math1774;
#line 81
    sjt_dot1117 = _parent;
#line 89
    sjt_math1772 = (sjt_dot1117)->m30;
#line 89
    sjt_math1766 = sjt_math1771 * sjt_math1772;
#line 89
    sjt_math1763 = sjt_math1765 - sjt_math1766;
#line 81
    sjt_dot1118 = _parent;
#line 89
    sjt_math1777 = (sjt_dot1118)->m03;
#line 81
    sjt_dot1119 = _parent;
#line 89
    sjt_math1778 = (sjt_dot1119)->m10;
#line 89
    sjt_math1775 = sjt_math1777 * sjt_math1778;
#line 81
    sjt_dot1120 = _parent;
#line 89
    sjt_math1776 = (sjt_dot1120)->m32;
#line 89
    sjt_math1764 = sjt_math1775 * sjt_math1776;
#line 89
    sjt_math1761 = sjt_math1763 - sjt_math1764;
#line 81
    sjt_dot1121 = _parent;
#line 89
    sjt_math1781 = (sjt_dot1121)->m00;
#line 81
    sjt_dot1122 = _parent;
#line 89
    sjt_math1782 = (sjt_dot1122)->m13;
#line 89
    sjt_math1779 = sjt_math1781 * sjt_math1782;
#line 81
    sjt_dot1123 = _parent;
#line 89
    sjt_math1780 = (sjt_dot1123)->m32;
#line 89
    sjt_math1762 = sjt_math1779 * sjt_math1780;
#line 89
    sjt_math1759 = sjt_math1761 + sjt_math1762;
#line 81
    sjt_dot1124 = _parent;
#line 89
    sjt_math1785 = (sjt_dot1124)->m02;
#line 81
    sjt_dot1125 = _parent;
#line 89
    sjt_math1786 = (sjt_dot1125)->m10;
#line 89
    sjt_math1783 = sjt_math1785 * sjt_math1786;
#line 81
    sjt_dot1126 = _parent;
#line 89
    sjt_math1784 = (sjt_dot1126)->m33;
#line 89
    sjt_math1760 = sjt_math1783 * sjt_math1784;
#line 89
    sjt_math1757 = sjt_math1759 + sjt_math1760;
#line 81
    sjt_dot1127 = _parent;
#line 89
    sjt_math1789 = (sjt_dot1127)->m00;
#line 81
    sjt_dot1128 = _parent;
#line 89
    sjt_math1790 = (sjt_dot1128)->m12;
#line 89
    sjt_math1787 = sjt_math1789 * sjt_math1790;
#line 81
    sjt_dot1129 = _parent;
#line 89
    sjt_math1788 = (sjt_dot1129)->m33;
#line 89
    sjt_math1758 = sjt_math1787 * sjt_math1788;
#line 89
    sjv_t.m12 = sjt_math1757 - sjt_math1758;
#line 81
    sjt_dot1130 = _parent;
#line 90
    sjt_math1803 = (sjt_dot1130)->m02;
#line 81
    sjt_dot1131 = _parent;
#line 90
    sjt_math1804 = (sjt_dot1131)->m13;
#line 90
    sjt_math1801 = sjt_math1803 * sjt_math1804;
#line 81
    sjt_dot1132 = _parent;
#line 90
    sjt_math1802 = (sjt_dot1132)->m20;
#line 90
    sjt_math1799 = sjt_math1801 * sjt_math1802;
#line 81
    sjt_dot1133 = _parent;
#line 90
    sjt_math1807 = (sjt_dot1133)->m03;
#line 81
    sjt_dot1134 = _parent;
#line 90
    sjt_math1808 = (sjt_dot1134)->m12;
#line 90
    sjt_math1805 = sjt_math1807 * sjt_math1808;
#line 81
    sjt_dot1135 = _parent;
#line 90
    sjt_math1806 = (sjt_dot1135)->m20;
#line 90
    sjt_math1800 = sjt_math1805 * sjt_math1806;
#line 90
    sjt_math1797 = sjt_math1799 - sjt_math1800;
#line 81
    sjt_dot1136 = _parent;
#line 90
    sjt_math1811 = (sjt_dot1136)->m03;
#line 81
    sjt_dot1137 = _parent;
#line 90
    sjt_math1812 = (sjt_dot1137)->m10;
#line 90
    sjt_math1809 = sjt_math1811 * sjt_math1812;
#line 81
    sjt_dot1138 = _parent;
#line 90
    sjt_math1810 = (sjt_dot1138)->m22;
#line 90
    sjt_math1798 = sjt_math1809 * sjt_math1810;
#line 90
    sjt_math1795 = sjt_math1797 + sjt_math1798;
#line 81
    sjt_dot1139 = _parent;
#line 90
    sjt_math1815 = (sjt_dot1139)->m00;
#line 81
    sjt_dot1140 = _parent;
#line 90
    sjt_math1816 = (sjt_dot1140)->m13;
#line 90
    sjt_math1813 = sjt_math1815 * sjt_math1816;
#line 81
    sjt_dot1141 = _parent;
#line 90
    sjt_math1814 = (sjt_dot1141)->m22;
#line 90
    sjt_math1796 = sjt_math1813 * sjt_math1814;
#line 90
    sjt_math1793 = sjt_math1795 - sjt_math1796;
#line 81
    sjt_dot1142 = _parent;
#line 90
    sjt_math1819 = (sjt_dot1142)->m02;
#line 81
    sjt_dot1143 = _parent;
#line 90
    sjt_math1820 = (sjt_dot1143)->m10;
#line 90
    sjt_math1817 = sjt_math1819 * sjt_math1820;
#line 81
    sjt_dot1144 = _parent;
#line 90
    sjt_math1818 = (sjt_dot1144)->m23;
#line 90
    sjt_math1794 = sjt_math1817 * sjt_math1818;
#line 90
    sjt_math1791 = sjt_math1793 - sjt_math1794;
#line 81
    sjt_dot1145 = _parent;
#line 90
    sjt_math1823 = (sjt_dot1145)->m00;
#line 81
    sjt_dot1146 = _parent;
#line 90
    sjt_math1824 = (sjt_dot1146)->m12;
#line 90
    sjt_math1821 = sjt_math1823 * sjt_math1824;
#line 81
    sjt_dot1147 = _parent;
#line 90
    sjt_math1822 = (sjt_dot1147)->m23;
#line 90
    sjt_math1792 = sjt_math1821 * sjt_math1822;
#line 90
    sjv_t.m13 = sjt_math1791 + sjt_math1792;
#line 81
    sjt_dot1148 = _parent;
#line 91
    sjt_math1837 = (sjt_dot1148)->m11;
#line 81
    sjt_dot1149 = _parent;
#line 91
    sjt_math1838 = (sjt_dot1149)->m23;
#line 91
    sjt_math1835 = sjt_math1837 * sjt_math1838;
#line 81
    sjt_dot1150 = _parent;
#line 91
    sjt_math1836 = (sjt_dot1150)->m30;
#line 91
    sjt_math1833 = sjt_math1835 * sjt_math1836;
#line 81
    sjt_dot1151 = _parent;
#line 91
    sjt_math1841 = (sjt_dot1151)->m13;
#line 81
    sjt_dot1152 = _parent;
#line 91
    sjt_math1842 = (sjt_dot1152)->m21;
#line 91
    sjt_math1839 = sjt_math1841 * sjt_math1842;
#line 81
    sjt_dot1153 = _parent;
#line 91
    sjt_math1840 = (sjt_dot1153)->m30;
#line 91
    sjt_math1834 = sjt_math1839 * sjt_math1840;
#line 91
    sjt_math1831 = sjt_math1833 - sjt_math1834;
#line 81
    sjt_dot1154 = _parent;
#line 91
    sjt_math1845 = (sjt_dot1154)->m13;
#line 81
    sjt_dot1155 = _parent;
#line 91
    sjt_math1846 = (sjt_dot1155)->m20;
#line 91
    sjt_math1843 = sjt_math1845 * sjt_math1846;
#line 81
    sjt_dot1156 = _parent;
#line 91
    sjt_math1844 = (sjt_dot1156)->m31;
#line 91
    sjt_math1832 = sjt_math1843 * sjt_math1844;
#line 91
    sjt_math1829 = sjt_math1831 + sjt_math1832;
#line 81
    sjt_dot1157 = _parent;
#line 91
    sjt_math1849 = (sjt_dot1157)->m10;
#line 81
    sjt_dot1158 = _parent;
#line 91
    sjt_math1850 = (sjt_dot1158)->m23;
#line 91
    sjt_math1847 = sjt_math1849 * sjt_math1850;
#line 81
    sjt_dot1159 = _parent;
#line 91
    sjt_math1848 = (sjt_dot1159)->m31;
#line 91
    sjt_math1830 = sjt_math1847 * sjt_math1848;
#line 91
    sjt_math1827 = sjt_math1829 - sjt_math1830;
#line 81
    sjt_dot1160 = _parent;
#line 91
    sjt_math1853 = (sjt_dot1160)->m11;
#line 81
    sjt_dot1161 = _parent;
#line 91
    sjt_math1854 = (sjt_dot1161)->m20;
#line 91
    sjt_math1851 = sjt_math1853 * sjt_math1854;
#line 81
    sjt_dot1162 = _parent;
#line 91
    sjt_math1852 = (sjt_dot1162)->m33;
#line 91
    sjt_math1828 = sjt_math1851 * sjt_math1852;
#line 91
    sjt_math1825 = sjt_math1827 - sjt_math1828;
#line 81
    sjt_dot1163 = _parent;
#line 91
    sjt_math1857 = (sjt_dot1163)->m10;
#line 81
    sjt_dot1164 = _parent;
#line 91
    sjt_math1858 = (sjt_dot1164)->m21;
#line 91
    sjt_math1855 = sjt_math1857 * sjt_math1858;
#line 81
    sjt_dot1165 = _parent;
#line 91
    sjt_math1856 = (sjt_dot1165)->m33;
#line 91
    sjt_math1826 = sjt_math1855 * sjt_math1856;
#line 91
    sjv_t.m20 = sjt_math1825 + sjt_math1826;
#line 81
    sjt_dot1166 = _parent;
#line 92
    sjt_math1871 = (sjt_dot1166)->m03;
#line 81
    sjt_dot1167 = _parent;
#line 92
    sjt_math1872 = (sjt_dot1167)->m21;
#line 92
    sjt_math1869 = sjt_math1871 * sjt_math1872;
#line 81
    sjt_dot1168 = _parent;
#line 92
    sjt_math1870 = (sjt_dot1168)->m30;
#line 92
    sjt_math1867 = sjt_math1869 * sjt_math1870;
#line 81
    sjt_dot1169 = _parent;
#line 92
    sjt_math1875 = (sjt_dot1169)->m01;
#line 81
    sjt_dot1170 = _parent;
#line 92
    sjt_math1876 = (sjt_dot1170)->m23;
#line 92
    sjt_math1873 = sjt_math1875 * sjt_math1876;
#line 81
    sjt_dot1171 = _parent;
#line 92
    sjt_math1874 = (sjt_dot1171)->m30;
#line 92
    sjt_math1868 = sjt_math1873 * sjt_math1874;
#line 92
    sjt_math1865 = sjt_math1867 - sjt_math1868;
#line 81
    sjt_dot1172 = _parent;
#line 92
    sjt_math1879 = (sjt_dot1172)->m03;
#line 81
    sjt_dot1173 = _parent;
#line 92
    sjt_math1880 = (sjt_dot1173)->m20;
#line 92
    sjt_math1877 = sjt_math1879 * sjt_math1880;
#line 81
    sjt_dot1174 = _parent;
#line 92
    sjt_math1878 = (sjt_dot1174)->m31;
#line 92
    sjt_math1866 = sjt_math1877 * sjt_math1878;
#line 92
    sjt_math1863 = sjt_math1865 - sjt_math1866;
#line 81
    sjt_dot1175 = _parent;
#line 92
    sjt_math1883 = (sjt_dot1175)->m00;
#line 81
    sjt_dot1176 = _parent;
#line 92
    sjt_math1884 = (sjt_dot1176)->m23;
#line 92
    sjt_math1881 = sjt_math1883 * sjt_math1884;
#line 81
    sjt_dot1177 = _parent;
#line 92
    sjt_math1882 = (sjt_dot1177)->m31;
#line 92
    sjt_math1864 = sjt_math1881 * sjt_math1882;
#line 92
    sjt_math1861 = sjt_math1863 + sjt_math1864;
#line 81
    sjt_dot1178 = _parent;
#line 92
    sjt_math1887 = (sjt_dot1178)->m01;
#line 81
    sjt_dot1179 = _parent;
#line 92
    sjt_math1888 = (sjt_dot1179)->m20;
#line 92
    sjt_math1885 = sjt_math1887 * sjt_math1888;
#line 81
    sjt_dot1180 = _parent;
#line 92
    sjt_math1886 = (sjt_dot1180)->m33;
#line 92
    sjt_math1862 = sjt_math1885 * sjt_math1886;
#line 92
    sjt_math1859 = sjt_math1861 + sjt_math1862;
#line 81
    sjt_dot1181 = _parent;
#line 92
    sjt_math1891 = (sjt_dot1181)->m00;
#line 81
    sjt_dot1182 = _parent;
#line 92
    sjt_math1892 = (sjt_dot1182)->m21;
#line 92
    sjt_math1889 = sjt_math1891 * sjt_math1892;
#line 81
    sjt_dot1183 = _parent;
#line 92
    sjt_math1890 = (sjt_dot1183)->m33;
#line 92
    sjt_math1860 = sjt_math1889 * sjt_math1890;
#line 92
    sjv_t.m21 = sjt_math1859 - sjt_math1860;
#line 81
    sjt_dot1184 = _parent;
#line 93
    sjt_math1905 = (sjt_dot1184)->m01;
#line 81
    sjt_dot1185 = _parent;
#line 93
    sjt_math1906 = (sjt_dot1185)->m13;
#line 93
    sjt_math1903 = sjt_math1905 * sjt_math1906;
#line 81
    sjt_dot1186 = _parent;
#line 93
    sjt_math1904 = (sjt_dot1186)->m30;
#line 93
    sjt_math1901 = sjt_math1903 * sjt_math1904;
#line 81
    sjt_dot1187 = _parent;
#line 93
    sjt_math1909 = (sjt_dot1187)->m03;
#line 81
    sjt_dot1188 = _parent;
#line 93
    sjt_math1910 = (sjt_dot1188)->m11;
#line 93
    sjt_math1907 = sjt_math1909 * sjt_math1910;
#line 81
    sjt_dot1189 = _parent;
#line 93
    sjt_math1908 = (sjt_dot1189)->m30;
#line 93
    sjt_math1902 = sjt_math1907 * sjt_math1908;
#line 93
    sjt_math1899 = sjt_math1901 - sjt_math1902;
#line 81
    sjt_dot1190 = _parent;
#line 93
    sjt_math1913 = (sjt_dot1190)->m03;
#line 81
    sjt_dot1191 = _parent;
#line 93
    sjt_math1914 = (sjt_dot1191)->m10;
#line 93
    sjt_math1911 = sjt_math1913 * sjt_math1914;
#line 81
    sjt_dot1192 = _parent;
#line 93
    sjt_math1912 = (sjt_dot1192)->m31;
#line 93
    sjt_math1900 = sjt_math1911 * sjt_math1912;
#line 93
    sjt_math1897 = sjt_math1899 + sjt_math1900;
#line 81
    sjt_dot1193 = _parent;
#line 93
    sjt_math1917 = (sjt_dot1193)->m00;
#line 81
    sjt_dot1194 = _parent;
#line 93
    sjt_math1918 = (sjt_dot1194)->m13;
#line 93
    sjt_math1915 = sjt_math1917 * sjt_math1918;
#line 81
    sjt_dot1195 = _parent;
#line 93
    sjt_math1916 = (sjt_dot1195)->m31;
#line 93
    sjt_math1898 = sjt_math1915 * sjt_math1916;
#line 93
    sjt_math1895 = sjt_math1897 - sjt_math1898;
#line 81
    sjt_dot1196 = _parent;
#line 93
    sjt_math1921 = (sjt_dot1196)->m01;
#line 81
    sjt_dot1197 = _parent;
#line 93
    sjt_math1922 = (sjt_dot1197)->m10;
#line 93
    sjt_math1919 = sjt_math1921 * sjt_math1922;
#line 81
    sjt_dot1198 = _parent;
#line 93
    sjt_math1920 = (sjt_dot1198)->m33;
#line 93
    sjt_math1896 = sjt_math1919 * sjt_math1920;
#line 93
    sjt_math1893 = sjt_math1895 - sjt_math1896;
#line 81
    sjt_dot1199 = _parent;
#line 93
    sjt_math1925 = (sjt_dot1199)->m00;
#line 81
    sjt_dot1200 = _parent;
#line 93
    sjt_math1926 = (sjt_dot1200)->m11;
#line 93
    sjt_math1923 = sjt_math1925 * sjt_math1926;
#line 81
    sjt_dot1201 = _parent;
#line 93
    sjt_math1924 = (sjt_dot1201)->m33;
#line 93
    sjt_math1894 = sjt_math1923 * sjt_math1924;
#line 93
    sjv_t.m22 = sjt_math1893 + sjt_math1894;
#line 81
    sjt_dot1202 = _parent;
#line 94
    sjt_math1939 = (sjt_dot1202)->m03;
#line 81
    sjt_dot1203 = _parent;
#line 94
    sjt_math1940 = (sjt_dot1203)->m11;
#line 94
    sjt_math1937 = sjt_math1939 * sjt_math1940;
#line 81
    sjt_dot1204 = _parent;
#line 94
    sjt_math1938 = (sjt_dot1204)->m20;
#line 94
    sjt_math1935 = sjt_math1937 * sjt_math1938;
#line 81
    sjt_dot1205 = _parent;
#line 94
    sjt_math1943 = (sjt_dot1205)->m01;
#line 81
    sjt_dot1206 = _parent;
#line 94
    sjt_math1944 = (sjt_dot1206)->m13;
#line 94
    sjt_math1941 = sjt_math1943 * sjt_math1944;
#line 81
    sjt_dot1207 = _parent;
#line 94
    sjt_math1942 = (sjt_dot1207)->m20;
#line 94
    sjt_math1936 = sjt_math1941 * sjt_math1942;
#line 94
    sjt_math1933 = sjt_math1935 - sjt_math1936;
#line 81
    sjt_dot1208 = _parent;
#line 94
    sjt_math1947 = (sjt_dot1208)->m03;
#line 81
    sjt_dot1209 = _parent;
#line 94
    sjt_math1948 = (sjt_dot1209)->m10;
#line 94
    sjt_math1945 = sjt_math1947 * sjt_math1948;
#line 81
    sjt_dot1210 = _parent;
#line 94
    sjt_math1946 = (sjt_dot1210)->m21;
#line 94
    sjt_math1934 = sjt_math1945 * sjt_math1946;
#line 94
    sjt_math1931 = sjt_math1933 - sjt_math1934;
#line 81
    sjt_dot1211 = _parent;
#line 94
    sjt_math1951 = (sjt_dot1211)->m00;
#line 81
    sjt_dot1212 = _parent;
#line 94
    sjt_math1952 = (sjt_dot1212)->m13;
#line 94
    sjt_math1949 = sjt_math1951 * sjt_math1952;
#line 81
    sjt_dot1213 = _parent;
#line 94
    sjt_math1950 = (sjt_dot1213)->m21;
#line 94
    sjt_math1932 = sjt_math1949 * sjt_math1950;
#line 94
    sjt_math1929 = sjt_math1931 + sjt_math1932;
#line 81
    sjt_dot1214 = _parent;
#line 94
    sjt_math1955 = (sjt_dot1214)->m01;
#line 81
    sjt_dot1215 = _parent;
#line 94
    sjt_math1956 = (sjt_dot1215)->m10;
#line 94
    sjt_math1953 = sjt_math1955 * sjt_math1956;
#line 81
    sjt_dot1216 = _parent;
#line 94
    sjt_math1954 = (sjt_dot1216)->m23;
#line 94
    sjt_math1930 = sjt_math1953 * sjt_math1954;
#line 94
    sjt_math1927 = sjt_math1929 + sjt_math1930;
#line 81
    sjt_dot1217 = _parent;
#line 94
    sjt_math1959 = (sjt_dot1217)->m00;
#line 81
    sjt_dot1218 = _parent;
#line 94
    sjt_math1960 = (sjt_dot1218)->m11;
#line 94
    sjt_math1957 = sjt_math1959 * sjt_math1960;
#line 81
    sjt_dot1219 = _parent;
#line 94
    sjt_math1958 = (sjt_dot1219)->m23;
#line 94
    sjt_math1928 = sjt_math1957 * sjt_math1958;
#line 94
    sjv_t.m23 = sjt_math1927 - sjt_math1928;
#line 81
    sjt_dot1220 = _parent;
#line 95
    sjt_math1973 = (sjt_dot1220)->m12;
#line 81
    sjt_dot1221 = _parent;
#line 95
    sjt_math1974 = (sjt_dot1221)->m21;
#line 95
    sjt_math1971 = sjt_math1973 * sjt_math1974;
#line 81
    sjt_dot1222 = _parent;
#line 95
    sjt_math1972 = (sjt_dot1222)->m30;
#line 95
    sjt_math1969 = sjt_math1971 * sjt_math1972;
#line 81
    sjt_dot1223 = _parent;
#line 95
    sjt_math1977 = (sjt_dot1223)->m11;
#line 81
    sjt_dot1224 = _parent;
#line 95
    sjt_math1978 = (sjt_dot1224)->m22;
#line 95
    sjt_math1975 = sjt_math1977 * sjt_math1978;
#line 81
    sjt_dot1225 = _parent;
#line 95
    sjt_math1976 = (sjt_dot1225)->m30;
#line 95
    sjt_math1970 = sjt_math1975 * sjt_math1976;
#line 95
    sjt_math1967 = sjt_math1969 - sjt_math1970;
#line 81
    sjt_dot1226 = _parent;
#line 95
    sjt_math1981 = (sjt_dot1226)->m12;
#line 81
    sjt_dot1227 = _parent;
#line 95
    sjt_math1982 = (sjt_dot1227)->m20;
#line 95
    sjt_math1979 = sjt_math1981 * sjt_math1982;
#line 81
    sjt_dot1228 = _parent;
#line 95
    sjt_math1980 = (sjt_dot1228)->m31;
#line 95
    sjt_math1968 = sjt_math1979 * sjt_math1980;
#line 95
    sjt_math1965 = sjt_math1967 - sjt_math1968;
#line 81
    sjt_dot1229 = _parent;
#line 95
    sjt_math1985 = (sjt_dot1229)->m10;
#line 81
    sjt_dot1230 = _parent;
#line 95
    sjt_math1986 = (sjt_dot1230)->m22;
#line 95
    sjt_math1983 = sjt_math1985 * sjt_math1986;
#line 81
    sjt_dot1231 = _parent;
#line 95
    sjt_math1984 = (sjt_dot1231)->m31;
#line 95
    sjt_math1966 = sjt_math1983 * sjt_math1984;
#line 95
    sjt_math1963 = sjt_math1965 + sjt_math1966;
#line 81
    sjt_dot1232 = _parent;
#line 95
    sjt_math1989 = (sjt_dot1232)->m11;
#line 81
    sjt_dot1233 = _parent;
#line 95
    sjt_math1990 = (sjt_dot1233)->m20;
#line 95
    sjt_math1987 = sjt_math1989 * sjt_math1990;
#line 81
    sjt_dot1234 = _parent;
#line 95
    sjt_math1988 = (sjt_dot1234)->m32;
#line 95
    sjt_math1964 = sjt_math1987 * sjt_math1988;
#line 95
    sjt_math1961 = sjt_math1963 + sjt_math1964;
#line 81
    sjt_dot1235 = _parent;
#line 95
    sjt_math1993 = (sjt_dot1235)->m10;
#line 81
    sjt_dot1236 = _parent;
#line 95
    sjt_math1994 = (sjt_dot1236)->m21;
#line 95
    sjt_math1991 = sjt_math1993 * sjt_math1994;
#line 81
    sjt_dot1237 = _parent;
#line 95
    sjt_math1992 = (sjt_dot1237)->m32;
#line 95
    sjt_math1962 = sjt_math1991 * sjt_math1992;
#line 95
    sjv_t.m30 = sjt_math1961 - sjt_math1962;
#line 81
    sjt_dot1238 = _parent;
#line 96
    sjt_math2007 = (sjt_dot1238)->m01;
#line 81
    sjt_dot1239 = _parent;
#line 96
    sjt_math2008 = (sjt_dot1239)->m22;
#line 96
    sjt_math2005 = sjt_math2007 * sjt_math2008;
#line 81
    sjt_dot1240 = _parent;
#line 96
    sjt_math2006 = (sjt_dot1240)->m30;
#line 96
    sjt_math2003 = sjt_math2005 * sjt_math2006;
#line 81
    sjt_dot1241 = _parent;
#line 96
    sjt_math2011 = (sjt_dot1241)->m02;
#line 81
    sjt_dot1242 = _parent;
#line 96
    sjt_math2012 = (sjt_dot1242)->m21;
#line 96
    sjt_math2009 = sjt_math2011 * sjt_math2012;
#line 81
    sjt_dot1243 = _parent;
#line 96
    sjt_math2010 = (sjt_dot1243)->m30;
#line 96
    sjt_math2004 = sjt_math2009 * sjt_math2010;
#line 96
    sjt_math2001 = sjt_math2003 - sjt_math2004;
#line 81
    sjt_dot1244 = _parent;
#line 96
    sjt_math2015 = (sjt_dot1244)->m02;
#line 81
    sjt_dot1245 = _parent;
#line 96
    sjt_math2016 = (sjt_dot1245)->m20;
#line 96
    sjt_math2013 = sjt_math2015 * sjt_math2016;
#line 81
    sjt_dot1246 = _parent;
#line 96
    sjt_math2014 = (sjt_dot1246)->m31;
#line 96
    sjt_math2002 = sjt_math2013 * sjt_math2014;
#line 96
    sjt_math1999 = sjt_math2001 + sjt_math2002;
#line 81
    sjt_dot1247 = _parent;
#line 96
    sjt_math2019 = (sjt_dot1247)->m00;
#line 81
    sjt_dot1248 = _parent;
#line 96
    sjt_math2020 = (sjt_dot1248)->m22;
#line 96
    sjt_math2017 = sjt_math2019 * sjt_math2020;
#line 81
    sjt_dot1249 = _parent;
#line 96
    sjt_math2018 = (sjt_dot1249)->m31;
#line 96
    sjt_math2000 = sjt_math2017 * sjt_math2018;
#line 96
    sjt_math1997 = sjt_math1999 - sjt_math2000;
#line 81
    sjt_dot1250 = _parent;
#line 96
    sjt_math2023 = (sjt_dot1250)->m01;
#line 81
    sjt_dot1251 = _parent;
#line 96
    sjt_math2024 = (sjt_dot1251)->m20;
#line 96
    sjt_math2021 = sjt_math2023 * sjt_math2024;
#line 81
    sjt_dot1252 = _parent;
#line 96
    sjt_math2022 = (sjt_dot1252)->m32;
#line 96
    sjt_math1998 = sjt_math2021 * sjt_math2022;
#line 96
    sjt_math1995 = sjt_math1997 - sjt_math1998;
#line 81
    sjt_dot1253 = _parent;
#line 96
    sjt_math2027 = (sjt_dot1253)->m00;
#line 81
    sjt_dot1254 = _parent;
#line 96
    sjt_math2028 = (sjt_dot1254)->m21;
#line 96
    sjt_math2025 = sjt_math2027 * sjt_math2028;
#line 81
    sjt_dot1255 = _parent;
#line 96
    sjt_math2026 = (sjt_dot1255)->m32;
#line 96
    sjt_math1996 = sjt_math2025 * sjt_math2026;
#line 96
    sjv_t.m31 = sjt_math1995 + sjt_math1996;
#line 81
    sjt_dot1256 = _parent;
#line 97
    sjt_math2041 = (sjt_dot1256)->m02;
#line 81
    sjt_dot1257 = _parent;
#line 97
    sjt_math2042 = (sjt_dot1257)->m11;
#line 97
    sjt_math2039 = sjt_math2041 * sjt_math2042;
#line 81
    sjt_dot1258 = _parent;
#line 97
    sjt_math2040 = (sjt_dot1258)->m30;
#line 97
    sjt_math2037 = sjt_math2039 * sjt_math2040;
#line 81
    sjt_dot1259 = _parent;
#line 97
    sjt_math2045 = (sjt_dot1259)->m01;
#line 81
    sjt_dot1260 = _parent;
#line 97
    sjt_math2046 = (sjt_dot1260)->m12;
#line 97
    sjt_math2043 = sjt_math2045 * sjt_math2046;
#line 81
    sjt_dot1261 = _parent;
#line 97
    sjt_math2044 = (sjt_dot1261)->m30;
#line 97
    sjt_math2038 = sjt_math2043 * sjt_math2044;
#line 97
    sjt_math2035 = sjt_math2037 - sjt_math2038;
#line 81
    sjt_dot1262 = _parent;
#line 97
    sjt_math2049 = (sjt_dot1262)->m02;
#line 81
    sjt_dot1263 = _parent;
#line 97
    sjt_math2050 = (sjt_dot1263)->m10;
#line 97
    sjt_math2047 = sjt_math2049 * sjt_math2050;
#line 81
    sjt_dot1264 = _parent;
#line 97
    sjt_math2048 = (sjt_dot1264)->m31;
#line 97
    sjt_math2036 = sjt_math2047 * sjt_math2048;
#line 97
    sjt_math2033 = sjt_math2035 - sjt_math2036;
#line 81
    sjt_dot1265 = _parent;
#line 97
    sjt_math2053 = (sjt_dot1265)->m00;
#line 81
    sjt_dot1266 = _parent;
#line 97
    sjt_math2054 = (sjt_dot1266)->m12;
#line 97
    sjt_math2051 = sjt_math2053 * sjt_math2054;
#line 81
    sjt_dot1267 = _parent;
#line 97
    sjt_math2052 = (sjt_dot1267)->m31;
#line 97
    sjt_math2034 = sjt_math2051 * sjt_math2052;
#line 97
    sjt_math2031 = sjt_math2033 + sjt_math2034;
#line 81
    sjt_dot1268 = _parent;
#line 97
    sjt_math2057 = (sjt_dot1268)->m01;
#line 81
    sjt_dot1269 = _parent;
#line 97
    sjt_math2058 = (sjt_dot1269)->m10;
#line 97
    sjt_math2055 = sjt_math2057 * sjt_math2058;
#line 81
    sjt_dot1270 = _parent;
#line 97
    sjt_math2056 = (sjt_dot1270)->m32;
#line 97
    sjt_math2032 = sjt_math2055 * sjt_math2056;
#line 97
    sjt_math2029 = sjt_math2031 + sjt_math2032;
#line 81
    sjt_dot1271 = _parent;
#line 97
    sjt_math2061 = (sjt_dot1271)->m00;
#line 81
    sjt_dot1272 = _parent;
#line 97
    sjt_math2062 = (sjt_dot1272)->m11;
#line 97
    sjt_math2059 = sjt_math2061 * sjt_math2062;
#line 81
    sjt_dot1273 = _parent;
#line 97
    sjt_math2060 = (sjt_dot1273)->m32;
#line 97
    sjt_math2030 = sjt_math2059 * sjt_math2060;
#line 97
    sjv_t.m32 = sjt_math2029 - sjt_math2030;
#line 81
    sjt_dot1274 = _parent;
#line 98
    sjt_math2075 = (sjt_dot1274)->m01;
#line 81
    sjt_dot1275 = _parent;
#line 98
    sjt_math2076 = (sjt_dot1275)->m12;
#line 98
    sjt_math2073 = sjt_math2075 * sjt_math2076;
#line 81
    sjt_dot1276 = _parent;
#line 98
    sjt_math2074 = (sjt_dot1276)->m20;
#line 98
    sjt_math2071 = sjt_math2073 * sjt_math2074;
#line 81
    sjt_dot1277 = _parent;
#line 98
    sjt_math2079 = (sjt_dot1277)->m02;
#line 81
    sjt_dot1278 = _parent;
#line 98
    sjt_math2080 = (sjt_dot1278)->m11;
#line 98
    sjt_math2077 = sjt_math2079 * sjt_math2080;
#line 81
    sjt_dot1279 = _parent;
#line 98
    sjt_math2078 = (sjt_dot1279)->m20;
#line 98
    sjt_math2072 = sjt_math2077 * sjt_math2078;
#line 98
    sjt_math2069 = sjt_math2071 - sjt_math2072;
#line 81
    sjt_dot1280 = _parent;
#line 98
    sjt_math2083 = (sjt_dot1280)->m02;
#line 81
    sjt_dot1281 = _parent;
#line 98
    sjt_math2084 = (sjt_dot1281)->m10;
#line 98
    sjt_math2081 = sjt_math2083 * sjt_math2084;
#line 81
    sjt_dot1282 = _parent;
#line 98
    sjt_math2082 = (sjt_dot1282)->m21;
#line 98
    sjt_math2070 = sjt_math2081 * sjt_math2082;
#line 98
    sjt_math2067 = sjt_math2069 + sjt_math2070;
#line 81
    sjt_dot1283 = _parent;
#line 98
    sjt_math2087 = (sjt_dot1283)->m00;
#line 81
    sjt_dot1284 = _parent;
#line 98
    sjt_math2088 = (sjt_dot1284)->m12;
#line 98
    sjt_math2085 = sjt_math2087 * sjt_math2088;
#line 81
    sjt_dot1285 = _parent;
#line 98
    sjt_math2086 = (sjt_dot1285)->m21;
#line 98
    sjt_math2068 = sjt_math2085 * sjt_math2086;
#line 98
    sjt_math2065 = sjt_math2067 - sjt_math2068;
#line 81
    sjt_dot1286 = _parent;
#line 98
    sjt_math2091 = (sjt_dot1286)->m01;
#line 81
    sjt_dot1287 = _parent;
#line 98
    sjt_math2092 = (sjt_dot1287)->m10;
#line 98
    sjt_math2089 = sjt_math2091 * sjt_math2092;
#line 81
    sjt_dot1288 = _parent;
#line 98
    sjt_math2090 = (sjt_dot1288)->m22;
#line 98
    sjt_math2066 = sjt_math2089 * sjt_math2090;
#line 98
    sjt_math2063 = sjt_math2065 - sjt_math2066;
#line 81
    sjt_dot1289 = _parent;
#line 98
    sjt_math2095 = (sjt_dot1289)->m00;
#line 81
    sjt_dot1290 = _parent;
#line 98
    sjt_math2096 = (sjt_dot1290)->m11;
#line 98
    sjt_math2093 = sjt_math2095 * sjt_math2096;
#line 81
    sjt_dot1291 = _parent;
#line 98
    sjt_math2094 = (sjt_dot1291)->m22;
#line 98
    sjt_math2064 = sjt_math2093 * sjt_math2094;
#line 98
    sjv_t.m33 = sjt_math2063 + sjt_math2064;
#line 98
    sjf_mat4(&sjv_t);
#line 40
    sjt_parent52 = &sjv_t;
#line 101
    sjt_math2097 = 1.0f;
#line 101
    sjf_mat4_determinant(_parent, &sjt_math2098);
#line 101
    sjt_functionParam113 = sjt_math2097 / sjt_math2098;
#line 101
    sjf_mat4_multiply_f32_heap(sjt_parent52, sjt_functionParam113, _return);

    sjf_mat4_destroy(&sjv_t);
}

void sjf_mat4_lookAtLH(sjs_vec3* camera, sjs_vec3* target, sjs_vec3* up, sjs_mat4* _return) {
    sjs_vec3 sjt_call5;
    sjs_vec3* sjt_dot168;
    sjs_vec3* sjt_dot169;
    sjs_vec3* sjt_dot170;
    sjs_vec3* sjt_dot171;
    sjs_vec3* sjt_dot172;
    sjs_vec3* sjt_dot173;
    sjs_vec3* sjt_dot174;
    sjs_vec3* sjt_dot175;
    sjs_vec3* sjt_dot176;
    sjs_vec3* sjt_functionParam81;
    sjs_vec3* sjt_functionParam84;
    sjs_vec3* sjt_functionParam85;
    sjs_vec3* sjt_functionParam86;
    sjs_vec3* sjt_functionParam87;
    sjs_vec3* sjt_functionParam88;
    float sjt_math163;
    float sjt_math164;
    float sjt_math175;
    float sjt_math176;
    float sjt_math177;
    float sjt_math178;
    sjs_vec3* sjt_parent23;
    sjs_vec3* sjt_parent24;
    sjs_vec3* sjt_parent25;
    sjs_vec3* sjt_parent26;
    sjs_vec3* sjt_parent27;
    sjs_vec3* sjt_parent28;
    sjs_vec3* sjt_parent29;
    sjs_vec3* sjt_parent30;
    sjs_vec3 sjv_temp;
    sjs_vec3 sjv_xaxis;
    sjs_vec3 sjv_yaxis;
    sjs_vec3 sjv_zaxis;

#line 143 "lib/ui/mat4.sj"
    sjt_parent23 = target;
#line 143
    sjt_functionParam81 = camera;
#line 143
    sjf_vec3_subtract(sjt_parent23, sjt_functionParam81, &sjv_temp);
#line 38 "lib/ui/vec3.sj"
    sjt_parent24 = &sjv_temp;
#line 38
    sjf_vec3_normalize(sjt_parent24, &sjv_zaxis);
#line 143 "lib/ui/mat4.sj"
    sjt_parent26 = up;
#line 146
    sjt_functionParam84 = &sjv_zaxis;
#line 146
    sjf_vec3_cross(sjt_parent26, sjt_functionParam84, &sjt_call5);
#line 146
    sjt_parent25 = &sjt_call5;
#line 146
    sjf_vec3_normalize(sjt_parent25, &sjv_xaxis);
#line 47 "lib/ui/vec3.sj"
    sjt_parent27 = &sjv_zaxis;
#line 147 "lib/ui/mat4.sj"
    sjt_functionParam85 = &sjv_xaxis;
#line 147
    sjf_vec3_cross(sjt_parent27, sjt_functionParam85, &sjv_yaxis);
#line 1 "lib/ui/vec3.sj"
    sjt_dot168 = &sjv_xaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m00 = (sjt_dot168)->x;
#line 1 "lib/ui/vec3.sj"
    sjt_dot169 = &sjv_yaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m01 = (sjt_dot169)->x;
#line 1 "lib/ui/vec3.sj"
    sjt_dot170 = &sjv_zaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m02 = (sjt_dot170)->x;
#line 152
    _return->m03 = 0.0f;
#line 1 "lib/ui/vec3.sj"
    sjt_dot171 = &sjv_xaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m10 = (sjt_dot171)->y;
#line 1 "lib/ui/vec3.sj"
    sjt_dot172 = &sjv_yaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m11 = (sjt_dot172)->y;
#line 1 "lib/ui/vec3.sj"
    sjt_dot173 = &sjv_zaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m12 = (sjt_dot173)->y;
#line 156
    _return->m13 = 0.0f;
#line 1 "lib/ui/vec3.sj"
    sjt_dot174 = &sjv_xaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m20 = (sjt_dot174)->z;
#line 1 "lib/ui/vec3.sj"
    sjt_dot175 = &sjv_yaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m21 = (sjt_dot175)->z;
#line 1 "lib/ui/vec3.sj"
    sjt_dot176 = &sjv_zaxis;
#line 148 "lib/ui/mat4.sj"
    _return->m22 = (sjt_dot176)->z;
#line 160
    _return->m23 = 0.0f;
#line 161
    sjt_math163 = 0.0f;
#line 55 "lib/ui/vec3.sj"
    sjt_parent28 = &sjv_xaxis;
#line 143 "lib/ui/mat4.sj"
    sjt_functionParam86 = camera;
#line 143
    sjf_vec3_dot(sjt_parent28, sjt_functionParam86, &sjt_math164);
#line 161
    _return->m30 = sjt_math163 - sjt_math164;
#line 162
    sjt_math175 = 0.0f;
#line 55 "lib/ui/vec3.sj"
    sjt_parent29 = &sjv_yaxis;
#line 143 "lib/ui/mat4.sj"
    sjt_functionParam87 = camera;
#line 143
    sjf_vec3_dot(sjt_parent29, sjt_functionParam87, &sjt_math176);
#line 162
    _return->m31 = sjt_math175 - sjt_math176;
#line 163
    sjt_math177 = 0.0f;
#line 55 "lib/ui/vec3.sj"
    sjt_parent30 = &sjv_zaxis;
#line 143 "lib/ui/mat4.sj"
    sjt_functionParam88 = camera;
#line 143
    sjf_vec3_dot(sjt_parent30, sjt_functionParam88, &sjt_math178);
#line 163
    _return->m32 = sjt_math177 - sjt_math178;
#line 164
    _return->m33 = 1.0f;
#line 164
    sjf_mat4(_return);

    sjf_vec3_destroy(&sjt_call5);
    sjf_vec3_destroy(&sjv_temp);
    sjf_vec3_destroy(&sjv_xaxis);
    sjf_vec3_destroy(&sjv_yaxis);
    sjf_vec3_destroy(&sjv_zaxis);
}

void sjf_mat4_lookAtLH_heap(sjs_vec3* camera, sjs_vec3* target, sjs_vec3* up, sjs_mat4_heap** _return) {
    sjs_vec3 sjt_call6;
    sjs_vec3* sjt_dot183;
    sjs_vec3* sjt_dot184;
    sjs_vec3* sjt_dot185;
    sjs_vec3* sjt_dot186;
    sjs_vec3* sjt_dot187;
    sjs_vec3* sjt_dot188;
    sjs_vec3* sjt_dot189;
    sjs_vec3* sjt_dot190;
    sjs_vec3* sjt_dot191;
    sjs_vec3* sjt_functionParam89;
    sjs_vec3* sjt_functionParam90;
    sjs_vec3* sjt_functionParam91;
    sjs_vec3* sjt_functionParam92;
    sjs_vec3* sjt_functionParam93;
    sjs_vec3* sjt_functionParam94;
    float sjt_math179;
    float sjt_math180;
    float sjt_math181;
    float sjt_math182;
    float sjt_math183;
    float sjt_math184;
    sjs_vec3* sjt_parent31;
    sjs_vec3* sjt_parent32;
    sjs_vec3* sjt_parent33;
    sjs_vec3* sjt_parent34;
    sjs_vec3* sjt_parent35;
    sjs_vec3* sjt_parent36;
    sjs_vec3* sjt_parent37;
    sjs_vec3* sjt_parent38;
    sjs_vec3 sjv_temp;
    sjs_vec3 sjv_xaxis;
    sjs_vec3 sjv_yaxis;
    sjs_vec3 sjv_zaxis;

#line 143 "lib/ui/mat4.sj"
    sjt_parent31 = target;
#line 143
    sjt_functionParam89 = camera;
#line 143
    sjf_vec3_subtract(sjt_parent31, sjt_functionParam89, &sjv_temp);
#line 38 "lib/ui/vec3.sj"
    sjt_parent32 = &sjv_temp;
#line 38
    sjf_vec3_normalize(sjt_parent32, &sjv_zaxis);
#line 143 "lib/ui/mat4.sj"
    sjt_parent34 = up;
#line 146
    sjt_functionParam90 = &sjv_zaxis;
#line 146
    sjf_vec3_cross(sjt_parent34, sjt_functionParam90, &sjt_call6);
#line 146
    sjt_parent33 = &sjt_call6;
#line 146
    sjf_vec3_normalize(sjt_parent33, &sjv_xaxis);
#line 47 "lib/ui/vec3.sj"
    sjt_parent35 = &sjv_zaxis;
#line 147 "lib/ui/mat4.sj"
    sjt_functionParam91 = &sjv_xaxis;
#line 147
    sjf_vec3_cross(sjt_parent35, sjt_functionParam91, &sjv_yaxis);
#line 147
    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
#line 147
    (*_return)->_refCount = 1;
#line 1 "lib/ui/vec3.sj"
    sjt_dot183 = &sjv_xaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m00 = (sjt_dot183)->x;
#line 1 "lib/ui/vec3.sj"
    sjt_dot184 = &sjv_yaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m01 = (sjt_dot184)->x;
#line 1 "lib/ui/vec3.sj"
    sjt_dot185 = &sjv_zaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m02 = (sjt_dot185)->x;
#line 152
    (*_return)->m03 = 0.0f;
#line 1 "lib/ui/vec3.sj"
    sjt_dot186 = &sjv_xaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m10 = (sjt_dot186)->y;
#line 1 "lib/ui/vec3.sj"
    sjt_dot187 = &sjv_yaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m11 = (sjt_dot187)->y;
#line 1 "lib/ui/vec3.sj"
    sjt_dot188 = &sjv_zaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m12 = (sjt_dot188)->y;
#line 156
    (*_return)->m13 = 0.0f;
#line 1 "lib/ui/vec3.sj"
    sjt_dot189 = &sjv_xaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m20 = (sjt_dot189)->z;
#line 1 "lib/ui/vec3.sj"
    sjt_dot190 = &sjv_yaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m21 = (sjt_dot190)->z;
#line 1 "lib/ui/vec3.sj"
    sjt_dot191 = &sjv_zaxis;
#line 148 "lib/ui/mat4.sj"
    (*_return)->m22 = (sjt_dot191)->z;
#line 160
    (*_return)->m23 = 0.0f;
#line 161
    sjt_math179 = 0.0f;
#line 55 "lib/ui/vec3.sj"
    sjt_parent36 = &sjv_xaxis;
#line 143 "lib/ui/mat4.sj"
    sjt_functionParam92 = camera;
#line 143
    sjf_vec3_dot(sjt_parent36, sjt_functionParam92, &sjt_math180);
#line 161
    (*_return)->m30 = sjt_math179 - sjt_math180;
#line 162
    sjt_math181 = 0.0f;
#line 55 "lib/ui/vec3.sj"
    sjt_parent37 = &sjv_yaxis;
#line 143 "lib/ui/mat4.sj"
    sjt_functionParam93 = camera;
#line 143
    sjf_vec3_dot(sjt_parent37, sjt_functionParam93, &sjt_math182);
#line 162
    (*_return)->m31 = sjt_math181 - sjt_math182;
#line 163
    sjt_math183 = 0.0f;
#line 55 "lib/ui/vec3.sj"
    sjt_parent38 = &sjv_zaxis;
#line 143 "lib/ui/mat4.sj"
    sjt_functionParam94 = camera;
#line 143
    sjf_vec3_dot(sjt_parent38, sjt_functionParam94, &sjt_math184);
#line 163
    (*_return)->m32 = sjt_math183 - sjt_math184;
#line 164
    (*_return)->m33 = 1.0f;
#line 164
    sjf_mat4_heap((*_return));

    sjf_vec3_destroy(&sjt_call6);
    sjf_vec3_destroy(&sjv_temp);
    sjf_vec3_destroy(&sjv_xaxis);
    sjf_vec3_destroy(&sjv_yaxis);
    sjf_vec3_destroy(&sjv_zaxis);
}

void sjf_mat4_multiply(sjs_mat4* _parent, sjs_mat4* m, sjs_mat4* _return) {
    sjs_mat4* sjt_dot200;
    sjs_mat4* sjt_dot201;
    sjs_mat4* sjt_dot202;
    sjs_mat4* sjt_dot203;
    sjs_mat4* sjt_dot204;
    sjs_mat4* sjt_dot205;
    sjs_mat4* sjt_dot206;
    sjs_mat4* sjt_dot207;
    sjs_mat4* sjt_dot208;
    sjs_mat4* sjt_dot209;
    sjs_mat4* sjt_dot210;
    sjs_mat4* sjt_dot211;
    sjs_mat4* sjt_dot212;
    sjs_mat4* sjt_dot213;
    sjs_mat4* sjt_dot214;
    sjs_mat4* sjt_dot215;
    sjs_mat4* sjt_dot216;
    sjs_mat4* sjt_dot217;
    sjs_mat4* sjt_dot218;
    sjs_mat4* sjt_dot219;
    sjs_mat4* sjt_dot220;
    sjs_mat4* sjt_dot221;
    sjs_mat4* sjt_dot222;
    sjs_mat4* sjt_dot223;
    sjs_mat4* sjt_dot224;
    sjs_mat4* sjt_dot225;
    sjs_mat4* sjt_dot226;
    sjs_mat4* sjt_dot227;
    sjs_mat4* sjt_dot228;
    sjs_mat4* sjt_dot229;
    sjs_mat4* sjt_dot230;
    sjs_mat4* sjt_dot231;
    sjs_mat4* sjt_dot232;
    sjs_mat4* sjt_dot233;
    sjs_mat4* sjt_dot234;
    sjs_mat4* sjt_dot235;
    sjs_mat4* sjt_dot236;
    sjs_mat4* sjt_dot237;
    sjs_mat4* sjt_dot238;
    sjs_mat4* sjt_dot239;
    sjs_mat4* sjt_dot240;
    sjs_mat4* sjt_dot241;
    sjs_mat4* sjt_dot242;
    sjs_mat4* sjt_dot243;
    sjs_mat4* sjt_dot244;
    sjs_mat4* sjt_dot245;
    sjs_mat4* sjt_dot246;
    sjs_mat4* sjt_dot247;
    sjs_mat4* sjt_dot248;
    sjs_mat4* sjt_dot249;
    sjs_mat4* sjt_dot250;
    sjs_mat4* sjt_dot251;
    sjs_mat4* sjt_dot252;
    sjs_mat4* sjt_dot253;
    sjs_mat4* sjt_dot254;
    sjs_mat4* sjt_dot255;
    sjs_mat4* sjt_dot256;
    sjs_mat4* sjt_dot257;
    sjs_mat4* sjt_dot258;
    sjs_mat4* sjt_dot259;
    sjs_mat4* sjt_dot260;
    sjs_mat4* sjt_dot261;
    sjs_mat4* sjt_dot262;
    sjs_mat4* sjt_dot263;
    sjs_mat4* sjt_dot264;
    sjs_mat4* sjt_dot265;
    sjs_mat4* sjt_dot266;
    sjs_mat4* sjt_dot267;
    sjs_mat4* sjt_dot268;
    sjs_mat4* sjt_dot269;
    sjs_mat4* sjt_dot270;
    sjs_mat4* sjt_dot271;
    sjs_mat4* sjt_dot272;
    sjs_mat4* sjt_dot273;
    sjs_mat4* sjt_dot274;
    sjs_mat4* sjt_dot275;
    sjs_mat4* sjt_dot276;
    sjs_mat4* sjt_dot277;
    sjs_mat4* sjt_dot278;
    sjs_mat4* sjt_dot279;
    sjs_mat4* sjt_dot280;
    sjs_mat4* sjt_dot281;
    sjs_mat4* sjt_dot282;
    sjs_mat4* sjt_dot283;
    sjs_mat4* sjt_dot284;
    sjs_mat4* sjt_dot285;
    sjs_mat4* sjt_dot286;
    sjs_mat4* sjt_dot287;
    sjs_mat4* sjt_dot288;
    sjs_mat4* sjt_dot289;
    sjs_mat4* sjt_dot290;
    sjs_mat4* sjt_dot291;
    sjs_mat4* sjt_dot292;
    sjs_mat4* sjt_dot293;
    sjs_mat4* sjt_dot294;
    sjs_mat4* sjt_dot295;
    sjs_mat4* sjt_dot296;
    sjs_mat4* sjt_dot297;
    sjs_mat4* sjt_dot298;
    sjs_mat4* sjt_dot299;
    sjs_mat4* sjt_dot300;
    sjs_mat4* sjt_dot301;
    sjs_mat4* sjt_dot302;
    sjs_mat4* sjt_dot303;
    sjs_mat4* sjt_dot304;
    sjs_mat4* sjt_dot305;
    sjs_mat4* sjt_dot306;
    sjs_mat4* sjt_dot307;
    sjs_mat4* sjt_dot308;
    sjs_mat4* sjt_dot309;
    sjs_mat4* sjt_dot310;
    sjs_mat4* sjt_dot311;
    sjs_mat4* sjt_dot312;
    sjs_mat4* sjt_dot313;
    sjs_mat4* sjt_dot314;
    sjs_mat4* sjt_dot315;
    sjs_mat4* sjt_dot316;
    sjs_mat4* sjt_dot317;
    sjs_mat4* sjt_dot318;
    sjs_mat4* sjt_dot319;
    sjs_mat4* sjt_dot320;
    sjs_mat4* sjt_dot321;
    sjs_mat4* sjt_dot322;
    sjs_mat4* sjt_dot323;
    sjs_mat4* sjt_dot324;
    sjs_mat4* sjt_dot325;
    sjs_mat4* sjt_dot326;
    sjs_mat4* sjt_dot327;
    float sjt_math185;
    float sjt_math186;
    float sjt_math187;
    float sjt_math188;
    float sjt_math189;
    float sjt_math190;
    float sjt_math191;
    float sjt_math192;
    float sjt_math193;
    float sjt_math194;
    float sjt_math195;
    float sjt_math196;
    float sjt_math197;
    float sjt_math198;
    float sjt_math199;
    float sjt_math200;
    float sjt_math201;
    float sjt_math202;
    float sjt_math203;
    float sjt_math204;
    float sjt_math205;
    float sjt_math206;
    float sjt_math207;
    float sjt_math208;
    float sjt_math209;
    float sjt_math210;
    float sjt_math211;
    float sjt_math212;
    float sjt_math213;
    float sjt_math214;
    float sjt_math215;
    float sjt_math216;
    float sjt_math217;
    float sjt_math218;
    float sjt_math219;
    float sjt_math220;
    float sjt_math221;
    float sjt_math222;
    float sjt_math223;
    float sjt_math224;
    float sjt_math225;
    float sjt_math226;
    float sjt_math227;
    float sjt_math228;
    float sjt_math229;
    float sjt_math230;
    float sjt_math231;
    float sjt_math232;
    float sjt_math233;
    float sjt_math234;
    float sjt_math235;
    float sjt_math236;
    float sjt_math237;
    float sjt_math238;
    float sjt_math239;
    float sjt_math240;
    float sjt_math241;
    float sjt_math242;
    float sjt_math243;
    float sjt_math244;
    float sjt_math245;
    float sjt_math246;
    float sjt_math247;
    float sjt_math248;
    float sjt_math249;
    float sjt_math250;
    float sjt_math251;
    float sjt_math252;
    float sjt_math253;
    float sjt_math254;
    float sjt_math255;
    float sjt_math256;
    float sjt_math257;
    float sjt_math258;
    float sjt_math259;
    float sjt_math260;
    float sjt_math261;
    float sjt_math262;
    float sjt_math263;
    float sjt_math264;
    float sjt_math265;
    float sjt_math266;
    float sjt_math267;
    float sjt_math268;
    float sjt_math269;
    float sjt_math270;
    float sjt_math271;
    float sjt_math272;
    float sjt_math273;
    float sjt_math274;
    float sjt_math275;
    float sjt_math276;
    float sjt_math277;
    float sjt_math278;
    float sjt_math279;
    float sjt_math280;
    float sjt_math281;
    float sjt_math282;
    float sjt_math283;
    float sjt_math284;
    float sjt_math285;
    float sjt_math286;
    float sjt_math287;
    float sjt_math288;
    float sjt_math289;
    float sjt_math290;
    float sjt_math291;
    float sjt_math292;
    float sjt_math293;
    float sjt_math294;
    float sjt_math295;
    float sjt_math296;
    float sjt_math297;
    float sjt_math298;
    float sjt_math299;
    float sjt_math300;
    float sjt_math301;
    float sjt_math302;
    float sjt_math303;
    float sjt_math304;
    float sjt_math305;
    float sjt_math306;
    float sjt_math307;
    float sjt_math308;
    float sjt_math309;
    float sjt_math310;
    float sjt_math311;
    float sjt_math312;
    float sjt_math313;
    float sjt_math314;
    float sjt_math315;
    float sjt_math316;
    float sjt_math317;
    float sjt_math318;
    float sjt_math319;
    float sjt_math320;
    float sjt_math321;
    float sjt_math322;
    float sjt_math323;
    float sjt_math324;
    float sjt_math325;
    float sjt_math326;
    float sjt_math327;
    float sjt_math328;
    float sjt_math329;
    float sjt_math330;
    float sjt_math331;
    float sjt_math332;
    float sjt_math333;
    float sjt_math334;
    float sjt_math335;
    float sjt_math336;
    float sjt_math337;
    float sjt_math338;
    float sjt_math339;
    float sjt_math340;
    float sjt_math341;
    float sjt_math342;
    float sjt_math343;
    float sjt_math344;
    float sjt_math345;
    float sjt_math346;
    float sjt_math347;
    float sjt_math348;
    float sjt_math349;
    float sjt_math350;
    float sjt_math351;
    float sjt_math352;
    float sjt_math353;
    float sjt_math354;
    float sjt_math355;
    float sjt_math356;
    float sjt_math357;
    float sjt_math358;
    float sjt_math359;
    float sjt_math360;
    float sjt_math361;
    float sjt_math362;
    float sjt_math363;
    float sjt_math364;
    float sjt_math365;
    float sjt_math366;
    float sjt_math367;
    float sjt_math368;
    float sjt_math369;
    float sjt_math370;
    float sjt_math371;
    float sjt_math372;
    float sjt_math373;
    float sjt_math374;
    float sjt_math375;
    float sjt_math376;
    float sjt_math377;
    float sjt_math378;
    float sjt_math379;
    float sjt_math380;
    float sjt_math381;
    float sjt_math382;
    float sjt_math383;
    float sjt_math384;
    float sjt_math385;
    float sjt_math386;
    float sjt_math387;
    float sjt_math388;
    float sjt_math389;
    float sjt_math390;
    float sjt_math391;
    float sjt_math392;
    float sjt_math393;
    float sjt_math394;
    float sjt_math395;
    float sjt_math396;
    float sjt_math397;
    float sjt_math398;
    float sjt_math399;
    float sjt_math400;
    float sjt_math401;
    float sjt_math402;
    float sjt_math403;
    float sjt_math404;
    float sjt_math405;
    float sjt_math406;
    float sjt_math407;
    float sjt_math408;

#line 19 "lib/ui/mat4.sj"
    sjt_dot200 = m;
#line 21
    sjt_math191 = (sjt_dot200)->m00;
#line 19
    sjt_dot201 = _parent;
#line 21
    sjt_math192 = (sjt_dot201)->m00;
#line 21
    sjt_math189 = sjt_math191 * sjt_math192;
#line 19
    sjt_dot202 = m;
#line 21
    sjt_math193 = (sjt_dot202)->m01;
#line 19
    sjt_dot203 = _parent;
#line 21
    sjt_math194 = (sjt_dot203)->m10;
#line 21
    sjt_math190 = sjt_math193 * sjt_math194;
#line 21
    sjt_math187 = sjt_math189 + sjt_math190;
#line 19
    sjt_dot204 = m;
#line 21
    sjt_math195 = (sjt_dot204)->m02;
#line 19
    sjt_dot205 = _parent;
#line 21
    sjt_math196 = (sjt_dot205)->m20;
#line 21
    sjt_math188 = sjt_math195 * sjt_math196;
#line 21
    sjt_math185 = sjt_math187 + sjt_math188;
#line 19
    sjt_dot206 = m;
#line 21
    sjt_math197 = (sjt_dot206)->m03;
#line 19
    sjt_dot207 = _parent;
#line 21
    sjt_math198 = (sjt_dot207)->m30;
#line 21
    sjt_math186 = sjt_math197 * sjt_math198;
#line 21
    _return->m00 = sjt_math185 + sjt_math186;
#line 19
    sjt_dot208 = m;
#line 22
    sjt_math205 = (sjt_dot208)->m00;
#line 19
    sjt_dot209 = _parent;
#line 22
    sjt_math206 = (sjt_dot209)->m01;
#line 22
    sjt_math203 = sjt_math205 * sjt_math206;
#line 19
    sjt_dot210 = m;
#line 22
    sjt_math207 = (sjt_dot210)->m01;
#line 19
    sjt_dot211 = _parent;
#line 22
    sjt_math208 = (sjt_dot211)->m11;
#line 22
    sjt_math204 = sjt_math207 * sjt_math208;
#line 22
    sjt_math201 = sjt_math203 + sjt_math204;
#line 19
    sjt_dot212 = m;
#line 22
    sjt_math209 = (sjt_dot212)->m02;
#line 19
    sjt_dot213 = _parent;
#line 22
    sjt_math210 = (sjt_dot213)->m21;
#line 22
    sjt_math202 = sjt_math209 * sjt_math210;
#line 22
    sjt_math199 = sjt_math201 + sjt_math202;
#line 19
    sjt_dot214 = m;
#line 22
    sjt_math211 = (sjt_dot214)->m03;
#line 19
    sjt_dot215 = _parent;
#line 22
    sjt_math212 = (sjt_dot215)->m31;
#line 22
    sjt_math200 = sjt_math211 * sjt_math212;
#line 22
    _return->m01 = sjt_math199 + sjt_math200;
#line 19
    sjt_dot216 = m;
#line 23
    sjt_math219 = (sjt_dot216)->m00;
#line 19
    sjt_dot217 = _parent;
#line 23
    sjt_math220 = (sjt_dot217)->m02;
#line 23
    sjt_math217 = sjt_math219 * sjt_math220;
#line 19
    sjt_dot218 = m;
#line 23
    sjt_math221 = (sjt_dot218)->m01;
#line 19
    sjt_dot219 = _parent;
#line 23
    sjt_math222 = (sjt_dot219)->m12;
#line 23
    sjt_math218 = sjt_math221 * sjt_math222;
#line 23
    sjt_math215 = sjt_math217 + sjt_math218;
#line 19
    sjt_dot220 = m;
#line 23
    sjt_math223 = (sjt_dot220)->m02;
#line 19
    sjt_dot221 = _parent;
#line 23
    sjt_math224 = (sjt_dot221)->m22;
#line 23
    sjt_math216 = sjt_math223 * sjt_math224;
#line 23
    sjt_math213 = sjt_math215 + sjt_math216;
#line 19
    sjt_dot222 = m;
#line 23
    sjt_math225 = (sjt_dot222)->m03;
#line 19
    sjt_dot223 = _parent;
#line 23
    sjt_math226 = (sjt_dot223)->m32;
#line 23
    sjt_math214 = sjt_math225 * sjt_math226;
#line 23
    _return->m02 = sjt_math213 + sjt_math214;
#line 19
    sjt_dot224 = m;
#line 24
    sjt_math233 = (sjt_dot224)->m00;
#line 19
    sjt_dot225 = _parent;
#line 24
    sjt_math234 = (sjt_dot225)->m03;
#line 24
    sjt_math231 = sjt_math233 * sjt_math234;
#line 19
    sjt_dot226 = m;
#line 24
    sjt_math235 = (sjt_dot226)->m01;
#line 19
    sjt_dot227 = _parent;
#line 24
    sjt_math236 = (sjt_dot227)->m13;
#line 24
    sjt_math232 = sjt_math235 * sjt_math236;
#line 24
    sjt_math229 = sjt_math231 + sjt_math232;
#line 19
    sjt_dot228 = m;
#line 24
    sjt_math237 = (sjt_dot228)->m02;
#line 19
    sjt_dot229 = _parent;
#line 24
    sjt_math238 = (sjt_dot229)->m23;
#line 24
    sjt_math230 = sjt_math237 * sjt_math238;
#line 24
    sjt_math227 = sjt_math229 + sjt_math230;
#line 19
    sjt_dot230 = m;
#line 24
    sjt_math239 = (sjt_dot230)->m03;
#line 19
    sjt_dot231 = _parent;
#line 24
    sjt_math240 = (sjt_dot231)->m33;
#line 24
    sjt_math228 = sjt_math239 * sjt_math240;
#line 24
    _return->m03 = sjt_math227 + sjt_math228;
#line 19
    sjt_dot232 = m;
#line 25
    sjt_math247 = (sjt_dot232)->m10;
#line 19
    sjt_dot233 = _parent;
#line 25
    sjt_math248 = (sjt_dot233)->m00;
#line 25
    sjt_math245 = sjt_math247 * sjt_math248;
#line 19
    sjt_dot234 = m;
#line 25
    sjt_math249 = (sjt_dot234)->m11;
#line 19
    sjt_dot235 = _parent;
#line 25
    sjt_math250 = (sjt_dot235)->m10;
#line 25
    sjt_math246 = sjt_math249 * sjt_math250;
#line 25
    sjt_math243 = sjt_math245 + sjt_math246;
#line 19
    sjt_dot236 = m;
#line 25
    sjt_math251 = (sjt_dot236)->m12;
#line 19
    sjt_dot237 = _parent;
#line 25
    sjt_math252 = (sjt_dot237)->m20;
#line 25
    sjt_math244 = sjt_math251 * sjt_math252;
#line 25
    sjt_math241 = sjt_math243 + sjt_math244;
#line 19
    sjt_dot238 = m;
#line 25
    sjt_math253 = (sjt_dot238)->m13;
#line 19
    sjt_dot239 = _parent;
#line 25
    sjt_math254 = (sjt_dot239)->m30;
#line 25
    sjt_math242 = sjt_math253 * sjt_math254;
#line 25
    _return->m10 = sjt_math241 + sjt_math242;
#line 19
    sjt_dot240 = m;
#line 26
    sjt_math261 = (sjt_dot240)->m10;
#line 19
    sjt_dot241 = _parent;
#line 26
    sjt_math262 = (sjt_dot241)->m01;
#line 26
    sjt_math259 = sjt_math261 * sjt_math262;
#line 19
    sjt_dot242 = m;
#line 26
    sjt_math263 = (sjt_dot242)->m11;
#line 19
    sjt_dot243 = _parent;
#line 26
    sjt_math264 = (sjt_dot243)->m11;
#line 26
    sjt_math260 = sjt_math263 * sjt_math264;
#line 26
    sjt_math257 = sjt_math259 + sjt_math260;
#line 19
    sjt_dot244 = m;
#line 26
    sjt_math265 = (sjt_dot244)->m12;
#line 19
    sjt_dot245 = _parent;
#line 26
    sjt_math266 = (sjt_dot245)->m21;
#line 26
    sjt_math258 = sjt_math265 * sjt_math266;
#line 26
    sjt_math255 = sjt_math257 + sjt_math258;
#line 19
    sjt_dot246 = m;
#line 26
    sjt_math267 = (sjt_dot246)->m13;
#line 19
    sjt_dot247 = _parent;
#line 26
    sjt_math268 = (sjt_dot247)->m31;
#line 26
    sjt_math256 = sjt_math267 * sjt_math268;
#line 26
    _return->m11 = sjt_math255 + sjt_math256;
#line 19
    sjt_dot248 = m;
#line 27
    sjt_math275 = (sjt_dot248)->m10;
#line 19
    sjt_dot249 = _parent;
#line 27
    sjt_math276 = (sjt_dot249)->m02;
#line 27
    sjt_math273 = sjt_math275 * sjt_math276;
#line 19
    sjt_dot250 = m;
#line 27
    sjt_math277 = (sjt_dot250)->m11;
#line 19
    sjt_dot251 = _parent;
#line 27
    sjt_math278 = (sjt_dot251)->m12;
#line 27
    sjt_math274 = sjt_math277 * sjt_math278;
#line 27
    sjt_math271 = sjt_math273 + sjt_math274;
#line 19
    sjt_dot252 = m;
#line 27
    sjt_math279 = (sjt_dot252)->m12;
#line 19
    sjt_dot253 = _parent;
#line 27
    sjt_math280 = (sjt_dot253)->m22;
#line 27
    sjt_math272 = sjt_math279 * sjt_math280;
#line 27
    sjt_math269 = sjt_math271 + sjt_math272;
#line 19
    sjt_dot254 = m;
#line 27
    sjt_math281 = (sjt_dot254)->m13;
#line 19
    sjt_dot255 = _parent;
#line 27
    sjt_math282 = (sjt_dot255)->m32;
#line 27
    sjt_math270 = sjt_math281 * sjt_math282;
#line 27
    _return->m12 = sjt_math269 + sjt_math270;
#line 19
    sjt_dot256 = m;
#line 28
    sjt_math289 = (sjt_dot256)->m10;
#line 19
    sjt_dot257 = _parent;
#line 28
    sjt_math290 = (sjt_dot257)->m03;
#line 28
    sjt_math287 = sjt_math289 * sjt_math290;
#line 19
    sjt_dot258 = m;
#line 28
    sjt_math291 = (sjt_dot258)->m11;
#line 19
    sjt_dot259 = _parent;
#line 28
    sjt_math292 = (sjt_dot259)->m13;
#line 28
    sjt_math288 = sjt_math291 * sjt_math292;
#line 28
    sjt_math285 = sjt_math287 + sjt_math288;
#line 19
    sjt_dot260 = m;
#line 28
    sjt_math293 = (sjt_dot260)->m12;
#line 19
    sjt_dot261 = _parent;
#line 28
    sjt_math294 = (sjt_dot261)->m23;
#line 28
    sjt_math286 = sjt_math293 * sjt_math294;
#line 28
    sjt_math283 = sjt_math285 + sjt_math286;
#line 19
    sjt_dot262 = m;
#line 28
    sjt_math295 = (sjt_dot262)->m13;
#line 19
    sjt_dot263 = _parent;
#line 28
    sjt_math296 = (sjt_dot263)->m33;
#line 28
    sjt_math284 = sjt_math295 * sjt_math296;
#line 28
    _return->m13 = sjt_math283 + sjt_math284;
#line 19
    sjt_dot264 = m;
#line 29
    sjt_math303 = (sjt_dot264)->m20;
#line 19
    sjt_dot265 = _parent;
#line 29
    sjt_math304 = (sjt_dot265)->m00;
#line 29
    sjt_math301 = sjt_math303 * sjt_math304;
#line 19
    sjt_dot266 = m;
#line 29
    sjt_math305 = (sjt_dot266)->m21;
#line 19
    sjt_dot267 = _parent;
#line 29
    sjt_math306 = (sjt_dot267)->m10;
#line 29
    sjt_math302 = sjt_math305 * sjt_math306;
#line 29
    sjt_math299 = sjt_math301 + sjt_math302;
#line 19
    sjt_dot268 = m;
#line 29
    sjt_math307 = (sjt_dot268)->m22;
#line 19
    sjt_dot269 = _parent;
#line 29
    sjt_math308 = (sjt_dot269)->m20;
#line 29
    sjt_math300 = sjt_math307 * sjt_math308;
#line 29
    sjt_math297 = sjt_math299 + sjt_math300;
#line 19
    sjt_dot270 = m;
#line 29
    sjt_math309 = (sjt_dot270)->m23;
#line 19
    sjt_dot271 = _parent;
#line 29
    sjt_math310 = (sjt_dot271)->m30;
#line 29
    sjt_math298 = sjt_math309 * sjt_math310;
#line 29
    _return->m20 = sjt_math297 + sjt_math298;
#line 19
    sjt_dot272 = m;
#line 30
    sjt_math317 = (sjt_dot272)->m20;
#line 19
    sjt_dot273 = _parent;
#line 30
    sjt_math318 = (sjt_dot273)->m01;
#line 30
    sjt_math315 = sjt_math317 * sjt_math318;
#line 19
    sjt_dot274 = m;
#line 30
    sjt_math319 = (sjt_dot274)->m21;
#line 19
    sjt_dot275 = _parent;
#line 30
    sjt_math320 = (sjt_dot275)->m11;
#line 30
    sjt_math316 = sjt_math319 * sjt_math320;
#line 30
    sjt_math313 = sjt_math315 + sjt_math316;
#line 19
    sjt_dot276 = m;
#line 30
    sjt_math321 = (sjt_dot276)->m22;
#line 19
    sjt_dot277 = _parent;
#line 30
    sjt_math322 = (sjt_dot277)->m21;
#line 30
    sjt_math314 = sjt_math321 * sjt_math322;
#line 30
    sjt_math311 = sjt_math313 + sjt_math314;
#line 19
    sjt_dot278 = m;
#line 30
    sjt_math323 = (sjt_dot278)->m23;
#line 19
    sjt_dot279 = _parent;
#line 30
    sjt_math324 = (sjt_dot279)->m31;
#line 30
    sjt_math312 = sjt_math323 * sjt_math324;
#line 30
    _return->m21 = sjt_math311 + sjt_math312;
#line 19
    sjt_dot280 = m;
#line 31
    sjt_math331 = (sjt_dot280)->m20;
#line 19
    sjt_dot281 = _parent;
#line 31
    sjt_math332 = (sjt_dot281)->m02;
#line 31
    sjt_math329 = sjt_math331 * sjt_math332;
#line 19
    sjt_dot282 = m;
#line 31
    sjt_math333 = (sjt_dot282)->m21;
#line 19
    sjt_dot283 = _parent;
#line 31
    sjt_math334 = (sjt_dot283)->m12;
#line 31
    sjt_math330 = sjt_math333 * sjt_math334;
#line 31
    sjt_math327 = sjt_math329 + sjt_math330;
#line 19
    sjt_dot284 = m;
#line 31
    sjt_math335 = (sjt_dot284)->m22;
#line 19
    sjt_dot285 = _parent;
#line 31
    sjt_math336 = (sjt_dot285)->m22;
#line 31
    sjt_math328 = sjt_math335 * sjt_math336;
#line 31
    sjt_math325 = sjt_math327 + sjt_math328;
#line 19
    sjt_dot286 = m;
#line 31
    sjt_math337 = (sjt_dot286)->m23;
#line 19
    sjt_dot287 = _parent;
#line 31
    sjt_math338 = (sjt_dot287)->m32;
#line 31
    sjt_math326 = sjt_math337 * sjt_math338;
#line 31
    _return->m22 = sjt_math325 + sjt_math326;
#line 19
    sjt_dot288 = m;
#line 32
    sjt_math345 = (sjt_dot288)->m20;
#line 19
    sjt_dot289 = _parent;
#line 32
    sjt_math346 = (sjt_dot289)->m03;
#line 32
    sjt_math343 = sjt_math345 * sjt_math346;
#line 19
    sjt_dot290 = m;
#line 32
    sjt_math347 = (sjt_dot290)->m21;
#line 19
    sjt_dot291 = _parent;
#line 32
    sjt_math348 = (sjt_dot291)->m13;
#line 32
    sjt_math344 = sjt_math347 * sjt_math348;
#line 32
    sjt_math341 = sjt_math343 + sjt_math344;
#line 19
    sjt_dot292 = m;
#line 32
    sjt_math349 = (sjt_dot292)->m22;
#line 19
    sjt_dot293 = _parent;
#line 32
    sjt_math350 = (sjt_dot293)->m23;
#line 32
    sjt_math342 = sjt_math349 * sjt_math350;
#line 32
    sjt_math339 = sjt_math341 + sjt_math342;
#line 19
    sjt_dot294 = m;
#line 32
    sjt_math351 = (sjt_dot294)->m23;
#line 19
    sjt_dot295 = _parent;
#line 32
    sjt_math352 = (sjt_dot295)->m33;
#line 32
    sjt_math340 = sjt_math351 * sjt_math352;
#line 32
    _return->m23 = sjt_math339 + sjt_math340;
#line 19
    sjt_dot296 = m;
#line 33
    sjt_math359 = (sjt_dot296)->m30;
#line 19
    sjt_dot297 = _parent;
#line 33
    sjt_math360 = (sjt_dot297)->m00;
#line 33
    sjt_math357 = sjt_math359 * sjt_math360;
#line 19
    sjt_dot298 = m;
#line 33
    sjt_math361 = (sjt_dot298)->m31;
#line 19
    sjt_dot299 = _parent;
#line 33
    sjt_math362 = (sjt_dot299)->m10;
#line 33
    sjt_math358 = sjt_math361 * sjt_math362;
#line 33
    sjt_math355 = sjt_math357 + sjt_math358;
#line 19
    sjt_dot300 = m;
#line 33
    sjt_math363 = (sjt_dot300)->m32;
#line 19
    sjt_dot301 = _parent;
#line 33
    sjt_math364 = (sjt_dot301)->m20;
#line 33
    sjt_math356 = sjt_math363 * sjt_math364;
#line 33
    sjt_math353 = sjt_math355 + sjt_math356;
#line 19
    sjt_dot302 = m;
#line 33
    sjt_math365 = (sjt_dot302)->m33;
#line 19
    sjt_dot303 = _parent;
#line 33
    sjt_math366 = (sjt_dot303)->m30;
#line 33
    sjt_math354 = sjt_math365 * sjt_math366;
#line 33
    _return->m30 = sjt_math353 + sjt_math354;
#line 19
    sjt_dot304 = m;
#line 34
    sjt_math373 = (sjt_dot304)->m30;
#line 19
    sjt_dot305 = _parent;
#line 34
    sjt_math374 = (sjt_dot305)->m01;
#line 34
    sjt_math371 = sjt_math373 * sjt_math374;
#line 19
    sjt_dot306 = m;
#line 34
    sjt_math375 = (sjt_dot306)->m31;
#line 19
    sjt_dot307 = _parent;
#line 34
    sjt_math376 = (sjt_dot307)->m11;
#line 34
    sjt_math372 = sjt_math375 * sjt_math376;
#line 34
    sjt_math369 = sjt_math371 + sjt_math372;
#line 19
    sjt_dot308 = m;
#line 34
    sjt_math377 = (sjt_dot308)->m32;
#line 19
    sjt_dot309 = _parent;
#line 34
    sjt_math378 = (sjt_dot309)->m21;
#line 34
    sjt_math370 = sjt_math377 * sjt_math378;
#line 34
    sjt_math367 = sjt_math369 + sjt_math370;
#line 19
    sjt_dot310 = m;
#line 34
    sjt_math379 = (sjt_dot310)->m33;
#line 19
    sjt_dot311 = _parent;
#line 34
    sjt_math380 = (sjt_dot311)->m31;
#line 34
    sjt_math368 = sjt_math379 * sjt_math380;
#line 34
    _return->m31 = sjt_math367 + sjt_math368;
#line 19
    sjt_dot312 = m;
#line 35
    sjt_math387 = (sjt_dot312)->m30;
#line 19
    sjt_dot313 = _parent;
#line 35
    sjt_math388 = (sjt_dot313)->m02;
#line 35
    sjt_math385 = sjt_math387 * sjt_math388;
#line 19
    sjt_dot314 = m;
#line 35
    sjt_math389 = (sjt_dot314)->m31;
#line 19
    sjt_dot315 = _parent;
#line 35
    sjt_math390 = (sjt_dot315)->m12;
#line 35
    sjt_math386 = sjt_math389 * sjt_math390;
#line 35
    sjt_math383 = sjt_math385 + sjt_math386;
#line 19
    sjt_dot316 = m;
#line 35
    sjt_math391 = (sjt_dot316)->m32;
#line 19
    sjt_dot317 = _parent;
#line 35
    sjt_math392 = (sjt_dot317)->m22;
#line 35
    sjt_math384 = sjt_math391 * sjt_math392;
#line 35
    sjt_math381 = sjt_math383 + sjt_math384;
#line 19
    sjt_dot318 = m;
#line 35
    sjt_math393 = (sjt_dot318)->m33;
#line 19
    sjt_dot319 = _parent;
#line 35
    sjt_math394 = (sjt_dot319)->m32;
#line 35
    sjt_math382 = sjt_math393 * sjt_math394;
#line 35
    _return->m32 = sjt_math381 + sjt_math382;
#line 19
    sjt_dot320 = m;
#line 36
    sjt_math401 = (sjt_dot320)->m30;
#line 19
    sjt_dot321 = _parent;
#line 36
    sjt_math402 = (sjt_dot321)->m03;
#line 36
    sjt_math399 = sjt_math401 * sjt_math402;
#line 19
    sjt_dot322 = m;
#line 36
    sjt_math403 = (sjt_dot322)->m31;
#line 19
    sjt_dot323 = _parent;
#line 36
    sjt_math404 = (sjt_dot323)->m13;
#line 36
    sjt_math400 = sjt_math403 * sjt_math404;
#line 36
    sjt_math397 = sjt_math399 + sjt_math400;
#line 19
    sjt_dot324 = m;
#line 36
    sjt_math405 = (sjt_dot324)->m32;
#line 19
    sjt_dot325 = _parent;
#line 36
    sjt_math406 = (sjt_dot325)->m23;
#line 36
    sjt_math398 = sjt_math405 * sjt_math406;
#line 36
    sjt_math395 = sjt_math397 + sjt_math398;
#line 19
    sjt_dot326 = m;
#line 36
    sjt_math407 = (sjt_dot326)->m33;
#line 19
    sjt_dot327 = _parent;
#line 36
    sjt_math408 = (sjt_dot327)->m33;
#line 36
    sjt_math396 = sjt_math407 * sjt_math408;
#line 36
    _return->m33 = sjt_math395 + sjt_math396;
#line 36
    sjf_mat4(_return);
}

void sjf_mat4_multiplyVec4(sjs_mat4* _parent, sjs_vec4* v, sjs_vec4* _return) {
    sjs_mat4* sjt_dot459;
    sjs_vec4* sjt_dot460;
    sjs_mat4* sjt_dot461;
    sjs_vec4* sjt_dot462;
    sjs_mat4* sjt_dot463;
    sjs_vec4* sjt_dot464;
    sjs_mat4* sjt_dot465;
    sjs_vec4* sjt_dot466;
    sjs_mat4* sjt_dot467;
    sjs_vec4* sjt_dot468;
    sjs_mat4* sjt_dot469;
    sjs_vec4* sjt_dot470;
    sjs_mat4* sjt_dot471;
    sjs_vec4* sjt_dot472;
    sjs_mat4* sjt_dot473;
    sjs_vec4* sjt_dot474;
    sjs_mat4* sjt_dot475;
    sjs_vec4* sjt_dot476;
    sjs_mat4* sjt_dot477;
    sjs_vec4* sjt_dot478;
    sjs_mat4* sjt_dot479;
    sjs_vec4* sjt_dot480;
    sjs_mat4* sjt_dot481;
    sjs_vec4* sjt_dot482;
    sjs_mat4* sjt_dot483;
    sjs_vec4* sjt_dot484;
    sjs_mat4* sjt_dot485;
    sjs_vec4* sjt_dot486;
    sjs_mat4* sjt_dot487;
    sjs_vec4* sjt_dot488;
    sjs_mat4* sjt_dot489;
    sjs_vec4* sjt_dot490;
    float sjt_math633;
    float sjt_math634;
    float sjt_math635;
    float sjt_math636;
    float sjt_math637;
    float sjt_math638;
    float sjt_math639;
    float sjt_math640;
    float sjt_math641;
    float sjt_math642;
    float sjt_math643;
    float sjt_math644;
    float sjt_math645;
    float sjt_math646;
    float sjt_math647;
    float sjt_math648;
    float sjt_math649;
    float sjt_math650;
    float sjt_math651;
    float sjt_math652;
    float sjt_math653;
    float sjt_math654;
    float sjt_math655;
    float sjt_math656;
    float sjt_math657;
    float sjt_math658;
    float sjt_math659;
    float sjt_math660;
    float sjt_math661;
    float sjt_math662;
    float sjt_math663;
    float sjt_math664;
    float sjt_math665;
    float sjt_math666;
    float sjt_math667;
    float sjt_math668;
    float sjt_math669;
    float sjt_math670;
    float sjt_math671;
    float sjt_math672;
    float sjt_math673;
    float sjt_math674;
    float sjt_math675;
    float sjt_math676;
    float sjt_math677;
    float sjt_math678;
    float sjt_math679;
    float sjt_math680;
    float sjt_math681;
    float sjt_math682;
    float sjt_math683;
    float sjt_math684;
    float sjt_math685;
    float sjt_math686;
    float sjt_math687;
    float sjt_math688;

#line 62 "lib/ui/mat4.sj"
    sjt_dot459 = _parent;
#line 64
    sjt_math639 = (sjt_dot459)->m00;
#line 62
    sjt_dot460 = v;
#line 64
    sjt_math640 = (sjt_dot460)->x;
#line 64
    sjt_math637 = sjt_math639 * sjt_math640;
#line 62
    sjt_dot461 = _parent;
#line 64
    sjt_math641 = (sjt_dot461)->m10;
#line 62
    sjt_dot462 = v;
#line 64
    sjt_math642 = (sjt_dot462)->y;
#line 64
    sjt_math638 = sjt_math641 * sjt_math642;
#line 64
    sjt_math635 = sjt_math637 + sjt_math638;
#line 62
    sjt_dot463 = _parent;
#line 64
    sjt_math643 = (sjt_dot463)->m20;
#line 62
    sjt_dot464 = v;
#line 64
    sjt_math644 = (sjt_dot464)->z;
#line 64
    sjt_math636 = sjt_math643 * sjt_math644;
#line 64
    sjt_math633 = sjt_math635 + sjt_math636;
#line 62
    sjt_dot465 = _parent;
#line 64
    sjt_math645 = (sjt_dot465)->m30;
#line 62
    sjt_dot466 = v;
#line 64
    sjt_math646 = (sjt_dot466)->w;
#line 64
    sjt_math634 = sjt_math645 * sjt_math646;
#line 64
    _return->x = sjt_math633 + sjt_math634;
#line 62
    sjt_dot467 = _parent;
#line 65
    sjt_math653 = (sjt_dot467)->m01;
#line 62
    sjt_dot468 = v;
#line 65
    sjt_math654 = (sjt_dot468)->x;
#line 65
    sjt_math651 = sjt_math653 * sjt_math654;
#line 62
    sjt_dot469 = _parent;
#line 65
    sjt_math655 = (sjt_dot469)->m11;
#line 62
    sjt_dot470 = v;
#line 65
    sjt_math656 = (sjt_dot470)->y;
#line 65
    sjt_math652 = sjt_math655 * sjt_math656;
#line 65
    sjt_math649 = sjt_math651 + sjt_math652;
#line 62
    sjt_dot471 = _parent;
#line 65
    sjt_math657 = (sjt_dot471)->m21;
#line 62
    sjt_dot472 = v;
#line 65
    sjt_math658 = (sjt_dot472)->z;
#line 65
    sjt_math650 = sjt_math657 * sjt_math658;
#line 65
    sjt_math647 = sjt_math649 + sjt_math650;
#line 62
    sjt_dot473 = _parent;
#line 65
    sjt_math659 = (sjt_dot473)->m31;
#line 62
    sjt_dot474 = v;
#line 65
    sjt_math660 = (sjt_dot474)->w;
#line 65
    sjt_math648 = sjt_math659 * sjt_math660;
#line 65
    _return->y = sjt_math647 + sjt_math648;
#line 62
    sjt_dot475 = _parent;
#line 66
    sjt_math667 = (sjt_dot475)->m02;
#line 62
    sjt_dot476 = v;
#line 66
    sjt_math668 = (sjt_dot476)->x;
#line 66
    sjt_math665 = sjt_math667 * sjt_math668;
#line 62
    sjt_dot477 = _parent;
#line 66
    sjt_math669 = (sjt_dot477)->m12;
#line 62
    sjt_dot478 = v;
#line 66
    sjt_math670 = (sjt_dot478)->y;
#line 66
    sjt_math666 = sjt_math669 * sjt_math670;
#line 66
    sjt_math663 = sjt_math665 + sjt_math666;
#line 62
    sjt_dot479 = _parent;
#line 66
    sjt_math671 = (sjt_dot479)->m22;
#line 62
    sjt_dot480 = v;
#line 66
    sjt_math672 = (sjt_dot480)->z;
#line 66
    sjt_math664 = sjt_math671 * sjt_math672;
#line 66
    sjt_math661 = sjt_math663 + sjt_math664;
#line 62
    sjt_dot481 = _parent;
#line 66
    sjt_math673 = (sjt_dot481)->m32;
#line 62
    sjt_dot482 = v;
#line 66
    sjt_math674 = (sjt_dot482)->w;
#line 66
    sjt_math662 = sjt_math673 * sjt_math674;
#line 66
    _return->z = sjt_math661 + sjt_math662;
#line 62
    sjt_dot483 = _parent;
#line 67
    sjt_math681 = (sjt_dot483)->m03;
#line 62
    sjt_dot484 = v;
#line 67
    sjt_math682 = (sjt_dot484)->x;
#line 67
    sjt_math679 = sjt_math681 * sjt_math682;
#line 62
    sjt_dot485 = _parent;
#line 67
    sjt_math683 = (sjt_dot485)->m13;
#line 62
    sjt_dot486 = v;
#line 67
    sjt_math684 = (sjt_dot486)->y;
#line 67
    sjt_math680 = sjt_math683 * sjt_math684;
#line 67
    sjt_math677 = sjt_math679 + sjt_math680;
#line 62
    sjt_dot487 = _parent;
#line 67
    sjt_math685 = (sjt_dot487)->m23;
#line 62
    sjt_dot488 = v;
#line 67
    sjt_math686 = (sjt_dot488)->z;
#line 67
    sjt_math678 = sjt_math685 * sjt_math686;
#line 67
    sjt_math675 = sjt_math677 + sjt_math678;
#line 62
    sjt_dot489 = _parent;
#line 67
    sjt_math687 = (sjt_dot489)->m33;
#line 62
    sjt_dot490 = v;
#line 67
    sjt_math688 = (sjt_dot490)->w;
#line 67
    sjt_math676 = sjt_math687 * sjt_math688;
#line 67
    _return->w = sjt_math675 + sjt_math676;
#line 67
    sjf_vec4(_return);
}

void sjf_mat4_multiplyVec4_heap(sjs_mat4* _parent, sjs_vec4* v, sjs_vec4_heap** _return) {
    sjs_mat4* sjt_dot491;
    sjs_vec4* sjt_dot492;
    sjs_mat4* sjt_dot493;
    sjs_vec4* sjt_dot494;
    sjs_mat4* sjt_dot495;
    sjs_vec4* sjt_dot496;
    sjs_mat4* sjt_dot497;
    sjs_vec4* sjt_dot498;
    sjs_mat4* sjt_dot499;
    sjs_vec4* sjt_dot500;
    sjs_mat4* sjt_dot501;
    sjs_vec4* sjt_dot502;
    sjs_mat4* sjt_dot503;
    sjs_vec4* sjt_dot504;
    sjs_mat4* sjt_dot505;
    sjs_vec4* sjt_dot506;
    sjs_mat4* sjt_dot507;
    sjs_vec4* sjt_dot508;
    sjs_mat4* sjt_dot509;
    sjs_vec4* sjt_dot510;
    sjs_mat4* sjt_dot511;
    sjs_vec4* sjt_dot512;
    sjs_mat4* sjt_dot513;
    sjs_vec4* sjt_dot514;
    sjs_mat4* sjt_dot515;
    sjs_vec4* sjt_dot516;
    sjs_mat4* sjt_dot517;
    sjs_vec4* sjt_dot518;
    sjs_mat4* sjt_dot519;
    sjs_vec4* sjt_dot520;
    sjs_mat4* sjt_dot521;
    sjs_vec4* sjt_dot522;
    float sjt_math689;
    float sjt_math690;
    float sjt_math691;
    float sjt_math692;
    float sjt_math693;
    float sjt_math694;
    float sjt_math695;
    float sjt_math696;
    float sjt_math697;
    float sjt_math698;
    float sjt_math699;
    float sjt_math700;
    float sjt_math701;
    float sjt_math702;
    float sjt_math703;
    float sjt_math704;
    float sjt_math705;
    float sjt_math706;
    float sjt_math707;
    float sjt_math708;
    float sjt_math709;
    float sjt_math710;
    float sjt_math711;
    float sjt_math712;
    float sjt_math713;
    float sjt_math714;
    float sjt_math715;
    float sjt_math716;
    float sjt_math717;
    float sjt_math718;
    float sjt_math719;
    float sjt_math720;
    float sjt_math721;
    float sjt_math722;
    float sjt_math723;
    float sjt_math724;
    float sjt_math725;
    float sjt_math726;
    float sjt_math727;
    float sjt_math728;
    float sjt_math729;
    float sjt_math730;
    float sjt_math731;
    float sjt_math732;
    float sjt_math733;
    float sjt_math734;
    float sjt_math735;
    float sjt_math736;
    float sjt_math737;
    float sjt_math738;
    float sjt_math739;
    float sjt_math740;
    float sjt_math741;
    float sjt_math742;
    float sjt_math743;
    float sjt_math744;

    (*_return) = (sjs_vec4_heap*)malloc(sizeof(sjs_vec4_heap));
    (*_return)->_refCount = 1;
#line 62 "lib/ui/mat4.sj"
    sjt_dot491 = _parent;
#line 64
    sjt_math695 = (sjt_dot491)->m00;
#line 62
    sjt_dot492 = v;
#line 64
    sjt_math696 = (sjt_dot492)->x;
#line 64
    sjt_math693 = sjt_math695 * sjt_math696;
#line 62
    sjt_dot493 = _parent;
#line 64
    sjt_math697 = (sjt_dot493)->m10;
#line 62
    sjt_dot494 = v;
#line 64
    sjt_math698 = (sjt_dot494)->y;
#line 64
    sjt_math694 = sjt_math697 * sjt_math698;
#line 64
    sjt_math691 = sjt_math693 + sjt_math694;
#line 62
    sjt_dot495 = _parent;
#line 64
    sjt_math699 = (sjt_dot495)->m20;
#line 62
    sjt_dot496 = v;
#line 64
    sjt_math700 = (sjt_dot496)->z;
#line 64
    sjt_math692 = sjt_math699 * sjt_math700;
#line 64
    sjt_math689 = sjt_math691 + sjt_math692;
#line 62
    sjt_dot497 = _parent;
#line 64
    sjt_math701 = (sjt_dot497)->m30;
#line 62
    sjt_dot498 = v;
#line 64
    sjt_math702 = (sjt_dot498)->w;
#line 64
    sjt_math690 = sjt_math701 * sjt_math702;
#line 64
    (*_return)->x = sjt_math689 + sjt_math690;
#line 62
    sjt_dot499 = _parent;
#line 65
    sjt_math709 = (sjt_dot499)->m01;
#line 62
    sjt_dot500 = v;
#line 65
    sjt_math710 = (sjt_dot500)->x;
#line 65
    sjt_math707 = sjt_math709 * sjt_math710;
#line 62
    sjt_dot501 = _parent;
#line 65
    sjt_math711 = (sjt_dot501)->m11;
#line 62
    sjt_dot502 = v;
#line 65
    sjt_math712 = (sjt_dot502)->y;
#line 65
    sjt_math708 = sjt_math711 * sjt_math712;
#line 65
    sjt_math705 = sjt_math707 + sjt_math708;
#line 62
    sjt_dot503 = _parent;
#line 65
    sjt_math713 = (sjt_dot503)->m21;
#line 62
    sjt_dot504 = v;
#line 65
    sjt_math714 = (sjt_dot504)->z;
#line 65
    sjt_math706 = sjt_math713 * sjt_math714;
#line 65
    sjt_math703 = sjt_math705 + sjt_math706;
#line 62
    sjt_dot505 = _parent;
#line 65
    sjt_math715 = (sjt_dot505)->m31;
#line 62
    sjt_dot506 = v;
#line 65
    sjt_math716 = (sjt_dot506)->w;
#line 65
    sjt_math704 = sjt_math715 * sjt_math716;
#line 65
    (*_return)->y = sjt_math703 + sjt_math704;
#line 62
    sjt_dot507 = _parent;
#line 66
    sjt_math723 = (sjt_dot507)->m02;
#line 62
    sjt_dot508 = v;
#line 66
    sjt_math724 = (sjt_dot508)->x;
#line 66
    sjt_math721 = sjt_math723 * sjt_math724;
#line 62
    sjt_dot509 = _parent;
#line 66
    sjt_math725 = (sjt_dot509)->m12;
#line 62
    sjt_dot510 = v;
#line 66
    sjt_math726 = (sjt_dot510)->y;
#line 66
    sjt_math722 = sjt_math725 * sjt_math726;
#line 66
    sjt_math719 = sjt_math721 + sjt_math722;
#line 62
    sjt_dot511 = _parent;
#line 66
    sjt_math727 = (sjt_dot511)->m22;
#line 62
    sjt_dot512 = v;
#line 66
    sjt_math728 = (sjt_dot512)->z;
#line 66
    sjt_math720 = sjt_math727 * sjt_math728;
#line 66
    sjt_math717 = sjt_math719 + sjt_math720;
#line 62
    sjt_dot513 = _parent;
#line 66
    sjt_math729 = (sjt_dot513)->m32;
#line 62
    sjt_dot514 = v;
#line 66
    sjt_math730 = (sjt_dot514)->w;
#line 66
    sjt_math718 = sjt_math729 * sjt_math730;
#line 66
    (*_return)->z = sjt_math717 + sjt_math718;
#line 62
    sjt_dot515 = _parent;
#line 67
    sjt_math737 = (sjt_dot515)->m03;
#line 62
    sjt_dot516 = v;
#line 67
    sjt_math738 = (sjt_dot516)->x;
#line 67
    sjt_math735 = sjt_math737 * sjt_math738;
#line 62
    sjt_dot517 = _parent;
#line 67
    sjt_math739 = (sjt_dot517)->m13;
#line 62
    sjt_dot518 = v;
#line 67
    sjt_math740 = (sjt_dot518)->y;
#line 67
    sjt_math736 = sjt_math739 * sjt_math740;
#line 67
    sjt_math733 = sjt_math735 + sjt_math736;
#line 62
    sjt_dot519 = _parent;
#line 67
    sjt_math741 = (sjt_dot519)->m23;
#line 62
    sjt_dot520 = v;
#line 67
    sjt_math742 = (sjt_dot520)->z;
#line 67
    sjt_math734 = sjt_math741 * sjt_math742;
#line 67
    sjt_math731 = sjt_math733 + sjt_math734;
#line 62
    sjt_dot521 = _parent;
#line 67
    sjt_math743 = (sjt_dot521)->m33;
#line 62
    sjt_dot522 = v;
#line 67
    sjt_math744 = (sjt_dot522)->w;
#line 67
    sjt_math732 = sjt_math743 * sjt_math744;
#line 67
    (*_return)->w = sjt_math731 + sjt_math732;
#line 67
    sjf_vec4_heap((*_return));
}

void sjf_mat4_multiply_f32(sjs_mat4* _parent, float x, sjs_mat4* _return) {
    sjs_mat4* sjt_dot876;
    sjs_mat4* sjt_dot877;
    sjs_mat4* sjt_dot878;
    sjs_mat4* sjt_dot879;
    sjs_mat4* sjt_dot880;
    sjs_mat4* sjt_dot881;
    sjs_mat4* sjt_dot882;
    sjs_mat4* sjt_dot883;
    sjs_mat4* sjt_dot884;
    sjs_mat4* sjt_dot885;
    sjs_mat4* sjt_dot886;
    sjs_mat4* sjt_dot887;
    sjs_mat4* sjt_dot888;
    sjs_mat4* sjt_dot889;
    sjs_mat4* sjt_dot890;
    sjs_mat4* sjt_dot891;
    float sjt_math1297;
    float sjt_math1298;
    float sjt_math1299;
    float sjt_math1300;
    float sjt_math1301;
    float sjt_math1302;
    float sjt_math1303;
    float sjt_math1304;
    float sjt_math1305;
    float sjt_math1306;
    float sjt_math1307;
    float sjt_math1308;
    float sjt_math1309;
    float sjt_math1310;
    float sjt_math1311;
    float sjt_math1312;
    float sjt_math1313;
    float sjt_math1314;
    float sjt_math1315;
    float sjt_math1316;
    float sjt_math1317;
    float sjt_math1318;
    float sjt_math1319;
    float sjt_math1320;
    float sjt_math1321;
    float sjt_math1322;
    float sjt_math1323;
    float sjt_math1324;
    float sjt_math1325;
    float sjt_math1326;
    float sjt_math1327;
    float sjt_math1328;

#line 40 "lib/ui/mat4.sj"
    sjt_dot876 = _parent;
#line 42
    sjt_math1297 = (sjt_dot876)->m00;
#line 40
    sjt_math1298 = x;
#line 42
    _return->m00 = sjt_math1297 * sjt_math1298;
#line 40
    sjt_dot877 = _parent;
#line 43
    sjt_math1299 = (sjt_dot877)->m01;
#line 40
    sjt_math1300 = x;
#line 43
    _return->m01 = sjt_math1299 * sjt_math1300;
#line 40
    sjt_dot878 = _parent;
#line 44
    sjt_math1301 = (sjt_dot878)->m02;
#line 40
    sjt_math1302 = x;
#line 44
    _return->m02 = sjt_math1301 * sjt_math1302;
#line 40
    sjt_dot879 = _parent;
#line 45
    sjt_math1303 = (sjt_dot879)->m03;
#line 40
    sjt_math1304 = x;
#line 45
    _return->m03 = sjt_math1303 * sjt_math1304;
#line 40
    sjt_dot880 = _parent;
#line 46
    sjt_math1305 = (sjt_dot880)->m10;
#line 40
    sjt_math1306 = x;
#line 46
    _return->m10 = sjt_math1305 * sjt_math1306;
#line 40
    sjt_dot881 = _parent;
#line 47
    sjt_math1307 = (sjt_dot881)->m11;
#line 40
    sjt_math1308 = x;
#line 47
    _return->m11 = sjt_math1307 * sjt_math1308;
#line 40
    sjt_dot882 = _parent;
#line 48
    sjt_math1309 = (sjt_dot882)->m12;
#line 40
    sjt_math1310 = x;
#line 48
    _return->m12 = sjt_math1309 * sjt_math1310;
#line 40
    sjt_dot883 = _parent;
#line 49
    sjt_math1311 = (sjt_dot883)->m13;
#line 40
    sjt_math1312 = x;
#line 49
    _return->m13 = sjt_math1311 * sjt_math1312;
#line 40
    sjt_dot884 = _parent;
#line 50
    sjt_math1313 = (sjt_dot884)->m20;
#line 40
    sjt_math1314 = x;
#line 50
    _return->m20 = sjt_math1313 * sjt_math1314;
#line 40
    sjt_dot885 = _parent;
#line 51
    sjt_math1315 = (sjt_dot885)->m21;
#line 40
    sjt_math1316 = x;
#line 51
    _return->m21 = sjt_math1315 * sjt_math1316;
#line 40
    sjt_dot886 = _parent;
#line 52
    sjt_math1317 = (sjt_dot886)->m22;
#line 40
    sjt_math1318 = x;
#line 52
    _return->m22 = sjt_math1317 * sjt_math1318;
#line 40
    sjt_dot887 = _parent;
#line 53
    sjt_math1319 = (sjt_dot887)->m23;
#line 40
    sjt_math1320 = x;
#line 53
    _return->m23 = sjt_math1319 * sjt_math1320;
#line 40
    sjt_dot888 = _parent;
#line 54
    sjt_math1321 = (sjt_dot888)->m30;
#line 40
    sjt_math1322 = x;
#line 54
    _return->m30 = sjt_math1321 * sjt_math1322;
#line 40
    sjt_dot889 = _parent;
#line 55
    sjt_math1323 = (sjt_dot889)->m31;
#line 40
    sjt_math1324 = x;
#line 55
    _return->m31 = sjt_math1323 * sjt_math1324;
#line 40
    sjt_dot890 = _parent;
#line 56
    sjt_math1325 = (sjt_dot890)->m32;
#line 40
    sjt_math1326 = x;
#line 56
    _return->m32 = sjt_math1325 * sjt_math1326;
#line 40
    sjt_dot891 = _parent;
#line 57
    sjt_math1327 = (sjt_dot891)->m33;
#line 40
    sjt_math1328 = x;
#line 57
    _return->m33 = sjt_math1327 * sjt_math1328;
#line 57
    sjf_mat4(_return);
}

void sjf_mat4_multiply_f32_heap(sjs_mat4* _parent, float x, sjs_mat4_heap** _return) {
    sjs_mat4* sjt_dot892;
    sjs_mat4* sjt_dot893;
    sjs_mat4* sjt_dot894;
    sjs_mat4* sjt_dot895;
    sjs_mat4* sjt_dot896;
    sjs_mat4* sjt_dot897;
    sjs_mat4* sjt_dot898;
    sjs_mat4* sjt_dot899;
    sjs_mat4* sjt_dot900;
    sjs_mat4* sjt_dot901;
    sjs_mat4* sjt_dot902;
    sjs_mat4* sjt_dot903;
    sjs_mat4* sjt_dot904;
    sjs_mat4* sjt_dot905;
    sjs_mat4* sjt_dot906;
    sjs_mat4* sjt_dot907;
    float sjt_math1329;
    float sjt_math1330;
    float sjt_math1331;
    float sjt_math1332;
    float sjt_math1333;
    float sjt_math1334;
    float sjt_math1335;
    float sjt_math1336;
    float sjt_math1337;
    float sjt_math1338;
    float sjt_math1339;
    float sjt_math1340;
    float sjt_math1341;
    float sjt_math1342;
    float sjt_math1343;
    float sjt_math1344;
    float sjt_math1345;
    float sjt_math1346;
    float sjt_math1347;
    float sjt_math1348;
    float sjt_math1349;
    float sjt_math1350;
    float sjt_math1351;
    float sjt_math1352;
    float sjt_math1353;
    float sjt_math1354;
    float sjt_math1355;
    float sjt_math1356;
    float sjt_math1357;
    float sjt_math1358;
    float sjt_math1359;
    float sjt_math1360;

    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
    (*_return)->_refCount = 1;
#line 40 "lib/ui/mat4.sj"
    sjt_dot892 = _parent;
#line 42
    sjt_math1329 = (sjt_dot892)->m00;
#line 40
    sjt_math1330 = x;
#line 42
    (*_return)->m00 = sjt_math1329 * sjt_math1330;
#line 40
    sjt_dot893 = _parent;
#line 43
    sjt_math1331 = (sjt_dot893)->m01;
#line 40
    sjt_math1332 = x;
#line 43
    (*_return)->m01 = sjt_math1331 * sjt_math1332;
#line 40
    sjt_dot894 = _parent;
#line 44
    sjt_math1333 = (sjt_dot894)->m02;
#line 40
    sjt_math1334 = x;
#line 44
    (*_return)->m02 = sjt_math1333 * sjt_math1334;
#line 40
    sjt_dot895 = _parent;
#line 45
    sjt_math1335 = (sjt_dot895)->m03;
#line 40
    sjt_math1336 = x;
#line 45
    (*_return)->m03 = sjt_math1335 * sjt_math1336;
#line 40
    sjt_dot896 = _parent;
#line 46
    sjt_math1337 = (sjt_dot896)->m10;
#line 40
    sjt_math1338 = x;
#line 46
    (*_return)->m10 = sjt_math1337 * sjt_math1338;
#line 40
    sjt_dot897 = _parent;
#line 47
    sjt_math1339 = (sjt_dot897)->m11;
#line 40
    sjt_math1340 = x;
#line 47
    (*_return)->m11 = sjt_math1339 * sjt_math1340;
#line 40
    sjt_dot898 = _parent;
#line 48
    sjt_math1341 = (sjt_dot898)->m12;
#line 40
    sjt_math1342 = x;
#line 48
    (*_return)->m12 = sjt_math1341 * sjt_math1342;
#line 40
    sjt_dot899 = _parent;
#line 49
    sjt_math1343 = (sjt_dot899)->m13;
#line 40
    sjt_math1344 = x;
#line 49
    (*_return)->m13 = sjt_math1343 * sjt_math1344;
#line 40
    sjt_dot900 = _parent;
#line 50
    sjt_math1345 = (sjt_dot900)->m20;
#line 40
    sjt_math1346 = x;
#line 50
    (*_return)->m20 = sjt_math1345 * sjt_math1346;
#line 40
    sjt_dot901 = _parent;
#line 51
    sjt_math1347 = (sjt_dot901)->m21;
#line 40
    sjt_math1348 = x;
#line 51
    (*_return)->m21 = sjt_math1347 * sjt_math1348;
#line 40
    sjt_dot902 = _parent;
#line 52
    sjt_math1349 = (sjt_dot902)->m22;
#line 40
    sjt_math1350 = x;
#line 52
    (*_return)->m22 = sjt_math1349 * sjt_math1350;
#line 40
    sjt_dot903 = _parent;
#line 53
    sjt_math1351 = (sjt_dot903)->m23;
#line 40
    sjt_math1352 = x;
#line 53
    (*_return)->m23 = sjt_math1351 * sjt_math1352;
#line 40
    sjt_dot904 = _parent;
#line 54
    sjt_math1353 = (sjt_dot904)->m30;
#line 40
    sjt_math1354 = x;
#line 54
    (*_return)->m30 = sjt_math1353 * sjt_math1354;
#line 40
    sjt_dot905 = _parent;
#line 55
    sjt_math1355 = (sjt_dot905)->m31;
#line 40
    sjt_math1356 = x;
#line 55
    (*_return)->m31 = sjt_math1355 * sjt_math1356;
#line 40
    sjt_dot906 = _parent;
#line 56
    sjt_math1357 = (sjt_dot906)->m32;
#line 40
    sjt_math1358 = x;
#line 56
    (*_return)->m32 = sjt_math1357 * sjt_math1358;
#line 40
    sjt_dot907 = _parent;
#line 57
    sjt_math1359 = (sjt_dot907)->m33;
#line 40
    sjt_math1360 = x;
#line 57
    (*_return)->m33 = sjt_math1359 * sjt_math1360;
#line 57
    sjf_mat4_heap((*_return));
}

void sjf_mat4_multiply_heap(sjs_mat4* _parent, sjs_mat4* m, sjs_mat4_heap** _return) {
    sjs_mat4* sjt_dot328;
    sjs_mat4* sjt_dot329;
    sjs_mat4* sjt_dot330;
    sjs_mat4* sjt_dot331;
    sjs_mat4* sjt_dot332;
    sjs_mat4* sjt_dot333;
    sjs_mat4* sjt_dot334;
    sjs_mat4* sjt_dot335;
    sjs_mat4* sjt_dot336;
    sjs_mat4* sjt_dot337;
    sjs_mat4* sjt_dot338;
    sjs_mat4* sjt_dot339;
    sjs_mat4* sjt_dot340;
    sjs_mat4* sjt_dot341;
    sjs_mat4* sjt_dot342;
    sjs_mat4* sjt_dot343;
    sjs_mat4* sjt_dot344;
    sjs_mat4* sjt_dot345;
    sjs_mat4* sjt_dot346;
    sjs_mat4* sjt_dot347;
    sjs_mat4* sjt_dot348;
    sjs_mat4* sjt_dot349;
    sjs_mat4* sjt_dot350;
    sjs_mat4* sjt_dot351;
    sjs_mat4* sjt_dot352;
    sjs_mat4* sjt_dot353;
    sjs_mat4* sjt_dot354;
    sjs_mat4* sjt_dot355;
    sjs_mat4* sjt_dot356;
    sjs_mat4* sjt_dot357;
    sjs_mat4* sjt_dot358;
    sjs_mat4* sjt_dot359;
    sjs_mat4* sjt_dot360;
    sjs_mat4* sjt_dot361;
    sjs_mat4* sjt_dot362;
    sjs_mat4* sjt_dot363;
    sjs_mat4* sjt_dot364;
    sjs_mat4* sjt_dot365;
    sjs_mat4* sjt_dot366;
    sjs_mat4* sjt_dot367;
    sjs_mat4* sjt_dot368;
    sjs_mat4* sjt_dot369;
    sjs_mat4* sjt_dot370;
    sjs_mat4* sjt_dot371;
    sjs_mat4* sjt_dot372;
    sjs_mat4* sjt_dot373;
    sjs_mat4* sjt_dot374;
    sjs_mat4* sjt_dot375;
    sjs_mat4* sjt_dot376;
    sjs_mat4* sjt_dot377;
    sjs_mat4* sjt_dot378;
    sjs_mat4* sjt_dot379;
    sjs_mat4* sjt_dot380;
    sjs_mat4* sjt_dot381;
    sjs_mat4* sjt_dot382;
    sjs_mat4* sjt_dot383;
    sjs_mat4* sjt_dot384;
    sjs_mat4* sjt_dot385;
    sjs_mat4* sjt_dot386;
    sjs_mat4* sjt_dot387;
    sjs_mat4* sjt_dot388;
    sjs_mat4* sjt_dot389;
    sjs_mat4* sjt_dot390;
    sjs_mat4* sjt_dot391;
    sjs_mat4* sjt_dot392;
    sjs_mat4* sjt_dot393;
    sjs_mat4* sjt_dot394;
    sjs_mat4* sjt_dot395;
    sjs_mat4* sjt_dot396;
    sjs_mat4* sjt_dot397;
    sjs_mat4* sjt_dot398;
    sjs_mat4* sjt_dot399;
    sjs_mat4* sjt_dot400;
    sjs_mat4* sjt_dot401;
    sjs_mat4* sjt_dot402;
    sjs_mat4* sjt_dot403;
    sjs_mat4* sjt_dot404;
    sjs_mat4* sjt_dot405;
    sjs_mat4* sjt_dot406;
    sjs_mat4* sjt_dot407;
    sjs_mat4* sjt_dot408;
    sjs_mat4* sjt_dot409;
    sjs_mat4* sjt_dot410;
    sjs_mat4* sjt_dot411;
    sjs_mat4* sjt_dot412;
    sjs_mat4* sjt_dot413;
    sjs_mat4* sjt_dot414;
    sjs_mat4* sjt_dot415;
    sjs_mat4* sjt_dot416;
    sjs_mat4* sjt_dot417;
    sjs_mat4* sjt_dot418;
    sjs_mat4* sjt_dot419;
    sjs_mat4* sjt_dot420;
    sjs_mat4* sjt_dot421;
    sjs_mat4* sjt_dot422;
    sjs_mat4* sjt_dot423;
    sjs_mat4* sjt_dot424;
    sjs_mat4* sjt_dot425;
    sjs_mat4* sjt_dot426;
    sjs_mat4* sjt_dot427;
    sjs_mat4* sjt_dot428;
    sjs_mat4* sjt_dot429;
    sjs_mat4* sjt_dot430;
    sjs_mat4* sjt_dot431;
    sjs_mat4* sjt_dot432;
    sjs_mat4* sjt_dot433;
    sjs_mat4* sjt_dot434;
    sjs_mat4* sjt_dot435;
    sjs_mat4* sjt_dot436;
    sjs_mat4* sjt_dot437;
    sjs_mat4* sjt_dot438;
    sjs_mat4* sjt_dot439;
    sjs_mat4* sjt_dot440;
    sjs_mat4* sjt_dot441;
    sjs_mat4* sjt_dot442;
    sjs_mat4* sjt_dot443;
    sjs_mat4* sjt_dot444;
    sjs_mat4* sjt_dot445;
    sjs_mat4* sjt_dot446;
    sjs_mat4* sjt_dot447;
    sjs_mat4* sjt_dot448;
    sjs_mat4* sjt_dot449;
    sjs_mat4* sjt_dot450;
    sjs_mat4* sjt_dot451;
    sjs_mat4* sjt_dot452;
    sjs_mat4* sjt_dot453;
    sjs_mat4* sjt_dot454;
    sjs_mat4* sjt_dot455;
    float sjt_math409;
    float sjt_math410;
    float sjt_math411;
    float sjt_math412;
    float sjt_math413;
    float sjt_math414;
    float sjt_math415;
    float sjt_math416;
    float sjt_math417;
    float sjt_math418;
    float sjt_math419;
    float sjt_math420;
    float sjt_math421;
    float sjt_math422;
    float sjt_math423;
    float sjt_math424;
    float sjt_math425;
    float sjt_math426;
    float sjt_math427;
    float sjt_math428;
    float sjt_math429;
    float sjt_math430;
    float sjt_math431;
    float sjt_math432;
    float sjt_math433;
    float sjt_math434;
    float sjt_math435;
    float sjt_math436;
    float sjt_math437;
    float sjt_math438;
    float sjt_math439;
    float sjt_math440;
    float sjt_math441;
    float sjt_math442;
    float sjt_math443;
    float sjt_math444;
    float sjt_math445;
    float sjt_math446;
    float sjt_math447;
    float sjt_math448;
    float sjt_math449;
    float sjt_math450;
    float sjt_math451;
    float sjt_math452;
    float sjt_math453;
    float sjt_math454;
    float sjt_math455;
    float sjt_math456;
    float sjt_math457;
    float sjt_math458;
    float sjt_math459;
    float sjt_math460;
    float sjt_math461;
    float sjt_math462;
    float sjt_math463;
    float sjt_math464;
    float sjt_math465;
    float sjt_math466;
    float sjt_math467;
    float sjt_math468;
    float sjt_math469;
    float sjt_math470;
    float sjt_math471;
    float sjt_math472;
    float sjt_math473;
    float sjt_math474;
    float sjt_math475;
    float sjt_math476;
    float sjt_math477;
    float sjt_math478;
    float sjt_math479;
    float sjt_math480;
    float sjt_math481;
    float sjt_math482;
    float sjt_math483;
    float sjt_math484;
    float sjt_math485;
    float sjt_math486;
    float sjt_math487;
    float sjt_math488;
    float sjt_math489;
    float sjt_math490;
    float sjt_math491;
    float sjt_math492;
    float sjt_math493;
    float sjt_math494;
    float sjt_math495;
    float sjt_math496;
    float sjt_math497;
    float sjt_math498;
    float sjt_math499;
    float sjt_math500;
    float sjt_math501;
    float sjt_math502;
    float sjt_math503;
    float sjt_math504;
    float sjt_math505;
    float sjt_math506;
    float sjt_math507;
    float sjt_math508;
    float sjt_math509;
    float sjt_math510;
    float sjt_math511;
    float sjt_math512;
    float sjt_math513;
    float sjt_math514;
    float sjt_math515;
    float sjt_math516;
    float sjt_math517;
    float sjt_math518;
    float sjt_math519;
    float sjt_math520;
    float sjt_math521;
    float sjt_math522;
    float sjt_math523;
    float sjt_math524;
    float sjt_math525;
    float sjt_math526;
    float sjt_math527;
    float sjt_math528;
    float sjt_math529;
    float sjt_math530;
    float sjt_math531;
    float sjt_math532;
    float sjt_math533;
    float sjt_math534;
    float sjt_math535;
    float sjt_math536;
    float sjt_math537;
    float sjt_math538;
    float sjt_math539;
    float sjt_math540;
    float sjt_math541;
    float sjt_math542;
    float sjt_math543;
    float sjt_math544;
    float sjt_math545;
    float sjt_math546;
    float sjt_math547;
    float sjt_math548;
    float sjt_math549;
    float sjt_math550;
    float sjt_math551;
    float sjt_math552;
    float sjt_math553;
    float sjt_math554;
    float sjt_math555;
    float sjt_math556;
    float sjt_math557;
    float sjt_math558;
    float sjt_math559;
    float sjt_math560;
    float sjt_math561;
    float sjt_math562;
    float sjt_math563;
    float sjt_math564;
    float sjt_math565;
    float sjt_math566;
    float sjt_math567;
    float sjt_math568;
    float sjt_math569;
    float sjt_math570;
    float sjt_math571;
    float sjt_math572;
    float sjt_math573;
    float sjt_math574;
    float sjt_math575;
    float sjt_math576;
    float sjt_math577;
    float sjt_math578;
    float sjt_math579;
    float sjt_math580;
    float sjt_math581;
    float sjt_math582;
    float sjt_math583;
    float sjt_math584;
    float sjt_math585;
    float sjt_math586;
    float sjt_math587;
    float sjt_math588;
    float sjt_math589;
    float sjt_math590;
    float sjt_math591;
    float sjt_math592;
    float sjt_math593;
    float sjt_math594;
    float sjt_math595;
    float sjt_math596;
    float sjt_math597;
    float sjt_math598;
    float sjt_math599;
    float sjt_math600;
    float sjt_math601;
    float sjt_math602;
    float sjt_math603;
    float sjt_math604;
    float sjt_math605;
    float sjt_math606;
    float sjt_math607;
    float sjt_math608;
    float sjt_math609;
    float sjt_math610;
    float sjt_math611;
    float sjt_math612;
    float sjt_math613;
    float sjt_math614;
    float sjt_math615;
    float sjt_math616;
    float sjt_math617;
    float sjt_math618;
    float sjt_math619;
    float sjt_math620;
    float sjt_math621;
    float sjt_math622;
    float sjt_math623;
    float sjt_math624;
    float sjt_math625;
    float sjt_math626;
    float sjt_math627;
    float sjt_math628;
    float sjt_math629;
    float sjt_math630;
    float sjt_math631;
    float sjt_math632;

    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
    (*_return)->_refCount = 1;
#line 19 "lib/ui/mat4.sj"
    sjt_dot328 = m;
#line 21
    sjt_math415 = (sjt_dot328)->m00;
#line 19
    sjt_dot329 = _parent;
#line 21
    sjt_math416 = (sjt_dot329)->m00;
#line 21
    sjt_math413 = sjt_math415 * sjt_math416;
#line 19
    sjt_dot330 = m;
#line 21
    sjt_math417 = (sjt_dot330)->m01;
#line 19
    sjt_dot331 = _parent;
#line 21
    sjt_math418 = (sjt_dot331)->m10;
#line 21
    sjt_math414 = sjt_math417 * sjt_math418;
#line 21
    sjt_math411 = sjt_math413 + sjt_math414;
#line 19
    sjt_dot332 = m;
#line 21
    sjt_math419 = (sjt_dot332)->m02;
#line 19
    sjt_dot333 = _parent;
#line 21
    sjt_math420 = (sjt_dot333)->m20;
#line 21
    sjt_math412 = sjt_math419 * sjt_math420;
#line 21
    sjt_math409 = sjt_math411 + sjt_math412;
#line 19
    sjt_dot334 = m;
#line 21
    sjt_math421 = (sjt_dot334)->m03;
#line 19
    sjt_dot335 = _parent;
#line 21
    sjt_math422 = (sjt_dot335)->m30;
#line 21
    sjt_math410 = sjt_math421 * sjt_math422;
#line 21
    (*_return)->m00 = sjt_math409 + sjt_math410;
#line 19
    sjt_dot336 = m;
#line 22
    sjt_math429 = (sjt_dot336)->m00;
#line 19
    sjt_dot337 = _parent;
#line 22
    sjt_math430 = (sjt_dot337)->m01;
#line 22
    sjt_math427 = sjt_math429 * sjt_math430;
#line 19
    sjt_dot338 = m;
#line 22
    sjt_math431 = (sjt_dot338)->m01;
#line 19
    sjt_dot339 = _parent;
#line 22
    sjt_math432 = (sjt_dot339)->m11;
#line 22
    sjt_math428 = sjt_math431 * sjt_math432;
#line 22
    sjt_math425 = sjt_math427 + sjt_math428;
#line 19
    sjt_dot340 = m;
#line 22
    sjt_math433 = (sjt_dot340)->m02;
#line 19
    sjt_dot341 = _parent;
#line 22
    sjt_math434 = (sjt_dot341)->m21;
#line 22
    sjt_math426 = sjt_math433 * sjt_math434;
#line 22
    sjt_math423 = sjt_math425 + sjt_math426;
#line 19
    sjt_dot342 = m;
#line 22
    sjt_math435 = (sjt_dot342)->m03;
#line 19
    sjt_dot343 = _parent;
#line 22
    sjt_math436 = (sjt_dot343)->m31;
#line 22
    sjt_math424 = sjt_math435 * sjt_math436;
#line 22
    (*_return)->m01 = sjt_math423 + sjt_math424;
#line 19
    sjt_dot344 = m;
#line 23
    sjt_math443 = (sjt_dot344)->m00;
#line 19
    sjt_dot345 = _parent;
#line 23
    sjt_math444 = (sjt_dot345)->m02;
#line 23
    sjt_math441 = sjt_math443 * sjt_math444;
#line 19
    sjt_dot346 = m;
#line 23
    sjt_math445 = (sjt_dot346)->m01;
#line 19
    sjt_dot347 = _parent;
#line 23
    sjt_math446 = (sjt_dot347)->m12;
#line 23
    sjt_math442 = sjt_math445 * sjt_math446;
#line 23
    sjt_math439 = sjt_math441 + sjt_math442;
#line 19
    sjt_dot348 = m;
#line 23
    sjt_math447 = (sjt_dot348)->m02;
#line 19
    sjt_dot349 = _parent;
#line 23
    sjt_math448 = (sjt_dot349)->m22;
#line 23
    sjt_math440 = sjt_math447 * sjt_math448;
#line 23
    sjt_math437 = sjt_math439 + sjt_math440;
#line 19
    sjt_dot350 = m;
#line 23
    sjt_math449 = (sjt_dot350)->m03;
#line 19
    sjt_dot351 = _parent;
#line 23
    sjt_math450 = (sjt_dot351)->m32;
#line 23
    sjt_math438 = sjt_math449 * sjt_math450;
#line 23
    (*_return)->m02 = sjt_math437 + sjt_math438;
#line 19
    sjt_dot352 = m;
#line 24
    sjt_math457 = (sjt_dot352)->m00;
#line 19
    sjt_dot353 = _parent;
#line 24
    sjt_math458 = (sjt_dot353)->m03;
#line 24
    sjt_math455 = sjt_math457 * sjt_math458;
#line 19
    sjt_dot354 = m;
#line 24
    sjt_math459 = (sjt_dot354)->m01;
#line 19
    sjt_dot355 = _parent;
#line 24
    sjt_math460 = (sjt_dot355)->m13;
#line 24
    sjt_math456 = sjt_math459 * sjt_math460;
#line 24
    sjt_math453 = sjt_math455 + sjt_math456;
#line 19
    sjt_dot356 = m;
#line 24
    sjt_math461 = (sjt_dot356)->m02;
#line 19
    sjt_dot357 = _parent;
#line 24
    sjt_math462 = (sjt_dot357)->m23;
#line 24
    sjt_math454 = sjt_math461 * sjt_math462;
#line 24
    sjt_math451 = sjt_math453 + sjt_math454;
#line 19
    sjt_dot358 = m;
#line 24
    sjt_math463 = (sjt_dot358)->m03;
#line 19
    sjt_dot359 = _parent;
#line 24
    sjt_math464 = (sjt_dot359)->m33;
#line 24
    sjt_math452 = sjt_math463 * sjt_math464;
#line 24
    (*_return)->m03 = sjt_math451 + sjt_math452;
#line 19
    sjt_dot360 = m;
#line 25
    sjt_math471 = (sjt_dot360)->m10;
#line 19
    sjt_dot361 = _parent;
#line 25
    sjt_math472 = (sjt_dot361)->m00;
#line 25
    sjt_math469 = sjt_math471 * sjt_math472;
#line 19
    sjt_dot362 = m;
#line 25
    sjt_math473 = (sjt_dot362)->m11;
#line 19
    sjt_dot363 = _parent;
#line 25
    sjt_math474 = (sjt_dot363)->m10;
#line 25
    sjt_math470 = sjt_math473 * sjt_math474;
#line 25
    sjt_math467 = sjt_math469 + sjt_math470;
#line 19
    sjt_dot364 = m;
#line 25
    sjt_math475 = (sjt_dot364)->m12;
#line 19
    sjt_dot365 = _parent;
#line 25
    sjt_math476 = (sjt_dot365)->m20;
#line 25
    sjt_math468 = sjt_math475 * sjt_math476;
#line 25
    sjt_math465 = sjt_math467 + sjt_math468;
#line 19
    sjt_dot366 = m;
#line 25
    sjt_math477 = (sjt_dot366)->m13;
#line 19
    sjt_dot367 = _parent;
#line 25
    sjt_math478 = (sjt_dot367)->m30;
#line 25
    sjt_math466 = sjt_math477 * sjt_math478;
#line 25
    (*_return)->m10 = sjt_math465 + sjt_math466;
#line 19
    sjt_dot368 = m;
#line 26
    sjt_math485 = (sjt_dot368)->m10;
#line 19
    sjt_dot369 = _parent;
#line 26
    sjt_math486 = (sjt_dot369)->m01;
#line 26
    sjt_math483 = sjt_math485 * sjt_math486;
#line 19
    sjt_dot370 = m;
#line 26
    sjt_math487 = (sjt_dot370)->m11;
#line 19
    sjt_dot371 = _parent;
#line 26
    sjt_math488 = (sjt_dot371)->m11;
#line 26
    sjt_math484 = sjt_math487 * sjt_math488;
#line 26
    sjt_math481 = sjt_math483 + sjt_math484;
#line 19
    sjt_dot372 = m;
#line 26
    sjt_math489 = (sjt_dot372)->m12;
#line 19
    sjt_dot373 = _parent;
#line 26
    sjt_math490 = (sjt_dot373)->m21;
#line 26
    sjt_math482 = sjt_math489 * sjt_math490;
#line 26
    sjt_math479 = sjt_math481 + sjt_math482;
#line 19
    sjt_dot374 = m;
#line 26
    sjt_math491 = (sjt_dot374)->m13;
#line 19
    sjt_dot375 = _parent;
#line 26
    sjt_math492 = (sjt_dot375)->m31;
#line 26
    sjt_math480 = sjt_math491 * sjt_math492;
#line 26
    (*_return)->m11 = sjt_math479 + sjt_math480;
#line 19
    sjt_dot376 = m;
#line 27
    sjt_math499 = (sjt_dot376)->m10;
#line 19
    sjt_dot377 = _parent;
#line 27
    sjt_math500 = (sjt_dot377)->m02;
#line 27
    sjt_math497 = sjt_math499 * sjt_math500;
#line 19
    sjt_dot378 = m;
#line 27
    sjt_math501 = (sjt_dot378)->m11;
#line 19
    sjt_dot379 = _parent;
#line 27
    sjt_math502 = (sjt_dot379)->m12;
#line 27
    sjt_math498 = sjt_math501 * sjt_math502;
#line 27
    sjt_math495 = sjt_math497 + sjt_math498;
#line 19
    sjt_dot380 = m;
#line 27
    sjt_math503 = (sjt_dot380)->m12;
#line 19
    sjt_dot381 = _parent;
#line 27
    sjt_math504 = (sjt_dot381)->m22;
#line 27
    sjt_math496 = sjt_math503 * sjt_math504;
#line 27
    sjt_math493 = sjt_math495 + sjt_math496;
#line 19
    sjt_dot382 = m;
#line 27
    sjt_math505 = (sjt_dot382)->m13;
#line 19
    sjt_dot383 = _parent;
#line 27
    sjt_math506 = (sjt_dot383)->m32;
#line 27
    sjt_math494 = sjt_math505 * sjt_math506;
#line 27
    (*_return)->m12 = sjt_math493 + sjt_math494;
#line 19
    sjt_dot384 = m;
#line 28
    sjt_math513 = (sjt_dot384)->m10;
#line 19
    sjt_dot385 = _parent;
#line 28
    sjt_math514 = (sjt_dot385)->m03;
#line 28
    sjt_math511 = sjt_math513 * sjt_math514;
#line 19
    sjt_dot386 = m;
#line 28
    sjt_math515 = (sjt_dot386)->m11;
#line 19
    sjt_dot387 = _parent;
#line 28
    sjt_math516 = (sjt_dot387)->m13;
#line 28
    sjt_math512 = sjt_math515 * sjt_math516;
#line 28
    sjt_math509 = sjt_math511 + sjt_math512;
#line 19
    sjt_dot388 = m;
#line 28
    sjt_math517 = (sjt_dot388)->m12;
#line 19
    sjt_dot389 = _parent;
#line 28
    sjt_math518 = (sjt_dot389)->m23;
#line 28
    sjt_math510 = sjt_math517 * sjt_math518;
#line 28
    sjt_math507 = sjt_math509 + sjt_math510;
#line 19
    sjt_dot390 = m;
#line 28
    sjt_math519 = (sjt_dot390)->m13;
#line 19
    sjt_dot391 = _parent;
#line 28
    sjt_math520 = (sjt_dot391)->m33;
#line 28
    sjt_math508 = sjt_math519 * sjt_math520;
#line 28
    (*_return)->m13 = sjt_math507 + sjt_math508;
#line 19
    sjt_dot392 = m;
#line 29
    sjt_math527 = (sjt_dot392)->m20;
#line 19
    sjt_dot393 = _parent;
#line 29
    sjt_math528 = (sjt_dot393)->m00;
#line 29
    sjt_math525 = sjt_math527 * sjt_math528;
#line 19
    sjt_dot394 = m;
#line 29
    sjt_math529 = (sjt_dot394)->m21;
#line 19
    sjt_dot395 = _parent;
#line 29
    sjt_math530 = (sjt_dot395)->m10;
#line 29
    sjt_math526 = sjt_math529 * sjt_math530;
#line 29
    sjt_math523 = sjt_math525 + sjt_math526;
#line 19
    sjt_dot396 = m;
#line 29
    sjt_math531 = (sjt_dot396)->m22;
#line 19
    sjt_dot397 = _parent;
#line 29
    sjt_math532 = (sjt_dot397)->m20;
#line 29
    sjt_math524 = sjt_math531 * sjt_math532;
#line 29
    sjt_math521 = sjt_math523 + sjt_math524;
#line 19
    sjt_dot398 = m;
#line 29
    sjt_math533 = (sjt_dot398)->m23;
#line 19
    sjt_dot399 = _parent;
#line 29
    sjt_math534 = (sjt_dot399)->m30;
#line 29
    sjt_math522 = sjt_math533 * sjt_math534;
#line 29
    (*_return)->m20 = sjt_math521 + sjt_math522;
#line 19
    sjt_dot400 = m;
#line 30
    sjt_math541 = (sjt_dot400)->m20;
#line 19
    sjt_dot401 = _parent;
#line 30
    sjt_math542 = (sjt_dot401)->m01;
#line 30
    sjt_math539 = sjt_math541 * sjt_math542;
#line 19
    sjt_dot402 = m;
#line 30
    sjt_math543 = (sjt_dot402)->m21;
#line 19
    sjt_dot403 = _parent;
#line 30
    sjt_math544 = (sjt_dot403)->m11;
#line 30
    sjt_math540 = sjt_math543 * sjt_math544;
#line 30
    sjt_math537 = sjt_math539 + sjt_math540;
#line 19
    sjt_dot404 = m;
#line 30
    sjt_math545 = (sjt_dot404)->m22;
#line 19
    sjt_dot405 = _parent;
#line 30
    sjt_math546 = (sjt_dot405)->m21;
#line 30
    sjt_math538 = sjt_math545 * sjt_math546;
#line 30
    sjt_math535 = sjt_math537 + sjt_math538;
#line 19
    sjt_dot406 = m;
#line 30
    sjt_math547 = (sjt_dot406)->m23;
#line 19
    sjt_dot407 = _parent;
#line 30
    sjt_math548 = (sjt_dot407)->m31;
#line 30
    sjt_math536 = sjt_math547 * sjt_math548;
#line 30
    (*_return)->m21 = sjt_math535 + sjt_math536;
#line 19
    sjt_dot408 = m;
#line 31
    sjt_math555 = (sjt_dot408)->m20;
#line 19
    sjt_dot409 = _parent;
#line 31
    sjt_math556 = (sjt_dot409)->m02;
#line 31
    sjt_math553 = sjt_math555 * sjt_math556;
#line 19
    sjt_dot410 = m;
#line 31
    sjt_math557 = (sjt_dot410)->m21;
#line 19
    sjt_dot411 = _parent;
#line 31
    sjt_math558 = (sjt_dot411)->m12;
#line 31
    sjt_math554 = sjt_math557 * sjt_math558;
#line 31
    sjt_math551 = sjt_math553 + sjt_math554;
#line 19
    sjt_dot412 = m;
#line 31
    sjt_math559 = (sjt_dot412)->m22;
#line 19
    sjt_dot413 = _parent;
#line 31
    sjt_math560 = (sjt_dot413)->m22;
#line 31
    sjt_math552 = sjt_math559 * sjt_math560;
#line 31
    sjt_math549 = sjt_math551 + sjt_math552;
#line 19
    sjt_dot414 = m;
#line 31
    sjt_math561 = (sjt_dot414)->m23;
#line 19
    sjt_dot415 = _parent;
#line 31
    sjt_math562 = (sjt_dot415)->m32;
#line 31
    sjt_math550 = sjt_math561 * sjt_math562;
#line 31
    (*_return)->m22 = sjt_math549 + sjt_math550;
#line 19
    sjt_dot416 = m;
#line 32
    sjt_math569 = (sjt_dot416)->m20;
#line 19
    sjt_dot417 = _parent;
#line 32
    sjt_math570 = (sjt_dot417)->m03;
#line 32
    sjt_math567 = sjt_math569 * sjt_math570;
#line 19
    sjt_dot418 = m;
#line 32
    sjt_math571 = (sjt_dot418)->m21;
#line 19
    sjt_dot419 = _parent;
#line 32
    sjt_math572 = (sjt_dot419)->m13;
#line 32
    sjt_math568 = sjt_math571 * sjt_math572;
#line 32
    sjt_math565 = sjt_math567 + sjt_math568;
#line 19
    sjt_dot420 = m;
#line 32
    sjt_math573 = (sjt_dot420)->m22;
#line 19
    sjt_dot421 = _parent;
#line 32
    sjt_math574 = (sjt_dot421)->m23;
#line 32
    sjt_math566 = sjt_math573 * sjt_math574;
#line 32
    sjt_math563 = sjt_math565 + sjt_math566;
#line 19
    sjt_dot422 = m;
#line 32
    sjt_math575 = (sjt_dot422)->m23;
#line 19
    sjt_dot423 = _parent;
#line 32
    sjt_math576 = (sjt_dot423)->m33;
#line 32
    sjt_math564 = sjt_math575 * sjt_math576;
#line 32
    (*_return)->m23 = sjt_math563 + sjt_math564;
#line 19
    sjt_dot424 = m;
#line 33
    sjt_math583 = (sjt_dot424)->m30;
#line 19
    sjt_dot425 = _parent;
#line 33
    sjt_math584 = (sjt_dot425)->m00;
#line 33
    sjt_math581 = sjt_math583 * sjt_math584;
#line 19
    sjt_dot426 = m;
#line 33
    sjt_math585 = (sjt_dot426)->m31;
#line 19
    sjt_dot427 = _parent;
#line 33
    sjt_math586 = (sjt_dot427)->m10;
#line 33
    sjt_math582 = sjt_math585 * sjt_math586;
#line 33
    sjt_math579 = sjt_math581 + sjt_math582;
#line 19
    sjt_dot428 = m;
#line 33
    sjt_math587 = (sjt_dot428)->m32;
#line 19
    sjt_dot429 = _parent;
#line 33
    sjt_math588 = (sjt_dot429)->m20;
#line 33
    sjt_math580 = sjt_math587 * sjt_math588;
#line 33
    sjt_math577 = sjt_math579 + sjt_math580;
#line 19
    sjt_dot430 = m;
#line 33
    sjt_math589 = (sjt_dot430)->m33;
#line 19
    sjt_dot431 = _parent;
#line 33
    sjt_math590 = (sjt_dot431)->m30;
#line 33
    sjt_math578 = sjt_math589 * sjt_math590;
#line 33
    (*_return)->m30 = sjt_math577 + sjt_math578;
#line 19
    sjt_dot432 = m;
#line 34
    sjt_math597 = (sjt_dot432)->m30;
#line 19
    sjt_dot433 = _parent;
#line 34
    sjt_math598 = (sjt_dot433)->m01;
#line 34
    sjt_math595 = sjt_math597 * sjt_math598;
#line 19
    sjt_dot434 = m;
#line 34
    sjt_math599 = (sjt_dot434)->m31;
#line 19
    sjt_dot435 = _parent;
#line 34
    sjt_math600 = (sjt_dot435)->m11;
#line 34
    sjt_math596 = sjt_math599 * sjt_math600;
#line 34
    sjt_math593 = sjt_math595 + sjt_math596;
#line 19
    sjt_dot436 = m;
#line 34
    sjt_math601 = (sjt_dot436)->m32;
#line 19
    sjt_dot437 = _parent;
#line 34
    sjt_math602 = (sjt_dot437)->m21;
#line 34
    sjt_math594 = sjt_math601 * sjt_math602;
#line 34
    sjt_math591 = sjt_math593 + sjt_math594;
#line 19
    sjt_dot438 = m;
#line 34
    sjt_math603 = (sjt_dot438)->m33;
#line 19
    sjt_dot439 = _parent;
#line 34
    sjt_math604 = (sjt_dot439)->m31;
#line 34
    sjt_math592 = sjt_math603 * sjt_math604;
#line 34
    (*_return)->m31 = sjt_math591 + sjt_math592;
#line 19
    sjt_dot440 = m;
#line 35
    sjt_math611 = (sjt_dot440)->m30;
#line 19
    sjt_dot441 = _parent;
#line 35
    sjt_math612 = (sjt_dot441)->m02;
#line 35
    sjt_math609 = sjt_math611 * sjt_math612;
#line 19
    sjt_dot442 = m;
#line 35
    sjt_math613 = (sjt_dot442)->m31;
#line 19
    sjt_dot443 = _parent;
#line 35
    sjt_math614 = (sjt_dot443)->m12;
#line 35
    sjt_math610 = sjt_math613 * sjt_math614;
#line 35
    sjt_math607 = sjt_math609 + sjt_math610;
#line 19
    sjt_dot444 = m;
#line 35
    sjt_math615 = (sjt_dot444)->m32;
#line 19
    sjt_dot445 = _parent;
#line 35
    sjt_math616 = (sjt_dot445)->m22;
#line 35
    sjt_math608 = sjt_math615 * sjt_math616;
#line 35
    sjt_math605 = sjt_math607 + sjt_math608;
#line 19
    sjt_dot446 = m;
#line 35
    sjt_math617 = (sjt_dot446)->m33;
#line 19
    sjt_dot447 = _parent;
#line 35
    sjt_math618 = (sjt_dot447)->m32;
#line 35
    sjt_math606 = sjt_math617 * sjt_math618;
#line 35
    (*_return)->m32 = sjt_math605 + sjt_math606;
#line 19
    sjt_dot448 = m;
#line 36
    sjt_math625 = (sjt_dot448)->m30;
#line 19
    sjt_dot449 = _parent;
#line 36
    sjt_math626 = (sjt_dot449)->m03;
#line 36
    sjt_math623 = sjt_math625 * sjt_math626;
#line 19
    sjt_dot450 = m;
#line 36
    sjt_math627 = (sjt_dot450)->m31;
#line 19
    sjt_dot451 = _parent;
#line 36
    sjt_math628 = (sjt_dot451)->m13;
#line 36
    sjt_math624 = sjt_math627 * sjt_math628;
#line 36
    sjt_math621 = sjt_math623 + sjt_math624;
#line 19
    sjt_dot452 = m;
#line 36
    sjt_math629 = (sjt_dot452)->m32;
#line 19
    sjt_dot453 = _parent;
#line 36
    sjt_math630 = (sjt_dot453)->m23;
#line 36
    sjt_math622 = sjt_math629 * sjt_math630;
#line 36
    sjt_math619 = sjt_math621 + sjt_math622;
#line 19
    sjt_dot454 = m;
#line 36
    sjt_math631 = (sjt_dot454)->m33;
#line 19
    sjt_dot455 = _parent;
#line 36
    sjt_math632 = (sjt_dot455)->m33;
#line 36
    sjt_math620 = sjt_math631 * sjt_math632;
#line 36
    (*_return)->m33 = sjt_math619 + sjt_math620;
#line 36
    sjf_mat4_heap((*_return));
}

void sjf_mat4_orthographic(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4* _return) {
    float result51;
    float sjt_math2157;
    float sjt_math2158;
    float sjt_math2159;
    float sjt_math2160;
    float sjt_math2161;
    float sjt_math2162;
    float sjt_math2163;
    float sjt_math2164;
    float sjt_math2165;
    float sjt_math2166;
    float sjt_math2167;
    float sjt_math2168;
    float sjt_math2169;
    float sjt_math2170;
    float sjt_math2171;
    float sjt_math2172;
    float sjt_math2173;
    float sjt_math2174;
    float sjt_math2175;
    float sjt_math2176;
    float sjt_math2177;
    float sjt_math2178;
    float sjt_math2179;
    float sjt_math2180;
    float sjt_math2181;
    float sjt_math2182;
    float sjt_math2183;
    float sjt_math2184;
    float sjt_math2185;
    float sjt_math2186;
    float sjt_math2187;
    float sjt_math2188;
    float sjt_math2189;
    float sjt_math2190;
    float sjt_math2191;
    float sjt_math2192;
    float sjt_negate46;

#line 182 "lib/ui/mat4.sj"
    sjt_math2157 = 2.0f;
#line 180
    sjt_math2159 = right;
#line 180
    sjt_math2160 = left;
#line 182
    sjt_math2158 = sjt_math2159 - sjt_math2160;
#line 182
    _return->m00 = sjt_math2157 / sjt_math2158;
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 184
    sjt_math2161 = 2.0f;
#line 180
    sjt_math2163 = top;
#line 180
    sjt_math2164 = bottom;
#line 184
    sjt_math2162 = sjt_math2163 - sjt_math2164;
#line 184
    _return->m11 = sjt_math2161 / sjt_math2162;
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 186
    sjt_negate46 = 2.0f;
#line 186
    result51 = -sjt_negate46;
#line 186
    sjt_math2165 = result51;
#line 180
    sjt_math2167 = zfar;
#line 180
    sjt_math2168 = znear;
#line 186
    sjt_math2166 = sjt_math2167 - sjt_math2168;
#line 186
    _return->m22 = sjt_math2165 / sjt_math2166;
#line 13
    _return->m23 = 0.0f;
#line 183
    sjt_math2169 = 0.0f;
#line 180
    sjt_math2173 = right;
#line 180
    sjt_math2174 = left;
#line 183
    sjt_math2171 = sjt_math2173 + sjt_math2174;
#line 180
    sjt_math2175 = right;
#line 180
    sjt_math2176 = left;
#line 183
    sjt_math2172 = sjt_math2175 - sjt_math2176;
#line 183
    sjt_math2170 = sjt_math2171 / sjt_math2172;
#line 183
    _return->m30 = sjt_math2169 - sjt_math2170;
#line 185
    sjt_math2177 = 0.0f;
#line 180
    sjt_math2181 = top;
#line 180
    sjt_math2182 = bottom;
#line 185
    sjt_math2179 = sjt_math2181 + sjt_math2182;
#line 180
    sjt_math2183 = top;
#line 180
    sjt_math2184 = bottom;
#line 185
    sjt_math2180 = sjt_math2183 - sjt_math2184;
#line 185
    sjt_math2178 = sjt_math2179 / sjt_math2180;
#line 185
    _return->m31 = sjt_math2177 - sjt_math2178;
#line 187
    sjt_math2185 = 0.0f;
#line 180
    sjt_math2189 = zfar;
#line 180
    sjt_math2190 = znear;
#line 187
    sjt_math2187 = sjt_math2189 + sjt_math2190;
#line 180
    sjt_math2191 = zfar;
#line 180
    sjt_math2192 = znear;
#line 187
    sjt_math2188 = sjt_math2191 - sjt_math2192;
#line 187
    sjt_math2186 = sjt_math2187 / sjt_math2188;
#line 187
    _return->m32 = sjt_math2185 - sjt_math2186;
#line 188
    _return->m33 = 1.0f;
#line 188
    sjf_mat4(_return);
}

void sjf_mat4_orthographic_heap(float left, float right, float bottom, float top, float znear, float zfar, sjs_mat4_heap** _return) {
    float result52;
    float sjt_math2193;
    float sjt_math2194;
    float sjt_math2195;
    float sjt_math2196;
    float sjt_math2197;
    float sjt_math2198;
    float sjt_math2199;
    float sjt_math2200;
    float sjt_math2201;
    float sjt_math2202;
    float sjt_math2203;
    float sjt_math2204;
    float sjt_math2205;
    float sjt_math2206;
    float sjt_math2207;
    float sjt_math2208;
    float sjt_math2209;
    float sjt_math2210;
    float sjt_math2211;
    float sjt_math2212;
    float sjt_math2213;
    float sjt_math2214;
    float sjt_math2215;
    float sjt_math2216;
    float sjt_math2217;
    float sjt_math2218;
    float sjt_math2219;
    float sjt_math2220;
    float sjt_math2221;
    float sjt_math2222;
    float sjt_math2223;
    float sjt_math2224;
    float sjt_math2225;
    float sjt_math2226;
    float sjt_math2227;
    float sjt_math2228;
    float sjt_negate47;

    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
    (*_return)->_refCount = 1;
#line 182 "lib/ui/mat4.sj"
    sjt_math2193 = 2.0f;
#line 180
    sjt_math2195 = right;
#line 180
    sjt_math2196 = left;
#line 182
    sjt_math2194 = sjt_math2195 - sjt_math2196;
#line 182
    (*_return)->m00 = sjt_math2193 / sjt_math2194;
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 184
    sjt_math2197 = 2.0f;
#line 180
    sjt_math2199 = top;
#line 180
    sjt_math2200 = bottom;
#line 184
    sjt_math2198 = sjt_math2199 - sjt_math2200;
#line 184
    (*_return)->m11 = sjt_math2197 / sjt_math2198;
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 186
    sjt_negate47 = 2.0f;
#line 186
    result52 = -sjt_negate47;
#line 186
    sjt_math2201 = result52;
#line 180
    sjt_math2203 = zfar;
#line 180
    sjt_math2204 = znear;
#line 186
    sjt_math2202 = sjt_math2203 - sjt_math2204;
#line 186
    (*_return)->m22 = sjt_math2201 / sjt_math2202;
#line 13
    (*_return)->m23 = 0.0f;
#line 183
    sjt_math2205 = 0.0f;
#line 180
    sjt_math2209 = right;
#line 180
    sjt_math2210 = left;
#line 183
    sjt_math2207 = sjt_math2209 + sjt_math2210;
#line 180
    sjt_math2211 = right;
#line 180
    sjt_math2212 = left;
#line 183
    sjt_math2208 = sjt_math2211 - sjt_math2212;
#line 183
    sjt_math2206 = sjt_math2207 / sjt_math2208;
#line 183
    (*_return)->m30 = sjt_math2205 - sjt_math2206;
#line 185
    sjt_math2213 = 0.0f;
#line 180
    sjt_math2217 = top;
#line 180
    sjt_math2218 = bottom;
#line 185
    sjt_math2215 = sjt_math2217 + sjt_math2218;
#line 180
    sjt_math2219 = top;
#line 180
    sjt_math2220 = bottom;
#line 185
    sjt_math2216 = sjt_math2219 - sjt_math2220;
#line 185
    sjt_math2214 = sjt_math2215 / sjt_math2216;
#line 185
    (*_return)->m31 = sjt_math2213 - sjt_math2214;
#line 187
    sjt_math2221 = 0.0f;
#line 180
    sjt_math2225 = zfar;
#line 180
    sjt_math2226 = znear;
#line 187
    sjt_math2223 = sjt_math2225 + sjt_math2226;
#line 180
    sjt_math2227 = zfar;
#line 180
    sjt_math2228 = znear;
#line 187
    sjt_math2224 = sjt_math2227 - sjt_math2228;
#line 187
    sjt_math2222 = sjt_math2223 / sjt_math2224;
#line 187
    (*_return)->m32 = sjt_math2221 - sjt_math2222;
#line 188
    (*_return)->m33 = 1.0f;
#line 188
    sjf_mat4_heap((*_return));
}

void sjf_mat4_perspective(float fovy, float aspect, float znear, float zfar, sjs_mat4* _return) {
    float sjt_functionParam7;
    float sjt_math10;
    float sjt_math11;
    float sjt_math12;
    float sjt_math13;
    float sjt_math14;
    float sjt_math15;
    float sjt_math16;
    float sjt_math17;
    float sjt_math18;
    float sjt_math19;
    float sjt_math20;
    float sjt_math21;
    float sjt_math22;
    float sjt_math3;
    float sjt_math4;
    float sjt_math5;
    float sjt_math6;
    float sjt_math7;
    float sjt_math8;
    float sjt_math9;
    float sjv_xscale;
    float sjv_yscale;

#line 169 "lib/ui/mat4.sj"
    sjt_math3 = 1.0f;
#line 168
    sjt_math7 = fovy;
#line 169
    sjt_math8 = 180.0f;
#line 169
    sjt_math5 = sjt_math7 / sjt_math8;
#line 169
    sjt_math6 = 2.0f;
#line 169
    sjt_functionParam7 = sjt_math5 / sjt_math6;
#line 169
    sjf_f32_tan(sjt_functionParam7, &sjt_math4);
#line 169
    sjv_yscale = sjt_math3 / sjt_math4;
#line 170
    sjt_math9 = sjv_yscale;
#line 168
    sjt_math10 = aspect;
#line 170
    sjv_xscale = sjt_math9 * sjt_math10;
#line 171
    _return->m00 = sjv_xscale;
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 171
    _return->m11 = sjv_yscale;
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 168
    sjt_math11 = zfar;
#line 168
    sjt_math13 = zfar;
#line 168
    sjt_math14 = znear;
#line 174
    sjt_math12 = sjt_math13 - sjt_math14;
#line 174
    _return->m22 = sjt_math11 / sjt_math12;
#line 175
    _return->m23 = 1.0f;
#line 14
    _return->m30 = 0.0f;
#line 15
    _return->m31 = 0.0f;
#line 176
    sjt_math15 = 0.0f;
#line 168
    sjt_math19 = znear;
#line 168
    sjt_math20 = zfar;
#line 176
    sjt_math17 = sjt_math19 * sjt_math20;
#line 168
    sjt_math21 = zfar;
#line 168
    sjt_math22 = znear;
#line 176
    sjt_math18 = sjt_math21 - sjt_math22;
#line 176
    sjt_math16 = sjt_math17 / sjt_math18;
#line 176
    _return->m32 = sjt_math15 - sjt_math16;
#line 17
    _return->m33 = 0.0f;
#line 17
    sjf_mat4(_return);
}

void sjf_mat4_perspective_heap(float fovy, float aspect, float znear, float zfar, sjs_mat4_heap** _return) {
    float sjt_functionParam8;
    float sjt_math23;
    float sjt_math24;
    float sjt_math25;
    float sjt_math26;
    float sjt_math27;
    float sjt_math28;
    float sjt_math29;
    float sjt_math30;
    float sjt_math31;
    float sjt_math32;
    float sjt_math33;
    float sjt_math34;
    float sjt_math35;
    float sjt_math36;
    float sjt_math37;
    float sjt_math38;
    float sjt_math39;
    float sjt_math40;
    float sjt_math41;
    float sjt_math42;
    float sjv_xscale;
    float sjv_yscale;

#line 169 "lib/ui/mat4.sj"
    sjt_math23 = 1.0f;
#line 168
    sjt_math27 = fovy;
#line 169
    sjt_math28 = 180.0f;
#line 169
    sjt_math25 = sjt_math27 / sjt_math28;
#line 169
    sjt_math26 = 2.0f;
#line 169
    sjt_functionParam8 = sjt_math25 / sjt_math26;
#line 169
    sjf_f32_tan(sjt_functionParam8, &sjt_math24);
#line 169
    sjv_yscale = sjt_math23 / sjt_math24;
#line 170
    sjt_math29 = sjv_yscale;
#line 168
    sjt_math30 = aspect;
#line 170
    sjv_xscale = sjt_math29 * sjt_math30;
#line 170
    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
#line 170
    (*_return)->_refCount = 1;
#line 171
    (*_return)->m00 = sjv_xscale;
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 171
    (*_return)->m11 = sjv_yscale;
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 168
    sjt_math31 = zfar;
#line 168
    sjt_math33 = zfar;
#line 168
    sjt_math34 = znear;
#line 174
    sjt_math32 = sjt_math33 - sjt_math34;
#line 174
    (*_return)->m22 = sjt_math31 / sjt_math32;
#line 175
    (*_return)->m23 = 1.0f;
#line 14
    (*_return)->m30 = 0.0f;
#line 15
    (*_return)->m31 = 0.0f;
#line 176
    sjt_math35 = 0.0f;
#line 168
    sjt_math39 = znear;
#line 168
    sjt_math40 = zfar;
#line 176
    sjt_math37 = sjt_math39 * sjt_math40;
#line 168
    sjt_math41 = zfar;
#line 168
    sjt_math42 = znear;
#line 176
    sjt_math38 = sjt_math41 - sjt_math42;
#line 176
    sjt_math36 = sjt_math37 / sjt_math38;
#line 176
    (*_return)->m32 = sjt_math35 - sjt_math36;
#line 17
    (*_return)->m33 = 0.0f;
#line 17
    sjf_mat4_heap((*_return));
}

void sjf_mat4_scale(float x, float y, float z, sjs_mat4* _return) {
#line 227 "lib/ui/mat4.sj"
    _return->m00 = x;
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 227
    _return->m11 = y;
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 227
    _return->m22 = z;
#line 13
    _return->m23 = 0.0f;
#line 14
    _return->m30 = 0.0f;
#line 15
    _return->m31 = 0.0f;
#line 16
    _return->m32 = 0.0f;
#line 232
    _return->m33 = 1.0f;
#line 232
    sjf_mat4(_return);
}

void sjf_mat4_scale_heap(float x, float y, float z, sjs_mat4_heap** _return) {
    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
    (*_return)->_refCount = 1;
#line 227 "lib/ui/mat4.sj"
    (*_return)->m00 = x;
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 227
    (*_return)->m11 = y;
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 227
    (*_return)->m22 = z;
#line 13
    (*_return)->m23 = 0.0f;
#line 14
    (*_return)->m30 = 0.0f;
#line 15
    (*_return)->m31 = 0.0f;
#line 16
    (*_return)->m32 = 0.0f;
#line 232
    (*_return)->m33 = 1.0f;
#line 232
    sjf_mat4_heap((*_return));
}

void sjf_mat4_translate(float x, float y, float z, sjs_mat4* _return) {
#line 217 "lib/ui/mat4.sj"
    _return->m00 = 1.0f;
#line 3
    _return->m01 = 0.0f;
#line 4
    _return->m02 = 0.0f;
#line 5
    _return->m03 = 0.0f;
#line 6
    _return->m10 = 0.0f;
#line 218
    _return->m11 = 1.0f;
#line 8
    _return->m12 = 0.0f;
#line 9
    _return->m13 = 0.0f;
#line 10
    _return->m20 = 0.0f;
#line 11
    _return->m21 = 0.0f;
#line 219
    _return->m22 = 1.0f;
#line 13
    _return->m23 = 0.0f;
#line 215
    _return->m30 = x;
#line 215
    _return->m31 = y;
#line 215
    _return->m32 = z;
#line 223
    _return->m33 = 1.0f;
#line 223
    sjf_mat4(_return);
}

void sjf_mat4_translate_heap(float x, float y, float z, sjs_mat4_heap** _return) {
    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
    (*_return)->_refCount = 1;
#line 217 "lib/ui/mat4.sj"
    (*_return)->m00 = 1.0f;
#line 3
    (*_return)->m01 = 0.0f;
#line 4
    (*_return)->m02 = 0.0f;
#line 5
    (*_return)->m03 = 0.0f;
#line 6
    (*_return)->m10 = 0.0f;
#line 218
    (*_return)->m11 = 1.0f;
#line 8
    (*_return)->m12 = 0.0f;
#line 9
    (*_return)->m13 = 0.0f;
#line 10
    (*_return)->m20 = 0.0f;
#line 11
    (*_return)->m21 = 0.0f;
#line 219
    (*_return)->m22 = 1.0f;
#line 13
    (*_return)->m23 = 0.0f;
#line 215
    (*_return)->m30 = x;
#line 215
    (*_return)->m31 = y;
#line 215
    (*_return)->m32 = z;
#line 223
    (*_return)->m33 = 1.0f;
#line 223
    sjf_mat4_heap((*_return));
}

void sjf_mat4_transpose(sjs_mat4* _parent, sjs_mat4* _return) {
    sjs_mat4* sjt_dot556;
    sjs_mat4* sjt_dot557;
    sjs_mat4* sjt_dot558;
    sjs_mat4* sjt_dot559;
    sjs_mat4* sjt_dot560;
    sjs_mat4* sjt_dot561;
    sjs_mat4* sjt_dot562;
    sjs_mat4* sjt_dot563;
    sjs_mat4* sjt_dot564;
    sjs_mat4* sjt_dot565;
    sjs_mat4* sjt_dot566;
    sjs_mat4* sjt_dot567;
    sjs_mat4* sjt_dot568;
    sjs_mat4* sjt_dot569;
    sjs_mat4* sjt_dot570;
    sjs_mat4* sjt_dot571;

#line 108 "lib/ui/mat4.sj"
    sjt_dot556 = _parent;
#line 109
    _return->m00 = (sjt_dot556)->m00;
#line 108
    sjt_dot557 = _parent;
#line 109
    _return->m01 = (sjt_dot557)->m10;
#line 108
    sjt_dot558 = _parent;
#line 109
    _return->m02 = (sjt_dot558)->m20;
#line 108
    sjt_dot559 = _parent;
#line 109
    _return->m03 = (sjt_dot559)->m30;
#line 108
    sjt_dot560 = _parent;
#line 109
    _return->m10 = (sjt_dot560)->m01;
#line 108
    sjt_dot561 = _parent;
#line 109
    _return->m11 = (sjt_dot561)->m11;
#line 108
    sjt_dot562 = _parent;
#line 109
    _return->m12 = (sjt_dot562)->m21;
#line 108
    sjt_dot563 = _parent;
#line 109
    _return->m13 = (sjt_dot563)->m31;
#line 108
    sjt_dot564 = _parent;
#line 109
    _return->m20 = (sjt_dot564)->m02;
#line 108
    sjt_dot565 = _parent;
#line 109
    _return->m21 = (sjt_dot565)->m12;
#line 108
    sjt_dot566 = _parent;
#line 109
    _return->m22 = (sjt_dot566)->m22;
#line 108
    sjt_dot567 = _parent;
#line 109
    _return->m23 = (sjt_dot567)->m32;
#line 108
    sjt_dot568 = _parent;
#line 109
    _return->m30 = (sjt_dot568)->m03;
#line 108
    sjt_dot569 = _parent;
#line 109
    _return->m31 = (sjt_dot569)->m13;
#line 108
    sjt_dot570 = _parent;
#line 109
    _return->m32 = (sjt_dot570)->m23;
#line 108
    sjt_dot571 = _parent;
#line 109
    _return->m33 = (sjt_dot571)->m33;
#line 109
    sjf_mat4(_return);
}

void sjf_mat4_transpose_heap(sjs_mat4* _parent, sjs_mat4_heap** _return) {
    sjs_mat4* sjt_dot572;
    sjs_mat4* sjt_dot573;
    sjs_mat4* sjt_dot574;
    sjs_mat4* sjt_dot575;
    sjs_mat4* sjt_dot576;
    sjs_mat4* sjt_dot577;
    sjs_mat4* sjt_dot578;
    sjs_mat4* sjt_dot579;
    sjs_mat4* sjt_dot580;
    sjs_mat4* sjt_dot581;
    sjs_mat4* sjt_dot582;
    sjs_mat4* sjt_dot583;
    sjs_mat4* sjt_dot584;
    sjs_mat4* sjt_dot585;
    sjs_mat4* sjt_dot586;
    sjs_mat4* sjt_dot587;

    (*_return) = (sjs_mat4_heap*)malloc(sizeof(sjs_mat4_heap));
    (*_return)->_refCount = 1;
#line 108 "lib/ui/mat4.sj"
    sjt_dot572 = _parent;
#line 109
    (*_return)->m00 = (sjt_dot572)->m00;
#line 108
    sjt_dot573 = _parent;
#line 109
    (*_return)->m01 = (sjt_dot573)->m10;
#line 108
    sjt_dot574 = _parent;
#line 109
    (*_return)->m02 = (sjt_dot574)->m20;
#line 108
    sjt_dot575 = _parent;
#line 109
    (*_return)->m03 = (sjt_dot575)->m30;
#line 108
    sjt_dot576 = _parent;
#line 109
    (*_return)->m10 = (sjt_dot576)->m01;
#line 108
    sjt_dot577 = _parent;
#line 109
    (*_return)->m11 = (sjt_dot577)->m11;
#line 108
    sjt_dot578 = _parent;
#line 109
    (*_return)->m12 = (sjt_dot578)->m21;
#line 108
    sjt_dot579 = _parent;
#line 109
    (*_return)->m13 = (sjt_dot579)->m31;
#line 108
    sjt_dot580 = _parent;
#line 109
    (*_return)->m20 = (sjt_dot580)->m02;
#line 108
    sjt_dot581 = _parent;
#line 109
    (*_return)->m21 = (sjt_dot581)->m12;
#line 108
    sjt_dot582 = _parent;
#line 109
    (*_return)->m22 = (sjt_dot582)->m22;
#line 108
    sjt_dot583 = _parent;
#line 109
    (*_return)->m23 = (sjt_dot583)->m32;
#line 108
    sjt_dot584 = _parent;
#line 109
    (*_return)->m30 = (sjt_dot584)->m03;
#line 108
    sjt_dot585 = _parent;
#line 109
    (*_return)->m31 = (sjt_dot585)->m13;
#line 108
    sjt_dot586 = _parent;
#line 109
    (*_return)->m32 = (sjt_dot586)->m23;
#line 108
    sjt_dot587 = _parent;
#line 109
    (*_return)->m33 = (sjt_dot587)->m33;
#line 109
    sjf_mat4_heap((*_return));
}

void sjf_model(sjs_model* _this) {
}

sjs_object* sjf_model_asInterface(sjs_model* _this, int typeId) {
    switch (typeId) {
        case sji_nauScene3dElement_model_typeId:  {
            return (sjs_object*)sjf_model_as_sji_nauScene3dElement_model(_this);
        }
    }

    return 0;
}

sji_nauScene3dElement_model* sjf_model_as_sji_nauScene3dElement_model(sjs_model* _this) {
    sji_nauScene3dElement_model* _interface;
    _interface = (sji_nauScene3dElement_model*)malloc(sizeof(sji_nauScene3dElement_model));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_model_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_model_asInterface;
    _interface->update = (void(*)(void*,sjs_rect*,sjs_mat4*,sjs_mat4*,sjs_mat4*,sjs_light*))sjf_model_update;
    _interface->getZ = (void(*)(void*, float*))sjf_model_getZ;
    _interface->renderOrQueue = (void(*)(void*,sjs_list_heap_model*))sjf_model_renderOrQueue;
    _interface->render = (void(*)(void*))sjf_model_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_model_fireMouseEvent;

    return _interface;
}

void sjf_model_copy(sjs_model* _this, sjs_model* _from) {
#line 13 "lib/ui/model.sj"
    sjf_vertexBuffer_vertex_location_texture_normal_copy(&_this->vertexBuffer, &_from->vertexBuffer);
#line 13
    sjf_shader_copy(&_this->shader, &_from->shader);
#line 13
    sjf_texture_copy(&_this->texture, &_from->texture);
#line 13
    sjf_mat4_copy(&_this->model, &_from->model);
#line 13
    sjf_vec3_copy(&_this->center, &_from->center);
#line 13
    _this->hasAlpha = _from->hasAlpha;
#line 13
    sjf_string_copy(&_this->id, &_from->id);
#line 13
    sjf_mat4_copy(&_this->_projection, &_from->_projection);
#line 13
    sjf_mat4_copy(&_this->_view, &_from->_view);
#line 13
    sjf_mat4_copy(&_this->_world, &_from->_world);
#line 13
    sjf_light_copy(&_this->_light, &_from->_light);
#line 13
    sjf_vec3_copy(&_this->_projectedCenter, &_from->_projectedCenter);
}

void sjf_model_destroy(sjs_model* _this) {
}

void sjf_model_fireMouseEvent(sjs_model* _parent, sjs_point* point, int32_t eventId) {
}

void sjf_model_getZ(sjs_model* _parent, float* _return) {
    sjs_vec3* sjt_dot537;
    sjs_model* sjt_dot538;

#line 38 "lib/ui/model.sj"
    sjt_dot538 = _parent;
#line 1 "lib/ui/vec3.sj"
    sjt_dot537 = &(sjt_dot538)->_projectedCenter;
#line 38 "lib/ui/model.sj"
    (*_return) = (sjt_dot537)->z;
}

void sjf_model_heap(sjs_model_heap* _this) {
}

sjs_object* sjf_model_heap_asInterface(sjs_model_heap* _this, int typeId) {
    switch (typeId) {
        case sji_nauScene3dElement_model_typeId:  {
            return (sjs_object*)sjf_model_heap_as_sji_nauScene3dElement_model(_this);
        }
    }

    return 0;
}

sji_nauScene3dElement_model* sjf_model_heap_as_sji_nauScene3dElement_model(sjs_model_heap* _this) {
    sji_nauScene3dElement_model* _interface;
    _interface = (sji_nauScene3dElement_model*)malloc(sizeof(sji_nauScene3dElement_model));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_model_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_model_heap_asInterface;
    _interface->update = (void(*)(void*,sjs_rect*,sjs_mat4*,sjs_mat4*,sjs_mat4*,sjs_light*))sjf_model_update;
    _interface->getZ = (void(*)(void*, float*))sjf_model_getZ;
    _interface->renderOrQueue = (void(*)(void*,sjs_list_heap_model*))sjf_model_renderOrQueue;
    _interface->render = (void(*)(void*))sjf_model_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_model_fireMouseEvent;

    return _interface;
}

void sjf_model_render(sjs_model* _parent) {
    sjs_mat4 sjt_call10;
    sjs_string sjt_call11;
    sjs_string sjt_call12;
    sjs_string sjt_call13;
    sjs_string sjt_call14;
    sjs_string sjt_call15;
    sjs_vec3 sjt_call16;
    sjs_string sjt_call17;
    sjs_vec3 sjt_call18;
    sjs_model* sjt_dot1292;
    sjs_model* sjt_dot1293;
    sjs_model* sjt_dot1294;
    sjs_model* sjt_dot1295;
    sjs_model* sjt_dot1296;
    sjs_model* sjt_dot1297;
    sjs_model* sjt_dot1298;
    sjs_light* sjt_dot1299;
    sjs_model* sjt_dot1300;
    sjs_model* sjt_dot1301;
    sjs_light* sjt_dot1308;
    sjs_model* sjt_dot1309;
    sjs_model* sjt_dot1310;
    sjs_light* sjt_dot1311;
    sjs_model* sjt_dot1312;
    sjs_model* sjt_dot1313;
    sjs_model* sjt_dot553;
    sjs_model* sjt_dot554;
    sjs_model* sjt_dot555;
    sjs_mat4* sjt_functionParam110;
    sjs_mat4* sjt_functionParam111;
    sjs_shader* sjt_functionParam114;
    int32_t sjt_functionParam115;
    sjs_texture* sjt_functionParam116;
    int32_t sjt_functionParam117;
    sjs_shader* sjt_functionParam118;
    sjs_string* sjt_functionParam119;
    sjs_mat4* sjt_functionParam120;
    int32_t sjt_functionParam121;
    sjs_shader* sjt_functionParam122;
    sjs_string* sjt_functionParam123;
    sjs_mat4* sjt_functionParam124;
    int32_t sjt_functionParam125;
    sjs_shader* sjt_functionParam126;
    sjs_string* sjt_functionParam127;
    sjs_mat4* sjt_functionParam128;
    int32_t sjt_functionParam129;
    sjs_shader* sjt_functionParam130;
    sjs_string* sjt_functionParam131;
    sjs_vec3* sjt_functionParam132;
    int32_t sjt_functionParam133;
    sjs_shader* sjt_functionParam134;
    sjs_string* sjt_functionParam135;
    sjs_vec3* sjt_functionParam136;
    int32_t sjt_functionParam137;
    sjs_shader* sjt_functionParam138;
    sjs_string* sjt_functionParam139;
    sjs_vec3* sjt_functionParam140;
    sjs_mat4* sjt_parent48;
    sjs_mat4* sjt_parent49;
    sjs_mat4* sjt_parent50;
    sjs_mat4* sjt_parent53;
    sjs_color* sjt_parent54;
    sjs_color* sjt_parent55;
    sjs_vertexBuffer_vertex_location_texture_normal* sjt_parent56;
    sjs_mat4 sjv_normalMat;
    sjs_mat4 sjv_viewWorld;
    sjs_mat4 sjv_world;

#line 50 "lib/ui/model.sj"
    sjt_dot553 = _parent;
#line 19 "lib/ui/mat4.sj"
    sjt_parent48 = &(sjt_dot553)->_world;
#line 50 "lib/ui/model.sj"
    sjt_dot554 = _parent;
#line 51
    sjt_functionParam110 = &(sjt_dot554)->model;
#line 51
    sjf_mat4_multiply(sjt_parent48, sjt_functionParam110, &sjv_world);
#line 50
    sjt_dot555 = _parent;
#line 19 "lib/ui/mat4.sj"
    sjt_parent49 = &(sjt_dot555)->_view;
#line 52 "lib/ui/model.sj"
    sjt_functionParam111 = &sjv_world;
#line 52
    sjf_mat4_multiply(sjt_parent49, sjt_functionParam111, &sjv_viewWorld);
#line 81 "lib/ui/mat4.sj"
    sjt_parent53 = &sjv_viewWorld;
#line 81
    sjf_mat4_invert(sjt_parent53, &sjt_call10);
#line 53 "lib/ui/model.sj"
    sjt_parent50 = &sjt_call10;
#line 53
    sjf_mat4_transpose(sjt_parent50, &sjv_normalMat);
#line 50
    sjt_dot1292 = _parent;
#line 54
    sjt_functionParam114 = &(sjt_dot1292)->shader;
#line 54
    sjf_glUseProgram(sjt_functionParam114);
#line 55
    sjt_functionParam115 = sjv_glTexture_GL_TEXTURE_2D;
#line 50
    sjt_dot1293 = _parent;
#line 55
    sjt_functionParam116 = &(sjt_dot1293)->texture;
#line 55
    sjf_glBindTexture(sjt_functionParam115, sjt_functionParam116);
#line 50
    sjt_dot1294 = _parent;
#line 56
    sjt_functionParam118 = &(sjt_dot1294)->shader;
#line 56
    sjt_call11.count = 9;
#line 56
    sjt_call11.data.dataSize = 10;
#line 56
    sjt_call11.data.data = (void*)sjg_string91;
#line 56
    sjt_call11.data._isGlobal = true;
#line 56
    sjt_call11.data.count = 10;
#line 56
    sjf_array_char(&sjt_call11.data);
#line 56
    sjf_string(&sjt_call11);
#line 56
    sjt_functionParam119 = &sjt_call11;
#line 56
    sjf_glGetUniformLocation(sjt_functionParam118, sjt_functionParam119, &sjt_functionParam117);
#line 56
    sjt_functionParam120 = &sjv_viewWorld;
#line 56
    sjf_glUniformMat4(sjt_functionParam117, sjt_functionParam120);
#line 50
    sjt_dot1295 = _parent;
#line 57
    sjt_functionParam122 = &(sjt_dot1295)->shader;
#line 57
    sjt_call12.count = 9;
#line 57
    sjt_call12.data.dataSize = 10;
#line 57
    sjt_call12.data.data = (void*)sjg_string92;
#line 57
    sjt_call12.data._isGlobal = true;
#line 57
    sjt_call12.data.count = 10;
#line 57
    sjf_array_char(&sjt_call12.data);
#line 57
    sjf_string(&sjt_call12);
#line 57
    sjt_functionParam123 = &sjt_call12;
#line 57
    sjf_glGetUniformLocation(sjt_functionParam122, sjt_functionParam123, &sjt_functionParam121);
#line 57
    sjt_functionParam124 = &sjv_normalMat;
#line 57
    sjf_glUniformMat4(sjt_functionParam121, sjt_functionParam124);
#line 50
    sjt_dot1296 = _parent;
#line 58
    sjt_functionParam126 = &(sjt_dot1296)->shader;
#line 58
    sjt_call13.count = 10;
#line 58
    sjt_call13.data.dataSize = 11;
#line 58
    sjt_call13.data.data = (void*)sjg_string93;
#line 58
    sjt_call13.data._isGlobal = true;
#line 58
    sjt_call13.data.count = 11;
#line 58
    sjf_array_char(&sjt_call13.data);
#line 58
    sjf_string(&sjt_call13);
#line 58
    sjt_functionParam127 = &sjt_call13;
#line 58
    sjf_glGetUniformLocation(sjt_functionParam126, sjt_functionParam127, &sjt_functionParam125);
#line 50
    sjt_dot1297 = _parent;
#line 58
    sjt_functionParam128 = &(sjt_dot1297)->_projection;
#line 58
    sjf_glUniformMat4(sjt_functionParam125, sjt_functionParam128);
#line 50
    sjt_dot1298 = _parent;
#line 59
    sjt_functionParam130 = &(sjt_dot1298)->shader;
#line 59
    sjt_call14.count = 8;
#line 59
    sjt_call14.data.dataSize = 9;
#line 59
    sjt_call14.data.data = (void*)sjg_string94;
#line 59
    sjt_call14.data._isGlobal = true;
#line 59
    sjt_call14.data.count = 9;
#line 59
    sjf_array_char(&sjt_call14.data);
#line 59
    sjf_string(&sjt_call14);
#line 59
    sjt_functionParam131 = &sjt_call14;
#line 59
    sjf_glGetUniformLocation(sjt_functionParam130, sjt_functionParam131, &sjt_functionParam129);
#line 50
    sjt_dot1300 = _parent;
#line 1 "lib/ui/scene3dElement.sj"
    sjt_dot1299 = &(sjt_dot1300)->_light;
#line 59 "lib/ui/model.sj"
    sjt_functionParam132 = &(sjt_dot1299)->pos;
#line 59
    sjf_glUniformVec3(sjt_functionParam129, sjt_functionParam132);
#line 50
    sjt_dot1301 = _parent;
#line 60
    sjt_functionParam134 = &(sjt_dot1301)->shader;
#line 60
    sjt_call15.count = 12;
#line 60
    sjt_call15.data.dataSize = 13;
#line 60
    sjt_call15.data.data = (void*)sjg_string95;
#line 60
    sjt_call15.data._isGlobal = true;
#line 60
    sjt_call15.data.count = 13;
#line 60
    sjf_array_char(&sjt_call15.data);
#line 60
    sjf_string(&sjt_call15);
#line 60
    sjt_functionParam135 = &sjt_call15;
#line 60
    sjf_glGetUniformLocation(sjt_functionParam134, sjt_functionParam135, &sjt_functionParam133);
#line 50
    sjt_dot1309 = _parent;
#line 1 "lib/ui/scene3dElement.sj"
    sjt_dot1308 = &(sjt_dot1309)->_light;
#line 19 "lib/ui/color.sj"
    sjt_parent54 = &(sjt_dot1308)->diffuseColor;
#line 19
    sjf_color_asVec3(sjt_parent54, &sjt_call16);
#line 60 "lib/ui/model.sj"
    sjt_functionParam136 = &sjt_call16;
#line 60
    sjf_glUniformVec3(sjt_functionParam133, sjt_functionParam136);
#line 50
    sjt_dot1310 = _parent;
#line 61
    sjt_functionParam138 = &(sjt_dot1310)->shader;
#line 61
    sjt_call17.count = 9;
#line 61
    sjt_call17.data.dataSize = 10;
#line 61
    sjt_call17.data.data = (void*)sjg_string96;
#line 61
    sjt_call17.data._isGlobal = true;
#line 61
    sjt_call17.data.count = 10;
#line 61
    sjf_array_char(&sjt_call17.data);
#line 61
    sjf_string(&sjt_call17);
#line 61
    sjt_functionParam139 = &sjt_call17;
#line 61
    sjf_glGetUniformLocation(sjt_functionParam138, sjt_functionParam139, &sjt_functionParam137);
#line 50
    sjt_dot1312 = _parent;
#line 1 "lib/ui/scene3dElement.sj"
    sjt_dot1311 = &(sjt_dot1312)->_light;
#line 19 "lib/ui/color.sj"
    sjt_parent55 = &(sjt_dot1311)->specColor;
#line 19
    sjf_color_asVec3(sjt_parent55, &sjt_call18);
#line 61 "lib/ui/model.sj"
    sjt_functionParam140 = &sjt_call18;
#line 61
    sjf_glUniformVec3(sjt_functionParam137, sjt_functionParam140);
#line 50
    sjt_dot1313 = _parent;
#line 88 "lib/ui/vertexBuffer.sj"
    sjt_parent56 = &(sjt_dot1313)->vertexBuffer;
#line 88
    sjf_vertexBuffer_vertex_location_texture_normal_render(sjt_parent56);

    sjf_mat4_destroy(&sjt_call10);
    sjf_string_destroy(&sjt_call11);
    sjf_string_destroy(&sjt_call12);
    sjf_string_destroy(&sjt_call13);
    sjf_string_destroy(&sjt_call14);
    sjf_string_destroy(&sjt_call15);
    sjf_vec3_destroy(&sjt_call16);
    sjf_string_destroy(&sjt_call17);
    sjf_vec3_destroy(&sjt_call18);
    sjf_mat4_destroy(&sjv_normalMat);
    sjf_mat4_destroy(&sjv_viewWorld);
    sjf_mat4_destroy(&sjv_world);
}

void sjf_model_renderOrQueue(sjs_model* _parent, sjs_list_heap_model* zqueue) {
    sjs_model* sjt_dot539;
    bool sjt_ifElse13;

#line 42 "lib/ui/model.sj"
    sjt_dot539 = _parent;
#line 43
    sjt_ifElse13 = (sjt_dot539)->hasAlpha;
    if (sjt_ifElse13) {
        sjs_model_heap* sjt_cast10;
        sji_nauScene3dElement_model* sjt_functionParam109;
        sjs_list_heap_model* sjt_parent47;

#line 42 "lib/ui/model.sj"
        sjt_parent47 = zqueue;
#line 44
        sjt_cast10 = (sjs_model_heap*)((char*)_parent - sizeof(intptr_t));
#line 44
        sjt_cast10->_refCount++;
#line 1
        sjt_functionParam109 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast10);
#line 1
        sjf_list_heap_model_add(sjt_parent47, sjt_functionParam109);

        sjt_cast10->_refCount--;
        if (sjt_cast10->_refCount <= 0) {
            sjf_model_destroy((sjs_model*)(((char*)sjt_cast10) + sizeof(intptr_t)));
        }
        sjt_functionParam109->_refCount--;
        if (sjt_functionParam109->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjt_functionParam109);
        }
    } else {
        sjf_model_render(_parent);
    }
}

void sjf_model_update(sjs_model* _parent, sjs_rect* sceneRect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light) {
    sjs_mat4 sjt_call8;
    sjs_vec4 sjt_call9;
    sjs_mat4* sjt_copy5;
    sjs_mat4* sjt_copy6;
    sjs_mat4* sjt_copy7;
    sjs_light* sjt_copy8;
    sjs_model* sjt_dot197;
    sjs_model* sjt_dot198;
    sjs_model* sjt_dot199;
    sjs_model* sjt_dot456;
    sjs_model* sjt_dot457;
    sjs_model* sjt_dot458;
    sjs_vec3* sjt_dot523;
    sjs_model* sjt_dot524;
    sjs_vec3* sjt_dot525;
    sjs_model* sjt_dot526;
    sjs_vec3* sjt_dot527;
    sjs_model* sjt_dot528;
    sjs_model* sjt_dot529;
    sjs_vec4* sjt_dot530;
    sjs_vec4* sjt_dot531;
    sjs_vec4* sjt_dot532;
    sjs_vec4* sjt_dot533;
    sjs_vec4* sjt_dot534;
    sjs_vec4* sjt_dot535;
    sjs_model* sjt_dot536;
    sjs_mat4* sjt_functionParam101;
    sjs_mat4* sjt_functionParam102;
    sjs_vec4* sjt_functionParam103;
    float sjt_math745;
    float sjt_math746;
    float sjt_math747;
    float sjt_math748;
    float sjt_math749;
    float sjt_math750;
    sjs_mat4* sjt_parent42;
    sjs_mat4* sjt_parent43;
    sjs_mat4* sjt_parent44;
    sjs_mat4 sjv_t;
    sjs_vec4 sjv_t2;

#line 27 "lib/ui/model.sj"
    sjt_dot197 = _parent;
#line 27
    sjt_copy5 = projection;
#line 28
    sjf_mat4_copy(&sjt_dot197->_projection, sjt_copy5);
#line 27
    sjt_dot198 = _parent;
#line 27
    sjt_copy6 = view;
#line 29
    sjf_mat4_copy(&sjt_dot198->_view, sjt_copy6);
#line 27
    sjt_dot199 = _parent;
#line 27
    sjt_copy7 = world;
#line 30
    sjf_mat4_copy(&sjt_dot199->_world, sjt_copy7);
#line 27
    sjt_dot456 = _parent;
#line 19 "lib/ui/mat4.sj"
    sjt_parent43 = &(sjt_dot456)->_view;
#line 27 "lib/ui/model.sj"
    sjt_dot457 = _parent;
#line 31
    sjt_functionParam101 = &(sjt_dot457)->_world;
#line 31
    sjf_mat4_multiply(sjt_parent43, sjt_functionParam101, &sjt_call8);
#line 31
    sjt_parent42 = &sjt_call8;
#line 27
    sjt_dot458 = _parent;
#line 31
    sjt_functionParam102 = &(sjt_dot458)->model;
#line 31
    sjf_mat4_multiply(sjt_parent42, sjt_functionParam102, &sjv_t);
#line 62 "lib/ui/mat4.sj"
    sjt_parent44 = &sjv_t;
#line 27 "lib/ui/model.sj"
    sjt_dot524 = _parent;
#line 1 "lib/ui/vec3.sj"
    sjt_dot523 = &(sjt_dot524)->center;
#line 32 "lib/ui/model.sj"
    sjt_call9.x = (sjt_dot523)->x;
#line 27
    sjt_dot526 = _parent;
#line 1 "lib/ui/vec3.sj"
    sjt_dot525 = &(sjt_dot526)->center;
#line 32 "lib/ui/model.sj"
    sjt_call9.y = (sjt_dot525)->y;
#line 27
    sjt_dot528 = _parent;
#line 1 "lib/ui/vec3.sj"
    sjt_dot527 = &(sjt_dot528)->center;
#line 32 "lib/ui/model.sj"
    sjt_call9.z = (sjt_dot527)->z;
#line 32
    sjt_call9.w = 1.0f;
#line 32
    sjf_vec4(&sjt_call9);
#line 32
    sjt_functionParam103 = &sjt_call9;
#line 32
    sjf_mat4_multiplyVec4(sjt_parent44, sjt_functionParam103, &sjv_t2);
#line 27
    sjt_dot529 = _parent;
#line 1 "lib/ui/vec4.sj"
    sjt_dot530 = &sjv_t2;
#line 33 "lib/ui/model.sj"
    sjt_math745 = (sjt_dot530)->x;
#line 1 "lib/ui/vec4.sj"
    sjt_dot531 = &sjv_t2;
#line 33 "lib/ui/model.sj"
    sjt_math746 = (sjt_dot531)->w;
#line 33
    sjt_dot529->_projectedCenter.x = sjt_math745 / sjt_math746;
#line 1 "lib/ui/vec4.sj"
    sjt_dot532 = &sjv_t2;
#line 33 "lib/ui/model.sj"
    sjt_math747 = (sjt_dot532)->y;
#line 1 "lib/ui/vec4.sj"
    sjt_dot533 = &sjv_t2;
#line 33 "lib/ui/model.sj"
    sjt_math748 = (sjt_dot533)->w;
#line 33
    sjt_dot529->_projectedCenter.y = sjt_math747 / sjt_math748;
#line 1 "lib/ui/vec4.sj"
    sjt_dot534 = &sjv_t2;
#line 33 "lib/ui/model.sj"
    sjt_math749 = (sjt_dot534)->z;
#line 1 "lib/ui/vec4.sj"
    sjt_dot535 = &sjv_t2;
#line 33 "lib/ui/model.sj"
    sjt_math750 = (sjt_dot535)->w;
#line 33
    sjt_dot529->_projectedCenter.z = sjt_math749 / sjt_math750;
#line 33
    sjf_vec3(&sjt_dot529->_projectedCenter);
#line 27
    sjt_dot536 = _parent;
#line 27
    sjt_copy8 = light;
#line 34
    sjf_light_copy(&sjt_dot536->_light, sjt_copy8);

    sjf_mat4_destroy(&sjt_call8);
    sjf_vec4_destroy(&sjt_call9);
    sjf_mat4_destroy(&sjv_t);
    sjf_vec4_destroy(&sjv_t2);
}

void sjf_model_zsort(sji_nauScene3dElement_model* l, sji_nauScene3dElement_model* r, int32_t* _return) {
    float sjt_functionParam46;
    float sjt_functionParam47;
    sji_nauScene3dElement_model* sjt_parent15;
    sji_nauScene3dElement_model* sjt_parent16;

#line 9 "lib/ui/model.sj"
    sjt_parent15 = l;
#line 10
    sjt_parent15->getZ((void*)(((char*)sjt_parent15->_parent) + sizeof(intptr_t)), &sjt_functionParam46);
#line 9
    sjt_parent16 = r;
#line 10
    sjt_parent16->getZ((void*)(((char*)sjt_parent16->_parent) + sizeof(intptr_t)), &sjt_functionParam47);
#line 10
    sjf_f32_compare(sjt_functionParam46, sjt_functionParam47, _return);
}

void sjf_model_zsort_callback(void * _parent, sji_nauScene3dElement_model* l, sji_nauScene3dElement_model* r, int32_t* _return) {
    sjf_model_zsort(l, r, _return);
}

void sjf_nauScene3dElement(sjs_nauScene3dElement* _this) {
}

sjs_object* sjf_nauScene3dElement_asInterface(sjs_nauScene3dElement* _this, int typeId) {
    switch (typeId) {
        case sji_element_typeId:  {
            return (sjs_object*)sjf_nauScene3dElement_as_sji_element(_this);
        }
    }

    return 0;
}

sji_element* sjf_nauScene3dElement_as_sji_element(sjs_nauScene3dElement* _this) {
    sji_element* _interface;
    _interface = (sji_element*)malloc(sizeof(sji_element));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_nauScene3dElement_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_nauScene3dElement_asInterface;
    _interface->getSize = (void(*)(void*,sjs_size*, sjs_size*))sjf_nauScene3dElement_getSize;
    _interface->getSize_heap = (void(*)(void*,sjs_size*, sjs_size_heap**))sjf_nauScene3dElement_getSize_heap;
    _interface->getRect = (void(*)(void*, sjs_rect**))sjf_nauScene3dElement_getRect;
    _interface->setRect = (void(*)(void*,sjs_rect*))sjf_nauScene3dElement_setRect;
    _interface->render = (void(*)(void*,sjs_scene2d*))sjf_nauScene3dElement_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_nauScene3dElement_fireMouseEvent;

    return _interface;
}

void sjf_nauScene3dElement_copy(sjs_nauScene3dElement* _this, sjs_nauScene3dElement* _from) {
#line 1 "nau/nauScene3dElement.sj"
    sjf_array_heap_model_copy(&_this->children, &_from->children);
#line 1
    sjf_vec3_copy(&_this->lookAtMin, &_from->lookAtMin);
#line 1
    sjf_vec3_copy(&_this->lookAtMax, &_from->lookAtMax);
#line 1
    _this->fieldOfView = _from->fieldOfView;
#line 1
    _this->zNear = _from->zNear;
#line 1
    _this->zFar = _from->zFar;
#line 1
    sjf_light_copy(&_this->light, &_from->light);
#line 1
    sjf_mat4_copy(&_this->projection, &_from->projection);
#line 1
    sjf_mat4_copy(&_this->view, &_from->view);
#line 1
    sjf_mat4_copy(&_this->world, &_from->world);
#line 1
    sjf_rect_copy(&_this->_rect, &_from->_rect);
#line 1
    _this->_isDragging = _from->_isDragging;
#line 1
    sjf_point_copy(&_this->_startDrag, &_from->_startDrag);
#line 1
    sjf_vec3_copy(&_this->_lookAt, &_from->_lookAt);
#line 1
    sjf_vec3_copy(&_this->_lookAtDrag, &_from->_lookAtDrag);
}

void sjf_nauScene3dElement_destroy(sjs_nauScene3dElement* _this) {
}

void sjf_nauScene3dElement_fireMouseEvent(sjs_nauScene3dElement* _parent, sjs_point* point, int32_t eventId) {
    int32_t i;
    bool sjt_and7;
    bool sjt_and8;
    int32_t sjt_compare33;
    int32_t sjt_compare34;
    int32_t sjt_compare35;
    int32_t sjt_compare36;
    int32_t sjt_compare41;
    int32_t sjt_compare42;
    sjs_array_heap_model* sjt_dot194;
    sjs_nauScene3dElement* sjt_dot195;
    sjs_nauScene3dElement* sjt_dot61;
    int32_t sjt_forEnd7;
    int32_t sjt_forStart7;
    bool sjt_ifElse12;
    bool sjt_ifElse8;
    bool sjt_ifElse9;

#line 57 "nau/nauScene3dElement.sj"
    sjt_compare33 = eventId;
#line 58
    sjt_compare34 = sjv_mouseEvent_down;
#line 58
    sjt_ifElse8 = sjt_compare33 == sjt_compare34;
    if (sjt_ifElse8) {
        sjs_point* sjt_copy3;
        sjs_vec3* sjt_copy4;
        sjs_nauScene3dElement* sjt_dot57;
        sjs_nauScene3dElement* sjt_dot58;
        sjs_nauScene3dElement* sjt_dot59;
        sjs_nauScene3dElement* sjt_dot60;

#line 57 "nau/nauScene3dElement.sj"
        sjt_dot57 = _parent;
#line 59
        sjt_dot57->_isDragging = true;
#line 57
        sjt_dot58 = _parent;
#line 57
        sjt_copy3 = point;
#line 60
        sjf_point_copy(&sjt_dot58->_startDrag, sjt_copy3);
#line 57
        sjt_dot59 = _parent;
#line 57
        sjt_dot60 = _parent;
#line 61
        sjt_copy4 = &(sjt_dot60)->_lookAt;
#line 61
        sjf_vec3_copy(&sjt_dot59->_lookAtDrag, sjt_copy4);
    }

#line 57
    sjt_compare35 = eventId;
#line 64
    sjt_compare36 = sjv_mouseEvent_move;
#line 64
    sjt_and7 = sjt_compare35 == sjt_compare36;
#line 57
    sjt_dot61 = _parent;
#line 64
    sjt_and8 = (sjt_dot61)->_isDragging;
#line 64
    sjt_ifElse9 = sjt_and7 && sjt_and8;
    if (sjt_ifElse9) {
        sjs_vec3 sjt_call1;
        sjs_vec3 sjt_call2;
        sjs_vec3 sjt_call3;
        sjs_vec3 sjt_call4;
        sjs_vec3 sjt_call7;
        int32_t sjt_cast5;
        int32_t sjt_cast6;
        int32_t sjt_cast7;
        int32_t sjt_cast8;
        sjs_nauScene3dElement* sjt_dot101;
        sjs_point* sjt_dot102;
        sjs_nauScene3dElement* sjt_dot103;
        sjs_point* sjt_dot104;
        sjs_rect* sjt_dot105;
        sjs_nauScene3dElement* sjt_dot106;
        sjs_point* sjt_dot107;
        sjs_point* sjt_dot108;
        sjs_nauScene3dElement* sjt_dot109;
        sjs_rect* sjt_dot110;
        sjs_nauScene3dElement* sjt_dot111;
        sjs_nauScene3dElement* sjt_dot124;
        sjs_nauScene3dElement* sjt_dot125;
        sjs_nauScene3dElement* sjt_dot192;
        sjs_nauScene3dElement* sjt_dot62;
        sjs_nauScene3dElement* sjt_dot75;
        sjs_nauScene3dElement* sjt_dot88;
        sjs_vec3* sjt_functionParam63;
        sjs_vec3* sjt_functionParam64;
        sjs_vec3* sjt_functionParam77;
        sjs_vec3* sjt_functionParam78;
        sjs_vec3* sjt_functionParam79;
        sjs_vec3* sjt_functionParam80;
        sjs_vec3* sjt_functionParam95;
        sjs_vec3* sjt_functionParam96;
        sjs_vec3* sjt_functionParam97;
        float sjt_math71;
        float sjt_math72;
        float sjt_math73;
        float sjt_math74;
        int32_t sjt_math75;
        int32_t sjt_math76;
        float sjt_math77;
        float sjt_math78;
        float sjt_math79;
        float sjt_math80;
        int32_t sjt_math81;
        int32_t sjt_math82;
        sjs_vec3* sjt_parent21;
        sjs_vec3* sjt_parent22;
        sjs_vec3 sjv_camera;

#line 57 "nau/nauScene3dElement.sj"
        sjt_dot62 = _parent;
#line 57
        sjt_dot75 = _parent;
#line 65
        sjt_functionParam63 = &(sjt_dot75)->lookAtMax;
#line 57
        sjt_dot88 = _parent;
#line 65
        sjt_functionParam77 = &(sjt_dot88)->lookAtMin;
#line 57
        sjt_dot101 = _parent;
#line 22 "lib/ui/vec3.sj"
        sjt_parent21 = &(sjt_dot101)->_lookAtDrag;
#line 57 "nau/nauScene3dElement.sj"
        sjt_dot103 = _parent;
#line 1 "lib/ui/point.sj"
        sjt_dot102 = &(sjt_dot103)->_startDrag;
#line 66 "nau/nauScene3dElement.sj"
        sjt_math75 = (sjt_dot102)->x;
#line 57
        sjt_dot104 = point;
#line 66
        sjt_math76 = (sjt_dot104)->x;
#line 66
        sjt_cast5 = sjt_math75 - sjt_math76;
#line 66
        sjt_math73 = (float)sjt_cast5;
#line 57
        sjt_dot106 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot105 = &(sjt_dot106)->_rect;
#line 66 "nau/nauScene3dElement.sj"
        sjt_cast6 = (sjt_dot105)->w;
#line 66
        sjt_math74 = (float)sjt_cast6;
#line 66
        sjt_math71 = sjt_math73 / sjt_math74;
#line 66
        sjt_math72 = 2.0f;
#line 66
        sjt_call3.x = sjt_math71 * sjt_math72;
#line 57
        sjt_dot107 = point;
#line 67
        sjt_math81 = (sjt_dot107)->y;
#line 57
        sjt_dot109 = _parent;
#line 1 "lib/ui/point.sj"
        sjt_dot108 = &(sjt_dot109)->_startDrag;
#line 67 "nau/nauScene3dElement.sj"
        sjt_math82 = (sjt_dot108)->y;
#line 67
        sjt_cast7 = sjt_math81 - sjt_math82;
#line 67
        sjt_math79 = (float)sjt_cast7;
#line 57
        sjt_dot111 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot110 = &(sjt_dot111)->_rect;
#line 67 "nau/nauScene3dElement.sj"
        sjt_cast8 = (sjt_dot110)->h;
#line 67
        sjt_math80 = (float)sjt_cast8;
#line 67
        sjt_math77 = sjt_math79 / sjt_math80;
#line 67
        sjt_math78 = 2.0f;
#line 67
        sjt_call3.y = sjt_math77 * sjt_math78;
#line 68
        sjt_call3.z = 0.0f;
#line 68
        sjf_vec3(&sjt_call3);
#line 65
        sjt_functionParam79 = &sjt_call3;
#line 65
        sjf_vec3_add(sjt_parent21, sjt_functionParam79, &sjt_call2);
#line 65
        sjt_functionParam78 = &sjt_call2;
#line 65
        sjf_vec3_max(sjt_functionParam77, sjt_functionParam78, &sjt_call1);
#line 65
        sjt_functionParam64 = &sjt_call1;
#line 65
        sjf_vec3_min(sjt_functionParam63, sjt_functionParam64, &sjt_dot62->_lookAt);
#line 57
        sjt_dot124 = _parent;
#line 30 "lib/ui/vec3.sj"
        sjt_parent22 = &(sjt_dot124)->_lookAt;
#line 70 "nau/nauScene3dElement.sj"
        sjt_call4.x = 0.0f;
#line 70
        sjt_call4.y = 0.0f;
#line 70
        sjt_call4.z = 5.0f;
#line 70
        sjf_vec3(&sjt_call4);
#line 70
        sjt_functionParam80 = &sjt_call4;
#line 70
        sjf_vec3_subtract(sjt_parent22, sjt_functionParam80, &sjv_camera);
#line 57
        sjt_dot125 = _parent;
#line 71
        sjt_functionParam95 = &sjv_camera;
#line 57
        sjt_dot192 = _parent;
#line 71
        sjt_functionParam96 = &(sjt_dot192)->_lookAt;
#line 71
        sjt_call7.x = 0.0f;
#line 71
        sjt_call7.y = 1.0f;
#line 71
        sjt_call7.z = 0.0f;
#line 71
        sjf_vec3(&sjt_call7);
#line 71
        sjt_functionParam97 = &sjt_call7;
#line 71
        sjf_mat4_lookAtLH(sjt_functionParam95, sjt_functionParam96, sjt_functionParam97, &sjt_dot125->view);

        sjf_vec3_destroy(&sjt_call1);
        sjf_vec3_destroy(&sjt_call2);
        sjf_vec3_destroy(&sjt_call3);
        sjf_vec3_destroy(&sjt_call4);
        sjf_vec3_destroy(&sjt_call7);
        sjf_vec3_destroy(&sjv_camera);
    }

#line 57
    sjt_compare41 = eventId;
#line 74
    sjt_compare42 = sjv_mouseEvent_up;
#line 74
    sjt_ifElse12 = sjt_compare41 == sjt_compare42;
    if (sjt_ifElse12) {
        sjs_nauScene3dElement* sjt_dot193;

#line 57 "nau/nauScene3dElement.sj"
        sjt_dot193 = _parent;
#line 75
        sjt_dot193->_isDragging = false;
    }

#line 78
    sjt_forStart7 = 0;
#line 57
    sjt_dot195 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot194 = &(sjt_dot195)->children;
#line 78 "nau/nauScene3dElement.sj"
    sjt_forEnd7 = (sjt_dot194)->count;
#line 78
    i = sjt_forStart7;
    while (i < sjt_forEnd7) {
        sjs_nauScene3dElement* sjt_dot196;
        int32_t sjt_functionParam98;
        sjs_point* sjt_interfaceParam11;
        int32_t sjt_interfaceParam12;
        sjs_array_heap_model* sjt_parent39;
        sji_nauScene3dElement_model* sjt_parent40;
        sji_nauScene3dElement_model* sjv_child;

#line 57 "nau/nauScene3dElement.sj"
        sjt_dot196 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent39 = &(sjt_dot196)->children;
#line 78 "nau/nauScene3dElement.sj"
        sjt_functionParam98 = i;
#line 78
        sjf_array_heap_model_getAt_heap(sjt_parent39, sjt_functionParam98, &sjv_child);
#line 6 "lib/ui/model.sj"
        sjt_parent40 = sjv_child;
#line 57 "nau/nauScene3dElement.sj"
        sjt_interfaceParam11 = point;
#line 57
        sjt_interfaceParam12 = eventId;
#line 80
        sjt_parent40->fireMouseEvent((void*)(((char*)sjt_parent40->_parent) + sizeof(intptr_t)), sjt_interfaceParam11, sjt_interfaceParam12);
#line 78
        i++;

        sjv_child->_refCount--;
        if (sjv_child->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_child);
        }
    }
}

void sjf_nauScene3dElement_getRect(sjs_nauScene3dElement* _parent, sjs_rect** _return) {
    sjs_nauScene3dElement* sjt_dot21;

#line 18 "nau/nauScene3dElement.sj"
    sjt_dot21 = _parent;
#line 18
    (*_return) = &(sjt_dot21)->_rect;
}

void sjf_nauScene3dElement_getSize(sjs_nauScene3dElement* _parent, sjs_size* maxSize, sjs_size* _return) {
    sjs_size* sjt_dot17;
    sjs_size* sjt_dot18;

#line 14 "nau/nauScene3dElement.sj"
    sjt_dot17 = maxSize;
#line 15
    _return->w = (sjt_dot17)->w;
#line 14
    sjt_dot18 = maxSize;
#line 15
    _return->h = (sjt_dot18)->h;
#line 15
    sjf_size(_return);
}

void sjf_nauScene3dElement_getSize_heap(sjs_nauScene3dElement* _parent, sjs_size* maxSize, sjs_size_heap** _return) {
    sjs_size* sjt_dot19;
    sjs_size* sjt_dot20;

    (*_return) = (sjs_size_heap*)malloc(sizeof(sjs_size_heap));
    (*_return)->_refCount = 1;
#line 14 "nau/nauScene3dElement.sj"
    sjt_dot19 = maxSize;
#line 15
    (*_return)->w = (sjt_dot19)->w;
#line 14
    sjt_dot20 = maxSize;
#line 15
    (*_return)->h = (sjt_dot20)->h;
#line 15
    sjf_size_heap((*_return));
}

void sjf_nauScene3dElement_heap(sjs_nauScene3dElement_heap* _this) {
}

sjs_object* sjf_nauScene3dElement_heap_asInterface(sjs_nauScene3dElement_heap* _this, int typeId) {
    switch (typeId) {
        case sji_element_typeId:  {
            return (sjs_object*)sjf_nauScene3dElement_heap_as_sji_element(_this);
        }
    }

    return 0;
}

sji_element* sjf_nauScene3dElement_heap_as_sji_element(sjs_nauScene3dElement_heap* _this) {
    sji_element* _interface;
    _interface = (sji_element*)malloc(sizeof(sji_element));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_nauScene3dElement_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_nauScene3dElement_heap_asInterface;
    _interface->getSize = (void(*)(void*,sjs_size*, sjs_size*))sjf_nauScene3dElement_getSize;
    _interface->getSize_heap = (void(*)(void*,sjs_size*, sjs_size_heap**))sjf_nauScene3dElement_getSize_heap;
    _interface->getRect = (void(*)(void*, sjs_rect**))sjf_nauScene3dElement_getRect;
    _interface->setRect = (void(*)(void*,sjs_rect*))sjf_nauScene3dElement_setRect;
    _interface->render = (void(*)(void*,sjs_scene2d*))sjf_nauScene3dElement_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_nauScene3dElement_fireMouseEvent;

    return _interface;
}

void sjf_nauScene3dElement_render(sjs_nauScene3dElement* _parent, sjs_scene2d* scene) {
    int32_t i;
    sjs_array_heap_model* sjt_dot40;
    sjs_nauScene3dElement* sjt_dot41;
    sjs_array_heap_model* sjt_dot48;
    sjs_nauScene3dElement* sjt_dot49;
    int32_t sjt_forEnd4;
    int32_t sjt_forEnd5;
    int32_t sjt_forEnd6;
    int32_t sjt_forStart4;
    int32_t sjt_forStart5;
    int32_t sjt_forStart6;
    int32_t sjt_functionParam14;
    cb_heap_model_heap_model_i32 sjt_functionParam45;
    int32_t sjt_functionParam50;
    sjs_list_heap_model* sjt_parent14;
    sjs_list_heap_model* sjt_parent17;
    sjs_list_heap_model sjv_a;

#line 29 "nau/nauScene3dElement.sj"
    sjt_forStart4 = 0;
#line 28
    sjt_dot41 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot40 = &(sjt_dot41)->children;
#line 29 "nau/nauScene3dElement.sj"
    sjt_forEnd4 = (sjt_dot40)->count;
#line 29
    i = sjt_forStart4;
    while (i < sjt_forEnd4) {
        sjs_nauScene3dElement* sjt_dot42;
        sjs_nauScene3dElement* sjt_dot43;
        sjs_nauScene3dElement* sjt_dot44;
        sjs_nauScene3dElement* sjt_dot45;
        sjs_nauScene3dElement* sjt_dot46;
        sjs_nauScene3dElement* sjt_dot47;
        int32_t sjt_functionParam13;
        sjs_rect* sjt_interfaceParam5;
        sjs_mat4* sjt_interfaceParam6;
        sjs_mat4* sjt_interfaceParam7;
        sjs_mat4* sjt_interfaceParam8;
        sjs_light* sjt_interfaceParam9;
        sji_nauScene3dElement_model* sjt_parent10;
        sjs_array_heap_model* sjt_parent9;
        sji_nauScene3dElement_model* sjv_child;

#line 28 "nau/nauScene3dElement.sj"
        sjt_dot42 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent9 = &(sjt_dot42)->children;
#line 29 "nau/nauScene3dElement.sj"
        sjt_functionParam13 = i;
#line 29
        sjf_array_heap_model_getAt_heap(sjt_parent9, sjt_functionParam13, &sjv_child);
#line 2 "lib/ui/model.sj"
        sjt_parent10 = sjv_child;
#line 28 "nau/nauScene3dElement.sj"
        sjt_dot43 = _parent;
#line 31
        sjt_interfaceParam5 = &(sjt_dot43)->_rect;
#line 28
        sjt_dot44 = _parent;
#line 31
        sjt_interfaceParam6 = &(sjt_dot44)->projection;
#line 28
        sjt_dot45 = _parent;
#line 31
        sjt_interfaceParam7 = &(sjt_dot45)->view;
#line 28
        sjt_dot46 = _parent;
#line 31
        sjt_interfaceParam8 = &(sjt_dot46)->world;
#line 28
        sjt_dot47 = _parent;
#line 31
        sjt_interfaceParam9 = &(sjt_dot47)->light;
#line 31
        sjt_parent10->update((void*)(((char*)sjt_parent10->_parent) + sizeof(intptr_t)), sjt_interfaceParam5, sjt_interfaceParam6, sjt_interfaceParam7, sjt_interfaceParam8, sjt_interfaceParam9);
#line 29
        i++;

        sjv_child->_refCount--;
        if (sjv_child->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_child);
        }
    }

#line 34
    sjt_functionParam14 = sjv_glFeature_GL_DEPTH_TEST;
#line 34
    sjf_glEnable(sjt_functionParam14);
#line 2 "lib/common/list.sj"
    sjv_a.array.dataSize = 0;
#line 3 "lib/common/array.sj"
    sjv_a.array.data = 0;
#line 4
    sjv_a.array._isGlobal = false;
#line 5
    sjv_a.array.count = 0;
#line 5
    sjf_array_heap_model(&sjv_a.array);
#line 5
    sjf_list_heap_model(&sjv_a);
#line 38 "nau/nauScene3dElement.sj"
    sjt_forStart5 = 0;
#line 28
    sjt_dot49 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot48 = &(sjt_dot49)->children;
#line 38 "nau/nauScene3dElement.sj"
    sjt_forEnd5 = (sjt_dot48)->count;
#line 38
    i = sjt_forStart5;
    while (i < sjt_forEnd5) {
        sjs_nauScene3dElement* sjt_dot50;
        int32_t sjt_functionParam15;
        sjs_list_heap_model* sjt_interfaceParam10;
        sjs_array_heap_model* sjt_parent11;
        sji_nauScene3dElement_model* sjt_parent12;
        sji_nauScene3dElement_model* sjv_child;

#line 28 "nau/nauScene3dElement.sj"
        sjt_dot50 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent11 = &(sjt_dot50)->children;
#line 38 "nau/nauScene3dElement.sj"
        sjt_functionParam15 = i;
#line 38
        sjf_array_heap_model_getAt_heap(sjt_parent11, sjt_functionParam15, &sjv_child);
#line 4 "lib/ui/model.sj"
        sjt_parent12 = sjv_child;
#line 40 "nau/nauScene3dElement.sj"
        sjt_interfaceParam10 = &sjv_a;
#line 40
        sjt_parent12->renderOrQueue((void*)(((char*)sjt_parent12->_parent) + sizeof(intptr_t)), sjt_interfaceParam10);
#line 38
        i++;

        sjv_child->_refCount--;
        if (sjv_child->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_child);
        }
    }

#line 28 "lib/common/list.sj"
    sjt_parent14 = &sjv_a;
#line 43 "nau/nauScene3dElement.sj"
    sjt_functionParam45._parent = (void*)1;
#line 43
    sjt_functionParam45._cb = (void(*)(void*,sji_nauScene3dElement_model*,sji_nauScene3dElement_model*, int32_t*))sjf_model_zsort_callback;
#line 43
    sjf_list_heap_model_sortcb(sjt_parent14, sjt_functionParam45);
#line 44
    sjt_forStart6 = 0;
#line 4 "lib/common/list.sj"
    sjt_parent17 = &sjv_a;
#line 4
    sjf_list_heap_model_getCount(sjt_parent17, &sjt_forEnd6);
#line 44 "nau/nauScene3dElement.sj"
    i = sjt_forStart6;
    while (i < sjt_forEnd6) {
        int32_t sjt_functionParam49;
        sjs_list_heap_model* sjt_parent19;
        sji_nauScene3dElement_model* sjt_parent20;
        sji_nauScene3dElement_model* sjv_child;

#line 8 "lib/common/list.sj"
        sjt_parent19 = &sjv_a;
#line 44 "nau/nauScene3dElement.sj"
        sjt_functionParam49 = i;
#line 44
        sjf_list_heap_model_getAt_heap(sjt_parent19, sjt_functionParam49, &sjv_child);
#line 5 "lib/ui/model.sj"
        sjt_parent20 = sjv_child;
#line 46 "nau/nauScene3dElement.sj"
        sjt_parent20->render((void*)(((char*)sjt_parent20->_parent) + sizeof(intptr_t)));
#line 44
        i++;

        sjv_child->_refCount--;
        if (sjv_child->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_child);
        }
    }

#line 49
    sjt_functionParam50 = sjv_glFeature_GL_DEPTH_TEST;
#line 49
    sjf_glDisable(sjt_functionParam50);

    sjf_list_heap_model_destroy(&sjv_a);
}

void sjf_nauScene3dElement_setRect(sjs_nauScene3dElement* _parent, sjs_rect* rect_) {
    bool result2;
    sjs_nauScene3dElement* sjt_dot30;
    sjs_rect* sjt_functionParam6;
    bool sjt_ifElse1;
    bool sjt_not1;
    sjs_rect* sjt_parent8;

#line 20 "nau/nauScene3dElement.sj"
    sjt_dot30 = _parent;
#line 15 "lib/ui/rect.sj"
    sjt_parent8 = &(sjt_dot30)->_rect;
#line 20 "nau/nauScene3dElement.sj"
    sjt_functionParam6 = rect_;
#line 20
    sjf_rect_isEqual(sjt_parent8, sjt_functionParam6, &sjt_not1);
#line 21
    result2 = !sjt_not1;
#line 21
    sjt_ifElse1 = result2;
    if (sjt_ifElse1) {
        int32_t sjt_cast3;
        int32_t sjt_cast4;
        sjs_rect* sjt_copy2;
        sjs_nauScene3dElement* sjt_dot31;
        sjs_nauScene3dElement* sjt_dot32;
        sjs_nauScene3dElement* sjt_dot33;
        sjs_rect* sjt_dot34;
        sjs_nauScene3dElement* sjt_dot35;
        sjs_rect* sjt_dot36;
        sjs_nauScene3dElement* sjt_dot37;
        sjs_nauScene3dElement* sjt_dot38;
        sjs_nauScene3dElement* sjt_dot39;
        float sjt_functionParam10;
        float sjt_functionParam11;
        float sjt_functionParam12;
        float sjt_functionParam9;
        float sjt_math43;
        float sjt_math44;

#line 20 "nau/nauScene3dElement.sj"
        sjt_dot31 = _parent;
#line 20
        sjt_copy2 = rect_;
#line 22
        sjf_rect_copy(&sjt_dot31->_rect, sjt_copy2);
#line 20
        sjt_dot32 = _parent;
#line 20
        sjt_dot33 = _parent;
#line 23
        sjt_functionParam9 = (sjt_dot33)->fieldOfView;
#line 20
        sjt_dot35 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot34 = &(sjt_dot35)->_rect;
#line 23 "nau/nauScene3dElement.sj"
        sjt_cast3 = (sjt_dot34)->h;
#line 23
        sjt_math43 = (float)sjt_cast3;
#line 20
        sjt_dot37 = _parent;
#line 1 "lib/ui/rect.sj"
        sjt_dot36 = &(sjt_dot37)->_rect;
#line 23 "nau/nauScene3dElement.sj"
        sjt_cast4 = (sjt_dot36)->w;
#line 23
        sjt_math44 = (float)sjt_cast4;
#line 23
        sjt_functionParam10 = sjt_math43 / sjt_math44;
#line 20
        sjt_dot38 = _parent;
#line 23
        sjt_functionParam11 = (sjt_dot38)->zNear;
#line 20
        sjt_dot39 = _parent;
#line 23
        sjt_functionParam12 = (sjt_dot39)->zFar;
#line 23
        sjf_mat4_perspective(sjt_functionParam9, sjt_functionParam10, sjt_functionParam11, sjt_functionParam12, &sjt_dot32->projection);
    }
}

void sjf_panel3d(sjs_panel3d* _this) {
}

sjs_object* sjf_panel3d_asInterface(sjs_panel3d* _this, int typeId) {
    switch (typeId) {
        case sji_nauScene3dElement_model_typeId:  {
            return (sjs_object*)sjf_panel3d_as_sji_nauScene3dElement_model(_this);
        }
    }

    return 0;
}

sji_nauScene3dElement_model* sjf_panel3d_as_sji_nauScene3dElement_model(sjs_panel3d* _this) {
    sji_nauScene3dElement_model* _interface;
    _interface = (sji_nauScene3dElement_model*)malloc(sizeof(sji_nauScene3dElement_model));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_panel3d_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_panel3d_asInterface;
    _interface->update = (void(*)(void*,sjs_rect*,sjs_mat4*,sjs_mat4*,sjs_mat4*,sjs_light*))sjf_panel3d_update;
    _interface->getZ = (void(*)(void*, float*))sjf_panel3d_getZ;
    _interface->renderOrQueue = (void(*)(void*,sjs_list_heap_model*))sjf_panel3d_renderOrQueue;
    _interface->render = (void(*)(void*))sjf_panel3d_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_panel3d_fireMouseEvent;

    return _interface;
}

void sjf_panel3d_copy(sjs_panel3d* _this, sjs_panel3d* _from) {
#line 1 "lib/ui/panel3d.sj"
    sjf_mat4_copy(&_this->model, &_from->model);
#line 1
    sjf_array_heap_model_copy(&_this->children, &_from->children);
}

void sjf_panel3d_destroy(sjs_panel3d* _this) {
}

void sjf_panel3d_fireMouseEvent(sjs_panel3d* _parent, sjs_point* point, int32_t eventId) {
    int32_t i;
    sjs_array_heap_model* sjt_dot1361;
    sjs_panel3d* sjt_dot1362;
    int32_t sjt_forEnd17;
    int32_t sjt_forStart17;

#line 30 "lib/ui/panel3d.sj"
    sjt_forStart17 = 0;
#line 29
    sjt_dot1362 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot1361 = &(sjt_dot1362)->children;
#line 30 "lib/ui/panel3d.sj"
    sjt_forEnd17 = (sjt_dot1361)->count;
#line 30
    i = sjt_forStart17;
    while (i < sjt_forEnd17) {
        sjs_panel3d* sjt_dot1363;
        int32_t sjt_functionParam272;
        sjs_point* sjt_interfaceParam27;
        int32_t sjt_interfaceParam28;
        sjs_array_heap_model* sjt_parent115;
        sji_nauScene3dElement_model* sjt_parent116;
        sji_nauScene3dElement_model* sjv_c;

#line 29 "lib/ui/panel3d.sj"
        sjt_dot1363 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent115 = &(sjt_dot1363)->children;
#line 30 "lib/ui/panel3d.sj"
        sjt_functionParam272 = i;
#line 30
        sjf_array_heap_model_getAt_heap(sjt_parent115, sjt_functionParam272, &sjv_c);
#line 6 "lib/ui/model.sj"
        sjt_parent116 = sjv_c;
#line 29 "lib/ui/panel3d.sj"
        sjt_interfaceParam27 = point;
#line 29
        sjt_interfaceParam28 = eventId;
#line 32
        sjt_parent116->fireMouseEvent((void*)(((char*)sjt_parent116->_parent) + sizeof(intptr_t)), sjt_interfaceParam27, sjt_interfaceParam28);
#line 30
        i++;

        sjv_c->_refCount--;
        if (sjv_c->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_c);
        }
    }
}

void sjf_panel3d_getZ(sjs_panel3d* _parent, float* _return) {
#line 15 "lib/ui/panel3d.sj"
    (*_return) = 0.0f;
}

void sjf_panel3d_heap(sjs_panel3d_heap* _this) {
}

sjs_object* sjf_panel3d_heap_asInterface(sjs_panel3d_heap* _this, int typeId) {
    switch (typeId) {
        case sji_nauScene3dElement_model_typeId:  {
            return (sjs_object*)sjf_panel3d_heap_as_sji_nauScene3dElement_model(_this);
        }
    }

    return 0;
}

sji_nauScene3dElement_model* sjf_panel3d_heap_as_sji_nauScene3dElement_model(sjs_panel3d_heap* _this) {
    sji_nauScene3dElement_model* _interface;
    _interface = (sji_nauScene3dElement_model*)malloc(sizeof(sji_nauScene3dElement_model));
    _interface->_refCount = 1;
    _interface->_parent = (sjs_object*)_this;
    _interface->_parent->_refCount++;
    _interface->destroy = (void(*)(void*))sjf_panel3d_destroy;
    _interface->asInterface = (sjs_object*(*)(sjs_object*,int))sjf_panel3d_heap_asInterface;
    _interface->update = (void(*)(void*,sjs_rect*,sjs_mat4*,sjs_mat4*,sjs_mat4*,sjs_light*))sjf_panel3d_update;
    _interface->getZ = (void(*)(void*, float*))sjf_panel3d_getZ;
    _interface->renderOrQueue = (void(*)(void*,sjs_list_heap_model*))sjf_panel3d_renderOrQueue;
    _interface->render = (void(*)(void*))sjf_panel3d_render;
    _interface->fireMouseEvent = (void(*)(void*,sjs_point*,int32_t))sjf_panel3d_fireMouseEvent;

    return _interface;
}

void sjf_panel3d_render(sjs_panel3d* _parent) {
}

void sjf_panel3d_renderOrQueue(sjs_panel3d* _parent, sjs_list_heap_model* zqueue) {
    int32_t i;
    sjs_array_heap_model* sjt_dot1358;
    sjs_panel3d* sjt_dot1359;
    int32_t sjt_forEnd16;
    int32_t sjt_forStart16;

#line 19 "lib/ui/panel3d.sj"
    sjt_forStart16 = 0;
#line 18
    sjt_dot1359 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot1358 = &(sjt_dot1359)->children;
#line 19 "lib/ui/panel3d.sj"
    sjt_forEnd16 = (sjt_dot1358)->count;
#line 19
    i = sjt_forStart16;
    while (i < sjt_forEnd16) {
        sjs_panel3d* sjt_dot1360;
        int32_t sjt_functionParam271;
        sjs_list_heap_model* sjt_interfaceParam26;
        sjs_array_heap_model* sjt_parent113;
        sji_nauScene3dElement_model* sjt_parent114;
        sji_nauScene3dElement_model* sjv_c;

#line 18 "lib/ui/panel3d.sj"
        sjt_dot1360 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent113 = &(sjt_dot1360)->children;
#line 19 "lib/ui/panel3d.sj"
        sjt_functionParam271 = i;
#line 19
        sjf_array_heap_model_getAt_heap(sjt_parent113, sjt_functionParam271, &sjv_c);
#line 4 "lib/ui/model.sj"
        sjt_parent114 = sjv_c;
#line 18 "lib/ui/panel3d.sj"
        sjt_interfaceParam26 = zqueue;
#line 21
        sjt_parent114->renderOrQueue((void*)(((char*)sjt_parent114->_parent) + sizeof(intptr_t)), sjt_interfaceParam26);
#line 19
        i++;

        sjv_c->_refCount--;
        if (sjv_c->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_c);
        }
    }
}

void sjf_panel3d_update(sjs_panel3d* _parent, sjs_rect* sceneRect, sjs_mat4* projection, sjs_mat4* view, sjs_mat4* world, sjs_light* light) {
    int32_t i;
    sjs_panel3d* sjt_dot1354;
    sjs_array_heap_model* sjt_dot1355;
    sjs_panel3d* sjt_dot1356;
    int32_t sjt_forEnd15;
    int32_t sjt_forStart15;
    sjs_mat4* sjt_functionParam269;
    sjs_mat4* sjt_parent110;
    sjs_mat4 sjv_childWorld;

#line 5 "lib/ui/panel3d.sj"
    sjt_parent110 = world;
#line 5
    sjt_dot1354 = _parent;
#line 6
    sjt_functionParam269 = &(sjt_dot1354)->model;
#line 6
    sjf_mat4_multiply(sjt_parent110, sjt_functionParam269, &sjv_childWorld);
#line 7
    sjt_forStart15 = 0;
#line 5
    sjt_dot1356 = _parent;
#line 1 "lib/common/array.sj"
    sjt_dot1355 = &(sjt_dot1356)->children;
#line 7 "lib/ui/panel3d.sj"
    sjt_forEnd15 = (sjt_dot1355)->count;
#line 7
    i = sjt_forStart15;
    while (i < sjt_forEnd15) {
        sjs_panel3d* sjt_dot1357;
        int32_t sjt_functionParam270;
        sjs_rect* sjt_interfaceParam21;
        sjs_mat4* sjt_interfaceParam22;
        sjs_mat4* sjt_interfaceParam23;
        sjs_mat4* sjt_interfaceParam24;
        sjs_light* sjt_interfaceParam25;
        sjs_array_heap_model* sjt_parent111;
        sji_nauScene3dElement_model* sjt_parent112;
        sji_nauScene3dElement_model* sjv_c;

#line 5 "lib/ui/panel3d.sj"
        sjt_dot1357 = _parent;
#line 7 "lib/common/array.sj"
        sjt_parent111 = &(sjt_dot1357)->children;
#line 7 "lib/ui/panel3d.sj"
        sjt_functionParam270 = i;
#line 7
        sjf_array_heap_model_getAt_heap(sjt_parent111, sjt_functionParam270, &sjv_c);
#line 2 "lib/ui/model.sj"
        sjt_parent112 = sjv_c;
#line 5 "lib/ui/panel3d.sj"
        sjt_interfaceParam21 = sceneRect;
#line 5
        sjt_interfaceParam22 = projection;
#line 5
        sjt_interfaceParam23 = view;
#line 9
        sjt_interfaceParam24 = &sjv_childWorld;
#line 5
        sjt_interfaceParam25 = light;
#line 9
        sjt_parent112->update((void*)(((char*)sjt_parent112->_parent) + sizeof(intptr_t)), sjt_interfaceParam21, sjt_interfaceParam22, sjt_interfaceParam23, sjt_interfaceParam24, sjt_interfaceParam25);
#line 7
        i++;

        sjv_c->_refCount--;
        if (sjv_c->_refCount <= 0) {
            sji_nauScene3dElement_model_destroy(sjv_c);
        }
    }

    sjf_mat4_destroy(&sjv_childWorld);
}

void sjf_planeVertexBuffer(float x0, float x1, float y0, float y1, float z0, float s0, float s1, float t0, float t1, sjs_vertexBuffer_vertex_location_texture_normal* _return) {
    float result4;
    float result5;
    float result6;
    float result7;
    sjs_vertex_location_texture_normal sjt_call19;
    sjs_vertex_location_texture_normal sjt_call20;
    sjs_vertex_location_texture_normal sjt_call21;
    sjs_vertex_location_texture_normal sjt_call22;
    sjs_string* sjt_copy9;
    int32_t sjt_functionParam141;
    int32_t sjt_functionParam142;
    int32_t sjt_functionParam143;
    int32_t sjt_functionParam144;
    int32_t sjt_functionParam145;
    int32_t sjt_functionParam146;
    int32_t sjt_functionParam147;
    int32_t sjt_functionParam148;
    int32_t sjt_functionParam149;
    int32_t sjt_functionParam150;
    int32_t sjt_functionParam151;
    int32_t sjt_functionParam152;
    int32_t sjt_functionParam153;
    sjs_vertex_location_texture_normal* sjt_functionParam154;
    int32_t sjt_functionParam155;
    sjs_vertex_location_texture_normal* sjt_functionParam156;
    int32_t sjt_functionParam157;
    sjs_vertex_location_texture_normal* sjt_functionParam158;
    int32_t sjt_functionParam159;
    sjs_vertex_location_texture_normal* sjt_functionParam160;
    float sjt_negate3;
    float sjt_negate4;
    float sjt_negate5;
    float sjt_negate6;
    sjs_array_i32* sjt_parent57;
    sjs_array_i32* sjt_parent58;
    sjs_array_i32* sjt_parent59;
    sjs_array_i32* sjt_parent60;
    sjs_array_i32* sjt_parent61;
    sjs_array_i32* sjt_parent62;
    sjs_array_vertex_location_texture_normal* sjt_parent63;
    sjs_array_vertex_location_texture_normal* sjt_parent64;
    sjs_array_vertex_location_texture_normal* sjt_parent65;
    sjs_array_vertex_location_texture_normal* sjt_parent66;

#line 77 "lib/ui/vertexBufferBuilders.sj"
    sjt_copy9 = &sjv_vertex_location_texture_normal_format;
#line 77
    sjf_string_copy(&_return->format, sjt_copy9);
#line 78
    _return->indices.dataSize = 6;
#line 3 "lib/common/array.sj"
    _return->indices.data = 0;
#line 4
    _return->indices._isGlobal = false;
#line 5
    _return->indices.count = 0;
#line 5
    sjf_array_i32(&_return->indices);
#line 78 "lib/ui/vertexBufferBuilders.sj"
    sjs_array_i32* array1;
#line 78
    array1 = &_return->indices;
#line 78
    sjt_parent57 = array1;
#line 78
    sjt_functionParam141 = 0;
#line 79
    sjt_functionParam142 = 0;
#line 79
    sjf_array_i32_initAt(sjt_parent57, sjt_functionParam141, sjt_functionParam142);
#line 78
    sjt_parent58 = array1;
#line 78
    sjt_functionParam143 = 1;
#line 79
    sjt_functionParam144 = 1;
#line 79
    sjf_array_i32_initAt(sjt_parent58, sjt_functionParam143, sjt_functionParam144);
#line 78
    sjt_parent59 = array1;
#line 78
    sjt_functionParam145 = 2;
#line 79
    sjt_functionParam146 = 2;
#line 79
    sjf_array_i32_initAt(sjt_parent59, sjt_functionParam145, sjt_functionParam146);
#line 78
    sjt_parent60 = array1;
#line 78
    sjt_functionParam147 = 3;
#line 80
    sjt_functionParam148 = 0;
#line 80
    sjf_array_i32_initAt(sjt_parent60, sjt_functionParam147, sjt_functionParam148);
#line 78
    sjt_parent61 = array1;
#line 78
    sjt_functionParam149 = 4;
#line 80
    sjt_functionParam150 = 2;
#line 80
    sjf_array_i32_initAt(sjt_parent61, sjt_functionParam149, sjt_functionParam150);
#line 78
    sjt_parent62 = array1;
#line 78
    sjt_functionParam151 = 5;
#line 80
    sjt_functionParam152 = 3;
#line 80
    sjf_array_i32_initAt(sjt_parent62, sjt_functionParam151, sjt_functionParam152);
#line 82
    _return->vertices.dataSize = 4;
#line 3 "lib/common/array.sj"
    _return->vertices.data = 0;
#line 4
    _return->vertices._isGlobal = false;
#line 5
    _return->vertices.count = 0;
#line 5
    sjf_array_vertex_location_texture_normal(&_return->vertices);
#line 82 "lib/ui/vertexBufferBuilders.sj"
    sjs_array_vertex_location_texture_normal* array2;
#line 82
    array2 = &_return->vertices;
#line 82
    sjt_parent63 = array2;
#line 82
    sjt_functionParam153 = 0;
#line 65
    sjt_call19.location.x = x0;
#line 65
    sjt_call19.location.y = y0;
#line 65
    sjt_call19.location.z = z0;
#line 65
    sjf_vec3(&sjt_call19.location);
#line 65
    sjt_call19.texture.x = s0;
#line 65
    sjt_call19.texture.y = t0;
#line 65
    sjf_vec2(&sjt_call19.texture);
#line 83
    sjt_call19.normal.x = 0.0f;
#line 83
    sjt_call19.normal.y = 0.0f;
#line 83
    sjt_negate3 = 1.0f;
#line 83
    result4 = -sjt_negate3;
#line 83
    sjt_call19.normal.z = result4;
#line 83
    sjf_vec3(&sjt_call19.normal);
#line 83
    sjf_vertex_location_texture_normal(&sjt_call19);
#line 83
    sjt_functionParam154 = &sjt_call19;
#line 83
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent63, sjt_functionParam153, sjt_functionParam154);
#line 82
    sjt_parent64 = array2;
#line 82
    sjt_functionParam155 = 1;
#line 65
    sjt_call20.location.x = x0;
#line 65
    sjt_call20.location.y = y1;
#line 65
    sjt_call20.location.z = z0;
#line 65
    sjf_vec3(&sjt_call20.location);
#line 65
    sjt_call20.texture.x = s0;
#line 65
    sjt_call20.texture.y = t1;
#line 65
    sjf_vec2(&sjt_call20.texture);
#line 84
    sjt_call20.normal.x = 0.0f;
#line 84
    sjt_call20.normal.y = 0.0f;
#line 84
    sjt_negate4 = 1.0f;
#line 84
    result5 = -sjt_negate4;
#line 84
    sjt_call20.normal.z = result5;
#line 84
    sjf_vec3(&sjt_call20.normal);
#line 84
    sjf_vertex_location_texture_normal(&sjt_call20);
#line 84
    sjt_functionParam156 = &sjt_call20;
#line 84
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent64, sjt_functionParam155, sjt_functionParam156);
#line 82
    sjt_parent65 = array2;
#line 82
    sjt_functionParam157 = 2;
#line 65
    sjt_call21.location.x = x1;
#line 65
    sjt_call21.location.y = y1;
#line 65
    sjt_call21.location.z = z0;
#line 65
    sjf_vec3(&sjt_call21.location);
#line 65
    sjt_call21.texture.x = s1;
#line 65
    sjt_call21.texture.y = t1;
#line 65
    sjf_vec2(&sjt_call21.texture);
#line 85
    sjt_call21.normal.x = 0.0f;
#line 85
    sjt_call21.normal.y = 0.0f;
#line 85
    sjt_negate5 = 1.0f;
#line 85
    result6 = -sjt_negate5;
#line 85
    sjt_call21.normal.z = result6;
#line 85
    sjf_vec3(&sjt_call21.normal);
#line 85
    sjf_vertex_location_texture_normal(&sjt_call21);
#line 85
    sjt_functionParam158 = &sjt_call21;
#line 85
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent65, sjt_functionParam157, sjt_functionParam158);
#line 82
    sjt_parent66 = array2;
#line 82
    sjt_functionParam159 = 3;
#line 65
    sjt_call22.location.x = x1;
#line 65
    sjt_call22.location.y = y0;
#line 65
    sjt_call22.location.z = z0;
#line 65
    sjf_vec3(&sjt_call22.location);
#line 65
    sjt_call22.texture.x = s1;
#line 65
    sjt_call22.texture.y = t0;
#line 65
    sjf_vec2(&sjt_call22.texture);
#line 86
    sjt_call22.normal.x = 0.0f;
#line 86
    sjt_call22.normal.y = 0.0f;
#line 86
    sjt_negate6 = 1.0f;
#line 86
    result7 = -sjt_negate6;
#line 86
    sjt_call22.normal.z = result7;
#line 86
    sjf_vec3(&sjt_call22.normal);
#line 86
    sjf_vertex_location_texture_normal(&sjt_call22);
#line 86
    sjt_functionParam160 = &sjt_call22;
#line 86
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent66, sjt_functionParam159, sjt_functionParam160);
#line 86
    sjf_vertexBuffer_vertex_location_texture_normal(_return);

    sjf_vertex_location_texture_normal_destroy(&sjt_call19);
    sjf_vertex_location_texture_normal_destroy(&sjt_call20);
    sjf_vertex_location_texture_normal_destroy(&sjt_call21);
    sjf_vertex_location_texture_normal_destroy(&sjt_call22);
}

void sjf_planeVertexBuffer_heap(float x0, float x1, float y0, float y1, float z0, float s0, float s1, float t0, float t1, sjs_vertexBuffer_vertex_location_texture_normal_heap** _return) {
    float result10;
    float result11;
    float result8;
    float result9;
    sjs_vertex_location_texture_normal sjt_call23;
    sjs_vertex_location_texture_normal sjt_call24;
    sjs_vertex_location_texture_normal sjt_call25;
    sjs_vertex_location_texture_normal sjt_call26;
    sjs_string* sjt_copy10;
    int32_t sjt_functionParam161;
    int32_t sjt_functionParam162;
    int32_t sjt_functionParam163;
    int32_t sjt_functionParam164;
    int32_t sjt_functionParam165;
    int32_t sjt_functionParam166;
    int32_t sjt_functionParam167;
    int32_t sjt_functionParam168;
    int32_t sjt_functionParam169;
    int32_t sjt_functionParam170;
    int32_t sjt_functionParam171;
    int32_t sjt_functionParam172;
    int32_t sjt_functionParam173;
    sjs_vertex_location_texture_normal* sjt_functionParam174;
    int32_t sjt_functionParam175;
    sjs_vertex_location_texture_normal* sjt_functionParam176;
    int32_t sjt_functionParam177;
    sjs_vertex_location_texture_normal* sjt_functionParam178;
    int32_t sjt_functionParam179;
    sjs_vertex_location_texture_normal* sjt_functionParam180;
    float sjt_negate10;
    float sjt_negate7;
    float sjt_negate8;
    float sjt_negate9;
    sjs_array_i32* sjt_parent67;
    sjs_array_i32* sjt_parent68;
    sjs_array_i32* sjt_parent69;
    sjs_array_i32* sjt_parent70;
    sjs_array_i32* sjt_parent71;
    sjs_array_i32* sjt_parent72;
    sjs_array_vertex_location_texture_normal* sjt_parent73;
    sjs_array_vertex_location_texture_normal* sjt_parent74;
    sjs_array_vertex_location_texture_normal* sjt_parent75;
    sjs_array_vertex_location_texture_normal* sjt_parent76;

    (*_return) = (sjs_vertexBuffer_vertex_location_texture_normal_heap*)malloc(sizeof(sjs_vertexBuffer_vertex_location_texture_normal_heap));
    (*_return)->_refCount = 1;
#line 77 "lib/ui/vertexBufferBuilders.sj"
    sjt_copy10 = &sjv_vertex_location_texture_normal_format;
#line 77
    sjf_string_copy(&(*_return)->format, sjt_copy10);
#line 78
    (*_return)->indices.dataSize = 6;
#line 3 "lib/common/array.sj"
    (*_return)->indices.data = 0;
#line 4
    (*_return)->indices._isGlobal = false;
#line 5
    (*_return)->indices.count = 0;
#line 5
    sjf_array_i32(&(*_return)->indices);
#line 78 "lib/ui/vertexBufferBuilders.sj"
    sjs_array_i32* array3;
#line 78
    array3 = &(*_return)->indices;
#line 78
    sjt_parent67 = array3;
#line 78
    sjt_functionParam161 = 0;
#line 79
    sjt_functionParam162 = 0;
#line 79
    sjf_array_i32_initAt(sjt_parent67, sjt_functionParam161, sjt_functionParam162);
#line 78
    sjt_parent68 = array3;
#line 78
    sjt_functionParam163 = 1;
#line 79
    sjt_functionParam164 = 1;
#line 79
    sjf_array_i32_initAt(sjt_parent68, sjt_functionParam163, sjt_functionParam164);
#line 78
    sjt_parent69 = array3;
#line 78
    sjt_functionParam165 = 2;
#line 79
    sjt_functionParam166 = 2;
#line 79
    sjf_array_i32_initAt(sjt_parent69, sjt_functionParam165, sjt_functionParam166);
#line 78
    sjt_parent70 = array3;
#line 78
    sjt_functionParam167 = 3;
#line 80
    sjt_functionParam168 = 0;
#line 80
    sjf_array_i32_initAt(sjt_parent70, sjt_functionParam167, sjt_functionParam168);
#line 78
    sjt_parent71 = array3;
#line 78
    sjt_functionParam169 = 4;
#line 80
    sjt_functionParam170 = 2;
#line 80
    sjf_array_i32_initAt(sjt_parent71, sjt_functionParam169, sjt_functionParam170);
#line 78
    sjt_parent72 = array3;
#line 78
    sjt_functionParam171 = 5;
#line 80
    sjt_functionParam172 = 3;
#line 80
    sjf_array_i32_initAt(sjt_parent72, sjt_functionParam171, sjt_functionParam172);
#line 82
    (*_return)->vertices.dataSize = 4;
#line 3 "lib/common/array.sj"
    (*_return)->vertices.data = 0;
#line 4
    (*_return)->vertices._isGlobal = false;
#line 5
    (*_return)->vertices.count = 0;
#line 5
    sjf_array_vertex_location_texture_normal(&(*_return)->vertices);
#line 82 "lib/ui/vertexBufferBuilders.sj"
    sjs_array_vertex_location_texture_normal* array4;
#line 82
    array4 = &(*_return)->vertices;
#line 82
    sjt_parent73 = array4;
#line 82
    sjt_functionParam173 = 0;
#line 65
    sjt_call23.location.x = x0;
#line 65
    sjt_call23.location.y = y0;
#line 65
    sjt_call23.location.z = z0;
#line 65
    sjf_vec3(&sjt_call23.location);
#line 65
    sjt_call23.texture.x = s0;
#line 65
    sjt_call23.texture.y = t0;
#line 65
    sjf_vec2(&sjt_call23.texture);
#line 83
    sjt_call23.normal.x = 0.0f;
#line 83
    sjt_call23.normal.y = 0.0f;
#line 83
    sjt_negate7 = 1.0f;
#line 83
    result8 = -sjt_negate7;
#line 83
    sjt_call23.normal.z = result8;
#line 83
    sjf_vec3(&sjt_call23.normal);
#line 83
    sjf_vertex_location_texture_normal(&sjt_call23);
#line 83
    sjt_functionParam174 = &sjt_call23;
#line 83
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent73, sjt_functionParam173, sjt_functionParam174);
#line 82
    sjt_parent74 = array4;
#line 82
    sjt_functionParam175 = 1;
#line 65
    sjt_call24.location.x = x0;
#line 65
    sjt_call24.location.y = y1;
#line 65
    sjt_call24.location.z = z0;
#line 65
    sjf_vec3(&sjt_call24.location);
#line 65
    sjt_call24.texture.x = s0;
#line 65
    sjt_call24.texture.y = t1;
#line 65
    sjf_vec2(&sjt_call24.texture);
#line 84
    sjt_call24.normal.x = 0.0f;
#line 84
    sjt_call24.normal.y = 0.0f;
#line 84
    sjt_negate8 = 1.0f;
#line 84
    result9 = -sjt_negate8;
#line 84
    sjt_call24.normal.z = result9;
#line 84
    sjf_vec3(&sjt_call24.normal);
#line 84
    sjf_vertex_location_texture_normal(&sjt_call24);
#line 84
    sjt_functionParam176 = &sjt_call24;
#line 84
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent74, sjt_functionParam175, sjt_functionParam176);
#line 82
    sjt_parent75 = array4;
#line 82
    sjt_functionParam177 = 2;
#line 65
    sjt_call25.location.x = x1;
#line 65
    sjt_call25.location.y = y1;
#line 65
    sjt_call25.location.z = z0;
#line 65
    sjf_vec3(&sjt_call25.location);
#line 65
    sjt_call25.texture.x = s1;
#line 65
    sjt_call25.texture.y = t1;
#line 65
    sjf_vec2(&sjt_call25.texture);
#line 85
    sjt_call25.normal.x = 0.0f;
#line 85
    sjt_call25.normal.y = 0.0f;
#line 85
    sjt_negate9 = 1.0f;
#line 85
    result10 = -sjt_negate9;
#line 85
    sjt_call25.normal.z = result10;
#line 85
    sjf_vec3(&sjt_call25.normal);
#line 85
    sjf_vertex_location_texture_normal(&sjt_call25);
#line 85
    sjt_functionParam178 = &sjt_call25;
#line 85
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent75, sjt_functionParam177, sjt_functionParam178);
#line 82
    sjt_parent76 = array4;
#line 82
    sjt_functionParam179 = 3;
#line 65
    sjt_call26.location.x = x1;
#line 65
    sjt_call26.location.y = y0;
#line 65
    sjt_call26.location.z = z0;
#line 65
    sjf_vec3(&sjt_call26.location);
#line 65
    sjt_call26.texture.x = s1;
#line 65
    sjt_call26.texture.y = t0;
#line 65
    sjf_vec2(&sjt_call26.texture);
#line 86
    sjt_call26.normal.x = 0.0f;
#line 86
    sjt_call26.normal.y = 0.0f;
#line 86
    sjt_negate10 = 1.0f;
#line 86
    result11 = -sjt_negate10;
#line 86
    sjt_call26.normal.z = result11;
#line 86
    sjf_vec3(&sjt_call26.normal);
#line 86
    sjf_vertex_location_texture_normal(&sjt_call26);
#line 86
    sjt_functionParam180 = &sjt_call26;
#line 86
    sjf_array_vertex_location_texture_normal_initAt(sjt_parent76, sjt_functionParam179, sjt_functionParam180);
#line 86
    sjf_vertexBuffer_vertex_location_texture_normal_heap((*_return));

    sjf_vertex_location_texture_normal_destroy(&sjt_call23);
    sjf_vertex_location_texture_normal_destroy(&sjt_call24);
    sjf_vertex_location_texture_normal_destroy(&sjt_call25);
    sjf_vertex_location_texture_normal_destroy(&sjt_call26);
}

void sjf_point(sjs_point* _this) {
}

void sjf_point_copy(sjs_point* _this, sjs_point* _from) {
#line 1 "lib/ui/point.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
}

void sjf_point_destroy(sjs_point* _this) {
}

void sjf_point_heap(sjs_point_heap* _this) {
}

void sjf_rect(sjs_rect* _this) {
}

void sjf_rect_containsPoint(sjs_rect* _parent, sjs_point* point, bool* _return) {
    bool sjt_and10;
    bool sjt_and11;
    bool sjt_and12;
    bool sjt_and13;
    bool sjt_and14;
    bool sjt_and9;
    int32_t sjt_compare51;
    int32_t sjt_compare52;
    int32_t sjt_compare53;
    int32_t sjt_compare54;
    int32_t sjt_compare55;
    int32_t sjt_compare56;
    int32_t sjt_compare57;
    int32_t sjt_compare58;
    sjs_rect* sjt_dot1395;
    sjs_point* sjt_dot1396;
    sjs_rect* sjt_dot1397;
    sjs_point* sjt_dot1398;
    sjs_point* sjt_dot1399;
    sjs_rect* sjt_dot1400;
    sjs_rect* sjt_dot1401;
    sjs_point* sjt_dot1402;
    sjs_rect* sjt_dot1403;
    sjs_rect* sjt_dot1404;
    int32_t sjt_math2149;
    int32_t sjt_math2150;
    int32_t sjt_math2151;
    int32_t sjt_math2152;

#line 11 "lib/ui/rect.sj"
    sjt_dot1395 = _parent;
#line 12
    sjt_compare51 = (sjt_dot1395)->x;
#line 11
    sjt_dot1396 = point;
#line 12
    sjt_compare52 = (sjt_dot1396)->x;
#line 12
    sjt_and9 = sjt_compare51 <= sjt_compare52;
#line 11
    sjt_dot1397 = _parent;
#line 12
    sjt_compare53 = (sjt_dot1397)->y;
#line 11
    sjt_dot1398 = point;
#line 12
    sjt_compare54 = (sjt_dot1398)->x;
#line 12
    sjt_and11 = sjt_compare53 <= sjt_compare54;
#line 11
    sjt_dot1399 = point;
#line 12
    sjt_compare55 = (sjt_dot1399)->x;
#line 11
    sjt_dot1400 = _parent;
#line 12
    sjt_math2149 = (sjt_dot1400)->x;
#line 11
    sjt_dot1401 = _parent;
#line 12
    sjt_math2150 = (sjt_dot1401)->w;
#line 12
    sjt_compare56 = sjt_math2149 + sjt_math2150;
#line 12
    sjt_and13 = sjt_compare55 < sjt_compare56;
#line 11
    sjt_dot1402 = point;
#line 12
    sjt_compare57 = (sjt_dot1402)->y;
#line 11
    sjt_dot1403 = _parent;
#line 12
    sjt_math2151 = (sjt_dot1403)->y;
#line 11
    sjt_dot1404 = _parent;
#line 12
    sjt_math2152 = (sjt_dot1404)->h;
#line 12
    sjt_compare58 = sjt_math2151 + sjt_math2152;
#line 12
    sjt_and14 = sjt_compare57 < sjt_compare58;
#line 12
    sjt_and12 = sjt_and13 && sjt_and14;
#line 12
    sjt_and10 = sjt_and11 && sjt_and12;
#line 12
    (*_return) = sjt_and9 && sjt_and10;
}

void sjf_rect_copy(sjs_rect* _this, sjs_rect* _from) {
#line 1 "lib/ui/rect.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
#line 1
    _this->w = _from->w;
#line 1
    _this->h = _from->h;
}

void sjf_rect_destroy(sjs_rect* _this) {
}

void sjf_rect_heap(sjs_rect_heap* _this) {
}

void sjf_rect_isEqual(sjs_rect* _parent, sjs_rect* rect, bool* _return) {
    bool sjt_and1;
    bool sjt_and2;
    bool sjt_and3;
    bool sjt_and4;
    bool sjt_and5;
    bool sjt_and6;
    int32_t sjt_compare1;
    int32_t sjt_compare2;
    int32_t sjt_compare3;
    int32_t sjt_compare4;
    int32_t sjt_compare5;
    int32_t sjt_compare6;
    int32_t sjt_compare7;
    int32_t sjt_compare8;
    sjs_rect* sjt_dot22;
    sjs_rect* sjt_dot23;
    sjs_rect* sjt_dot24;
    sjs_rect* sjt_dot25;
    sjs_rect* sjt_dot26;
    sjs_rect* sjt_dot27;
    sjs_rect* sjt_dot28;
    sjs_rect* sjt_dot29;

#line 15 "lib/ui/rect.sj"
    sjt_dot22 = _parent;
#line 16
    sjt_compare1 = (sjt_dot22)->x;
#line 15
    sjt_dot23 = rect;
#line 16
    sjt_compare2 = (sjt_dot23)->x;
#line 16
    sjt_and1 = sjt_compare1 == sjt_compare2;
#line 15
    sjt_dot24 = _parent;
#line 16
    sjt_compare3 = (sjt_dot24)->y;
#line 15
    sjt_dot25 = rect;
#line 16
    sjt_compare4 = (sjt_dot25)->y;
#line 16
    sjt_and3 = sjt_compare3 == sjt_compare4;
#line 15
    sjt_dot26 = _parent;
#line 16
    sjt_compare5 = (sjt_dot26)->w;
#line 15
    sjt_dot27 = rect;
#line 16
    sjt_compare6 = (sjt_dot27)->w;
#line 16
    sjt_and5 = sjt_compare5 == sjt_compare6;
#line 15
    sjt_dot28 = _parent;
#line 16
    sjt_compare7 = (sjt_dot28)->h;
#line 15
    sjt_dot29 = rect;
#line 16
    sjt_compare8 = (sjt_dot29)->h;
#line 16
    sjt_and6 = sjt_compare7 == sjt_compare8;
#line 16
    sjt_and4 = sjt_and5 && sjt_and6;
#line 16
    sjt_and2 = sjt_and3 && sjt_and4;
#line 16
    (*_return) = sjt_and1 && sjt_and2;
}

void sjf_runLoop(void) {
#line 59 "lib/ui/loop.sj"
    #ifdef EMSCRIPTEN
#line 59
    emscripten_set_main_loop((em_callback_func)sjf_mainLoop, 0, 0);
#line 59
    exit(0);
#line 59
    #else
#line 59
    bool quit = false;
#line 59
    while (!quit) {
#line 59
        sjf_mainLoop();
#line 59
    }
#line 59
    #endif	
}

void sjf_scene2d(sjs_scene2d* _this) {
}

void sjf_scene2d_clear(sjs_scene2d* _parent) {
#line 8 "lib/ui/scene2d.sj"
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
#line 8
    glEnable( GL_TEXTURE_2D );
#line 8
    glDisable( GL_DEPTH_TEST );
#line 8
    sjf_scene2d_updateViewport(_parent);
}

void sjf_scene2d_copy(sjs_scene2d* _this, sjs_scene2d* _from) {
#line 1 "lib/ui/scene2d.sj"
    sjf_size_copy(&_this->_size, &_from->_size);
#line 1
    sjf_mat4_copy(&_this->model, &_from->model);
#line 1
    sjf_mat4_copy(&_this->view, &_from->view);
#line 1
    sjf_mat4_copy(&_this->projection, &_from->projection);
}

void sjf_scene2d_destroy(sjs_scene2d* _this) {
}

void sjf_scene2d_heap(sjs_scene2d_heap* _this) {
}

void sjf_scene2d_setSize(sjs_scene2d* _parent, sjs_size* size) {
    bool result50;
    sjs_scene2d* sjt_dot1422;
    sjs_size* sjt_functionParam479;
    bool sjt_ifElse27;
    bool sjt_not5;
    sjs_size* sjt_parent152;

#line 27 "lib/ui/scene2d.sj"
    sjt_dot1422 = _parent;
#line 16 "lib/ui/size.sj"
    sjt_parent152 = &(sjt_dot1422)->_size;
#line 27 "lib/ui/scene2d.sj"
    sjt_functionParam479 = size;
#line 27
    sjf_size_isEqual(sjt_parent152, sjt_functionParam479, &sjt_not5);
#line 28
    result50 = !sjt_not5;
#line 28
    sjt_ifElse27 = result50;
    if (sjt_ifElse27) {
        float result53;
        float result54;
        int32_t sjt_cast29;
        int32_t sjt_cast30;
        sjs_size* sjt_copy32;
        sjs_scene2d* sjt_dot1423;
        sjs_scene2d* sjt_dot1424;
        sjs_size* sjt_dot1425;
        sjs_scene2d* sjt_dot1426;
        sjs_size* sjt_dot1427;
        sjs_scene2d* sjt_dot1428;
        sjs_scene2d* sjt_dot1429;
        sjs_scene2d* sjt_dot1430;
        float sjt_functionParam480;
        float sjt_functionParam481;
        float sjt_functionParam482;
        float sjt_functionParam483;
        float sjt_functionParam484;
        float sjt_functionParam485;
        float sjt_functionParam486;
        float sjt_functionParam487;
        float sjt_functionParam488;
        int32_t sjt_math2229;
        int32_t sjt_math2230;
        float sjt_negate48;
        float sjt_negate49;

#line 27 "lib/ui/scene2d.sj"
        sjt_dot1423 = _parent;
#line 27
        sjt_copy32 = size;
#line 29
        sjf_size_copy(&sjt_dot1423->_size, sjt_copy32);
#line 27
        sjt_dot1424 = _parent;
#line 30
        sjt_functionParam480 = 0.0f;
#line 27
        sjt_dot1426 = _parent;
#line 1 "lib/ui/size.sj"
        sjt_dot1425 = &(sjt_dot1426)->_size;
#line 30 "lib/ui/scene2d.sj"
        sjt_cast29 = (sjt_dot1425)->w;
#line 30
        sjt_functionParam481 = (float)sjt_cast29;
#line 30
        sjt_math2229 = 0;
#line 27
        sjt_dot1428 = _parent;
#line 1 "lib/ui/size.sj"
        sjt_dot1427 = &(sjt_dot1428)->_size;
#line 30 "lib/ui/scene2d.sj"
        sjt_math2230 = (sjt_dot1427)->h;
#line 30
        sjt_cast30 = sjt_math2229 - sjt_math2230;
#line 30
        sjt_functionParam482 = (float)sjt_cast30;
#line 30
        sjt_functionParam483 = 0.0f;
#line 30
        sjt_negate48 = 1.0f;
#line 30
        result53 = -sjt_negate48;
#line 30
        sjt_functionParam484 = result53;
#line 30
        sjt_functionParam485 = 1.0f;
#line 30
        sjf_mat4_orthographic(sjt_functionParam480, sjt_functionParam481, sjt_functionParam482, sjt_functionParam483, sjt_functionParam484, sjt_functionParam485, &sjt_dot1424->projection);
#line 27
        sjt_dot1429 = _parent;
#line 31
        sjt_functionParam486 = 1.0f;
#line 31
        sjt_negate49 = 1.0f;
#line 31
        result54 = -sjt_negate49;
#line 31
        sjt_functionParam487 = result54;
#line 31
        sjt_functionParam488 = 1.0f;
#line 31
        sjf_mat4_scale(sjt_functionParam486, sjt_functionParam487, sjt_functionParam488, &sjt_dot1429->model);
#line 27
        sjt_dot1430 = _parent;
#line 27
        sjf_mat4_identity(&sjt_dot1430->view);
    }
}

void sjf_scene2d_updateViewport(sjs_scene2d* _parent) {
#line 18 "lib/ui/scene2d.sj"
    glViewport(0, 0, _parent->_size.w, _parent->_size.h);
}

void sjf_shader(sjs_shader* _this) {
#line 16 "lib/ui/shader.sj"
    _this->id = shader_load((char*)_this->vertex.data.data, (char*)_this->pixel.data.data);
}

void sjf_shader_copy(sjs_shader* _this, sjs_shader* _from) {
#line 9 "lib/ui/shader.sj"
    sjf_string_copy(&_this->vertex, &_from->vertex);
#line 9
    sjf_string_copy(&_this->pixel, &_from->pixel);
#line 21
    _this->id = _from->id;
#line 21
    _retainGLid(_this->id);
}

void sjf_shader_destroy(sjs_shader* _this) {
#line 26 "lib/ui/shader.sj"
    if (_releaseGLid(_this->id)) {
#line 26
        glDeleteShader(_this->id);
#line 26
    }
}

void sjf_shader_heap(sjs_shader_heap* _this) {
#line 16 "lib/ui/shader.sj"
    _this->id = shader_load((char*)_this->vertex.data.data, (char*)_this->pixel.data.data);
}

void sjf_size(sjs_size* _this) {
}

void sjf_size_copy(sjs_size* _this, sjs_size* _from) {
#line 1 "lib/ui/size.sj"
    _this->w = _from->w;
#line 1
    _this->h = _from->h;
}

void sjf_size_destroy(sjs_size* _this) {
}

void sjf_size_heap(sjs_size_heap* _this) {
}

void sjf_size_isEqual(sjs_size* _parent, sjs_size* size, bool* _return) {
    bool sjt_and15;
    bool sjt_and16;
    int32_t sjt_compare63;
    int32_t sjt_compare64;
    int32_t sjt_compare65;
    int32_t sjt_compare66;
    sjs_size* sjt_dot1418;
    sjs_size* sjt_dot1419;
    sjs_size* sjt_dot1420;
    sjs_size* sjt_dot1421;

#line 16 "lib/ui/size.sj"
    sjt_dot1418 = _parent;
#line 17
    sjt_compare63 = (sjt_dot1418)->w;
#line 16
    sjt_dot1419 = size;
#line 17
    sjt_compare64 = (sjt_dot1419)->w;
#line 17
    sjt_and15 = sjt_compare63 == sjt_compare64;
#line 16
    sjt_dot1420 = _parent;
#line 17
    sjt_compare65 = (sjt_dot1420)->h;
#line 16
    sjt_dot1421 = size;
#line 17
    sjt_compare66 = (sjt_dot1421)->h;
#line 17
    sjt_and16 = sjt_compare65 == sjt_compare66;
#line 17
    (*_return) = sjt_and15 && sjt_and16;
}

void sjf_string(sjs_string* _this) {
}

void sjf_string_add(sjs_string* _parent, sjs_string* item, sjs_string* _return) {
    int32_t sjt_compare47;
    int32_t sjt_compare48;
    sjs_string* sjt_dot1325;
    bool sjt_ifElse16;

#line 15 "lib/common/string.sj"
    sjt_dot1325 = item;
#line 16
    sjt_compare47 = (sjt_dot1325)->count;
#line 16
    sjt_compare48 = 0;
#line 16
    sjt_ifElse16 = sjt_compare47 == sjt_compare48;
    if (sjt_ifElse16) {
        sjs_array_char* sjt_copy14;
        sjs_string* sjt_dot1326;
        sjs_string* sjt_dot1327;

#line 15 "lib/common/string.sj"
        sjt_dot1326 = _parent;
#line 17
        _return->count = (sjt_dot1326)->count;
#line 15
        sjt_dot1327 = _parent;
#line 17
        sjt_copy14 = &(sjt_dot1327)->data;
#line 17
        sjf_array_char_copy(&_return->data, sjt_copy14);
#line 17
        sjf_string(_return);
    } else {
        int32_t i;
        int32_t sjt_cast14;
        sjs_array_char* sjt_copy15;
        sjs_string* sjt_dot1330;
        sjs_string* sjt_dot1331;
        sjs_string* sjt_dot1332;
        sjs_string* sjt_dot1333;
        sjs_string* sjt_dot1335;
        int32_t sjt_forEnd10;
        int32_t sjt_forStart10;
        int32_t sjt_functionParam218;
        int32_t sjt_functionParam219;
        char sjt_functionParam220;
        int32_t sjt_functionParam222;
        int32_t sjt_functionParam226;
        char sjt_functionParam227;
        int32_t sjt_math2121;
        int32_t sjt_math2122;
        int32_t sjt_math2123;
        int32_t sjt_math2124;
        int32_t sjt_math2125;
        int32_t sjt_math2126;
        sjs_array_char* sjt_parent80;
        sjs_array_char* sjt_parent81;
        sjs_string* sjt_parent83;
        sjs_array_char* sjt_parent86;
        int32_t sjv_newCount;
        sjs_array_char sjv_newData;

#line 15 "lib/common/string.sj"
        sjt_dot1330 = _parent;
#line 115 "lib/common/array.sj"
        sjt_parent80 = &(sjt_dot1330)->data;
#line 15 "lib/common/string.sj"
        sjt_dot1331 = _parent;
#line 19
        sjt_math2123 = (sjt_dot1331)->count;
#line 15
        sjt_dot1332 = item;
#line 19
        sjt_math2124 = (sjt_dot1332)->count;
#line 19
        sjt_math2121 = sjt_math2123 + sjt_math2124;
#line 19
        sjt_math2122 = 1;
#line 19
        sjt_functionParam218 = sjt_math2121 + sjt_math2122;
#line 19
        sjf_array_char_grow(sjt_parent80, sjt_functionParam218, &sjv_newData);
#line 15
        sjt_dot1333 = _parent;
#line 20
        sjv_newCount = (sjt_dot1333)->count;
#line 34 "lib/common/array.sj"
        sjt_parent81 = &sjv_newData;
#line 21 "lib/common/string.sj"
        sjt_functionParam219 = sjv_newCount;
#line 15
        sjt_parent83 = item;
#line 21
        sjt_functionParam222 = 0;
#line 21
        sjf_string_getAt(sjt_parent83, sjt_functionParam222, &sjt_functionParam220);
#line 21
        sjf_array_char_setAt(sjt_parent81, sjt_functionParam219, sjt_functionParam220);
#line 22
        sjt_math2125 = sjv_newCount;
#line 22
        sjt_math2126 = 1;
#line 22
        sjv_newCount = sjt_math2125 + sjt_math2126;
#line 24
        sjt_forStart10 = 1;
#line 15
        sjt_dot1335 = item;
#line 24
        sjt_forEnd10 = (sjt_dot1335)->count;
#line 24
        i = sjt_forStart10;
        while (i < sjt_forEnd10) {
            int32_t sjt_functionParam223;
            char sjt_functionParam224;
            int32_t sjt_functionParam225;
            int32_t sjt_math2127;
            int32_t sjt_math2128;
            sjs_array_char* sjt_parent84;
            sjs_string* sjt_parent85;

#line 19 "lib/common/array.sj"
            sjt_parent84 = &sjv_newData;
#line 25 "lib/common/string.sj"
            sjt_functionParam223 = sjv_newCount;
#line 15
            sjt_parent85 = item;
#line 24
            sjt_functionParam225 = i;
#line 24
            sjf_string_getAt(sjt_parent85, sjt_functionParam225, &sjt_functionParam224);
#line 24
            sjf_array_char_initAt(sjt_parent84, sjt_functionParam223, sjt_functionParam224);
#line 26
            sjt_math2127 = sjv_newCount;
#line 26
            sjt_math2128 = 1;
#line 26
            sjv_newCount = sjt_math2127 + sjt_math2128;
#line 24
            i++;
        }

#line 19 "lib/common/array.sj"
        sjt_parent86 = &sjv_newData;
#line 29 "lib/common/string.sj"
        sjt_functionParam226 = sjv_newCount;
#line 29
        sjt_cast14 = 0;
#line 29
        sjt_functionParam227 = (char)sjt_cast14;
#line 29
        sjf_array_char_initAt(sjt_parent86, sjt_functionParam226, sjt_functionParam227);
#line 30
        _return->count = sjv_newCount;
#line 30
        sjt_copy15 = &sjv_newData;
#line 30
        sjf_array_char_copy(&_return->data, sjt_copy15);
#line 30
        sjf_string(_return);

        sjf_array_char_destroy(&sjv_newData);
    }
}

void sjf_string_add_heap(sjs_string* _parent, sjs_string* item, sjs_string_heap** _return) {
    int32_t sjt_compare49;
    int32_t sjt_compare50;
    sjs_string* sjt_dot1336;
    bool sjt_ifElse17;

#line 15 "lib/common/string.sj"
    sjt_dot1336 = item;
#line 16
    sjt_compare49 = (sjt_dot1336)->count;
#line 16
    sjt_compare50 = 0;
#line 16
    sjt_ifElse17 = sjt_compare49 == sjt_compare50;
    if (sjt_ifElse17) {
        sjs_array_char* sjt_copy16;
        sjs_string* sjt_dot1337;
        sjs_string* sjt_dot1338;

        (*_return) = (sjs_string_heap*)malloc(sizeof(sjs_string_heap));
        (*_return)->_refCount = 1;
#line 15 "lib/common/string.sj"
        sjt_dot1337 = _parent;
#line 17
        (*_return)->count = (sjt_dot1337)->count;
#line 15
        sjt_dot1338 = _parent;
#line 17
        sjt_copy16 = &(sjt_dot1338)->data;
#line 17
        sjf_array_char_copy(&(*_return)->data, sjt_copy16);
#line 17
        sjf_string_heap((*_return));
    } else {
        int32_t i;
        int32_t sjt_cast15;
        sjs_array_char* sjt_copy17;
        sjs_string* sjt_dot1339;
        sjs_string* sjt_dot1340;
        sjs_string* sjt_dot1341;
        sjs_string* sjt_dot1342;
        sjs_string* sjt_dot1343;
        int32_t sjt_forEnd11;
        int32_t sjt_forStart11;
        int32_t sjt_functionParam228;
        int32_t sjt_functionParam229;
        char sjt_functionParam230;
        int32_t sjt_functionParam231;
        int32_t sjt_functionParam235;
        char sjt_functionParam236;
        int32_t sjt_math2129;
        int32_t sjt_math2130;
        int32_t sjt_math2131;
        int32_t sjt_math2132;
        int32_t sjt_math2133;
        int32_t sjt_math2134;
        sjs_array_char* sjt_parent87;
        sjs_array_char* sjt_parent88;
        sjs_string* sjt_parent89;
        sjs_array_char* sjt_parent92;
        int32_t sjv_newCount;
        sjs_array_char sjv_newData;

#line 15 "lib/common/string.sj"
        sjt_dot1339 = _parent;
#line 115 "lib/common/array.sj"
        sjt_parent87 = &(sjt_dot1339)->data;
#line 15 "lib/common/string.sj"
        sjt_dot1340 = _parent;
#line 19
        sjt_math2131 = (sjt_dot1340)->count;
#line 15
        sjt_dot1341 = item;
#line 19
        sjt_math2132 = (sjt_dot1341)->count;
#line 19
        sjt_math2129 = sjt_math2131 + sjt_math2132;
#line 19
        sjt_math2130 = 1;
#line 19
        sjt_functionParam228 = sjt_math2129 + sjt_math2130;
#line 19
        sjf_array_char_grow(sjt_parent87, sjt_functionParam228, &sjv_newData);
#line 15
        sjt_dot1342 = _parent;
#line 20
        sjv_newCount = (sjt_dot1342)->count;
#line 34 "lib/common/array.sj"
        sjt_parent88 = &sjv_newData;
#line 21 "lib/common/string.sj"
        sjt_functionParam229 = sjv_newCount;
#line 15
        sjt_parent89 = item;
#line 21
        sjt_functionParam231 = 0;
#line 21
        sjf_string_getAt(sjt_parent89, sjt_functionParam231, &sjt_functionParam230);
#line 21
        sjf_array_char_setAt(sjt_parent88, sjt_functionParam229, sjt_functionParam230);
#line 22
        sjt_math2133 = sjv_newCount;
#line 22
        sjt_math2134 = 1;
#line 22
        sjv_newCount = sjt_math2133 + sjt_math2134;
#line 24
        sjt_forStart11 = 1;
#line 15
        sjt_dot1343 = item;
#line 24
        sjt_forEnd11 = (sjt_dot1343)->count;
#line 24
        i = sjt_forStart11;
        while (i < sjt_forEnd11) {
            int32_t sjt_functionParam232;
            char sjt_functionParam233;
            int32_t sjt_functionParam234;
            int32_t sjt_math2135;
            int32_t sjt_math2136;
            sjs_array_char* sjt_parent90;
            sjs_string* sjt_parent91;

#line 19 "lib/common/array.sj"
            sjt_parent90 = &sjv_newData;
#line 25 "lib/common/string.sj"
            sjt_functionParam232 = sjv_newCount;
#line 15
            sjt_parent91 = item;
#line 24
            sjt_functionParam234 = i;
#line 24
            sjf_string_getAt(sjt_parent91, sjt_functionParam234, &sjt_functionParam233);
#line 24
            sjf_array_char_initAt(sjt_parent90, sjt_functionParam232, sjt_functionParam233);
#line 26
            sjt_math2135 = sjv_newCount;
#line 26
            sjt_math2136 = 1;
#line 26
            sjv_newCount = sjt_math2135 + sjt_math2136;
#line 24
            i++;
        }

#line 19 "lib/common/array.sj"
        sjt_parent92 = &sjv_newData;
#line 29 "lib/common/string.sj"
        sjt_functionParam235 = sjv_newCount;
#line 29
        sjt_cast15 = 0;
#line 29
        sjt_functionParam236 = (char)sjt_cast15;
#line 29
        sjf_array_char_initAt(sjt_parent92, sjt_functionParam235, sjt_functionParam236);
#line 29
        (*_return) = (sjs_string_heap*)malloc(sizeof(sjs_string_heap));
#line 29
        (*_return)->_refCount = 1;
#line 30
        (*_return)->count = sjv_newCount;
#line 30
        sjt_copy17 = &sjv_newData;
#line 30
        sjf_array_char_copy(&(*_return)->data, sjt_copy17);
#line 30
        sjf_string_heap((*_return));

        sjf_array_char_destroy(&sjv_newData);
    }
}

void sjf_string_copy(sjs_string* _this, sjs_string* _from) {
#line 6 "lib/common/string.sj"
    _this->count = _from->count;
#line 6
    sjf_array_char_copy(&_this->data, &_from->data);
}

void sjf_string_destroy(sjs_string* _this) {
}

void sjf_string_getAt(sjs_string* _parent, int32_t index, char* _return) {
    sjs_string* sjt_dot1334;
    int32_t sjt_functionParam221;
    sjs_array_char* sjt_parent82;

#line 34 "lib/common/string.sj"
    sjt_dot1334 = _parent;
#line 7 "lib/common/array.sj"
    sjt_parent82 = &(sjt_dot1334)->data;
#line 34 "lib/common/string.sj"
    sjt_functionParam221 = index;
#line 34
    sjf_array_char_getAt(sjt_parent82, sjt_functionParam221, _return);
}

void sjf_string_heap(sjs_string_heap* _this) {
}

void sjf_texture(sjs_texture* _this) {
}

void sjf_textureFromPng(sjs_string* fileName, sjs_texture* _return) {
    int32_t sjv_h;
    uint32_t sjv_id;
    int32_t sjv_w;

#line 2 "lib/ui/texture.sj"
    sjv_id = (uint32_t)0u;
#line 3
    sjv_w = 0;
#line 4
    sjv_h = 0;
#line 5
    sjv_id = png_texture_load((char*)fileName->data.data, &sjv_w, &sjv_h);
#line 8
    _return->size.w = sjv_w;
#line 8
    _return->size.h = sjv_h;
#line 8
    sjf_size(&_return->size);
#line 8
    _return->id = sjv_id;
#line 8
    sjf_texture(_return);
}

void sjf_textureFromPng_heap(sjs_string* fileName, sjs_texture_heap** _return) {
    int32_t sjv_h;
    uint32_t sjv_id;
    int32_t sjv_w;

#line 2 "lib/ui/texture.sj"
    sjv_id = (uint32_t)0u;
#line 3
    sjv_w = 0;
#line 4
    sjv_h = 0;
#line 5
    sjv_id = png_texture_load((char*)fileName->data.data, &sjv_w, &sjv_h);
#line 5
    (*_return) = (sjs_texture_heap*)malloc(sizeof(sjs_texture_heap));
#line 5
    (*_return)->_refCount = 1;
#line 8
    (*_return)->size.w = sjv_w;
#line 8
    (*_return)->size.h = sjv_h;
#line 8
    sjf_size(&(*_return)->size);
#line 8
    (*_return)->id = sjv_id;
#line 8
    sjf_texture_heap((*_return));
}

void sjf_texture_copy(sjs_texture* _this, sjs_texture* _from) {
#line 11 "lib/ui/texture.sj"
    sjf_size_copy(&_this->size, &_from->size);
#line 11
    _this->id = _from->id;
#line 19
    _retainGLid(_this->id);
}

void sjf_texture_destroy(sjs_texture* _this) {
#line 23 "lib/ui/texture.sj"
    if (_releaseGLid(_this->id)) {
#line 23
        glDeleteTextures(1, &_this->id);
#line 23
    }
}

void sjf_texture_heap(sjs_texture_heap* _this) {
}

void sjf_vec2(sjs_vec2* _this) {
}

void sjf_vec2_copy(sjs_vec2* _this, sjs_vec2* _from) {
#line 1 "lib/ui/vec2.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
}

void sjf_vec2_destroy(sjs_vec2* _this) {
}

void sjf_vec2_heap(sjs_vec2_heap* _this) {
}

void sjf_vec3(sjs_vec3* _this) {
}

void sjf_vec3_add(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3* _return) {
    sjs_vec3* sjt_dot89;
    sjs_vec3* sjt_dot90;
    sjs_vec3* sjt_dot91;
    sjs_vec3* sjt_dot92;
    sjs_vec3* sjt_dot93;
    sjs_vec3* sjt_dot94;
    float sjt_math59;
    float sjt_math60;
    float sjt_math61;
    float sjt_math62;
    float sjt_math63;
    float sjt_math64;

#line 22 "lib/ui/vec3.sj"
    sjt_dot89 = _parent;
#line 24
    sjt_math59 = (sjt_dot89)->x;
#line 22
    sjt_dot90 = v;
#line 24
    sjt_math60 = (sjt_dot90)->x;
#line 24
    _return->x = sjt_math59 + sjt_math60;
#line 22
    sjt_dot91 = _parent;
#line 25
    sjt_math61 = (sjt_dot91)->y;
#line 22
    sjt_dot92 = v;
#line 25
    sjt_math62 = (sjt_dot92)->y;
#line 25
    _return->y = sjt_math61 + sjt_math62;
#line 22
    sjt_dot93 = _parent;
#line 26
    sjt_math63 = (sjt_dot93)->z;
#line 22
    sjt_dot94 = v;
#line 26
    sjt_math64 = (sjt_dot94)->z;
#line 26
    _return->z = sjt_math63 + sjt_math64;
#line 26
    sjf_vec3(_return);
}

void sjf_vec3_add_heap(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3_heap** _return) {
    sjs_vec3* sjt_dot100;
    sjs_vec3* sjt_dot95;
    sjs_vec3* sjt_dot96;
    sjs_vec3* sjt_dot97;
    sjs_vec3* sjt_dot98;
    sjs_vec3* sjt_dot99;
    float sjt_math65;
    float sjt_math66;
    float sjt_math67;
    float sjt_math68;
    float sjt_math69;
    float sjt_math70;

    (*_return) = (sjs_vec3_heap*)malloc(sizeof(sjs_vec3_heap));
    (*_return)->_refCount = 1;
#line 22 "lib/ui/vec3.sj"
    sjt_dot95 = _parent;
#line 24
    sjt_math65 = (sjt_dot95)->x;
#line 22
    sjt_dot96 = v;
#line 24
    sjt_math66 = (sjt_dot96)->x;
#line 24
    (*_return)->x = sjt_math65 + sjt_math66;
#line 22
    sjt_dot97 = _parent;
#line 25
    sjt_math67 = (sjt_dot97)->y;
#line 22
    sjt_dot98 = v;
#line 25
    sjt_math68 = (sjt_dot98)->y;
#line 25
    (*_return)->y = sjt_math67 + sjt_math68;
#line 22
    sjt_dot99 = _parent;
#line 26
    sjt_math69 = (sjt_dot99)->z;
#line 22
    sjt_dot100 = v;
#line 26
    sjt_math70 = (sjt_dot100)->z;
#line 26
    (*_return)->z = sjt_math69 + sjt_math70;
#line 26
    sjf_vec3_heap((*_return));
}

void sjf_vec3_copy(sjs_vec3* _this, sjs_vec3* _from) {
#line 1 "lib/ui/vec3.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
#line 1
    _this->z = _from->z;
}

void sjf_vec3_cross(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3* _return) {
    sjs_vec3* sjt_dot144;
    sjs_vec3* sjt_dot145;
    sjs_vec3* sjt_dot146;
    sjs_vec3* sjt_dot147;
    sjs_vec3* sjt_dot148;
    sjs_vec3* sjt_dot149;
    sjs_vec3* sjt_dot150;
    sjs_vec3* sjt_dot151;
    sjs_vec3* sjt_dot152;
    sjs_vec3* sjt_dot153;
    sjs_vec3* sjt_dot154;
    sjs_vec3* sjt_dot155;
    float sjt_math127;
    float sjt_math128;
    float sjt_math129;
    float sjt_math130;
    float sjt_math131;
    float sjt_math132;
    float sjt_math133;
    float sjt_math134;
    float sjt_math135;
    float sjt_math136;
    float sjt_math137;
    float sjt_math138;
    float sjt_math139;
    float sjt_math140;
    float sjt_math141;
    float sjt_math142;
    float sjt_math143;
    float sjt_math144;

#line 47 "lib/ui/vec3.sj"
    sjt_dot144 = _parent;
#line 49
    sjt_math129 = (sjt_dot144)->y;
#line 47
    sjt_dot145 = v;
#line 49
    sjt_math130 = (sjt_dot145)->z;
#line 49
    sjt_math127 = sjt_math129 * sjt_math130;
#line 47
    sjt_dot146 = _parent;
#line 49
    sjt_math131 = (sjt_dot146)->z;
#line 47
    sjt_dot147 = v;
#line 49
    sjt_math132 = (sjt_dot147)->y;
#line 49
    sjt_math128 = sjt_math131 * sjt_math132;
#line 49
    _return->x = sjt_math127 - sjt_math128;
#line 47
    sjt_dot148 = _parent;
#line 50
    sjt_math135 = (sjt_dot148)->z;
#line 47
    sjt_dot149 = v;
#line 50
    sjt_math136 = (sjt_dot149)->x;
#line 50
    sjt_math133 = sjt_math135 * sjt_math136;
#line 47
    sjt_dot150 = _parent;
#line 50
    sjt_math137 = (sjt_dot150)->x;
#line 47
    sjt_dot151 = v;
#line 50
    sjt_math138 = (sjt_dot151)->z;
#line 50
    sjt_math134 = sjt_math137 * sjt_math138;
#line 50
    _return->y = sjt_math133 - sjt_math134;
#line 47
    sjt_dot152 = _parent;
#line 51
    sjt_math141 = (sjt_dot152)->x;
#line 47
    sjt_dot153 = v;
#line 51
    sjt_math142 = (sjt_dot153)->y;
#line 51
    sjt_math139 = sjt_math141 * sjt_math142;
#line 47
    sjt_dot154 = _parent;
#line 51
    sjt_math143 = (sjt_dot154)->y;
#line 47
    sjt_dot155 = v;
#line 51
    sjt_math144 = (sjt_dot155)->x;
#line 51
    sjt_math140 = sjt_math143 * sjt_math144;
#line 51
    _return->z = sjt_math139 - sjt_math140;
#line 51
    sjf_vec3(_return);
}

void sjf_vec3_cross_heap(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3_heap** _return) {
    sjs_vec3* sjt_dot156;
    sjs_vec3* sjt_dot157;
    sjs_vec3* sjt_dot158;
    sjs_vec3* sjt_dot159;
    sjs_vec3* sjt_dot160;
    sjs_vec3* sjt_dot161;
    sjs_vec3* sjt_dot162;
    sjs_vec3* sjt_dot163;
    sjs_vec3* sjt_dot164;
    sjs_vec3* sjt_dot165;
    sjs_vec3* sjt_dot166;
    sjs_vec3* sjt_dot167;
    float sjt_math145;
    float sjt_math146;
    float sjt_math147;
    float sjt_math148;
    float sjt_math149;
    float sjt_math150;
    float sjt_math151;
    float sjt_math152;
    float sjt_math153;
    float sjt_math154;
    float sjt_math155;
    float sjt_math156;
    float sjt_math157;
    float sjt_math158;
    float sjt_math159;
    float sjt_math160;
    float sjt_math161;
    float sjt_math162;

    (*_return) = (sjs_vec3_heap*)malloc(sizeof(sjs_vec3_heap));
    (*_return)->_refCount = 1;
#line 47 "lib/ui/vec3.sj"
    sjt_dot156 = _parent;
#line 49
    sjt_math147 = (sjt_dot156)->y;
#line 47
    sjt_dot157 = v;
#line 49
    sjt_math148 = (sjt_dot157)->z;
#line 49
    sjt_math145 = sjt_math147 * sjt_math148;
#line 47
    sjt_dot158 = _parent;
#line 49
    sjt_math149 = (sjt_dot158)->z;
#line 47
    sjt_dot159 = v;
#line 49
    sjt_math150 = (sjt_dot159)->y;
#line 49
    sjt_math146 = sjt_math149 * sjt_math150;
#line 49
    (*_return)->x = sjt_math145 - sjt_math146;
#line 47
    sjt_dot160 = _parent;
#line 50
    sjt_math153 = (sjt_dot160)->z;
#line 47
    sjt_dot161 = v;
#line 50
    sjt_math154 = (sjt_dot161)->x;
#line 50
    sjt_math151 = sjt_math153 * sjt_math154;
#line 47
    sjt_dot162 = _parent;
#line 50
    sjt_math155 = (sjt_dot162)->x;
#line 47
    sjt_dot163 = v;
#line 50
    sjt_math156 = (sjt_dot163)->z;
#line 50
    sjt_math152 = sjt_math155 * sjt_math156;
#line 50
    (*_return)->y = sjt_math151 - sjt_math152;
#line 47
    sjt_dot164 = _parent;
#line 51
    sjt_math159 = (sjt_dot164)->x;
#line 47
    sjt_dot165 = v;
#line 51
    sjt_math160 = (sjt_dot165)->y;
#line 51
    sjt_math157 = sjt_math159 * sjt_math160;
#line 47
    sjt_dot166 = _parent;
#line 51
    sjt_math161 = (sjt_dot166)->y;
#line 47
    sjt_dot167 = v;
#line 51
    sjt_math162 = (sjt_dot167)->x;
#line 51
    sjt_math158 = sjt_math161 * sjt_math162;
#line 51
    (*_return)->z = sjt_math157 - sjt_math158;
#line 51
    sjf_vec3_heap((*_return));
}

void sjf_vec3_destroy(sjs_vec3* _this) {
}

void sjf_vec3_dot(sjs_vec3* _parent, sjs_vec3* v, float* _return) {
    sjs_vec3* sjt_dot177;
    sjs_vec3* sjt_dot178;
    sjs_vec3* sjt_dot179;
    sjs_vec3* sjt_dot180;
    sjs_vec3* sjt_dot181;
    sjs_vec3* sjt_dot182;
    float sjt_math165;
    float sjt_math166;
    float sjt_math167;
    float sjt_math168;
    float sjt_math169;
    float sjt_math170;
    float sjt_math171;
    float sjt_math172;
    float sjt_math173;
    float sjt_math174;

#line 55 "lib/ui/vec3.sj"
    sjt_dot177 = _parent;
#line 56
    sjt_math169 = (sjt_dot177)->x;
#line 55
    sjt_dot178 = v;
#line 56
    sjt_math170 = (sjt_dot178)->x;
#line 56
    sjt_math167 = sjt_math169 * sjt_math170;
#line 55
    sjt_dot179 = _parent;
#line 56
    sjt_math171 = (sjt_dot179)->y;
#line 55
    sjt_dot180 = v;
#line 56
    sjt_math172 = (sjt_dot180)->y;
#line 56
    sjt_math168 = sjt_math171 * sjt_math172;
#line 56
    sjt_math165 = sjt_math167 + sjt_math168;
#line 55
    sjt_dot181 = _parent;
#line 56
    sjt_math173 = (sjt_dot181)->z;
#line 55
    sjt_dot182 = v;
#line 56
    sjt_math174 = (sjt_dot182)->z;
#line 56
    sjt_math166 = sjt_math173 * sjt_math174;
#line 56
    (*_return) = sjt_math165 + sjt_math166;
}

void sjf_vec3_heap(sjs_vec3_heap* _this) {
}

void sjf_vec3_max(sjs_vec3* a, sjs_vec3* b, sjs_vec3* _return) {
    sjs_vec3* sjt_dot76;
    sjs_vec3* sjt_dot77;
    sjs_vec3* sjt_dot78;
    sjs_vec3* sjt_dot79;
    sjs_vec3* sjt_dot80;
    sjs_vec3* sjt_dot81;
    float sjt_functionParam65;
    float sjt_functionParam66;
    float sjt_functionParam67;
    float sjt_functionParam68;
    float sjt_functionParam69;
    float sjt_functionParam70;

#line 68 "lib/ui/vec3.sj"
    sjt_dot76 = a;
#line 70
    sjt_functionParam65 = (sjt_dot76)->x;
#line 68
    sjt_dot77 = b;
#line 70
    sjt_functionParam66 = (sjt_dot77)->x;
#line 70
    sjf_f32_max(sjt_functionParam65, sjt_functionParam66, &_return->x);
#line 68
    sjt_dot78 = a;
#line 71
    sjt_functionParam67 = (sjt_dot78)->y;
#line 68
    sjt_dot79 = b;
#line 71
    sjt_functionParam68 = (sjt_dot79)->y;
#line 71
    sjf_f32_max(sjt_functionParam67, sjt_functionParam68, &_return->y);
#line 68
    sjt_dot80 = a;
#line 72
    sjt_functionParam69 = (sjt_dot80)->z;
#line 68
    sjt_dot81 = b;
#line 72
    sjt_functionParam70 = (sjt_dot81)->z;
#line 72
    sjf_f32_max(sjt_functionParam69, sjt_functionParam70, &_return->z);
#line 72
    sjf_vec3(_return);
}

void sjf_vec3_max_heap(sjs_vec3* a, sjs_vec3* b, sjs_vec3_heap** _return) {
    sjs_vec3* sjt_dot82;
    sjs_vec3* sjt_dot83;
    sjs_vec3* sjt_dot84;
    sjs_vec3* sjt_dot85;
    sjs_vec3* sjt_dot86;
    sjs_vec3* sjt_dot87;
    float sjt_functionParam71;
    float sjt_functionParam72;
    float sjt_functionParam73;
    float sjt_functionParam74;
    float sjt_functionParam75;
    float sjt_functionParam76;

    (*_return) = (sjs_vec3_heap*)malloc(sizeof(sjs_vec3_heap));
    (*_return)->_refCount = 1;
#line 68 "lib/ui/vec3.sj"
    sjt_dot82 = a;
#line 70
    sjt_functionParam71 = (sjt_dot82)->x;
#line 68
    sjt_dot83 = b;
#line 70
    sjt_functionParam72 = (sjt_dot83)->x;
#line 70
    sjf_f32_max(sjt_functionParam71, sjt_functionParam72, &(*_return)->x);
#line 68
    sjt_dot84 = a;
#line 71
    sjt_functionParam73 = (sjt_dot84)->y;
#line 68
    sjt_dot85 = b;
#line 71
    sjt_functionParam74 = (sjt_dot85)->y;
#line 71
    sjf_f32_max(sjt_functionParam73, sjt_functionParam74, &(*_return)->y);
#line 68
    sjt_dot86 = a;
#line 72
    sjt_functionParam75 = (sjt_dot86)->z;
#line 68
    sjt_dot87 = b;
#line 72
    sjt_functionParam76 = (sjt_dot87)->z;
#line 72
    sjf_f32_max(sjt_functionParam75, sjt_functionParam76, &(*_return)->z);
#line 72
    sjf_vec3_heap((*_return));
}

void sjf_vec3_min(sjs_vec3* a, sjs_vec3* b, sjs_vec3* _return) {
    sjs_vec3* sjt_dot63;
    sjs_vec3* sjt_dot64;
    sjs_vec3* sjt_dot65;
    sjs_vec3* sjt_dot66;
    sjs_vec3* sjt_dot67;
    sjs_vec3* sjt_dot68;
    float sjt_functionParam51;
    float sjt_functionParam52;
    float sjt_functionParam53;
    float sjt_functionParam54;
    float sjt_functionParam55;
    float sjt_functionParam56;

#line 60 "lib/ui/vec3.sj"
    sjt_dot63 = a;
#line 62
    sjt_functionParam51 = (sjt_dot63)->x;
#line 60
    sjt_dot64 = b;
#line 62
    sjt_functionParam52 = (sjt_dot64)->x;
#line 62
    sjf_f32_min(sjt_functionParam51, sjt_functionParam52, &_return->x);
#line 60
    sjt_dot65 = a;
#line 63
    sjt_functionParam53 = (sjt_dot65)->y;
#line 60
    sjt_dot66 = b;
#line 63
    sjt_functionParam54 = (sjt_dot66)->y;
#line 63
    sjf_f32_min(sjt_functionParam53, sjt_functionParam54, &_return->y);
#line 60
    sjt_dot67 = a;
#line 64
    sjt_functionParam55 = (sjt_dot67)->z;
#line 60
    sjt_dot68 = b;
#line 64
    sjt_functionParam56 = (sjt_dot68)->z;
#line 64
    sjf_f32_min(sjt_functionParam55, sjt_functionParam56, &_return->z);
#line 64
    sjf_vec3(_return);
}

void sjf_vec3_min_heap(sjs_vec3* a, sjs_vec3* b, sjs_vec3_heap** _return) {
    sjs_vec3* sjt_dot69;
    sjs_vec3* sjt_dot70;
    sjs_vec3* sjt_dot71;
    sjs_vec3* sjt_dot72;
    sjs_vec3* sjt_dot73;
    sjs_vec3* sjt_dot74;
    float sjt_functionParam57;
    float sjt_functionParam58;
    float sjt_functionParam59;
    float sjt_functionParam60;
    float sjt_functionParam61;
    float sjt_functionParam62;

    (*_return) = (sjs_vec3_heap*)malloc(sizeof(sjs_vec3_heap));
    (*_return)->_refCount = 1;
#line 60 "lib/ui/vec3.sj"
    sjt_dot69 = a;
#line 62
    sjt_functionParam57 = (sjt_dot69)->x;
#line 60
    sjt_dot70 = b;
#line 62
    sjt_functionParam58 = (sjt_dot70)->x;
#line 62
    sjf_f32_min(sjt_functionParam57, sjt_functionParam58, &(*_return)->x);
#line 60
    sjt_dot71 = a;
#line 63
    sjt_functionParam59 = (sjt_dot71)->y;
#line 60
    sjt_dot72 = b;
#line 63
    sjt_functionParam60 = (sjt_dot72)->y;
#line 63
    sjf_f32_min(sjt_functionParam59, sjt_functionParam60, &(*_return)->y);
#line 60
    sjt_dot73 = a;
#line 64
    sjt_functionParam61 = (sjt_dot73)->z;
#line 60
    sjt_dot74 = b;
#line 64
    sjt_functionParam62 = (sjt_dot74)->z;
#line 64
    sjf_f32_min(sjt_functionParam61, sjt_functionParam62, &(*_return)->z);
#line 64
    sjf_vec3_heap((*_return));
}

void sjf_vec3_normalize(sjs_vec3* _parent, sjs_vec3* _return) {
    sjs_vec3* sjt_dot126;
    sjs_vec3* sjt_dot127;
    sjs_vec3* sjt_dot128;
    sjs_vec3* sjt_dot129;
    sjs_vec3* sjt_dot130;
    sjs_vec3* sjt_dot131;
    sjs_vec3* sjt_dot132;
    sjs_vec3* sjt_dot133;
    sjs_vec3* sjt_dot134;
    float sjt_functionParam82;
    float sjt_math100;
    float sjt_math101;
    float sjt_math102;
    float sjt_math103;
    float sjt_math104;
    float sjt_math105;
    float sjt_math106;
    float sjt_math107;
    float sjt_math108;
    float sjt_math109;
    float sjt_math110;
    float sjt_math95;
    float sjt_math96;
    float sjt_math97;
    float sjt_math98;
    float sjt_math99;
    float sjv_t;

#line 38 "lib/ui/vec3.sj"
    sjt_dot126 = _parent;
#line 39
    sjt_math99 = (sjt_dot126)->x;
#line 38
    sjt_dot127 = _parent;
#line 39
    sjt_math100 = (sjt_dot127)->x;
#line 39
    sjt_math97 = sjt_math99 * sjt_math100;
#line 38
    sjt_dot128 = _parent;
#line 39
    sjt_math101 = (sjt_dot128)->y;
#line 38
    sjt_dot129 = _parent;
#line 39
    sjt_math102 = (sjt_dot129)->y;
#line 39
    sjt_math98 = sjt_math101 * sjt_math102;
#line 39
    sjt_math95 = sjt_math97 + sjt_math98;
#line 38
    sjt_dot130 = _parent;
#line 39
    sjt_math103 = (sjt_dot130)->z;
#line 38
    sjt_dot131 = _parent;
#line 39
    sjt_math104 = (sjt_dot131)->z;
#line 39
    sjt_math96 = sjt_math103 * sjt_math104;
#line 39
    sjt_functionParam82 = sjt_math95 + sjt_math96;
#line 39
    sjf_f32_sqrt(sjt_functionParam82, &sjv_t);
#line 38
    sjt_dot132 = _parent;
#line 41
    sjt_math105 = (sjt_dot132)->x;
#line 41
    sjt_math106 = sjv_t;
#line 41
    _return->x = sjt_math105 / sjt_math106;
#line 38
    sjt_dot133 = _parent;
#line 42
    sjt_math107 = (sjt_dot133)->y;
#line 42
    sjt_math108 = sjv_t;
#line 42
    _return->y = sjt_math107 / sjt_math108;
#line 38
    sjt_dot134 = _parent;
#line 43
    sjt_math109 = (sjt_dot134)->z;
#line 43
    sjt_math110 = sjv_t;
#line 43
    _return->z = sjt_math109 / sjt_math110;
#line 43
    sjf_vec3(_return);
}

void sjf_vec3_normalize_heap(sjs_vec3* _parent, sjs_vec3_heap** _return) {
    sjs_vec3* sjt_dot135;
    sjs_vec3* sjt_dot136;
    sjs_vec3* sjt_dot137;
    sjs_vec3* sjt_dot138;
    sjs_vec3* sjt_dot139;
    sjs_vec3* sjt_dot140;
    sjs_vec3* sjt_dot141;
    sjs_vec3* sjt_dot142;
    sjs_vec3* sjt_dot143;
    float sjt_functionParam83;
    float sjt_math111;
    float sjt_math112;
    float sjt_math113;
    float sjt_math114;
    float sjt_math115;
    float sjt_math116;
    float sjt_math117;
    float sjt_math118;
    float sjt_math119;
    float sjt_math120;
    float sjt_math121;
    float sjt_math122;
    float sjt_math123;
    float sjt_math124;
    float sjt_math125;
    float sjt_math126;
    float sjv_t;

#line 38 "lib/ui/vec3.sj"
    sjt_dot135 = _parent;
#line 39
    sjt_math115 = (sjt_dot135)->x;
#line 38
    sjt_dot136 = _parent;
#line 39
    sjt_math116 = (sjt_dot136)->x;
#line 39
    sjt_math113 = sjt_math115 * sjt_math116;
#line 38
    sjt_dot137 = _parent;
#line 39
    sjt_math117 = (sjt_dot137)->y;
#line 38
    sjt_dot138 = _parent;
#line 39
    sjt_math118 = (sjt_dot138)->y;
#line 39
    sjt_math114 = sjt_math117 * sjt_math118;
#line 39
    sjt_math111 = sjt_math113 + sjt_math114;
#line 38
    sjt_dot139 = _parent;
#line 39
    sjt_math119 = (sjt_dot139)->z;
#line 38
    sjt_dot140 = _parent;
#line 39
    sjt_math120 = (sjt_dot140)->z;
#line 39
    sjt_math112 = sjt_math119 * sjt_math120;
#line 39
    sjt_functionParam83 = sjt_math111 + sjt_math112;
#line 39
    sjf_f32_sqrt(sjt_functionParam83, &sjv_t);
#line 39
    (*_return) = (sjs_vec3_heap*)malloc(sizeof(sjs_vec3_heap));
#line 39
    (*_return)->_refCount = 1;
#line 38
    sjt_dot141 = _parent;
#line 41
    sjt_math121 = (sjt_dot141)->x;
#line 41
    sjt_math122 = sjv_t;
#line 41
    (*_return)->x = sjt_math121 / sjt_math122;
#line 38
    sjt_dot142 = _parent;
#line 42
    sjt_math123 = (sjt_dot142)->y;
#line 42
    sjt_math124 = sjv_t;
#line 42
    (*_return)->y = sjt_math123 / sjt_math124;
#line 38
    sjt_dot143 = _parent;
#line 43
    sjt_math125 = (sjt_dot143)->z;
#line 43
    sjt_math126 = sjv_t;
#line 43
    (*_return)->z = sjt_math125 / sjt_math126;
#line 43
    sjf_vec3_heap((*_return));
}

void sjf_vec3_subtract(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3* _return) {
    sjs_vec3* sjt_dot112;
    sjs_vec3* sjt_dot113;
    sjs_vec3* sjt_dot114;
    sjs_vec3* sjt_dot115;
    sjs_vec3* sjt_dot116;
    sjs_vec3* sjt_dot117;
    float sjt_math83;
    float sjt_math84;
    float sjt_math85;
    float sjt_math86;
    float sjt_math87;
    float sjt_math88;

#line 30 "lib/ui/vec3.sj"
    sjt_dot112 = _parent;
#line 32
    sjt_math83 = (sjt_dot112)->x;
#line 30
    sjt_dot113 = v;
#line 32
    sjt_math84 = (sjt_dot113)->x;
#line 32
    _return->x = sjt_math83 - sjt_math84;
#line 30
    sjt_dot114 = _parent;
#line 33
    sjt_math85 = (sjt_dot114)->y;
#line 30
    sjt_dot115 = v;
#line 33
    sjt_math86 = (sjt_dot115)->y;
#line 33
    _return->y = sjt_math85 - sjt_math86;
#line 30
    sjt_dot116 = _parent;
#line 34
    sjt_math87 = (sjt_dot116)->z;
#line 30
    sjt_dot117 = v;
#line 34
    sjt_math88 = (sjt_dot117)->z;
#line 34
    _return->z = sjt_math87 - sjt_math88;
#line 34
    sjf_vec3(_return);
}

void sjf_vec3_subtract_heap(sjs_vec3* _parent, sjs_vec3* v, sjs_vec3_heap** _return) {
    sjs_vec3* sjt_dot118;
    sjs_vec3* sjt_dot119;
    sjs_vec3* sjt_dot120;
    sjs_vec3* sjt_dot121;
    sjs_vec3* sjt_dot122;
    sjs_vec3* sjt_dot123;
    float sjt_math89;
    float sjt_math90;
    float sjt_math91;
    float sjt_math92;
    float sjt_math93;
    float sjt_math94;

    (*_return) = (sjs_vec3_heap*)malloc(sizeof(sjs_vec3_heap));
    (*_return)->_refCount = 1;
#line 30 "lib/ui/vec3.sj"
    sjt_dot118 = _parent;
#line 32
    sjt_math89 = (sjt_dot118)->x;
#line 30
    sjt_dot119 = v;
#line 32
    sjt_math90 = (sjt_dot119)->x;
#line 32
    (*_return)->x = sjt_math89 - sjt_math90;
#line 30
    sjt_dot120 = _parent;
#line 33
    sjt_math91 = (sjt_dot120)->y;
#line 30
    sjt_dot121 = v;
#line 33
    sjt_math92 = (sjt_dot121)->y;
#line 33
    (*_return)->y = sjt_math91 - sjt_math92;
#line 30
    sjt_dot122 = _parent;
#line 34
    sjt_math93 = (sjt_dot122)->z;
#line 30
    sjt_dot123 = v;
#line 34
    sjt_math94 = (sjt_dot123)->z;
#line 34
    (*_return)->z = sjt_math93 - sjt_math94;
#line 34
    sjf_vec3_heap((*_return));
}

void sjf_vec4(sjs_vec4* _this) {
}

void sjf_vec4_copy(sjs_vec4* _this, sjs_vec4* _from) {
#line 1 "lib/ui/vec4.sj"
    _this->x = _from->x;
#line 1
    _this->y = _from->y;
#line 1
    _this->z = _from->z;
#line 1
    _this->w = _from->w;
}

void sjf_vec4_destroy(sjs_vec4* _this) {
}

void sjf_vec4_heap(sjs_vec4_heap* _this) {
}

void sjf_vertexBuffer_vertex_location_texture_normal(sjs_vertexBuffer_vertex_location_texture_normal* _this) {
#line 95 "lib/ui/vertexBuffer.sj"
    _this->buffer = vertex_buffer_new((char*)_this->format.data.data);
#line 95
    vertex_buffer_push_back_indices(_this->buffer, (GLuint*)_this->indices.data, _this->indices.count);
#line 95
    vertex_buffer_push_back_vertices(_this->buffer, (sjs_vertex_location_texture_normal*)_this->vertices.data, _this->vertices.count);
}

void sjf_vertexBuffer_vertex_location_texture_normal_copy(sjs_vertexBuffer_vertex_location_texture_normal* _this, sjs_vertexBuffer_vertex_location_texture_normal* _from) {
#line 7 "lib/ui/vertexBuffer.sj"
    sjf_string_copy(&_this->format, &_from->format);
#line 7
    sjf_array_i32_copy(&_this->indices, &_from->indices);
#line 7
    sjf_array_vertex_location_texture_normal_copy(&_this->vertices, &_from->vertices);
#line 102
    _this->buffer = _from->buffer;
#line 102
    _retain(_this->buffer);
}

void sjf_vertexBuffer_vertex_location_texture_normal_destroy(sjs_vertexBuffer_vertex_location_texture_normal* _this) {
#line 107 "lib/ui/vertexBuffer.sj"
    if (_release(_this->buffer)) {
#line 107
        vertex_buffer_delete(_this->buffer);  
#line 107
    }
}

void sjf_vertexBuffer_vertex_location_texture_normal_heap(sjs_vertexBuffer_vertex_location_texture_normal_heap* _this) {
#line 95 "lib/ui/vertexBuffer.sj"
    _this->buffer = vertex_buffer_new((char*)_this->format.data.data);
#line 95
    vertex_buffer_push_back_indices(_this->buffer, (GLuint*)_this->indices.data, _this->indices.count);
#line 95
    vertex_buffer_push_back_vertices(_this->buffer, (sjs_vertex_location_texture_normal*)_this->vertices.data, _this->vertices.count);
}

void sjf_vertexBuffer_vertex_location_texture_normal_render(sjs_vertexBuffer_vertex_location_texture_normal* _parent) {
#line 89 "lib/ui/vertexBuffer.sj"
    vertex_buffer_render(_parent->buffer, GL_TRIANGLES);
}

void sjf_vertex_location_texture_normal(sjs_vertex_location_texture_normal* _this) {
}

void sjf_vertex_location_texture_normal_copy(sjs_vertex_location_texture_normal* _this, sjs_vertex_location_texture_normal* _from) {
#line 2 "lib/ui/vertexBufferBuilders.sj"
    sjf_vec3_copy(&_this->location, &_from->location);
#line 2
    sjf_vec2_copy(&_this->texture, &_from->texture);
#line 2
    sjf_vec3_copy(&_this->normal, &_from->normal);
}

void sjf_vertex_location_texture_normal_destroy(sjs_vertex_location_texture_normal* _this) {
}

void sjf_vertex_location_texture_normal_heap(sjs_vertex_location_texture_normal_heap* _this) {
}

void sjf_windowRenderer(sjs_windowRenderer* _this) {
#line 23 "lib/ui/windowRenderer.sj"
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
#line 23
        halt("SDL_Init Error: %s\n", SDL_GetError());
#line 23
    }
#line 23
    #ifdef __APPLE__
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#line 23
    #else
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#line 23
    #endif
#line 23
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#line 23
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#line 23
    _this->win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
#line 23
    if (_this->win == 0) {
#line 23
        halt("SDL_CreateWindow Error: %s\n", SDL_GetError());
#line 23
    }
#line 23
    SDL_GL_CreateContext((SDL_Window*)_this->win);
#line 23
    #ifdef WIN32
#line 23
    GLint GlewInitResult = glewInit();
#line 23
    if (GLEW_OK != GlewInitResult) 
#line 23
    {
#line 23
        halt("ERROR: %s\n", glewGetErrorString(GlewInitResult));
#line 23
    }
#line 23
    #endif
#line 23
    _this->ren = SDL_CreateRenderer((SDL_Window*)_this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#line 23
    if (_this->ren == 0) {
#line 23
        halt("SDL_CreateRenderer Error: %s\n", SDL_GetError());
#line 23
    }
#line 23
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
#line 23
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
#line 23
    glEnable( GL_BLEND );
}

void sjf_windowRenderer_copy(sjs_windowRenderer* _this, sjs_windowRenderer* _from) {
#line 64 "lib/ui/windowRenderer.sj"
    _this->ren = _from->ren;
#line 64
    _retain(_this->ren);
#line 64
    _this->win = _from->win;
#line 64
    _retain(_this->win);
}

void sjf_windowRenderer_destroy(sjs_windowRenderer* _this) {
#line 71 "lib/ui/windowRenderer.sj"
    if (_release(_this->ren)) {
#line 71
        SDL_DestroyRenderer(_this->ren);
#line 71
    }
#line 71
    if (_release(_this->win)) {
#line 71
        SDL_DestroyWindow(_this->win);
#line 71
    }
}

void sjf_windowRenderer_getSize(sjs_windowRenderer* _parent, sjs_size* _return) {
    int32_t sjv_h;
    int32_t sjv_w;

#line 8 "lib/ui/windowRenderer.sj"
    sjv_w = 0;
#line 9
    sjv_h = 0;
#line 10
    SDL_GetRendererOutputSize(_parent->ren, &sjv_w, &sjv_h);
#line 13
    _return->w = sjv_w;
#line 13
    _return->h = sjv_h;
#line 13
    sjf_size(_return);
}

void sjf_windowRenderer_getSize_heap(sjs_windowRenderer* _parent, sjs_size_heap** _return) {
    int32_t sjv_h;
    int32_t sjv_w;

#line 8 "lib/ui/windowRenderer.sj"
    sjv_w = 0;
#line 9
    sjv_h = 0;
#line 10
    SDL_GetRendererOutputSize(_parent->ren, &sjv_w, &sjv_h);
#line 10
    (*_return) = (sjs_size_heap*)malloc(sizeof(sjs_size_heap));
#line 10
    (*_return)->_refCount = 1;
#line 13
    (*_return)->w = sjv_w;
#line 13
    (*_return)->h = sjv_h;
#line 13
    sjf_size_heap((*_return));
}

void sjf_windowRenderer_heap(sjs_windowRenderer_heap* _this) {
#line 23 "lib/ui/windowRenderer.sj"
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
#line 23
        halt("SDL_Init Error: %s\n", SDL_GetError());
#line 23
    }
#line 23
    #ifdef __APPLE__
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#line 23
    #else
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#line 23
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#line 23
    #endif
#line 23
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#line 23
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#line 23
    _this->win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
#line 23
    if (_this->win == 0) {
#line 23
        halt("SDL_CreateWindow Error: %s\n", SDL_GetError());
#line 23
    }
#line 23
    SDL_GL_CreateContext((SDL_Window*)_this->win);
#line 23
    #ifdef WIN32
#line 23
    GLint GlewInitResult = glewInit();
#line 23
    if (GLEW_OK != GlewInitResult) 
#line 23
    {
#line 23
        halt("ERROR: %s\n", glewGetErrorString(GlewInitResult));
#line 23
    }
#line 23
    #endif
#line 23
    _this->ren = SDL_CreateRenderer((SDL_Window*)_this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#line 23
    if (_this->ren == 0) {
#line 23
        halt("SDL_CreateRenderer Error: %s\n", SDL_GetError());
#line 23
    }
#line 23
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
#line 23
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
#line 23
    glEnable( GL_BLEND );
}

void sjf_windowRenderer_present(sjs_windowRenderer* _parent) {
#line 17 "lib/ui/windowRenderer.sj"
    SDL_GL_SwapWindow((SDL_Window*)_parent->win);
}

void sji_anon2_animation_copy(sji_anon2_animation* _this, sji_anon2_animation* _from) {
    _this->_refCount = 1;
    _this->_parent = _from->_parent;
    _this->_parent->_refCount++;
    _this->destroy = _from->destroy;
    _this->asInterface = _from->asInterface;
    _this->nextFrame = _from->nextFrame;
}

void sji_anon2_animation_destroy(sji_anon2_animation* _this) {
    _this->_parent->_refCount--;
    if (_this->_parent->_refCount <= 0) {
        _this->destroy((void*)(((char*)_this->_parent) + sizeof(intptr_t)));
        free(_this->_parent);
    }
}

void sji_element_copy(sji_element* _this, sji_element* _from) {
    _this->_refCount = 1;
    _this->_parent = _from->_parent;
    _this->_parent->_refCount++;
    _this->destroy = _from->destroy;
    _this->asInterface = _from->asInterface;
    _this->getSize = _from->getSize;
    _this->getSize = _from->getSize;
    _this->getRect = _from->getRect;
    _this->setRect = _from->setRect;
    _this->render = _from->render;
    _this->fireMouseEvent = _from->fireMouseEvent;
}

void sji_element_destroy(sji_element* _this) {
    _this->_parent->_refCount--;
    if (_this->_parent->_refCount <= 0) {
        _this->destroy((void*)(((char*)_this->_parent) + sizeof(intptr_t)));
        free(_this->_parent);
    }
}

void sji_nauScene3dElement_model_copy(sji_nauScene3dElement_model* _this, sji_nauScene3dElement_model* _from) {
    _this->_refCount = 1;
    _this->_parent = _from->_parent;
    _this->_parent->_refCount++;
    _this->destroy = _from->destroy;
    _this->asInterface = _from->asInterface;
    _this->update = _from->update;
    _this->getZ = _from->getZ;
    _this->renderOrQueue = _from->renderOrQueue;
    _this->render = _from->render;
    _this->fireMouseEvent = _from->fireMouseEvent;
}

void sji_nauScene3dElement_model_destroy(sji_nauScene3dElement_model* _this) {
    _this->_parent->_refCount--;
    if (_this->_parent->_refCount <= 0) {
        _this->destroy((void*)(((char*)_this->_parent) + sizeof(intptr_t)));
        free(_this->_parent);
    }
}

int main(int argc, char** argv) {
    sjf_windowRenderer(&sjv_rootWindowRenderer);
#line 2 "lib/ui/size.sj"
    sjv_rootScene._size.w = 0;
#line 3
    sjv_rootScene._size.h = 0;
#line 3
    sjf_size(&sjv_rootScene._size);
#line 2 "lib/ui/mat4.sj"
    sjv_rootScene.model.m00 = 0.0f;
#line 3
    sjv_rootScene.model.m01 = 0.0f;
#line 4
    sjv_rootScene.model.m02 = 0.0f;
#line 5
    sjv_rootScene.model.m03 = 0.0f;
#line 6
    sjv_rootScene.model.m10 = 0.0f;
#line 7
    sjv_rootScene.model.m11 = 0.0f;
#line 8
    sjv_rootScene.model.m12 = 0.0f;
#line 9
    sjv_rootScene.model.m13 = 0.0f;
#line 10
    sjv_rootScene.model.m20 = 0.0f;
#line 11
    sjv_rootScene.model.m21 = 0.0f;
#line 12
    sjv_rootScene.model.m22 = 0.0f;
#line 13
    sjv_rootScene.model.m23 = 0.0f;
#line 14
    sjv_rootScene.model.m30 = 0.0f;
#line 15
    sjv_rootScene.model.m31 = 0.0f;
#line 16
    sjv_rootScene.model.m32 = 0.0f;
#line 17
    sjv_rootScene.model.m33 = 0.0f;
#line 17
    sjf_mat4(&sjv_rootScene.model);
#line 2
    sjv_rootScene.view.m00 = 0.0f;
#line 3
    sjv_rootScene.view.m01 = 0.0f;
#line 4
    sjv_rootScene.view.m02 = 0.0f;
#line 5
    sjv_rootScene.view.m03 = 0.0f;
#line 6
    sjv_rootScene.view.m10 = 0.0f;
#line 7
    sjv_rootScene.view.m11 = 0.0f;
#line 8
    sjv_rootScene.view.m12 = 0.0f;
#line 9
    sjv_rootScene.view.m13 = 0.0f;
#line 10
    sjv_rootScene.view.m20 = 0.0f;
#line 11
    sjv_rootScene.view.m21 = 0.0f;
#line 12
    sjv_rootScene.view.m22 = 0.0f;
#line 13
    sjv_rootScene.view.m23 = 0.0f;
#line 14
    sjv_rootScene.view.m30 = 0.0f;
#line 15
    sjv_rootScene.view.m31 = 0.0f;
#line 16
    sjv_rootScene.view.m32 = 0.0f;
#line 17
    sjv_rootScene.view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjv_rootScene.view);
#line 2
    sjv_rootScene.projection.m00 = 0.0f;
#line 3
    sjv_rootScene.projection.m01 = 0.0f;
#line 4
    sjv_rootScene.projection.m02 = 0.0f;
#line 5
    sjv_rootScene.projection.m03 = 0.0f;
#line 6
    sjv_rootScene.projection.m10 = 0.0f;
#line 7
    sjv_rootScene.projection.m11 = 0.0f;
#line 8
    sjv_rootScene.projection.m12 = 0.0f;
#line 9
    sjv_rootScene.projection.m13 = 0.0f;
#line 10
    sjv_rootScene.projection.m20 = 0.0f;
#line 11
    sjv_rootScene.projection.m21 = 0.0f;
#line 12
    sjv_rootScene.projection.m22 = 0.0f;
#line 13
    sjv_rootScene.projection.m23 = 0.0f;
#line 14
    sjv_rootScene.projection.m30 = 0.0f;
#line 15
    sjv_rootScene.projection.m31 = 0.0f;
#line 16
    sjv_rootScene.projection.m32 = 0.0f;
#line 17
    sjv_rootScene.projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjv_rootScene.projection);
#line 17
    sjf_scene2d(&sjv_rootScene);
#line 17
    sjf_anon1(&sjv_console);
#line 1 "lib/common/f32.sj"
    sjv_f32_pi = 3.14159265358979323846f;
#line 1 "lib/common/i32.sj"
    sjv_u32_maxValue = (uint32_t)4294967295u;
#line 3
    sjt_negate1 = 1;
#line 3
    result1 = -sjt_negate1;
#line 3
    sjt_math1 = result1;
#line 3
    sjt_math2 = 2147483647;
#line 3
    sjv_i32_maxValue = sjt_math1 - sjt_math2;
#line 4
    sjv_i32_minValue = 2147483647;
#line 1 "lib/common/string.sj"
    sjv_emptyStringData = 0;
#line 2
    sjv_emptyStringData = "";
#line 2 "lib/common/list.sj"
    sjv_animator.animations.array.dataSize = 0;
#line 3 "lib/common/array.sj"
    sjv_animator.animations.array.data = 0;
#line 4
    sjv_animator.animations.array._isGlobal = false;
#line 5
    sjv_animator.animations.array.count = 0;
#line 5
    sjf_array_heap_animation(&sjv_animator.animations.array);
#line 5
    sjf_list_heap_animation(&sjv_animator.animations);
#line 29 "lib/ui/animation.sj"
    sjv_animator.current = 0;
#line 29
    sjf_anon2(&sjv_animator);
#line 2 "lib/ui/borderLayout.sj"
    sjv_borderPosition.fill = 0;
#line 3
    sjv_borderPosition.left = 1;
#line 4
    sjv_borderPosition.right = 2;
#line 5
    sjv_borderPosition.top = 3;
#line 6
    sjv_borderPosition.bottom = 4;
#line 6
    sjf_anon3(&sjv_borderPosition);
#line 2 "lib/ui/buttonElement.sj"
    sjv_buttonState.normal = 0;
#line 3
    sjv_buttonState.hot = 1;
#line 4
    sjv_buttonState.pressed = 2;
#line 4
    sjf_anon4(&sjv_buttonState);
#line 4
    sjf_anon5(&sjv_colors);
#line 1 "lib/ui/gl.sj"
    sjv_glFeature_GL_BLEND = 0x0BE2;
#line 1
    sjv_glFeature_GL_CULL_FACE = 0x0B44;
#line 1
    sjv_glFeature_GL_DEPTH_TEST = 0x0B71;
#line 1
    sjv_glFeature_GL_DITHER = 0x0BD0;
#line 1
    sjv_glFeature_GL_POLYGON_OFFSET_FILL = 0x8037;
#line 1
    sjv_glFeature_GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
#line 1
    sjv_glFeature_GL_SAMPLE_COVERAGE = 0x80A0;
#line 1
    sjv_glFeature_GL_SCISSOR_TEST = 0x0C11;
#line 1
    sjv_glFeature_GL_STENCIL_TEST = 0x0B90;
#line 13
    sjv_glTexture_GL_TEXTURE_2D = 0x0DE1;
#line 13
    sjv_glTexture_GL_TEXTURE_CUBE_MAP = 0x8513;
#line 18
    sjv_glTextureAttribute_GL_TEXTURE_MIN_FILTER = 0x2801;
#line 18
    sjv_glTextureAttribute_GL_TEXTURE_MAG_FILTER = 0x2800;
#line 18
    sjv_glTextureAttribute_GL_TEXTURE_WRAP_S = 0x2802;
#line 18
    sjv_glTextureAttribute_GL_TEXTURE_WRAP_T = 0x2803;
#line 25
    sjv_glTextureValue_GL_CLAMP_TO_EDGE = 0x812F;
#line 25
    sjv_glTextureValue_GL_MIRRORED_REPEAT = 0x8370;
#line 25
    sjv_glTextureValue_GL_REPEAT = 0x2901;
#line 25
    sjv_glTextureValue_GL_NEAREST = 0x2600;
#line 25
    sjv_glTextureValue_GL_LINEAR = 0x2601;
#line 25
    sjv_glTextureValue_GL_NEAREST_MIPMAP_NEAREST = 0x2700;
#line 25
    sjv_glTextureValue_GL_LINEAR_MIPMAP_NEAREST = 0x2701;
#line 25
    sjv_glTextureValue_GL_NEAREST_MIPMAP_LINEAR = 0x2702;
#line 25
    sjv_glTextureValue_GL_LINEAR_MIPMAP_LINEAR = 0x2703;
#line 37
    sjv_glTextureFormat_GL_ALPHA = 0x1906;
#line 37
    sjv_glTextureFormat_GL_LUMINANCE = 0x1909;
#line 37
    sjv_glTextureFormat_GL_LUMINANCE_ALPHA = 0x190A;
#line 37
    sjv_glTextureFormat_GL_RGB = 0x1907;
#line 37
    sjv_glTextureFormat_GL_RGBA = 0x1908;
#line 45
    sjv_glTextureType_GL_UNSIGNED_BYTE = 0x1401;
#line 45
    sjv_glTextureType_GL_UNSIGNED_SHORT_5_6_5 = 0x8363;
#line 45
    sjv_glTextureType_GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
#line 45
    sjv_glTextureType_GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
#line 52
    sjv_glFramebufferAttachment_GL_COLOR_ATTACHMENT0 = 0x8CE0;
#line 52
    sjv_glFramebufferAttachment_GL_DEPTH_ATTACHMENT = 0x8D00;
#line 52
    sjv_glFramebufferAttachment_GL_STENCIL_ATTACHMENT = 0x8D20;
#line 58
    sjv_glFramebufferTexture_GL_TEXTURE_2D = 0x0DE1;
#line 58
    sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
#line 58
    sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
#line 58
    sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
#line 58
    sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
#line 58
    sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
#line 58
    sjv_glFramebufferTexture_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A;
#line 68
    sjv_glRenderbufferFormat_GL_RGBA4 = 0x8056;
#line 68
    sjv_glRenderbufferFormat_GL_RGB565 = 0x8D62;
#line 68
    sjv_glRenderbufferFormat_GL_RGB5_A1 = 0x8057;
#line 68
    sjv_glRenderbufferFormat_GL_DEPTH_COMPONENT16 = 0x81A5;
#line 68
    sjv_glRenderbufferFormat_GL_STENCIL_INDEX8 = 0x8D48;
#line 76
    sjv_glFramebufferStatus_GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
#line 76
    sjv_glFramebufferStatus_GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6;
#line 76
    sjv_glFramebufferStatus_GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7;
#line 76
    sjv_glFramebufferStatus_GL_FRAMEBUFFER_UNSUPPORTED = 0x8CDD;
#line 1 "lib/ui/loop.sj"
    sjv_mouseEvent_move = 0;
#line 2
    sjv_mouseEvent_up = 1;
#line 3
    sjv_mouseEvent_down = 2;
#line 1 "lib/ui/shader.sj"
    sjv_boxShader.vertex.count = 20;
#line 1
    sjv_boxShader.vertex.data.dataSize = 21;
#line 1
    sjv_boxShader.vertex.data.data = (void*)sjg_string1;
#line 1
    sjv_boxShader.vertex.data._isGlobal = true;
#line 1
    sjv_boxShader.vertex.data.count = 21;
#line 1
    sjf_array_char(&sjv_boxShader.vertex.data);
#line 1
    sjf_string(&sjv_boxShader.vertex);
#line 1
    sjv_boxShader.pixel.count = 20;
#line 1
    sjv_boxShader.pixel.data.dataSize = 21;
#line 1
    sjv_boxShader.pixel.data.data = (void*)sjg_string2;
#line 1
    sjv_boxShader.pixel.data._isGlobal = true;
#line 1
    sjv_boxShader.pixel.data.count = 21;
#line 1
    sjf_array_char(&sjv_boxShader.pixel.data);
#line 1
    sjf_string(&sjv_boxShader.pixel);
#line 1
    sjf_shader(&sjv_boxShader);
#line 2
    sjv_blurHorizontalShader.vertex.count = 24;
#line 2
    sjv_blurHorizontalShader.vertex.data.dataSize = 25;
#line 2
    sjv_blurHorizontalShader.vertex.data.data = (void*)sjg_string3;
#line 2
    sjv_blurHorizontalShader.vertex.data._isGlobal = true;
#line 2
    sjv_blurHorizontalShader.vertex.data.count = 25;
#line 2
    sjf_array_char(&sjv_blurHorizontalShader.vertex.data);
#line 2
    sjf_string(&sjv_blurHorizontalShader.vertex);
#line 2
    sjv_blurHorizontalShader.pixel.count = 28;
#line 2
    sjv_blurHorizontalShader.pixel.data.dataSize = 29;
#line 2
    sjv_blurHorizontalShader.pixel.data.data = (void*)sjg_string4;
#line 2
    sjv_blurHorizontalShader.pixel.data._isGlobal = true;
#line 2
    sjv_blurHorizontalShader.pixel.data.count = 29;
#line 2
    sjf_array_char(&sjv_blurHorizontalShader.pixel.data);
#line 2
    sjf_string(&sjv_blurHorizontalShader.pixel);
#line 2
    sjf_shader(&sjv_blurHorizontalShader);
#line 3
    sjv_blurVerticalShader.vertex.count = 24;
#line 3
    sjv_blurVerticalShader.vertex.data.dataSize = 25;
#line 3
    sjv_blurVerticalShader.vertex.data.data = (void*)sjg_string5;
#line 3
    sjv_blurVerticalShader.vertex.data._isGlobal = true;
#line 3
    sjv_blurVerticalShader.vertex.data.count = 25;
#line 3
    sjf_array_char(&sjv_blurVerticalShader.vertex.data);
#line 3
    sjf_string(&sjv_blurVerticalShader.vertex);
#line 3
    sjv_blurVerticalShader.pixel.count = 26;
#line 3
    sjv_blurVerticalShader.pixel.data.dataSize = 27;
#line 3
    sjv_blurVerticalShader.pixel.data.data = (void*)sjg_string6;
#line 3
    sjv_blurVerticalShader.pixel.data._isGlobal = true;
#line 3
    sjv_blurVerticalShader.pixel.data.count = 27;
#line 3
    sjf_array_char(&sjv_blurVerticalShader.pixel.data);
#line 3
    sjf_string(&sjv_blurVerticalShader.pixel);
#line 3
    sjf_shader(&sjv_blurVerticalShader);
#line 4
    sjv_imageShader.vertex.count = 20;
#line 4
    sjv_imageShader.vertex.data.dataSize = 21;
#line 4
    sjv_imageShader.vertex.data.data = (void*)sjg_string7;
#line 4
    sjv_imageShader.vertex.data._isGlobal = true;
#line 4
    sjv_imageShader.vertex.data.count = 21;
#line 4
    sjf_array_char(&sjv_imageShader.vertex.data);
#line 4
    sjf_string(&sjv_imageShader.vertex);
#line 4
    sjv_imageShader.pixel.count = 20;
#line 4
    sjv_imageShader.pixel.data.dataSize = 21;
#line 4
    sjv_imageShader.pixel.data.data = (void*)sjg_string8;
#line 4
    sjv_imageShader.pixel.data._isGlobal = true;
#line 4
    sjv_imageShader.pixel.data.count = 21;
#line 4
    sjf_array_char(&sjv_imageShader.pixel.data);
#line 4
    sjf_string(&sjv_imageShader.pixel);
#line 4
    sjf_shader(&sjv_imageShader);
#line 5
    sjv_phongColorShader.vertex.count = 26;
#line 5
    sjv_phongColorShader.vertex.data.dataSize = 27;
#line 5
    sjv_phongColorShader.vertex.data.data = (void*)sjg_string9;
#line 5
    sjv_phongColorShader.vertex.data._isGlobal = true;
#line 5
    sjv_phongColorShader.vertex.data.count = 27;
#line 5
    sjf_array_char(&sjv_phongColorShader.vertex.data);
#line 5
    sjf_string(&sjv_phongColorShader.vertex);
#line 5
    sjv_phongColorShader.pixel.count = 26;
#line 5
    sjv_phongColorShader.pixel.data.dataSize = 27;
#line 5
    sjv_phongColorShader.pixel.data.data = (void*)sjg_string10;
#line 5
    sjv_phongColorShader.pixel.data._isGlobal = true;
#line 5
    sjv_phongColorShader.pixel.data.count = 27;
#line 5
    sjf_array_char(&sjv_phongColorShader.pixel.data);
#line 5
    sjf_string(&sjv_phongColorShader.pixel);
#line 5
    sjf_shader(&sjv_phongColorShader);
#line 6
    sjv_phongTextureShader.vertex.count = 30;
#line 6
    sjv_phongTextureShader.vertex.data.dataSize = 31;
#line 6
    sjv_phongTextureShader.vertex.data.data = (void*)sjg_string11;
#line 6
    sjv_phongTextureShader.vertex.data._isGlobal = true;
#line 6
    sjv_phongTextureShader.vertex.data.count = 31;
#line 6
    sjf_array_char(&sjv_phongTextureShader.vertex.data);
#line 6
    sjf_string(&sjv_phongTextureShader.vertex);
#line 6
    sjv_phongTextureShader.pixel.count = 30;
#line 6
    sjv_phongTextureShader.pixel.data.dataSize = 31;
#line 6
    sjv_phongTextureShader.pixel.data.data = (void*)sjg_string12;
#line 6
    sjv_phongTextureShader.pixel.data._isGlobal = true;
#line 6
    sjv_phongTextureShader.pixel.data.count = 31;
#line 6
    sjf_array_char(&sjv_phongTextureShader.pixel.data);
#line 6
    sjf_string(&sjv_phongTextureShader.pixel);
#line 6
    sjf_shader(&sjv_phongTextureShader);
#line 7
    sjv_textShader.vertex.count = 24;
#line 7
    sjv_textShader.vertex.data.dataSize = 25;
#line 7
    sjv_textShader.vertex.data.data = (void*)sjg_string13;
#line 7
    sjv_textShader.vertex.data._isGlobal = true;
#line 7
    sjv_textShader.vertex.data.count = 25;
#line 7
    sjf_array_char(&sjv_textShader.vertex.data);
#line 7
    sjf_string(&sjv_textShader.vertex);
#line 7
    sjv_textShader.pixel.count = 24;
#line 7
    sjv_textShader.pixel.data.dataSize = 25;
#line 7
    sjv_textShader.pixel.data.data = (void*)sjg_string14;
#line 7
    sjv_textShader.pixel.data._isGlobal = true;
#line 7
    sjv_textShader.pixel.data.count = 25;
#line 7
    sjf_array_char(&sjv_textShader.pixel.data);
#line 7
    sjf_string(&sjv_textShader.pixel);
#line 7
    sjf_shader(&sjv_textShader);
#line 7
    sjf_anon6(&sjv_style);
#line 1 "lib/ui/vertexBufferBuilders.sj"
    sjv_vertex_location_texture_normal_format.count = 32;
#line 1
    sjv_vertex_location_texture_normal_format.data.dataSize = 33;
#line 1
    sjv_vertex_location_texture_normal_format.data.data = (void*)sjg_string15;
#line 1
    sjv_vertex_location_texture_normal_format.data._isGlobal = true;
#line 1
    sjv_vertex_location_texture_normal_format.data.count = 33;
#line 1
    sjf_array_char(&sjv_vertex_location_texture_normal_format.data);
#line 1
    sjf_string(&sjv_vertex_location_texture_normal_format);
#line 1
    sjt_cast1 = (sjs_fillElement_heap*)malloc(sizeof(sjs_fillElement_heap));
#line 1
    sjt_cast1->_refCount = 1;
#line 7 "nau.sj"
    sjt_cast1->children.dataSize = 2;
#line 3 "lib/common/array.sj"
    sjt_cast1->children.data = 0;
#line 4
    sjt_cast1->children._isGlobal = false;
#line 5
    sjt_cast1->children.count = 0;
#line 5
    sjf_array_heap_element(&sjt_cast1->children);
#line 7 "nau.sj"
    sjs_array_heap_element* array8;
#line 7
    array8 = &sjt_cast1->children;
#line 7
    sjt_parent7 = array8;
#line 7
    sjt_functionParam4 = 0;
#line 7
    sjt_cast2 = (sjs_nauScene3dElement_heap*)malloc(sizeof(sjs_nauScene3dElement_heap));
#line 7
    sjt_cast2->_refCount = 1;
#line 11
    sjt_cast2->children.dataSize = 3;
#line 3 "lib/common/array.sj"
    sjt_cast2->children.data = 0;
#line 4
    sjt_cast2->children._isGlobal = false;
#line 5
    sjt_cast2->children.count = 0;
#line 5
    sjf_array_heap_model(&sjt_cast2->children);
#line 11 "nau.sj"
    sjs_array_heap_model* array5;
#line 11
    array5 = &sjt_cast2->children;
#line 11
    sjt_parent41 = array5;
#line 11
    sjt_functionParam99 = 0;
#line 11
    sjt_cast9 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 11
    sjt_cast9->_refCount = 1;
#line 16
    sjt_negate11 = 3.7f;
#line 16
    result12 = -sjt_negate11;
#line 16
    sjt_functionParam181 = result12;
#line 16
    sjt_functionParam182 = 3.7f;
#line 16
    sjt_negate12 = 1.0f;
#line 16
    result13 = -sjt_negate12;
#line 16
    sjt_functionParam183 = result13;
#line 16
    sjt_functionParam184 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam185 = 0.0f;
#line 71
    sjt_functionParam186 = 0.0f;
#line 72
    sjt_functionParam187 = 1.0f;
#line 73
    sjt_functionParam188 = 0.0f;
#line 74
    sjt_functionParam189 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam181, sjt_functionParam182, sjt_functionParam183, sjt_functionParam184, sjt_functionParam185, sjt_functionParam186, sjt_functionParam187, sjt_functionParam188, sjt_functionParam189, &sjt_cast9->vertexBuffer);
#line 14 "nau.sj"
    sjt_copy11 = &sjv_phongTextureShader;
#line 14
    sjf_shader_copy(&sjt_cast9->shader, sjt_copy11);
#line 13
    sjt_call27.count = 17;
#line 13
    sjt_call27.data.dataSize = 18;
#line 13
    sjt_call27.data.data = (void*)sjg_string16;
#line 13
    sjt_call27.data._isGlobal = true;
#line 13
    sjt_call27.data.count = 18;
#line 13
    sjf_array_char(&sjt_call27.data);
#line 13
    sjf_string(&sjt_call27);
#line 13
    sjt_functionParam190 = &sjt_call27;
#line 13
    sjf_textureFromPng(sjt_functionParam190, &sjt_cast9->texture);
#line 15
    sjt_functionParam191 = 0.0f;
#line 15
    sjt_functionParam192 = 0.0f;
#line 15
    sjt_functionParam193 = 20.0f;
#line 15
    sjf_mat4_translate(sjt_functionParam191, sjt_functionParam192, sjt_functionParam193, &sjt_call28);
#line 15
    sjt_parent77 = &sjt_call28;
#line 15
    sjt_functionParam195 = 12.0f;
#line 15
    sjt_functionParam196 = 12.0f;
#line 15
    sjt_functionParam197 = 12.0f;
#line 15
    sjf_mat4_scale(sjt_functionParam195, sjt_functionParam196, sjt_functionParam197, &sjt_call29);
#line 15
    sjt_functionParam194 = &sjt_call29;
#line 15
    sjf_mat4_multiply(sjt_parent77, sjt_functionParam194, &sjt_cast9->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast9->center.x = 0.0f;
#line 3
    sjt_cast9->center.y = 0.0f;
#line 4
    sjt_cast9->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast9->center);
#line 17 "nau.sj"
    sjt_cast9->hasAlpha = true;
#line 7 "lib/common/string.sj"
    sjt_cast9->id.count = 0;
#line 10
    sjt_cast9->id.data.dataSize = 1;
#line 8
    sjt_cast9->id.data.data = sjv_emptyStringData;
#line 12
    sjt_cast9->id.data._isGlobal = true;
#line 11
    sjt_cast9->id.data.count = 1;
#line 11
    sjf_array_char(&sjt_cast9->id.data);
#line 11
    sjf_string(&sjt_cast9->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast9->_projection.m00 = 0.0f;
#line 3
    sjt_cast9->_projection.m01 = 0.0f;
#line 4
    sjt_cast9->_projection.m02 = 0.0f;
#line 5
    sjt_cast9->_projection.m03 = 0.0f;
#line 6
    sjt_cast9->_projection.m10 = 0.0f;
#line 7
    sjt_cast9->_projection.m11 = 0.0f;
#line 8
    sjt_cast9->_projection.m12 = 0.0f;
#line 9
    sjt_cast9->_projection.m13 = 0.0f;
#line 10
    sjt_cast9->_projection.m20 = 0.0f;
#line 11
    sjt_cast9->_projection.m21 = 0.0f;
#line 12
    sjt_cast9->_projection.m22 = 0.0f;
#line 13
    sjt_cast9->_projection.m23 = 0.0f;
#line 14
    sjt_cast9->_projection.m30 = 0.0f;
#line 15
    sjt_cast9->_projection.m31 = 0.0f;
#line 16
    sjt_cast9->_projection.m32 = 0.0f;
#line 17
    sjt_cast9->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast9->_projection);
#line 2
    sjt_cast9->_view.m00 = 0.0f;
#line 3
    sjt_cast9->_view.m01 = 0.0f;
#line 4
    sjt_cast9->_view.m02 = 0.0f;
#line 5
    sjt_cast9->_view.m03 = 0.0f;
#line 6
    sjt_cast9->_view.m10 = 0.0f;
#line 7
    sjt_cast9->_view.m11 = 0.0f;
#line 8
    sjt_cast9->_view.m12 = 0.0f;
#line 9
    sjt_cast9->_view.m13 = 0.0f;
#line 10
    sjt_cast9->_view.m20 = 0.0f;
#line 11
    sjt_cast9->_view.m21 = 0.0f;
#line 12
    sjt_cast9->_view.m22 = 0.0f;
#line 13
    sjt_cast9->_view.m23 = 0.0f;
#line 14
    sjt_cast9->_view.m30 = 0.0f;
#line 15
    sjt_cast9->_view.m31 = 0.0f;
#line 16
    sjt_cast9->_view.m32 = 0.0f;
#line 17
    sjt_cast9->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast9->_view);
#line 2
    sjt_cast9->_world.m00 = 0.0f;
#line 3
    sjt_cast9->_world.m01 = 0.0f;
#line 4
    sjt_cast9->_world.m02 = 0.0f;
#line 5
    sjt_cast9->_world.m03 = 0.0f;
#line 6
    sjt_cast9->_world.m10 = 0.0f;
#line 7
    sjt_cast9->_world.m11 = 0.0f;
#line 8
    sjt_cast9->_world.m12 = 0.0f;
#line 9
    sjt_cast9->_world.m13 = 0.0f;
#line 10
    sjt_cast9->_world.m20 = 0.0f;
#line 11
    sjt_cast9->_world.m21 = 0.0f;
#line 12
    sjt_cast9->_world.m22 = 0.0f;
#line 13
    sjt_cast9->_world.m23 = 0.0f;
#line 14
    sjt_cast9->_world.m30 = 0.0f;
#line 15
    sjt_cast9->_world.m31 = 0.0f;
#line 16
    sjt_cast9->_world.m32 = 0.0f;
#line 17
    sjt_cast9->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast9->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast9->_light.pos.x = 1.0f;
#line 2
    sjt_cast9->_light.pos.y = 1.0f;
#line 2
    sjt_cast9->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast9->_light.pos);
#line 3
    sjt_cast9->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast9->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast9->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast9->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast9->_light.diffuseColor);
#line 4
    sjt_cast9->_light.specColor.r = 1.0f;
#line 4
    sjt_cast9->_light.specColor.g = 1.0f;
#line 4
    sjt_cast9->_light.specColor.b = 1.0f;
#line 4
    sjt_cast9->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast9->_light.specColor);
#line 4
    sjf_light(&sjt_cast9->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast9->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast9->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast9->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast9->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast9);
#line 1 "lib/ui/model.sj"
    sjt_functionParam100 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast9);
#line 1
    sjf_array_heap_model_initAt(sjt_parent41, sjt_functionParam99, sjt_functionParam100);
#line 11 "nau.sj"
    sjt_parent78 = array5;
#line 11
    sjt_functionParam198 = 1;
#line 11
    sjt_cast11 = (sjs_leafPanel_heap*)malloc(sizeof(sjs_leafPanel_heap));
#line 11
    sjt_cast11->_refCount = 1;
#line 21
    sjt_cast11->textures.dataSize = 8;
#line 3 "lib/common/array.sj"
    sjt_cast11->textures.data = 0;
#line 4
    sjt_cast11->textures._isGlobal = false;
#line 5
    sjt_cast11->textures.count = 0;
#line 5
    sjf_array_texture(&sjt_cast11->textures);
#line 21 "nau.sj"
    sjs_array_texture* array6;
#line 21
    array6 = &sjt_cast11->textures;
#line 21
    sjt_parent101 = array6;
#line 21
    sjt_functionParam243 = 0;
#line 22
    sjt_call35.count = 21;
#line 22
    sjt_call35.data.dataSize = 22;
#line 22
    sjt_call35.data.data = (void*)sjg_string19;
#line 22
    sjt_call35.data._isGlobal = true;
#line 22
    sjt_call35.data.count = 22;
#line 22
    sjf_array_char(&sjt_call35.data);
#line 22
    sjf_string(&sjt_call35);
#line 22
    sjt_functionParam245 = &sjt_call35;
#line 22
    sjf_textureFromPng(sjt_functionParam245, &sjt_call34);
#line 22
    sjt_functionParam244 = &sjt_call34;
#line 22
    sjf_array_texture_initAt(sjt_parent101, sjt_functionParam243, sjt_functionParam244);
#line 21
    sjt_parent102 = array6;
#line 21
    sjt_functionParam246 = 1;
#line 23
    sjt_call37.count = 21;
#line 23
    sjt_call37.data.dataSize = 22;
#line 23
    sjt_call37.data.data = (void*)sjg_string20;
#line 23
    sjt_call37.data._isGlobal = true;
#line 23
    sjt_call37.data.count = 22;
#line 23
    sjf_array_char(&sjt_call37.data);
#line 23
    sjf_string(&sjt_call37);
#line 23
    sjt_functionParam248 = &sjt_call37;
#line 23
    sjf_textureFromPng(sjt_functionParam248, &sjt_call36);
#line 23
    sjt_functionParam247 = &sjt_call36;
#line 23
    sjf_array_texture_initAt(sjt_parent102, sjt_functionParam246, sjt_functionParam247);
#line 21
    sjt_parent103 = array6;
#line 21
    sjt_functionParam249 = 2;
#line 24
    sjt_call39.count = 21;
#line 24
    sjt_call39.data.dataSize = 22;
#line 24
    sjt_call39.data.data = (void*)sjg_string21;
#line 24
    sjt_call39.data._isGlobal = true;
#line 24
    sjt_call39.data.count = 22;
#line 24
    sjf_array_char(&sjt_call39.data);
#line 24
    sjf_string(&sjt_call39);
#line 24
    sjt_functionParam251 = &sjt_call39;
#line 24
    sjf_textureFromPng(sjt_functionParam251, &sjt_call38);
#line 24
    sjt_functionParam250 = &sjt_call38;
#line 24
    sjf_array_texture_initAt(sjt_parent103, sjt_functionParam249, sjt_functionParam250);
#line 21
    sjt_parent104 = array6;
#line 21
    sjt_functionParam252 = 3;
#line 25
    sjt_call41.count = 21;
#line 25
    sjt_call41.data.dataSize = 22;
#line 25
    sjt_call41.data.data = (void*)sjg_string22;
#line 25
    sjt_call41.data._isGlobal = true;
#line 25
    sjt_call41.data.count = 22;
#line 25
    sjf_array_char(&sjt_call41.data);
#line 25
    sjf_string(&sjt_call41);
#line 25
    sjt_functionParam254 = &sjt_call41;
#line 25
    sjf_textureFromPng(sjt_functionParam254, &sjt_call40);
#line 25
    sjt_functionParam253 = &sjt_call40;
#line 25
    sjf_array_texture_initAt(sjt_parent104, sjt_functionParam252, sjt_functionParam253);
#line 21
    sjt_parent105 = array6;
#line 21
    sjt_functionParam255 = 4;
#line 26
    sjt_call43.count = 21;
#line 26
    sjt_call43.data.dataSize = 22;
#line 26
    sjt_call43.data.data = (void*)sjg_string23;
#line 26
    sjt_call43.data._isGlobal = true;
#line 26
    sjt_call43.data.count = 22;
#line 26
    sjf_array_char(&sjt_call43.data);
#line 26
    sjf_string(&sjt_call43);
#line 26
    sjt_functionParam257 = &sjt_call43;
#line 26
    sjf_textureFromPng(sjt_functionParam257, &sjt_call42);
#line 26
    sjt_functionParam256 = &sjt_call42;
#line 26
    sjf_array_texture_initAt(sjt_parent105, sjt_functionParam255, sjt_functionParam256);
#line 21
    sjt_parent106 = array6;
#line 21
    sjt_functionParam258 = 5;
#line 27
    sjt_call45.count = 21;
#line 27
    sjt_call45.data.dataSize = 22;
#line 27
    sjt_call45.data.data = (void*)sjg_string24;
#line 27
    sjt_call45.data._isGlobal = true;
#line 27
    sjt_call45.data.count = 22;
#line 27
    sjf_array_char(&sjt_call45.data);
#line 27
    sjf_string(&sjt_call45);
#line 27
    sjt_functionParam260 = &sjt_call45;
#line 27
    sjf_textureFromPng(sjt_functionParam260, &sjt_call44);
#line 27
    sjt_functionParam259 = &sjt_call44;
#line 27
    sjf_array_texture_initAt(sjt_parent106, sjt_functionParam258, sjt_functionParam259);
#line 21
    sjt_parent107 = array6;
#line 21
    sjt_functionParam261 = 6;
#line 28
    sjt_call47.count = 21;
#line 28
    sjt_call47.data.dataSize = 22;
#line 28
    sjt_call47.data.data = (void*)sjg_string25;
#line 28
    sjt_call47.data._isGlobal = true;
#line 28
    sjt_call47.data.count = 22;
#line 28
    sjf_array_char(&sjt_call47.data);
#line 28
    sjf_string(&sjt_call47);
#line 28
    sjt_functionParam263 = &sjt_call47;
#line 28
    sjf_textureFromPng(sjt_functionParam263, &sjt_call46);
#line 28
    sjt_functionParam262 = &sjt_call46;
#line 28
    sjf_array_texture_initAt(sjt_parent107, sjt_functionParam261, sjt_functionParam262);
#line 21
    sjt_parent108 = array6;
#line 21
    sjt_functionParam264 = 7;
#line 29
    sjt_call49.count = 21;
#line 29
    sjt_call49.data.dataSize = 22;
#line 29
    sjt_call49.data.data = (void*)sjg_string26;
#line 29
    sjt_call49.data._isGlobal = true;
#line 29
    sjt_call49.data.count = 22;
#line 29
    sjf_array_char(&sjt_call49.data);
#line 29
    sjf_string(&sjt_call49);
#line 29
    sjt_functionParam266 = &sjt_call49;
#line 29
    sjf_textureFromPng(sjt_functionParam266, &sjt_call48);
#line 29
    sjt_functionParam265 = &sjt_call48;
#line 29
    sjf_array_texture_initAt(sjt_parent108, sjt_functionParam264, sjt_functionParam265);
#line 2 "lib/common/array.sj"
    sjt_cast11->children.dataSize = 0;
#line 3
    sjt_cast11->children.data = 0;
#line 4
    sjt_cast11->children._isGlobal = false;
#line 5
    sjt_cast11->children.count = 0;
#line 5
    sjf_array_heap_model(&sjt_cast11->children);
#line 35 "nau/leafPanel.sj"
    sjt_cast11->_angle = 0.1f;
#line 35
    sjf_leafPanel_heap(sjt_cast11);
#line 1 "lib/ui/model.sj"
    sjt_functionParam199 = (sji_nauScene3dElement_model*)sjf_leafPanel_heap_as_sji_nauScene3dElement_model(sjt_cast11);
#line 1
    sjf_array_heap_model_initAt(sjt_parent78, sjt_functionParam198, sjt_functionParam199);
#line 11 "nau.sj"
    sjt_parent109 = array5;
#line 11
    sjt_functionParam267 = 2;
#line 11
    sjt_cast17 = (sjs_panel3d_heap*)malloc(sizeof(sjs_panel3d_heap));
#line 11
    sjt_cast17->_refCount = 1;
#line 34
    sjt_functionParam273 = 0.0f;
#line 34
    sjt_negate15 = 1.3f;
#line 34
    result16 = -sjt_negate15;
#line 34
    sjt_functionParam274 = result16;
#line 34
    sjt_functionParam275 = 0.0f;
#line 34
    sjf_mat4_translate(sjt_functionParam273, sjt_functionParam274, sjt_functionParam275, &sjt_cast17->model);
#line 35
    sjt_cast17->children.dataSize = 10;
#line 3 "lib/common/array.sj"
    sjt_cast17->children.data = 0;
#line 4
    sjt_cast17->children._isGlobal = false;
#line 5
    sjt_cast17->children.count = 0;
#line 5
    sjf_array_heap_model(&sjt_cast17->children);
#line 35 "nau.sj"
    sjs_array_heap_model* array7;
#line 35
    array7 = &sjt_cast17->children;
#line 35
    sjt_parent117 = array7;
#line 35
    sjt_functionParam276 = 0;
#line 35
    sjt_cast18 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast18->_refCount = 1;
#line 41
    sjt_negate16 = 4.3f;
#line 41
    result17 = -sjt_negate16;
#line 41
    sjt_functionParam278 = result17;
#line 41
    sjt_functionParam279 = 4.3f;
#line 41
    sjt_negate17 = 1.0f;
#line 41
    result18 = -sjt_negate17;
#line 41
    sjt_functionParam280 = result18;
#line 41
    sjt_functionParam281 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam282 = 0.0f;
#line 71
    sjt_functionParam283 = 0.0f;
#line 72
    sjt_functionParam284 = 1.0f;
#line 73
    sjt_functionParam285 = 0.0f;
#line 74
    sjt_functionParam286 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam278, sjt_functionParam279, sjt_functionParam280, sjt_functionParam281, sjt_functionParam282, sjt_functionParam283, sjt_functionParam284, sjt_functionParam285, sjt_functionParam286, &sjt_cast18->vertexBuffer);
#line 39 "nau.sj"
    sjt_copy18 = &sjv_phongTextureShader;
#line 39
    sjf_shader_copy(&sjt_cast18->shader, sjt_copy18);
#line 38
    sjt_call50.count = 16;
#line 38
    sjt_call50.data.dataSize = 17;
#line 38
    sjt_call50.data.data = (void*)sjg_string28;
#line 38
    sjt_call50.data._isGlobal = true;
#line 38
    sjt_call50.data.count = 17;
#line 38
    sjf_array_char(&sjt_call50.data);
#line 38
    sjf_string(&sjt_call50);
#line 38
    sjt_functionParam287 = &sjt_call50;
#line 38
    sjf_textureFromPng(sjt_functionParam287, &sjt_cast18->texture);
#line 40
    sjt_negate18 = 8.6f;
#line 40
    result19 = -sjt_negate18;
#line 40
    sjt_functionParam288 = result19;
#line 40
    sjt_functionParam289 = 0.0f;
#line 40
    sjt_functionParam290 = 6.2f;
#line 40
    sjf_mat4_translate(sjt_functionParam288, sjt_functionParam289, sjt_functionParam290, &sjt_call51);
#line 40
    sjt_parent118 = &sjt_call51;
#line 40
    sjt_functionParam292 = 2.0f;
#line 40
    sjt_functionParam293 = 2.0f;
#line 40
    sjt_functionParam294 = 2.0f;
#line 40
    sjf_mat4_scale(sjt_functionParam292, sjt_functionParam293, sjt_functionParam294, &sjt_call52);
#line 40
    sjt_functionParam291 = &sjt_call52;
#line 40
    sjf_mat4_multiply(sjt_parent118, sjt_functionParam291, &sjt_cast18->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast18->center.x = 0.0f;
#line 3
    sjt_cast18->center.y = 0.0f;
#line 4
    sjt_cast18->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast18->center);
#line 42 "nau.sj"
    sjt_cast18->hasAlpha = true;
#line 37
    sjt_cast18->id.count = 8;
#line 37
    sjt_cast18->id.data.dataSize = 9;
#line 37
    sjt_cast18->id.data.data = (void*)sjg_string27;
#line 37
    sjt_cast18->id.data._isGlobal = true;
#line 37
    sjt_cast18->id.data.count = 9;
#line 37
    sjf_array_char(&sjt_cast18->id.data);
#line 37
    sjf_string(&sjt_cast18->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast18->_projection.m00 = 0.0f;
#line 3
    sjt_cast18->_projection.m01 = 0.0f;
#line 4
    sjt_cast18->_projection.m02 = 0.0f;
#line 5
    sjt_cast18->_projection.m03 = 0.0f;
#line 6
    sjt_cast18->_projection.m10 = 0.0f;
#line 7
    sjt_cast18->_projection.m11 = 0.0f;
#line 8
    sjt_cast18->_projection.m12 = 0.0f;
#line 9
    sjt_cast18->_projection.m13 = 0.0f;
#line 10
    sjt_cast18->_projection.m20 = 0.0f;
#line 11
    sjt_cast18->_projection.m21 = 0.0f;
#line 12
    sjt_cast18->_projection.m22 = 0.0f;
#line 13
    sjt_cast18->_projection.m23 = 0.0f;
#line 14
    sjt_cast18->_projection.m30 = 0.0f;
#line 15
    sjt_cast18->_projection.m31 = 0.0f;
#line 16
    sjt_cast18->_projection.m32 = 0.0f;
#line 17
    sjt_cast18->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast18->_projection);
#line 2
    sjt_cast18->_view.m00 = 0.0f;
#line 3
    sjt_cast18->_view.m01 = 0.0f;
#line 4
    sjt_cast18->_view.m02 = 0.0f;
#line 5
    sjt_cast18->_view.m03 = 0.0f;
#line 6
    sjt_cast18->_view.m10 = 0.0f;
#line 7
    sjt_cast18->_view.m11 = 0.0f;
#line 8
    sjt_cast18->_view.m12 = 0.0f;
#line 9
    sjt_cast18->_view.m13 = 0.0f;
#line 10
    sjt_cast18->_view.m20 = 0.0f;
#line 11
    sjt_cast18->_view.m21 = 0.0f;
#line 12
    sjt_cast18->_view.m22 = 0.0f;
#line 13
    sjt_cast18->_view.m23 = 0.0f;
#line 14
    sjt_cast18->_view.m30 = 0.0f;
#line 15
    sjt_cast18->_view.m31 = 0.0f;
#line 16
    sjt_cast18->_view.m32 = 0.0f;
#line 17
    sjt_cast18->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast18->_view);
#line 2
    sjt_cast18->_world.m00 = 0.0f;
#line 3
    sjt_cast18->_world.m01 = 0.0f;
#line 4
    sjt_cast18->_world.m02 = 0.0f;
#line 5
    sjt_cast18->_world.m03 = 0.0f;
#line 6
    sjt_cast18->_world.m10 = 0.0f;
#line 7
    sjt_cast18->_world.m11 = 0.0f;
#line 8
    sjt_cast18->_world.m12 = 0.0f;
#line 9
    sjt_cast18->_world.m13 = 0.0f;
#line 10
    sjt_cast18->_world.m20 = 0.0f;
#line 11
    sjt_cast18->_world.m21 = 0.0f;
#line 12
    sjt_cast18->_world.m22 = 0.0f;
#line 13
    sjt_cast18->_world.m23 = 0.0f;
#line 14
    sjt_cast18->_world.m30 = 0.0f;
#line 15
    sjt_cast18->_world.m31 = 0.0f;
#line 16
    sjt_cast18->_world.m32 = 0.0f;
#line 17
    sjt_cast18->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast18->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast18->_light.pos.x = 1.0f;
#line 2
    sjt_cast18->_light.pos.y = 1.0f;
#line 2
    sjt_cast18->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast18->_light.pos);
#line 3
    sjt_cast18->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast18->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast18->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast18->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast18->_light.diffuseColor);
#line 4
    sjt_cast18->_light.specColor.r = 1.0f;
#line 4
    sjt_cast18->_light.specColor.g = 1.0f;
#line 4
    sjt_cast18->_light.specColor.b = 1.0f;
#line 4
    sjt_cast18->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast18->_light.specColor);
#line 4
    sjf_light(&sjt_cast18->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast18->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast18->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast18->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast18->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast18);
#line 1 "lib/ui/model.sj"
    sjt_functionParam277 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast18);
#line 1
    sjf_array_heap_model_initAt(sjt_parent117, sjt_functionParam276, sjt_functionParam277);
#line 35 "nau.sj"
    sjt_parent119 = array7;
#line 35
    sjt_functionParam295 = 1;
#line 35
    sjt_cast19 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast19->_refCount = 1;
#line 51
    sjt_negate19 = 4.3f;
#line 51
    result20 = -sjt_negate19;
#line 51
    sjt_functionParam297 = result20;
#line 51
    sjt_functionParam298 = 4.3f;
#line 51
    sjt_negate20 = 1.0f;
#line 51
    result21 = -sjt_negate20;
#line 51
    sjt_functionParam299 = result21;
#line 51
    sjt_functionParam300 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam301 = 0.0f;
#line 71
    sjt_functionParam302 = 0.0f;
#line 72
    sjt_functionParam303 = 1.0f;
#line 73
    sjt_functionParam304 = 0.0f;
#line 74
    sjt_functionParam305 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam297, sjt_functionParam298, sjt_functionParam299, sjt_functionParam300, sjt_functionParam301, sjt_functionParam302, sjt_functionParam303, sjt_functionParam304, sjt_functionParam305, &sjt_cast19->vertexBuffer);
#line 49 "nau.sj"
    sjt_copy19 = &sjv_phongTextureShader;
#line 49
    sjf_shader_copy(&sjt_cast19->shader, sjt_copy19);
#line 48
    sjt_call53.count = 16;
#line 48
    sjt_call53.data.dataSize = 17;
#line 48
    sjt_call53.data.data = (void*)sjg_string30;
#line 48
    sjt_call53.data._isGlobal = true;
#line 48
    sjt_call53.data.count = 17;
#line 48
    sjf_array_char(&sjt_call53.data);
#line 48
    sjf_string(&sjt_call53);
#line 48
    sjt_functionParam306 = &sjt_call53;
#line 48
    sjf_textureFromPng(sjt_functionParam306, &sjt_cast19->texture);
#line 50
    sjt_functionParam307 = 8.6f;
#line 50
    sjt_functionParam308 = 0.0f;
#line 50
    sjt_functionParam309 = 6.2f;
#line 50
    sjf_mat4_translate(sjt_functionParam307, sjt_functionParam308, sjt_functionParam309, &sjt_call54);
#line 50
    sjt_parent120 = &sjt_call54;
#line 50
    sjt_functionParam311 = 2.0f;
#line 50
    sjt_functionParam312 = 2.0f;
#line 50
    sjt_functionParam313 = 2.0f;
#line 50
    sjf_mat4_scale(sjt_functionParam311, sjt_functionParam312, sjt_functionParam313, &sjt_call55);
#line 50
    sjt_functionParam310 = &sjt_call55;
#line 50
    sjf_mat4_multiply(sjt_parent120, sjt_functionParam310, &sjt_cast19->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast19->center.x = 0.0f;
#line 3
    sjt_cast19->center.y = 0.0f;
#line 4
    sjt_cast19->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast19->center);
#line 52 "nau.sj"
    sjt_cast19->hasAlpha = true;
#line 47
    sjt_cast19->id.count = 8;
#line 47
    sjt_cast19->id.data.dataSize = 9;
#line 47
    sjt_cast19->id.data.data = (void*)sjg_string29;
#line 47
    sjt_cast19->id.data._isGlobal = true;
#line 47
    sjt_cast19->id.data.count = 9;
#line 47
    sjf_array_char(&sjt_cast19->id.data);
#line 47
    sjf_string(&sjt_cast19->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast19->_projection.m00 = 0.0f;
#line 3
    sjt_cast19->_projection.m01 = 0.0f;
#line 4
    sjt_cast19->_projection.m02 = 0.0f;
#line 5
    sjt_cast19->_projection.m03 = 0.0f;
#line 6
    sjt_cast19->_projection.m10 = 0.0f;
#line 7
    sjt_cast19->_projection.m11 = 0.0f;
#line 8
    sjt_cast19->_projection.m12 = 0.0f;
#line 9
    sjt_cast19->_projection.m13 = 0.0f;
#line 10
    sjt_cast19->_projection.m20 = 0.0f;
#line 11
    sjt_cast19->_projection.m21 = 0.0f;
#line 12
    sjt_cast19->_projection.m22 = 0.0f;
#line 13
    sjt_cast19->_projection.m23 = 0.0f;
#line 14
    sjt_cast19->_projection.m30 = 0.0f;
#line 15
    sjt_cast19->_projection.m31 = 0.0f;
#line 16
    sjt_cast19->_projection.m32 = 0.0f;
#line 17
    sjt_cast19->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast19->_projection);
#line 2
    sjt_cast19->_view.m00 = 0.0f;
#line 3
    sjt_cast19->_view.m01 = 0.0f;
#line 4
    sjt_cast19->_view.m02 = 0.0f;
#line 5
    sjt_cast19->_view.m03 = 0.0f;
#line 6
    sjt_cast19->_view.m10 = 0.0f;
#line 7
    sjt_cast19->_view.m11 = 0.0f;
#line 8
    sjt_cast19->_view.m12 = 0.0f;
#line 9
    sjt_cast19->_view.m13 = 0.0f;
#line 10
    sjt_cast19->_view.m20 = 0.0f;
#line 11
    sjt_cast19->_view.m21 = 0.0f;
#line 12
    sjt_cast19->_view.m22 = 0.0f;
#line 13
    sjt_cast19->_view.m23 = 0.0f;
#line 14
    sjt_cast19->_view.m30 = 0.0f;
#line 15
    sjt_cast19->_view.m31 = 0.0f;
#line 16
    sjt_cast19->_view.m32 = 0.0f;
#line 17
    sjt_cast19->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast19->_view);
#line 2
    sjt_cast19->_world.m00 = 0.0f;
#line 3
    sjt_cast19->_world.m01 = 0.0f;
#line 4
    sjt_cast19->_world.m02 = 0.0f;
#line 5
    sjt_cast19->_world.m03 = 0.0f;
#line 6
    sjt_cast19->_world.m10 = 0.0f;
#line 7
    sjt_cast19->_world.m11 = 0.0f;
#line 8
    sjt_cast19->_world.m12 = 0.0f;
#line 9
    sjt_cast19->_world.m13 = 0.0f;
#line 10
    sjt_cast19->_world.m20 = 0.0f;
#line 11
    sjt_cast19->_world.m21 = 0.0f;
#line 12
    sjt_cast19->_world.m22 = 0.0f;
#line 13
    sjt_cast19->_world.m23 = 0.0f;
#line 14
    sjt_cast19->_world.m30 = 0.0f;
#line 15
    sjt_cast19->_world.m31 = 0.0f;
#line 16
    sjt_cast19->_world.m32 = 0.0f;
#line 17
    sjt_cast19->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast19->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast19->_light.pos.x = 1.0f;
#line 2
    sjt_cast19->_light.pos.y = 1.0f;
#line 2
    sjt_cast19->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast19->_light.pos);
#line 3
    sjt_cast19->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast19->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast19->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast19->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast19->_light.diffuseColor);
#line 4
    sjt_cast19->_light.specColor.r = 1.0f;
#line 4
    sjt_cast19->_light.specColor.g = 1.0f;
#line 4
    sjt_cast19->_light.specColor.b = 1.0f;
#line 4
    sjt_cast19->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast19->_light.specColor);
#line 4
    sjf_light(&sjt_cast19->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast19->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast19->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast19->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast19->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast19);
#line 1 "lib/ui/model.sj"
    sjt_functionParam296 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast19);
#line 1
    sjf_array_heap_model_initAt(sjt_parent119, sjt_functionParam295, sjt_functionParam296);
#line 35 "nau.sj"
    sjt_parent121 = array7;
#line 35
    sjt_functionParam314 = 2;
#line 35
    sjt_cast20 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast20->_refCount = 1;
#line 60
    sjt_negate21 = 4.3f;
#line 60
    result22 = -sjt_negate21;
#line 60
    sjt_functionParam316 = result22;
#line 60
    sjt_functionParam317 = 4.3f;
#line 60
    sjt_negate22 = 1.0f;
#line 60
    result23 = -sjt_negate22;
#line 60
    sjt_functionParam318 = result23;
#line 60
    sjt_functionParam319 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam320 = 0.0f;
#line 71
    sjt_functionParam321 = 0.0f;
#line 72
    sjt_functionParam322 = 1.0f;
#line 73
    sjt_functionParam323 = 0.0f;
#line 74
    sjt_functionParam324 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam316, sjt_functionParam317, sjt_functionParam318, sjt_functionParam319, sjt_functionParam320, sjt_functionParam321, sjt_functionParam322, sjt_functionParam323, sjt_functionParam324, &sjt_cast20->vertexBuffer);
#line 58 "nau.sj"
    sjt_copy20 = &sjv_phongTextureShader;
#line 58
    sjf_shader_copy(&sjt_cast20->shader, sjt_copy20);
#line 57
    sjt_call56.count = 16;
#line 57
    sjt_call56.data.dataSize = 17;
#line 57
    sjt_call56.data.data = (void*)sjg_string32;
#line 57
    sjt_call56.data._isGlobal = true;
#line 57
    sjt_call56.data.count = 17;
#line 57
    sjf_array_char(&sjt_call56.data);
#line 57
    sjf_string(&sjt_call56);
#line 57
    sjt_functionParam325 = &sjt_call56;
#line 57
    sjf_textureFromPng(sjt_functionParam325, &sjt_cast20->texture);
#line 59
    sjt_negate23 = 8.6f;
#line 59
    result24 = -sjt_negate23;
#line 59
    sjt_functionParam326 = result24;
#line 59
    sjt_functionParam327 = 0.0f;
#line 59
    sjt_functionParam328 = 4.2f;
#line 59
    sjf_mat4_translate(sjt_functionParam326, sjt_functionParam327, sjt_functionParam328, &sjt_call57);
#line 59
    sjt_parent122 = &sjt_call57;
#line 59
    sjt_functionParam330 = 2.0f;
#line 59
    sjt_functionParam331 = 2.0f;
#line 59
    sjt_functionParam332 = 2.0f;
#line 59
    sjf_mat4_scale(sjt_functionParam330, sjt_functionParam331, sjt_functionParam332, &sjt_call58);
#line 59
    sjt_functionParam329 = &sjt_call58;
#line 59
    sjf_mat4_multiply(sjt_parent122, sjt_functionParam329, &sjt_cast20->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast20->center.x = 0.0f;
#line 3
    sjt_cast20->center.y = 0.0f;
#line 4
    sjt_cast20->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast20->center);
#line 61 "nau.sj"
    sjt_cast20->hasAlpha = true;
#line 56
    sjt_cast20->id.count = 8;
#line 56
    sjt_cast20->id.data.dataSize = 9;
#line 56
    sjt_cast20->id.data.data = (void*)sjg_string31;
#line 56
    sjt_cast20->id.data._isGlobal = true;
#line 56
    sjt_cast20->id.data.count = 9;
#line 56
    sjf_array_char(&sjt_cast20->id.data);
#line 56
    sjf_string(&sjt_cast20->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast20->_projection.m00 = 0.0f;
#line 3
    sjt_cast20->_projection.m01 = 0.0f;
#line 4
    sjt_cast20->_projection.m02 = 0.0f;
#line 5
    sjt_cast20->_projection.m03 = 0.0f;
#line 6
    sjt_cast20->_projection.m10 = 0.0f;
#line 7
    sjt_cast20->_projection.m11 = 0.0f;
#line 8
    sjt_cast20->_projection.m12 = 0.0f;
#line 9
    sjt_cast20->_projection.m13 = 0.0f;
#line 10
    sjt_cast20->_projection.m20 = 0.0f;
#line 11
    sjt_cast20->_projection.m21 = 0.0f;
#line 12
    sjt_cast20->_projection.m22 = 0.0f;
#line 13
    sjt_cast20->_projection.m23 = 0.0f;
#line 14
    sjt_cast20->_projection.m30 = 0.0f;
#line 15
    sjt_cast20->_projection.m31 = 0.0f;
#line 16
    sjt_cast20->_projection.m32 = 0.0f;
#line 17
    sjt_cast20->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast20->_projection);
#line 2
    sjt_cast20->_view.m00 = 0.0f;
#line 3
    sjt_cast20->_view.m01 = 0.0f;
#line 4
    sjt_cast20->_view.m02 = 0.0f;
#line 5
    sjt_cast20->_view.m03 = 0.0f;
#line 6
    sjt_cast20->_view.m10 = 0.0f;
#line 7
    sjt_cast20->_view.m11 = 0.0f;
#line 8
    sjt_cast20->_view.m12 = 0.0f;
#line 9
    sjt_cast20->_view.m13 = 0.0f;
#line 10
    sjt_cast20->_view.m20 = 0.0f;
#line 11
    sjt_cast20->_view.m21 = 0.0f;
#line 12
    sjt_cast20->_view.m22 = 0.0f;
#line 13
    sjt_cast20->_view.m23 = 0.0f;
#line 14
    sjt_cast20->_view.m30 = 0.0f;
#line 15
    sjt_cast20->_view.m31 = 0.0f;
#line 16
    sjt_cast20->_view.m32 = 0.0f;
#line 17
    sjt_cast20->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast20->_view);
#line 2
    sjt_cast20->_world.m00 = 0.0f;
#line 3
    sjt_cast20->_world.m01 = 0.0f;
#line 4
    sjt_cast20->_world.m02 = 0.0f;
#line 5
    sjt_cast20->_world.m03 = 0.0f;
#line 6
    sjt_cast20->_world.m10 = 0.0f;
#line 7
    sjt_cast20->_world.m11 = 0.0f;
#line 8
    sjt_cast20->_world.m12 = 0.0f;
#line 9
    sjt_cast20->_world.m13 = 0.0f;
#line 10
    sjt_cast20->_world.m20 = 0.0f;
#line 11
    sjt_cast20->_world.m21 = 0.0f;
#line 12
    sjt_cast20->_world.m22 = 0.0f;
#line 13
    sjt_cast20->_world.m23 = 0.0f;
#line 14
    sjt_cast20->_world.m30 = 0.0f;
#line 15
    sjt_cast20->_world.m31 = 0.0f;
#line 16
    sjt_cast20->_world.m32 = 0.0f;
#line 17
    sjt_cast20->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast20->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast20->_light.pos.x = 1.0f;
#line 2
    sjt_cast20->_light.pos.y = 1.0f;
#line 2
    sjt_cast20->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast20->_light.pos);
#line 3
    sjt_cast20->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast20->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast20->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast20->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast20->_light.diffuseColor);
#line 4
    sjt_cast20->_light.specColor.r = 1.0f;
#line 4
    sjt_cast20->_light.specColor.g = 1.0f;
#line 4
    sjt_cast20->_light.specColor.b = 1.0f;
#line 4
    sjt_cast20->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast20->_light.specColor);
#line 4
    sjf_light(&sjt_cast20->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast20->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast20->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast20->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast20->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast20);
#line 1 "lib/ui/model.sj"
    sjt_functionParam315 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast20);
#line 1
    sjf_array_heap_model_initAt(sjt_parent121, sjt_functionParam314, sjt_functionParam315);
#line 35 "nau.sj"
    sjt_parent123 = array7;
#line 35
    sjt_functionParam333 = 3;
#line 35
    sjt_cast21 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast21->_refCount = 1;
#line 69
    sjt_negate24 = 4.3f;
#line 69
    result25 = -sjt_negate24;
#line 69
    sjt_functionParam335 = result25;
#line 69
    sjt_functionParam336 = 4.3f;
#line 69
    sjt_negate25 = 1.0f;
#line 69
    result26 = -sjt_negate25;
#line 69
    sjt_functionParam337 = result26;
#line 69
    sjt_functionParam338 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam339 = 0.0f;
#line 71
    sjt_functionParam340 = 0.0f;
#line 72
    sjt_functionParam341 = 1.0f;
#line 73
    sjt_functionParam342 = 0.0f;
#line 74
    sjt_functionParam343 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam335, sjt_functionParam336, sjt_functionParam337, sjt_functionParam338, sjt_functionParam339, sjt_functionParam340, sjt_functionParam341, sjt_functionParam342, sjt_functionParam343, &sjt_cast21->vertexBuffer);
#line 67 "nau.sj"
    sjt_copy21 = &sjv_phongTextureShader;
#line 67
    sjf_shader_copy(&sjt_cast21->shader, sjt_copy21);
#line 66
    sjt_call59.count = 16;
#line 66
    sjt_call59.data.dataSize = 17;
#line 66
    sjt_call59.data.data = (void*)sjg_string34;
#line 66
    sjt_call59.data._isGlobal = true;
#line 66
    sjt_call59.data.count = 17;
#line 66
    sjf_array_char(&sjt_call59.data);
#line 66
    sjf_string(&sjt_call59);
#line 66
    sjt_functionParam344 = &sjt_call59;
#line 66
    sjf_textureFromPng(sjt_functionParam344, &sjt_cast21->texture);
#line 68
    sjt_functionParam345 = 8.6f;
#line 68
    sjt_functionParam346 = 0.0f;
#line 68
    sjt_functionParam347 = 4.2f;
#line 68
    sjf_mat4_translate(sjt_functionParam345, sjt_functionParam346, sjt_functionParam347, &sjt_call60);
#line 68
    sjt_parent124 = &sjt_call60;
#line 68
    sjt_functionParam349 = 2.0f;
#line 68
    sjt_functionParam350 = 2.0f;
#line 68
    sjt_functionParam351 = 2.0f;
#line 68
    sjf_mat4_scale(sjt_functionParam349, sjt_functionParam350, sjt_functionParam351, &sjt_call61);
#line 68
    sjt_functionParam348 = &sjt_call61;
#line 68
    sjf_mat4_multiply(sjt_parent124, sjt_functionParam348, &sjt_cast21->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast21->center.x = 0.0f;
#line 3
    sjt_cast21->center.y = 0.0f;
#line 4
    sjt_cast21->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast21->center);
#line 70 "nau.sj"
    sjt_cast21->hasAlpha = true;
#line 65
    sjt_cast21->id.count = 8;
#line 65
    sjt_cast21->id.data.dataSize = 9;
#line 65
    sjt_cast21->id.data.data = (void*)sjg_string33;
#line 65
    sjt_cast21->id.data._isGlobal = true;
#line 65
    sjt_cast21->id.data.count = 9;
#line 65
    sjf_array_char(&sjt_cast21->id.data);
#line 65
    sjf_string(&sjt_cast21->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast21->_projection.m00 = 0.0f;
#line 3
    sjt_cast21->_projection.m01 = 0.0f;
#line 4
    sjt_cast21->_projection.m02 = 0.0f;
#line 5
    sjt_cast21->_projection.m03 = 0.0f;
#line 6
    sjt_cast21->_projection.m10 = 0.0f;
#line 7
    sjt_cast21->_projection.m11 = 0.0f;
#line 8
    sjt_cast21->_projection.m12 = 0.0f;
#line 9
    sjt_cast21->_projection.m13 = 0.0f;
#line 10
    sjt_cast21->_projection.m20 = 0.0f;
#line 11
    sjt_cast21->_projection.m21 = 0.0f;
#line 12
    sjt_cast21->_projection.m22 = 0.0f;
#line 13
    sjt_cast21->_projection.m23 = 0.0f;
#line 14
    sjt_cast21->_projection.m30 = 0.0f;
#line 15
    sjt_cast21->_projection.m31 = 0.0f;
#line 16
    sjt_cast21->_projection.m32 = 0.0f;
#line 17
    sjt_cast21->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast21->_projection);
#line 2
    sjt_cast21->_view.m00 = 0.0f;
#line 3
    sjt_cast21->_view.m01 = 0.0f;
#line 4
    sjt_cast21->_view.m02 = 0.0f;
#line 5
    sjt_cast21->_view.m03 = 0.0f;
#line 6
    sjt_cast21->_view.m10 = 0.0f;
#line 7
    sjt_cast21->_view.m11 = 0.0f;
#line 8
    sjt_cast21->_view.m12 = 0.0f;
#line 9
    sjt_cast21->_view.m13 = 0.0f;
#line 10
    sjt_cast21->_view.m20 = 0.0f;
#line 11
    sjt_cast21->_view.m21 = 0.0f;
#line 12
    sjt_cast21->_view.m22 = 0.0f;
#line 13
    sjt_cast21->_view.m23 = 0.0f;
#line 14
    sjt_cast21->_view.m30 = 0.0f;
#line 15
    sjt_cast21->_view.m31 = 0.0f;
#line 16
    sjt_cast21->_view.m32 = 0.0f;
#line 17
    sjt_cast21->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast21->_view);
#line 2
    sjt_cast21->_world.m00 = 0.0f;
#line 3
    sjt_cast21->_world.m01 = 0.0f;
#line 4
    sjt_cast21->_world.m02 = 0.0f;
#line 5
    sjt_cast21->_world.m03 = 0.0f;
#line 6
    sjt_cast21->_world.m10 = 0.0f;
#line 7
    sjt_cast21->_world.m11 = 0.0f;
#line 8
    sjt_cast21->_world.m12 = 0.0f;
#line 9
    sjt_cast21->_world.m13 = 0.0f;
#line 10
    sjt_cast21->_world.m20 = 0.0f;
#line 11
    sjt_cast21->_world.m21 = 0.0f;
#line 12
    sjt_cast21->_world.m22 = 0.0f;
#line 13
    sjt_cast21->_world.m23 = 0.0f;
#line 14
    sjt_cast21->_world.m30 = 0.0f;
#line 15
    sjt_cast21->_world.m31 = 0.0f;
#line 16
    sjt_cast21->_world.m32 = 0.0f;
#line 17
    sjt_cast21->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast21->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast21->_light.pos.x = 1.0f;
#line 2
    sjt_cast21->_light.pos.y = 1.0f;
#line 2
    sjt_cast21->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast21->_light.pos);
#line 3
    sjt_cast21->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast21->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast21->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast21->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast21->_light.diffuseColor);
#line 4
    sjt_cast21->_light.specColor.r = 1.0f;
#line 4
    sjt_cast21->_light.specColor.g = 1.0f;
#line 4
    sjt_cast21->_light.specColor.b = 1.0f;
#line 4
    sjt_cast21->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast21->_light.specColor);
#line 4
    sjf_light(&sjt_cast21->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast21->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast21->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast21->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast21->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast21);
#line 1 "lib/ui/model.sj"
    sjt_functionParam334 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast21);
#line 1
    sjf_array_heap_model_initAt(sjt_parent123, sjt_functionParam333, sjt_functionParam334);
#line 35 "nau.sj"
    sjt_parent125 = array7;
#line 35
    sjt_functionParam352 = 4;
#line 35
    sjt_cast22 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast22->_refCount = 1;
#line 78
    sjt_negate26 = 4.3f;
#line 78
    result27 = -sjt_negate26;
#line 78
    sjt_functionParam354 = result27;
#line 78
    sjt_functionParam355 = 4.3f;
#line 78
    sjt_negate27 = 1.0f;
#line 78
    result28 = -sjt_negate27;
#line 78
    sjt_functionParam356 = result28;
#line 78
    sjt_functionParam357 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam358 = 0.0f;
#line 71
    sjt_functionParam359 = 0.0f;
#line 72
    sjt_functionParam360 = 1.0f;
#line 73
    sjt_functionParam361 = 0.0f;
#line 74
    sjt_functionParam362 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam354, sjt_functionParam355, sjt_functionParam356, sjt_functionParam357, sjt_functionParam358, sjt_functionParam359, sjt_functionParam360, sjt_functionParam361, sjt_functionParam362, &sjt_cast22->vertexBuffer);
#line 76 "nau.sj"
    sjt_copy22 = &sjv_phongTextureShader;
#line 76
    sjf_shader_copy(&sjt_cast22->shader, sjt_copy22);
#line 75
    sjt_call62.count = 16;
#line 75
    sjt_call62.data.dataSize = 17;
#line 75
    sjt_call62.data.data = (void*)sjg_string36;
#line 75
    sjt_call62.data._isGlobal = true;
#line 75
    sjt_call62.data.count = 17;
#line 75
    sjf_array_char(&sjt_call62.data);
#line 75
    sjf_string(&sjt_call62);
#line 75
    sjt_functionParam363 = &sjt_call62;
#line 75
    sjf_textureFromPng(sjt_functionParam363, &sjt_cast22->texture);
#line 77
    sjt_negate28 = 9.6f;
#line 77
    result29 = -sjt_negate28;
#line 77
    sjt_functionParam364 = result29;
#line 77
    sjt_functionParam365 = 0.0f;
#line 77
    sjt_functionParam366 = 2.2f;
#line 77
    sjf_mat4_translate(sjt_functionParam364, sjt_functionParam365, sjt_functionParam366, &sjt_call63);
#line 77
    sjt_parent126 = &sjt_call63;
#line 77
    sjt_functionParam368 = 2.0f;
#line 77
    sjt_functionParam369 = 2.0f;
#line 77
    sjt_functionParam370 = 2.0f;
#line 77
    sjf_mat4_scale(sjt_functionParam368, sjt_functionParam369, sjt_functionParam370, &sjt_call64);
#line 77
    sjt_functionParam367 = &sjt_call64;
#line 77
    sjf_mat4_multiply(sjt_parent126, sjt_functionParam367, &sjt_cast22->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast22->center.x = 0.0f;
#line 3
    sjt_cast22->center.y = 0.0f;
#line 4
    sjt_cast22->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast22->center);
#line 79 "nau.sj"
    sjt_cast22->hasAlpha = true;
#line 74
    sjt_cast22->id.count = 8;
#line 74
    sjt_cast22->id.data.dataSize = 9;
#line 74
    sjt_cast22->id.data.data = (void*)sjg_string35;
#line 74
    sjt_cast22->id.data._isGlobal = true;
#line 74
    sjt_cast22->id.data.count = 9;
#line 74
    sjf_array_char(&sjt_cast22->id.data);
#line 74
    sjf_string(&sjt_cast22->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast22->_projection.m00 = 0.0f;
#line 3
    sjt_cast22->_projection.m01 = 0.0f;
#line 4
    sjt_cast22->_projection.m02 = 0.0f;
#line 5
    sjt_cast22->_projection.m03 = 0.0f;
#line 6
    sjt_cast22->_projection.m10 = 0.0f;
#line 7
    sjt_cast22->_projection.m11 = 0.0f;
#line 8
    sjt_cast22->_projection.m12 = 0.0f;
#line 9
    sjt_cast22->_projection.m13 = 0.0f;
#line 10
    sjt_cast22->_projection.m20 = 0.0f;
#line 11
    sjt_cast22->_projection.m21 = 0.0f;
#line 12
    sjt_cast22->_projection.m22 = 0.0f;
#line 13
    sjt_cast22->_projection.m23 = 0.0f;
#line 14
    sjt_cast22->_projection.m30 = 0.0f;
#line 15
    sjt_cast22->_projection.m31 = 0.0f;
#line 16
    sjt_cast22->_projection.m32 = 0.0f;
#line 17
    sjt_cast22->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast22->_projection);
#line 2
    sjt_cast22->_view.m00 = 0.0f;
#line 3
    sjt_cast22->_view.m01 = 0.0f;
#line 4
    sjt_cast22->_view.m02 = 0.0f;
#line 5
    sjt_cast22->_view.m03 = 0.0f;
#line 6
    sjt_cast22->_view.m10 = 0.0f;
#line 7
    sjt_cast22->_view.m11 = 0.0f;
#line 8
    sjt_cast22->_view.m12 = 0.0f;
#line 9
    sjt_cast22->_view.m13 = 0.0f;
#line 10
    sjt_cast22->_view.m20 = 0.0f;
#line 11
    sjt_cast22->_view.m21 = 0.0f;
#line 12
    sjt_cast22->_view.m22 = 0.0f;
#line 13
    sjt_cast22->_view.m23 = 0.0f;
#line 14
    sjt_cast22->_view.m30 = 0.0f;
#line 15
    sjt_cast22->_view.m31 = 0.0f;
#line 16
    sjt_cast22->_view.m32 = 0.0f;
#line 17
    sjt_cast22->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast22->_view);
#line 2
    sjt_cast22->_world.m00 = 0.0f;
#line 3
    sjt_cast22->_world.m01 = 0.0f;
#line 4
    sjt_cast22->_world.m02 = 0.0f;
#line 5
    sjt_cast22->_world.m03 = 0.0f;
#line 6
    sjt_cast22->_world.m10 = 0.0f;
#line 7
    sjt_cast22->_world.m11 = 0.0f;
#line 8
    sjt_cast22->_world.m12 = 0.0f;
#line 9
    sjt_cast22->_world.m13 = 0.0f;
#line 10
    sjt_cast22->_world.m20 = 0.0f;
#line 11
    sjt_cast22->_world.m21 = 0.0f;
#line 12
    sjt_cast22->_world.m22 = 0.0f;
#line 13
    sjt_cast22->_world.m23 = 0.0f;
#line 14
    sjt_cast22->_world.m30 = 0.0f;
#line 15
    sjt_cast22->_world.m31 = 0.0f;
#line 16
    sjt_cast22->_world.m32 = 0.0f;
#line 17
    sjt_cast22->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast22->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast22->_light.pos.x = 1.0f;
#line 2
    sjt_cast22->_light.pos.y = 1.0f;
#line 2
    sjt_cast22->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast22->_light.pos);
#line 3
    sjt_cast22->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast22->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast22->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast22->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast22->_light.diffuseColor);
#line 4
    sjt_cast22->_light.specColor.r = 1.0f;
#line 4
    sjt_cast22->_light.specColor.g = 1.0f;
#line 4
    sjt_cast22->_light.specColor.b = 1.0f;
#line 4
    sjt_cast22->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast22->_light.specColor);
#line 4
    sjf_light(&sjt_cast22->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast22->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast22->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast22->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast22->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast22);
#line 1 "lib/ui/model.sj"
    sjt_functionParam353 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast22);
#line 1
    sjf_array_heap_model_initAt(sjt_parent125, sjt_functionParam352, sjt_functionParam353);
#line 35 "nau.sj"
    sjt_parent127 = array7;
#line 35
    sjt_functionParam371 = 5;
#line 35
    sjt_cast23 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast23->_refCount = 1;
#line 87
    sjt_negate29 = 4.3f;
#line 87
    result30 = -sjt_negate29;
#line 87
    sjt_functionParam373 = result30;
#line 87
    sjt_functionParam374 = 4.3f;
#line 87
    sjt_negate30 = 1.0f;
#line 87
    result31 = -sjt_negate30;
#line 87
    sjt_functionParam375 = result31;
#line 87
    sjt_functionParam376 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam377 = 0.0f;
#line 71
    sjt_functionParam378 = 0.0f;
#line 72
    sjt_functionParam379 = 1.0f;
#line 73
    sjt_functionParam380 = 0.0f;
#line 74
    sjt_functionParam381 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam373, sjt_functionParam374, sjt_functionParam375, sjt_functionParam376, sjt_functionParam377, sjt_functionParam378, sjt_functionParam379, sjt_functionParam380, sjt_functionParam381, &sjt_cast23->vertexBuffer);
#line 85 "nau.sj"
    sjt_copy23 = &sjv_phongTextureShader;
#line 85
    sjf_shader_copy(&sjt_cast23->shader, sjt_copy23);
#line 84
    sjt_call65.count = 16;
#line 84
    sjt_call65.data.dataSize = 17;
#line 84
    sjt_call65.data.data = (void*)sjg_string38;
#line 84
    sjt_call65.data._isGlobal = true;
#line 84
    sjt_call65.data.count = 17;
#line 84
    sjf_array_char(&sjt_call65.data);
#line 84
    sjf_string(&sjt_call65);
#line 84
    sjt_functionParam382 = &sjt_call65;
#line 84
    sjf_textureFromPng(sjt_functionParam382, &sjt_cast23->texture);
#line 86
    sjt_functionParam383 = 7.6f;
#line 86
    sjt_functionParam384 = 0.0f;
#line 86
    sjt_functionParam385 = 2.2f;
#line 86
    sjf_mat4_translate(sjt_functionParam383, sjt_functionParam384, sjt_functionParam385, &sjt_call66);
#line 86
    sjt_parent128 = &sjt_call66;
#line 86
    sjt_functionParam387 = 2.0f;
#line 86
    sjt_functionParam388 = 2.0f;
#line 86
    sjt_functionParam389 = 2.0f;
#line 86
    sjf_mat4_scale(sjt_functionParam387, sjt_functionParam388, sjt_functionParam389, &sjt_call67);
#line 86
    sjt_functionParam386 = &sjt_call67;
#line 86
    sjf_mat4_multiply(sjt_parent128, sjt_functionParam386, &sjt_cast23->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast23->center.x = 0.0f;
#line 3
    sjt_cast23->center.y = 0.0f;
#line 4
    sjt_cast23->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast23->center);
#line 88 "nau.sj"
    sjt_cast23->hasAlpha = true;
#line 83
    sjt_cast23->id.count = 8;
#line 83
    sjt_cast23->id.data.dataSize = 9;
#line 83
    sjt_cast23->id.data.data = (void*)sjg_string37;
#line 83
    sjt_cast23->id.data._isGlobal = true;
#line 83
    sjt_cast23->id.data.count = 9;
#line 83
    sjf_array_char(&sjt_cast23->id.data);
#line 83
    sjf_string(&sjt_cast23->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast23->_projection.m00 = 0.0f;
#line 3
    sjt_cast23->_projection.m01 = 0.0f;
#line 4
    sjt_cast23->_projection.m02 = 0.0f;
#line 5
    sjt_cast23->_projection.m03 = 0.0f;
#line 6
    sjt_cast23->_projection.m10 = 0.0f;
#line 7
    sjt_cast23->_projection.m11 = 0.0f;
#line 8
    sjt_cast23->_projection.m12 = 0.0f;
#line 9
    sjt_cast23->_projection.m13 = 0.0f;
#line 10
    sjt_cast23->_projection.m20 = 0.0f;
#line 11
    sjt_cast23->_projection.m21 = 0.0f;
#line 12
    sjt_cast23->_projection.m22 = 0.0f;
#line 13
    sjt_cast23->_projection.m23 = 0.0f;
#line 14
    sjt_cast23->_projection.m30 = 0.0f;
#line 15
    sjt_cast23->_projection.m31 = 0.0f;
#line 16
    sjt_cast23->_projection.m32 = 0.0f;
#line 17
    sjt_cast23->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast23->_projection);
#line 2
    sjt_cast23->_view.m00 = 0.0f;
#line 3
    sjt_cast23->_view.m01 = 0.0f;
#line 4
    sjt_cast23->_view.m02 = 0.0f;
#line 5
    sjt_cast23->_view.m03 = 0.0f;
#line 6
    sjt_cast23->_view.m10 = 0.0f;
#line 7
    sjt_cast23->_view.m11 = 0.0f;
#line 8
    sjt_cast23->_view.m12 = 0.0f;
#line 9
    sjt_cast23->_view.m13 = 0.0f;
#line 10
    sjt_cast23->_view.m20 = 0.0f;
#line 11
    sjt_cast23->_view.m21 = 0.0f;
#line 12
    sjt_cast23->_view.m22 = 0.0f;
#line 13
    sjt_cast23->_view.m23 = 0.0f;
#line 14
    sjt_cast23->_view.m30 = 0.0f;
#line 15
    sjt_cast23->_view.m31 = 0.0f;
#line 16
    sjt_cast23->_view.m32 = 0.0f;
#line 17
    sjt_cast23->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast23->_view);
#line 2
    sjt_cast23->_world.m00 = 0.0f;
#line 3
    sjt_cast23->_world.m01 = 0.0f;
#line 4
    sjt_cast23->_world.m02 = 0.0f;
#line 5
    sjt_cast23->_world.m03 = 0.0f;
#line 6
    sjt_cast23->_world.m10 = 0.0f;
#line 7
    sjt_cast23->_world.m11 = 0.0f;
#line 8
    sjt_cast23->_world.m12 = 0.0f;
#line 9
    sjt_cast23->_world.m13 = 0.0f;
#line 10
    sjt_cast23->_world.m20 = 0.0f;
#line 11
    sjt_cast23->_world.m21 = 0.0f;
#line 12
    sjt_cast23->_world.m22 = 0.0f;
#line 13
    sjt_cast23->_world.m23 = 0.0f;
#line 14
    sjt_cast23->_world.m30 = 0.0f;
#line 15
    sjt_cast23->_world.m31 = 0.0f;
#line 16
    sjt_cast23->_world.m32 = 0.0f;
#line 17
    sjt_cast23->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast23->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast23->_light.pos.x = 1.0f;
#line 2
    sjt_cast23->_light.pos.y = 1.0f;
#line 2
    sjt_cast23->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast23->_light.pos);
#line 3
    sjt_cast23->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast23->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast23->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast23->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast23->_light.diffuseColor);
#line 4
    sjt_cast23->_light.specColor.r = 1.0f;
#line 4
    sjt_cast23->_light.specColor.g = 1.0f;
#line 4
    sjt_cast23->_light.specColor.b = 1.0f;
#line 4
    sjt_cast23->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast23->_light.specColor);
#line 4
    sjf_light(&sjt_cast23->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast23->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast23->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast23->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast23->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast23);
#line 1 "lib/ui/model.sj"
    sjt_functionParam372 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast23);
#line 1
    sjf_array_heap_model_initAt(sjt_parent127, sjt_functionParam371, sjt_functionParam372);
#line 35 "nau.sj"
    sjt_parent129 = array7;
#line 35
    sjt_functionParam390 = 6;
#line 35
    sjt_cast24 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast24->_refCount = 1;
#line 96
    sjt_negate31 = 4.3f;
#line 96
    result32 = -sjt_negate31;
#line 96
    sjt_functionParam392 = result32;
#line 96
    sjt_functionParam393 = 4.3f;
#line 96
    sjt_negate32 = 1.0f;
#line 96
    result33 = -sjt_negate32;
#line 96
    sjt_functionParam394 = result33;
#line 96
    sjt_functionParam395 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam396 = 0.0f;
#line 71
    sjt_functionParam397 = 0.0f;
#line 72
    sjt_functionParam398 = 1.0f;
#line 73
    sjt_functionParam399 = 0.0f;
#line 74
    sjt_functionParam400 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam392, sjt_functionParam393, sjt_functionParam394, sjt_functionParam395, sjt_functionParam396, sjt_functionParam397, sjt_functionParam398, sjt_functionParam399, sjt_functionParam400, &sjt_cast24->vertexBuffer);
#line 94 "nau.sj"
    sjt_copy24 = &sjv_phongTextureShader;
#line 94
    sjf_shader_copy(&sjt_cast24->shader, sjt_copy24);
#line 93
    sjt_call68.count = 16;
#line 93
    sjt_call68.data.dataSize = 17;
#line 93
    sjt_call68.data.data = (void*)sjg_string40;
#line 93
    sjt_call68.data._isGlobal = true;
#line 93
    sjt_call68.data.count = 17;
#line 93
    sjf_array_char(&sjt_call68.data);
#line 93
    sjf_string(&sjt_call68);
#line 93
    sjt_functionParam401 = &sjt_call68;
#line 93
    sjf_textureFromPng(sjt_functionParam401, &sjt_cast24->texture);
#line 95
    sjt_negate33 = 10.6f;
#line 95
    result34 = -sjt_negate33;
#line 95
    sjt_functionParam402 = result34;
#line 95
    sjt_functionParam403 = 0.0f;
#line 95
    sjt_functionParam404 = 0.2f;
#line 95
    sjf_mat4_translate(sjt_functionParam402, sjt_functionParam403, sjt_functionParam404, &sjt_call69);
#line 95
    sjt_parent130 = &sjt_call69;
#line 95
    sjt_functionParam406 = 2.0f;
#line 95
    sjt_functionParam407 = 2.0f;
#line 95
    sjt_functionParam408 = 2.0f;
#line 95
    sjf_mat4_scale(sjt_functionParam406, sjt_functionParam407, sjt_functionParam408, &sjt_call70);
#line 95
    sjt_functionParam405 = &sjt_call70;
#line 95
    sjf_mat4_multiply(sjt_parent130, sjt_functionParam405, &sjt_cast24->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast24->center.x = 0.0f;
#line 3
    sjt_cast24->center.y = 0.0f;
#line 4
    sjt_cast24->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast24->center);
#line 97 "nau.sj"
    sjt_cast24->hasAlpha = true;
#line 92
    sjt_cast24->id.count = 8;
#line 92
    sjt_cast24->id.data.dataSize = 9;
#line 92
    sjt_cast24->id.data.data = (void*)sjg_string39;
#line 92
    sjt_cast24->id.data._isGlobal = true;
#line 92
    sjt_cast24->id.data.count = 9;
#line 92
    sjf_array_char(&sjt_cast24->id.data);
#line 92
    sjf_string(&sjt_cast24->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast24->_projection.m00 = 0.0f;
#line 3
    sjt_cast24->_projection.m01 = 0.0f;
#line 4
    sjt_cast24->_projection.m02 = 0.0f;
#line 5
    sjt_cast24->_projection.m03 = 0.0f;
#line 6
    sjt_cast24->_projection.m10 = 0.0f;
#line 7
    sjt_cast24->_projection.m11 = 0.0f;
#line 8
    sjt_cast24->_projection.m12 = 0.0f;
#line 9
    sjt_cast24->_projection.m13 = 0.0f;
#line 10
    sjt_cast24->_projection.m20 = 0.0f;
#line 11
    sjt_cast24->_projection.m21 = 0.0f;
#line 12
    sjt_cast24->_projection.m22 = 0.0f;
#line 13
    sjt_cast24->_projection.m23 = 0.0f;
#line 14
    sjt_cast24->_projection.m30 = 0.0f;
#line 15
    sjt_cast24->_projection.m31 = 0.0f;
#line 16
    sjt_cast24->_projection.m32 = 0.0f;
#line 17
    sjt_cast24->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast24->_projection);
#line 2
    sjt_cast24->_view.m00 = 0.0f;
#line 3
    sjt_cast24->_view.m01 = 0.0f;
#line 4
    sjt_cast24->_view.m02 = 0.0f;
#line 5
    sjt_cast24->_view.m03 = 0.0f;
#line 6
    sjt_cast24->_view.m10 = 0.0f;
#line 7
    sjt_cast24->_view.m11 = 0.0f;
#line 8
    sjt_cast24->_view.m12 = 0.0f;
#line 9
    sjt_cast24->_view.m13 = 0.0f;
#line 10
    sjt_cast24->_view.m20 = 0.0f;
#line 11
    sjt_cast24->_view.m21 = 0.0f;
#line 12
    sjt_cast24->_view.m22 = 0.0f;
#line 13
    sjt_cast24->_view.m23 = 0.0f;
#line 14
    sjt_cast24->_view.m30 = 0.0f;
#line 15
    sjt_cast24->_view.m31 = 0.0f;
#line 16
    sjt_cast24->_view.m32 = 0.0f;
#line 17
    sjt_cast24->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast24->_view);
#line 2
    sjt_cast24->_world.m00 = 0.0f;
#line 3
    sjt_cast24->_world.m01 = 0.0f;
#line 4
    sjt_cast24->_world.m02 = 0.0f;
#line 5
    sjt_cast24->_world.m03 = 0.0f;
#line 6
    sjt_cast24->_world.m10 = 0.0f;
#line 7
    sjt_cast24->_world.m11 = 0.0f;
#line 8
    sjt_cast24->_world.m12 = 0.0f;
#line 9
    sjt_cast24->_world.m13 = 0.0f;
#line 10
    sjt_cast24->_world.m20 = 0.0f;
#line 11
    sjt_cast24->_world.m21 = 0.0f;
#line 12
    sjt_cast24->_world.m22 = 0.0f;
#line 13
    sjt_cast24->_world.m23 = 0.0f;
#line 14
    sjt_cast24->_world.m30 = 0.0f;
#line 15
    sjt_cast24->_world.m31 = 0.0f;
#line 16
    sjt_cast24->_world.m32 = 0.0f;
#line 17
    sjt_cast24->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast24->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast24->_light.pos.x = 1.0f;
#line 2
    sjt_cast24->_light.pos.y = 1.0f;
#line 2
    sjt_cast24->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast24->_light.pos);
#line 3
    sjt_cast24->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast24->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast24->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast24->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast24->_light.diffuseColor);
#line 4
    sjt_cast24->_light.specColor.r = 1.0f;
#line 4
    sjt_cast24->_light.specColor.g = 1.0f;
#line 4
    sjt_cast24->_light.specColor.b = 1.0f;
#line 4
    sjt_cast24->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast24->_light.specColor);
#line 4
    sjf_light(&sjt_cast24->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast24->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast24->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast24->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast24->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast24);
#line 1 "lib/ui/model.sj"
    sjt_functionParam391 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast24);
#line 1
    sjf_array_heap_model_initAt(sjt_parent129, sjt_functionParam390, sjt_functionParam391);
#line 35 "nau.sj"
    sjt_parent131 = array7;
#line 35
    sjt_functionParam409 = 7;
#line 35
    sjt_cast25 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast25->_refCount = 1;
#line 105
    sjt_negate34 = 4.3f;
#line 105
    result35 = -sjt_negate34;
#line 105
    sjt_functionParam411 = result35;
#line 105
    sjt_functionParam412 = 4.3f;
#line 105
    sjt_negate35 = 1.0f;
#line 105
    result36 = -sjt_negate35;
#line 105
    sjt_functionParam413 = result36;
#line 105
    sjt_functionParam414 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam415 = 0.0f;
#line 71
    sjt_functionParam416 = 0.0f;
#line 72
    sjt_functionParam417 = 1.0f;
#line 73
    sjt_functionParam418 = 0.0f;
#line 74
    sjt_functionParam419 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam411, sjt_functionParam412, sjt_functionParam413, sjt_functionParam414, sjt_functionParam415, sjt_functionParam416, sjt_functionParam417, sjt_functionParam418, sjt_functionParam419, &sjt_cast25->vertexBuffer);
#line 103 "nau.sj"
    sjt_copy25 = &sjv_phongTextureShader;
#line 103
    sjf_shader_copy(&sjt_cast25->shader, sjt_copy25);
#line 102
    sjt_call71.count = 16;
#line 102
    sjt_call71.data.dataSize = 17;
#line 102
    sjt_call71.data.data = (void*)sjg_string42;
#line 102
    sjt_call71.data._isGlobal = true;
#line 102
    sjt_call71.data.count = 17;
#line 102
    sjf_array_char(&sjt_call71.data);
#line 102
    sjf_string(&sjt_call71);
#line 102
    sjt_functionParam420 = &sjt_call71;
#line 102
    sjf_textureFromPng(sjt_functionParam420, &sjt_cast25->texture);
#line 104
    sjt_functionParam421 = 6.6f;
#line 104
    sjt_functionParam422 = 0.0f;
#line 104
    sjt_functionParam423 = 0.2f;
#line 104
    sjf_mat4_translate(sjt_functionParam421, sjt_functionParam422, sjt_functionParam423, &sjt_call72);
#line 104
    sjt_parent132 = &sjt_call72;
#line 104
    sjt_functionParam425 = 2.0f;
#line 104
    sjt_functionParam426 = 2.0f;
#line 104
    sjt_functionParam427 = 2.0f;
#line 104
    sjf_mat4_scale(sjt_functionParam425, sjt_functionParam426, sjt_functionParam427, &sjt_call73);
#line 104
    sjt_functionParam424 = &sjt_call73;
#line 104
    sjf_mat4_multiply(sjt_parent132, sjt_functionParam424, &sjt_cast25->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast25->center.x = 0.0f;
#line 3
    sjt_cast25->center.y = 0.0f;
#line 4
    sjt_cast25->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast25->center);
#line 106 "nau.sj"
    sjt_cast25->hasAlpha = true;
#line 101
    sjt_cast25->id.count = 8;
#line 101
    sjt_cast25->id.data.dataSize = 9;
#line 101
    sjt_cast25->id.data.data = (void*)sjg_string41;
#line 101
    sjt_cast25->id.data._isGlobal = true;
#line 101
    sjt_cast25->id.data.count = 9;
#line 101
    sjf_array_char(&sjt_cast25->id.data);
#line 101
    sjf_string(&sjt_cast25->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast25->_projection.m00 = 0.0f;
#line 3
    sjt_cast25->_projection.m01 = 0.0f;
#line 4
    sjt_cast25->_projection.m02 = 0.0f;
#line 5
    sjt_cast25->_projection.m03 = 0.0f;
#line 6
    sjt_cast25->_projection.m10 = 0.0f;
#line 7
    sjt_cast25->_projection.m11 = 0.0f;
#line 8
    sjt_cast25->_projection.m12 = 0.0f;
#line 9
    sjt_cast25->_projection.m13 = 0.0f;
#line 10
    sjt_cast25->_projection.m20 = 0.0f;
#line 11
    sjt_cast25->_projection.m21 = 0.0f;
#line 12
    sjt_cast25->_projection.m22 = 0.0f;
#line 13
    sjt_cast25->_projection.m23 = 0.0f;
#line 14
    sjt_cast25->_projection.m30 = 0.0f;
#line 15
    sjt_cast25->_projection.m31 = 0.0f;
#line 16
    sjt_cast25->_projection.m32 = 0.0f;
#line 17
    sjt_cast25->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast25->_projection);
#line 2
    sjt_cast25->_view.m00 = 0.0f;
#line 3
    sjt_cast25->_view.m01 = 0.0f;
#line 4
    sjt_cast25->_view.m02 = 0.0f;
#line 5
    sjt_cast25->_view.m03 = 0.0f;
#line 6
    sjt_cast25->_view.m10 = 0.0f;
#line 7
    sjt_cast25->_view.m11 = 0.0f;
#line 8
    sjt_cast25->_view.m12 = 0.0f;
#line 9
    sjt_cast25->_view.m13 = 0.0f;
#line 10
    sjt_cast25->_view.m20 = 0.0f;
#line 11
    sjt_cast25->_view.m21 = 0.0f;
#line 12
    sjt_cast25->_view.m22 = 0.0f;
#line 13
    sjt_cast25->_view.m23 = 0.0f;
#line 14
    sjt_cast25->_view.m30 = 0.0f;
#line 15
    sjt_cast25->_view.m31 = 0.0f;
#line 16
    sjt_cast25->_view.m32 = 0.0f;
#line 17
    sjt_cast25->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast25->_view);
#line 2
    sjt_cast25->_world.m00 = 0.0f;
#line 3
    sjt_cast25->_world.m01 = 0.0f;
#line 4
    sjt_cast25->_world.m02 = 0.0f;
#line 5
    sjt_cast25->_world.m03 = 0.0f;
#line 6
    sjt_cast25->_world.m10 = 0.0f;
#line 7
    sjt_cast25->_world.m11 = 0.0f;
#line 8
    sjt_cast25->_world.m12 = 0.0f;
#line 9
    sjt_cast25->_world.m13 = 0.0f;
#line 10
    sjt_cast25->_world.m20 = 0.0f;
#line 11
    sjt_cast25->_world.m21 = 0.0f;
#line 12
    sjt_cast25->_world.m22 = 0.0f;
#line 13
    sjt_cast25->_world.m23 = 0.0f;
#line 14
    sjt_cast25->_world.m30 = 0.0f;
#line 15
    sjt_cast25->_world.m31 = 0.0f;
#line 16
    sjt_cast25->_world.m32 = 0.0f;
#line 17
    sjt_cast25->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast25->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast25->_light.pos.x = 1.0f;
#line 2
    sjt_cast25->_light.pos.y = 1.0f;
#line 2
    sjt_cast25->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast25->_light.pos);
#line 3
    sjt_cast25->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast25->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast25->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast25->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast25->_light.diffuseColor);
#line 4
    sjt_cast25->_light.specColor.r = 1.0f;
#line 4
    sjt_cast25->_light.specColor.g = 1.0f;
#line 4
    sjt_cast25->_light.specColor.b = 1.0f;
#line 4
    sjt_cast25->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast25->_light.specColor);
#line 4
    sjf_light(&sjt_cast25->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast25->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast25->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast25->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast25->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast25);
#line 1 "lib/ui/model.sj"
    sjt_functionParam410 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast25);
#line 1
    sjf_array_heap_model_initAt(sjt_parent131, sjt_functionParam409, sjt_functionParam410);
#line 35 "nau.sj"
    sjt_parent133 = array7;
#line 35
    sjt_functionParam428 = 8;
#line 35
    sjt_cast26 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast26->_refCount = 1;
#line 114
    sjt_negate36 = 4.3f;
#line 114
    result37 = -sjt_negate36;
#line 114
    sjt_functionParam430 = result37;
#line 114
    sjt_functionParam431 = 4.3f;
#line 114
    sjt_negate37 = 1.0f;
#line 114
    result38 = -sjt_negate37;
#line 114
    sjt_functionParam432 = result38;
#line 114
    sjt_functionParam433 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam434 = 0.0f;
#line 71
    sjt_functionParam435 = 0.0f;
#line 72
    sjt_functionParam436 = 1.0f;
#line 73
    sjt_functionParam437 = 0.0f;
#line 74
    sjt_functionParam438 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam430, sjt_functionParam431, sjt_functionParam432, sjt_functionParam433, sjt_functionParam434, sjt_functionParam435, sjt_functionParam436, sjt_functionParam437, sjt_functionParam438, &sjt_cast26->vertexBuffer);
#line 112 "nau.sj"
    sjt_copy26 = &sjv_phongTextureShader;
#line 112
    sjf_shader_copy(&sjt_cast26->shader, sjt_copy26);
#line 111
    sjt_call74.count = 16;
#line 111
    sjt_call74.data.dataSize = 17;
#line 111
    sjt_call74.data.data = (void*)sjg_string44;
#line 111
    sjt_call74.data._isGlobal = true;
#line 111
    sjt_call74.data.count = 17;
#line 111
    sjf_array_char(&sjt_call74.data);
#line 111
    sjf_string(&sjt_call74);
#line 111
    sjt_functionParam439 = &sjt_call74;
#line 111
    sjf_textureFromPng(sjt_functionParam439, &sjt_cast26->texture);
#line 113
    sjt_negate38 = 8.6f;
#line 113
    result39 = -sjt_negate38;
#line 113
    sjt_functionParam440 = result39;
#line 113
    sjt_functionParam441 = 0.0f;
#line 113
    sjt_negate39 = 1.8f;
#line 113
    result40 = -sjt_negate39;
#line 113
    sjt_functionParam442 = result40;
#line 113
    sjf_mat4_translate(sjt_functionParam440, sjt_functionParam441, sjt_functionParam442, &sjt_call75);
#line 113
    sjt_parent134 = &sjt_call75;
#line 113
    sjt_functionParam444 = 2.0f;
#line 113
    sjt_functionParam445 = 2.0f;
#line 113
    sjt_functionParam446 = 2.0f;
#line 113
    sjf_mat4_scale(sjt_functionParam444, sjt_functionParam445, sjt_functionParam446, &sjt_call76);
#line 113
    sjt_functionParam443 = &sjt_call76;
#line 113
    sjf_mat4_multiply(sjt_parent134, sjt_functionParam443, &sjt_cast26->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast26->center.x = 0.0f;
#line 3
    sjt_cast26->center.y = 0.0f;
#line 4
    sjt_cast26->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast26->center);
#line 115 "nau.sj"
    sjt_cast26->hasAlpha = true;
#line 110
    sjt_cast26->id.count = 9;
#line 110
    sjt_cast26->id.data.dataSize = 10;
#line 110
    sjt_cast26->id.data.data = (void*)sjg_string43;
#line 110
    sjt_cast26->id.data._isGlobal = true;
#line 110
    sjt_cast26->id.data.count = 10;
#line 110
    sjf_array_char(&sjt_cast26->id.data);
#line 110
    sjf_string(&sjt_cast26->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast26->_projection.m00 = 0.0f;
#line 3
    sjt_cast26->_projection.m01 = 0.0f;
#line 4
    sjt_cast26->_projection.m02 = 0.0f;
#line 5
    sjt_cast26->_projection.m03 = 0.0f;
#line 6
    sjt_cast26->_projection.m10 = 0.0f;
#line 7
    sjt_cast26->_projection.m11 = 0.0f;
#line 8
    sjt_cast26->_projection.m12 = 0.0f;
#line 9
    sjt_cast26->_projection.m13 = 0.0f;
#line 10
    sjt_cast26->_projection.m20 = 0.0f;
#line 11
    sjt_cast26->_projection.m21 = 0.0f;
#line 12
    sjt_cast26->_projection.m22 = 0.0f;
#line 13
    sjt_cast26->_projection.m23 = 0.0f;
#line 14
    sjt_cast26->_projection.m30 = 0.0f;
#line 15
    sjt_cast26->_projection.m31 = 0.0f;
#line 16
    sjt_cast26->_projection.m32 = 0.0f;
#line 17
    sjt_cast26->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast26->_projection);
#line 2
    sjt_cast26->_view.m00 = 0.0f;
#line 3
    sjt_cast26->_view.m01 = 0.0f;
#line 4
    sjt_cast26->_view.m02 = 0.0f;
#line 5
    sjt_cast26->_view.m03 = 0.0f;
#line 6
    sjt_cast26->_view.m10 = 0.0f;
#line 7
    sjt_cast26->_view.m11 = 0.0f;
#line 8
    sjt_cast26->_view.m12 = 0.0f;
#line 9
    sjt_cast26->_view.m13 = 0.0f;
#line 10
    sjt_cast26->_view.m20 = 0.0f;
#line 11
    sjt_cast26->_view.m21 = 0.0f;
#line 12
    sjt_cast26->_view.m22 = 0.0f;
#line 13
    sjt_cast26->_view.m23 = 0.0f;
#line 14
    sjt_cast26->_view.m30 = 0.0f;
#line 15
    sjt_cast26->_view.m31 = 0.0f;
#line 16
    sjt_cast26->_view.m32 = 0.0f;
#line 17
    sjt_cast26->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast26->_view);
#line 2
    sjt_cast26->_world.m00 = 0.0f;
#line 3
    sjt_cast26->_world.m01 = 0.0f;
#line 4
    sjt_cast26->_world.m02 = 0.0f;
#line 5
    sjt_cast26->_world.m03 = 0.0f;
#line 6
    sjt_cast26->_world.m10 = 0.0f;
#line 7
    sjt_cast26->_world.m11 = 0.0f;
#line 8
    sjt_cast26->_world.m12 = 0.0f;
#line 9
    sjt_cast26->_world.m13 = 0.0f;
#line 10
    sjt_cast26->_world.m20 = 0.0f;
#line 11
    sjt_cast26->_world.m21 = 0.0f;
#line 12
    sjt_cast26->_world.m22 = 0.0f;
#line 13
    sjt_cast26->_world.m23 = 0.0f;
#line 14
    sjt_cast26->_world.m30 = 0.0f;
#line 15
    sjt_cast26->_world.m31 = 0.0f;
#line 16
    sjt_cast26->_world.m32 = 0.0f;
#line 17
    sjt_cast26->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast26->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast26->_light.pos.x = 1.0f;
#line 2
    sjt_cast26->_light.pos.y = 1.0f;
#line 2
    sjt_cast26->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast26->_light.pos);
#line 3
    sjt_cast26->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast26->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast26->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast26->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast26->_light.diffuseColor);
#line 4
    sjt_cast26->_light.specColor.r = 1.0f;
#line 4
    sjt_cast26->_light.specColor.g = 1.0f;
#line 4
    sjt_cast26->_light.specColor.b = 1.0f;
#line 4
    sjt_cast26->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast26->_light.specColor);
#line 4
    sjf_light(&sjt_cast26->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast26->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast26->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast26->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast26->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast26);
#line 1 "lib/ui/model.sj"
    sjt_functionParam429 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast26);
#line 1
    sjf_array_heap_model_initAt(sjt_parent133, sjt_functionParam428, sjt_functionParam429);
#line 35 "nau.sj"
    sjt_parent135 = array7;
#line 35
    sjt_functionParam447 = 9;
#line 35
    sjt_cast27 = (sjs_model_heap*)malloc(sizeof(sjs_model_heap));
#line 35
    sjt_cast27->_refCount = 1;
#line 123
    sjt_negate40 = 4.3f;
#line 123
    result41 = -sjt_negate40;
#line 123
    sjt_functionParam449 = result41;
#line 123
    sjt_functionParam450 = 4.3f;
#line 123
    sjt_negate41 = 1.0f;
#line 123
    result42 = -sjt_negate41;
#line 123
    sjt_functionParam451 = result42;
#line 123
    sjt_functionParam452 = 1.0f;
#line 70 "lib/ui/vertexBufferBuilders.sj"
    sjt_functionParam453 = 0.0f;
#line 71
    sjt_functionParam454 = 0.0f;
#line 72
    sjt_functionParam455 = 1.0f;
#line 73
    sjt_functionParam456 = 0.0f;
#line 74
    sjt_functionParam457 = 1.0f;
#line 74
    sjf_planeVertexBuffer(sjt_functionParam449, sjt_functionParam450, sjt_functionParam451, sjt_functionParam452, sjt_functionParam453, sjt_functionParam454, sjt_functionParam455, sjt_functionParam456, sjt_functionParam457, &sjt_cast27->vertexBuffer);
#line 121 "nau.sj"
    sjt_copy27 = &sjv_phongTextureShader;
#line 121
    sjf_shader_copy(&sjt_cast27->shader, sjt_copy27);
#line 120
    sjt_call77.count = 16;
#line 120
    sjt_call77.data.dataSize = 17;
#line 120
    sjt_call77.data.data = (void*)sjg_string46;
#line 120
    sjt_call77.data._isGlobal = true;
#line 120
    sjt_call77.data.count = 17;
#line 120
    sjf_array_char(&sjt_call77.data);
#line 120
    sjf_string(&sjt_call77);
#line 120
    sjt_functionParam458 = &sjt_call77;
#line 120
    sjf_textureFromPng(sjt_functionParam458, &sjt_cast27->texture);
#line 122
    sjt_functionParam459 = 8.6f;
#line 122
    sjt_functionParam460 = 0.0f;
#line 122
    sjt_negate42 = 1.8f;
#line 122
    result43 = -sjt_negate42;
#line 122
    sjt_functionParam461 = result43;
#line 122
    sjf_mat4_translate(sjt_functionParam459, sjt_functionParam460, sjt_functionParam461, &sjt_call78);
#line 122
    sjt_parent136 = &sjt_call78;
#line 122
    sjt_functionParam463 = 2.0f;
#line 122
    sjt_functionParam464 = 2.0f;
#line 122
    sjt_functionParam465 = 2.0f;
#line 122
    sjf_mat4_scale(sjt_functionParam463, sjt_functionParam464, sjt_functionParam465, &sjt_call79);
#line 122
    sjt_functionParam462 = &sjt_call79;
#line 122
    sjf_mat4_multiply(sjt_parent136, sjt_functionParam462, &sjt_cast27->model);
#line 2 "lib/ui/vec3.sj"
    sjt_cast27->center.x = 0.0f;
#line 3
    sjt_cast27->center.y = 0.0f;
#line 4
    sjt_cast27->center.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast27->center);
#line 124 "nau.sj"
    sjt_cast27->hasAlpha = true;
#line 119
    sjt_cast27->id.count = 9;
#line 119
    sjt_cast27->id.data.dataSize = 10;
#line 119
    sjt_cast27->id.data.data = (void*)sjg_string45;
#line 119
    sjt_cast27->id.data._isGlobal = true;
#line 119
    sjt_cast27->id.data.count = 10;
#line 119
    sjf_array_char(&sjt_cast27->id.data);
#line 119
    sjf_string(&sjt_cast27->id);
#line 2 "lib/ui/mat4.sj"
    sjt_cast27->_projection.m00 = 0.0f;
#line 3
    sjt_cast27->_projection.m01 = 0.0f;
#line 4
    sjt_cast27->_projection.m02 = 0.0f;
#line 5
    sjt_cast27->_projection.m03 = 0.0f;
#line 6
    sjt_cast27->_projection.m10 = 0.0f;
#line 7
    sjt_cast27->_projection.m11 = 0.0f;
#line 8
    sjt_cast27->_projection.m12 = 0.0f;
#line 9
    sjt_cast27->_projection.m13 = 0.0f;
#line 10
    sjt_cast27->_projection.m20 = 0.0f;
#line 11
    sjt_cast27->_projection.m21 = 0.0f;
#line 12
    sjt_cast27->_projection.m22 = 0.0f;
#line 13
    sjt_cast27->_projection.m23 = 0.0f;
#line 14
    sjt_cast27->_projection.m30 = 0.0f;
#line 15
    sjt_cast27->_projection.m31 = 0.0f;
#line 16
    sjt_cast27->_projection.m32 = 0.0f;
#line 17
    sjt_cast27->_projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast27->_projection);
#line 2
    sjt_cast27->_view.m00 = 0.0f;
#line 3
    sjt_cast27->_view.m01 = 0.0f;
#line 4
    sjt_cast27->_view.m02 = 0.0f;
#line 5
    sjt_cast27->_view.m03 = 0.0f;
#line 6
    sjt_cast27->_view.m10 = 0.0f;
#line 7
    sjt_cast27->_view.m11 = 0.0f;
#line 8
    sjt_cast27->_view.m12 = 0.0f;
#line 9
    sjt_cast27->_view.m13 = 0.0f;
#line 10
    sjt_cast27->_view.m20 = 0.0f;
#line 11
    sjt_cast27->_view.m21 = 0.0f;
#line 12
    sjt_cast27->_view.m22 = 0.0f;
#line 13
    sjt_cast27->_view.m23 = 0.0f;
#line 14
    sjt_cast27->_view.m30 = 0.0f;
#line 15
    sjt_cast27->_view.m31 = 0.0f;
#line 16
    sjt_cast27->_view.m32 = 0.0f;
#line 17
    sjt_cast27->_view.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast27->_view);
#line 2
    sjt_cast27->_world.m00 = 0.0f;
#line 3
    sjt_cast27->_world.m01 = 0.0f;
#line 4
    sjt_cast27->_world.m02 = 0.0f;
#line 5
    sjt_cast27->_world.m03 = 0.0f;
#line 6
    sjt_cast27->_world.m10 = 0.0f;
#line 7
    sjt_cast27->_world.m11 = 0.0f;
#line 8
    sjt_cast27->_world.m12 = 0.0f;
#line 9
    sjt_cast27->_world.m13 = 0.0f;
#line 10
    sjt_cast27->_world.m20 = 0.0f;
#line 11
    sjt_cast27->_world.m21 = 0.0f;
#line 12
    sjt_cast27->_world.m22 = 0.0f;
#line 13
    sjt_cast27->_world.m23 = 0.0f;
#line 14
    sjt_cast27->_world.m30 = 0.0f;
#line 15
    sjt_cast27->_world.m31 = 0.0f;
#line 16
    sjt_cast27->_world.m32 = 0.0f;
#line 17
    sjt_cast27->_world.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast27->_world);
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast27->_light.pos.x = 1.0f;
#line 2
    sjt_cast27->_light.pos.y = 1.0f;
#line 2
    sjt_cast27->_light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast27->_light.pos);
#line 3
    sjt_cast27->_light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast27->_light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast27->_light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast27->_light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast27->_light.diffuseColor);
#line 4
    sjt_cast27->_light.specColor.r = 1.0f;
#line 4
    sjt_cast27->_light.specColor.g = 1.0f;
#line 4
    sjt_cast27->_light.specColor.b = 1.0f;
#line 4
    sjt_cast27->_light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast27->_light.specColor);
#line 4
    sjf_light(&sjt_cast27->_light);
#line 2 "lib/ui/vec3.sj"
    sjt_cast27->_projectedCenter.x = 0.0f;
#line 3
    sjt_cast27->_projectedCenter.y = 0.0f;
#line 4
    sjt_cast27->_projectedCenter.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast27->_projectedCenter);
#line 4
    sjf_model_heap(sjt_cast27);
#line 1 "lib/ui/model.sj"
    sjt_functionParam448 = (sji_nauScene3dElement_model*)sjf_model_heap_as_sji_nauScene3dElement_model(sjt_cast27);
#line 1
    sjf_array_heap_model_initAt(sjt_parent135, sjt_functionParam447, sjt_functionParam448);
#line 1
    sjf_panel3d_heap(sjt_cast17);
#line 1
    sjt_functionParam268 = (sji_nauScene3dElement_model*)sjf_panel3d_heap_as_sji_nauScene3dElement_model(sjt_cast17);
#line 1
    sjf_array_heap_model_initAt(sjt_parent109, sjt_functionParam267, sjt_functionParam268);
#line 9 "nau.sj"
    sjt_negate43 = 16.0f;
#line 9
    result44 = -sjt_negate43;
#line 9
    sjt_cast2->lookAtMin.x = result44;
#line 9
    sjt_negate44 = 1.0f;
#line 9
    result45 = -sjt_negate44;
#line 9
    sjt_cast2->lookAtMin.y = result45;
#line 9
    sjt_cast2->lookAtMin.z = 0.0f;
#line 9
    sjf_vec3(&sjt_cast2->lookAtMin);
#line 10
    sjt_cast2->lookAtMax.x = 16.0f;
#line 10
    sjt_cast2->lookAtMax.y = 1.0f;
#line 10
    sjt_cast2->lookAtMax.z = 6.0f;
#line 10
    sjf_vec3(&sjt_cast2->lookAtMax);
#line 5 "nau/nauScene3dElement.sj"
    sjt_cast2->fieldOfView = 90.0f;
#line 6
    sjt_cast2->zNear = 1.0f;
#line 7
    sjt_cast2->zFar = 20.0f;
#line 2 "lib/ui/scene3dElement.sj"
    sjt_cast2->light.pos.x = 1.0f;
#line 2
    sjt_cast2->light.pos.y = 1.0f;
#line 2
    sjt_cast2->light.pos.z = 1.0f;
#line 2
    sjf_vec3(&sjt_cast2->light.pos);
#line 3
    sjt_cast2->light.diffuseColor.r = 0.5f;
#line 3
    sjt_cast2->light.diffuseColor.g = 0.5f;
#line 3
    sjt_cast2->light.diffuseColor.b = 0.0f;
#line 3
    sjt_cast2->light.diffuseColor.a = 1.0f;
#line 3
    sjf_color(&sjt_cast2->light.diffuseColor);
#line 4
    sjt_cast2->light.specColor.r = 1.0f;
#line 4
    sjt_cast2->light.specColor.g = 1.0f;
#line 4
    sjt_cast2->light.specColor.b = 1.0f;
#line 4
    sjt_cast2->light.specColor.a = 1.0f;
#line 4
    sjf_color(&sjt_cast2->light.specColor);
#line 4
    sjf_light(&sjt_cast2->light);
#line 2 "lib/ui/mat4.sj"
    sjt_cast2->projection.m00 = 0.0f;
#line 3
    sjt_cast2->projection.m01 = 0.0f;
#line 4
    sjt_cast2->projection.m02 = 0.0f;
#line 5
    sjt_cast2->projection.m03 = 0.0f;
#line 6
    sjt_cast2->projection.m10 = 0.0f;
#line 7
    sjt_cast2->projection.m11 = 0.0f;
#line 8
    sjt_cast2->projection.m12 = 0.0f;
#line 9
    sjt_cast2->projection.m13 = 0.0f;
#line 10
    sjt_cast2->projection.m20 = 0.0f;
#line 11
    sjt_cast2->projection.m21 = 0.0f;
#line 12
    sjt_cast2->projection.m22 = 0.0f;
#line 13
    sjt_cast2->projection.m23 = 0.0f;
#line 14
    sjt_cast2->projection.m30 = 0.0f;
#line 15
    sjt_cast2->projection.m31 = 0.0f;
#line 16
    sjt_cast2->projection.m32 = 0.0f;
#line 17
    sjt_cast2->projection.m33 = 0.0f;
#line 17
    sjf_mat4(&sjt_cast2->projection);
#line 10 "nau/nauScene3dElement.sj"
    sjt_call80.x = 0.0f;
#line 10
    sjt_call80.y = 0.0f;
#line 10
    sjt_negate45 = 5.0f;
#line 10
    result46 = -sjt_negate45;
#line 10
    sjt_call80.z = result46;
#line 10
    sjf_vec3(&sjt_call80);
#line 10
    sjt_functionParam466 = &sjt_call80;
#line 10
    sjt_call81.x = 0.0f;
#line 10
    sjt_call81.y = 0.0f;
#line 10
    sjt_call81.z = 0.0f;
#line 10
    sjf_vec3(&sjt_call81);
#line 10
    sjt_functionParam467 = &sjt_call81;
#line 10
    sjt_call82.x = 0.0f;
#line 10
    sjt_call82.y = 1.0f;
#line 10
    sjt_call82.z = 0.0f;
#line 10
    sjf_vec3(&sjt_call82);
#line 10
    sjt_functionParam468 = &sjt_call82;
#line 10
    sjf_mat4_lookAtLH(sjt_functionParam466, sjt_functionParam467, sjt_functionParam468, &sjt_cast2->view);
#line 10
    sjf_mat4_identity(&sjt_cast2->world);
#line 2 "lib/ui/rect.sj"
    sjt_cast2->_rect.x = 0;
#line 3
    sjt_cast2->_rect.y = 0;
#line 4
    sjt_cast2->_rect.w = 0;
#line 5
    sjt_cast2->_rect.h = 0;
#line 5
    sjf_rect(&sjt_cast2->_rect);
#line 52 "nau/nauScene3dElement.sj"
    sjt_cast2->_isDragging = false;
#line 2 "lib/ui/point.sj"
    sjt_cast2->_startDrag.x = 0;
#line 3
    sjt_cast2->_startDrag.y = 0;
#line 3
    sjf_point(&sjt_cast2->_startDrag);
#line 54 "nau/nauScene3dElement.sj"
    sjt_cast2->_lookAt.x = 0.0f;
#line 54
    sjt_cast2->_lookAt.y = 0.0f;
#line 54
    sjt_cast2->_lookAt.z = 0.0f;
#line 54
    sjf_vec3(&sjt_cast2->_lookAt);
#line 2 "lib/ui/vec3.sj"
    sjt_cast2->_lookAtDrag.x = 0.0f;
#line 3
    sjt_cast2->_lookAtDrag.y = 0.0f;
#line 4
    sjt_cast2->_lookAtDrag.z = 0.0f;
#line 4
    sjf_vec3(&sjt_cast2->_lookAtDrag);
#line 4
    sjf_nauScene3dElement_heap(sjt_cast2);
#line 1 "lib/ui/element.sj"
    sjt_functionParam5 = (sji_element*)sjf_nauScene3dElement_heap_as_sji_element(sjt_cast2);
#line 1
    sjf_array_heap_element_initAt(sjt_parent7, sjt_functionParam4, sjt_functionParam5);
#line 7 "nau.sj"
    sjt_parent137 = array8;
#line 7
    sjt_functionParam469 = 1;
#line 7
    sjt_cast28 = (sjs_crossHairsElement_heap*)malloc(sizeof(sjs_crossHairsElement_heap));
#line 7
    sjt_cast28->_refCount = 1;
#line 2 "lib/ui/color.sj"
    sjt_parent142 = &sjv_colors;
#line 2
    sjf_anon5_red(sjt_parent142, &sjt_cast28->color);
#line 2 "lib/ui/rect.sj"
    sjt_cast28->_rect.x = 0;
#line 3
    sjt_cast28->_rect.y = 0;
#line 4
    sjt_cast28->_rect.w = 0;
#line 5
    sjt_cast28->_rect.h = 0;
#line 5
    sjf_rect(&sjt_cast28->_rect);
#line 4 "lib/ui/crossHairsElement.sj"
    sjt_cast28->_topDownRenderer = 0;
    if (sjt_cast28->_topDownRenderer != 0) {
        sjt_cast28->_topDownRenderer->_refCount++;
    }

#line 5
    sjt_cast28->_leftRightRenderer = 0;
    if (sjt_cast28->_leftRightRenderer != 0) {
        sjt_cast28->_leftRightRenderer->_refCount++;
    }

#line 2 "lib/ui/point.sj"
    sjt_cast28->_point.x = 0;
#line 3
    sjt_cast28->_point.y = 0;
#line 3
    sjf_point(&sjt_cast28->_point);
#line 3
    sjf_crossHairsElement_heap(sjt_cast28);
#line 1 "lib/ui/element.sj"
    sjt_functionParam470 = (sji_element*)sjf_crossHairsElement_heap_as_sji_element(sjt_cast28);
#line 1
    sjf_array_heap_element_initAt(sjt_parent137, sjt_functionParam469, sjt_functionParam470);
#line 2 "lib/ui/rect.sj"
    sjt_cast1->_rect.x = 0;
#line 3
    sjt_cast1->_rect.y = 0;
#line 4
    sjt_cast1->_rect.w = 0;
#line 5
    sjt_cast1->_rect.h = 0;
#line 5
    sjf_rect(&sjt_cast1->_rect);
#line 5
    sjf_fillElement_heap(sjt_cast1);
#line 1 "lib/ui/element.sj"
    sjv_root = (sji_element*)sjf_fillElement_heap_as_sji_element(sjt_cast1);
#line 1
    sjf_runLoop();
    main_destroy();
    return 0;
}

void main_destroy() {

    sjt_cast1->_refCount--;
    if (sjt_cast1->_refCount <= 0) {
        sjf_fillElement_destroy((sjs_fillElement*)(((char*)sjt_cast1) + sizeof(intptr_t)));
    }
    sjt_cast11->_refCount--;
    if (sjt_cast11->_refCount <= 0) {
        sjf_leafPanel_destroy((sjs_leafPanel*)(((char*)sjt_cast11) + sizeof(intptr_t)));
    }
    sjt_cast17->_refCount--;
    if (sjt_cast17->_refCount <= 0) {
        sjf_panel3d_destroy((sjs_panel3d*)(((char*)sjt_cast17) + sizeof(intptr_t)));
    }
    sjt_cast18->_refCount--;
    if (sjt_cast18->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast18) + sizeof(intptr_t)));
    }
    sjt_cast19->_refCount--;
    if (sjt_cast19->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast19) + sizeof(intptr_t)));
    }
    sjt_cast2->_refCount--;
    if (sjt_cast2->_refCount <= 0) {
        sjf_nauScene3dElement_destroy((sjs_nauScene3dElement*)(((char*)sjt_cast2) + sizeof(intptr_t)));
    }
    sjt_cast20->_refCount--;
    if (sjt_cast20->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast20) + sizeof(intptr_t)));
    }
    sjt_cast21->_refCount--;
    if (sjt_cast21->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast21) + sizeof(intptr_t)));
    }
    sjt_cast22->_refCount--;
    if (sjt_cast22->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast22) + sizeof(intptr_t)));
    }
    sjt_cast23->_refCount--;
    if (sjt_cast23->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast23) + sizeof(intptr_t)));
    }
    sjt_cast24->_refCount--;
    if (sjt_cast24->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast24) + sizeof(intptr_t)));
    }
    sjt_cast25->_refCount--;
    if (sjt_cast25->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast25) + sizeof(intptr_t)));
    }
    sjt_cast26->_refCount--;
    if (sjt_cast26->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast26) + sizeof(intptr_t)));
    }
    sjt_cast27->_refCount--;
    if (sjt_cast27->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast27) + sizeof(intptr_t)));
    }
    sjt_cast28->_refCount--;
    if (sjt_cast28->_refCount <= 0) {
        sjf_crossHairsElement_destroy((sjs_crossHairsElement*)(((char*)sjt_cast28) + sizeof(intptr_t)));
    }
    sjt_cast9->_refCount--;
    if (sjt_cast9->_refCount <= 0) {
        sjf_model_destroy((sjs_model*)(((char*)sjt_cast9) + sizeof(intptr_t)));
    }
    sjt_functionParam100->_refCount--;
    if (sjt_functionParam100->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam100);
    }
    sjt_functionParam199->_refCount--;
    if (sjt_functionParam199->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam199);
    }
    sjt_functionParam268->_refCount--;
    if (sjt_functionParam268->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam268);
    }
    sjt_functionParam277->_refCount--;
    if (sjt_functionParam277->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam277);
    }
    sjt_functionParam296->_refCount--;
    if (sjt_functionParam296->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam296);
    }
    sjt_functionParam315->_refCount--;
    if (sjt_functionParam315->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam315);
    }
    sjt_functionParam334->_refCount--;
    if (sjt_functionParam334->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam334);
    }
    sjt_functionParam353->_refCount--;
    if (sjt_functionParam353->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam353);
    }
    sjt_functionParam372->_refCount--;
    if (sjt_functionParam372->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam372);
    }
    sjt_functionParam391->_refCount--;
    if (sjt_functionParam391->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam391);
    }
    sjt_functionParam410->_refCount--;
    if (sjt_functionParam410->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam410);
    }
    sjt_functionParam429->_refCount--;
    if (sjt_functionParam429->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam429);
    }
    sjt_functionParam448->_refCount--;
    if (sjt_functionParam448->_refCount <= 0) {
        sji_nauScene3dElement_model_destroy(sjt_functionParam448);
    }
    sjt_functionParam470->_refCount--;
    if (sjt_functionParam470->_refCount <= 0) {
        sji_element_destroy(sjt_functionParam470);
    }
    sjt_functionParam5->_refCount--;
    if (sjt_functionParam5->_refCount <= 0) {
        sji_element_destroy(sjt_functionParam5);
    }
    sjv_root->_refCount--;
    if (sjv_root->_refCount <= 0) {
        sji_element_destroy(sjv_root);
    }
    sjf_string_destroy(&sjt_call27);
    sjf_mat4_destroy(&sjt_call28);
    sjf_mat4_destroy(&sjt_call29);
    sjf_texture_destroy(&sjt_call34);
    sjf_string_destroy(&sjt_call35);
    sjf_texture_destroy(&sjt_call36);
    sjf_string_destroy(&sjt_call37);
    sjf_texture_destroy(&sjt_call38);
    sjf_string_destroy(&sjt_call39);
    sjf_texture_destroy(&sjt_call40);
    sjf_string_destroy(&sjt_call41);
    sjf_texture_destroy(&sjt_call42);
    sjf_string_destroy(&sjt_call43);
    sjf_texture_destroy(&sjt_call44);
    sjf_string_destroy(&sjt_call45);
    sjf_texture_destroy(&sjt_call46);
    sjf_string_destroy(&sjt_call47);
    sjf_texture_destroy(&sjt_call48);
    sjf_string_destroy(&sjt_call49);
    sjf_string_destroy(&sjt_call50);
    sjf_mat4_destroy(&sjt_call51);
    sjf_mat4_destroy(&sjt_call52);
    sjf_string_destroy(&sjt_call53);
    sjf_mat4_destroy(&sjt_call54);
    sjf_mat4_destroy(&sjt_call55);
    sjf_string_destroy(&sjt_call56);
    sjf_mat4_destroy(&sjt_call57);
    sjf_mat4_destroy(&sjt_call58);
    sjf_string_destroy(&sjt_call59);
    sjf_mat4_destroy(&sjt_call60);
    sjf_mat4_destroy(&sjt_call61);
    sjf_string_destroy(&sjt_call62);
    sjf_mat4_destroy(&sjt_call63);
    sjf_mat4_destroy(&sjt_call64);
    sjf_string_destroy(&sjt_call65);
    sjf_mat4_destroy(&sjt_call66);
    sjf_mat4_destroy(&sjt_call67);
    sjf_string_destroy(&sjt_call68);
    sjf_mat4_destroy(&sjt_call69);
    sjf_mat4_destroy(&sjt_call70);
    sjf_string_destroy(&sjt_call71);
    sjf_mat4_destroy(&sjt_call72);
    sjf_mat4_destroy(&sjt_call73);
    sjf_string_destroy(&sjt_call74);
    sjf_mat4_destroy(&sjt_call75);
    sjf_mat4_destroy(&sjt_call76);
    sjf_string_destroy(&sjt_call77);
    sjf_mat4_destroy(&sjt_call78);
    sjf_mat4_destroy(&sjt_call79);
    sjf_vec3_destroy(&sjt_call80);
    sjf_vec3_destroy(&sjt_call81);
    sjf_vec3_destroy(&sjt_call82);
    sjf_anon2_destroy(&sjv_animator);
    sjf_shader_destroy(&sjv_blurHorizontalShader);
    sjf_shader_destroy(&sjv_blurVerticalShader);
    sjf_anon3_destroy(&sjv_borderPosition);
    sjf_shader_destroy(&sjv_boxShader);
    sjf_anon4_destroy(&sjv_buttonState);
    sjf_anon5_destroy(&sjv_colors);
    sjf_anon1_destroy(&sjv_console);
    sjf_shader_destroy(&sjv_imageShader);
    sjf_shader_destroy(&sjv_phongColorShader);
    sjf_shader_destroy(&sjv_phongTextureShader);
    sjf_scene2d_destroy(&sjv_rootScene);
    sjf_windowRenderer_destroy(&sjv_rootWindowRenderer);
    sjf_anon6_destroy(&sjv_style);
    sjf_shader_destroy(&sjv_textShader);
    sjf_string_destroy(&sjv_vertex_location_texture_normal_format);
}
