#include "framework.h"

#include "point.h"
#include "vectorgraphic.h"
#include <list>
#include <memory>
#include <string>

namespace framework {
void PlacedGrahpic::setPlacementPoint(geom::Point const &placement) {
}
geom::Point const &PlacedGraphic::getPlacementPoint() const {
}
void PlacedGraphic::setGraphic(HVectorGraphic const &graphic) {
}
HVectorGraphic const &PlacedGraphic::getGraphic() const {
}
void Layer::insert(const PlacedGraphic &pg) {
}
void Layer::remove(const PlacedGraphic &pg) {
}
Layer::PlacedGraphicIterator Layer::begin() {
}
Layer::PlacedGraphicIterator Layer::end() {
}
std::string &Layer::getAlias() const {
}
void Layer::setAlias() {

}

void Scene::insert(const Layer &layer) {

}
void Scene::remove(const Layer &layer) {
}

Scene::LayerIterator Scene::begin() {
}
Scene::LayerIterator Scene::end() {
}
} // namespace framework

