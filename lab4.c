#include <dos.h>
#include <stdio.h>

#define X1 10
#define Y1 15
#define X2 70
#define Y2 20
#define DELAY 150

// Structure to represent a point on the screen with x and y coordinates,
// and direction of movement dx and dy
typedef struct {
    int x;
    int y;
    int dx; // Direction along X-axis (-1, 0, 1)
    int dy; // Direction along Y-axis (-1, 0, 1)
} Point;

// Custom implementation of getch(), which reads a character without echoing it
int my_getch() {
    union REGS in, out;
    in.h.ah = 0x07;
    int86(0x21, &in, &out);
    return out.h.al;
}

// Custom implementation of kbhit(), which checks if a key is pressed
int my_kbhit() {
    union REGS in, out;
    in.h.ah = 0x0B; // DOS function for checking keyboard input
    int86(0x21, &in, &out);
    return out.h.al != 0; // Returns non-zero if a key is pressed
}

void draw_window() {
    int i;
    for (i = X1; i <= X2; i++) {
        gotoxy(i, Y1);
        printf("=");
        gotoxy(i, Y2);
        printf("=");
    }
    for (i = Y1; i <= Y2; i++) {
        gotoxy(X1, i);
        printf("||");
        gotoxy(X2, i);
        printf(" ");
    }
}

void render(Point p) {
    gotoxy(p.x, p.y);
    printf("*");
}

void clear(Point p) {
    gotoxy(p.x, p.y);
    printf(" ");
}

// Handles keyboard input to set movement direction based on arrow keys
void update_direction(Point *p) {
    int ch = my_getch(); // Read initial key press

    if (ch == 27) { // ESC key to exit
        p->dx = 0;
        p->dy = 0;
        return;
    }

    // Arrow keys are scanning as two bytes
    if (ch == 0) {
        ch = my_getch(); // Read the second part of the arrow key code

        // Set direction based on arrow key code
        if (ch == 48) { // Up arrow
            p->dx = 0;
            p->dy = -1;
        } else if (ch == 49) { // Down arrow
            p->dx = 0;
            p->dy = 1;
        } else if (ch == 50) { // Left arrow
            p->dx = -1;
            p->dy = 0;
        } else if (ch == 51) { // Right arrow
            p->dx = 1;
            p->dy = 0;
        }
    }
}

// Updates the symbol’s position based on the current direction
void update_position(Point *p) {
    // Clear the current position before moving
    clear(*p);

    // Move within window boundaries
    if (p->dy == -1 && p->y > Y1 + 1) { // Upward movement
        p->y--;
    } else if (p->dy == 1 && p->y < Y2 - 1) { // Downward movement
        p->y++;
    } else if (p->dx == -1 && p->x > X1 + 1) { // Left movement
        p->x--;
    } else if (p->dx == 1 && p->x < X2 - 1) { // Right movement
        p->x++;
    }

    // Render the symbol at the new position
    render(*p);
}

int main() {
    Point point = {
        (X1 + X2) / 2, // Initial x-coordinate (centered)
        (Y1 + Y2) / 2, // Initial y-coordinate (centered)
        0,             // Initial dx (stationary)
        0              // Initial dy (stationary)
    };

    clrscr(); // Clear screen
    draw_window(); // Draw window borders
    render(point); // Draw initial symbol position

    while (1) {
        if (my_kbhit()) { // Check if a key is pressed
            update_direction(&point);

            if (point.dx == 0 && point.dy == 0) {
                break; // Exit if ESC was pressed
            }
        }

        // Move the symbol according to the current direction
        if (point.dx != 0 || point.dy != 0) {
            update_position(&point);
            delay(DELAY); // Delay for controlling movement speed
        }
    }

    clrscr(); // Clear screen before exiting
    return 0;
}
