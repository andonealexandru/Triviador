#ifndef TRIVIADOR_REGION_H
#define TRIVIADOR_REGION_H

#include <vector>
#include <memory>

namespace Server {
    class Region {
    public:
        // constructors
        Region();
        Region(int id);

        ~Region() = default;

        // setters
        void SetId(int id);
        void SetUserId(int userId);
        void MakeBase();

        // getters
        int GetId();
        int GetUserId();
        bool IsBase();

        // others
        void AddAdjacentRegion(std::shared_ptr<Region> region);

    private:
        int m_Id;
        int m_UserId;
        std::vector<std::shared_ptr<Region>> m_AdjacentRegions;
        bool m_isBase;
    };
}
#endif //TRIVIADOR_REGION_H
