#include <EntityService.h>

extern Player *player;

EntityService::EntityService()
{
    _flat_entities = new std::vector<Entity2D *>();
    _thic_entities = new std::vector<Entity3D *>();
    _camera_p = Camera(PERSPECTIVE, window);
    _camera_o = Camera(ORTHO, window);
    _renderer2d = new Renderer2d(_flat_entities, _camera_o);
    _renderer3d = new Renderer3d(_thic_entities, _camera_p);
}

EntityService::~EntityService()
{
    for(auto i = _flat_entities->size(); i-- > 0;)
        delete (*_flat_entities)[i];
    for(auto i = _thic_entities->size(); i-- > 0;)
        delete (*_thic_entities)[i];
    delete _flat_entities;
    delete _thic_entities;
    delete _renderer2d;
    delete _renderer3d;
}
    
void EntityService::updateFlatEntities(double delta) const
{
    for(auto i = _flat_entities->size(); i-- > 0;)
        (*_flat_entities)[i]->update(delta);
    player->update(delta);
}

void EntityService::updateThiccEntities(double delta) const
{
    for(auto i = _thic_entities->size(); i-- > 0;)
        (*_thic_entities)[i]->update(delta);
}

void EntityService::render() const
{
    _renderer3d->render();
    _renderer2d->render();
}

void EntityService::addEntity(Entity2D *entity)
{
    _flat_entities->push_back(entity);
}

void EntityService::addEntity(Entity3D *entity)
{
    _thic_entities->push_back(entity);
}

std::vector<Entity2D *> *EntityService::get_all_flat_entities() const
{
    return _flat_entities;
}

std::vector<Entity3D *> *EntityService::get_all_thic_entities() const
{
    return _thic_entities;
}