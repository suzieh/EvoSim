#ifndef ANIMAL_H
#define ANIMAL_H

#include <tuple>
#include <vector>
#include <memory>

#include "plant.h"

using namespace std;

extern int Screen_Width, Screen_Height;

class Animal
{
 private:
  // 0 = speed, 1 = staminaRate, 2 = sense, 3 = mateRate, 4 = lifeSpan, 5 = foodCap
  float DNA[6];
  bool is_carn;
  float pos_x, pos_y;
  int dir_x, dir_y;
  int width, height;
  float stamina, mateCooldown, mateReduc;
  int life, food;
  std::tuple<float, float, float> fill_color;
  std::tuple<float, float, float> outline_color;

  void findMate(vector<unique_ptr<Animal>> & animal_list);
  bool findPlant(vector<unique_ptr<Plant>> & plant_list);
  void idle(vector<unique_ptr<Animal>> & animal_list);
  void walk();
  void run();
  
 public:
  Animal(int x, int y, bool carn, float speed,
	 float staminaRate, float sense, float mateRate, float lifeSpan, float foodCap);
  Animal(int x, int y, bool carn, float D1[6], float D2[6]);
  float * getDNA();
  float getSpeed();
  float getStaminaRate();
  float getSense();
  float getMateRate();
  int getLifeSpan();
  int getFoodCap();
  int getFood();
  int getLife();
  float getStamina();
  float getMateCooldown();
  float getPosX();
  float getPosY();
  bool getCarn();
  bool hungry();
  
  void resetMateCooldown();

  tuple<float, float, float> setFillColor();
  tuple<float, float, float> setOutlineColor();
  
  void draw();
  void move(vector<unique_ptr<Animal>> & animal_list, vector<unique_ptr<Plant>> & plant_list);
  void foodCheck();
  void update(vector<unique_ptr<Animal>> & animal_list, vector<unique_ptr<Plant>> & plant_list);
};

#endif
