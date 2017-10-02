#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

void gotoxy(int col, int lin){
	COORD coo;
	coo.X= col;
	coo.Y= lin;
	SetConsoleCursorPosition(
		GetStdHandle( STD_OUTPUT_HANDLE ),coo);
}

void setColor(short C) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, C);
}

class CPosition{
protected:
	int m_x;
	int m_y;
	int m_warna;
public:
	int GetX(){
		return m_x;
	}
	int GetY(){
		return m_y;
	}
	void SetY(int n){
		m_y = n;
	}
	void SetX(int n){
		m_x = n;
	}

	void SetColor(int n){
		m_warna = n;
	}

	int GetColor(){
		return m_warna;
	}
};

class CDensus:public CPosition{
	std::string m_type;
public:
	CDensus(){
		m_x = rand() % 80;
		m_y = rand() % 24;
		m_warna = 1;
		m_type = "D";
		}

	void Move(int fx , int fy){
		int x = fx-m_x;
		int y = fy-m_y; 
		
		int dx=0, dy=0;

		if(x== 0){		
			if(y<0){dy =-1;} else {dy=1;}} 
		else if (y==0){
			if(x<0){dx=-1;}	else {dx=1;}}
		else if(y > x){
			if(x<0){dx=-1;}	else {dx=1;}} 
		else {
			if(y<0){dy =-1;}else {dy=1;}}

		gotoxy(m_x, m_y);
		std::cout << " ";
		m_x+=dx;
		m_y+=dy;
		gotoxy(m_x, m_y);
		std::cout << m_type;
	}
};


class CSkill:public CPosition{
protected:
	int m_duration;
	int m_count;
	std::string m_name;
	std::string m_type;

public:
	CSkill(){
		m_x = 36;
		m_y = 23;
		m_count = 0;
	}
	std::string GetName(){
		return m_name;
	}

	void Print(){
		gotoxy(m_x, m_y);
		setColor(m_warna);
		std::cout << m_type;
	}

	void SetCount(){
		m_count++;
		if(m_count == m_duration){m_count =0;} 
	}

	std::string GetType(){
		return m_type;
	}

	int GetCount(){
		return m_count;
	}
};
class CWeapon: public CSkill{
protected:
	int m_projectile;
	std::string m_projectileType;
	CPosition m_posProjectile;
	int m_dx;
	int m_dy;
	int m_time;
	int m_timeCount;
public:
	CWeapon(){
		m_projectile =0;
		m_dx = 0;
		m_dy = 0;
		m_x = 37;
		m_y = 23;
		m_timeCount=0;
	}

	void Fire(int x, int y,int dx, int dy){
		m_projectile = 1;
		m_timeCount++;

		m_posProjectile.SetX(x);
		m_posProjectile.SetY(y);
		m_posProjectile.SetColor(1);


		if(m_type=="B"){
			m_dx = 0;
			m_dy = 0;
		} 
		else{
			m_dx = dx;
			m_dy = dy;
		}
	}

	void PrintProjectile(){
		gotoxy(m_posProjectile.GetX(),m_posProjectile.GetY());
		std::cout << " ";

		m_posProjectile.SetX(m_posProjectile.GetX()+m_dx);
		m_posProjectile.SetY(m_posProjectile.GetY()+m_dy);	

		gotoxy(m_posProjectile.GetX(),m_posProjectile.GetY());
		std::cout << m_projectileType;

	}

	void SetProjectileCount(){
		m_timeCount++;
		if(m_timeCount==m_time){
			Explode();
			m_timeCount = 0;
			m_projectile = 0;
		}
	}

	int GetProjectile(){
		return m_projectile;
	}

