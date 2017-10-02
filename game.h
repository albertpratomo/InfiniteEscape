#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>

#include "class.h"

class CButton{
private:
	sf::Texture textureButton;
	sf::Sprite spriteButton;
	sf::Font fontButton;
	sf::Text textButton;
public:
	CButton(){
		textureButton.loadFromFile("images/button.png");
		spriteButton.setTexture(textureButton);
		spriteButton.setScale(0.6, 0.6);
		fontButton.loadFromFile("font/font.ttf");
		textButton.setFont(fontButton);
		textButton.setColor(sf::Color::Black);
		textButton.setCharacterSize(30);
		textButton.setString("Click here");
		textButton.setOrigin(textButton.getGlobalBounds().width / 2, textButton.getGlobalBounds().height / 2);
		textButton.setPosition(spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().height / 2);
	}
	CButton(char *nama){
		textureButton.loadFromFile("images/button.png");
		spriteButton.setTexture(textureButton);
		spriteButton.setScale(0.6, 0.6);
		fontButton.loadFromFile("font/font.ttf");
		textButton.setString(nama);
		textButton.setFont(fontButton);
		textButton.setColor(sf::Color::Black);
		textButton.setCharacterSize(30);
		textButton.setOrigin(textButton.getGlobalBounds().width / 2, textButton.getGlobalBounds().height / 2);
		textButton.setPosition(spriteButton.getGlobalBounds().left + spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().top + spriteButton.getGlobalBounds().height / 2);
	}
	CButton(std::stringstream nama){
		textureButton.loadFromFile("images/button.png");
		spriteButton.setTexture(textureButton);
		spriteButton.setScale(0.6, 0.6);
		fontButton.loadFromFile("font/font.ttf");
		textButton.setString(nama.str());
		textButton.setFont(fontButton);
		textButton.setColor(sf::Color::Black);
		textButton.setCharacterSize(30);
		textButton.setOrigin(textButton.getGlobalBounds().width / 2, textButton.getGlobalBounds().height / 2);
		textButton.setPosition(spriteButton.getGlobalBounds().left + spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().top + spriteButton.getGlobalBounds().height / 2);
	}

	CButton(std::string nama){
		textureButton.loadFromFile("images/button.png");
		spriteButton.setTexture(textureButton);
		spriteButton.setScale(0.6, 0.6);
		fontButton.loadFromFile("font/font.ttf");
		textButton.setString(nama);
		textButton.setFont(fontButton);
		textButton.setColor(sf::Color::Black);
		textButton.setCharacterSize(30);
		textButton.setOrigin(textButton.getGlobalBounds().width / 2, textButton.getGlobalBounds().height / 2);
		textButton.setPosition(spriteButton.getGlobalBounds().left + spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().top + spriteButton.getGlobalBounds().height / 2);
	}

	void draw(sf::RenderWindow &window){
		window.draw(spriteButton);
		window.draw(textButton);
	}
	void settext(char *nama){
		textButton.setString(nama);
	}

	void settext(std::string nama){
		textButton.setString(nama);
	}
	void setPosition(float x, float y){
		spriteButton.setPosition(x, y);
		textButton.setPosition(spriteButton.getGlobalBounds().left + spriteButton.getGlobalBounds().width / 2, spriteButton.getGlobalBounds().top + spriteButton.getGlobalBounds().height / 2);
	}
	bool isClicked(float x, float y){
		if(spriteButton.getGlobalBounds().contains(x, y)){

			return true;
		}
		return false;
	}
	float getX(){
		return spriteButton.getPosition().x;
	}
	float getY(){
		return spriteButton.getPosition().y;
	}
};

class CBar{
	sf::Text textScore;
	sf::Text textTime;
	sf::Text textWeapon;
	sf::Text textSkill;
	sf::Font font;
	sf::Texture textureBar;
	sf::Sprite spriteBar;
	sf::Sprite spriteBorder;
	sf::Texture textureBorder;

	std::stringstream stringscore;
	std::stringstream stringtime;
	std::stringstream stringskill;
	std::stringstream stringweapon;
public:
	CBar(){
		font.loadFromFile("font/font.ttf");
		textureBorder.loadFromFile("images/bardanger.png");
		textureBar.loadFromFile("images/bardanger1.png");
		spriteBar.setTexture(textureBar);
		spriteBorder.setTexture(textureBorder);
		spriteBar.setTextureRect(sf::IntRect(0,0,1, 42));
		textScore.setFont(font);
		textTime.setFont(font);
		textSkill.setFont(font);
		textWeapon.setFont(font);
	}

