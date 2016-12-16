#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include <math.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#include "animal.h"

using namespace std;

Animal::Animal(int x, int y, bool carn, float speed,
	       float staminaRate, float sense, float mateRate, float lifeSpan, float foodCap)
{
  width = 30; height = 30;
  stamina = 100;
  pos_x = x; pos_y = y;
  dir_x = (rand()%2+1 == 1)?1:-1;
  dir_y = (rand()%2+1 == 1)?1:-1;
  is_carn = carn;
  DNA[0] = speed;
  DNA[1] = staminaRate;
  DNA[2] = sense;
  DNA[3] = mateRate;
  DNA[4] = lifeSpan;
  life = getLifeSpan();
  DNA[5] = foodCap;
  food = getFoodCap();
  mateCooldown = mateReduc = 0;
  fill_color = setFillColor();
  outline_color = setOutlineColor();

}

Animal::Animal(int x, int y, bool carn, float D1[6], float D2[6])
{
  width = 30; height = 30;
  stamina = 100;
  pos_x = x; pos_y = y;
  dir_x = (rand()%2+1 == 1)?1:-1;
  dir_y = (rand()%2+1 == 1)?1:-1;
  is_carn = carn;
  
  for(int i = 0; i < 6; i++)
    {
      float mutRate = (rand()%2+1 == 1) ? 1.1 : .9;
      DNA[i] = (D1[i] + D2[i])/2 * mutRate;
    }
  
  life = getLifeSpan();
  food = getFoodCap();
  mateCooldown = mateReduc = 0;
  fill_color = setFillColor();
  outline_color = setOutlineColor();
}

float * Animal::getDNA()
{
  return DNA;
}

float Animal::getSpeed()
{
  return DNA[0] + .5;
}

float Animal::getStaminaRate()
{
  return DNA[1] * .8 + .2;
}

float Animal::getSense()
{
  return DNA[2] * 100 + 100;
}

float Animal::getMateRate()
{
  return DNA[3] * .15 + .1;
}

int Animal::getLifeSpan()
{
  return DNA[4] * 500 + 3000;
}

int Animal::getFoodCap()
{
  return DNA[5] * 150 + 700;
}

int Animal::getFood()
{
  return food;
}

int Animal::getLife()
{
  return life;
}

float Animal::getStamina()
{
  return stamina;
}

float Animal::getMateCooldown()
{
  return mateCooldown;
}

float Animal::getPosX()
{
  return pos_x;
}

float Animal::getPosY()
{
  return pos_y;
}

bool Animal::getCarn()
{
  return is_carn;
}

bool Animal::hungry()
{
  return food < getFoodCap() * .7;
}

void Animal::resetMateCooldown()
{
  mateCooldown = 0;
}

tuple<float, float, float> Animal::setFillColor()
{
  int which = 0;
  for(unsigned int i = 1; i < 6; i++)
  {
    if (DNA[i] > DNA[which])
    {
      which = i;
    }
  }
  if(which == 0)
    return make_tuple(1., 0., 0.); // speed = red
  else if(which == 1)
    return make_tuple(1., 1., 0.); // staminaRate = yellow
  else if(which == 2)
    return make_tuple(1., 0., 1.); // sense = purple
  else if(which == 3)
    return make_tuple(0., 0., 1.); // mateRate = blue
  else if(which == 4)
    return make_tuple(1., .5, 0.); // lifeSpan = orange
  else if(which == 5)
    return make_tuple(0., 1., 1.); // foodCap = cyan
  else
    return make_tuple(1., 1., 1.); // white
}

tuple<float, float, float> Animal::setOutlineColor()
{
  int which1 = 0;  //max
  int which2 = 1;  //second-to-max
  for(unsigned int i = 1; i < 6; i++)
  {
    if (DNA[i] > DNA[which1])
    {
      which2 = which1;
      which1 = i;   
    }
  }
  if(which2 == 0)
    return make_tuple(1., 0., 0.); // speed = red
  else if(which2 == 1)
    return make_tuple(1., 1., 0.); // staminaRate = yellow
  else if(which2 == 2)
    return make_tuple(1., 0., 1.); // sense = purple
  else if(which2 == 3)
    return make_tuple(0., 0., 1.); // mateRate = blue
  else if(which2 == 4)
    return make_tuple(1., .5, 0.); // lifeSpan = orange
  else if(which2 == 5)
    return make_tuple(0., 1., 1.); // foodCap = cyan
  else
    return make_tuple(1., 1., 1.); // white
}

