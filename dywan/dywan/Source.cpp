
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>



GLint poziom = 3;
GLfloat szerokosc = 200;
GLfloat st_deformacji = 2;


void rysuj_dywan(GLfloat x, GLfloat y, GLfloat szerokosc, GLint poziom)
{
	// rekurencja do dywanu 
	if (poziom > 0)
	{
		szerokosc = szerokosc / 3;
		rysuj_dywan(x, y, szerokosc, poziom - 1);
		rysuj_dywan(x - szerokosc, y, szerokosc, poziom - 1);
		rysuj_dywan(x - 2 * szerokosc, y, szerokosc, poziom - 1);
		rysuj_dywan(x, y - szerokosc, szerokosc, poziom - 1);
		rysuj_dywan(x - 2 * szerokosc, y - szerokosc, szerokosc, poziom - 1);
		rysuj_dywan(x, y - 2 * szerokosc, szerokosc, poziom - 1);
		rysuj_dywan(x - szerokosc, y - 2 * szerokosc, szerokosc, poziom - 1);
		rysuj_dywan(x - 2 * szerokosc, y - 2 * szerokosc, szerokosc, poziom - 1);
	}

	else
	{
		GLfloat def = (rand() % 20)*st_deformacji / (10 * szerokosc);
		glBegin(GL_POLYGON);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand()% 100)*0.01));
		glVertex2f(x + def, y + def);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand()% 100)*0.01));
		glVertex2f(x + def, y - szerokosc + def);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand()% 100)*0.01));
		glVertex2f(x - szerokosc + def, y - szerokosc + def);
		glColor3f(((rand() % 100)*0.01), ((rand() % 100)*0.01), ((rand()% 100)*0.01));
		glVertex2f(x - szerokosc + def, y + def);
		glEnd();
	}

}

void RenderScene(void)

{

	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	rysuj_dywan(100, 100, szerokosc, poziom);

	glFlush();
	// Przekazanie poleceń rysujących do wykonania

}
/*************************************************************************************/
// Funkcja ustalająca stan renderowania

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor okna wnętrza okna - ustawiono na czarny
}
/*************************************************************************************/
// Funkcja służąca do kontroli zachowania proporcji rysowanych obiektów
// niezależnie od rozmiarów okna graficznego


void ChangeSize(GLsizei horizontal, GLsizei vertical)
// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna

	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)

	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora
	glLoadIdentity();
	// Określenie przestrzeni ograniczającej
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna
	// Gdy okno na ekranie nie jest kwadratem wymagane jest 
	// określenie okna obserwatora. 
	// Pozwala to zachować właściwe proporcje rysowanego obiektu
	// Do określenia okna obserwatora służy funkcja glOrtho(...)

	if (horizontal <= vertical)
		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych    
	glLoadIdentity();
}
/*************************************************************************************/
// Główny punkt wejścia programu. Program działa w trybie konsoli

void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);


	glutCreateWindow("Zadanie domowe, Dywan");


	glutDisplayFunc(RenderScene);


	glutReshapeFunc(ChangeSize);


	MyInit();


	glutMainLoop();

}
/*************************************************************************************/