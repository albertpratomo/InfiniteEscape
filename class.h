#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <math.h>

class CPosition{
protected:
	int m_x;
	int m_y;

public:
	int GetX(){return m_x;}
	int GetY(){return m_y;}
	void SetY(int n){m_y = n;}
	void SetX(int n){m_x = n;}
};

class CDensus:public CPosition{
	sf::Texture texture;
	sf::Sprite player;
	CPosition m_pos;

	int m_exist;
	int m_view;
	int lastMove;

	sf::Font fontPlayer;
	sf::Text textPlayer;
	sf::Text textType;
public:
	CDensus(){
		m_exist = 0;
		m_pos.SetX(0);
		m_pos.SetY(0);
		lastMove = 0;

		texture.loadFromFile("images/densus.png");
		texture.setSmooth(true);

		player.setTexture(texture);
		player.setTextureRect(sf::IntRect(0,0, 32, 32));

		fontPlayer.loadFromFile("font/font.ttf");
		textPlayer.setFont(fontPlayer);
		textPlayer.setStyle(sf::Text::Bold);
		textPlayer.setColor(sf::Color::White);
		textPlayer.setCharacterSize(12);
		textPlayer.setOrigin(textPlayer.getGlobalBounds().left, textPlayer.getGlobalBounds().height / 2);

		textType.setString("");
		textType.setFont(fontPlayer);
		textType.setStyle(sf::Text::Bold);
		textType.setColor(sf::Color::Yellow);
		textType.setCharacterSize(12);
		textType.setOrigin(textPlayer.getOrigin().x, textPlayer.getOrigin().y);
	}

	void SetExist(int exist,float view){
		if(exist == 1){SetImage(1);}
		m_exist = exist;
		m_view = ceil(view/32.0);
	}

	void SetImage(int n = 0){
		if(n == 1){
			texture.loadFromFile("images/densus.png");
		} 
		else {
			texture.loadFromFile("images/densusfire.png");}
		player.setTexture(texture);
	}

	void SetText(char* text){
		textPlayer.setString(text);
	}

	bool SetType(char type){
		textType.setString(textType.getString() + type);
		if(textType.getString().getSize() == 5){
			m_exist=-180;
			return true;
		}
		return false;
	}

	bool CekType(char type){

		if(type == textPlayer.getString().substring(textType.getString().getSize(),1)){
			return true;
		}
		return false;
	}

	int GetExist(){
		return m_exist;
	}

	void MoveX(){
		if(m_pos.GetX()==2){m_pos.SetX(0);}
		else{m_pos.SetX(2);}
	}

	void MoveRight(){
		m_pos.SetY(2);
		MoveX();
		Move(1,0);
	}
	void MoveLeft(){
		m_pos.SetY(1);	
		MoveX();
		Move(-1,0);
	}
	void MoveUp(){
		m_pos.SetY(3);
		MoveX();
		Move(0,-1);
	}
	void MoveDown(){
		m_pos.SetY(0);
		MoveX();
		Move(0,1);
	}

	void SetPosition(int map[24][30], int diff){
		int x=0,y;
		bool status = true;
		while(status){
			y = 13 - diff;
			if(y%2 == 0){
				for(int i=0;i<30;i++){
					if(map[y][i] == -2){
						x++;
						if(x>=rand()%5+2){
							x=i;
							break;
						}
					}	
				}	
			}
			else{
				for(int i=29;i>=0;i--){
					if(map[y][i] == -2){
						x++;
						if(x>=rand()%5+2){
							x=i;
							break;
						}	
					}
				}
			}
			diff+=5;
			if(map[y][x]==-2){status = false;}
		}
		m_x = x;
		m_y = y;
		player.setPosition(m_x*32, (m_y+m_view)*32-4);
	}

	void DecideMove(int map[24][30]){
		if(map[m_y][m_x]>=0){
	  		if(map[m_y][m_x+1]==map[m_y][m_x]-1){MoveRight();}
			else if(map[m_y][m_x-1]==map[m_y][m_x]-1){MoveLeft();}
			else if(map[m_y+1][m_x]==map[m_y][m_x]-1){MoveDown();}
			else if(map[m_y-1][m_x]==map[m_y][m_x]-1){MoveUp();}
		}
		else{
			int co=rand()%4;
			if(co==0 && map[m_y][m_x+1] != -1){MoveRight();}
			else if(co==1 && map[m_y][m_x-1] != -1){MoveLeft();}
			else if(co==2 && map[m_y+1][m_x] != -1){MoveDown();}
			else if(map[m_y-1][m_x] != -1){MoveUp();}
		}
	}

	void Move(int dx, int dy){
		m_x+=dx;
		m_y+=dy;
		if(m_x<0){m_x=0;} 
		if(m_x>29){m_x=29;}
		if(m_y<0){m_y=0;}
		if(m_y>23){m_y=23;}

		player.setTextureRect(sf::IntRect(m_pos.GetX()*32, m_pos.GetY()*32, 32,32));
		player.setPosition(m_x*32, (m_y+m_view)*32-4);
	}

	void SetTexture(int n=0){
		player.setTextureRect(sf::IntRect(n*32, 0, 32, 64));
	}

