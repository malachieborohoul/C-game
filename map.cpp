#include "map.h"

using namespace std;
using namespace sf;

//Constructeur
Map::Map()
{
//Chargement des ressources graphiques
//Chargement des 2 tilesets n°1
if (!tileSet1Texture.loadFromFile("graphics/tileset1.png"))
{
// Erreur
cout << "Erreur durant le chargement de l'image du tileset 1." << endl;
}
else
tileSet1.setTexture(tileSet1Texture);

if (!tileSet1BTexture.loadFromFile("graphics/tileset1b.png"))
{
// Erreur
cout << "Erreur durant le chargement de l'image du tileset 1b." << endl;
}
else
tileSet1B.setTexture(tileSet1BTexture);

//Chargement de la police Gentium
if (!font.loadFromFile("font/GenBasB.ttf"))
{
// Erreur
cout << "Erreur durant le chargement de la police." << endl;
}

//Chargement du HUD
if (!HUDTexture.loadFromFile("graphics/HUD.png"))
{
// Erreur
cout << "Erreur durant le chargement de l'image du HUD." << endl;
}
else
HUD.setTexture(HUDTexture);

if (!HUDMagicTexture.loadFromFile("graphics/energy.png"))
{
// Erreur
cout << "Erreur durant le chargement de l'image du HUD Magic." << endl;
}
else
HUDMagic.setTexture(HUDMagicTexture);

if (!HUDHeartsTexture.loadFromFile("graphics/life.png"))
{
// Erreur
cout << "Erreur durant le chargement de l'image du HUD Vies." << endl;
}
else
HUDHearts.setTexture(HUDHeartsTexture);


//Autres variables
mapTimer = TIME_BETWEEN_2_FRAMES * 3;
tileSetNumber = 0;
testdefil = 0;
level = 1;
startX = startY = 0;
warpDirection = warp_coming_from_x = warp_coming_from_y = 0;
HUDtimer = 3;
HUDDirection = DOWN;
}


//Accesseurs
int Map::getBeginX(void) const { return beginx; }
int Map::getBeginY(void) const { return beginy; }
int Map::getStartX(void) const { return startX; }
int Map::getStartY(void) const { return startY; }
int Map::getMaxX(void) const { return maxX; }
int Map::getMaxY(void) const { return maxY; }
int Map::getTile(int y, int x) const { return tile4[y][x]; }
int Map::getLevel(void) const { return level; }
int Map::getNombreMonstres(void) const { return nombreMonstres; }
int Map::getWarpUp(void) const { return warpUp; }
int Map::getWarpDown(void) const { return warpDown; }
int Map::getWarpLeft(void) const { return warpLeft; }
int Map::getWarpRight(void) const { return warpRight; }
int Map::getWarpSP(int number) const { return warpSP[number].value; }
int Map::getWarpDirection(void) const { return warpDirection; }
int Map::getWarp_coming_from_x(void) const { return warp_coming_from_x; }
int Map::getWarp_coming_from_y(void) const { return warp_coming_from_y; }


//Mutateurs
void Map::setLevel(int valeur) { level = valeur; }
void Map::setStartX(int valeur) { startX = valeur; }
void Map::setStartY(int valeur) { startY = valeur; }
void Map::setTile(int y, int x, int valeur) { tile[y][x] = valeur; }
void Map::setNombreMonstres(int valeur) { nombreMonstres = valeur; }
void Map::setWarpDirection(int valeur) { warpDirection = valeur; }
void Map::setWarp_coming_from_x(int valeur) { warp_coming_from_x = valeur; }
void Map::setWarp_coming_from_y(int valeur) { warp_coming_from_y = valeur; }


//Fonctions

void Map::changeLevel(void)
{
string filename;
filename = "map/map" + to_string(level) + ".txt";
loadMap(filename);
}


