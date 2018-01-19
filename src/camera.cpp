#include <camera.h>

#include <glm/gtx/transform.hpp>

Camera::Camera() {}

Camera::Camera(CameraType _type, WindowData &windowData)
{
    type = _type;
    aspect_ratio = windowData.get_aspect_ratio();
    x = 0;
    y = 0;
    width = windowData.w;
    height = windowData.h;
    view = glm::lookAt(glm::vec3(0, 0, 15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
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
            projection = glm::ortho(-1.0f, float(aspect_ratio), -1.0f, float(aspect_ratio), 0.0f, 100.0f);
            break;
        case PERSPECTIVE:
            projection = glm::perspective(glm::radians(50.0f), float(aspect_ratio), 0.1f, 100.0f);
            break;
    }
}

void Camera::set_camera_type(CameraType _type)
{
    type = _type;
}

void Camera::getMVP(glm::mat4 &mvp)
{
    mvp = projection * view * model;
}