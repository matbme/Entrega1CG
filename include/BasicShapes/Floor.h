#ifndef FLOOR_H
#define FLOOR_H

#include <GLFW/glfw3.h>

namespace BasicShapes {
class Floor {
public:
    static constexpr GLfloat vertices[] = {
//       x     y     z     r    g    b
        // base
        -0.5, -0.5, -0.5, 0.3, 0.3, 0.3, // A - 0
        -0.5, -0.5,  0.5, 0.3, 0.3, 0.3, // B - 1
         0.5, -0.5, -0.5, 0.3, 0.3, 0.3, // C - 2
         0.5, -0.5,  0.5, 0.3, 0.3, 0.3, // D - 3
    };

    static constexpr unsigned int indices[] = {
        // base
        0, 1, 2,
        1, 2, 3,
    };

    static constexpr int size_vertices () {
        return sizeof (vertices);
    }
    
    static constexpr int size_indices () {
        return sizeof (indices);
    }
};
}

#endif
