
#include "TextRenderer.h"

	void print(int x, int y, string text, double size) {
		glPushMatrix();
		glLoadIdentity();
		glScalef(SCREEN_SHRINK_RATIO / SCREEN_WIDTH,
			-SCREEN_SHRINK_RATIO / SCREEN_HEIGHT,
			1);

		glTranslatef(x - SCREEN_WIDTH / 2, y - SCREEN_HEIGHT / 2, 0.0);
		glScalef(0.2 * size, -0.2 * size, 0.0);
		glLineWidth(size * 1.5);
		glColor3f(0, 0, 0);
		for (auto ch : text) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);
		}
		glPopMatrix();
	}
	void printCenter(int x, int y, string text, double size) {
		double width = textWidth(text, size);
		print(x - width / 2, y, text, size);
	}

	double textWidth(string text, double size) {
		glPushMatrix();
		glLoadIdentity();
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		GLfloat matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		double before = matrix[12];
		glScalef(0.2 * size, -0.2 * size, 0.0);
		for (auto ch : text) {
			glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);
		}
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		double width = (matrix[12] - before) / matrix[0] * 0.2 * size;
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glPopMatrix();
		return width;
	}