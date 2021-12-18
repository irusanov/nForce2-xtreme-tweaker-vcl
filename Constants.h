// linux/include/asm-generic/bitsperlong.h
#if defined(_WIN64)
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif

// linux/include/linux/bits.h
#define ULL(nr)                       (long long) nr
#define UL(nr)                        (long) nr
#define LBIT(x)                       (UL(1) << x)
#define BIT_ULL(nr)                   (ULL(1) << (nr))
#define BIT_MASK(nr)                  (UL(1) << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)                  ((nr) / BITS_PER_LONG)
#define BIT_ULL_MASK(nr)              (ULL(1) << ((nr) % BITS_PER_LONG_LONG))
#define BIT_ULL_WORD(nr)              ((nr) / BITS_PER_LONG_LONG)
#define BITS_PER_BYTE                 8

#define GENMASK(h, l) \
	(((~UL(0)) - (UL(1) << (l)) + 1) & \
	 (~UL(0) >> (BITS_PER_LONG - 1 - (h))))

#define GENMASK_ULL(h, l) \
	(((~ULL(0)) - (ULL(1) << (l)) + 1) & \
	 (~ULL(0) >> (BITS_PER_LONG_LONG - 1 - (h))))

/* K7 MSRs */
#define MSR_K7_EVNTSEL0               0xc0010000
#define MSR_K7_PERFCTR0               0xc0010004
#define MSR_K7_EVNTSEL1               0xc0010001
#define MSR_K7_PERFCTR1               0xc0010005
#define MSR_K7_EVNTSEL2               0xc0010002
#define MSR_K7_PERFCTR2               0xc0010006
#define MSR_K7_EVNTSEL3               0xc0010003
#define MSR_K7_PERFCTR3               0xc0010007
#define MSR_K7_CLK_CTL                0xc001001b
#define MSR_K7_MANID                  0xc001001e
#define MSR_K7_HWCR                   0xc0010015
#define MSR_K7_HWCR_SMMLOCK_BIT       0
#define MSR_K7_HWCR_SMMLOCK           BIT_ULL(MSR_K7_HWCR_SMMLOCK_BIT)
#define MSR_K7_HWCR_IRPERF_EN_BIT     30
#define MSR_K7_HWCR_IRPERF_EN         BIT_ULL(MSR_K7_HWCR_IRPERF_EN_BIT)
#define MSR_K7_FID_VID_CTL            0xc0010041
#define MSR_K7_FID_VID_STATUS         0xc0010042
#define FEATURE_K7_ECC_BIT            19

/* CPUID function 0x80000001, ebx */
#define CPUID_PKGTYPE_MASK            GENMASK(31, 28)

#define PCI_ADDR_PORT                 0xCF8
#define PCI_DATA_PORT                 0xCFC
#define COUNT_OF(array) (sizeof(array) / sizeof(array[0]))
