#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;
float tx = 150, ty = 70, maca1x = 150.0f, maca1y = 400;
int placar = 0, valorAleatorio = 0, falhas=0;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;
	
	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();

}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Hello Sprites", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Build and compile our shader program
	addShader("../shaders/transformations.vs", "../shaders/transformations.frag");

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

}

void SceneManager::addShader(string vFilename, string fFilename)
{
	shader = new Shader (vFilename.c_str(), fFilename.c_str());
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		tx -= 0.50;
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		tx += 0.50;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void SceneManager::resize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}


void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	else if (keys[GLFW_KEY_LEFT]) {
		if (tx - 0.50 >= 95) {
			tx -= 0.50;
		}
	}
	else if (keys[GLFW_KEY_RIGHT]) {
		if (tx + 0.50 <= 709.50) {
			tx += 0.50;
		}
	}

	//AQUI aplicaremos as transformações nos sprites
	objects[5]->setPosition(glm::vec3(tx, ty, 0.0f));

	maca1y -= 0.2f;
	objects[6]->setPosition(glm::vec3(maca1x, maca1y, 0.0f));

	if (maca1x <= (tx + 59.89) && maca1x >= (tx - 59.89) && maca1y <= 130) {
		placar += 1;
		printf("Placar: %d\n", placar);

		srand(time(NULL));
		//valorAleatorio = rand() % 701 + 70;
		valorAleatorio = rand() % 8 + 1;

		if (valorAleatorio * 100 < 770) {
			valorAleatorio *= 100;
		}
		else if (valorAleatorio == 8) {
			valorAleatorio = 70;
		}
	
		maca1x = (float)valorAleatorio ;
		maca1y = 600.0f;
		objects[6]->setPosition(glm::vec3(maca1x, maca1y, 0.0f));
	}
	else if (maca1y <= 80.0f) {
		falhas += 1;
		if (falhas >= 2) {
			printf("\n\n=================================================\n");
			printf("======================GAME OVER====================\n");
			printf("=================================================\n\n");
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		srand(time(NULL));

		valorAleatorio = rand() % 8 + 1;

		if (valorAleatorio * 100 < 770) {
			valorAleatorio *= 100;
		}
		else if (valorAleatorio == 8) {
			valorAleatorio = 70;
		}

		maca1x = (float)valorAleatorio;
		maca1y = 600.0f;
		objects[6]->setPosition(glm::vec3(maca1x, maca1y, 0.0f));
		
	}
}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	//atualiza e desenha os Sprites

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update();
		objects[i]->draw();
	}
}

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Update method(s)
		update();

		//Render scene
		render();
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}


void SceneManager::setupScene()
{
	//Criação dos Sprites iniciais -- pode-se fazer métodos de criação posteriormente
	
	//Mínimo: posicao e escala e ponteiro para o shader
	Sprite* obj = new Sprite;
	//Céu azul parte 1
	obj = new Sprite;
	obj->setPosition(glm::vec3(0.0f, 552.0f, 0.0));
	obj->setDimension(glm::vec3(800.0f, 900.0f, 1.0f));
	obj->setShader(shader);
	objects.push_back(obj); //adiciona o terceiro obj

	//Céu azul parte 2
	obj = new Sprite;
	obj->setPosition(glm::vec3(595.0f, 552.0f, 0.0));
	obj->setDimension(glm::vec3(440.0f, 900.0f, 1.0f));
	obj->setShader(shader);
	objects.push_back(obj); //adiciona o terceiro obj

	//Árvore
	obj = new Sprite;
	obj->setPosition(glm::vec3(630.0f, 260.0f, 0.0));
	obj->setDimension(glm::vec3(302.0f, 360.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shader);
	objects.push_back(obj); //adiciona o primeiro obj

	//Nuvem sozinha
	obj = new Sprite;
	obj->setPosition(glm::vec3(100.0f, 525.0f, 0.0));
	obj->setDimension(glm::vec3(200.0f, 85.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shader);
	objects.push_back(obj); //adiciona o primeiro obj

	//Nuvem sozinha direita
	obj = new Sprite;
	obj->setPosition(glm::vec3(565.0f, 525.0f, 0.0));
	obj->setDimension(glm::vec3(200.0f, 85.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shader);
	objects.push_back(obj); //adiciona o primeiro obj

	//Cesta
	obj = new Sprite;
	obj->setPosition(glm::vec3(150.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(200.0f, 200.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shader);
	objects.push_back(obj); //adiciona o primeiro obj

	//Maçã 1
	obj = new Sprite;
	obj->setPosition(glm::vec3(maca1x, maca1y, 0.0));
	obj->setDimension(glm::vec3(60.0f, 60.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shader);
	objects.push_back(obj); //adiciona o primeiro obj
	
	//Carregamento das texturas (pode ser feito intercalado na criação)
	//Futuramente, utilizar classe de materiais e armazenar dimensoes, etc
	unsigned int texID = loadTexture("../textures/ceu.png");
	objects[0]->setTexture(texID);
	objects[1]->setTexture(texID);
		
	texID = loadTexture("../textures/arvore2.png");
	objects[2]->setTexture(texID);

	texID = loadTexture("../textures/nuvemSozinha.png");
	objects[3]->setTexture(texID);
	objects[4]->setTexture(texID);

	texID = loadTexture("../textures/cesta.png");
	objects[5]->setTexture(texID);

	texID = loadTexture("../textures/maca.png");
	objects[6]->setTexture(texID);

	//Definindo a janela do mundo (ortho2D)
	ortho2D[0] = 0.0f; //xMin
	ortho2D[1] = 800.0f; //xMax
	ortho2D[2] = 0.0f; //yMin
	ortho2D[3] = 600.0f; //yMax

	//Habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D() //TO DO: parametrizar aqui
{
	float zNear = -1.0, zFar = 1.0; //estão fixos porque não precisamos mudar

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);


	//Obtendo o identificador da matriz de projeção para enviar para o shader
	GLint projLoc = glGetUniformLocation(shader->ID, "projection");
	//Enviando a matriz de projeção para o shader
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture;

	// load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	
	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glActiveTexture(GL_TEXTURE0);

	return texture;
}

