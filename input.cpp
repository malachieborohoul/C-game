#include "input.h"

using namespace std;
using namespace sf;

//Constructeur
Input::Input()
{
    button.left = button.right = button.up = button.down = button.run =
    button.attack = button.enter = button.magie = false;
}


//Accesseur
Input::Button Input::getButton(void) const { return button; }


//Mutateur
void Input::setButton(int bouton, bool etat)
{
    switch (bouton)
    {
    case up:
        button.up = etat;
        break;

    case down:
        button.down = etat;
        break;

    case right:
        button.right = etat;
        break;

    case left:
        button.left = etat;
        break;

    case attack:
        button.attack = etat;
        break;

    case run:
        button.run = etat;
        break;

    case magic:
        button.magie = etat;
        break;

    case enter:
        button.enter = etat;
        break;
    }
}


//Fonctions
void Input::gestionInputs(RenderWindow &window)
{
    //Pour l'instant, on ne g�re que le clavier.
    //On g�rera les joysticks plus tard, s'il y en a
    //un de branch�.
    //Pour l'instant, cette fonction n'est donc pas indispensable.
    getInput(window);
}


void Input::getInput(RenderWindow &window)
{

    // Tant qu'il y a des �v�nements � traiter...
    while (window.pollEvent(event))
    {
        // on regarde le type de l'�v�nement...
        switch (event.type)
        {
        // On ferme la fen�tre
        case Event::Closed:
            window.close();
            break;

        // Touche press�e
        case Event::KeyPressed:
            switch (event.key.code) // La touche qui a �t� press�e
            {
            case Keyboard::Escape: // Echap
                window.close();
                break;

            case Keyboard::X:
                button.run = true;
                break;

            case Keyboard::C:
                button.magie = true;
                break;

            case Keyboard::V:
                button.attack = true;
                break;

            case Keyboard::Left:
                button.left = true;
                break;

            case Keyboard::Right:
                button.right = true;
                break;

            case Keyboard::Down:
                button.down = true;
                break;

            case Keyboard::Up:
                button.up = true;
                break;

            case Keyboard::Return:
                button.enter = true;
                break;

            default:
                break;
            }
    break;

// Touche rel�ch�e
case Event::KeyReleased:
switch (event.key.code)
{
    case Keyboard::X:
        button.run = false;
        break;

    case Keyboard::C:
        button.magie = false;
        break;

    case Keyboard::V:
        button.attack = false;
        break;

    case Keyboard::Left:
        button.left = false;
        break;

    case Keyboard::Right:
        button.right = false;
        break;

    case Keyboard::Down:
        button.down = false;
        break;

    case Keyboard::Up:
        button.up = false;
        break;


    case Keyboard::Return:
        button.enter = false;
        break;

    default:
        break;
    }
    break;

// on ne traite pas les autres types d'�v�nements
    default:
    break;
    }
    }
    }