	void Print(sf::RenderWindow &window){
		if(m_exist!=0){
			if(m_exist<-150){SetTexture(0);}
			else if(m_exist<-120){SetTexture(1);}
			else if(m_exist<-90){SetTexture(2);}
			else if(m_exist<-60){SetTexture(3);}
			else if(m_exist<-30){SetTexture(4);}
			else if(m_exist<0){SetTexture(5);}	

			player.setPosition(m_x*32, (m_y+m_view)*32-4);
			
			if(m_exist<0){player.setPosition(player.getPosition().x, player.getPosition().y-32 +4);}
			
			window.draw(player);
			textPlayer.setPosition(player.getGlobalBounds().left - 4, player.getGlobalBounds().top);
			textType.setPosition(player.getGlobalBounds().left - 4, player.getGlobalBounds().top);
			window.draw(textPlayer);
			window.draw(textType);
			if(m_exist<0){m_exist++;}
		}
		else{
			textType.setString("");
		}
	}
};
class CPowerup:public CPosition{
	int m_exist;
	std::string m_typePowerup;
	sf::Texture m_texturePowerup;
	sf::Sprite m_spritePowerup;
public:
	CPowerup(){
		m_exist = 0;
	}
	void SetUp(int tipe,int x, int y){
		if (tipe == 0){
			m_texturePowerup.loadFromFile("images/freeze.png");
			m_typePowerup = "F";
		}
		else if (tipe == 1){
			m_texturePowerup.loadFromFile("images/stealth.png");
			m_typePowerup = "S";
		}
		else if (tipe == 2){
			m_texturePowerup.loadFromFile("images/bomb.png");
			m_typePowerup = "B";
		}
		else if (tipe == 3){
			m_texturePowerup.loadFromFile("images/laser.png");
			m_typePowerup = "L";
		}
		m_spritePowerup.setTexture(m_texturePowerup);
		m_x = x;
		m_y = y;
		m_exist = 1;// powerup sudah di print di map
	}

	void SetExist(int n){
		m_exist = n;
	}
	int GetExist(){
		return m_exist;
	}

	std::string GetType(){
		return m_typePowerup;
	}
	void Print(sf::RenderWindow &window){
		m_spritePowerup.setPosition(m_x * 32, m_y * 32);
		window.draw(m_spritePowerup);
	}

	void Move(){
		m_y++;
	}
};

class CSkill{
protected:
	int m_duration;
	int m_exist;
	std::string m_type;
	sf::Clock m_count;
	sf::SoundBuffer m_soundbuffer;
	sf::Sound m_sound;
public:
	CSkill(){
		m_exist = 1;
		m_soundbuffer.loadFromFile("sound/skill.wav");
		m_sound.setBuffer(m_soundbuffer);
	}

	int GetExist(){
		return m_exist;
	}

	void SetExist(int n){
		m_exist =n;
	}

	void SetCount(){
		m_exist = 1;

		if(m_count.getElapsedTime().asMilliseconds() >= 8000){
			m_sound.pause();
			m_sound.play();
		}
		if(m_count.getElapsedTime().asMilliseconds() >= m_duration){
			m_count.restart();
			m_exist = 0;
		} 
	}

	int GetCount(){
		return m_duration/1000 - m_count.getElapsedTime().asSeconds();
	}
	std::string GetType(){
		return m_type;
	}

};

class CWeapon{
protected:
	int m_count;

	CPosition m_posProjectile[5];
	sf::Clock clockProjectile[5];
	int m_existProjectile[5];
	int m_dx[5];
	int m_dy[5];
	int m_durationProjectile;

	std::string m_type;
	sf::Texture textureProjectile;
	sf::Sprite spriteProjectile;

public:
	CWeapon(){
		for(int i =0; i< 5;  i++){
			m_existProjectile[i] =0;
		}
		m_count =0;
	}

	virtual void SetTexture(int n =0)=0;

	virtual void Fire(int x, int y, int arah=0)=0;

	virtual void MoveProjectile()=0;

	virtual void PrintProjectile(sf::RenderWindow &window)=0;

	std::string GetType(){
		return m_type;
	}

	int GetExist(){
		int cek=1;
		if(m_count==5 ){
			for(int i=0; i<5; i++){if(m_existProjectile[i]==0){cek++;}}
		}

		if(cek == 6){
			return 0;}
		return 1;
	}

	void SetExist(int n){m_existProjectile[n] = 0;}

	int GetExistProjectile(int i){
		return m_existProjectile[i];
	}

	int GetCount(){
		return m_count;
	}

	int GetProjectileX(int n){
		return m_posProjectile[n].GetX();
	}

	int GetProjectileY(int n){
		return m_posProjectile[n].GetY();
	}

	void Move(int i, int x, int y){
		m_posProjectile[i].SetX(m_posProjectile[i].GetX()+x);
		m_posProjectile[i].SetY(m_posProjectile[i].GetY()+y);
		if(m_posProjectile[i].GetY()<0 || m_posProjectile[i].GetY()>29){m_existProjectile[i]=0;m_posProjectile[i].SetY(0);}
		if(m_posProjectile[i].GetX()<0 || m_posProjectile[i].GetX()>29){m_existProjectile[i]=0;m_posProjectile[i].SetX(0);}
	}
};