	void Explode(){
		gotoxy(m_posProjectile.GetX()-1,m_posProjectile.GetY());
		std::cout << "*";
		gotoxy(m_posProjectile.GetX()+1,m_posProjectile.GetY());
		std::cout << "*";
		gotoxy(m_posProjectile.GetX(),m_posProjectile.GetY()-1);
		std::cout << "*";
		gotoxy(m_posProjectile.GetX(),m_posProjectile.GetY()+1);
		std::cout << "*";

		Sleep(100);
		gotoxy(m_posProjectile.GetX(),m_posProjectile.GetY());
		std::cout << " ";
		gotoxy(m_posProjectile.GetX()-1,m_posProjectile.GetY());
		std::cout << " ";
		gotoxy(m_posProjectile.GetX()+1,m_posProjectile.GetY());
		std::cout << " ";
		gotoxy(m_posProjectile.GetX(),m_posProjectile.GetY()-1);
		std::cout << " ";
		gotoxy(m_posProjectile.GetX(),m_posProjectile.GetY()+1);
		std::cout << " ";

	}
};
class CBomb:public CWeapon{
public:
	CBomb(){
		m_duration = 100;
		m_name = "Bomb";
		m_type = "B";
		m_warna = 1;
		m_projectileType="8";
		m_time = 10;
	}
};

class CLaser:public CWeapon{
public:
	CLaser(){
		m_duration = 100;
		m_name = "Laser";
		m_type = "L";
		m_warna = 1;
		m_projectileType ="-";
		m_time = 40;
	}
};

class CFreeze:public CSkill{
public:
	CFreeze(){
		m_duration = 100;
		m_name = "Freeze";
		m_type = "F";
		m_warna = 1;
	}
};

class CStealth:public CSkill{
public:
	CStealth(){
		m_duration = 100;
		m_name = "Stealth";
		m_type = "S";
		m_warna = 1;
	}
};

class CObstacle:public CPosition{
protected: 
	std::string m_type;
	int m_length;
	int m_direction;
	int m_available;
public:
	CObstacle(){
		m_available = 1;
	}

	int GetAvailable(){
		return m_available;
	}

	void SetAvailable(int n){
		m_available = n;
	}

	void Move(){
		m_x+=m_direction;
		if(m_x <-2){ m_x = 79;}
		if(m_x >85){ m_x = 0;}
	}

	int GetDirection(){
		return m_direction;
	}

	int GetLength(){
		return m_length;
	}

	void Print(std::string cek, int warna=0){
		if(m_available == 1){
			if(m_direction!=0){
				int direction = m_direction/abs(m_direction);
				for(int i=0; i< m_length; i++){
					int x = m_x-(i*m_direction/abs(m_direction));
					int y = m_y;

					if(i==0){
						for(int j = m_length; j<(m_length+abs(m_direction));  j++){
							gotoxy(m_x-(j*direction), m_y);
							setColor(warna);
							if(m_x-(j*direction)<=79 && m_x-(j*direction)>=0){
								std::cout << cek;
							}
						}
					}

					if(x>= 0 && x<= 79){

						gotoxy(x,y);
						setColor(m_warna);
						std::cout << m_type;
					}
				}
			} 
			else {
				for(int i=0; i< m_length ; i++){
					gotoxy(m_x+i, m_y);
					setColor(m_warna);
					std::cout << m_type;
				}
			}
		}
		else{
			for(int i=0; i< m_length ; i++){
				gotoxy(m_x+i, m_y);
				setColor(warna);
				std::cout << cek;
			}
		}
	}
};

class CCar:public CObstacle{
public:
	CCar(){
		m_length = 2;
		m_direction = -1;
		m_x = 79;
		m_y = 23;
		m_type = "O";
		m_warna = 12;
	}
};

class CTurtle:public CObstacle{
public:
	CTurtle(){
		m_length = 2;
		m_direction = -1;
		m_x = 79;
		m_type = "K";
		m_warna = 8;
	}
};

class CTree:public CObstacle{
public:
	CTree(){
		m_length = 2;
		m_direction = 0;
		m_type = "P";
		m_warna = 5;
	}
};

class CWood:public CObstacle{
public:
	CWood(){
		m_length = 3;
		m_direction = 1;
		m_type = "W";
		m_warna = 7;
	}
};