void Animal::draw()
{
  if(is_carn) // carn is triangle
    {
      glColor3f(std::get<0>(fill_color), std::get<1>(fill_color), std::get<2>(fill_color));  // triangle
      glBegin(GL_POLYGON);
      glVertex2f(pos_x - width/2, pos_y - height/2);
      glVertex2f(pos_x + width/2, pos_y - height/2);
      glVertex2f(pos_x, pos_y + height/2);
      glEnd();
  
      glColor3f(std::get<0>(outline_color), std::get<1>(outline_color), std::get<2>(outline_color));// outline
      glBegin(GL_LINE_STRIP);
      glVertex2f(pos_x - width/2, pos_y - height/2);
      glVertex2f(pos_x + width/2, pos_y - height/2);
      glVertex2f(pos_x + width/2, pos_y - height/2);
      glVertex2f(pos_x, pos_y + height/2);
      glVertex2f(pos_x, pos_y + height/2);
      glVertex2f(pos_x - width/2, pos_y - height/2);
      glEnd();
    }
  else // herb is circle
    {
      glColor3f(std::get<0>(fill_color), std::get<1>(fill_color), std::get<2>(fill_color));  // circle
      const int NUM_DIVS = 50;
      glBegin(GL_TRIANGLE_FAN);
      glVertex2d(pos_x, pos_y);
      for ( int i = 0; i < NUM_DIVS; ++i )
	glVertex2d(pos_x + width/2*cos(i*2*M_PI/(NUM_DIVS-1)),
		   pos_y + width/2*sin(i*2*M_PI/(NUM_DIVS-1)));
      glEnd();
      
      glColor3f(std::get<0>(outline_color), std::get<1>(outline_color), std::get<2>(outline_color));// outline
      glBegin(GL_LINE_STRIP);
      for ( int i = 0; i < NUM_DIVS; ++i )
        glVertex2d(pos_x + width/2*cos(i*2*M_PI/(NUM_DIVS-1)),
		   pos_y + width/2*sin(i*2*M_PI/(NUM_DIVS-1)));
      glEnd();
    }
}

float distance(float x1, float y1, float x2, float y2)
{
  return sqrt( (pow((x2-x1), 2)) + (pow((y2-y1), 2)) );
}

void Animal::findMate(vector<unique_ptr<Animal>> & animal_list)
{
  int closest_mate = -1;
  float dist_mate = 10000;
  for(unsigned int other = 0; other < animal_list.size(); other++)
    {
      float temp_dist = distance(getPosX(), getPosY(),
				 animal_list[other]->getPosX(), animal_list[other]->getPosY());
      if(dist_mate > temp_dist && animal_list[other]->getCarn() == is_carn && temp_dist != 0)
	{
	  dist_mate = temp_dist;
	  closest_mate = other;
	}
    }
  if(mateCooldown >= 100)
    {
      if(getPosX() < animal_list[closest_mate]->getPosX()) 
	dir_x = 1; 
      else if(getPosX() > animal_list[closest_mate]->getPosX()) 
	dir_x = -1;
      else
	dir_x = 0;
      if(getPosY() < animal_list[closest_mate]->getPosY()) 
	dir_y = 1;
      else if(getPosY() > animal_list[closest_mate]->getPosY())
	dir_y = -1;
      else
	dir_y = 0;
	  
      // check if able to mate, then do so
      if(dist_mate < 20)
	{
	  animal_list.push_back(std::move(make_unique<Animal>(pos_x, pos_y,
							      is_carn, getDNA(),
							      animal_list[closest_mate]->getDNA())));

	  // start mate cooldown			
	  mateCooldown = 0; animal_list[closest_mate]->resetMateCooldown();
	  mateReduc++;
	}
    }
}

