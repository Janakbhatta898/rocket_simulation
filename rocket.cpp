#include <graphics.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;


class GraphicsEngine {
public:

    // DDA Line Algorithm
    static void drawLineDDA(int x1, int y1, int x2, int y2, int color) {
        float dx = x2 - x1;
        float dy = y2 - y1;

        float steps = max(abs(dx), abs(dy));

        float Xinc = dx / steps;
        float Yinc = dy / steps;

        float x = x1;
        float y = y1;

        for (int i = 0; i <= steps; i++) {
            putpixel(round(x), round(y), color);
            x += Xinc;
            y += Yinc;
        }
    }

    // Midpoint Circle Algorithm
    static void drawCircle(int xc, int yc, int r, int color) {
        int x = 0;
        int y = r;
        int d = 1 - r;

        while (x <= y) {
            plotCirclePoints(xc, yc, x, y, color);

            if (d < 0)
                d += 2 * x + 3;
            else {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
        }
    }

private:
    static void plotCirclePoints(int xc, int yc, int x, int y, int color) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color);
        putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color);
        putpixel(xc - y, yc - x, color);
    }
};


class Rocket {
private:
    float x, y;
    float velocity;
    float fuel;
    bool separated;

public:
    Rocket() {
        x = 400;
        y = 500;
        velocity = 0;
        fuel = 300;
        separated = false;
    }

    void update() {
        float gravity = 0.05;
        float thrust = 0.15;

        if (fuel > 0) {
            velocity -= thrust;
            fuel -= 0.5;
        }

        velocity += gravity;
        y += velocity;

     
    }

    void draw() {
        drawBody();
        drawNose();
        drawFins();

        if (fuel > 0)
            drawFlames();

        if (separated)
            drawStageSeparation();
    }

private:

    void drawBody() {
        GraphicsEngine::drawLineDDA(x-10, y-40, x+10, y-40, WHITE);
        GraphicsEngine::drawLineDDA(x-10, y+40, x+10, y+40, WHITE);
        GraphicsEngine::drawLineDDA(x-10, y-40, x-10, y+40, WHITE);
        GraphicsEngine::drawLineDDA(x+10, y-40, x+10, y+40, WHITE);     

       
    }

    void drawNose() {
        GraphicsEngine::drawLineDDA(x-10, y-40, x, y-70, WHITE);
        GraphicsEngine::drawLineDDA(x+10, y-40, x, y-70, WHITE);
    }

    void drawFins() {
        GraphicsEngine::drawLineDDA(x-10, y+40, x-25, y+60, WHITE);
        GraphicsEngine::drawLineDDA(x+10, y+40, x+25, y+60, WHITE);
    }

    void drawFlames() {
        GraphicsEngine::drawCircle(x, y+50, 5, RED);
        GraphicsEngine::drawCircle(x-3, y+55, 4, YELLOW);
        GraphicsEngine::drawCircle(x+3, y+55, 4, YELLOW);
    }

    void drawStageSeparation() {
        GraphicsEngine::drawLineDDA(x-15, y+50, x+15, y+50, YELLOW);
        GraphicsEngine::drawLineDDA(x-15, y+50, x-15, y+80, YELLOW);
        GraphicsEngine::drawLineDDA(x+15, y+50, x+15, y+80, YELLOW);
        GraphicsEngine::drawLineDDA(x-15, y+80, x+15, y+80, YELLOW);
    }
};


void countdown() {
    for (int i = 5; i >= 0; i--) {
        cleardevice();
        settextstyle(10, 0, 5);
        string text = to_string(i);
        outtextxy(380, 300, (char*)text.c_str());
        delay(1000);
    }
}


int main() {

    initwindow(800, 600, "Rocket Launch Simulation");
    putpixel(399, 299, RED);
 
    
    int centerx=getmaxx()/2;
    int centery=getmaxy()/2;
    cout<<"center"<<centerx<<centery<<endl;
 
    Rocket rocket;

    countdown();
    cleardevice();
    GraphicsEngine::drawCircle(399, 299, 25, RED);

    while (true) {
        cleardevice();
        rocket.update();
        rocket.draw();
        delay(200);
    }

    closegraph();
    return 0;
}