	void SetString(int score, int time, std::string weaponType, std::string skillType, int n , int s){
		stringscore.str("");
		stringtime.str("");
		stringskill.str("");
		stringweapon.str("");

		if(skillType == "F"){
			stringskill<< "FREEZE " << s;
		} 
		else if(skillType == "S"){
			stringskill<<"STEALTH " << s;
		}
		


		if(weaponType == "B"){
		stringweapon<<"BOM X" <<5-n;
		} 
		else if(weaponType == "L"){
			stringweapon<<"LASER X" <<5-n;
		}
		

		stringscore<<"SCORE: " <<score;
		stringtime <<"TIME: "<<time;


		textScore.setString(stringscore.str());
		textTime.setString(stringtime.str());
		textSkill.setString(stringskill.str());
		textWeapon.setString(stringweapon.str());
	}
	
	void Print(float time, float y, sf::RenderWindow &window){
		textTime.setPosition(20, y+20 );
		textScore.setPosition(20, y+64 );
		textWeapon.setPosition(720, y+20 );
		textSkill.setPosition(720, y+64 );
		spriteBar.setPosition(308, y+32);
		spriteBorder.setPosition(308, y+32);
		spriteBar.setTextureRect(sf::IntRect(0,0,(time/20.0)*335, 42));


		window.draw(spriteBar);
		window.draw(spriteBorder);
		window.draw(textScore);
		window.draw(textSkill);
		window.draw(textWeapon);
		window.draw(textTime);		
	}

};

class CGame{
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	int m_score;
	sf::Font font;
	sf::Sprite spritePause;
	sf::Sprite spriteResume;
	sf::Sprite spriteRestart;
	sf::Sprite spriteButtonmenu;
	sf::Sprite spriteMenu;
	sf::Sprite spriteStart;
	sf::Sprite spriteHigh;
	sf::Sprite spriteBack;
	sf::Sprite spriteOver;
	sf::Sprite spriteHighscore;
	sf::Texture textureHighscore;
	sf::Texture textureBack;
	sf::Texture textureStart;
	sf::Texture textureHigh;
	sf::Texture textureMenu;
	sf::Texture textureOver;

	sf::Texture texturePause;
	sf::Texture textureRestart;
	sf::Texture textureResume;
	sf::Texture textureButtonmenu;

public:
	CGame(){
		window.create(sf::VideoMode(960,768), "Infinite Escape");
		font.loadFromFile("font/font.ttf");

		texturePause.loadFromFile("images/pause.png");
		textureRestart.loadFromFile("images/buttonrestart.png");
		textureResume.loadFromFile("images/buttonresume.png");
		textureButtonmenu.loadFromFile("images/buttonmenu.png");

		textureStart.loadFromFile("images/buttonplay.png");
		textureMenu.loadFromFile("images/menu.png");
		textureHigh.loadFromFile("images/buttonhighscore.png");
		
		textureBack.loadFromFile("images/buttonback.png");
		textureHighscore.loadFromFile("images/highscore.png");

		textureOver.loadFromFile("images/gameover.png");

		spriteStart.setTexture(textureStart);
		spriteMenu.setTexture(textureMenu);
		spriteHigh.setTexture(textureHigh);
		
		spritePause.setTexture(texturePause);
		spriteRestart.setTexture(textureRestart);
		spriteResume.setTexture(textureResume);
		spriteButtonmenu.setTexture(textureButtonmenu);

		spriteRestart.setTextureRect(sf::IntRect(0,0,358, 97));
		spriteResume.setTextureRect(sf::IntRect(0,0,358, 97));
		spriteButtonmenu.setTextureRect(sf::IntRect(0,0,358, 97));
		
		spriteBack.setTexture(textureBack);
		spriteHighscore.setTexture(textureHighscore);

		spriteOver.setTexture(textureOver);
	}

	int SetViewY(int pos){
		pos += 32;
		if(pos > 160){pos = 160;}
		return pos;
	}

