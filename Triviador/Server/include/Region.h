#ifndef TRIVIADOR_REGION_H
#define TRIVIADOR_REGION_H

#include <vector>
#include <memory>

namespace Server {
    class Region {
    public:
        // constructors
        Region();
        explicit Region(int id);

        ~Region() = default;

        // setters
        void SetId(int id);
        void SetUserId(int userId);
        void MakeBase();

        // getters
        int GetId() const;
        int GetUserId() const;
        bool IsBase() const;

        // others
        void AddAdjacentRegion(const std::weak_ptr<Region> &region);

    private:
        int m_Id;
        int m_UserId;
        std::vector<std::weak_ptr<Region>> m_AdjacentRegions;
        bool m_isBase;
    };
}
#endif //TRIVIADOR_REGION_H
