#include <asm-generic/ioctls.h>
#include <raylib.h>
#include <pty.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include "config.h"

// pseudoterminal master slave struct
typedef struct {
  int master; 
  int slave;
  // TODO:
  // char *name;
  // const struct termios *termp;
  // const struct winsize *winp;
} PTY;

// Connecting a child process to terminal
bool spawn_proc(PTY pty){
  char *env[] = { "TERM=dumb", NULL };
  pid_t p = fork();
  if (p == 0) {
    close(pty.master);

    setsid();
    // BSD aproach of getting controlling tty
    if (ioctl(pty.slave, TIOCSCTTY, NULL) == -1) {
      puts("Could not become controlling TTY. ioctl error.");
      return false;
    }

    // copy slave to stdin, stdout, stderr then start shell
    dup2(pty.slave, stdin);
    dup2(pty.slave, stdout);
    dup2(pty.slave, stderr);
    close(pty.slave);

    execle(SHELL, NULL, env);
  }
  else if (p > 1) {
    close(pty.slave);
    puts("Error while forking the process.");
    return false;
  }

  return true;
}


int main() {
  // Initialization
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
  SetTargetFPS(TARGET_FPS);
  SetTextLineSpacing(FONT_SIZE + 1);
  char cursor_char = '_';

  char text[1025] = "\0";
  int cursor = 0;

  // TODO: connect window with pty
  // TODO: text handling with dramatic cam action like tsoding's ded

  while (!WindowShouldClose()) {
    char key = GetCharPressed();
    while (key > 0) {
      if ((key >= 32) && (key <= 127) && (cursor < 1023)){
        text[cursor] = (char)key;
        text[cursor + 1] = cursor_char;
        text[cursor + 2] = '\0';
        cursor++;
        key = GetCharPressed();
      }
    }
    if (IsKeyPressed(KEY_ENTER) && (cursor < 1024)){
      text[cursor] = '\n';
      text[cursor + 1] = cursor_char;
      text[cursor + 2] = '\0';
      cursor++;
    }
    if (IsKeyPressed(KEY_BACKSPACE)){
      cursor--;
      if (cursor < 0) cursor = 0;
      text[cursor] = cursor_char;
      text[cursor + 1] = '\0';
    }
    BeginDrawing();
      ClearBackground(BLACK);
      DrawText(text, 5, 5, FONT_SIZE, WHITE);
      DrawFPS(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 20);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

// TODO: font stuff
// TODO: unicode support
