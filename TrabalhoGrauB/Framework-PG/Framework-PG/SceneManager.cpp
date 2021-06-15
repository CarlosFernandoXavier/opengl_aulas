#include "SceneManager.h"
#include <stdio.h>

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;
//char iPath[364];
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
	
	addShader("../shaders/transformations.vs", "../shaders/pretoEBranco.frag");
	addShader("../shaders/transformations.vs", "../shaders/escalaDeCinza.frag");
	addShader("../shaders/transformations.vs", "../shaders/escalaDeCinzaComInversao.frag");
	addShader("../shaders/transformations.vs", "../shaders/inversao.frag");
	addShader("../shaders/transformations.vs", "../shaders/azulEsverdeado.frag");
	addShader("../shaders/transformations.vs", "../shaders/magenta.frag");
	addShader("../shaders/transformations.vs", "../shaders/amareloQueimado.frag");
	addShader("../shaders/transformations.vs", "../shaders/semFiltro.frag");
	

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

}

void SceneManager::addShader(string vFilename, string fFilename)
{
	Shader *shader = new Shader (vFilename.c_str(), fFilename.c_str());
	shaders.push_back(shader);
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	double posX, posY;
	glfwGetCursorPos(window, &posX, &posY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		

		if (posX >= 69 && posX <= 127 && posY >= 68 && posY <= 110) {		
			setClickedSticker(1);
		}
		else if (posX >= 68 && posX <= 127 && posY >= 120 && posY <= 171) {
			setClickedSticker(2);
		}
		else if (posX >= 68 && posX <= 127 && posY >= 182 && posY <= 225) {
			setClickedSticker(3);
		}
		else if (posX >= 68 && posX <= 127 && posY >= 234 && posY <= 283) {
			setClickedSticker(4);
		}
		else if (posX >= 68 && posX <= 127 && posY >= 292 && posY <= 331) {
			setClickedSticker(5);
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
		posX >= 250 && posX <= 547 && posY >= 51 && posY <= 348) {

		if (clickedSticker == 1) {

			//std::cout << "(x,y) coordinates are when clicked: " << posX << " " << posY << std::endl;
			int unsigned texID = loadTexture("../textures/bola.png");
			Sprite* obj = new Sprite;
			obj = new Sprite;
			obj->setPosition(glm::vec3(posX, height - posY, 0.0));
			obj->setDimension(glm::vec3(40.0f, 39.75f, 1.0f)); 
			obj->setShader(shaders[7]);
			obj->setTexture(texID);
			objects.push_back(obj); 
			setClickedSticker(0);
		}
		else if (clickedSticker == 2) {
			int unsigned texID = loadTexture("../textures/copo.png");
			Sprite* obj = new Sprite;
			obj = new Sprite;
			obj->setPosition(glm::vec3(posX, height - posY, 0.0));
			obj->setDimension(glm::vec3(80.0f, 83.18f, 1.0f)); 
			obj->setShader(shaders[7]);
			obj->setTexture(texID);
			objects.push_back(obj); 
			setClickedSticker(0);
		}
		else if (clickedSticker == 3) {
			int unsigned texID = loadTexture("../textures/coracao.png");
			Sprite* obj = new Sprite;
			obj = new Sprite;
			obj->setPosition(glm::vec3(posX, height - posY, 0.0));
			obj->setDimension(glm::vec3(80.0f, 53.67f, 1.0f));
			obj->setShader(shaders[7]);
			obj->setTexture(texID);
			objects.push_back(obj); 
			setClickedSticker(0);
		}
		else if (clickedSticker == 4) {
			int unsigned texID = loadTexture("../textures/skate.png");
			Sprite* obj = new Sprite;
			obj = new Sprite;
			obj->setPosition(glm::vec3(posX, height - posY, 0.0));
			obj->setDimension(glm::vec3(80.0f, 78.92f, 1.0f));
			obj->setShader(shaders[7]);
			obj->setTexture(texID);
			objects.push_back(obj); 
			setClickedSticker(0);
		}
		else if (clickedSticker == 5) {
			int unsigned texID = loadTexture("../textures/disco.png");
			Sprite* obj = new Sprite;
			obj = new Sprite;
			obj->setPosition(glm::vec3(posX, height - posY, 0.0));
			obj->setDimension(glm::vec3(80.0f, 46.56f, 1.0f));
			obj->setShader(shaders[7]);
			obj->setTexture(texID);
			objects.push_back(obj); 
			setClickedSticker(0);
		}
	}
	

	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		
		if (posX >= 1 && posX <= 99 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[0]);

		} else if (posX >= 101 && posX <= 199 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[1]);

		} else if (posX >= 201 && posX <= 299 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[2]);

		} else if (posX >= 301 && posX <= 399 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[3]);

		} else if (posX >=401 && posX <= 499 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[4]);

		} else if (posX >= 501 && posX <= 599 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[5]);

		} else if (posX >= 601 && posX <= 699 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[6]);

		} else if (posX >= 701 && posX <= 799 && posY >= 449 && posY <= 547) {
			objects[8]->setShader(shaders[7]);
		}
	}
}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
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
	obj->setPosition(glm::vec3(50, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj); 

	printf("\nValor da imagePath: %s", imagePath);
	unsigned int texID = loadTexture(imagePath);
	objects[0]->setTexture(texID);

	
	obj = new Sprite;
	obj->setPosition(glm::vec3(150, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f)); 
	obj->setShader(shaders[1]);
	objects.push_back(obj); 
	objects[1]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(250, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f)); 
	obj->setShader(shaders[2]);
	objects.push_back(obj); 
	objects[2]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(350, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f)); 
	obj->setShader(shaders[3]);
	objects.push_back(obj); 
	objects[3]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(450, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f)); 
	obj->setShader(shaders[4]);
	objects.push_back(obj); 
	objects[4]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(550, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f)); 
	obj->setShader(shaders[5]);
	objects.push_back(obj); 
	objects[5]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(650, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[6]);
	objects.push_back(obj); 
	objects[6]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(750, 100.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[7]);
	objects.push_back(obj); 
	objects[7]->setTexture(texID);

	obj = new Sprite;
	obj->setPosition(glm::vec3(400, 400.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 300.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shaders[7]);
	objects.push_back(obj); //adiciona o primeiro obj
	objects[8]->setTexture(texID);

	texID = loadTexture("../textures/stickers.png");
	obj = new Sprite;
	obj->setPosition(glm::vec3(100, 400.0f, 0.0));
	obj->setDimension(glm::vec3(75.0f, 278.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shaders[7]);
	objects.push_back(obj); //adiciona o primeiro obj
	objects[9]->setTexture(texID);

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
	for (int indice = 0; indice < shaders.size(); indice++) {
		shaders[indice] -> Use();
		GLint projLoc = glGetUniformLocation(shaders[indice]->ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}
	
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


void SceneManager::setImage(char path[364]) {
	for (int i = 0; i < 364; i++) {
		imagePath[i] = path[i];
	}
}

void SceneManager::setClickedSticker(int sticker) {
	clickedSticker = sticker;
	
}

