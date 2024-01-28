#pragma once
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>
namespace mmt_gd
{
    struct PairHash {
        template <class T1, class T2>
        std::size_t operator () (const std::pair<T1, T2>& p) const;
    };

    struct PairEqual {
        template <class T1, class T2>
        bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const;
    };

    struct Node
    {
        int m_x, m_y;
        int m_steps, m_heur, m_weight;

        Node(int x, int y, int steps, int heur) : m_x(x), m_y(y), m_steps(steps), m_heur(heur), m_weight(steps + heur) {}

        bool operator>(const Node& other) const;
        
    };

    std::vector<std::pair<int, int>> AStar(const std::vector<std::vector<int>>& grid, const Node& start, const Node& goal);
}