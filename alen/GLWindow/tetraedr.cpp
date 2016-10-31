//
// A simple example of OpenGL usage over X11:
// draw a tetrahedron with a spere on top of it.
//
// The 3D model can be rotated by the mouse movement
// with the left mouse button pressed.
//
// The program is based on the class GLWindow, that presents a
// convenient C++ interface to OpenGL and X11 functions.
//
//                                      Written by V.Borisenko
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GLWindow.h"

static int getIntersection(GLfloat *n, GLfloat *p, GLfloat *v0, GLfloat *v1, GLfloat *in);
static void drawTetra(GLfloat **tv); //Рисует тетраэдр
static void drawTetraPyr(GLfloat **tv); //Рисует четырёхугольную пирамиду
static void drawFrustum(GLfloat **tv); //Рисует усечённый тетраэдр
static const GLfloat epsilon=0.0000000000000000000000001;

//--------------------------------------------------
// Definition of class "MyWindow"
//
class MyWindow: public GLWindow {  // Our main class derived from GLWindow
    GLUquadricObj*  m_Quadric;  // Quadric object used to draw a sphere
    GLfloat         m_Alpha;    // Angle of rotation around vert.axis in degrees
    GLfloat         m_Beta;     // Angle of rotation around hor.axis in degrees
    I2Point         m_MousePos; // Previous position of mouse pointer
    
    float px;
    float py;
    float pz;
	float nx;
	float ny;
	float nz;
public:
    MyWindow():                 // Constructor
        GLWindow(),
        m_Quadric(0),
        m_Alpha(-10.),
        m_Beta(-7.),
        m_MousePos(-1, -1)
    {
		printf("Enter point coordinates: ");
		scanf("%f %f %f", &px, &py, &pz);
		printf("Enter normal vector coordinates: ");
		scanf("%f %f %f", &nx, &ny, &nz);	
	}

    void render();              // Draw a scene graph

    virtual void onExpose(XEvent& event);
    virtual void onKeyPress(XEvent& event);
    virtual void onButtonPress(XEvent& event);
    virtual void onButtonRelease(XEvent& event);
    virtual void onMotionNotify(XEvent& event);
};

//
// Process the Expose event: draw in the window
//
void MyWindow::onExpose(XEvent& /* event */) {
    makeCurrent();

    // Rotate the scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHT0);        // Turn on the first light source

    // Rotate a model
    glRotatef(m_Beta, 1., 0., 0.);
    glRotatef(m_Alpha, 0., 1., 0.);

    render();           // Draw a scene graph

    swapBuffers();
}

//
// Process the KeyPress event: 
// if "q" is pressed, then close the window
//
void MyWindow::onKeyPress(XEvent& event) {
    KeySym key;
    char keyName[256];
    int nameLen = XLookupString(&(event.xkey), keyName, 255, &key, 0);
    printf("KeyPress: keycode=0x%x, state=0x%x, KeySym=0x%x\n",
        event.xkey.keycode, event.xkey.state, (int) key);
    if (nameLen > 0) {
        keyName[nameLen] = 0;
        printf("\"%s\" button pressed.\n", keyName);
        if (keyName[0] == 'q') { // quit => close window
            destroyWindow();
        }
    }
}

// Process mouse click
void MyWindow::onButtonPress(XEvent& /* event */) {
    // int x = event.xbutton.x;
    // int y = event.xbutton.y;
    // int mouseButton = event.xbutton.button;

    // printf("Mouse click: x=%d, y=%d, button=%d\n", x, y, mouseButton);

    m_MousePos.x = (-1); m_MousePos.y = (-1); // Mouse position undefined
}

void MyWindow::onButtonRelease(XEvent& /* event */) {
    m_MousePos.x = (-1); m_MousePos.y = (-1); // Mouse position undefined
}

//
// Process the mouse movement
//
void MyWindow::onMotionNotify(XEvent& event) {
    int x = event.xbutton.x;
    int y = event.xbutton.y;
    if ((event.xbutton.state & Button1Mask) != 0) {
        if (m_MousePos.x >= 0) {
            int dx = x - m_MousePos.x;
            int dy = y - m_MousePos.y;
            if (m_Beta > 100. || m_Beta < (-100.))
                dx = -dx;

            m_Alpha += (GLfloat) dx * 0.1;
            if (fabs(m_Alpha) > 360.)
                m_Alpha -= ((int) m_Alpha / 360) * 360.;

            m_Beta += (GLfloat) dy * 0.1;
            if (fabs(m_Beta) > 360.)
                m_Beta -= ((int) m_Beta / 360) * 360.;

            redraw();
        }
        m_MousePos.x = x; m_MousePos.y = y;
    } else {
        m_MousePos.x = (-1); m_MousePos.y = (-1);   // Undefined
    }
}