void Map::draw(int layer, RenderWindow &window)
{
int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

/* On initialise mapX à la 1ère colonne qu'on doit blitter.
Celle-ci correspond au x de la map (en pixels) divisés par la taille d'une tile (32)
pour obtenir la bonne colonne de notre map
Exemple : si x du début de la map = 1026, on fait 1026 / 32
et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
mapX = startX / TILE_SIZE;

/* Coordonnées de départ pour l'affichage de la map : permet
de déterminer à quels coordonnées blitter la 1ère colonne de tiles au pixel près
(par exemple, si la 1ère colonne n'est visible qu'en partie, on devra commencer à blitter
hors écran, donc avoir des coordonnées négatives - d'où le -1). */
x1 = (startX % TILE_SIZE) * -1;

/* Calcul des coordonnées de la fin de la map : jusqu'où doit-on blitter ?
Logiquement, on doit aller à x1 (départ) + SCREEN_WIDTH (la largeur de l'écran).
Mais si on a commencé à blitter en dehors de l'écran la première colonne, il
va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
if(x1 != 0)
x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forcément, c'est plus long ;)*/
x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

/* On fait exactement pareil pour calculer y */
mapY = startY / TILE_SIZE;
y1 = (startY % TILE_SIZE) * -1;
y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


//On met en place un timer pour animer la map
if (mapTimer <= 0)
{
if (tileSetNumber == 0)
{
tileSetNumber = 1;
mapTimer = TIME_BETWEEN_2_FRAMES * 3;
}
else
{
tileSetNumber = 0;
mapTimer = TIME_BETWEEN_2_FRAMES * 3;
}

}
else
mapTimer--;


/* Dessine la carte en commençant par startX et startY */

/* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
de tile (qui fait 32 pixels de hauteur) */
if (layer == 1)
{
for (y = y1; y < y2; y += TILE_SIZE)
{
/* A chaque début de ligne, on réinitialise mapX qui contient la colonne
(0 au début puisqu'on ne scrolle pas) */
mapX = startX / TILE_SIZE;

/* A chaque colonne de tile, on dessine la bonne tile en allant
de x = 0 à x = 640 */
for (x = x1; x < x2; x += TILE_SIZE)
{
/* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
de la tile */
a = tile[mapY][mapX];

/* Calcul pour obtenir son y (pour un tileset de 10 tiles
par ligne, d'où le 10 */
ysource = a / 10 * TILE_SIZE;
/* Et son x */
xsource = a % 10 * TILE_SIZE;

/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
if (tileSetNumber == 0)
{
tileSet1.setPosition(Vector2f(x, y));
tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
window.draw(tileSet1);
}
else
{
tileSet1B.setPosition(Vector2f(x, y));
tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
window.draw(tileSet1B);
}

mapX++;
}

mapY++;
}
}

else if (layer == 2)
{
//Deuxième couche de tiles ;)
for (y = y1; y < y2; y += TILE_SIZE)
{
mapX = startX / TILE_SIZE;

for (x = x1; x < x2; x += TILE_SIZE)
{
/* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
de la tile */
a = tile2[mapY][mapX];

/* Calcul pour obtenir son y (pour un tileset de 10 tiles
par ligne, d'où le 10 */
ysource = a / 10 * TILE_SIZE;
/* Et son x */
xsource = a % 10 * TILE_SIZE;

/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
if (tileSetNumber == 0)
{
tileSet1.setPosition(Vector2f(x, y));
tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
window.draw(tileSet1);
}
else
{
tileSet1B.setPosition(Vector2f(x, y));
tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
window.draw(tileSet1B);
}

mapX++;
}

mapY++;
}
}

else if (layer == 3)
{
//Troisième couche de tiles ;)
for (y = y1; y < y2; y += TILE_SIZE)
{
mapX = startX / TILE_SIZE;

for (x = x1; x < x2; x += TILE_SIZE)
{
/* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
de la tile */
a = tile3[mapY][mapX];

/* Calcul pour obtenir son y (pour un tileset de 10 tiles
par ligne, d'où le 10 */
ysource = a / 10 * TILE_SIZE;
/* Et son x */
xsource = a % 10 * TILE_SIZE;

/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
if (tileSetNumber == 0)
{
tileSet1.setPosition(Vector2f(x, y));
tileSet1.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
window.draw(tileSet1);
}
else
{
tileSet1B.setPosition(Vector2f(x, y));
tileSet1B.setTextureRect(sf::IntRect(xsource, ysource, TILE_SIZE, TILE_SIZE));
window.draw(tileSet1B);
}

mapX++;
}

mapY++;
}
}
}



void Map::testDefilement(void)
{
//Test de défilement de la map


//On commence à faire défiler vers la droite (valeur == 0)
if (testdefil == 0)
{
//Tant que le début du blittage de la map est inférieur aux coordonnées
//en X de la fin de la map (- la largeur de l'écran pour ne pas afficher
//du noir), on fait défiler la map.
if (startX < maxX - SCREEN_WIDTH)
//Vous pouvez changer cette valeur pour faire défiler la map plus ou moins vite
startX += 2;
else
testdefil = 1;
}
//Une fois au bout, on fait défiler vers le bas (valeur == 1)
else if (testdefil == 1)
{
if (startY < maxY - SCREEN_HEIGHT)
//Vous pouvez changer cette valeur pour faire défiler la map plus ou moins vite
startY += 2;
else
testdefil = 2;
}
//Une fois en bas, on fait défiler vers la gauche (valeur == 2)
else if (testdefil == 2)
{
if (startX > 0)
//Vous pouvez changer cette valeur pour faire défiler la map plus ou moins vite
startX -= 2;
else
testdefil = 3;
}
//Puis on remonte au point de départ (valeur == 3) et on recommence
else if (testdefil == 3)
{
if (startY > 0)
//Vous pouvez changer cette valeur pour faire défiler la map plus ou moins vite
startY -= 2;
else
testdefil = 0;
}
}



