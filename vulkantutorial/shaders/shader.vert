#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 normalin;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {

    vec4 normalrecalc = ubo.model * vec4(normalin,1.0f);

    vec3 lightpos = vec3(2,-3,0);
    float light = dot(lightpos,vec3(normalrecalc.x,normalrecalc.y,normalrecalc.z))/5+0.8;

    gl_Position = ubo.proj * ubo.view * ubo.model *  vec4(inPosition, 1.0f);  

    fragColor = vec3(1,1,1)*light;
    fragTexCoord = inTexCoord;
}