class CTruck:public CObstacle{
public:
	CTruck(){
		m_length = 3;
		m_direction = 1;
		m_x = 0;
		m_type = "X";
		m_warna = 14;
	}
};

class CTrain :public CObstacle{
public:
	CTrain(){
		m_length = 6;
		m_direction = 5;
		m_x = 0;
		m_type = "K";
		m_warna = 9;
	}
};

class CRoad:public CPosition{
protected:
	CObstacle* m_obstacle[8];
	int m_n;
	int m_danger;
	int m_count;
	std::string m_type;
public:
	void Print(){
		for(int i=0; i<80; i++){
			gotoxy(i,m_y);
			setColor(m_warna);
			std::cout << m_type;
		}
	}

	std::string GetType(){
		return m_type;
	};

	int GetDanger(){
		return m_danger;
	}

	CObstacle* GetObstacle(int n){
		return m_obstacle[n];
	}

	virtual int CekCrash(int x)=0;

	virtual void CekCount(int n)=0;

	int CekObstacle(int n){
		int cek =1;

		int x = m_obstacle[n/10]->GetX();

		for(int i=0; i<m_obstacle[n/10]->GetLength(); i++){
			if(x+i==n){
				cek =0;
			}
		}

		return cek;
	}

	void MoveObstacle(std::string cek){
		for(int i=0; i< m_n; i++){
			m_obstacle[i]->Move();
			m_obstacle[i]->Print(cek, m_warna);
		}
	}

	int GetDirection(){
		return m_obstacle[0]->GetDirection();
	}

	void SetY(){
		m_y =m_y+1;
		if(m_y>23){m_y=0;}

		for(int i=0; i< m_n ; i++){
			m_obstacle[i]->SetY(m_y);
		}
	}
};

class CRel:public CRoad{
public:
	CRel(int n){
		m_y =n;
		m_danger = 0;
		m_type = "R";
		m_n = 0;
		m_warna = 4;
		m_count = rand()%8 +5;
	}

	int CekCrash(int x){
		int HP =1;
		for(int j=0; j<m_obstacle[0]->GetLength(); j++){
			if(x==m_obstacle[0]->GetX()-j){
				HP = 0;
			}
		}
		return HP;
	}

	void CekCount(int n){
		if(m_count == 0){
			m_obstacle[m_n] = new CTrain;
			m_obstacle[m_n]->SetY(n);
			m_n++;

			m_obstacle[m_n] = new CTree;
			m_obstacle[m_n]->SetY(n);
			m_obstacle[m_n]->SetX(40);
			m_n++;
		}

		if(m_n == 2){
			if(m_obstacle[0]->GetX()-m_obstacle[0]->GetLength()>41){
				m_obstacle[1]->SetAvailable(0);
			} else{
				m_obstacle[1]->SetAvailable(1);
			}
		}
		m_count--;
	}
};

class CJalan:public CRoad{
public:
	CJalan(int n){
		m_y =n;
		m_danger = 0;
		m_type = " ";
		m_n = 0;
		m_warna = 6;
		m_count = rand()%8 +5;
	}

	int CekCrash(int x){
		int HP =1;
		for(int i=0; i<m_n; i++){
			for(int j=0; j<m_obstacle[i]->GetLength(); j++){
				if(x==m_obstacle[i]->GetX()-(j*m_obstacle[i]->GetDirection()/abs(m_obstacle[i]->GetDirection()))){
					HP = 0;
				}
			}
		}
		return HP;
	}

