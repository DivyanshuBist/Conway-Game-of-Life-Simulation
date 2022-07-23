#include<iostream>
#include <ctime>
#include <unistd.h>
#include<random>
#include <SFML/Graphics.hpp>
#define Height 705
#define Width 955

using namespace std;
int main(){
    mt19937 mt(time(nullptr));
    int thickness=1;
    int resolution=5;
    int rows=Height/(resolution+thickness);
    int cols=Width/(resolution+thickness);

    bool curr_grid[rows][cols];
    bool next_grid[rows][cols];
    for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            curr_grid[r][c]=mt()%2;
        }
    }

    sf::RenderWindow window(sf::VideoMode(Width, Height), "Game of Life!");
       while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color(128,128,128));
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(resolution, resolution));
                if(curr_grid[i][j]==0){
                    rectangle.setFillColor(sf::Color::Black);
                }
                else{
                    rectangle.setFillColor(sf::Color::White);
                }
                rectangle.setPosition(j*resolution+thickness*(j+1), i*resolution+thickness*(i+1));
                window.draw(rectangle);
            }
        }
        window.display();
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                int alive_n=0;
                alive_n+=(i!=0 && curr_grid[i-1][j]==1)?1:0;//.top
                alive_n+=(i!=0 && curr_grid[i-1][j-1]==1)?1:0;//.top left
                alive_n+=(i!=0 && curr_grid[i-1][j+1]==1)?1:0;//.top right

                alive_n+=(j!=0 && curr_grid[i][j-1]==1)?1:0;//.left
                alive_n+=(j!=0 && curr_grid[i+1][j-1]==1)?1:0;//.bottom left

                alive_n+=(j!=cols-1 && curr_grid[i][j+1]==1)?1:0;//.right
                alive_n+=(j!=cols-1 && curr_grid[i+1][j+1]==1)?1:0;//.bottom right

                alive_n+=(i!=rows-1 && curr_grid[i+1][j]==1)?1:0;//.bottom
                
                if(curr_grid[i][j]==0){
                    if(alive_n==3) next_grid[i][j]=1;
                    else{
                        next_grid[i][j]=0;
                    }
                }
                else{ //alive
                    if(alive_n<2) next_grid[i][j]=0;
                    else if(alive_n==2 or alive_n==3 ) next_grid[i][j]=1;
                    else next_grid[i][j]=0;
                }
            }
        }
        for(int r=0;r<rows;r++){
        for(int c=0;c<cols;c++){
            curr_grid[r][c]=next_grid[r][c];
            }
        }
        sleep(0.9);
    }
    return 0;
}
