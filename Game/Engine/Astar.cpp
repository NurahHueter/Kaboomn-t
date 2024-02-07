#include "pch.h"
#include <queue>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include "Astar.h"
#include "tileson.hpp"
namespace mmt_gd
{

    bool Node::operator>(const Node& other) const
    {
        return Node::m_weight > other.m_weight;
    }

    template <class T1, class T2>
    std::size_t PairHash::operator()(const std::pair<T1, T2>& p) const
    {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Simple hash combine function
        return h1 ^ h2;
    }

    template <class T1, class T2>
    bool PairEqual::operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    std::vector<std::pair<int, int>> AStar(const std::vector<std::vector<int>>& grid, const Node& start, const Node& goal)
    {
        // Direction in which one can move
        const int dx[] = { 0, 1, 0, -1 };
        const int dy[] = { 1, 0, -1, 0 };

        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;   // Points to be processed
        std::unordered_set<std::pair<int, int>, PairHash, PairEqual> seenSet;       // Processed points
        std::unordered_map<std::pair<int, int>, int, PairHash, PairEqual> costMap;
        std::unordered_map<std::pair<int, int>, std::pair<int, int>, PairHash, PairEqual> parentMap;  // To store the parent information

        openSet.push(start);
        costMap[{start.m_x, start.m_y}] = start.m_weight;

        while (!openSet.empty())
        {
            Node current = openSet.top();
            openSet.pop();

            if (current.m_x == goal.m_x && current.m_y == goal.m_y)
            {
                // Path found, reconstruct and print the path
                std::vector<std::pair<int, int>> path;
                std::pair<int, int> currentPos = { current.m_x, current.m_y };

                while (parentMap.find(currentPos) != parentMap.end())
                {
                    path.push_back(currentPos);
                    currentPos = parentMap[currentPos];
                }
                path.push_back(std::make_pair(start.m_x, start.m_y));
                openSet.empty();
                seenSet.empty();
                costMap.clear();
                parentMap.clear();
                return path;
            }

            seenSet.insert({ current.m_x, current.m_y }); // Once visited, no need to visit again

            for (int i = 0; i < 4; ++i)
            {
                // Test all 4 directions
                int nx = current.m_x + dx[i];
                int ny = current.m_y + dy[i];

                if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size())
                {
                    if (grid[nx][ny] == 1 && seenSet.find({ nx, ny }) == seenSet.end()) // If walkable and not in the closed set
                    {

                        int newSteps = current.m_steps + 1;
                        int newHeur = abs(nx - goal.m_x) + abs(ny - goal.m_y);
                        int newWeight = newSteps + newHeur;

                        auto it = costMap.find({ nx, ny });

                        if (it == costMap.end() || newWeight < it->second)
                        {
                            openSet.push(Node(nx, ny, newSteps, newHeur));
                            costMap[{nx, ny}] = newWeight;
                            parentMap[{nx, ny}] = { current.m_x, current.m_y };  // Store the parent information
                        }
                    }
                }            
            }
        }
    }
}

