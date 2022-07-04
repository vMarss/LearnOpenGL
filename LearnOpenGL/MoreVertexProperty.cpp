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

	// GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL����ǰ��Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD " << std::endl;
		return -1;
	}

	// �����ӿڣ�����ӿڱ������WindowsС���������ʾ��ȫ����Щ��ʾ���ӿ�֮��
	glViewport(0, 0, 800, 600);

	// ע�ᴰ�ڴ�С�ı�Ļص�����
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

	// ����ÿ�����������
	float vertices[] = {
	// ---- λ�� -----  ------ ��ɫ -----  -- UV --
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // ����
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // ����
	 0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // ����
	-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// ����
	 //0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // ����
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ��������λ��ֵΪ0�Ķ������ԣ�λ�ã�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// ��������λ��ֵΪ1�Ķ������ԣ���ɫ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	// ��������λ��ֵΪ2�Ķ������ԣ�UV���꣩
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

	// ����ģʽ�������涼����+�߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	/***************************************** �������� ***********************************************/
	

	// ��������
	// 1. ������Ӧ�Ŀռ䣬��ǰ���VBO/VAO����
	unsigned int texture[2];
	glGenTextures(2, texture);
	// 2. ���������
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// 3. Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 4. ����ͼƬ������ǰ�󶨵�������󸽼�����ͼƬ
	int width, height, nrChannels;
	unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// ָ������Ŀ�꣬ mipmap����, �������ʽ, �����ȸ߶�, ����Ϊ0(��ʷ��������), ͼƬԴ�ĸ�ʽ��������, ͼƬԴ
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// 5. ������Ӧ�Ķ༶��Զ����(Mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// 6. ��ԭ����ͼƬ�ڴ��ͷ�
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
		// ָ������Ŀ�꣬ mipmap����, �������ʽ, �����ȸ߶�, ����Ϊ0(��ʷ��������), ͼƬԴ�ĸ�ʽ��������, ͼƬԴ
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// 5. ������Ӧ�Ķ༶��Զ����(Mipmap)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// ����fragmentShader��ʹ�õ�����Ԫ
	ourShader.use();
	//glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	/************************************** RenderLoop ***********************************************/
	// ��Ⱦѭ�����û����ڹرմ���ǰһֱ��
	while (!glfwWindowShouldClose(window))
	{
		// ������������¼�
		processInput(window);

		// ...��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��������Ԫ����ָ���Ļ�Ĭ����0������fragmentShader�� uniform sampler2D ourTexture ���Բ�����ʽָ��
		// OpenGL һ���ṩ16������Ԫ��ʹ��(��4bits����)
		glActiveTexture(GL_TEXTURE0);
		// ������
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);

		// ���ǰ��ʹ�õ�ShaderProgram
		//glUseProgram(ShaderProgram);
		ourShader.use();
		/*float offset[] = { 0.1, 0.1, 0.1 };
		ourShader.setVec3("offset", offset);*/

		// ����ͼ��
		glBindVertexArray(VAO);

		// ��EBO
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// ���ö�������
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// ��鲢�����¼�������������
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// �ͷ�������Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteProgram(ShaderProgram);

	glfwTerminate();

	return 0;
}