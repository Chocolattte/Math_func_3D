#include <iostream>
#include <stdio.h>
#include "glut.h"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
int l = 1, x, y, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, zoom = -3;
double mas[500][500], n = 0.3, max, min, m;
double z = 0;

void read_key(unsigned char key, int, int) 
{
	switch (key)
	{
		// Выход на Esc
	case 27:
		exit(0);
		break;

	case 'd':
		a2++;
		break;

	case 'a':
		a2--;
		break;

		// Зум
	case '+':
		zoom++;
		break;

	case '-':
		--zoom; 
		break;

	//По осям
	case 'y': 
		a5++; 
		break;

	case 'i':
		a5--; 
		break;

	case 'u':
		a3--; 
		break;

	case 'j':
		a3++; 
		break;

	case 'h':
		a4--; 
		break;

	case 'k':
		a4++; 
		break;
	}
}

// Работает PageUP, PageDown, но проблема в а1 или в функции которая с а1 работает
void read_spec_key(int key, int, int)
{
	if (key == GLUT_KEY_PAGE_UP) z += 0.20;
	if (key == GLUT_KEY_PAGE_DOWN) z -= 0.20;

	glutPostRedisplay();
}

void background()
{
  n+=0.0006*l;
  if(n>0.6) l=-1; 
  if(n<0.3) l=1;
  glClearColor(n, n, 1, n);

  glutPostRedisplay();
}

void RenderScene() 
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, 800, 800);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, 1.0f, 0.1f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(a2,a1,50*zoom);
  glLoadIdentity();
  glTranslatef(0,0,50*zoom+a1);
  glLoadIdentity();
  glTranslatef(0, a1, 50 * zoom);
  glTranslatef(a2,0,50*zoom);
  glRotatef(a3,1,0,0);
  glRotatef(a4,0,1,0);
  glRotatef(a5,0,0,1);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glColor3f(0,1,0);

	for (int i=0;i<x-1;i++)
	for (int j=0;j<y-1;j++)
	{
    glBegin(GL_QUADS);
    glVertex3f(i-x/2,j-y/2,(4 + z)*mas[i][j]);
    glVertex3f(i-x/2,j-y/2+1,(4 + z)*mas[i][j+1]);
    glVertex3f(i-x/2+1,j-y/2+1,(4 + z)*mas[i+1][j+1]);
    glVertex3f(i-x/2+1,j-y/2,(4 + z)*mas[i+1][j]);
    glEnd();
	}
	glutSwapBuffers();
}

int main(int argc, char *argv[]) 
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Отрисовка математических функций");
  glEnable(GL_DEPTH_TEST);
  glClearColor(1, 0, 0, 1);
  glutDisplayFunc(RenderScene);
  glutIdleFunc(background);
  glutKeyboardFunc(read_key);
  glutSpecialFunc(read_spec_key);
  
  FILE *f=fopen("tests_ekt33\\test_33_00.txt","r"); /*4 файла:00, 01, 02, 03*/
  if (f==NULL){
    std::cout<<"Error!"<<std::endl;
    return 0;
  }
  fscanf (f,"%d",&x);
  fscanf (f,"%d",&y);
  for (int i=0;i<x;i++)
    for (int j=0;j<y;j++)
      fscanf (f,"%lf",&mas[i][j]);
  max=mas[0][0];
  min=mas[0][0];
  for (int i=0;i<x;i++)
    for (int j=0;j<y;j++){
      if(mas[i][j]>max)
        max=mas[i][j];
      if(mas[i][j]<min)
        min=mas[i][j];
    }
  fclose (f);
  std::cout<<max<<std::endl;
  std::cout<<min<<std::endl;
  glutMainLoop();

  return 0;
}