#ifdef __APPLE__
#else
#include <windows.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "tetris.h"
Tetris g_tetris;
int g_windowId;

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(5.0, 12.5, 12.5, 5.0, 0.0, -10.0, 0.0, 1.0, 0.0);
  g_tetris.draw();
  glutSwapBuffers();
}

void handleKeyboardEvents(unsigned char key, int x, int y)
{
  if (key == 'w')
  {
    g_tetris.onRotateFieldLeftKeyPressed();
  }
  else if (key == 'x')
  {
    g_tetris.onRotateFieldRightKeyPressed();
  }
  else if (key == 'c')
  {
    g_tetris.onSoftDropKeyPressed();
  }
  else if (key == 'b')
  {
    g_tetris.onXRotateKeyPressed();
  }
  else if (key == 'n')
  {
    g_tetris.onYRotateKeyPressed();
  }
  else if (key == 'v')
  {
    g_tetris.onZRotateKeyPressed();
  }
  glutPostRedisplay();
}

void handleSpecialKeyboardEvents(int key, int x, int y)
{
  if (key == GLUT_KEY_UP)
  {
    g_tetris.onUpKeyPressed();
  }
  else if (key == GLUT_KEY_DOWN)
  {
    g_tetris.onDownKeyPressed();
  }
  else if (key == GLUT_KEY_LEFT)
  {
    g_tetris.onLeftKeyPressed();
  }
  else if (key == GLUT_KEY_RIGHT)
  {
    g_tetris.onRightKeyPressed();
  }
  glutPostRedisplay();
}

void idle(void)
{
  g_tetris.update();
  glutPostRedisplay();
}

void resize(int width, int height)
{
  const float ar = (float)width / (float)height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(10, 10);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  g_windowId = glutCreateWindow("Tetris 3D");
  glutKeyboardFunc(handleKeyboardEvents);
  glutSpecialFunc(handleSpecialKeyboardEvents);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutIdleFunc(idle);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClearDepth(1.0);
  glCullFace(GL_BACK);
  glDepthFunc(GL_LESS);
  glShadeModel(GL_SMOOTH);
  GLfloat ambientLightModel[4] = {0.5, 0.5, 0.5, 1.0};
  GLfloat lightPosition[4] = {0.0, 25.0, 0.0, 1.0};
  GLfloat whiteLight[4] = {1.0, 1.0, 1.0, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLightModel);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glutMainLoop();
  return EXIT_SUCCESS;
}
