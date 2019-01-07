#include "my_opengl.h"
#include "main.h"
#include "data_load.h"
#include <math.h>
#include <GL/glh_glut.h>
#include "b_spline.h"
using namespace glh;


void Init()
{
   // load data from file
	samples.load_data("../data/saddle.txt");

	// ����͸��Ч����ͼ      
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0f, 1.0f, 1.0f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 1, 0, 0, 0, 0, 0, 0, 1);
}

void OpenglInit(int argc, char** argv)
{
	Init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowSize(800, 600);			//set window size
	glutInitWindowPosition(100, 150);		//set window position
	glutCreateWindow("Display");			//window name
	glutDisplayFunc(DisplayFunc);			//��Ļ��ʾ�Ļص�����
	glutIdleFunc(IdleFunc);					//����ʱ�ص���������û����Ϣʱ���ã�
	glutKeyboardFunc(KeyboardFunc);			//���֡���ĸ���İ������Ļص�����
	glutSpecialFunc(SpecialFunc);			//���ⰴ����⣨F1~F12�����Ƽ���
	glutMouseFunc(MouseFunc);//�����
	glutMotionFunc(MotionFunc);//��갴���϶����
	glutPassiveMotionFunc(PassiveMotionFunc);//����ƶ����
	glutMainLoop();
}

void define_material()
{
	GLfloat amb_Diff[4] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat specular[4] = { 1, 1, 1, 1.0 };
	GLfloat shin[] = { 10 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);	//��ɫ
	glMaterialfv(GL_FRONT, GL_SHININESS, shin);	//����ָ��
}

void add_light()
{
	GLfloat  whiteLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat  sourceLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat     lightPos[] = { -1.f, 1.0f, 1.0f, 1.0f };
	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	//���ù���ģʽ��ȱʡ�Ļ�������
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);

	//���û�����
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);

	//����ɢ���
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);

	//���ù���λ��
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//���ô˹���
	glEnable(GL_LIGHT0);

	//������ɫ׷��
	glEnable(GL_COLOR_MATERIAL);

	//�����������ϻ�����ɢ����ɫ ׷��glcolor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
void DisplayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//clear color buffer
	glDisable(GL_DEPTH_TEST | GL_LIGHTING);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

	//set background
	glClearColor(0, 0, 0, 0);
	vector<float> x, y;
	for (float i = -2; i <= 8; i = i + 0.1)
	{
		x.push_back(i);
		y.push_back(sin(i));
	}

	//vector<float> out_x, out_y;
	//B_spline bs;
	//bs.fitting_curve(x,y,out_y);

	/*for (float i = 0; i <x.size(); i++)
	{
		float temp_y = bs.BaseFunction(4, 3, x[i]);
		y.push_back(temp_y);
	}*/

	/*x.erase(x.begin(),x.begin()+4);
	out_y.erase(out_y.begin(),out_y.begin()+4);*/
	//plot(x, out_y);


	add_light();

	/*B_spline bs;
	vector<vector<Vec3f>> out;
	bs.fitting_surface(samples.samples_,out);
	Mesh(out);*/

	
	Mesh(samples.samples_);
	glutSwapBuffers();
}

