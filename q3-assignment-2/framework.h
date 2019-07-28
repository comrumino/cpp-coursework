#pragma once
#include <list>
#include <string>
#include <memory>
#include "point.h"
#include "vectorgraphic.h"


namespace framework {
using HVectorGraphic = std::unique_ptr<geom::VectorGraphic>;
    class PlacedGraphic {
        public:
            void setPlacementPoint (geom::Point const& placement);
            geom::Point const& getPlacementPoint () const;

            void setGraphic (HVectorGraphic const& graphic);
            HVectorGraphic const& getGraphic () const;
  
        private:
            geom::Point placementPoint;
            HVectorGraphic graphic;
    };

    class Layer {
    private:
        typedef std::list<PlacedGraphic> PlacedGraphicCollection;

    public:
        typedef PlacedGraphicCollection::iterator PlacedGraphicIterator;

        // insert, remove, iteration support.

        // accessors to alias.

    private:
        PlacedGraphicCollection graphics;
        std::string alias;
    };

    class Scene {
    private:
        typedef std::list<Layer> LayerCollection;

    public: typedef LayerCollection::iterator LayerIterator;

            // insert, remove, iteration support.

            // accessors to width and height.

    private:
        LayerCollection layers;
        int width;
        int height;
    };
}