class CBomb:public CWeapon{

public:
	CBomb(){
		m_type = "B";
		m_durationProjectile = 1000;

		textureProjectile.loadFromFile("images/bomb1.png");
		spriteProjectile.setTexture(textureProjectile);
		spriteProjectile.setTextureRect(sf::IntRect(0,0,96,96));
	}
	void SetTexture(int n=0){
		spriteProjectile.setTextureRect(sf::IntRect(n*96,0,96,96));
	
	}
	void Fire(int x, int y, int arah=0){
		if(m_count <5){
			m_posProjectile[m_count].SetX(x);
			m_posProjectile[m_count].SetY(y);
			m_existProjectile[m_count]=1;
			m_count++;
		}
	}

	void PrintProjectile(sf::RenderWindow &window){
		for(int i=0; i< m_count; i++){
			
			spriteProjectile.setPosition((m_posProjectile[i].GetX()-1)*32, (m_posProjectile[i].GetY()-1)*32);
			if(m_existProjectile[i]<0){

				if(m_existProjectile[i]<-140){SetTexture(1);}
				else if(m_existProjectile[i]<-130){SetTexture(2);}
				else if(m_existProjectile[i]<-120){SetTexture(3);}
				else if(m_existProjectile[i]<-110){SetTexture(4);}
				else if(m_existProjectile[i]<-100){SetTexture(5);}
				else if(m_existProjectile[i]<-90){SetTexture(6);}
				else if(m_existProjectile[i]<-80){SetTexture(7);}
				else if(m_existProjectile[i]<-60){SetTexture(8);}
				else if(m_existProjectile[i]<-50){SetTexture(9);}
				else if(m_existProjectile[i]<-40){SetTexture(10);}
				else if(m_existProjectile[i]<-30){SetTexture(11);}	
				else if(m_existProjectile[i]<-20){SetTexture(12);}
				else if(m_existProjectile[i]<-10){SetTexture(13);}
				else if(m_existProjectile[i]<0){SetTexture(14);}	
				m_existProjectile[i]++;
			} else if(m_existProjectile[i]==1){SetTexture(0);}
			if(m_existProjectile[i]!=0){window.draw(spriteProjectile);}
		}
	}

	void MoveProjectile(){
		for(int i=0; i<5; i++){
			if(m_existProjectile[i]==1){
				if(clockProjectile[i].getElapsedTime().asMilliseconds() >= m_durationProjectile){
					m_existProjectile[i]=-140;
				}
			}
			else{
				clockProjectile[i].restart();
			}
		}
	}
};

class CLaser:public CWeapon{

public:
	CLaser(){
		m_type = "L";
		m_durationProjectile = 200;
		textureProjectile.loadFromFile("images/laser1.png");
		spriteProjectile.setTexture(textureProjectile);
	}

	void SetTexture(int n=0){
		spriteProjectile.setTextureRect(sf::IntRect(n*32,0,32,32));
	
	}

	void PrintProjectile(sf::RenderWindow &window){
		for(int i=0; i< m_count; i++){
			spriteProjectile.setPosition(m_posProjectile[i].GetX()*32, m_posProjectile[i].GetY()*32);
			if(m_existProjectile[i]!=0){window.draw(spriteProjectile);}
		}
	}

	void Fire(int x, int y,int arah=0){
		if(m_count <5){
			m_posProjectile[m_count].SetX(x);
			m_posProjectile[m_count].SetY(y);
			m_existProjectile[m_count]=1;

			if(arah == 0){
				m_dx[m_count]=0;
				m_dy[m_count]=1;
				SetTexture(3);
			} 
			else if(arah == 1){
				m_dx[m_count]=-1;
				m_dy[m_count]=0;
				SetTexture(0);
			}
			else if(arah == 2){
				m_dx[m_count]=1;
				m_dy[m_count]=0;
				SetTexture(2);
			}
			else if(arah == 3){
				m_dx[m_count]=0;
				m_dy[m_count]=-1;
				SetTexture(1);
			}

			m_count++;
		}
	}

	void MoveProjectile(){
		for(int i=0; i< m_count ; i++){
			if(m_existProjectile[i]==1){
				if(clockProjectile[i].getElapsedTime().asMilliseconds()>=m_durationProjectile){
					m_posProjectile[i].SetX(m_posProjectile[i].GetX()+m_dx[i]);
					m_posProjectile[i].SetY(m_posProjectile[i].GetY()+m_dy[i]);
					if(m_posProjectile[i].GetX() > 29 || m_posProjectile[i].GetX()<0){m_existProjectile[i] = 0;}
					if(m_posProjectile[i].GetY() > 29 || m_posProjectile[i].GetY()<0){m_existProjectile[i] = 0;}
					clockProjectile[i].restart();
				}
			}
		}
	}

};

class CFreeze:public CSkill{
public:
	CFreeze(){
		m_duration = 10000;
		m_type = "F";
	}
};

class CStealth:public CSkill{
public:
	CStealth(){
		m_duration = 10000;
		m_type = "S";
	}
};

class CObstacle:public CPosition{
protected: 
	sf::Texture textureObstacle;
	sf::Sprite obstacle;
	

	std::string m_type;
	int m_length;
	int m_direction;
	int m_exist;
	sf::Clock clockObstacle;
	int m_time;

public:
	CObstacle(){
		m_exist = 1;
		m_time = 100;
		obstacle.setPosition(-1*(m_length-1)*32,0);
	}

	int GetExist(){
		return m_exist;
	}

	void SetExist(int n){
		if(m_exist == 0 || m_exist== 1){
			m_exist = n;
		}

	}

