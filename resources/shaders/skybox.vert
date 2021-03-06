#version 450

layout(std140, set = 0, binding = 0) uniform cameraBlock {
    mat4 view;
    mat4 proj;
} camera;

layout (location = 0) in vec3 inPos;

layout (location = 0) out vec3 outPos;

void main() {
    outPos = inPos;
    outPos.y *= -1.0;

    // Remove the translation from camera view matrix
    gl_Position = camera.proj * mat4(mat3(camera.view)) * vec4(inPos, 1.0);
    gl_Position.y = -gl_Position.y;
    gl_Position = gl_Position.xyww;
}
