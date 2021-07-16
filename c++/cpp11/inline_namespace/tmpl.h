_Pragma("once")

namespace Jim {
    inline namespace Basic {
        struct Knife {};
        class CorkScrew {};
    }

    inline namespace Toolkit {
        template <typename T> class SwissArmyknife{};
    }

    namespace Other {
        Knife b;       // Knife in Basic
        struct Knife {};  // New Knife;
        Knife c;       // Knife in Other
        Basic::Knife k;// Knife in Basic;
    }
}
