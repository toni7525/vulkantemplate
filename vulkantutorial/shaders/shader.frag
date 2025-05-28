#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 0) out vec4 outColor;



void main() {

    //vec3 lightpos = vec3(2,-3,0);
    //float light = (dot(lightpos,vec3(normalrecalc.x,normalrecalc.y,normalrecalc.z))+1)/2;
    //outColor = vec4(light,light,light, 1.0);
    //outColor = vec4(innormal, 1.0);
    outColor = vec4(fragColor * texture(texSampler, fragTexCoord).rgb, 1.0);
}