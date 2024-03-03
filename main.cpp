#include "main.h"


int main(int argc, char *argv[])
{
// Création d'une fenêtre en SFML
RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),
"Meruvia - Big Tuto A-RPG/SFML2 - Chapitre 4 - www.meruvia.fr");


//On active la synchro verticale
window.setVerticalSyncEnabled(true);

//Instanciation des classes
Input input;
Map map;

//On commence au premier niveau
map.setLevel(1);
map.changeLevel();

// Boucle infinie, principale, du jeu
while (window.isOpen())
{

// Gestion des inputs
input.gestionInputs(window);

//Updates
update(input, map);

// Dessin - draw
draw(window, map);

window.display();
}

// On quitte
return 0;

}



//Fonction de mise à jour du jeu : gère la logique du jeu
void update(Input &input, Map &map)
{
map.testDefilement();
}



//Fonction de dessin du jeu : dessine tous les éléments
void draw(RenderWindow &window, Map &map)
{
//On efface tout
window.clear();

// Affiche la map de tiles : layer 2 (couche du fond)
map.draw(2, window);

// Affiche la map de tiles : layer 1 (couche active : sol, etc.)
map.draw(1, window);

// Affiche la map de tiles : layer 3 (couche en foreground / devant)
map.draw(3, window);
}