bool Animal::findPlant(vector<unique_ptr<Plant>> & plant_list)
{
  int closest_plant = -1;
  float dist_plant = 10000;
  for(unsigned int other = 0; other < plant_list.size(); other++)
    {
      float temp_dist = distance(getPosX(), getPosY(),
				 plant_list[other]->getPosX(), plant_list[other]->getPosY());
      if(dist_plant > temp_dist)
	{
	  dist_plant = temp_dist;
	  closest_plant = other;
	}
      
    }
  if(getSense()*2 > dist_plant)
    {	  
      if(getPosX() < plant_list[closest_plant]->getPosX()) 
	dir_x = 1; 
      else if(getPosX() > plant_list[closest_plant]->getPosX()) 
	dir_x = -1;
      else
	dir_x = 0;
      if(getPosY() < plant_list[closest_plant]->getPosY()) 
	dir_y = 1;
      else if(getPosY() > plant_list[closest_plant]->getPosY())
	dir_y = -1;
	  
      // check if able to eat, then do so
      if(dist_plant < 20)
	{
	  plant_list.erase(plant_list.begin() + closest_plant);
	  food = getFoodCap();
	}
      walk();
      return true;
    }
  return false;
}

void Animal::idle(vector<unique_ptr<Animal>> & animal_list)
{
  // different random direction
  int chance = rand() % (Screen_Width + Screen_Height)/2 + 1;
  if(chance > 6 && chance < 10)
    dir_x = 1;
  else if(chance < 7 && chance > 4)
    dir_x = -1;
  else if(chance < 5 && chance > 2)
    dir_y = 1;
  else if(chance < 3)
    dir_y = -1;

  for(unsigned int other = 0; other < animal_list.size(); other++)
    {
      float temp_dist = distance(getPosX(), getPosY(),
				 animal_list[other]->getPosX(),
				 animal_list[other]->getPosY());
      // personal space
      float space = 20.0;
      if(getPosX() > animal_list[other]->getPosX() && temp_dist <= space) 
	dir_x = 1; 
      else if(getPosX() < animal_list[other]->getPosX() && temp_dist <= space) 
	dir_x = -1;
      if(getPosY() < animal_list[other]->getPosY() && temp_dist <= space) 
	dir_y = 1;
      else if(getPosY() < animal_list[other]->getPosY() && temp_dist <= space)
	dir_y = -1;
    }
  
  // recover stamina
  if(stamina < 100)
    stamina += getStaminaRate();
 
  // try mate
  findMate(animal_list);
  
  // then move
  walk();
}

void Animal::run()
{
  walk();
  if(stamina > 0)
    {
      walk();
      stamina -= getStaminaRate()*2;
    }
}

