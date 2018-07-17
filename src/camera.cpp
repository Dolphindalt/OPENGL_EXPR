#include <camera.h>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <shaders.h>

Camera::Camera() {}

Camera::Camera(CameraType _type, WindowData &windowData)
{
    type = _type;
    aspect_ratio = windowData.get_aspect_ratio();
    x = 0;
    y = 0;
    width = windowData.w;
    height = windowData.h;
    view = glm::lookAt(glm::vec3(0, 0, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
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

void Camera::load_view_and_projection(GLuint &program, const std::string &viewstr, const std::string &projectionstr)
{
    GLuint view_loc = shader_get_uniform_location(program, viewstr.c_str()),
    proj_loc = shader_get_uniform_location(program, projectionstr.c_str());
    shader_load_mat4(view_loc, view);
    shader_load_mat4(proj_loc, projection);
}


void Camera::set_camera_type(CameraType _type)
{
    type = _type;
}

void Camera::getView(glm::mat4 &v)
{
    v = view;
}

void Camera::getProjection(glm::mat4 &p)
{
    p = projection;
}