	void Move(){
		m_x+=m_direction;
		if(m_x <-2){ m_x = 29;}
		if(m_type== "K"){
			if(m_x >125){ m_x = 0;}
		}
		else if(m_x >35){ m_x = 0;}
		MoveX();
		clockObstacle.restart();
	}

	void MoveAnimation(){
		int n;
		n = 32/1*m_direction;
		obstacle.setPosition(obstacle.getPosition().x+n,0);
	}

	void MoveX(){// untuk mengeset origin dari obstacle.co: kereta dari kiri berbeda dengan mobil dari kanan
		int n;
		if(m_direction >0){ n = -1*(m_length-1)*32;} else {n=0;}
		obstacle.setPosition(m_x*32+n, 0);
	}

	virtual void SetTexture(int n=0)=0;

	int GetDirection(){
		return m_direction;
	}

	int GetLength(){
		return m_length;
	}

	virtual void Print( sf::RenderWindow &window, int yy)=0;
};

class CCar:public CObstacle{
public:
	CCar(){
		m_length = 2;
		m_direction = -1;
		m_x = 29;
		m_type = "O";
		int random = rand()%4;
		if(random == 0){textureObstacle.loadFromFile("images/car1fire.png");}
		else if(random == 1){textureObstacle.loadFromFile("images/car2fire.png");}
		else if(random == 2){textureObstacle.loadFromFile("images/car3fire.png");}
		else if(random == 3){textureObstacle.loadFromFile("images/car4fire.png");}
		SetTexture();
		
		obstacle.setPosition(m_x*32,0);
	}
	void SetTexture(int n =0){
		obstacle.setTexture(textureObstacle);
		obstacle.setTextureRect(sf::IntRect(n*64,0,64,64));
	}

	void Print( sf::RenderWindow &window, int yy){
		if(m_exist != 0){
			if(m_exist < -162){SetTexture(1);}
			else if(m_exist < -144){SetTexture(2);}
			else if(m_exist < -126){SetTexture(3);}
			else if(m_exist < -108){SetTexture(4);}
			else if(m_exist < -90){SetTexture(5);}
			else if(m_exist < -72){SetTexture(6);}
			else if(m_exist < -54){SetTexture(7);}
			else if(m_exist < -36){SetTexture(8);}
			else if(m_exist < -18){SetTexture(9);}
			else if(m_exist < 0){SetTexture(10);}

			obstacle.setPosition(obstacle.getPosition().x,yy*32-36);
			window.draw(obstacle);


			if(m_exist<0){m_exist++;}
		}
	}
};

class CTurtle:public CObstacle{
public:
	CTurtle(){
		m_length = 2;
		m_direction = -1;
		m_x = 29;
		m_type = "K";

		textureObstacle.loadFromFile("images/kayu2.png");
		SetTexture();
		obstacle.setPosition(m_x*32,0);
	}
	void SetTexture(int n = 0){
		obstacle.setTexture(textureObstacle);
	}

	void Print( sf::RenderWindow &window, int yy){
		if(m_exist != 0){
			obstacle.setPosition(obstacle.getPosition().x,yy*32-36);
			window.draw(obstacle);
		}
	}
};

class CPalang:public CObstacle{
public:
	CPalang(){
		m_length = 1;
		m_direction = 0;
		m_type = "PA";
		textureObstacle.loadFromFile("images/palang.png");
		textureObstacle.setSmooth(true);
		obstacle.setTexture(textureObstacle);

		obstacle.setTextureRect(sf::IntRect(0,0,32,64));
	}

	void SetTexture(int n=0){
		obstacle.setTextureRect(sf::IntRect(n*32, 0, 32, 64));
	}

	void Print( sf::RenderWindow &window, int yy){
		if(m_exist != 0){
			obstacle.setPosition(obstacle.getPosition().x,yy*32-36);
			window.draw(obstacle);
			if(m_exist<0){m_exist++;}
		}
	}
};

class CTree:public CObstacle{
public:
	CTree(){
		m_length = 1;
		m_direction = 0;
		m_type = "P";
		int random= rand()%2;

		if(random==0){
			textureObstacle.loadFromFile("images/tree1fire.png");}
		else{
			textureObstacle.loadFromFile("images/tree1fire.png");
		}
		textureObstacle.setSmooth(true);
		SetTexture();
	}

	void SetTexture(int n =0){
		obstacle.setTexture(textureObstacle);
		obstacle.setTextureRect(sf::IntRect(n*32,0,32,64));
	}

	void Print( sf::RenderWindow &window, int yy){
		if(m_exist != 0){
			if(m_exist < -150){SetTexture(1);}
			else if(m_exist < -120){SetTexture(2);}
			else if(m_exist < -90){SetTexture(3);}
			else if(m_exist < -60){SetTexture(4);}
			else if(m_exist < -30){SetTexture(5);}
			else if(m_exist < 0){SetTexture(6);}

			for(int i=0; i< m_length ; i++){
				obstacle.setPosition(obstacle.getPosition().x,yy*32-36);
				window.draw(obstacle);
			}

			if(m_exist<0){m_exist++;}
		}
	}
};

class CWood:public CObstacle{
public:
	CWood(){
		m_length = 3;
		m_direction = 1;
		m_type = "W";
		m_x = 0;
		textureObstacle.loadFromFile("images/kayu3.png");
		textureObstacle.setSmooth(true);
		SetTexture();
	}

	void SetTexture(int n =0){
		obstacle.setTexture(textureObstacle);
	}

