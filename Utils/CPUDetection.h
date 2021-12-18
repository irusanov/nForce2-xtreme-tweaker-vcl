#include <algorithm>

using namespace std;

struct match_entry_t {
	int family, model, stepping, ext_family, ext_model;
	int l1_data_cache, l1_inst_cache, l2cache;
	unsigned int model_bits;
	char rev[2];
    char core[32];
	char name[32];
};

enum _cpu_bits_t {
    _M_          = BIT_ULL( 0 ),
    _MP_         = BIT_ULL( 1 ),
    _XP_         = BIT_ULL( 2 ),
    _LV_         = BIT_ULL( 3 ),
    _NX_         = BIT_ULL( 4 ),
    _SFF_        = BIT_ULL( 5 ),
    _4_          = BIT_ULL( 6 ),
    MOBILE_      = BIT_ULL( 7 ),
    ATHLON_      = BIT_ULL( 8 ),
    DURON_       = BIT_ULL( 9 ),
    SEMPRON_     = BIT_ULL( 10 ),
    GEODE_       = BIT_ULL( 11 ),
};

static string to_lower (string s) {
    std::for_each(s.begin(), s.end(), [](char & c) {
        c = ::tolower(c);
    });

    return s;
}

static bool decode_amd_model_string(string name) {
    int i = 0;
    unsigned int bits = 0x0;

    const struct { unsigned int bit; const string search; } bit_matchtable[] = {
        { _M_,       " XP-M"   },
        { _MP_,      " MP"     },
        { _XP_,      " XP"     },
        { _LV_,      " (LV)"   },
        { _NX_,      " NX"     },
        { _SFF_,     " SFF"    },
        { _4_,       " 4"      },
        { MOBILE_,   "Mobile"  },
        { ATHLON_,   "Athlon"  },
        { DURON_,    "Duron"   },
        { SEMPRON_,  "Sempron" },
        { GEODE_,    "Geode"   },
    };

    for (i = 0; i < COUNT_OF(bit_matchtable); i++) {
        if (to_lower(name).find(to_lower(bit_matchtable[i].search)) != std::string::npos)
			bits |= bit_matchtable[i].bit;
	}

    return true;
}
