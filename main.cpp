
//////////////////////////////////////////////////////////////////////////////
/////////////// Demo: Loading PNG images in openGL using /////////////////////
///////////////////////////// Lodepng ////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "lodepng.h"

using namespace std;

int WIDTH=640;
int HEIGHT=480;
vector <unsigned char> image;
unsigned imageWidth=250;
unsigned imageHeight=100;
const char* imageName="example.png";

void invert(vector<unsigned char> &img,const unsigned width,const unsigned height)
{
    unsigned char *imageptr = &img[0];
    unsigned char *first = NULL;
    unsigned char *last = NULL;
    unsigned char temp = 0;
    for( int h = 0; h <(int) height/2; ++h )
    {

        first = imageptr + h * width * 4;
        last = imageptr + (height - h - 1) * width*4;
        for( int i = 0; i < (int)width*4; ++i )
        {
            temp = *first;
            *first = *last;
            *last = temp;
            ++first;
            ++last;
        }
    }
}
void loadImage()
{
    int error;
    if((error=lodepng::decode(image,imageWidth,imageHeight,imageName)))
    {
        cout<<imageName<<":"<<lodepng_error_text(error)<<endl;
        exit(1);
    }
    else
        invert(image,imageWidth,imageHeight);

}
static void resize(int width, int height)
{
    WIDTH=width;
    HEIGHT=height;
    glClearColor(0,0,0,0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glRasterPos2i(WIDTH/2-(imageWidth/2),HEIGHT/2-(imageHeight/2));
    glDrawPixels(imageWidth,imageHeight, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    glPopMatrix();
    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}
int main(int argc, char *argv[])
{
    loadImage();
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutCreateWindow("glImage");
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return EXIT_SUCCESS;
}
