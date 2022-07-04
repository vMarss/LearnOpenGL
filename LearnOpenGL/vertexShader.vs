#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;
uniform vec3 offset; 

void main()
{  
   vec3 curPos = aPos + offset;
   gl_Position = vec4(curPos, 1.0);
   ourColor = curPos;
   // 将顶点上的纹理坐标传到FragmentShader
   TexCoord = aTexCoord;
}