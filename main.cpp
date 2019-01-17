#include "stdio.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

using namespace std;

#define tailleCarreauPixel 1
#define tailleFenenetrePixel 1000
#define nbreCarreau tailleFenenetrePixel/tailleCarreauPixel
#define AffichageTemps 1

bool etat[nbreCarreau][nbreCarreau];
bool etat_nv[nbreCarreau][nbreCarreau];
bool pause = 0;
int x,y;

int nbrevoisin(int x,int y){
  int result = etat[x+1][y+1]
              +etat[x-1][y-1]
              +etat[x-1][y+1]
              +etat[x+1][y-1]
              +etat[x+1][y]
              +etat[x-1][y]
              +etat[x][y+1]
              +etat[x][y-1];
  return result;
}

void premierTirage(){

  for(int i = 0 ; i < nbreCarreau ; i ++ ){
    for(int j = 0 ; j < nbreCarreau ; j ++ ){
      etat[i][j] = rand() %2;
    }
  }

}

int main()
{
    srand(time(NULL));

    premierTirage();

    sf::RenderWindow window(sf::VideoMode(tailleFenenetrePixel,tailleFenenetrePixel), "Game Of Life");
    sf::RectangleShape shape(sf::Vector2f(tailleCarreauPixel,tailleCarreauPixel));



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
              {
                pause = !pause;
              }

        }

        window.clear();

        sf::Clock clock; // démarre le chrono

        if(!pause){

              for(int i = 0 ; i < nbreCarreau ; i ++ ){
                for(int j = 0 ; j < nbreCarreau ; j ++ ){
                      if(nbrevoisin(i,j) == 2){
                        etat_nv[i][j] = etat[i][j];
                      }else if(nbrevoisin(i,j) == 3) {
                        etat_nv[i][j] = 1;
                      }else{
                        etat_nv[i][j] = 0;
                      }
                }
              }

              for(int i = 0 ; i < nbreCarreau ; i ++ ){
                for(int j = 0 ; j < nbreCarreau ; j ++ ){
                  etat[i][j] = etat_nv[i][j];
                }
              }

              if(AffichageTemps){
                sf::Time elapsed1 = clock.getElapsedTime();
                cout << "Calcul : " << elapsed1.asSeconds() << endl;
                clock.restart();
              }

        }else{
          if (event.mouseButton.button == sf::Mouse::Left)
            {
              x = event.mouseButton.x % nbreCarreau;
              y = event.mouseButton.y % nbreCarreau;
              etat[x][y] = 0;


            }
            if (event.mouseButton.button == sf::Mouse::Right)
              {
                x = event.mouseButton.x % nbreCarreau;
                y = event.mouseButton.y % nbreCarreau;
                etat[x][y] = 1;
              }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
              {
                for(int i = 0 ; i < nbreCarreau ; i ++ ){
                  for(int j = 0 ; j < nbreCarreau ; j ++ ){
                    etat[i][j] = 0;
                  }
                }
              }



        }

        sf::VertexArray quad(sf::Quads, nbreCarreau*nbreCarreau*4);

        for(int i = 0 ; i < nbreCarreau ; i ++ ){
          for(int j = 0 ; j < nbreCarreau ; j ++ ){

            quad[0].position = sf::Vector2f(i * tailleCarreauPixel, j * tailleCarreauPixel);
            quad[1].position = sf::Vector2f(i * tailleCarreauPixel + tailleCarreauPixel, j * tailleCarreauPixel);
            quad[2].position = sf::Vector2f(i * tailleCarreauPixel + tailleCarreauPixel, j * tailleCarreauPixel + tailleCarreauPixel);
            quad[3].position = sf::Vector2f(i * tailleCarreauPixel, j * tailleCarreauPixel + tailleCarreauPixel);

            if(etat[i][j] == 1){
              for(int k = 0 ; k < 4 ; k++){
                quad[k].color = sf::Color::Green;
              }
            }else{
              for(int k = 0 ; k < 4 ; k++){
                quad[k].color = sf::Color::Black;
              }
            }
          }
        }
        window.draw(quad);



        window.display();

        if(AffichageTemps){
          sf::Time elapsed2 = clock.getElapsedTime();
          cout << "Affichage :" << elapsed2.asSeconds() << endl;
          clock.restart();
        }

    }

    return 0;
}
