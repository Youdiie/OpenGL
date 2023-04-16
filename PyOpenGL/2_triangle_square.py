from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *


def myInit():
    glClearColor(1.0, 1.0, 1.0, 1.0)
    glColor3f(0.2, 0.2, 0.2)
    glPointSize(4.0)
    gluOrtho2D(0, 500, 0, 500)


def display():
    glClear(GL_COLOR_BUFFER_BIT)

    # 도형을 그리기 위해선 glVertex2f()를 사용해 점의 위치를 지정
    glBegin(GL_POINTS)  # glBegin() 인자로 도형의 종류를 지정
    glVertex2f(100, 100)
    glVertex2f(300, 200)
    glEnd()  # glEnd()로 도형의 끝을 지정

    glBegin(GL_QUADS)
    glVertex2f(100, 100)
    glVertex2f(300, 100)
    glVertex2f(300, 200)
    glVertex2f(100, 200)
    glEnd()

    glBegin(GL_TRIANGLE_STRIP)
    glVertex2f(100, 210)
    glVertex2f(300, 210)
    glVertex2f(300, 310)
    glEnd()

    glFlush()  # glFlush()로 버퍼에 저장된 도형을 화면에 출력


glutInit()
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
glutInitWindowSize(500, 500)
glutInitWindowPosition(100, 100)
glutCreateWindow(b"PyOpenGL Coding Practice")
myInit()
glutDisplayFunc(display)
glutMainLoop()