//
// Draw a 3D model
//
void MyWindow::render() {
  	GLfloat p[3] = {px, py, pz};
	GLfloat n[3] = {nx, ny, nz};
	
	// Задаём размеры тетраэдра
    GLfloat side = sqrt(2.);
    GLfloat height = sqrt(4.0/3.0);

    // Расчитываем координаты его вершин
    GLfloat tv[4][3] = {{	0., 		0, 	1.		},
						{	0, 	1, 	0	},
						{	1,	0,   	0	},
						{	1,			1,	1		}};
						
	//Массивы под индексы
	int idx[4] = {-1, -1, -1, -1};
	int nonZeroIdx[4] = {-1, -1, -1, -1};	
	int zeroIdx[4] = {-1, -1, -1, -1};
	
	//Массив под скалярные произведения
	GLfloat pos[4] = {0., 0., 0., 0.};
	
    int totalIn = 0; //Всего вершин в неотрицательном полупространстве
    int totalZero = 0; //Всего вершин в плоскости
    int totalNonZero = 0; //Всего вершин в положительном полпространстве

    // Находим скалярные произведения нормали и радиус-векторов вершин тетраэдра
    for(int i = 0; i < 4; ++i)
    {
		for(int j = 0; j < 3; ++j)
		{
			pos[i] += n[j] * (tv[i][j] - p[j]);
		}
		if(pos[i] >= 0) //Если в неотрицательном полупространстве
		{
			idx[totalIn++] = i;
			if(fabsf(pos[i]) < epsilon) //Если в плоскости
			{
				zeroIdx[totalZero++] = i;
			}
			else //Иначе в положительном
			{
				nonZeroIdx[totalNonZero++] = i;
			}
		}
	}
	
	//printf("%d %d\n", totalIn, totalZero);
	
	glClearColor(0.2, 0.3, 0.5, 1.); // Выставляем цвет фона
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Очищаем сцену	  
	
		
		switch(totalIn) //Смотрим, сколько вершин тетраэдра в неотрицательном полупространстве
		{
			case 0:	//Нет вершин в неотрицательной полуплоскости, рисовать нечего
				break;
			case 1:	//1 вершина в неотрицательной, ещё 3 ищем на её рёбрах
			{
			  if(fabsf(pos[idx[0]]) < epsilon) //Если эта вершина ещё и лежит в плоскости, её одну и рисуем
				{
					glBegin(GL_POINTS); //Инициализируем режим рисования точек
						glVertex3f(tv[idx[0]][0], tv[idx[0]][1], tv[idx[0]][2]); //рисуем точку
					glEnd(); //Завершаем
					break;
				}
				//Иначе рисуем тетраэдр с этой вершиной
				GLfloat ip[3][3]; //Точки пересечения
				int k = 0;
				for(int i = 0; i < 4; ++i) //Ищем точки пересечения плоскости с рёбрами
				{
					if(i == idx[0])
					{
						continue;
					}
					if(getIntersection(n, p, &tv[idx[0]][0], &tv[i][0], &ip[k++][0]) != 0) //Если точка пересечения не нашлась, что-то не так
					{
						printf("Something wrong.\n");
						exit(1);
					}
				}
				
				GLfloat *arg[4] = {tv[idx[0]], ip[0], ip[1], ip[2]}; //Собираем аргумент
				drawTetra(arg); //Рисуем
				break;
			}
			
			case 2: //2 в неотрицательной, ещё 4 на их рёбрах (кроме общего)
			{
				switch(totalZero) //Проверяем, сколько вершин в плоскости лежит
				{
					case 2: //Обе вершины в плоскости, рисуем отрезок
					{
						glBegin(GL_LINES); //Рисование отрезка
							glVertex3f(tv[idx[0]][0], tv[idx[0]][1], tv[idx[0]][2]); //Первая точка
							glVertex3f(tv[idx[1]][0], tv[idx[1]][1], tv[idx[1]][2]); //Вторая точка
						glEnd();
						break;
					}
					
					case 1: //Одна вершина в плоскости, рисуем тетраэдр
					{
						GLfloat ip[2][3]; //Точки пересечения
						int k = 0;
						for(int i = 0; i < 4; ++i)
						{
							if(i == idx[0] || i == idx[1])
							{
								continue;
							}
							if(getIntersection(n, p, &tv[nonZeroIdx[0]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
						}
						GLfloat *arg[4] = {tv[nonZeroIdx[0]], ip[0], ip[1], tv[zeroIdx[0]]};
						drawTetra(arg);
						break;
					}
					
					case 0: //Обе вершины вне плоскости, рисуем усечённый тетраэдр
					{
						GLfloat ip[4][3];
						int k = 0;
						for(int i = 0; i < 4; ++i)
						{
							if(i == idx[0] || i == idx[1])
							{
								continue;
							}
							if(getIntersection(n, p, &tv[idx[0]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
							if(getIntersection(n, p, &tv[idx[1]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
						}
						GLfloat *arg[6] = {tv[idx[0]], ip[0], ip[2], tv[idx[1]], ip[1], ip[3]};
						drawFrustum(arg);
						break;
					}
				}
				break;						
			}
			
			case 3:	//3 в неотрицательной, ещё 3 на их рёбрах (кроме общих)
			{
				switch(totalZero)
				{
					case 3: //Все 3 в плоскости, рисуем треугольник
					{
						glBegin(GL_POLYGON);
							glVertex3f(tv[idx[0]][0], tv[idx[0]][1], tv[idx[0]][2]);
							glVertex3f(tv[idx[1]][0], tv[idx[1]][1], tv[idx[1]][2]);
							glVertex3f(tv[idx[2]][0], tv[idx[2]][1], tv[idx[2]][2]);
						glEnd();
						break;	
					}
					
					case 2: //2 в плоскости, рисуем тетраэдр
					{
						GLfloat ip[3]; //Точка пересечения
						int k = 0;
						for(int i = 0; i < 4; ++i)
						{
							if(i == idx[0] || i == idx[1] || i == idx[2])
							{
								continue;
							}
							if(getIntersection(n, p, &tv[nonZeroIdx[0]][0], &tv[i][0], &ip[k++]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
						}			
						GLfloat *arg[4] = {tv[nonZeroIdx[0]], ip, tv[zeroIdx[0]], tv[zeroIdx[1]]};
						drawTetra(arg);
						break;
					}
					
					case 1: //1 в плоскости, 2 снаружи, рисуем четырёхугольную пирамиду
					{
						GLfloat ip[2][3];
						int k = 0;
						for(int i = 0; i < 4; ++i)
						{
							if(i == nonZeroIdx[0] || i == nonZeroIdx[1])
							{
								continue;
							}
							if(getIntersection(n, p, &tv[nonZeroIdx[0]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
							if(getIntersection(n, p, &tv[nonZeroIdx[1]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
						}
						GLfloat *arg[5] = {tv[zeroIdx[0]], ip[0], ip[1], tv[nonZeroIdx[0]], tv[nonZeroIdx[1]]};
						drawTetraPyr(arg);
						break;
					}
					
					case 0: //Все 3 снаружи, рисуем усечённый тетраэдр			
					{
						GLfloat ip[3][3]; //Точки пересечения
						int k = 0;
						for(int i = 0; i < 4; ++i)
						{
							if(i == idx[0] || i == idx[1] || i == idx[2])
							{
								continue;
							}
							if(getIntersection(n, p, &tv[idx[0]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
							if(getIntersection(n, p, &tv[idx[1]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
							if(getIntersection(n, p, &tv[idx[3]][0], &tv[i][0], &ip[k++][0]) != 0)
							{
								printf("Something wrong.\n");
								exit(1);
							}
						}	
						GLfloat *arg[6] = {tv[idx[0]], tv[idx[1]], tv[idx[2]], ip[0], ip[1], ip[2]};
						drawFrustum(arg);
						break;
					}					
				}
				break;	
			}
			
			case 4: //Все в неотрицательной, рисуем тетраэдр целиком
				GLfloat *arg[4] = {tv[0], tv[1], tv[2], tv[3]};
				drawTetra(arg);
				break;
		}
}

/////////////////////////////////////////////////////////////
// Main: initialize X, create an instance of MyWindow class,
//       and start the message loop
int main() {
    // Initialize X stuff
    if (!GWindow::initX()) {
        printf("Could not connect to X-server.\n");
        exit(1);
    }

    int width = GWindow::screenMaxX()/2;
    int height = GWindow::screenMaxY()/2;
    double aspect = (double) width / (double) height;

    MyWindow w;
    w.createWindow(
        I2Rectangle(                    // Window frame rectangle:
            I2Point(10, 10),            //     left-top corner,
            width, height               //     width, height
        ),
        R2Rectangle(                    // Window coordinate rectangle
            R2Point(-2. * aspect, -2.), //     left-top corner,
            4. * aspect, 4.             //     width, height
        ),
        "OpenGL Test"                   // Window title
    );
    w.setBackground("lightGray");
    w.makeCurrent();
    GLWindow::initializeOpenGL();

    GWindow::messageLoop();

    GWindow::closeX();
    return 0;
}

static void drawTetra(GLfloat **tv) //Рисует тетраэдр
{
	GLfloat color[4];
	glBegin(GL_TRIANGLES); //Рисуем грани-треугольники
        color[0] = 0.2; color[1] = 1.; color[2] = 0.2;  // Green
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color); //Устанавливаем цвет заливки
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);

        color[0] = 1.; color[1] = 0.2; color[2] = 0.2;  // Red
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);

        color[0] = 0.9; color[1] = 0.8; color[2] = 0.1; // Yellow
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);

        color[0] = 0.2; color[1] = 0.2; color[2] = 1.;  // Blue
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);
    glEnd();
}

static void drawTetraPyr(GLfloat **tv) //Рисует четырёхугольную пирамиду
{
	GLfloat color[4];
	glBegin(GL_TRIANGLES); //Боковые грани
        color[0] = 1.; color[1] = 0.2; color[2] = 0.2;  // Red
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);

        color[0] = 0.9; color[1] = 0.8; color[2] = 0.1; // Yellow
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);

        color[0] = 0.2; color[1] = 0.2; color[2] = 1.;  // Blue
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);
        glVertex3f(tv[4][0], tv[4][1], tv[4][2]);
        
        color[0] = 0.5; color[1] = 0.1; color[2] = 0.5;  // Deep Purple
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[4][0], tv[4][1], tv[4][2]);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
    glEnd();
    
    glBegin(GL_QUADS); //Дно
        color[0] = 0.2; color[1] = 1.; color[2] = 0.2;  // Green
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);        
        glVertex3f(tv[4][0], tv[4][1], tv[4][2]);
    glEnd();
	
}
static void drawFrustum(GLfloat **tv) //Рисует усечённый тетраэдр
{
	 GLfloat color[4];
	 glBegin(GL_TRIANGLES); //Верхняя грань
        color[0] = 0.5; color[1] = 0.1; color[2] = 0.5;  // Deep Purple
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);
    glEnd();
    
    glBegin(GL_TRIANGLES); //Нижняя грань
        color[0] = 0.2; color[1] = 0.2; color[2] = 1.;  // Blue
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);  
        glVertex3f(tv[5][0], tv[5][1], tv[5][2]); 
        glVertex3f(tv[4][0], tv[4][1], tv[4][2]); 
    glEnd();
    
    glBegin(GL_QUADS); //Боковые грани
        color[0] = 0.2; color[1] = 1.; color[2] = 0.2;  // Green
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
        glVertex3f(tv[4][0], tv[4][1], tv[4][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);     
        
        color[0] = 1.; color[1] = 0.2; color[2] = 0.2;  // Red
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[1][0], tv[1][1], tv[1][2]);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);
        glVertex3f(tv[5][0], tv[5][1], tv[5][2]);              
        glVertex3f(tv[4][0], tv[4][1], tv[4][2]); 
        
        color[0] = 0.9; color[1] = 0.8; color[2] = 0.1; // Yellow
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glVertex3f(tv[2][0], tv[2][1], tv[2][2]);           
        glVertex3f(tv[0][0], tv[0][1], tv[0][2]);
        glVertex3f(tv[3][0], tv[3][1], tv[3][2]);     
        glVertex3f(tv[5][0], tv[5][1], tv[5][2]);       
    glEnd();    
}

static int getIntersection(GLfloat *n, GLfloat *p, GLfloat *v0, GLfloat *v1, GLfloat *in) //Поиск пересечения плоскости, заданной парой вектор-точка (n, p) и прямой, заданной парой точек (v0, v1).
{
	GLfloat t = 0;
	GLfloat d = 0;
	for(int i = 0; i < 3; ++i) //Пользуемся формулой пересечения прямой и плоскости dk = t, где k - параметр в параметрическом уравнении прямой
	{
		t += n[i] * (p[i] - v0[i]);
		d += n[i] * (v1[i] - v0[i]);
	}
	
	if(fabsf(d) < epsilon)
	{
	  if(fabsf(t) < epsilon) //Прямая лежит в плоскости
		{
			return 1;
		}
		else //Прямая параллельна плоскости
		{
			return -1;
		}
	}
	
	t /= d; //t - параметр точки пересечения с плоскостью на прямой, заданной параметрически
	
	for(int i = 0; i < 3; ++i)
	{
		in[i] = (v1[i] - v0[i]) * t + v0[i];
	}
	return 0; //Прямая пересекает плоскость
}
