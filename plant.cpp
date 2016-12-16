#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include <time.h>
#include <stdlib.h>

#include "plant.h"

using namespace std;

Plant::Plant(int x, int y)
{
  width = 20; height = 20;
  pos_x = x; pos_y = y;
  life = 2000;
  mateReduc = 0;
}

float Plant::getPosX()
{
  return pos_x;
}

float Plant::getPosY()
{
  return pos_y;
}

int Plant::getLife()
{
  return life;
}

void Plant::draw()
{
	glColor3f(0., 1., 0.);     // green square
	glBegin(GL_POLYGON);
	glVertex2f(pos_x, pos_y);
	glVertex2f(pos_x, pos_y + height);
	glVertex2f(pos_x + width, pos_y + height);
	glVertex2f(pos_x + width, pos_y);
	glEnd();

	glColor3f(1., 1., 1.);     // white outline
	glBegin(GL_LINE_STRIP);
	glVertex2f(pos_x, pos_y);
	glVertex2f(pos_x, pos_y + height);
	glVertex2f(pos_x, pos_y + height);
	glVertex2f(pos_x + width, pos_y + height);
	glVertex2f(pos_x + width, pos_y + height);
	glVertex2f(pos_x + width, pos_y);
	glVertex2f(pos_x + width, pos_y);
	glVertex2f(pos_x, pos_y);
	glEnd();
}

void Plant::update(vector<unique_ptr<Plant>> & plant_list)
{
  //spawn plant
  float range = rand()%120+30;
  if(rand()%4000+1 > 3985 + mateReduc + (plant_list.size() * .1))
    {
      plant_list.push_back(move(make_unique<Plant>(pos_x + ((rand()%2+1 > 1)?range:-range),
						   pos_y + ((rand()%2+1 > 1)?range:-range))));
      mateReduc++;
    }

  //live
  life--;

  for(unsigned int other = 0; other < plant_list.size(); other++)
    {
      float buffer = 80.0;
      // check plant's life
      if(plant_list[other]->getLife() <= 0 || plant_list[other]->getPosX() < buffer || plant_list[other]->getPosX() > Screen_Width - buffer || plant_list[other]->getPosY() < buffer || plant_list[other]->getPosY() > Screen_Height - buffer)
	{
	  plant_list.erase(plant_list.begin() + other);
	}
    }
}
