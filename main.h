#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "input.h"
#include "map.h"

using namespace std;
using namespace sf;


//Fonctions
void update(Input &input,Map &map);
void draw(sf::RenderWindow &window, Map &map);


// Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
