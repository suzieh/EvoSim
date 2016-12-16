#include <iostream>
#include <vector>
#include <memory>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <time.h>
#include <cmath>

#include "animal.h"
#include "plant.h"

using namespace std;

int Screen_Width = 1000;  // width of the user window
int Screen_Height = 750;  // height of the user window
char programName[] = "EvoSim";
vector<unique_ptr<Animal>> animal_list;
vector<unique_ptr<Plant>> plant_list;

// the display function actually does the work of drawing in the window.
// this function will be called every time the appearance of the window
// needs to be remade.
void display()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Loop through list of plants to draw
  for(unsigned int i = 0; i < plant_list.size(); i++)
    {
      plant_list[i]->draw();
    }
  // Loop through list of animals to draw
  for(unsigned int i = 0; i < animal_list.size(); i++)
    {
      animal_list[i]->draw();
    }

  // tell the graphics card that we're done-- go ahead and draw!
  glutSwapBuffers();
}

// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
  int win = glutGetWindow();
  switch(c) {
    case 'q':
    case 'Q':
    case 27:
      // get rid of the window (as part of shutting down)
      glutDestroyWindow(win);
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void simulation_update()
{
  for(unsigned int self = 0; self < animal_list.size(); self++)
    {
      animal_list[self]->update(animal_list, plant_list);
    }
  for(unsigned int self = 0; self < plant_list.size(); self++)
    {
      plant_list[self]->update(plant_list);
    }
  
  glutPostRedisplay();
}

// the atTime function is called approximately every 60th of a second.
void atTime(int tmp)
{
  // update simulation
  simulation_update();
  
  glutTimerFunc(1000/60., atTime, 0);  // every 1/30 of a second
}

// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   Screen_Width = w;  Screen_Height = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., Screen_Width-1, 0., Screen_Height-1, -1.0, 1.0);
}

// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., Screen_Width-1, 0., Screen_Height-1, -1.0, 1.0);

  // set up how points and lines will be drawn.  The following
  //  commands make points and lines look nice and smooth.
  glPointSize(3);
  glLineWidth(1.5);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

// init_gl_window is the function that starts the ball rolling, in
//  terms of getting everything set up and passing control over to the
//  glut library for event handling.  It needs to tell the glut library
//  about all the essential functions:  what function to call if the
//  window changes shape, what to do to redraw, handle the keyboard,
//  etc.
void init_gl_window()
{
  char *argv[] = {programName};
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(Screen_Width,Screen_Height);
  glutInitWindowPosition(100,100);
  glutCreateWindow(programName);
  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(1000/60., atTime, 0);
  glutMainLoop();
}

void initial_population()
{ 
  for(int i = 0; i < 50; i++)
    {
      animal_list.push_back(move(make_unique<Animal>(rand()%Screen_Width+25, // x
						     rand()%Screen_Height+25, // y 
						     (rand()%10+1 > 2)?0:1, // is_carn
						     ((float)rand()/(float)(RAND_MAX)), //speed
						     ((float)rand()/(float)(RAND_MAX)), // stamina
						     ((float)rand()/(float)(RAND_MAX)), // sense
						     ((float)rand()/(float)(RAND_MAX)), //mate
						     ((float)rand()/(float)(RAND_MAX)), //lifeSpan
						     ((float)rand()/(float)(RAND_MAX))))); // food
    }
  for(int i = 0; i < 30; i++)
    {
      plant_list.push_back(move(make_unique<Plant>(rand()%Screen_Width+60,
						    rand()%Screen_Height+60)));
    }
}

int main()
{
  srand(time(NULL));
  initial_population();
  
  init_gl_window();
}
