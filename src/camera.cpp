#include <camera.h>

#include <glm/gtx/transform.hpp>

Camera::Camera() {}

Camera::Camera(CameraType _type, WindowData &windowData)
{
    type = _type;
    aspect_ratio = windowData.get_aspect_ratio();
    view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    model = glm::mat4(1.0f);
}

Camera::~Camera()
{

}

void Camera::update()
{
    switch(type)
    {
        case ORTHO:
            projection = glm::ortho(-1.5f * float(aspect_ratio), 1.5f * float(aspect_ratio), -1.5f, 1.5f, -10.0f, 10.f);
            break;
        case PERSPECTIVE:
            break;
    }
}

void Camera::getMVP(glm::mat4 &mvp)
{
    mvp = projection * view * model;
}