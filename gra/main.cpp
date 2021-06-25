#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <time.h>

//#include <stdlib.h>
//#include <stdio.h>
//#include <math.h>

//using namespace std;
//using namespace sf;

class Bullet {
public:
    Bullet(sf::Vector2f size) {
        bullet.setSize(size);
        bullet.setFillColor(sf::Color::Red);
    }

    void setPos(sf::Vector2f newPos) { bullet.setPosition(newPos); }
    void setnewColorW(){ bullet.setFillColor(sf::Color::White); }
    void draw(sf::RenderWindow &window) { window.draw(bullet); }

    void fire(float speed) { bullet.move(0,-speed); }
    void fire2(float speed) { bullet.move(0,speed); }

    int getR() { return bullet.getPosition().x + bullet.getSize().x; }
    int getL() { return bullet.getPosition().x; }
    int getT() { return bullet.getPosition().y; }
    int getB() { return bullet.getPosition().y + bullet.getSize().y; }

    /*
    void del(std::vector <Bullet> vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        if(vec[i].getB() < -50) {
            vec[i].setPos(sf::Vector2f(10,10));
            std::cout << "kula usunieta/n";
        }}}
*/

private:
    sf::RectangleShape bullet;
};


class Enemy {
public:
    Enemy(sf::Vector2f size) {
        enemy.setSize(size);
        enemyTexture.loadFromFile(".\\textures\\player_texture.jpg");
        enemy.setTexture(&enemyTexture);//uvs.png
        //enemy.setFillColor(sf::Color::Blue);
    }

    void setPos(sf::Vector2f newPos) { enemy.setPosition(newPos); }
    void draw(sf::RenderWindow &window) { window.draw(enemy); }

    //void fire2(float speed) { bullet.move(0,speed); }

    void moveright() { enemy.move(0.05,0); }
    void moveleft() { enemy.move(-0.05,0); }
    void movedown() { enemy.move(0,30); }

    int getR() { return enemy.getPosition().x + enemy.getSize().x; }
    int getL() { return enemy.getPosition().x; }
    int getT() { return enemy.getPosition().y; }
    int getB() { return enemy.getPosition().y + enemy.getSize().y; }
    int getsizex() { return enemy.getSize().x; }

    bool checkColl(Bullet bullet) {
        int positionx = enemy.getPosition().x;
        if(enemy.getPosition().x < bullet.getL() &&
                enemy.getPosition().x + enemy.getSize().x > bullet.getR() &&
                enemy.getPosition().y + enemy.getSize().y > bullet.getT() &&
                enemy.getPosition().y < bullet.getT()) {
            enemy.setFillColor(sf::Color::Transparent);
            enemy.setPosition(sf::Vector2f(positionx, 1000));
            //std::cout << "enemy left\n";
            return true; } }

private:
    sf::RectangleShape enemy;
    sf::Texture enemyTexture;
};

class Block {
public:
    Block(sf::Vector2f size){
        block.setSize(size);
        blockTexture.loadFromFile(".\\textures\\block_texture.png");
        block.setTexture(&blockTexture);
        //block.setFillColor(sf::Color::Green);
    }

    void setNewSize(sf::Vector2f new_size){ block.setSize(new_size); }

    void setPos(sf::Vector2f newPos) { block.setPosition(newPos); }
    void draw(sf::RenderWindow &window) { window.draw(block); }

    int getR() { return block.getPosition().x + block.getSize().x; }
    int getL() { return block.getPosition().x; }
    int getT() { return block.getPosition().y; }
    int getB() { return block.getPosition().y + block.getSize().y; }

    bool checkColl(Bullet bullet) {
        if(block.getPosition().x < bullet.getL() &&
                block.getPosition().x + block.getSize().x > bullet.getR() &&
                block.getPosition().y + block.getSize().y > bullet.getT() &&
                block.getPosition().y < bullet.getT()) {
            block.setPosition(sf::Vector2f(-100, 1000));
            return true; } }

private:
    sf::RectangleShape block;
    sf::Texture blockTexture;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    float wspx=1000;
    float wspy=800;
    sf::RenderWindow window(sf::VideoMode(wspx, wspy), "My window");
/*
    sf::Texture background_texture;
    background_texture.loadFromFile(".\\textures\\background_texture.jpg");
    sf::Sprite set_background_texture(background_texture);
  */
    //sf::Sprite set_background_texture(background_texture);

    window.setKeyRepeatEnabled(false);