	void Print( sf::RenderWindow &window, int yy){
		if(m_exist != 0){
			int n= -1*(m_length-1)*32;
			obstacle.setPosition(obstacle.getPosition().x,yy*32-34);
			window.draw(obstacle);
			
			if(m_exist<0){m_exist++;}
		}
	}
};

class CTruck:public CObstacle{
public:
	CTruck(){
		m_length = 4;
		m_direction = 1;
		m_x = 0;
		m_type = "X";

		textureObstacle.loadFromFile("images/truck1.png");
		textureObstacle.setSmooth(true);
		obstacle.setTexture(textureObstacle);
		SetTexture();
	}

	void SetTexture(int n=0){
		obstacle.setTextureRect(sf::IntRect(0,n*64, 128, 64));
	}

	void Print( sf::RenderWindow &window, int yy){
		if(m_exist != 0){
			if(m_exist < -162){SetTexture(1);}
			else if(m_exist < -144){SetTexture(2);}
			else if(m_exist < -126){SetTexture(3);}
			else if(m_exist < -108){SetTexture(4);}
			else if(m_exist < -90){SetTexture(5);}
			else if(m_exist < -72){SetTexture(6);}
			else if(m_exist < -54){SetTexture(7);}
			else if(m_exist < -36){SetTexture(8);}
			else if(m_exist < -18){SetTexture(9);}
			else if(m_exist < 0){SetTexture(10);}

			obstacle.setPosition(obstacle.getPosition().x,yy*32-36);
			window.draw(obstacle);	

			if(m_exist<0){m_exist++;}
		}
	}
};

class CTrain :public CObstacle{
public:
	CTrain(){
		m_length = 13;
		m_direction = 2;
		m_x = 0;
		m_type = "K";

		textureObstacle.loadFromFile("images/train1.png");
		textureObstacle.setSmooth(true);
		obstacle.setTexture(textureObstacle);
		SetTexture();
	}

	void SetTexture(int n=0){
		obstacle.setTextureRect(sf::IntRect(0,n*64, 416, 64));
	}

	void Print( sf::RenderWindow &window, int yy){
		if(m_exist != 0){
			if(m_exist < -162){SetTexture(1);}
			else if(m_exist < -144){SetTexture(2);}
			else if(m_exist < -126){SetTexture(3);}
			else if(m_exist < -108){SetTexture(4);}
			else if(m_exist < -90){SetTexture(5);}
			else if(m_exist < -72){SetTexture(6);}
			else if(m_exist < -54){SetTexture(7);}
			else if(m_exist < -36){SetTexture(8);}
			else if(m_exist < -18){SetTexture(9);}
			else if(m_exist < 0){SetTexture(10);}

			obstacle.setPosition(obstacle.getPosition().x,yy*32-36);
			window.draw(obstacle);

			if(m_exist<0){m_exist++;}
		}
	}
};

class CRoad:public CPosition{
protected:
	CObstacle* m_obstacle[6];
	int m_n;
	int m_count;

	sf::Sprite road;
	sf::Texture textureRoad;
	std::string m_type;

public:
	void Print(sf::RenderWindow &window){
		for(int i=0; i<30; i++){
			road.setPosition(i*32, m_y*32);
			window.draw(road);
		}
	}

	std::string GetType(){return m_type;};

	virtual void SetExistObstacle(int x)=0;

	virtual int CekCrash(int x)=0;

	virtual void CekCount(int n)=0;

	void MoveObstacle(){
		for(int i=0; i< m_n; i++){m_obstacle[i]->Move();}
	}

	void MoveObstacleAnimation(){
		for(int i=0; i< m_n; i++){m_obstacle[i]->MoveAnimation();}
	}

	void PrintObstacle(sf::RenderWindow &window){
		for(int i=m_n-1; i>=0; i--){m_obstacle[i]->Print(window, m_y);}
	}

	int GetDirection(){
		return m_obstacle[0]->GetDirection();}

	void SetY(){
		m_y =m_y+1;
		if(m_y>29){m_y=0;}

		for(int i=0; i< m_n ; i++){
			m_obstacle[i]->SetY(m_y);
		}
	}
};

class CRel:public CRoad{
public:
	CRel(int n){
		m_y =n;
		m_type = "R";
		m_n = 0;

		m_count = rand()%50;
		textureRoad.loadFromFile("images/rail.png");
		road.setTexture(textureRoad);


		m_obstacle[0] = new CPalang;
		m_obstacle[0]->SetY(n);
		m_obstacle[0]->SetX(15);
		m_n++;
	}

	int CekCrash(int x){

		if(m_n == 2){
			if(m_obstacle[1]->GetExist()!= 0){
				for(int j=0; j<m_obstacle[1]->GetLength(); j++){
					if(x == m_obstacle[1]->GetX()-j){
						return 0;
					}
				}
			}
		}
		return 1;
	}

	void SetExistObstacle(int x){
		m_obstacle[1]->SetExist(-180);
	}

	void CekCount(int y){
		if(m_count == 0){
			m_obstacle[1] = new CTrain;
			m_obstacle[1]->SetY(y);
			m_n++;
		}

		if(m_n == 2){
			if(m_obstacle[1]->GetX()-m_obstacle[1]->GetLength()>16 || m_obstacle[1]->GetExist()==0){
				m_obstacle[0]->SetTexture(0);
			} else{
				m_obstacle[0]->SetTexture(1);
			}
		}
		m_count--;
	}
};