void Map::loadMap(string filename)
{
//On crée un flux (stream) pour lire notre fichier
//x et y nous serviront pour les boucles ci-dessous
fstream fin;
int x = 0;
int y = 0;

//On réinitialise maxX et maxY qui nous permettront de
//déterminer la taille de notre map
maxX = 0;
maxY = 0;

//On crée un vecteur en 2 dimensions (un vecteur de vecteurs, quoi)
vector < vector < int > > lignes;

//On crée un vecteur temporaire pour lire une ligne
vector < int > myVectData;

//On crée des chaînes de caractères temporaires
string strBuf, strTmp;

//On crée un stringstream pour gérer nos chaînes
stringstream iostr;

//On ouvre le fichier
fin.open(filename, fstream::in);

//Si on échoue, on fait une erreur
if (!fin.is_open())
{
cerr << "Erreur de chargement du fichier.\n";
exit(1);
}

//On lit notre fichier jusqu'à la fin (eof = end of file)
while (!fin.eof())
{
//On récupère la ligne dans la chaîne strBuf
getline(fin, strBuf);

//Si la ligne est vide, on continue la boucle
if (!strBuf.size())
continue;

//Sinon on poursuit et on réinitialise notre stringstream
iostr.clear();

//On y envoie le contenu du buffer strBuf
iostr.str(strBuf);

//On réinitialise le vecteur ligne
myVectData.clear();

//On boucle pour lire chaque numéro de tile du fichier map
while (true)
{
//Pour chaque ligne on récupère le numéro de la tile, en
//les parsant grâce aux espaces qui les séparent (' ')
getline(iostr, strTmp, ' ');

//On récupère ce numéro dans dans notre vecteur ligne
myVectData.push_back(atoi(strTmp.c_str()));

//Si on a fini, on quitte la boucle
if (!iostr.good()) break;
}

//Si le vecteur ligne n'est pas vide, on l'envoie dans notre vecteur à 2 dimensions
if (myVectData.size())
lignes.push_back(myVectData);
}

//On ferme le fichier
fin.close();

//On va maintenant remplir les variables de notre classe à l'aide de notre vecteur
//à 2 dimensions temporaire.
//On commence par récupérer les 3 premières valeurs de la 1ère ligne (0)
//qui sont les valeurs de départ du héros et du tileset à afficher
beginx = lignes[0][0];

beginy = lignes[0][1];

tilesetAffiche = lignes[0][2];

//On charge ensuite la première ligne individuellement car elle contient + de données
//(décalage de 3 numéros à cause des 3 précédents)
for (x = 3; x < MAX_MAP_X + 3; x++)
{
tile[y][x - 3] = lignes[y][x];
}

//Puis on charge le reste du tableau de tiles pour la couche 1.
//On boucle jusqu'à MAX_MAP_Y et MAX_MAP_X, soit les dimensions
//maxi de la map (400 x 150 tiles, pour rappel)
for (y = 1; y < MAX_MAP_Y; y++)
{
for (x = 0; x < MAX_MAP_X; x++)
{
//On copie la valeur de notre vecteur temporaire
//dans notre tableau à deux dimensions
tile[y][x] = lignes[y][x];

//On détecte si la tile n'est pas vide
if (tile[y][x] > 0)
{
//Si c'est la cas, on augmente la valeur de maxX ou
//maxY car la map n'est pas encore finie.
if (x > maxX)
{
maxX = x;
}

if (y > maxY)
{
maxY = y;
}
}
}
}

//On fait la même chose pour la seconde couche de tiles :
for (y = 0; y < MAX_MAP_Y; y++)
{
for (x = 0; x < MAX_MAP_X; x++)
{
tile2[y][x] = lignes[y + MAX_MAP_Y][x];
}
}

//Puis pour la troisième :
for (y = 0; y < MAX_MAP_Y; y++)
{
for (x = 0; x < MAX_MAP_X; x++)
{
tile3[y][x] = lignes[y + MAX_MAP_Y * 2][x];
}
}

//Et enfin pour la quatrième (la couche des collisions
//et des tiles spéciales) :
for (y = 0; y < MAX_MAP_Y; y++)
{
for (x = 0; x < MAX_MAP_X; x++)
{
tile4[y][x] = lignes[y + MAX_MAP_Y * 3][x];
}
}



//On charge les variables supplémentaires
y = MAX_MAP_Y * 4;

warpUp = lignes[y][0];
warpDown = lignes[y][1];
warpLeft = lignes[y][2];
warpRight = lignes[y][3];

for (int i = 0; i < 10; i++)
{
warpSP[i].value = lignes[y][i + 4];
}

for (int i = 0; i < 20; i++)
{
pnj[i].type = lignes[y][14 + i * 3];
pnj[i].text = lignes[y][15 + i * 3];
pnj[i].quest = lignes[y][16 + i * 3];
}

for (int i = 0; i < 20; i++)
{
chest[i].type = lignes[y][74 + i];
}

loot = lignes[y][94];
weather = lignes[y][95];
cinematics = lignes[y][96];
cinematics_condition = lignes[y][97];
musicNumber = lignes[y][98];

for (int i = 0; i < 10; i++)
{
button[i].type = lignes[y][99 + i];
}

for (int i = 0; i < 10; i++)
{
trap[i].type = lignes[y][109 + i];
}


//On convertit les dimensions max de notre map en pixels, en ajoutant
//1 (car on commence à la ligne/colonne 0) et en multipliant par la valeur
//en pixels d'une tile (32 pixels).
maxX = (maxX + 1) * TILE_SIZE;
maxY = (maxY + 1) * TILE_SIZE;
}
