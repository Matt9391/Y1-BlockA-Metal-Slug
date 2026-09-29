#pragma once

#include <vec2.h>
#include <MapLayerNames.h>
#include <MapLayer.h>

class Spawner;

struct MapRenderSet {
    const vec2& pos;
    const int& tileSize;
    const int& layerCount;
    const int& layerObjCount;
    const MapLayer(&layers)[MapLayerNames::MLN_COUNTS];
    Spawner**  const(&spawners)[MapObjectLayerNames::MOLN_COUNTS];
    const int(&spawnerCounts)[MapObjectLayerNames::MOLN_COUNTS];

    MapRenderSet(
        const vec2& pos,
        const int& tileSize,
        const int& layerCount,
        const int& layerObjCount,
        const MapLayer(&layers)[MapLayerNames::MLN_COUNTS],
        Spawner** const(&spawners)[MapObjectLayerNames::MOLN_COUNTS],
        const int(&spawnerCounts)[MapObjectLayerNames::MOLN_COUNTS]
    )
        : pos(pos),
        tileSize(tileSize),
        layerCount(layerCount),
        layerObjCount(layerObjCount),
        layers(layers),
        spawners(spawners),
        spawnerCounts(spawnerCounts)
    {
    }
};