class CJalan:public CRoad{
public:
	CJalan(int n){
		m_y =n;
		m_type = " ";
		m_n = 0;

		m_count = rand()%8 +5;

		textureRoad.loadFromFile("images/road3.png");
		road.setTexture(textureRoad);
	}

	void SetExistObstacle(int x){
		for(int i=0; i<m_n; i++){
			for(int j=0; j<m_obstacle[i]->GetLength(); j++){
				if(x==m_obstacle[i]->GetX()-(j*m_obstacle[i]->GetDirection()/abs(m_obstacle[i]->GetDirection()))){
					m_obstacle[i]->SetExist(-180);
				}
			}
		}
	}

	int CekCrash(int x){
		for(int i=0; i<m_n; i++){
			if(m_obstacle[i]->GetExist()!=0){
				for(int j=0; j<m_obstacle[i]->GetLength(); j++){
					if(x==m_obstacle[i]->GetX()-(j*m_obstacle[i]->GetDirection()/abs(m_obstacle[i]->GetDirection()))){
						return 0;
					}
				}
			}
		}
		return 1;
	}

	void CekCount(int n){
		if(m_n < 6 && n%2 ==0){
			if(m_count == 0){
				m_count = rand()%2 + 5;
				m_obstacle[m_n] = new CCar;
				m_obstacle[m_n]->SetY(n);

				m_n++;
			}
			m_count--;
		} 
		else if(m_n<3 && n%2 == 1){
			if(m_count == 0){
				m_count = rand()%5 + 10;
				m_obstacle[m_n] = new CTruck;
				m_obstacle[m_n]->SetY(n);
				m_n++;
			}
			m_count--;
		}
	}
};

class CSungai:public CRoad{
public:
	CSungai(int n){
		m_y =n;
		m_type = "S";
		m_n = 0;
		m_count = rand()%2 +4;


		textureRoad.loadFromFile("images/water.png");
		road.setTexture(textureRoad);
	}

	void SetExistObstacle(int x){;}
	void CekCount(int n){
		if(m_n < 6){
			if(m_count == 0){
				m_count = rand()%2 + 5;
				if(n%2==1){
					m_obstacle[m_n] = new CWood;
				} 
				else{
					m_obstacle[m_n] = new CTurtle;
				}
				m_obstacle[m_n]->SetY(n);

				m_n++;
			}
			m_count--;
		}
	}

	int CekCrash(int x){
		for(int i=0; i<m_n; i++){
			for(int j=0; j<m_obstacle[i]->GetLength(); j++){
				if(x==m_obstacle[i]->GetX()-(j*m_obstacle[i]->GetDirection()/abs(m_obstacle[i]->GetDirection()))){
					return 1;
				}
			}
		}
		return 0;
	}
};

class CTanah:public CRoad{
public:
	CTanah(int n, int y=0){
		m_y =n;
		m_type = "T";
		m_n =0;


		textureRoad.loadFromFile("images/grass3.png");
		textureRoad.setSmooth(true);
		road.setTexture(textureRoad);

		if(y == 0){
			for(int i=0; i< 6; i++){
				m_obstacle[i]= new CTree;
				m_obstacle[i]->SetY(m_y);
				m_obstacle[i]->SetX(rand()%4 + i*5);
				m_n++;
			}
		}
		else{
			for(int i=0; i< 6; i++){
				m_obstacle[i]= new CTree;
				m_obstacle[i]->SetY(m_y);
				if(i==3){
					m_obstacle[i]->SetX(rand()%3 + i*5+1);} 
				else{
					m_obstacle[i]->SetX(rand()%4 + i*5);
				}
				m_n++;
			}
		} 
	}

	void CekCount(int n){
	}

	int CekCrash(int x){

		for(int i=0; i<m_n; i++){
			if(m_obstacle[i]->GetExist()!=0){
				for(int j=0; j<m_obstacle[i]->GetLength(); j++){
					if(x==m_obstacle[i]->GetX()+j){
						return 0;
					}
				}
			}
		}
		return 1;
	}

	void SetExistObstacle(int x){

		for(int i=0; i<m_n; i++){
			for(int j=0; j<m_obstacle[i]->GetLength(); j++){
				if(x==m_obstacle[i]->GetX()+j){
					m_obstacle[i]->SetExist(-180);
				}
			}
		}
	}

};

class CTerror: public CPosition{
	sf::Texture texture;
	sf::Sprite player;
	CSkill* m_skill[1];
	CWeapon* m_weapon[1];
	CPosition m_pos;
	int m_skillCek;
	int m_weaponCek;
	int max_y, min_y;
	sf::SoundBuffer bufferLaser;
	sf::SoundBuffer bufferBomb;
	sf::SoundBuffer bufferJump;
	sf::SoundBuffer bufferPower;
	sf::SoundBuffer bufferWater;
	sf::Sound soundWater;
	sf::Sound soundJump;
	sf::Sound soundBomb;
	sf::Sound soundLaser;
	sf::Sound soundPower;
	int m_exist;
public:
	CTerror(){
		m_x = 15;
		m_y = 22;
		m_exist = 1;
		m_pos.SetX(0);
		m_pos.SetY(0);

		texture.loadFromFile("images/frogger.png");
		texture.setSmooth(true);

		player.setTexture(texture);
		player.setTextureRect(sf::IntRect(0,0, 32, 32));
		player.setPosition(m_x*32, m_y*32-4);

		min_y = 22;
		max_y = 30;
		m_skillCek= 0;
		m_weaponCek = 0;
		bufferPower.loadFromFile("sound/power.wav");
		bufferLaser.loadFromFile("sound/laser.wav");
		bufferJump.loadFromFile("sound/jump.wav");
		bufferBomb.loadFromFile("sound/bomb.wav");
		bufferWater.loadFromFile("sound/water.wav");
		soundWater.setBuffer(bufferWater);
		soundJump.setBuffer(bufferJump);
		soundPower.setBuffer(bufferPower);
		soundLaser.setBuffer(bufferLaser);
		soundBomb.setBuffer(bufferBomb);
	}