    //sf::Music music;
    //music.openFromFile("Warm-Memories-Emotional-Inspiring-Piano.mp3");
    //music.openFromFile("Warm-Memories-Emotional-Inspiring-Piano_v2.wav");
    //music.openFromFile("laser_gun.mp3");
    //music.play();

    bool move_right = true;
    int imps=0;
    int player_health=3;
    std::cout << "player health: " << player_health << "\n";
    int player_score=0;
    std::cout << "player score: " << player_score << "\n";


    // player
    float recx=80.0;
    float recy=80.0;
    sf::RectangleShape rec(sf::Vector2f(recx, recy));
    rec.setPosition(wspx/2, wspy - 120);
    sf::Texture playerTexture;
    //playerTexture.loadFromFile(".\\textures\\player_texture.jpg");
    playerTexture.loadFromFile(".\\textures\\playe_texture_new.png");
    rec.setTexture(&playerTexture);

    // black box
    sf::RectangleShape black_box(sf::Vector2f(180,80));
    black_box.setPosition(sf::Vector2f(0.0,0.0));
    black_box.setFillColor(sf::Color::Black);

    // blocks
    std::vector<Block> blockVec;

    Block newblock1(sf::Vector2f(50,50));
    newblock1.setPos(sf::Vector2f(100,wspy-200));
    blockVec.push_back(newblock1);

    Block newblock2(sf::Vector2f(50,50));
    newblock2.setPos(sf::Vector2f(350,wspy-200));
    blockVec.push_back(newblock2);

    Block newblock3(sf::Vector2f(50,50));
    newblock3.setPos(sf::Vector2f(600,wspy-200));
    blockVec.push_back(newblock3);

    Block newblock4(sf::Vector2f(50,50));
    newblock4.setPos(sf::Vector2f(850,wspy-200));
    blockVec.push_back(newblock4);

    sf::Clock clock;

    sf::Font font_start;
    font_start.loadFromFile(".\\fonts\\Plane_Crash.ttf");

    sf::Font font;
    font.loadFromFile(".\\fonts\\good_times_rg.ttf");

    // score and health font
    sf::Text score_text;
    score_text.setFont(font);
    score_text.setString("SCORE: ");
    score_text.setCharacterSize(20);
    score_text.setStyle(sf::Text::Regular);
    score_text.setFillColor(sf::Color::Red);
    score_text.setPosition(sf::Vector2f(15,10));

    sf::Text score_text_update;
    score_text_update.setFont(font);
    score_text_update.setString(std::to_string(player_score));
    score_text_update.setCharacterSize(20);
    score_text_update.setStyle(sf::Text::Regular);
    score_text_update.setFillColor(sf::Color::Red);
    score_text_update.setPosition(sf::Vector2f(115,10));

    sf::Text health_text;
    health_text.setFont(font);
    health_text.setString("HEALTH: ");
    health_text.setCharacterSize(20);
    health_text.setStyle(sf::Text::Regular);
    health_text.setFillColor(sf::Color::Green);
    health_text.setPosition(sf::Vector2f(15,40));

    sf::Text health_text_update;
    health_text_update.setFont(font);
    health_text_update.setString(std::to_string(player_health));
    health_text_update.setCharacterSize(20);
    health_text_update.setStyle(sf::Text::Regular);
    health_text_update.setFillColor(sf::Color::Green);
    health_text_update.setPosition(sf::Vector2f(125,40));

    std::vector<Bullet> bulletVec;
    std::vector<Bullet> bulletVec2;

    std::vector<Enemy> enemyVec;
/*
    Enemy newenemy1(sf::Vector2f(50,50)); // left
    newenemy1.setPos(sf::Vector2f(wspx/2-wspx/5-newenemy1.getsizex()/2, 100));
    enemyVec.push_back(newenemy1);

    Enemy newenemy2(sf::Vector2f(50,50));  // middle
    newenemy2.setPos(sf::Vector2f(wspx/2-newenemy2.getsizex()/2, 100));
    enemyVec.push_back(newenemy2);

    Enemy newenemy3(sf::Vector2f(50,50));  // right
    newenemy3.setPos(sf::Vector2f(wspx/2+wspx/5-newenemy3.getsizex()/2, 100));
    enemyVec.push_back(newenemy3);
*/

    Enemy newenemy1(sf::Vector2f(50,50));
    newenemy1.setPos(sf::Vector2f(200-newenemy1.getsizex()/2, 100));
    enemyVec.push_back(newenemy1);

