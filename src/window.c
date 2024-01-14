#include <raylib.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TITLE "raylib-eduterm"
#define TARGET_FPS 60
#define FONT_SIZE 20

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
  SetTargetFPS(TARGET_FPS);
  SetTextLineSpacing(FONT_SIZE + 1);
  char cursor_char = '_';

  char text[1025] = "\0";
  int cursor = 0;
  Vector2 pos = {5,5};

  while (!WindowShouldClose()) {
    char key = GetCharPressed();
    while (key > 0) {
      if ((key >= 32) && (key <= 125) && (cursor < 1023)){
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


// TODO: psuodoterminal stuff
// TODO: unicode support
// TODO: font stuff
// TODO: dramatic cam action like tsoding's ded
