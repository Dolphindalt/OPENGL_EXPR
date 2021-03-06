#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <window.h>
#include <string>

enum CameraType { ORTHO, PERSPECTIVE };

class Camera
{
public:
    Camera();
    Camera(CameraType, WindowData &);
    ~Camera();
    void update();
    void load_view_and_projection(GLuint &program, const std::string &viewstr, const std::string &projectionstr);
    void set_camera_type(CameraType _type);

    void getView(glm::mat4 &v);
    void getProjection(glm::mat4 &p);
private:
    CameraType type;
    int x, y, width, height;
    double aspect_ratio;
    glm::mat4 projection, view;
};

#endif