	void Menu(){
		spriteMenu.setPosition(0,0);
		spriteStart.setPosition(301,450);
		spriteHigh.setPosition(301,550);
		
		while (window.isOpen()){
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed){
					window.close();
				}
				if(spriteStart.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)){
					spriteStart.setTextureRect(sf::IntRect(0,97,358, 97));
				} 
				else{
					spriteStart.setTextureRect(sf::IntRect(0,0,358, 97));
				}

				if(spriteHigh.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)){
					spriteHigh.setTextureRect(sf::IntRect(0,97,358, 97));
				} 
				else {
					spriteHigh.setTextureRect(sf::IntRect(0,0,358, 97));
				} 
				
				if (event.type == sf::Event::MouseButtonPressed){
					if (event.mouseButton.button == sf::Mouse::Left){
						if(spriteStart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
							Run();
						}
						if(spriteHigh.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
							Highscore();
						}
					}
				}
			}

			view.reset(sf::FloatRect(0, 0, 960, 768));//ngereset posisi dari view
			window.setView(view);
			window.clear();
			window.draw(spriteMenu);
			window.draw(spriteStart);
			window.draw(spriteHigh);
			
			window.display();
		}
	}

	void Highscore(){
		std::fstream fio;
		spriteHighscore.setPosition(0,0);
		spriteBack.setPosition(374, 600);
		sf::Text textNama;
		sf::Text textScore;
		textNama.setFont(font);
		textScore.setFont(font);
		textNama.setCharacterSize(25);
		textScore.setCharacterSize(25);

		std::stringstream nama[11];
		std::stringstream score[11];

		char namahigh[11][100];
		int highscore[11];
		int co =0;
		fio.open("Highscore.txt", std::ios::in);
		while(!fio.eof()){
			fio.getline(namahigh[co], 100);
			fio>> highscore[co];
			nama[co]<< namahigh[co];
			score[co]<< highscore[co];

			if(!fio.eof()){
				co++;}
			fio.getline(namahigh[co], 100);
		}
		fio.close();

		while(true){
			while(window.pollEvent(event)){
				
				if(event.type==sf::Event::Closed){
					window.close();
				}

				if(spriteBack.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)){
					spriteBack.setTextureRect(sf::IntRect(0,80,212, 80));
				} 
				else{
				spriteBack.setTextureRect(sf::IntRect(0,0,212, 80));
				}

				if (event.mouseButton.button == sf::Mouse::Left){
					if(spriteBack.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)){
						Menu();
					}
				}

				window.clear();
				window.draw(spriteHighscore);
				window.draw(spriteBack);
				for(int i=0; i< co; i++){
					textNama.setString(nama[i].str());
					textScore.setString(score[i].str());

					textNama.setPosition(260, (i+6.5)*35);
					textScore.setPosition(650, (i+6.5)*35);
					
					window.draw(textNama);
					window.draw(textScore);

				}
				window.display();

				
			}
		}
	}

	int Resume(int posViewY){
		spritePause.setPosition(0, posViewY);
		spriteResume.setPosition(301,posViewY+300);
		spriteRestart.setPosition(301,posViewY+400);
		spriteButtonmenu.setPosition(301,posViewY+500);

		int m_pause=1;
		while(window.pollEvent(event)){
			if(event.type==sf::Event::Closed){
				window.close();
			}
			if(event.type==sf::Event::MouseEntered){
				m_pause = 0;
			} 	

			if(spriteRestart.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y+posViewY)){
					spriteRestart.setTextureRect(sf::IntRect(0,97,358, 97));
				} 
			else{
				spriteRestart.setTextureRect(sf::IntRect(0,0,358, 97));
			}

			if(spriteResume.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y+posViewY)){
				spriteResume.setTextureRect(sf::IntRect(0,97,358, 97));
			} 
			else {
				spriteResume.setTextureRect(sf::IntRect(0,0,358, 97));
			} 
			if(spriteButtonmenu.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y+posViewY)){
				spriteButtonmenu.setTextureRect(sf::IntRect(0,97,358, 97));
			} 
			else {
				spriteButtonmenu.setTextureRect(sf::IntRect(0,0,358, 97));
			} 


			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left){
					if(spriteRestart.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y+posViewY)){
						m_pause = 3;
					}
					if(spriteButtonmenu.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y+posViewY)){
						m_pause = 4;
					}
					if(spriteResume.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y+posViewY)){
						m_pause = 0;
					}
				}
			}
		}	
		window.draw(spritePause);
		window.draw(spriteResume);
		window.draw(spriteRestart);
		window.draw(spriteButtonmenu);

		return m_pause;
	}

	char* InputNama(){
		int nn=0;
		char namahighscore[100];

		sf::Text textNew;

		sf::Texture textureNew;
		sf::Sprite spriteNew;
		
		textureNew.loadFromFile("images/newhighscore.png");
		spriteNew.setTexture(textureNew);

		textNew.setFont(font);
		textNew.setCharacterSize(50);
		textNew.setPosition(295,527);
		spriteNew.setPosition(0,0);
		view.reset(sf::FloatRect(0, 0, 960, 768));//ngereset posisi dari view
		window.setView(view);
		namahighscore[nn]='\0';
		while(nn<10){
			while(window.pollEvent(event)){
				if(event.type==sf::Event::Closed){
					window.close();
				}
				if(event.type==sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Return) ){
					nn=20;
				}
				else if(event.type == sf::Event::TextEntered) {
					if(event.text.unicode==8){
						nn--;
						namahighscore[nn]='\0';
					} 
					else{
						namahighscore[nn]=toupper((char)event.text.unicode);
						nn++;
						namahighscore[nn]='\0';
					}	
				}
			}

			textNew.setString(namahighscore);
			window.draw(spriteNew);
			window.draw(textNew);
			
			window.display();
			window.clear();
		}
		return namahighscore;
	}

	void CekHighScore(int n){
		std::fstream fio;
		int highscore[10];
		char namahigh[11][100];
		int co=0;

		fio.open("Highscore.txt", std::ios::in);

		while(!fio.eof()){
			fio.getline(namahigh[co], 100);
			fio>> highscore[co];
			if(!fio.eof()){
				co++;}
			fio.getline(namahigh[co], 100);
		}
		fio.close();

		if(co <10){co++;}


		for(int i=0; i< co; i++){
			if(m_score > highscore[i]){
				for(int j=co-1; j>=i; j--){
					strcpy(namahigh[j], namahigh[j-1]);
					highscore[j]=highscore[j-1];
				}
				strcpy(namahigh[i],InputNama());
				highscore[i]= m_score;
				i =co;
			}
		}
		
		fio.open("Highscore.txt", std::ios::out);
		for(int i = 0; i< co; i++){
			fio<<namahigh[i]<<std::endl;
			fio<<highscore[i]<<std::endl;
		}
		fio.close();
	}

	void Run(){
		srand(time(NULL));
		view.reset(sf::FloatRect(0,0,960, 768));
		view.setViewport(sf::FloatRect(0,0,1.0f,1.0f));

		sf::Clock clockGame;//waktu game

		sf::Time timeGame;
		sf::Time timeDanger;
		sf::Time timeObstacle;
		sf::Time timeMap;
		sf::Time timeMove;
		sf::Time timeDensus;

		CTerror terror;
		CMap map;
		CPowerup powerup[2];
		CDensus densus[5];

		int m_pause = 0;
		float posViewY=160;
		sf::SoundBuffer bufferOver;
		sf::Sound soundOver;
		bufferOver.loadFromFile("sound/over.wav");
		soundOver.setBuffer(bufferOver);
		soundOver.setLoop(true);

		sf::SoundBuffer bufferRun;
		sf::Sound soundRun;
		bufferRun.loadFromFile("sound/run.wav");
		soundRun.setBuffer(bufferRun);
		soundRun.setLoop(true);

		sf::SoundBuffer bufferExplode;
		sf::Sound soundExplode;
		bufferExplode.loadFromFile("sound/explode.wav");
		soundExplode.setBuffer(bufferExplode);

		sf::SoundBuffer bufferType;
		sf::Sound soundType;
		bufferType.loadFromFile("sound/type.wav");
		soundType.setBuffer(bufferType);

		sf::Vector2i move(0,0);

		int nmove=0;
		int nProjectile=0;
		int duration=0;

		int HP = 1;
		std::string skillType;
		std::string weaponType;

		int dx = 0, dy = 0;
		int y = terror.GetY();
		int x = terror.GetX();

		int saveMap[24][30];
		int indexDensus = -1;
		int cekDensus =0;

		terror.SetWeapon("B");

		CBar bar;

		m_score=0;
		soundRun.play();
		while(window.isOpen() && HP == 1){
			
			if(m_pause == 0){

				timeGame += clockGame.getElapsedTime();
				timeDanger +=  clockGame.getElapsedTime();
				timeObstacle += clockGame.getElapsedTime();
				timeMap += clockGame.getElapsedTime();
				timeMove += clockGame.getElapsedTime();
				timeDensus += clockGame.getElapsedTime();

				clockGame.restart();
				
				
				y = terror.GetY();
				x = terror.GetX();

				//mengecek tabrakan frogger dengan halangan, dengan parameter koordinat frogger
				HP = map.CekCrash(x, y);

				if(HP == 0 && map.GetType(y)== "S"){terror.SetImage();}

				if(terror.GetSkillCount()==1){//mengambil tipe skill jika frogger punya skill
					skillType= terror.GetSkillType();
					duration = terror.GetSisaCount();
				} 
				else{skillType = "U";duration = 0;}

				if(terror.GetWeaponCount()==1){//mengambil tipe skill jika frogger punya skill
					weaponType= terror.GetWeaponType();
					nProjectile = terror.GetProjectileCount();} 
				else{weaponType = "U"; nProjectile = 0;}
			

				if(timeDanger.asMilliseconds()<=20000 && map.GetCekDanger()==0){//jika waktu kurang dari 100000, map n obstacle akan move
					if(skillType != "F"){//jika tipe skill bukan Freeze maka obstacle boleh dimove 
						if(timeMap.asMilliseconds() >= 50){//screen scrolling tiap 50 milisecond sejauh 0.32 
							posViewY-=0.32;
							timeMap = sf::seconds(0);
						}
						if(timeObstacle.asMilliseconds()>=200){
							map.MoveObstacleAnimation();
							timeObstacle= sf::seconds(0);
							nmove++;
						}
						if(nmove==1){//tiap 200 ms lakukan move obstacle
							if(map.GetType(y) == "S" && HP == 1){//cek jika tipe road adalah sungai, tapi HP masih 1. berarti frogger naik obstacle
								terror.Move(map.GetDirection(y), 0);	
							} 

							if(weaponType == "B"){//jika tipe weapon bom 
								for(int i =0; i< terror.GetProjectileCount(); i++){
									if(map.GetType(terror.GetProjectileY(i))=="S"){//jika iya bom ikut bergerak
										terror.MoveProjectile(i, map.GetDirection(terror.GetProjectileY(i)),0);
									}
								}
							}  
							nmove=0;
							map.MoveObstacle();
						}
					}
				} 
				else {//masuk mode danger
					
					int minY = ceil(posViewY/32.0);
					for(int i=minY,q=0;i<minY+24;i++,q++){//update saveMap
						for(int j=0;j<30;j++){
							if(map.CekCrash(j,i)==0){//terjadi crash dengan obstacle
								saveMap[q][j]=-1;// -1 = crash dengan obstacle
							}
							else{
								saveMap[q][j]=-2;// -2 = BFS belum diisi
							}		
						}
					}
					
					if(map.GetCekDanger()==1){//jika sudah berada di mode danger

						if(timeDensus.asMilliseconds()>=400 && skillType!="F"){//jika sudah waktunya densus bergerak dan tidak sedang freeze
							bool status = true;
							int co=1;
							x = terror.GetX();
							y = terror.GetY() - ceil(posViewY/32.0);

							saveMap[y][x]=0;
							if(saveMap[y][x+1]==-2){saveMap[y][x+1]=co;}
							if(saveMap[y][x-1]==-2){saveMap[y][x-1]=co;}
							if(saveMap[y+1][x]==-2){saveMap[y+1][x]=co;}
							if(saveMap[y-1][x]==-2){saveMap[y-1][x]=co;}
		
							while(status){//saveMap diisi dengan BFS
								bool flag=true;
								for(int i=23;i>=0;i--){
									for(int j=0;j<30;j++){
										if(saveMap[i][j]==co){
											if(saveMap[i][j+1]==-2 && j+1 <=29){saveMap[i][j+1]=co+1;flag=false;}
											if(saveMap[i][j-1]==-2 && j-1 >=0){saveMap[i][j-1]=co+1;flag=false;}
											if(saveMap[i+1][j]==-2 && i+1 <=23){saveMap[i+1][j]=co+1;flag=false;}
											if(saveMap[i-1][j]==-2 && i-1 >=0){saveMap[i-1][j]=co+1;flag=false;}			
										}
									}
								}
								co++;
								if(flag){status=false;}
							}

							for(int i=0;i<5;i++){
								if(densus[i].GetExist()==1){
									densus[i].DecideMove(saveMap);
									saveMap[densus[i].GetY()][densus[i].GetX()]=-1; //lokasi densus diberi -1,agar densus lain tidak menabrak kesana
								}
							}				
							timeDensus= sf::seconds(0);
						}

						cekDensus = 0;
						for(int i=0;i<5;i++){
							if(densus[i].GetExist()==0){
								cekDensus++; //cek jumlah densus yang mati
							}
						}
						if(cekDensus == 5 && timeDanger.asMilliseconds() >=200){//keluar dari mode danger
							y = terror.GetY();
						
							if(y>=22){
								map.SetCekDanger(0);
								soundRun.play();
							}
							else{
								map.Move();
								terror.Move(0,1);
							}
							timeDanger = sf::seconds(0);
						}
					}
					else{//jika baru memasuki mode danger
						soundRun.stop();
						map.SetCekDanger(1);//jika waktu lebih dari 10000, masuk ke mode danger

						std::fstream fio;
						char textDensus[25][6];
						int co=0;

						fio.open("TextDensus.txt", std::ios::in);//load dan random text densus
						while(!fio.eof()){
							fio.getline(textDensus[co++], 6);
						}
						fio.close();

						for(int i=0;i<5;i++){
							densus[i].SetExist(1,posViewY);
							densus[i].SetPosition(saveMap,i);
							saveMap[densus[i].GetY()][densus[i].GetX()]=-1;
							int randomText =  i * 5 + (rand()%5);
							densus[i].SetText(textDensus[randomText]);
						}

						terror.SetMinY(posViewY);
					}	
				}


				if( map.GetType(y) != "S" && HP==0 && skillType== "S"){HP = 1;}// jika skilltype = stealth dan HP 0 dan map bukan sungai, maka frogger tetap hidup


				int yy = 30;
				while(window.pollEvent(event)){

					if(event.type==sf::Event::Closed){
						window.close();
						soundRun.stop();
					}

					if(event.type==sf::Event::MouseLeft) {
						m_pause = 1;//mouse keluar dari window, game dipause
					}

					if(event.type==sf::Event::KeyPressed){

						if(timeMove.asMilliseconds() > 100){
							if(weaponType!="U"){
								if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
									terror.Fire();
								}
							}
							if(event.key.code==sf::Keyboard::Escape){
								m_pause = 1;//pencet escape game dipause
							}
							if(event.key.code==sf::Keyboard::Up){
								terror.MoveUp();
								yy = y;
								dx = 0;
								dy = -1;
								terror.Move(dx,dy);
							}

							if(event.key.code==sf::Keyboard::Down){
								terror.MoveDown();
								dx = 0; 
								dy = 1;
								terror.Move(dx,dy);
							}

							if(event.key.code==sf::Keyboard::Left){
								terror.MoveLeft();
								dx = -1; 
								dy = 0;
								terror.Move(dx,dy);
							}

							if(event.key.code==sf::Keyboard::Right){
								terror.MoveRight();
								dx = 1; 
								dy = 0;
								terror.Move(dx,dy);
							}

							x = terror.GetX();
							y = terror.GetY();

							if(map.GetCekDanger() == 1 || skillType == "F"){// cek apakah lagi danger atau skill freeze
								if(skillType=="F"){//jika freeze, map tetap bisa scrolling ketika frogger naik terus
									if(dy == -1){
										if(y == 22 && yy == 22){
											map.Move();
											m_score++;
											if(weaponType!="U"){
												for(int i=0; i< terror.GetProjectileCount(); i++){//gerakan y projectile jika map dimove
													terror.MoveProjectile(i,0,1);
												}
											}
										}
										posViewY = SetViewY(posViewY); 
									}
								}
								if(map.GetCekDanger() == 1){
									if(dy==-1){m_score++;}
									else if(dy==1){m_score--;}
								}//score tetap tambah mskipun di mode danger, kurang kalau densus turun

								HP = map.CekCrash(x, y);// cek tabrakan

								if(HP == 0 && map.GetType(y) == "S"){terror.SetImage();}//terror tercebur
								else if(HP == 0 ){//jika ada halangan, maka frogger tidak jadi bergerak
									if(skillType != "S"){
										terror.Move(-dx,-dy);
										dx = 0;
										dy = 0;
									}
									HP = 1;
								}
							} 
							else {
								if(yy == y){y--;}

								if(map.GetType(y)=="T" && skillType != "S"){//jika tipe map Tanah dan di depannya ada pohon, frogger tidak jadi bergerak. klo ada skill Stealth, frogger tembus
									if(map.CekCrash(x, y) == 0){
										if(y == 21){dy = 0;}
										terror.Move(-dx,-dy);
										dx = 0;
										dy = 0;
									}
								} 

								x = terror.GetX();
								y = terror.GetY();

								if(dy == -1){
									if(y == 22 && yy == 22){
										map.Move();
										m_score++;
										if(weaponType!="U"){
											for(int i=0; i< terror.GetProjectileCount(); i++){
												terror.MoveProjectile(i,0,1);
											}
										}
									}
									posViewY = SetViewY(posViewY); 
								}
							}
							dx=0; dy=0;
							timeMove = sf::seconds(0);
							terror.MoveX();//gerak animasi dari frogger, belum ada cek waktunya. jadi geraknya kecepeten
						}
					}
					if(map.GetCekDanger()==1& event.type == sf::Event::TextEntered){
						char type;
						type=(char)event.text.unicode;
						type = toupper(type);

						if(isalpha(type)){
							if(indexDensus == -1){
								for(int i=0;i<5;i++){
									if(densus[i].GetExist() == 1 && densus[i].CekType(type)){
										densus[i].SetType(type);
										soundType.play();
										indexDensus = i;
										break;
									}
								}
							}
							else{
								if(densus[indexDensus].CekType(type)){
									soundType.play();
									if(densus[indexDensus].SetType(type)){
										densus[indexDensus].SetImage();
										indexDensus = -1;
										soundExplode.play();
									}
								}
							}
						}
					}
				}
				bar.SetString(m_score, floor(timeGame.asSeconds()), weaponType, skillType, nProjectile, duration);

				view.reset(sf::FloatRect(0, posViewY, 960, 768));//ngereset posisi dari view


				if(posViewY-(y-22)*32<0){HP=0;}//jika posisi view lebih kecil dari 0, frogger mati

				if(terror.GetSkillCount()==1){//jika ada skill, lakukan skillcount, lalu dicek skillcount. jika sudah 0, powerup skill dimunculkan dengan mengubah exist jadi 0
					terror.SetSkillCount();

					if(terror.GetSkillCount()==0){
						map.SetExistSkill(0);} 
				};

				if(terror.GetWeaponCount()==1){
					terror.SetWeaponCount();
					if(weaponType == "L"){
						int cekCrash;
						for(int i = 0; i< terror.GetProjectileCount(); i++){
							if(terror.GetExistProjectile(i) == 1){
								if(terror.GetProjectileX(i)<30 && terror.GetProjectileX(i)>-1 && terror.GetProjectileY(i)>-1 && terror.GetProjectileY(i)<30){
									cekCrash= map.CekCrash(terror.GetProjectileX(i), terror.GetProjectileY(i));
									for(int l=0; l< 5;l++){
											if(densus[l].GetExist()==1){
												if( densus[l].GetX() ==terror.GetProjectileX(i) && densus[l].GetY()+ceil(posViewY/32) == terror.GetProjectileY(i) ){
													if(l == indexDensus){indexDensus = -1;};
													densus[l].SetImage();
													terror.SetExistProjectile(i);
													densus[l].SetExist(-180, posViewY);
													soundExplode.play();
												}
											}
										}


									if(map.GetType(terror.GetProjectileY(i))!="S" && cekCrash==0){
										terror.SetExistProjectile(i);
										map.SetExistObstacle(terror.GetProjectileY(i),terror.GetProjectileX(i));
										soundExplode.play();
									}
								}
							}
						}
					}

					if(weaponType == "B"){
						int cekCrash;
						for(int i = 0; i< terror.GetProjectileCount(); i++){
							if(terror.GetExistProjectile(i) <0 ){
								for(int j=-1; j<2; j++){
									for(int k = -1; k<2; k++){
										if(terror.GetProjectileX(i)+j<30 && terror.GetProjectileX(i)+j>-1 && terror.GetProjectileY(i)+k>-1 && terror.GetProjectileY(i)+k<30){
											x=terror.GetX();
											y=terror.GetY();
											if(x == terror.GetProjectileX(i)+j && y == terror.GetProjectileY(i)+k ){HP = 0; terror.SetImage(1);}
											
											for(int l=0; l< 5;l++){
												if(densus[l].GetExist()==1){
													if( densus[l].GetX() ==terror.GetProjectileX(i)+j && densus[l].GetY()+ceil(posViewY/32) == terror.GetProjectileY(i)+k ){
														if(l == indexDensus){indexDensus = -1;};
														densus[l].SetImage();
														densus[l].SetExist(-180, posViewY);
													}
												}
											}
											
											cekCrash= map.CekCrash(terror.GetProjectileX(i)+j, terror.GetProjectileY(i)+k);
											if(map.GetType(terror.GetProjectileY(i)+k)!="S" && cekCrash==0){
												map.SetExistObstacle(terror.GetProjectileY(i)+k,terror.GetProjectileX(i)+j);
											}
										}
									}
								}
								
							}
						}
					}

					if(terror.GetWeaponCount()==0){
						map.SetExistWeapon(0);} 
				};


				for(int i=0; i<5; i++){
					if(densus[i].GetExist()==1){
						x = terror.GetX();
						y = terror.GetY();
						if(densus[i].GetX()== x && densus[i].GetY()+ceil(posViewY/32)== y && skillType!="S"){
							HP = 0; terror.SetImage(1);
							soundExplode.play();
						}
					}
				}
				

				map.Update();

				if(map.CekCrashSkill(terror.GetX(),terror.GetY()) && terror.GetSkillCount()==0){
					// cek terror ambil skill
					terror.SetSkill(map.GetSkillTipe());
					map.SetExistSkill(1);
				}

				if(map.CekCrashWeapon(terror.GetX(),terror.GetY()) && terror.GetWeaponCount()==0){
					// cek terror ambil weapon
					terror.SetWeapon(map.GetWeaponTipe());
					map.SetExistWeapon(1);
				}
			}
			

			map.Print(window);//ngeprint map
			map.PrintObstacle(window);// ngeprint halangan sungai
			map.PrintPowerup(window, terror.GetSkillCount(), terror.GetWeaponCount());//print powerup jika skill || weapon frogger tidak ada
			terror.Print(window);//ngeprint frogger
			for(int i=0;i<5;i++){
				densus[i].Print(window);
			}
			map.PrintObstacle2(window);// ngeprint halangan bukan sungai
			terror.PrintProjectile(window);
			
			bar.Print(timeDanger.asSeconds(), posViewY, window);
			
			if(m_pause == 1){
				m_pause = Resume(posViewY);
				if(m_pause == 0){
					clockGame.restart();
				}
			} 
			else if(m_pause == 3 || m_pause == 4){HP=2;}//3 : restart , 4: back to menu

			if(HP == 0 || m_pause == 2){//game over
				m_pause = 2;
				soundRun.stop();
				soundOver.pause();
				soundOver.play();
				terror.Print(window);
				HP=PressAnyKey(posViewY, m_score);//dipencet baru keluar ke main menu
				
			}
			window.setView(view);
			window.display();
		}
		if(m_pause == 3){soundRun.stop();Run();}
		else if(m_pause == 4 ){soundRun.stop();Menu();} 
		else {CekHighScore(m_score);}//kalo udah kalah dicek antara score dengan highscore yang sudah ada
	}

	int PressAnyKey(int y, int n){
		int HP=1;
		sf::Text textScore;
		std::stringstream score;
		score << n;
		textScore.setFont(font);
		textScore.setString(score.str());
		textScore.setCharacterSize(50);
		textScore.setPosition(472-(textScore.getString().getSize()-1)*12,530+y);
		
		spriteOver.setPosition(0, y);
		while(window.pollEvent(event)){
				if(event.type==sf::Event::Closed){
					window.close();
				}
				if(event.key.code==sf::Keyboard::Return ){
					HP=0;
				}
			}
		window.draw(spriteOver);
		window.draw(textScore);

		return HP;
	}

	std::string SkillBar(std::string skillType){
	std::stringstream stringskill;

	return stringskill.str();
	}
	
	std::string WeaponBar(std::string weaponType, int n=0){
	std::stringstream stringweapon;
	
	return stringweapon.str();	
	}
};