	void SetImage(int k=0){
		if(k==0){
			texture.loadFromFile("images/terror1.png");
			player.setTexture(texture);
			player.setTextureRect(sf::IntRect(0, 0, 32, 32));
			player.setPosition(player.getPosition().x, player.getPosition().y +4);
			soundWater.play();
		}
		else {
			texture.loadFromFile("images/terrorfire.png");
			player.setTexture(texture);
			m_exist  = -180;
			player.setPosition(player.getPosition().x, player.getPosition().y-32 +4);
		}
	}

	void SetTexture(int k= 0){
		player.setTextureRect(sf::IntRect(k*32, 0, 32, 64));
	}

	void MoveX(){
		m_pos.SetX(m_pos.GetX()+1);
		if(m_pos.GetX()>2){m_pos.SetX(0);}
	}

	void MoveRight(){
		m_pos.SetY(2);
	}
	void MoveLeft(){
		m_pos.SetY(1);	
	}
	void MoveUp(){
		m_pos.SetY(3);
		//soundJump.play();
	}
	void MoveDown(){
		m_pos.SetY(0);
	}

	void SetMinY(int pos=200){
		if(pos!=200){
		max_y = 24+ceil(pos/32.0);
		min_y = ceil(pos/32.0);}
		else{
		max_y = 30;
		min_y = 22;
		}
	}

	void Move(int dx, int dy){
		m_x+=dx;
		m_y+=dy;
		if(m_x<0){m_x=0;}
		if(m_x>29){m_x=29;}

		if(m_y < min_y){m_y = min_y;}
		if(m_y > max_y){m_y = max_y;}		

	

		player.setTextureRect(sf::IntRect(m_pos.GetX()*32, m_pos.GetY()*32, 32,32));
		player.setPosition(m_x*32, m_y*32-4);
	}

	void Print(sf::RenderWindow &window){
		if(m_exist<0){
			if(m_exist<-150){SetTexture(0);}
			else if(m_exist<-120){SetTexture(1);}
			else if(m_exist<-90){SetTexture(2);}
			else if(m_exist<-60){SetTexture(3);}
			else if(m_exist<-30){SetTexture(4);}
			else if(m_exist<0){SetTexture(5);}	
			m_exist++;
		}

		window.draw(player);
	}

	void SetSkill(std::string skill){
		if(skill == "F"){
			m_skill[0] = new CFreeze;
		}
		else if(skill == "S"){
			m_skill[0] = new CStealth;
		}
		soundPower.play();
		m_skillCek = 1;
		if(m_skill[0]->GetType()=="S"){player.setColor(sf::Color(255,255,255,150));}
	}
	void SetWeapon(std::string weapon){
		if(weapon == "B"){
			m_weapon[0] = new CBomb;
		}
		else if(weapon == "L"){
			m_weapon[0] = new CLaser;
		}
		soundPower.play();
		m_weaponCek = 1;
	}

	void SetSkillCount(){
		m_skill[0]->SetCount();
		m_skillCek = m_skill[0]->GetExist();
		if(m_skillCek ==0){player.setColor(sf::Color(255,255,255,255));}
	}
	void SetWeaponCount(){
		m_weapon[0]->MoveProjectile();
		m_weaponCek = m_weapon[0]->GetExist();
	}

	int GetSkillCount(){
		return m_skillCek;}
	int GetWeaponCount(){
		return m_weaponCek;}

	std::string GetSkillType(){
		return m_skill[0]->GetType();
	}
	std::string GetWeaponType(){
		return m_weapon[0]->GetType();
	}

	void Fire(){
		if(m_weapon[0]->GetType()=="L"){soundLaser.play();}
		else{soundBomb.play();}
		m_weapon[0]->Fire(m_x, m_y, m_pos.GetY());
	}

	int GetProjectileCount(){
		return m_weapon[0]->GetCount();
	}
	int GetSisaCount(){
		return m_skill[0]->GetCount();
	}

	int GetProjectileX(int n){
		return m_weapon[0]->GetProjectileX(n);
	}

	int GetProjectileY(int n){
		return m_weapon[0]->GetProjectileY(n);
	}

	int GetExistProjectile(int n){
		return m_weapon[0]->GetExistProjectile(n);
	}

	void MoveProjectile(int i, int x, int y){
		m_weapon[0]->Move(i, x, y);
	}

	void SetExistProjectile(int n){
		m_weapon[0]->SetExist(n);
	}

	void PrintProjectile(sf::RenderWindow &window){
		if(m_weaponCek==1){
			m_weapon[0]->PrintProjectile(window);}
	}
};

class CMap{
	CRoad* m_road[30];
	CPowerup powerup[2];
	sf::SoundBuffer bufferDanger;
	sf::Sound soundDanger;

