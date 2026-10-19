#include "raylib.h"

int main(){

    InitWindow(800, 450, "ball");

    InitAudioDevice();

    Sound hit=LoadSound("hit.wav");
    Sound gameOver=LoadSound("over.mp3");
    Sound win=LoadSound("win.mp3");


    float pos1X=0;
    float pos1Y=200;

    float velRecY=0;

    float cirX=400;
    float cirY=225;

    float velX=-350;
    float velY=0;


    float cpuPosX=780;
    float cpuPosY=200;
    float cpuVelY=0;


    int userScore=0;
    int cpuScore=0;


    int flag=0;
    Rectangle myBox={300, 175, 200, 100};


    while(!WindowShouldClose()){

        if(flag==1){

            float dt=GetFrameTime();


            // user board

            if(IsKeyDown(KEY_DOWN)){
                velRecY=250.0f;
            }
            else if(IsKeyDown(KEY_UP)){
                velRecY=-250.0f;
            }

            else {
                if(velRecY>0.0f){
                    velRecY-=200*dt;
                    if(velRecY<=0.0f){
                        velRecY=0.0f;
                    }
                }
                else if(velRecY<0.0f){
                    velRecY+=200*dt;
                    if(velRecY>=0.0f){
                        velRecY=0.0f;
                    }
                }
            }

            pos1Y += dt*velRecY;

            //cpu board

            if(cirX>570 && velX>0){
                if(cirY>cpuPosY+50){
                    cpuVelY=250.0f;
                }
                else if(cirY<cpuPosY+50){
                    cpuVelY=-250.0f;
                }
                else{
                    cpuVelY=0.0f;
                }
            }
            else{
                cpuVelY=0.0f;
            }

            cpuPosY+=cpuVelY*dt;

            // boundary of user board

            if(pos1Y<=0){
                pos1Y=0;
            }
            else if(pos1Y+100>=450){
                pos1Y=450-100;
            }

            // boundary of CPU board

            if(cpuPosY<=0){
                cpuPosY=0;
            }
            else if(cpuPosY+100>=450){
                cpuPosY=450-100;
            }

            // circle bounce wrt user board

            if(velX<0 && (cirX+10>=pos1X)&& (cirX-10<=pos1X+20) && (cirY-10>=pos1Y && cirY+10<=pos1Y+100)){
                velX=-velX;
                velY=velRecY;

                PlaySound(hit);
            }

            // circle bounce wrt cpu board

            if(velX>0 && (cirX-10 <= cpuPosX+20) && (cirX+10>=cpuPosX) && (cirY-10 >= cpuPosY && cirY<=cpuPosY+100)){
                velX=-velX;
                velY=cpuVelY;

                PlaySound(hit);
            }

            //boundaries of window for ball

            if(cirY-10<0 || cirY+10>450){
                velY=-velY;
            }

            if(cirX+10<0){
                cirX=400;
                cirY=225;

                cpuScore++;
            }
            if(cirX-10>800){
                cirX=400;
                cirY=225;

                userScore++;
            }

            // moving circle wrt circle velocity

            cirX += velX*dt;
            cirY += velY*dt;
        }

        else{
            Vector2 mousePos=GetMousePosition();
            bool isHovering= CheckCollisionPointRec(mousePos, myBox);

            if(isHovering){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    flag=1;
                }
            }
        }

        BeginDrawing();

            if(flag==1){
                ClearBackground(WHITE);

                DrawRectangle(pos1X, pos1Y, 20, 100, BLACK);

                DrawRectangle(cpuPosX, cpuPosY, 20, 100, BLACK);

                DrawCircle(cirX, cirY, 10, RED);

                DrawText(TextFormat("%d", userScore), 150, 20, 50, GRAY);
                DrawText(TextFormat("%d", cpuScore), 800-150, 20, 50, GRAY);

                if(userScore==10 || cpuScore==10){
                    flag=2;

                    if(cpuScore==10){
                        PlaySound(gameOver);
                    }
                    else{
                        PlaySound(win);
                    }
                }
            }
            else if(flag==0){
                ClearBackground(YELLOW);

                DrawRectangleRec(myBox, MAROON);
                DrawText("PLAY", 325, 200, 50, BLACK);

            }

            else if(flag==2){
                ClearBackground(WHITE);
                DrawText(TextFormat("%d", userScore), 150, 20, 50, GRAY);
                DrawText(TextFormat("%d", cpuScore), 800-150, 20, 50, GRAY);


                if(userScore==10){
                    
                    DrawText("USER WON!!", 325, 200, 50, BLACK);
                }
                else{
                    DrawText("CPU WON!!", 325, 200, 50, BLACK);
                }
            }

        EndDrawing();
    }

    UnloadSound(hit);
    UnloadSound(gameOver);
    UnloadSound(win);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}