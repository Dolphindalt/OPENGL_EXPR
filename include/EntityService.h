#ifndef ENTITYSERVICE_H
#define ENTITYSERVICE_H

#include <player.h>
#include <vector>
#include <Entity.h>
#include <Renderer2d.h>
#include <Renderer3d.h>
#include <camera.h>

class EntityService {
private:
    std::vector<Entity2D *> *_flat_entities;
    std::vector<Entity3D *> *_thic_entities;
    Renderer2d *_renderer2d;
    Renderer3d *_renderer3d;
public:
    EntityService(Renderer2d *renderer2d, Renderer3d *renderer3d);
    ~EntityService();

    void updateFlatEntities(double delta) const;
    void updateThiccEntities(double delta) const;

    void render() const;

    void addEntity(Entity2D *entity);
    void addEntity(Entity3D *entity);

    std::vector<Entity2D *> *get_all_flat_entities() const;
    std::vector<Entity3D *> *get_all_thic_entities() const;
};

#endif