#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Player;
class Monster;

class Map
{

public:

// Structures pour les A-RPGs
struct PNJ { int type, text, quest; };
struct CHEST { int type; };
struct WARPSPE { int value; };
struct BUTTON { int type; };
struct TRAP { int type; };
struct POINT { int x, y; };

//Constructeur
Map();

//Accesseurs
int getBeginX(void) const;
int getBeginY(void) const;
int getStartX(void) const;
int getStartY(void) const;
int getMaxX(void) const;
int getMaxY(void) const;
int getTile(int y, int x) const;
int getLevel(void) const;
int getNombreMonstres(void) const;
int getWarpUp(void) const;
int getWarpDown(void) const;
int getWarpLeft(void) const;
int getWarpRight(void) const;
int getWarpSP(int number) const;
int getWarpDirection(void) const;
int getWarp_coming_from_x(void) const;
int getWarp_coming_from_y(void) const;

//Mutateurs
void setLevel(int valeur);
void setStartX(int valeur);
void setStartY(int valeur);
void setTile(int y, int x, int valeur);
void setNombreMonstres(int valeur);
void setWarpDirection(int valeur);
void setWarp_coming_from_x(int valeur);
void setWarp_coming_from_y(int valeur);

//Fonctions
void loadMap(std::string filename);
void draw(int layer, sf::RenderWindow &window);
void changeLevel(void);
void testDefilement(void);


private:
//Variables de la classe en accès privé

//Numéro du tileset à utiliser
int tilesetAffiche;

/* Coordonnées de départ du héros, lorsqu'il commence le niveau */
int beginx, beginy;

/* Coordonnées de début, lorsqu'on doit dessiner la map */
int startX, startY;

/* Coordonnées max de fin de la map */
int maxX, maxY;

/* Tableau à double dimension représentant la map de tiles */
int tile[80][80];

//Deuxième couche de tiles
int tile2[80][80];

//Troisième couche de tiles
int tile3[80][80];

//Quatrième couche de tiles pour les collisions
int tile4[80][80];

/* Timer et numéro du tileset à afficher pour animer la map */
int mapTimer, tileSetNumber;

//Numéro du niveau en cours
int level;

//Variable pour testDefilement()
int testdefil;

//Nouvelles variables pour les A-RPG
int warpUp, warpDown, warpLeft, warpRight;
WARPSPE warpSP[10];
PNJ pnj[20];
CHEST chest[20];
int loot, weather;
int cinematics, cinematics_condition;
int musicNumber;
BUTTON button[10];
TRAP trap[10];

//Pour gérer les warps
int warpDirection;
int warp_coming_from_x;
int warp_coming_from_y;

//Tilesets
sf::Texture tileSet1Texture;
sf::Sprite tileSet1;
sf::Texture tileSet1BTexture;
sf::Sprite tileSet1B;

//Nombre max de monstres à l'écran
int nombreMonstres;

//Police de caractères
sf::Font font;

//HUD (Informations affichées à l'écran, comme le nombre de coeurs, la magie, etc.)
sf::Texture HUDTexture;
sf::Sprite HUD;
sf::Texture HUDHeartsTexture;
sf::Sprite HUDHearts;
sf::Texture HUDMagicTexture;
sf::Sprite HUDMagic;
float HUDtimer;
int HUDDirection;


/*******************/
/* Constantes */
/******************/

// Taille de la fenêtre : 800x480 pixels
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

/* Taille maxi de la map : 400 x 150 tiles */
const int MAX_MAP_X = 80;
const int MAX_MAP_Y = 80;

/* Taille d'une tile (32 x 32 pixels) */
const int TILE_SIZE = 32;

/* Constante pour l'animation */
const int TIME_BETWEEN_2_FRAMES = 20;

//Nombre max de monstres gérés
const int MONSTRES_MAX = 50;

//Directions
const int DOWN = 0;
const int UP = 1;
const int RIGHT = 2;
const int LEFT = 3;


/*************************/
/* VALEURS DES TILES */
/************************/

const int TILE_MONSTRE_DEBUT = 20;
const int TILE_MONSTRE_FIN = 39;

};
#endif
