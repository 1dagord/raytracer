#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <Eigen/Dense>


#include "linalg.hpp"
#include "render_objects.hpp"

// World contains all objects to be rendered
class World {
    public:
        std::vector<std::unique_ptr<RTObject>> objects;
        std::vector<std::unique_ptr<PointLight>> lights;

    public:
        World () {
            objects.emplace_back(std::make_unique<RTSphere>(1.0));
            objects.emplace_back(std::make_unique<RTSphere>(0.5));
            lights.emplace_back(std::make_unique<PointLight>());
        }
            
};

#endif