#include <GL/glew.h>
#include <string>

using namespace std;

class  Utils
{
public:
    static string readShaderSource(const char* filePath);

    static bool checkOpenGLError();
    static void printShaderLog(GLuint shader);
    static void printProgramLog(int prog);

    static GLuint createShaderProgram(const char* vp, const char* fp);
    static GLuint createShaderProgram(const char* vp, const char* gp, const char* fp);
    static GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* fp);
    static GLuint createShaderProgram(const char* vp, const char* tCS, const char* tES, const char* gp, const char* fp);
};
