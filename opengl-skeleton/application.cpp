#include "application.hpp"

#include <iostream>
#include <fstream>

john::Application* john::Application::app = NULL;

namespace john 
{

int compile_shaders(const char* vtx_shdr_txt, const char* frg_shdr_txt) {
  GLuint vtx_shader, frg_shader, programID;
  vtx_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vtx_shader, 1,&vtx_shdr_txt, NULL);
  glCompileShader(vtx_shader);

  frg_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frg_shader, 1, &frg_shdr_txt, NULL);
  glCompileShader(frg_shader);

  programID = glCreateProgram();
  glAttachShader(programID, vtx_shader);
  glAttachShader(programID, frg_shader);
  glLinkProgram(programID);

  glDeleteShader(vtx_shader);
  glDeleteShader(frg_shader);

  return programID;
}

john::Application::Application() :
    paused(false)
{
}

void john::Application::startup() 
{
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* load and set the julia shader */
  programID = compile_shaders("", "");

  /* load the 1D palette texture */
  glGenTextures(1, &palette_texture);
  glBindTexture(GL_TEXTURE_1D, palette_texture);
  glTexStorage1D(GL_TEXTURE_1D, 8, GL_RGB8, 256);
  //glTexSubImage1D(GL_TEXTURE_1D, 0, 0, 256, GL_RGB, GL_UNSIGNED_BYTE, john::palettes::orange);
  glGenerateMipmap(GL_TEXTURE_1D);
}

void john::Application::run(john::Application* current_app) 
{
  app = current_app;
  bool running = true;

  // Initialise GLFW
  if( !glfwInit() ) {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(width, height, "Julia", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window.\n" );
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, glfw_on_key);
  glfwSetMouseButtonCallback(window, glfw_on_mouse);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    glfwTerminate();
    return;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  startup();

  do {
    render(glfwGetTime());

    glfwSwapBuffers(window);
    glfwPollEvents();

    running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
    running &= (glfwWindowShouldClose(window) != GL_TRUE);
  } while (running);

  shutdown(); 
  glfwDestroyWindow(window);
  glfwTerminate();
}

void john::Application::render(double currentTime) 
{
  // Clear the screen
  static const GLfloat color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
  glClearBufferfv(GL_COLOR, 0, color);

  double t;
  if (!paused)
    t = currentTime;

  glUseProgram(programID);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void john::Application::on_key(int key, int action) 
{
  if (GLFW_PRESS == action) {
    switch(key) {
      case GLFW_KEY_SPACE: paused = !paused; 
                       break;
      default: break;
    }
  }
}

void john::Application::on_mouse(int button, int action) 
{
  if (GLFW_MOUSE_BUTTON_1 == button) {
    switch(action) {
      case GLFW_PRESS:
        handle_click();
        break;
      default: break;
    }
  }

}

void john::Application::handle_click() 
{
  int x, y;
  float pixels[3];
  get_mouse_position(x, y);

  int screen_stats[4];

  // get width/height of window
  glGetIntegerv(GL_VIEWPORT, screen_stats);

  glReadPixels(x, screen_stats[3] - y, 1, 1, GL_RGB, GL_FLOAT, pixels);
  printf("Value of pixel at (%d, %d): [%f %f %f]", x, y, pixels[0], pixels[1], pixels[2]);
}

void john::Application::shutdown() 
{
}

}
