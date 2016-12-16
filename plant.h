// Plant Class
#ifndef PLANT_H
#define PLANT_H

#include <vector>
#include <memory>

using namespace std;

extern int Screen_Width, Screen_Height;

class Plant
{
private:
  float pos_x, pos_y;
  int width, height;
  int life;
  float mateReduc;

 public:
  Plant(int x, int y);

  int getLife();
  float getPosX();
  float getPosY();

  void draw();
  void update(vector<unique_ptr<Plant>> & plant_list);
};

#endif
