#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "MyShader.h"
#include "stb_image.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor, 1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL函数前需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD " << std::endl;
		return -1;
	}

	// 设置视口，如果视口比上面的Windows小，则可能显示不全，有些显示在视口之外
	glViewport(0, 0, 800, 600);

	// 注册窗口大小改变的回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/************************************** DrawArrays ***********************************************/
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/*float vertices[] = {
	0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	};*/

	// 增加每个顶点的属性
	float vertices[] = {
	// ---- 位置 -----  ------ 颜色 -----  -- UV --
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // 右下
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // 左下
	 0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // 右上
	-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// 左上
	 //0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // 顶部
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 配置属性位置值为0的顶点属性（位置）
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// 配置属性位置值为1的顶点属性（颜色）
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	// 配置属性位置值为2的顶点属性（UV坐标）
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int indices[] = {
		3, 0, 1,
		3, 2, 0,
	};
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	

	/************************************** ShaderProgram ***********************************************/
	Shader ourShader("E:/MyProject/LearnOpenGL/LearnOpenGL/vertexShader.vs", "E:/MyProject/LearnOpenGL/LearnOpenGL/fragmentShader.fs");
	/*unsigned int ShaderProgram, VertexShader, FragmentShader;
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(VertexShader);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(FragmentShader);

	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);*/

	// 绘制模式，正背面都绘制+线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	/***************************************** 创建纹理 ***********************************************/
	

	// 创建纹理
	// 1. 申请相应的空间，与前面的VBO/VAO类似
	unsigned int texture[2];
	glGenTextures(2, texture);
	// 2. 绑定纹理对象
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// 3. 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 4. 载入图片，给当前绑定的纹理对象附加纹理图片
	int width, height, nrChannels;
	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// 指定纹理目标， mipmap级别, 纹理储存格式, 纹理宽度高度, 总是为0(历史遗留问题), 图片源的格式数据类型, 图片源
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// 5. 生成相应的多级渐远纹理(Mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// 6. 将原本的图片内存释放
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// 指定纹理目标， mipmap级别, 纹理储存格式, 纹理宽度高度, 总是为0(历史遗留问题), 图片源的格式数据类型, 图片源
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// 5. 生成相应的多级渐远纹理(Mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// 告诉fragmentShader所使用的纹理单元
	ourShader.use();
	//glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	/************************************** RenderLoop ***********************************************/
	// 渲染循环，让画面在关闭窗口前一直画
	while (!glfwWindowShouldClose(window))
	{
		// 处理键盘输入事件
		processInput(window);

		// ...渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 激活纹理单元，不指定的话默认是0，所以fragmentShader的 uniform sampler2D ourTexture 可以不用显式指明
		// OpenGL 一共提供16个纹理单元供使用(用4bits来记)
		glActiveTexture(GL_TEXTURE0);
		// 绑定纹理
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		// 激活当前所使用的ShaderProgram
		//glUseProgram(ShaderProgram);
		ourShader.use();
		/*float offset[] = { 0.1, 0.1, 0.1 };
		ourShader.setVec3("offset", offset);*/

		// 绘制图形
		glBindVertexArray(VAO);

		// 用EBO
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 不用顶点索引
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// 检查并调用事件，交换缓冲区
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 释放所有资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(ShaderProgram);

	glfwTerminate();

	return 0;
}