	void CekCount(int n){
		if(m_n < 8){
			if(m_count == 0){
				m_count = rand()%8 + 5;
				if(n%2==0){
					m_obstacle[m_n] = new CCar;
				} 
				else{
					m_obstacle[m_n] = new CTruck;
				}
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
		m_danger = 1;
		m_type = "S";
		m_n = 0;
		m_warna = 11;
		m_count = rand()%8 +5;
	}

	void CekCount(int n){
		if(m_n < 8){
			if(m_count == 0){
				m_count = rand()%8 + 5;
				if(n%2==0){
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
		int HP =0;
		for(int i=0; i<m_n; i++){
			for(int j=0; j<m_obstacle[i]->GetLength(); j++){
				if(x==m_obstacle[i]->GetX()-(j*m_obstacle[i]->GetDirection()/abs(m_obstacle[i]->GetDirection()))){
					HP = 1;
				}
			}
		}
		return HP;
	}
};

class CTanah:public CRoad{
public:
	CTanah(int n){
		m_y =n;
		m_danger = 0;
		m_type = "T";
		m_warna = 10;
		m_n =0;

		for(int i=0; i< 8; i++){
			m_obstacle[i]= new CTree;
			m_obstacle[i]->SetY(m_y);
			m_obstacle[i]->SetX(rand()%8 + i*10);
			m_n++;
		}
	}

	void CekCount(int n){
	}

	int CekCrash(int x){
		int HP =1;
		for(int i=0; i<m_n; i++){
			for(int j=0; j<m_obstacle[i]->GetLength(); j++){
				if(x==m_obstacle[i]->GetX()+j){
					HP = 0;
				}
			}
		}
		return HP;
	}
};

class CTerror: public CPosition{
	CSkill* m_skill[1];
	CWeapon* m_weapon[1];
public:
	CTerror(){
		m_x = 40;
		m_y = 24;
		m_warna = 15;
		setColor(m_warna);
		gotoxy(m_x, m_y);
		std::cout << "F";

		m_weapon[0]= new CBomb;
		m_skill[0]= new CFreeze;
	}


	void Move(int dx, int dy, std::string cek ="0", int cekcolor=0){
		if(cek != "0" && cekcolor != 0){
			gotoxy(m_x, m_y);
			setColor(cekcolor);
			std::cout << cek;
		}

		m_x+=dx;
		m_y+=dy;
		if(m_x<0){m_x=0;}
		if(m_x>79){m_x=79;}
		if(m_y<0){m_y=0;}
		if(m_y>24){m_y=24;}
	}

	void Print(){
		setColor(m_warna);
		gotoxy(m_x, m_y);
		std::cout << "F";
	}

	void SetSkill(CSkill* skill){
		m_skill[0]= skill;
	}

	void SetSkillCount(){
		m_skill[0]->SetCount();
	}

	int GetSkillCount(){
		return m_skill[0]->GetCount();
	}

	std::string GetSkillName(){
		return m_skill[0]->GetName();
	}

	std::string GetSkillType(){
		return m_skill[0]->GetType();
	}

	void SetWeapon(CWeapon* skill){
		m_weapon[0]= skill;
	}

	void SetWeaponCount(){
		m_weapon[0]->SetCount();
	;}

	int GetWeaponCount(){
		return m_weapon[0]->GetCount();
	}

	int GetProjectile(){
		return m_weapon[0]->GetProjectile();
	}

	void SetProjectileCount(){
		m_weapon[0]->SetProjectileCount();
	}

	std::string GetWeaponName(){
		return m_weapon[0]->GetName();
	}

	std::string GetWeaponType(){
		return m_weapon[0]->GetType();
	}

	void Fire(int dx, int dy){
		m_weapon[0]->Fire(m_x, m_y, dx, dy);
	}

	void PrintProjectile(){
		m_weapon[0]->PrintProjectile();
	}
};


int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(960,768), "My first ");

	srand(time(NULL));
	CRoad* roadMap[50];

	int posY[50];
	for(int i=0; i<50; i++){
		int randomRoad= rand()%4;
		if(randomRoad==0){roadMap[i] = new CSungai(i);}
		if(randomRoad==1){roadMap[i] = new CTanah(i);}
		if(randomRoad==2){roadMap[i] = new CJalan(i);}
		if(randomRoad==3){roadMap[i] = new CRel(i);}
		roadMap[i]->Print();
		posY[i]=i;
	}

	sf::Vector2u size(400,400);
	sf::Vector2i sizei(200,200);
	sf::Clock clock;
	sf::Time time;
	sf::Vector2i move(0,0);



	int i=0;
	window.setSize(size);
	window.setTitle("Cba");
	window.setPosition(sizei);

	sf::Texture texture;
	sf::Texture textureGrass;
	sf::Texture textureWater;
	sf::Texture textureRoad ;
	sf::Texture textureRail;
	sf::Sprite player;
	sf::Sprite grass;
	sf::Sprite water;
	sf::Sprite road;
	sf::Sprite rail;
	texture.loadFromFile("player.png");
	textureGrass.loadFromFile("grass.png");
	textureWater.loadFromFile("water.gif");
	textureRoad.loadFromFile("road.png");
	textureRail.loadFromFile("rsz_rail.png");
			int x =0;
	player.setTexture(texture);
	grass.setTexture(textureGrass);
	water.setTexture(textureWater);
	road.setTexture(textureRoad);
	rail.setTexture(textureRail);
	sf::Time timeMap;
	sf::Clock clockMap;
	player.setPosition(800,704);
	float count =0, maxcount = 100;

	sf::View view;
	view.reset(sf::FloatRect(0,0,960, 768));
	view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));
	sf::Vector2f pos(352,160);

	while(window.isOpen()){
		sf::Event event;

		while(window.pollEvent(event)){
			if(event.type==sf::Event::Closed){
				window.close();
			}

			if(event.type==sf::Event::LostFocus){
				std::cout<<"lost"<<std::endl;
			}


		}

		if(event.type==sf::Event::KeyPressed){
			if(event.key.code==sf::Keyboard::Return){
				
				i++;
				system("cls");
			}
			if(event.type==sf::Event::TextEntered){
				system("cls");
			}

			if(time.asMilliseconds()>100){

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				move.y =3;
				int temp= posY[49];
			for(int i = 0; i<50;i++){
				roadMap[i]->SetY();
				if(i==49){
					posY[0]=temp;}
				else {
					posY[49-i]=posY[48-i];} 
			}
				//player.move(0,-32);
			pos.y +=32; 
			
		if(pos.y>256){pos.y = 256;}
		std::cout<<pos.y<<std::endl;

			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				move.y =0;	
				player.move(0,32);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				move.y =1;	
				player.move(-32,0);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				move.y =2;	
				player.move(32,0);
			}

			clock.restart();		
		}
		pos.x = player.getPosition().x +32 - 480;
		if(pos.x< 0){pos.x = 0;}
		}
		time=clock.getElapsedTime();

		move.x++;
			
			if(move.x>2){
				move.x=0;
			}
		
		player.setTextureRect(sf::IntRect(move.x*32,move.y*32, 32,32));



		timeMap=clockMap.getElapsedTime();
		if(timeMap.asMilliseconds()>100){
			pos.y-=3.2;
			clockMap.restart();
		}

		grass.setPosition(0,0);
		water.setPosition(0,0);
		road.setPosition(0,0);
		rail.setPosition(0,0);

		for(int i=0; i<50; i++){
			for(int j=0; j< 50; j++){
			if(roadMap[posY[i]]->GetType()=="S"){window.draw(water);}
			if(roadMap[posY[i]]->GetType()=="T"){window.draw(grass);}
			if(roadMap[posY[i]]->GetType()=="R"){window.draw(rail);}
			if(roadMap[posY[i]]->GetType()==" "){window.draw(road);}

			grass.move(32,0);
			road.move(32,0);
			water.move(32,0);
			rail.move(32,0);
			}
		grass.move(-1600,32);
		water.move(-1600,32);
		road.move(-1600,32);
		rail.move(-1600,32);

		}

		view.reset(sf::FloatRect(pos.x,pos.y,960, 600));
		window.draw(player);
		window.setView(view);
		window.display();
		window.clear();	
		
	}

}