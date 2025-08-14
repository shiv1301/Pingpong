#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>

using namespace sf;
using namespace std;

void centerTextOnRect(sf::Text& text, const sf::RectangleShape& rect) {
    text.setPosition(rect.getPosition());
}

int main()
{
    random_device rd;
    mt19937 gen(rd()); 
    
    std::uniform_real_distribution<> dist(-2.5, 2.5);
    std::uniform_real_distribution<> dy(0.002, 0.003);
    std::uniform_int_distribution<> distrib(0, 1);
    std::uniform_int_distribution<> di(50, 550);
    
    int xpos=di(gen);
    
    Texture texture;
    if (!texture.loadFromFile("Heart.png")) {
        return EXIT_FAILURE;
    }
    
    Sprite lost;
    lost.setTexture(texture);
    
    Vector2u textureSize = texture.getSize();
    float originalWidth = static_cast<float>(textureSize.x);
    float originalHeight = static_cast<float>(textureSize.y);
    
    float maxDimension = max(originalWidth, originalHeight);
    float scaleFactor = 35.0f / maxDimension;
    
    lost.setScale(scaleFactor, scaleFactor);
    
    Texture t;
    if (!t.loadFromFile("fill.png")) {
        return EXIT_FAILURE;
    }
    
    Sprite full;
    full.setTexture(t);
    
    Vector2u textureSiz = t.getSize();
    float originalWidt = static_cast<float>(textureSiz.x);
    float originalHeigh = static_cast<float>(textureSiz.y);
    
    float maxDimensio = max(originalWidt, originalHeigh);
    float scaleFacto = 35.0f / maxDimensio;
    
    full.setScale(scaleFacto, scaleFacto);
    
    RenderWindow window(VideoMode(600, 800), "PINGPONG");
    window.setFramerateLimit(120);
    CircleShape circle(10.f);
    circle.setFillColor(Color::Green);
    circle.setPosition(xpos, 400.f);
    
	sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        // Handle error
    }
    
    // Set window icon (appears in title bar and taskbar)
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
    RectangleShape bottomPaddle(Vector2f(100,15));
    bottomPaddle.setFillColor(Color::Yellow);
    bottomPaddle.setPosition(250.0f,750.0f);
    
    RectangleShape border(Vector2f(600,800));
    border.setFillColor(Color::White);
    border.setPosition(0,0);
    
    RectangleShape bor(Vector2f(570,730));
    bor.setFillColor(Color::Black);
    bor.setPosition(15,35);
    
    RectangleShape topPaddle(Vector2f(100,15));
    topPaddle.setPosition(250.0f,35.0f);
    topPaddle.setFillColor(Color::Red);
    
    RectangleShape bottonnot(Vector2f(200,50));
    bottonnot.setFillColor(Color::Black);
    bottonnot.setOutlineThickness(5.0f);
    bottonnot.setOutlineColor(Color::White);
    bottonnot.setOrigin(bottonnot.getSize().x / 2, bottonnot.getSize().y / 2);
    
    RectangleShape bottonyes(Vector2f(205,55));
    bottonyes.setFillColor(Color::Black);
    bottonyes.setOutlineThickness(5.0f);
    bottonyes.setOutlineColor(Color::White);
    bottonyes.setOrigin(bottonyes.getSize().x / 2, bottonyes.getSize().y / 2);
    
    int topHeart=3;
    int bottomHeart=3;
    

    float xSpeed = dist(gen);
    float ySpeed = 2.0f*(distrib(gen)-0.5);
    
    float paddleSpeed=8.0f;
    
    bool game=false;
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }
    
    Text text;
    text.setFont(font);
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, 
                  textRect.top + textRect.height/2.0f);


    while (window.isOpen())
    {
        while(!game){
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear(Color::Black);
            window.draw(border);
            window.draw(bor);
            Vector2i mousePos = Mouse::getPosition(window);
            
			text.setString("PLAY");
			text.setFillColor(sf::Color::White);
			
			FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width/2.0f, 
						  textRect.top + textRect.height/2.0f);
            if(mousePos.x>=200 && mousePos.x<=400 && mousePos.y>=375 && mousePos.y<=425){
                bottonyes.setPosition(window.getSize().x / 2, window.getSize().y / 2);
                text.setCharacterSize(50);
				
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, 
                  textRect.top + textRect.height/2.0f);
                text.setPosition(window.getSize().x / 2, window.getSize().y / 2);
				  
                window.draw(bottonyes);
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    game=true;
                }
            }
            else{
                text.setCharacterSize(45);
                bottonnot.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, 
                  textRect.top + textRect.height/2.0f);
                text.setPosition(window.getSize().x / 2, window.getSize().y / 2);
				  
                window.draw(bottonnot);
            }
            
            if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
            window.draw(text);
            window.display();
        }
        
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::A)) {
            Vector2f position = topPaddle.getPosition();
            if (position.x - paddleSpeed > 15) {
                topPaddle.move(-paddleSpeed, 0.f);
            } else {
                topPaddle.setPosition(15, position.y);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            Vector2f position = topPaddle.getPosition();
            if (position.x + paddleSpeed < 485) {
                topPaddle.move(paddleSpeed, 0.f);
            } else {
                topPaddle.setPosition(485, position.y);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            Vector2f position = bottomPaddle.getPosition();
            if (position.x - paddleSpeed > 15) {
                bottomPaddle.move(-paddleSpeed, 0.f);
            } else {
                bottomPaddle.setPosition(15, position.y);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            Vector2f position = bottomPaddle.getPosition();
            if (position.x + paddleSpeed < 485) {
                bottomPaddle.move(paddleSpeed, 0.f);
            } else {
                bottomPaddle.setPosition(485, position.y);
            }
        }

        Vector2f position = circle.getPosition();
        if (position.x <= 15 || position.x >= 555) xSpeed *= -1;
        if(ySpeed<10 && ySpeed>-10){
            if(ySpeed>=0)ySpeed +=dy(gen);
            else ySpeed-=dy(gen);
        }
        if (circle.getGlobalBounds().intersects(topPaddle.getGlobalBounds()) || 
            circle.getGlobalBounds().intersects(bottomPaddle.getGlobalBounds())){
            ySpeed *= -1;
            xSpeed += dist(gen)/2;
        }
        circle.move(xSpeed, ySpeed);
        if(position.y<=35){
            topHeart--;
            circle.setPosition(Vector2f(di(gen),400.0f));
            xSpeed = dist(gen);
            ySpeed = 2.0f*(distrib(gen)-0.5);
        }
        if(position.y>=765){
            bottomHeart--;
            circle.setPosition(Vector2f(di(gen),400.0f));
            xSpeed = dist(gen);
            ySpeed = 2.0f*(distrib(gen)-0.5);
        }
        
        if(bottomHeart==0){
            game=false;
            bottomHeart=3;
            topHeart=3;
			text.setString("Red Wins!!");
			text.setFillColor(Color::Red);
			text.setCharacterSize(75);
			
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, 
                  textRect.top + textRect.height/2.0f);
			text.setPosition(300,400);
			window.draw(text);
        window.display();
			sleep(seconds(2));
        }
		
		if(topHeart==0){
            game=false;
            bottomHeart=3;
            topHeart=3;
			text.setString("Yellow Wins!!");
			text.setFillColor(Color::Yellow);
			text.setCharacterSize(75);
			
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, 
                  textRect.top + textRect.height/2.0f);
			text.setPosition(300,400);
			window.draw(text);
        window.display();
			sleep(seconds(2));
        }

        window.clear(Color::Black);
        window.draw(border);
        window.draw(bor);
        for(int i=0;i<3-topHeart;i++){
            lost.setPosition(476+i*37,0);
            window.draw(lost);
        }
        for(int i=0;i<3-bottomHeart;i++){
            lost.setPosition(476+i*37,765);
            window.draw(lost);
        }
        for(int i=3-topHeart;i<3;i++){
            full.setPosition(476+i*37,0);
            window.draw(full);
        }
        for(int i=3-bottomHeart;i<3;i++){
            full.setPosition(476+i*37,765);
            window.draw(full);
        }
        window.draw(circle);
        window.draw(topPaddle);
        window.draw(bottomPaddle);
        
        window.display();
    }
    
    return 0;
}

//g++ -std=c++11 -IC:\msys64\ucrt64\include pingpong.cpp -o pingpong.exe -LC:\msys64\ucrt64\lib -lsfml-graphics -lsfml-window -lsfml-system