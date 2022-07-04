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
//	/************************************** VertexArray ***********************************************/
//	// 创建一个顶点属性配置项，任何在其之后的顶点属性调用都会存储在这个VAO中
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//
//	/************************************** VertexBuffer ***********************************************/
//	// 顶点数组，不带重复的，可以不适用索引
//	float vertices[] = {
//	0.5f, 0.5f, 0.0f,   // 右上角
//	0.5f, -0.5f, 0.0f,  // 右下角
//	-0.5f, -0.5f, 0.0f, // 左下角
//	-0.5f, 0.5f, 0.0f,   // 左上角
//	0.5f, 0.5f, 0.0f,   // 右上角
//	-0.5f, -0.5f, 0.0f, // 左下角
//	};
//
//	// 顶点数组，带重复的，需要配合索引使用
//	//float vertices[] = {
//	//0.5f, 0.5f, 0.0f,   // 右上角
//	//0.5f, -0.5f, 0.0f,  // 右下角
//	//-0.5f, -0.5f, 0.0f, // 左下角
//	//-0.5f, 0.5f, 0.0f   // 左上角
//	//};
//
//	// 仅仅只是请求生成一个缓冲对象，1表示缓冲对象的数量，分配好的缓冲对象会写到VBO中
//	// 这里VBO传的是一个指针，也可以是一个数组，当申请多个时会依次写到数组内
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	// 将该申请的缓冲内存指针，绑定为是vertex buffer，同一时间只能一个类型只能绑定一个缓冲内存，指定后所有该类型的数据将走所绑定的内存来传输
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// 将上面的顶点数据复制到缓冲内存中
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	/************************************** ElementBuffer ***********************************************/
//	unsigned int indices[] = { // 注意索引从0开始! 
//		0, 1, 3, // 第一个三角形
//		1, 2, 3  // 第二个三角形
//	};
//
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	/************************************** VertexShader ***********************************************/
//	// 创建一个顶点着色器对象，最后输出 x,y,z,w，即顶点的位置与深度信息
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	// 编译最上面定义的硬编码shader
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	// 判断是否编译成功
//	int  success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// 指定vertex_shader如何去读取vertex_buffer中的数据，这些配置会被VAO所记录
//	// 参数介绍：(顶点着色器的location， 每个顶点属性的大小，数据的类型，是否希望数据被标准化，定义步长， 数据在缓冲中起始位置的偏移量)
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	// 表示启用顶点属性，顶点属性默认是禁止的，参数是顶点属性的位置值
//	glEnableVertexAttribArray(0);
//
//
//	/************************************** FragmentShader ***********************************************/
//	// 创建一个片元着色器对象，最后输出 r,g,b,a，即像素的颜色与透明度
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	// 判断是否编译成功
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	/************************************** ShaderProgram ***********************************************/
//	// 创建一个shader program
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//
//	// 将前面自定义的shader加到这个shader program中
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	// 链接到shader program后删除对应的shader对象
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//
//	// 解注册VAO，用于多组VAO配置，这里只有一个VAO其实不需要
//	glBindVertexArray(0);
//
//	// 绘制模式，正背面都绘制+线框模式
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
//		glUseProgram(shaderProgram);
//		// 绑定顶点数组
//		glBindVertexArray(VAO);
//		// Vertex为所有顶点，直接一组一组画三角形
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		// Vertex为不重复的顶点，配合Index使用来绘制
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		// 检查并调用事件，交换缓冲区
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	// 释放所有资源
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//	glfwTerminate();
//
//	return 0;
//}