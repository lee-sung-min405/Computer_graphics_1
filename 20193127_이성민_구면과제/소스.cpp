#include <gl/glut.h>  

//#define		_USE_MATH_DEFINES
#include <math.h>

#define		Window_Width	800
#define     Window_Height	800

#define		PI	3.1415926
#define		N	36			// 경도 360도를 나누고자 하는 조각 수
#define		M	18			// 위도 180도를 나누고자 하는 조각 수


float	ver[N][M + 1][3];	// 구면 상의 점들의 집합
float	sphere_radius;		// 구면의 반경

// 카메라 관련 변수
float	camera_radius, camera_theta, camera_phi;

float	up = 1.0;

//구 생성 관련 변수
int i = 0;
float r = 10.0;
float x[36], y[36], z[36];
int delta_phi = PI / M;
int p[36][18]; //경도36, 위도18
int a, b;

void axis(void) {
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // x축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0); // y축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0); // z축 
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
}


void Sphere(void) {
	for (int j = 0; j < M; j++) {//18 // 위도 세로줄
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i <= N; i++) {//36 //경도 가로줄
			float theta = 2.0 * PI * i / N; //경도 계산
			float phi = PI * j / (M - 1); // 위도 계산

			//구면의 한점
			float x = sphere_radius * sin(phi) * cos(theta);
			float y = sphere_radius * sin(phi) * sin(theta);
			float z = sphere_radius * cos(phi);

			glColor3f(1.0, 1.0, 0.0); // 노랑색
			glVertex3f(x, y, z);

			phi = PI * (j + 1) / (M - 1);

			x = sphere_radius * sin(phi) * cos(theta);
			y = sphere_radius * sin(phi) * sin(theta);
			z = sphere_radius * cos(phi);

			glColor3f(1.0, 1.0, 0.0); // 노랑색
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}




void init(void)
{
	glEnable(GL_DEPTH_TEST);
	sphere_radius = 1.0;
	camera_radius = 5.0;
	camera_theta = 0.3;
	camera_phi = 0.2;
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 1.0, 1000);
}


void camera_setting(void)
{
	float	x, y, z;

	x = camera_radius * cos(camera_theta) * cos(camera_phi);
	y = camera_radius * sin(camera_theta) * cos(camera_phi);
	z = camera_radius * sin(camera_phi);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, up);

}


void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera_setting();
	axis();

	// Your Sphere Code 
	Sphere();


	glFlush();

}

void Adjust_camera_up_vector(void) {

	if (camera_phi > 3.0 * PI / 2.0)
		camera_phi -= 2.0 * PI;
	else if (camera_phi < -3.0 * PI / 2.0)
		camera_phi += 2.0 * PI;

	if (camera_phi > PI / 2.0)
		up = -1.0;
	else if (camera_phi < -1.0 * PI / 2.0)
		up = -1.0;
	else
		up = 1.0;
}

void special_key(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:		camera_theta -= 0.01; 	break;
	case GLUT_KEY_RIGHT:	camera_theta += 0.01;	break;
	case GLUT_KEY_UP:		camera_phi += 0.01;		break;
	case GLUT_KEY_DOWN:		camera_phi -= 0.01;		break;
	default: break;
	}
	Adjust_camera_up_vector();

	glutPostRedisplay();
}

void mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':	camera_radius += 0.1; break;
	case 's':	camera_radius -= 0.1; break;
	default: break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Window_Width, Window_Height);
	glutCreateWindow("Your 3D Sphere");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykey);
	glutSpecialFunc(special_key);
	glutMainLoop();
	return 0;
}