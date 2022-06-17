#ifndef __TOOLBOX_COMMON_H__
#define __TOOLBOX_COMMON_H__

#if UINTPTR_MAX == UINT64_MAX
#define __64_BITS__
#endif

#define IS_FALSE(b)         (false == (b))
#define IS_NULL(p)          (NULL == (p))
#define IS_TRUE(b)          (true == (b))
#define IS_VALID_POINTER(p) ((uintptr_t)(p) >= SEGMENT_SIZE)
#define IS_VALID_HANDLE(h)  (!IS_NULL(h) && (INVALID_HANDLE_VALUE != (h)))
#define IS_ZERO(v)          (0 == (v))

#define EXIT_FAILED(c)    (EXIT_SUCCESS != (c))
#define EXIT_SUCCEEDED(c) (EXIT_SUCCESS == (c))

#define PAGE_SIZE    SECTION_SIZE
#define SECTION_SIZE ((uintptr_t)0x1000)
#define SEGMENT_SIZE (0x10 * SECTION_SIZE)

#define POI(ptr, off) (*(void**)PTR(ptr, off))
#define PTR(ptr, off) ((void*)((uintptr_t)(ptr) + (intptr_t)(off)))

#ifdef __64_BITS__
#define PFx     PFx64
#define PFX     PFX64
#define FP(ptr) FP64(ptr)
#else
#define PFx     "%08x"
#define PFX     "%08X"
#define FP(ptr) (uint32_t)(ptr)
#endif

#define PFx64     "%08x`%08x"
#define PFX64     "%08X`%08X"
#define FP64(ptr) (uint32_t)((uint64_t)(ptr) >> 0x20), \
                  (uint32_t)((uint64_t)(ptr)&UINT32_MAX)

#endif // __TOOLBOX_COMMON_H__