void Animal::walk()
{
  float buffer = 20.0;
  if(pos_x < buffer)
    dir_x = 1;
  else if(pos_x > (Screen_Width - buffer))
    dir_x = -1;
  if(pos_y < buffer)
    dir_y = 1;
  else if(pos_y > (Screen_Height - buffer))
    dir_y = -1;
    
  // if diagonal
  float speed = getSpeed();
  if(dir_x != 0 || dir_y != 0)
    speed *= .7071;

  // walk
  if(dir_x == 1 && pos_x < Screen_Width)
    pos_x += speed;
  else if(dir_x == -1 && pos_x > 0)
    pos_x -= speed;
  else if(pos_x < Screen_Width - buffer)
    pos_x += speed*2;
  else if(pos_x > buffer)
    pos_x -= speed*2;
  
  if(dir_y == 1 && pos_y < Screen_Height)
    pos_y += speed;
  else if(dir_y == -1 && pos_y > 0)
    pos_y -= speed;
  else if(pos_y < Screen_Height - buffer)
    pos_y += speed*2;
  else if(pos_y > buffer)
    pos_y -= speed*2;
}


 
void Animal::move(vector<unique_ptr<Animal>> & animal_list, vector<unique_ptr<Plant>> & plant_list)
{ 
  int closest_chase = -1;
  float dist_chase = 10000;
  for(unsigned int other = 0; other < animal_list.size(); other++)
    {
      float temp_dist = distance(getPosX(), getPosY(),
				 animal_list[other]->getPosX(), animal_list[other]->getPosY());
      
      
      // carn
      if(dist_chase > temp_dist && animal_list[other]->getCarn() != is_carn && temp_dist != 0)
	{
	  dist_chase = temp_dist;
	  closest_chase = other;
	}
      // check other's life
      if(animal_list[other]->getLife() <= 0)
	{
	  animal_list.erase(animal_list.begin() + other);
	}
    }
  if(getSense() > dist_chase)
    {	  
      if(is_carn && hungry())// carn
	{
	  if(getPosX() < animal_list[closest_chase]->getPosX()) 
	    dir_x = 1; 
	  else if(getPosX() > animal_list[closest_chase]->getPosX()) 
	    dir_x = -1;
	  else
	    dir_x = 0;
	  if(getPosY() < animal_list[closest_chase]->getPosY()) 
	    dir_y = 1;
	  else if(getPosY() > animal_list[closest_chase]->getPosY())
	    dir_y = -1;
	  else
	    dir_y = 0;
	  
	  // check if able to eat, then do so
	  if(dist_chase < 20)
	    {
	      animal_list.erase(animal_list.begin() + closest_chase);
	      food = getFoodCap();
	    }
	  run();
	}
      else if(!is_carn)// herb
	{
	  if(getPosX() > animal_list[closest_chase]->getPosX()) 
	    dir_x = 1; 
	  else if(getPosX() < animal_list[closest_chase]->getPosX()) 
	    dir_x = -1;
	  else
	    dir_x = (rand()%2+1 == 1)?1:-1;
	  if(getPosY() > animal_list[closest_chase]->getPosY()) 
	    dir_y = 1;
	  else if(getPosY() < animal_list[closest_chase]->getPosY())
	    dir_y = -1;
	  else
	    dir_y = (rand()%2+1 == 1)?1:-1;
	  run();
	}
      else
	{
	  if(!is_carn && hungry())
	    findPlant(plant_list);
	  else
	    idle(animal_list);
	}
    }
  else
    {
      if(!is_carn && hungry() && findPlant(plant_list))
	;
      else
	idle(animal_list);
    }
  
  // ready mate
  if(mateCooldown < 100)
    {
      mateCooldown += getMateRate() - is_carn*.02;
    }
}

void Animal::foodCheck()
{
  if(food <= 0)
    life-=3;
  else
    {
      food--;
      life--;
    }
}

 void Animal::update(vector<unique_ptr<Animal>> & animal_list, vector<unique_ptr<Plant>> & plant_list)
{
  move(animal_list, plant_list);
  foodCheck();

  /*cout << endl;
  cout << &animal_list[0] << endl;
  cout << "posX: " << animal_list[0]->getPosX() << endl;
  cout << "posY: " << animal_list[0]->getPosY() << endl;
  cout << "isCarn: " << animal_list[0]->getCarn() << endl;
  cout << "speed: " << animal_list[0]->getSpeed() << endl;
  cout << "stamRate: " << animal_list[0]->getStaminaRate() << endl;
  cout << "stam: " << animal_list[0]->getStamina() << endl;
  cout << "sense: " << animal_list[0]->getSense() << endl;
  cout << "mateRate: " << animal_list[0]->getMateRate() << endl;
  cout << "mateCoolDown: " << animal_list[0]->getMateCooldown() << endl;
  cout << "lifeSpan: " << animal_list[0]->getLifeSpan() << endl;
  cout << "life: " << animal_list[0]->getLife() << endl;
  cout << "foodCap: " << animal_list[0]->getFoodCap() << endl;
  cout << "food: " << animal_list[0]->getFood() << endl;

  cout << endl;
  cout << "speed: " << DNA[0] << endl;
  cout << "stam: " << DNA[1] << endl;
  cout << "sense: " << DNA[2] << endl;
  cout << "mate: " << DNA[3] << endl;
  cout << "life: " << DNA[4] << endl;
  cout << "food: " << DNA[5] << endl;*/
}