    Enemy newenemy2(sf::Vector2f(50,50));
    newenemy2.setPos(sf::Vector2f(350-newenemy2.getsizex()/2, 100));
    enemyVec.push_back(newenemy2);

    Enemy newenemy3(sf::Vector2f(50,50));
    newenemy3.setPos(sf::Vector2f(500-newenemy3.getsizex()/2, 100));
    enemyVec.push_back(newenemy3);

    Enemy newenemy4(sf::Vector2f(50,50));
    newenemy4.setPos(sf::Vector2f(650-newenemy4.getsizex()/2, 100));
    enemyVec.push_back(newenemy4);

    Enemy newenemy5(sf::Vector2f(50,50));
    newenemy5.setPos(sf::Vector2f(800-newenemy5.getsizex()/2, 100));
    enemyVec.push_back(newenemy5);

    Enemy newenemy6(sf::Vector2f(50,50));
    newenemy6.setPos(sf::Vector2f(200-newenemy6.getsizex()/2, 200));
    enemyVec.push_back(newenemy6);

    Enemy newenemy7(sf::Vector2f(50,50));
    newenemy7.setPos(sf::Vector2f(350-newenemy7.getsizex()/2, 200));
    enemyVec.push_back(newenemy7);

    Enemy newenemy8(sf::Vector2f(50,50));
    newenemy8.setPos(sf::Vector2f(500-newenemy8.getsizex()/2, 200));
    enemyVec.push_back(newenemy8);

    Enemy newenemy9(sf::Vector2f(50,50));
    newenemy9.setPos(sf::Vector2f(650-newenemy9.getsizex()/2, 200));
    enemyVec.push_back(newenemy9);

    Enemy newenemy10(sf::Vector2f(50,50));
    newenemy10.setPos(sf::Vector2f(800-newenemy10.getsizex()/2, 200));
    enemyVec.push_back(newenemy10);

    Enemy newenemy11(sf::Vector2f(50,50));
    newenemy11.setPos(sf::Vector2f(200-newenemy11.getsizex()/2, 300));
    enemyVec.push_back(newenemy11);

    Enemy newenemy12(sf::Vector2f(50,50));
    newenemy12.setPos(sf::Vector2f(350-newenemy12.getsizex()/2, 300));
    enemyVec.push_back(newenemy12);

    Enemy newenemy13(sf::Vector2f(50,50));  // right
    newenemy13.setPos(sf::Vector2f(500-newenemy13.getsizex()/2, 300));
    enemyVec.push_back(newenemy13);

    Enemy newenemy14(sf::Vector2f(50,50));  // right
    newenemy14.setPos(sf::Vector2f(650-newenemy14.getsizex()/2, 300));
    enemyVec.push_back(newenemy14);

    Enemy newenemy15(sf::Vector2f(50,50));  // right
    newenemy15.setPos(sf::Vector2f(800-newenemy15.getsizex()/2, 300));
    enemyVec.push_back(newenemy15);


/*
    // setting enemies postions
    int pos_y=100;
    for(int i=0;i<3;i++){
        int pos_x=200;
        for(int j=0;j<5;j++){
            Enemy newenemy(sf::Vector2f(50,50));
            newenemy.setPos(sf::Vector2f(pos_x-newenemy.getsizex()/2, pos_y));
            enemyVec.push_back(newenemy);
            //enemyVec.emplace_back(Enemy(sf::Vector2f(50,50)));
            //enemyVec[j].setPos(sf::Vector2f(pos_x, pos_y));
            pos_x+=150;
        }
        pos_y+=100;
    }
*/

    bool isFiring = false;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        //std::cout << elapsed.asMicroseconds() << std::endl;
        //std::cout << elapsed.asSeconds() << std::endl;

        float movementSpeed = 300;
        std::pair<float,float> vel;
        vel.first = 0;
        vel.second = 0;

        //if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        //{ vel.second += -movementSpeed * elapsed.asSeconds(); }
        //if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        //{ vel.second += movementSpeed * elapsed.asSeconds(); }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        { vel.first -= movementSpeed * elapsed.asSeconds(); }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        { vel.first += movementSpeed * elapsed.asSeconds(); }

        rec.move(vel.first, vel.second);

        if(rec.getPosition().x<0){
            rec.setPosition(0, wspy-120);
        }
        if(rec.getPosition().x>wspx-recx){
            rec.setPosition(wspx-recx,wspy-120);
        }

