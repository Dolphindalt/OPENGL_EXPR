#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <window.h>

enum CameraType { ORTHO, PERSPECTIVE };

class Camera
{
public:
    Camera();
    Camera(CameraType, WindowData &);
    ~Camera();
    void update();

    void getMVP(glm::mat4 &mvp);
private:
    CameraType type;
    double aspect_ratio;
    glm::mat4 projection, view, model;
};

#endif