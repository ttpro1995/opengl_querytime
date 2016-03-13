#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

void display(void)
{
	GLuint64 startTime, stopTime;
	unsigned int queryID[2];

	// generate two queries
	glGenQueries(2, queryID);
		// issue the first query
		// Records the time only after all previous 
		// commands have been completed
		glQueryCounter(queryID[0], GL_TIMESTAMP);

	// call a sequence of OpenGL commands
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f); //Defining color (white)
		glBegin(GL_LINE_LOOP);
		glVertex3f(5.0f, 5.0f, 0.0f);
		glVertex3f(25.0f, 5.0f, 0.0f);
		glVertex3f(25.0f, 25.0f, 0.0f);
		glEnd();
		glFlush(); 

		// issue the second query
		// records the time when the sequence of OpenGL 
		// commands has been fully executed
		glQueryCounter(queryID[1], GL_TIMESTAMP);
		// wait until the results are available
		GLint stopTimerAvailable = 0;
		while (!stopTimerAvailable) {
			glGetQueryObjectiv(queryID[1],
			GL_QUERY_RESULT_AVAILABLE,
			&stopTimerAvailable);
	}

	// get query results
	glGetQueryObjectui64v(queryID[0], GL_QUERY_RESULT, &startTime);
	glGetQueryObjectui64v(queryID[1], GL_QUERY_RESULT, &stopTime);

	printf("Time spent on the GPU: %f ms\n", (stopTime - startTime) / 1000000.0);

}
void init(void)
{
	/* select clearing color */
	glClearColor(0.5, 0.5, 0.5, 0.0);
	/* initialize viewing values */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 30.0, 0.0, 35.0, -1.0, 1.0);
}
int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TRIANGLE");
	init();
	const char* version = (const char*)glGetString(GL_VERSION);
	std::cout << version;

	glutDisplayFunc(display);
	glutMainLoop();
	return 0; /* ANSI C requires main to return an int. */
}