#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

class mesh {
public:
    mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~mesh();

    void initialize();
    void draw() const;
    void shutdown();
private:
    unsigned int VBO, VAO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
#endif
