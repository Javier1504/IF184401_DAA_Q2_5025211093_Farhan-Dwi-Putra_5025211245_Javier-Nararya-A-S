#include <iostream>
#include <windows.h> //use gotoxy, GetAsyncKeyState

#define batas_atas 2 // upside game border
#define batas_bawah 23 // bottom side game border
#define batas_samping 2 // left side game border
#define batas_samping_k 78 // right side game border

using namespace std;
// declare variable
int iX(5), iY(5), x1 (4), y1 (4), xHapus(3), yHapus(3), veloX(1), veloY(0) ,ekorsX[200], ekorsY[200], nEkor = 5, start = 0, makX, makY;

void gotoxy(int x, int y) // Void for gotoxy, move cursor on console
{
 COORD pos = {x, y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void naik() //function that allow snake move up
{
  veloY = -1; // Y speed go up
  veloX = 0; // X speed is zero
}

void turun()
{
  veloY = 1; 
  veloX = 0; 
}

void samping()
{
  veloX = -1; 
  veloY = 0; 
}

void samping_k()
{
  veloX = 1; 
  veloY = 0; 
}

void hapus()
{
 gotoxy(xHapus, yHapus); // for deleting passed part 
 cout << " ";
}

void ekor()
{
 for(int j = 0; j <= 2; j++)
 {
  gotoxy(ekorsX[j], ekorsY[j]);
  cout << "+";
 }
}

void tampil()
{
 gotoxy(iX, iY); //iX and iY are head picture position 
 cout << char(2); //for draw head picture
 //because ascii from smiley is 2
 gotoxy(makX, makY);
 // makX and makY value is random
 // use for food position(random)
 cout << "*"; //food picture
}

void ganti_posisi() //change position
{
 xHapus = ekorsX[nEkor - 1];
 yHapus = ekorsY[nEkor - 1];
 for(int j = nEkor - 1; j >= 1; j--)
 {
  ekorsX[j] = ekorsX[j-1];
  ekorsY[j] = ekorsY[j-1];
 }
  ekorsX[0] = iX;
  ekorsY[0] = iY;
}

void velo() //for update position of snake according button we press
{
 ganti_posisi();
 hapus();
 iX += veloX;
 iY += veloY;
 tampil();
 ekor();
}

/*void trace()
{
 for(int j = 0; j <= nEkor -1; j++)
 {
  cout << "x" << j << " y"<< j<< " = " << ekorsX[j] << "," << ekorsY[j];
  cout << " // " << iX << "," << iY << endl;
 }
 system("pause");
 system("cls");
}*/

bool isDestroy()
{
 //check snake condition (deleting head if colliding frame too)
 if(iX == batas_samping_k) { iX = 3; gotoxy(78, iY); cout << " "; }
 if(iX == batas_samping)  { iX = 77; gotoxy(2, iY); cout << " "; }
 if(iY == batas_atas) { iY = 22; gotoxy(iX, 2); cout << " "; }
 if(iY == batas_bawah) { iY = 3; gotoxy(iX, 23); cout << " "; }
 //trace();
 for(int j = 0; j <= nEkor - 1; j++)
  if(ekorsX[j] == iX && ekorsY[j] == iY) return true;
 return false;
}


char getkey()// for getting pressed button
{
 for(int i = 8; i <= 222; i++)
 {
  if(GetAsyncKeyState(i) == -32767)
  {
   switch(i)
   {
    case 38 : if(veloY != 1)naik();
              break;//if pressed button is up
    case 40 : if(veloY != -1)turun();
              break; //if pressed button is down
    case 37 : if(veloX != 1)samping();
              break; //if pressed button is left
    case 39 : if(veloX != -1)samping_k();
              break; //if pressed button is right
   }
  }
 }
}

void random_makanan()
{
 makX = rand()%(batas_samping_k - 1);
 if(makX < 4) makX += 3 + (4-makX); //for limiting feed
 makY = rand()%(batas_bawah - 1);
 if(makY < 4) makY += 3 + (4-makY);
 gotoxy(makX, makY);
 cout << "*";
}

bool isEaten()
{
 if(iX == makX && iY == makY) return true; else return false;
}

void cBorder() //make border game
{
 for(int i = 1; i <= 78; i++)
 {
  for(int j = 1; j <= 24; j += 23)
  {
   if(j > 1 || i >= 32)
   {
    gotoxy(i, j);cout << char(219);
   }
  }
 }
 for(int i = 1; i <= 24; i++)
 {
  for(int k = 1; k <= 80; k += 78)
  {
   gotoxy(k, i); cout << char(219);
  }
 }
}
//Writing Score
void skor()
{
 gotoxy(3,1); cout << "Skor : ";
 gotoxy(18,1); cout << "Panjang : ";
}
//write new score and write the length of snake
void tulis_skor()
{
 gotoxy(11,1); cout << (nEkor - 5) * 10;
 gotoxy(28,1); cout << nEkor;
}
//run some function
//in the begin of program, only once
void inisialisasi()
{
 cBorder(); //make sideline of game
 random_makanan(); //put food randomly
 skor(); //write score at up side
 tulis_skor(); //write score
}

int main() // main function
{
 system("cls"); //clear screen
 inisialisasi(); //run iniialize func
 while(!(isDestroy())) //while snake not lose yet
  {
   velo(); //change snake speed according X or Y
   getkey(); //get pressed button
   if(isEaten())//check status of food
   {
    nEkor += 2; //tail length plus by 2
    random_makanan(); //put food again
    tulis_skor();//update score
   }
   Sleep(40 - (nEkor / 10)); //delay more faster while the length more long too
  }
 system("cls"); //clear screen
 gotoxy(32,12); cout << "Skor : " << (nEkor - 5) * 10; //show score
 gotoxy(25,13);
 system("pause"); //finish
}