	int m_cekDanger;
	int m_y[30];
public:
	CMap(){
		for(int i=18; i< 30; i++){
			m_road[i]= new CTanah(i,1);
			m_y[i] = i;
		}

		for(int i=0; i<18; i++){
			int randomRoad= rand()%4;
			if(randomRoad==0){m_road[i] = new CSungai(i);}
			if(randomRoad==1){m_road[i] = new CTanah(i);}
			if(randomRoad==2){m_road[i] = new CJalan(i);}
			if(randomRoad==3){m_road[i] = new CRel(i);}
			m_y[i]=i;
		}
		powerup[0].SetExist(0);
		powerup[1].SetExist(0);
		m_cekDanger = 0;

		bufferDanger.loadFromFile("sound/danger.wav");
		soundDanger.setBuffer(bufferDanger);
	}

	int GetCekDanger(){
		return m_cekDanger;
	}

	void SetCekDanger(int n=0){
		m_cekDanger = n;
		soundDanger.play();
	}

	void SetSkill(){
		for(int i=5;i<=15;i++){
			if(GetType(i) == "T"){
				int cek = 0;
				while(cek==0){
					int randX = rand()%30;
					if(CekCrash(randX,i) != 0){
						int random = rand()%2;
						if(random == 0){
							powerup[0].SetUp(0,randX,i);//Freeze
						}
						else{
							powerup[0].SetUp(1,randX,i);//Stealth;
						}
						i = 15;
						cek = 1;
					}
				}
			}
		}
	}

	void SetWeapon(){
		for(int i=15;i>=5;i--){
			if(GetType(i) == "T"){
				int cek = 0;
				while(cek==0){
					int randX = rand()%30;
					if(CekCrash(randX,i) != 0){
						int random = rand()%2;
						if(random == 0){
							powerup[1].SetUp(2,randX,i);//Bomb
						}
						else{
							powerup[1].SetUp(3,randX,i);//Laser;
						}
						i = 1;
						cek = 1;
					}
				}
			}
		}
	}

	void Print(sf::RenderWindow &window){
		for(int i=0; i<30; i++){m_road[i]->Print(window);}
	}

	void PrintPowerup(sf::RenderWindow &window,int skill, int weapon){

		if(powerup[0].GetExist()==1 && skill == 0){powerup[0].Print(window);}
		if(powerup[1].GetExist()==1 && weapon == 0){powerup[1].Print(window);}

	}

	void Move(){
		int temp = m_y[29];
		for(int i = 0; i<30;i++){
			m_road[i]->SetY();
			if(i==29){
				m_y[29-i]= temp;}
			else {
				m_y[29-i]=m_y[28-i];} 
		}

		delete m_road[m_y[0]];
		int randomRoad= rand()%4;
		if(randomRoad==0){m_road[m_y[0]] = new CSungai(0);}
		if(randomRoad==1){m_road[m_y[0]] = new CTanah(0);}
		if(randomRoad==2){m_road[m_y[0]] = new CJalan(0);}
		if(randomRoad==3){m_road[m_y[0]] = new CRel(0);}

		if(powerup[0].GetExist()==1){powerup[0].Move();}
		if(powerup[1].GetExist()==1){powerup[1].Move();}

		if(powerup[0].GetY()>29){powerup[0].SetExist(0);}
		if(powerup[1].GetY()>29){powerup[1].SetExist(0);}
	}

	void MoveObstacle(){
		for(int i=0; i<30; i++){
			m_road[i]->MoveObstacle();	
			m_road[i]->CekCount(i);
		}
	}

	void MoveObstacleAnimation(){
		for(int i=0; i<30; i++){
			m_road[i]->MoveObstacleAnimation();
		}
	}

	void PrintObstacle(sf::RenderWindow &window){
		for(int i=0; i<30; i++){if(m_road[i]->GetType()=="S"){m_road[i]->PrintObstacle(window);}}
	}

	void PrintObstacle2(sf::RenderWindow &window){
		for(int i=0; i<30; i++){if(m_road[i]->GetType()!="S"){m_road[i]->PrintObstacle(window);}}
	}

	std::string GetType(int y){
		return m_road[m_y[y]]->GetType();
	}

	int GetDirection(int y){
		return m_road[m_y[y]]->GetDirection();
	}

	int CekCrash(int x, int y){
		return m_road[m_y[y]]->CekCrash(x);
	}

	void SetExistSkill(int n){
		powerup[0].SetExist(n);
	}
	void SetExistWeapon(int n){
		powerup[1].SetExist(n);
	}

	void Update(){
		if(powerup[0].GetExist() == 0){
			SetSkill();
		}
		if(powerup[1].GetExist() == 0){
			SetWeapon();
		}
	}

	int CekCrashSkill(int x,int y){
		if(x == powerup[0].GetX() && y == powerup[0].GetY()){
			return 1;
		}
		return 0;
	}
	int CekCrashWeapon(int x,int y){
		if(x == powerup[1].GetX() && y == powerup[1].GetY()){
			return 1;
		}
		return 0;
	}

	std::string GetSkillTipe(){
		return powerup[0].GetType();
	}
	std::string GetWeaponTipe(){
		return powerup[1].GetType();
	}

	void SetExistObstacle(int y, int x){
		m_road[m_y[y]]->SetExistObstacle(x);
	}
};
