//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\0";
//
//const char* fragmentShaderSource2 = "#version 330 core\n"
//"uniform vec4 ourColor;\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = ourColor;\n"
//"}\0";
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//	}
//}
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	// GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL函数前需要初始化GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD " << std::endl;
//		return -1;
//	}
//
//	// 设置视口，如果视口比上面的Windows小，则可能显示不全，有些显示在视口之外
//	glViewport(0, 0, 800, 600);
//
//	// 注册窗口大小改变的回调函数
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	/************************************** DrawArrays ***********************************************/
//	unsigned int VAO[2], VBO[2], EBO;
//	glGenVertexArrays(2, VAO);
//	glBindVertexArray(VAO[0]);
//
//	float vertices1[] = {
//	0.5f, 0.5f, 0.0f,   // 右上角
//	0.5f, -0.5f, 0.0f,  // 右下角
//	-0.5f, -0.5f, 0.0f, // 左下角
//	-0.5f, 0.5f, 0.0f,   // 左上角
//	0.5f, 0.5f, 0.0f,   // 右上角
//	-0.5f, -0.5f, 0.0f, // 左下角
//	};
//
//	glGenBuffers(2, VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	// 启用这一项才可以在顶点着色器中访问到逐顶点的属性数据
//	glEnableVertexAttribArray(0);
//
//
//	/************************************** DrawElement ***********************************************/
//	glBindVertexArray(VAO[1]);
//
//	float vertices2[] = {
//	-0.5f, 0.5f, 0.0f,   // 左上角
//	0.5f, 0.5f, 0.0f,   // 右上角
//	-0.5f, -0.5f, 0.0f, // 左下角
//	};
//
//	/*glGenBuffers(2, VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);*/
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	/*glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);*/
//	
//
//	unsigned int indices[] = {
//		1, 2, 3,
//	};
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	
//	/************************************** ShaderProgram ***********************************************/
//	unsigned int ShaderProgram, ShaderProgram2, VertexShader, FragmentShader;
//	VertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(VertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(VertexShader);
//	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(FragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(FragmentShader);
//
//	ShaderProgram = glCreateProgram();
//	glAttachShader(ShaderProgram, VertexShader);
//	glAttachShader(ShaderProgram, FragmentShader);
//	glLinkProgram(ShaderProgram);
//
//	glDeleteShader(FragmentShader);
//
//	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(FragmentShader, 1, &fragmentShaderSource2, NULL);
//	glCompileShader(FragmentShader);
//
//	ShaderProgram2 = glCreateProgram();
//	glAttachShader(ShaderProgram2, VertexShader);
//	glAttachShader(ShaderProgram2, FragmentShader);
//	glLinkProgram(ShaderProgram2);
//
//	glDeleteShader(FragmentShader);
//	glDeleteShader(VertexShader);
//
//	// 绘制模式，正背面都绘制+线框模式
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	/************************************** RenderLoop ***********************************************/
//	// 渲染循环，让画面在关闭窗口前一直画
//	while (!glfwWindowShouldClose(window))
//	{
//		// 处理键盘输入事件
//		processInput(window);
//
//		// ...渲染指令
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// 激活应用程序对象
//		glUseProgram(ShaderProgram);
//		// 绑定顶点数组
//		glBindVertexArray(VAO[0]);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//		
//		// 获取该shaderProgram中的uniform全局变量的位置并赋值
//		float timeValue = glfwGetTime();
//		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//		int vertexColorLocation = glGetUniformLocation(ShaderProgram2, "ourColor");
//		glUseProgram(ShaderProgram2);
//		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//
//		// 绘制图形
//		glBindVertexArray(VAO[1]);
//		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//
//		// 检查并调用事件，交换缓冲区
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	// 释放所有资源
//	glDeleteVertexArrays(1, VAO);
//	glDeleteBuffers(1, VBO);
//	glDeleteProgram(ShaderProgram);
//	glDeleteProgram(ShaderProgram2);
//
//	glfwTerminate();
//
//	return 0;
//}