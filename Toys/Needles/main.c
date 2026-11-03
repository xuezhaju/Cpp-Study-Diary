#include <raylib.h>

#define FPS 60
#define D_SC_W 900
#define D_SC_H 600

int main(){
	SetTargetFPS(FPS);
	InitWindow(D_SC_W, D_SC_H, "Needles");
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		EndDrawing();
	}
}
