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
//	// GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL����ǰ��Ҫ��ʼ��GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD " << std::endl;
//		return -1;
//	}
//
//	// �����ӿڣ�����ӿڱ������WindowsС���������ʾ��ȫ����Щ��ʾ���ӿ�֮��
//	glViewport(0, 0, 800, 600);
//
//	// ע�ᴰ�ڴ�С�ı�Ļص�����
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	/************************************** VertexArray ***********************************************/
//	// ����һ����������������κ�����֮��Ķ������Ե��ö���洢�����VAO��
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//
//	/************************************** VertexBuffer ***********************************************/
//	// �������飬�����ظ��ģ����Բ���������
//	float vertices[] = {
//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
//	0.5f, -0.5f, 0.0f,  // ���½�
//	-0.5f, -0.5f, 0.0f, // ���½�
//	-0.5f, 0.5f, 0.0f,   // ���Ͻ�
//	0.5f, 0.5f, 0.0f,   // ���Ͻ�
//	-0.5f, -0.5f, 0.0f, // ���½�
//	};
//
//	// �������飬���ظ��ģ���Ҫ�������ʹ��
//	//float vertices[] = {
//	//0.5f, 0.5f, 0.0f,   // ���Ͻ�
//	//0.5f, -0.5f, 0.0f,  // ���½�
//	//-0.5f, -0.5f, 0.0f, // ���½�
//	//-0.5f, 0.5f, 0.0f   // ���Ͻ�
//	//};
//
//	// ����ֻ����������һ���������1��ʾ������������������õĻ�������д��VBO��
//	// ����VBO������һ��ָ�룬Ҳ������һ�����飬��������ʱ������д��������
//	unsigned int VBO;
//	glGenBuffers(1, &VBO);
//	// ��������Ļ����ڴ�ָ�룬��Ϊ��vertex buffer��ͬһʱ��ֻ��һ������ֻ�ܰ�һ�������ڴ棬ָ�������и����͵����ݽ������󶨵��ڴ�������
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// ������Ķ������ݸ��Ƶ������ڴ���
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	/************************************** ElementBuffer ***********************************************/
//	unsigned int indices[] = { // ע��������0��ʼ! 
//		0, 1, 3, // ��һ��������
//		1, 2, 3  // �ڶ���������
//	};
//
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	/************************************** VertexShader ***********************************************/
//	// ����һ��������ɫ������������ x,y,z,w���������λ���������Ϣ
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//
//	// ���������涨���Ӳ����shader
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	// �ж��Ƿ����ɹ�
//	int  success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	// ָ��vertex_shader���ȥ��ȡvertex_buffer�е����ݣ���Щ���ûᱻVAO����¼
//	// �������ܣ�(������ɫ����location�� ÿ���������ԵĴ�С�����ݵ����ͣ��Ƿ�ϣ�����ݱ���׼�������岽���� �����ڻ�������ʼλ�õ�ƫ����)
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	// ��ʾ���ö������ԣ���������Ĭ���ǽ�ֹ�ģ������Ƕ������Ե�λ��ֵ
//	glEnableVertexAttribArray(0);
//
//
//	/************************************** FragmentShader ***********************************************/
//	// ����һ��ƬԪ��ɫ������������ r,g,b,a�������ص���ɫ��͸����
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	// �ж��Ƿ����ɹ�
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	/************************************** ShaderProgram ***********************************************/
//	// ����һ��shader program
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//
//	// ��ǰ���Զ����shader�ӵ����shader program��
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	// ���ӵ�shader program��ɾ����Ӧ��shader����
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//
//	// ��ע��VAO�����ڶ���VAO���ã�����ֻ��һ��VAO��ʵ����Ҫ
//	glBindVertexArray(0);
//
//	// ����ģʽ�������涼����+�߿�ģʽ
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	/************************************** RenderLoop ***********************************************/
//	// ��Ⱦѭ�����û����ڹرմ���ǰһֱ��
//	while (!glfwWindowShouldClose(window))
//	{
//		// ������������¼�
//		processInput(window);
//
//		// ...��Ⱦָ��
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// ����Ӧ�ó������
//		glUseProgram(shaderProgram);
//		// �󶨶�������
//		glBindVertexArray(VAO);
//		// VertexΪ���ж��㣬ֱ��һ��һ�黭������
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		// VertexΪ���ظ��Ķ��㣬���Indexʹ��������
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		// ��鲢�����¼�������������
//		glfwPollEvents();
//		glfwSwapBuffers(window);
//	}
//
//	// �ͷ�������Դ
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//	glfwTerminate();
//
//	return 0;
//}