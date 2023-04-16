from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

w, h = 500, 500

# ---Section 1---
def triangle():
    # 점을 그리는 함수
    glBegin(GL_TRIANGLES)
    glVertex2f(-0.5, -0.5)
    glVertex2f(0, 0.5)
    glVertex2f(0.5, -0.5)
    glEnd()


# triangle() 함수만으론 화면에 그려지지 않음
# 화면을 만들고 showScreen() 함수를 오버라이딩 해서 triangle() 함수를 호출해야 함

# ---Section 2---
def showScreen():  # showScreen으로 불러야 GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT가 적용됨
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)  # 화면 초기화
    glLoadIdentity()
    triangle()
    glutSwapBuffers()


# ---Section 3---
# 실제로 openGL을 실행
glutInit()
glutInitDisplayMode(GLUT_RGBA)
glutInitWindowSize(w, h)
glutInitWindowPosition(0, 0)
wind = glutCreateWindow("PyOpenGL Coding Practice")
glutDisplayFunc(showScreen)
glutIdleFunc(showScreen)  # showScreen 함수를 계속 호출
glutMainLoop()
