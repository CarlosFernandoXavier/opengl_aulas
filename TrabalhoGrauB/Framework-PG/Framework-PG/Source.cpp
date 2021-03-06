/* Hello Transforms - c?digo inicial fornecido em https://learnopengl.com/#!Getting-started/Hello-Triangle 
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Computa??o Gr?fica - Jogos Digitais - Unisinos
 * Vers?o inicial: 7/4/2017
 * ?ltima atualiza??o em 14/03/2018
 *
 */

using namespace std;

#include "SceneManager.h"
#include <string.h>


// The MAIN function, from here we start the application and run the game loop
int main()
{
	char imagePath[364];
	printf("Digite o caminho da sua imagem:");
	scanf_s("%[^\n]363s%*", imagePath, 364);
	printf("Caminho digitado %s", imagePath);
	
	SceneManager *scene = new SceneManager;
	scene->setImage(imagePath);
	scene->initialize(800, 600);

	scene->run();

	scene->finish();
	
	return 0;
}


