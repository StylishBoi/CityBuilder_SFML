#include "motion/AStar.h"

#include <array>
#include <iostream>
#include <queue>

#include "motion/path.h"

namespace api::motion {
    namespace Astar {

        struct aStarNode {
            sf::Vector2f position;
            float g;
            float h;
            float f;

            size_t previous_index;
            bool has_previous;

            aStarNode(sf::Vector2f position, float g, float h, size_t prev_idx=0, bool has_prev=false) : position(position),
                g(g),
                h(h),
                f(g + h),
                previous_index(prev_idx),
                has_previous(has_prev){
            }

            // A Star node are prioritize by the lowest f value
            friend bool operator<(aStarNode const &left, aStarNode const &right){
                return left.f > right.f;
            }
        };

        float heuristic(sf::Vector2f p1, sf::Vector2f p2){
            return (p2 - p1).length();
        }

        std::array<sf::Vector2f, 4> neighbours(int gridStep = 16){
            std::array<sf::Vector2f, 4> neighbours = {
                sf::Vector2f(0, gridStep),
                sf::Vector2f(gridStep, 0),
                sf::Vector2f(0, -1 * gridStep),
                sf::Vector2f(-1 * gridStep, 0)
            };

            return neighbours;
        }

        Path ReconstitutePath(const std::vector<aStarNode>& nodes, size_t final_node_index) {
          Path path;
          std::vector<sf::Vector2f> pathPoints;
          size_t current_index = final_node_index;
          const aStarNode* current_node = &nodes[current_index];

          while (current_node->has_previous) {
            pathPoints.emplace_back(current_node->position);
            current_index = current_node->previous_index;
            current_node = &nodes[current_index];
          }
          pathPoints.emplace_back(current_node->position);

          std::reverse(pathPoints.begin(), pathPoints.end());
          path.Fill(pathPoints);
          return path;
        }

    Path GetPath(const int gridStep, sf::Vector2f start, sf::Vector2f end,
             std::vector<sf::Vector2f> walkableTiles) {
    Path aStarPath;

    // Are start / end point in walkables tiles ?
    auto f = std::find(walkableTiles.begin(), walkableTiles.end(), start);
    if (f == walkableTiles.end()) {
        std::cout << "Start point not in walkable tiles" << std::endl;
        return aStarPath;
    }

    auto g = std::find(walkableTiles.begin(), walkableTiles.end(), end);
    if (g == walkableTiles.end()) {
        std::cout << "End point not in walkable tiles" << std::endl;
        return aStarPath;
    }

    std::vector<aStarNode> allNodes;
    allNodes.reserve(walkableTiles.size() * 4);  // Reserve more space

    std::priority_queue<std::pair<float, size_t>> openList;
    std::vector<bool> inClosedList(walkableTiles.size() * 4, false);  // Increase size
    std::vector<bool> explored(walkableTiles.size(), false);  // Track explored tiles

    // Add start node
    allNodes.emplace_back(start, 0, heuristic(start, end));
    openList.push({0, 0});

    while (!openList.empty()) {
        size_t current_index = openList.top().second;
        aStarNode& currentNode = allNodes[current_index];
        openList.pop();

        if (currentNode.position == end) {
            return ReconstitutePath(allNodes, current_index);
        }

        if (inClosedList[current_index]) continue;
        inClosedList[current_index] = true;

        for (const auto& neighbour : neighbours(gridStep)) {
            sf::Vector2f newPosition = currentNode.position + neighbour;

            // Check if the position is walkable
            auto it = std::find(walkableTiles.begin(), walkableTiles.end(), newPosition);
            if (it != walkableTiles.end()) {
                size_t tile_index = std::distance(walkableTiles.begin(), it);

                // Skip if we've already explored this tile
                if (explored[tile_index]) continue;

                explored[tile_index] = true;

                float new_g = currentNode.g + 1;
                float new_h = heuristic(newPosition, end);

                allNodes.emplace_back(newPosition, new_g, new_h, current_index, true);
                openList.push({new_g + new_h, allNodes.size() - 1});
            }
        }
    }

    return aStarPath;
}
    }
}