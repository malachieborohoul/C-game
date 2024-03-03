#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>


class Input
{
    //Structures
    struct Button { bool left, right, up, down, attack, run, enter, magie; };

    public:

    //Constructeur
    Input();

    //Accesseur
    Button getButton(void) const;

    //Mutateur
    void setButton(int bouton, bool etat);

    //Fonctions
    void gestionInputs(sf::RenderWindow &window);
    void getInput(sf::RenderWindow &window);


    private:

    //Variables de la classe en accès privé
    sf::Event event;
    Button button;

    //Enum pour les boutons
    enum { up, down, right, left, attack, run, enter, magic };
};
#endif