        /* moveright
        if(mr)
        {
            enemy.moveright();
            if(enemy.getR()>wspx)
            {
                enemy.movedown();
                mr=false;
            }
        }
        else
        {
            enemy.moveleft();
            if(enemy.getL()<0)
            {
                enemy.movedown();
                mr=true;
            }
        }
*/


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {window.close();}
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { isFiring=true; } }


        window.clear(sf::Color::Black);
        //window.clear();
        //window.draw(set_background_texture);


        // drawing enemies
        for (size_t i = 0; i < enemyVec.size(); i++) {
            enemyVec[i].draw(window);
            }


        // drawing blocks
        for (size_t i = 0; i < blockVec.size(); i++) {
            blockVec[i].draw(window);
            }
/*
        if(move_right)
        {
            enemyVec[0].moveright();
            enemyVec[1].moveright();
            enemyVec[2].moveright();
            if(enemyVec[2].getR()>wspx)
            {
                enemyVec[0].movedown();
                enemyVec[1].movedown();
                enemyVec[2].movedown();
                move_right=false;
            }
        }
        else
        {
            enemyVec[0].moveleft();
            enemyVec[1].moveleft();
            enemyVec[2].moveleft();
            if(enemyVec[0].getL()<0)
            {
                enemyVec[0].movedown();
                enemyVec[1].movedown();
                enemyVec[2].movedown();
                move_right=true;
            }
        }
*/

        // moving enemies
        if(move_right)
        {
            for(size_t i=0;i<enemyVec.size();i++){
                enemyVec[i].moveright();
            }
            if(enemyVec[4].getR()>wspx)
            {
                for(size_t i=0;i<enemyVec.size();i++){
                    enemyVec[i].movedown();
                }
                move_right=false;
            }
        }
        else
        {
            for(size_t i=0;i<enemyVec.size();i++){
                enemyVec[i].moveleft();
            }
            if(enemyVec[0].getL()<0)
            {
                for(size_t i=0;i<enemyVec.size();i++){
                    enemyVec[i].movedown();
                }
                move_right=true;
            }
        }

        ////////// BULLET //////////

        // creating bullets
        if(isFiring == true) {
            Bullet newBullet(sf::Vector2f(5,30));
            newBullet.setPos(sf::Vector2f(rec.getPosition().x+(recx/2), rec.getPosition().y));
            bulletVec.push_back(newBullet);
            isFiring = false;
        }

        // player shooting
        for (size_t i = 0; i < bulletVec.size(); i++) {
            if(bulletVec[i].getT()>-20) {
                bulletVec[i].setnewColorW();
                bulletVec[i].draw(window);
                bulletVec[i].fire(3); //speed
            }
            //else if(bulletVec[i].getT()<10 && bulletVec[i].getT()>-1) { std::cout<<"bullet deleted\n"; }
        }

