#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // FragColor = vec4(ourColor, 1.0f);
    // 采样纹理颜色
    // FragColor = texture(texture2, TexCoord) * vec4(ourColor, 1.0f);
    // 混合两个颜色结果进行线性插值, 0 表示用第一个；1 表示用第二个
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}