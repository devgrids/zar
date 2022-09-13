#include "gl_skybox.h"

zar::GLSkybox::GLSkybox()
{
    // this->name_skybox_ = name_skybox_;
    // this->shader = *Util::Instance()->myShaders[ShaderType::CUBE_MAP];
    // this->skyboxShader = *Util::Instance()->myShaders[ShaderType::SKYBOX];

    // load_skybox(name_skybox_, type);
    // config_cube_map();
    // config_shader();
}

void zar::GLSkybox::render(GLCamera& camera, glm::vec3 ambient)
{
    // shader_.use();
    glm::mat4 model = glm::mat4(1.0f);
    // glm::mat4 view = camera.GetViewMatrix();
    // glm::mat4 projection = glm::perspective(glm::radians(camera.FOV), (float)WIDTH / (float)HEIGHT, camera.NEAR,
    //                                         camera.FAR);
    // shader_.setMat4("model", model);
    // shader_.setMat4("view", view);
    // shader_.setMat4("projection", projection);
    // shader_.setVec3("cameraPos", camera.Position);
    //
    // glDepthFunc(GL_LEQUAL);
    // skybox_shader_.use();
    // view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    // skybox_shader_.setMat4("view", view);
    // skybox_shader_.setMat4("projection", projection);
    // skybox_shader_.setVec3("ambient", ambient);

    glBindVertexArray(skybox_vao_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void zar::GLSkybox::load_skybox(const std::string& name_skybox, const std::string& type)
{
    // vector<string> faces;
    // vector<string> order = {"px", "nx", "py", "ny", "pz", "nz"};
    // string path = "assets\\skyboxs\\" + name_skybox + "\\" + name_skybox;
    // string direction;
    //
    // for (int i = 0; i < 6; i++)
    // {
    //     direction = path + "_" + order[i] + "." + type;
    //     faces.push_back(direction);
    // }
    // glDeleteTextures(1, &cubemap_texture_);
    // cubemap_texture_ = Util::loadCubemap(faces);
}

void zar::GLSkybox::config_cube_map()
{
    // cube VAO

    glGenVertexArrays(1, &cube_vao_);
    glGenBuffers(1, &cube_vbo_);
    glBindVertexArray(cube_vao_);
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), &cube_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // skybox VAO

    glGenVertexArrays(1, &skybox_vao_);
    glGenBuffers(1, &skybox_vbo_);
    glBindVertexArray(skybox_vao_);
    glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void zar::GLSkybox::config_shader()
{
    // shader_.use();
    // shader_.setInt("skybox", 0);
    //
    // skybox_shader_.use();
    // skybox_shader_.setInt("skybox", 0);
}