/*
        for (size_t i = 0; i < bulletVec.size(); i++) {
            enemy.checkColl(bulletVec[i]);
        } */


        // checking collision for every enemy
        for (size_t i = 0; i < enemyVec.size(); i++) {
            for (size_t j = 0; j < bulletVec.size(); j++) {
                if(enemyVec[i].checkColl(bulletVec[j])==true) {
                    bulletVec[j].setPos(sf::Vector2f(0,0));
                    player_score+=1;
                    score_text_update.setString(std::to_string(player_score));
                    std::cout << "player score update: " << player_score << "\n";
                    } } }


        // checking collision for every block
        for (size_t i = 0; i < blockVec.size(); i++) {
            for (size_t j = 0; j < bulletVec.size(); j++) {
                if(blockVec[i].checkColl(bulletVec[j])==true) {
                    bulletVec[j].setPos(sf::Vector2f(0,0));
                    //std::cout << "block left\n";
                    } } }


        // enemy shooting
        /*
        if(rollDice()==200){
            Bullet newBullet2(sf::Vector2f(10,30));
            //newBullet2.setPos(sf::Vector2f(rec.getPosition().x+(recx/2), rec.getPosition().y));
            newBullet2.setPos(sf::Vector2f(enemyVec[0].getL()+enemyVec[0].getsizex()/2, enemyVec[0].getB()));
            bulletVec2.push_back(newBullet2);
            //std::cout << "bull enemy created\n";
        }
     */

        // enemies shooting
        imps++;
        if(imps==500){
            Bullet newBullet2(sf::Vector2f(5,20));
            int enemy_pos=rand()%15;
            newBullet2.setPos(sf::Vector2f(enemyVec[enemy_pos].getL()+enemyVec[enemy_pos].getsizex()/2,
                                           enemyVec[enemy_pos].getB()));
            bulletVec2.push_back(newBullet2);
            imps=0;
        }

        // drawing enemy bullet
        for (size_t i = 0; i < bulletVec2.size(); i++) {
            if(bulletVec2[i].getB()<wspy+20) {
                bulletVec2[i].draw(window);
                bulletVec2[i].fire2(0.5); //speed
            }
        }

        // colission between enemy bullet and player
        for (size_t i = 0; i < bulletVec2.size(); i++) {
            if(rec.getPosition().x <  bulletVec2[i].getL() &&
                    rec.getPosition().x + rec.getSize().x > bulletVec2[i].getR() &&
                    rec.getPosition().y + rec.getSize().y > bulletVec2[i].getT() &&
                    rec.getPosition().y < bulletVec2[i].getT())
            {
                bulletVec2[i].setPos(sf::Vector2f(-30,0));
                //std::cout << "player left\n";
                player_health-=1;
                health_text_update.setString(std::to_string(player_health));
                std::cout << "player health update: " << player_health << "\n";
            }}

        // colission between enemy bullet and blocks
        for (size_t i = 0; i < blockVec.size(); i++) {
            for (size_t j = 0; j < bulletVec2.size(); j++) {
                if(blockVec[i].checkColl(bulletVec2[j])==true) {
                    bulletVec2[j].setPos(sf::Vector2f(0,0));
                    //std::cout << "block left\n";
                    } } }


        /*
        // colission between enemy bullet and block
        for (size_t i = 0; i < bulletVec2.size(); i++) {
            if(rec.getPosition().x <  bulletVec2[i].getL() &&
                    rec.getPosition().x + rec.getSize().x > bulletVec2[i].getR() &&
                    rec.getPosition().y + rec.getSize().y > bulletVec2[i].getT() &&
                    rec.getPosition().y < bulletVec2[i].getT())
            {
                bulletVec2[i].setPos(sf::Vector2f(-30,0));
                //std::cout << "player left\n";
                player_health-=1;
                health_text_update.setString(std::to_string(player_health));
                std::cout << "player health update: " << player_health << "\n";
            }}
*/


        //sf::Time t1 = t1+elapsed;
        //std::cout << t1.asSeconds() << std::endl;

        //int t2=floor(t1.asSeconds());
        //std::cout << t2 << std::endl << std::endl;



  /*
        sf::RectangleShape bullet2(sf::Vector2f(10,50));
        if(t2%2==0) {

            Bullet newBullet2(sf::Vector2f(10,50));
            //newBullet2.setPos(sf::Vector2f(enemy.getL()+((abs(enemy.getR()-enemy.getL()))/2),enemy.getB()));
            newBullet2.setPos(sf::Vector2f(enemy.getL()+(enemy.getsizex()/2),enemy.getB())); //- to samo co wyżej
            newBullet2.draw(window);
            newBullet2.fire2(3); //speed


            bullet2.setFillColor(sf::Color::Yellow);
            //bullet2.setPosition(sf::Vector2f(enemy.getL()+(enemy.getsizex()/2),enemy.getB()));
            bullet2.setPosition(sf::Vector2f(enemy.getL(),enemy.getB()));


            bullet2.move(10,-20);
            window.draw(bullet2);


            enemy.shoot();
        }
*/

        window.draw(rec);
        window.draw(black_box);

        window.draw(score_text);
        window.draw(score_text_update);
        window.draw(health_text);
        window.draw(health_text_update);

        //if(enemy1_isAlive)
        //{ enemy.draw(window); }

        if(player_health<1){
            window.clear(sf::Color::Black);
            sf::Text lose_text;
            lose_text.setFont(font);
            lose_text.setString("YOU LOST!");
            lose_text.setCharacterSize(100);
            lose_text.setStyle(sf::Text::Regular);
            lose_text.setFillColor(sf::Color::Red);
            lose_text.setPosition(sf::Vector2f(160,200));
            window.draw(lose_text);
        }

        if(player_score>=15){
            window.clear(sf::Color::Black);
            sf::Text win_text;
            win_text.setFont(font);
            win_text.setString("YOU WON!");
            win_text.setCharacterSize(100);
            win_text.setStyle(sf::Text::Regular);
            win_text.setFillColor(sf::Color::Green);
            win_text.setPosition(sf::Vector2f(160,200));
            window.draw(win_text);
        }

        window.display();
    }
    return 0;
}