void Mesh(vector<vector<Vec3f>>& dat)
{
	float xmin, ymin, zmin, xmax, ymax, zmax;
	xmin = ymin = zmin = INT_MAX;
	xmax = ymax = zmax = -INT_MAX;
	for (auto& line : dat)
	{
		for (auto& val : line)
		{
			xmin = min(xmin, val.x);
			ymin = min(ymin, val.y);
			zmin = min(zmin, val.z);

			xmax = max(xmax, val.x);
			ymax = max(ymax, val.y);
			zmax = max(zmax, val.z);
		}
	}


	for (int i = 0; i < dat.size() - 1; i++)
	{
		for (int j = 0; j < dat[0].size() - 1; j++)
		{
			float colorx = 0.6*(sin(10 * dat[i][j].x) + 1);
			float colory = 0.6*(sin(10 * dat[i][j].y) + 1);
			float colorz = 0.6*(sin(10 * dat[i][j].x + 1) + 1);

			glColor3f(colorx, colory, colorz);
			glBegin(GL_LINE_LOOP);
			glVertex3f(TOSCREEN(dat[i][j].x,xmin,xmax), TOSCREEN(dat[i][j].y,ymin,ymax), TOSCREEN(dat[i][j].z,zmin,zmax));
			glVertex3f(TOSCREEN(dat[i][j + 1].x,xmin,xmax), TOSCREEN(dat[i][j + 1].y,ymin,ymax), TOSCREEN(dat[i][j + 1].z,zmin,zmax));
			glVertex3f(TOSCREEN(dat[i + 1][j + 1].x,xmin,xmax), TOSCREEN(dat[i + 1][j + 1].y,ymin,ymax), TOSCREEN(dat[i + 1][j + 1].z,zmin,zmax));
			glVertex3f(TOSCREEN(dat[i + 1][j].x,xmin,xmax), TOSCREEN(dat[i + 1][j].y,ymin,ymax), TOSCREEN(dat[i + 1][j].z,zmin,zmax));
			glVertex3f(TOSCREEN(dat[i][j].x,xmin,xmax), TOSCREEN(dat[i][j].y,ymin,ymax), TOSCREEN(dat[i][j].z,zmin,zmax));
			glEnd();
		}
	}
}

void plot(vector<float>& x, vector<float>& y)
{
	glColor3f(1, 0, 0);
	if (x.size() == y.size())
	{
		vector<float>::iterator it = max_element(y.begin(), y.end());
		float y_max = *it;
		it = min_element(y.begin(), y.end());
		float y_min = *it;

		glBegin(GL_LINES);
		for (int i = 0; i < x.size()-1; i++)
		{			
			glVertex3f(TOSCREEN(x[i],x[0],x[x.size()-1]),TOSCREEN(y[i],y_min,y_max),0);
			glVertex3f(TOSCREEN(x[i+1], x[0], x[x.size() - 1]), TOSCREEN(y[i+1], y_min, y_max), 0);			
		}
		glEnd();
	}
	else
	{
		cout << "Error: The Dimension of x and y not matched!" << endl;
	}
}

//����ʱ���õĺ���
void IdleFunc()
{
	glutPostRedisplay();//���»��ƣ�������DisplayFunc()������
}

//���֡���ĸ���������
void KeyboardFunc(unsigned char Key, int x, int y)
{
	if (Key == 'w' || Key == 'W')
	{
		glRotated(1,10,0,0);			
	}

	if (Key == 's' || Key == 'S')
	{
		glRotated(1, -10, 0, 0);
	}

	if (Key == 'a' || Key == 'A')
	{
		glRotated(1,0, 10, 0);
	}

	if (Key == 'd' || Key == 'D')
	{
		glRotated(1, 0, -10, 0);
	}
	if (Key == 'q' || Key == 'Q')
	{
		glRotated(1, 0, 0, 10);
	}
	if (Key == 'e' || Key == 'E')
	{
		glRotated(1, 0, 0, -10);
	}
}

//F1~F12�����Ƽ����
void SpecialFunc(int Key, int x, int y)
{
	if (Key == GLUT_KEY_UP)
	{
		
	}

	if (Key == GLUT_KEY_DOWN)
	{
		
	}

	if (Key == GLUT_KEY_LEFT)
	{
		
	}

	if (Key == GLUT_KEY_RIGHT)
	{
		
	}
}

//�����
void MouseFunc(int button, int state, int x, int y)
{
	//button  ��갴�� 0 -- ���    1 -- �м�   2 -- �Ҽ�
	//state  ���״̬  0 -- ����  1 -- ̧��
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	if (button == 0)
	{
		if (state == 0)
		{
	
		}
		if (state == 1)
		{
			
		}
	}
	if (button == 1)
	{
		if (state == 0)
		{
			
		}
		if (state == 1)
		{
			
		}
	}
	if (button == 2)
	{
		if (state == 0)
		{
			
		}
		if (state == 1)
		{
			
		}
	}
}

//��갴���϶�
void MotionFunc(int x, int y)
{
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	
}

//����ƶ�
void PassiveMotionFunc(int x, int y)
{
	//x,y  �������ص����꣨�Դ��ڵ����Ͻ�Ϊԭ�������ϵ��
	
}