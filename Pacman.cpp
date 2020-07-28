#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
using namespace std;

char tmp_map[20][23];

char map[20][23]={
"+###################+",
"|    |   ## ##      |",
"| |  | | ## ## | ## |",
"| |    | ## ## | ## |",
"| | ###| ## ## |    |",
"| |              ## |",
"| |## | ### #|## ## |",
"| |   |      |   ## |",
"|   |   |      |    |",
"| ##| ##|    ##| ###|",
"|   |   |      |    |",
"| |   |      |   ## |",
"| |## | ### #|## ## |",
"| |              ## |",
"| | ###| ## ## |    |",
"| |    | ## ## | ## |",
"| |  | | ## ## | ## |",
"|    |   ## ##      |",
"+###################+"
};

void gotoxy( short x, short y )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}


int mod_select()
{
	int i,j,x;
	for(i=0;i<25;i++)
	{
		if(i==0 || i==24)
		for(j=0;j<74;j++)
		{
			cout<<"*";		
		}		
		else
		{
			for(j=0;j<75;j++)
			{
				if(j==0 || j==74)
					cout<<"*";
				else
					cout<<" ";		
			}
		}
		cout<<endl;
	}	
	
	gotoxy(22,8);
	cout<<"1)Easy";
	gotoxy(22,9);
	cout<<"2)Medium";
	gotoxy(22,10);
	cout<<"3)Hard";
	gotoxy(22,11);
	cout<<"Enter the mode : ";
	cin>>x;
	return x;	
}

void display()
{
	for(int i=0;i<20;i++)
	{
		cout<<map[i]<<endl;
	}
}

struct target
{
	short x;
	short y;
};

struct walk
{
	short walk_count;
	short x;
	short y;
	short back;
};

vector <target> walk_queue;

vector <walk> BFSArray;
void AddArray(int x,int y,int wc,int back)
{
	if( tmp_map[y][x] == ' ' || tmp_map[y][x] == '.' )
	{
		tmp_map[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		BFSArray.push_back( tmp );
	}
}

void Path(int sx,int sy,int x,int y)
{
	memcpy(tmp_map,map,sizeof(map));
	BFSArray.clear();
	walk tmp;
	tmp.x=sx;
	tmp.y=sy;
	tmp.walk_count=0;
	tmp.back=-1;
	BFSArray.push_back(tmp);
	int i=0;
	while(i<BFSArray.size())
	{
		if(BFSArray[i].x==x && BFSArray[i].y==y)
		{
			walk_queue.clear();
			target tmp2;
			while(BFSArray[i].walk_count!=0)
			{
				tmp2.x=BFSArray[i].x;
				tmp2.y=BFSArray[i].y;
				walk_queue.push_back(tmp2);
				i=BFSArray[i].back;	
			}
			break;	
		}	
		AddArray(BFSArray[i].x+1,BFSArray[i].y,BFSArray[i].walk_count+1,i);
		AddArray(BFSArray[i].x-1,BFSArray[i].y,BFSArray[i].walk_count+1,i);
		AddArray(BFSArray[i].x,BFSArray[i].y+1,BFSArray[i].walk_count+1,i);
		AddArray(BFSArray[i].x,BFSArray[i].y-1,BFSArray[i].walk_count+1,i);	
		i++;
	}	
	BFSArray.clear();
}

main()
{
	int mod=mod_select();
	int pts=0,frame=0;
	if(mod==3)
	mod=1;
	else if(mod==2)
	mod=2;
	else
	mod=3;
	int x=11;
	int y=9;
	int old_x,old_y;
	int ex=1,ey=1;
	system("cls");
	Path(ex,ey,x,y);
	system("cls");
	display();
	gotoxy(x,y);
	cout<<"H";
	while(1)
	{
		gotoxy(x,y);
		cout<<" ";
		old_x=x;
		old_y=y;
		if( GetAsyncKeyState( VK_UP ) )
		{
			if(map[y-1][x]=='.')
			{
				y--;
				pts++;		
			}	
			else if(map[y-1][x]==' ')
			{
				y--;
			}
		}	
		if( GetAsyncKeyState( VK_DOWN ) )
		{
			if(map[y+1][x]=='.')
			{
				y++;
				pts++;		
			}	
			else if(map[y+1][x]==' ')
			{
				y++;
			}
		}	
		if( GetAsyncKeyState( VK_LEFT ) )
		{
			if(map[y][x-1]=='.')
			{
				x--;
				pts++;		
			}	
			else if(map[y][x-1]==' ')
			{
				x--;
			}
		}	
		if( GetAsyncKeyState( VK_RIGHT ) )
		{
			if(map[y][x+1]=='.')
			{
				x++;
				pts++;		
			}	
			else if(map[y][x+1]==' ')
			{
				x++;
			}
		}	
		if(old_x!=x || old_y!=y)
		{
			Path(ex,ey,x,y);
		}
		
		gotoxy(x,y);
		cout<<"H";
		map[ey][ex]='.';
		gotoxy(ex,ey);
		cout<<".";
		if(frame%mod==0 && walk_queue.size()!=0)
		{
			ex=walk_queue.back().x;
			ey=walk_queue.back().y;
			walk_queue.pop_back();
		}
		gotoxy(ex,ey);
		cout<<"E";
		
		if(ex==x && ey==y)
		break;
		
		gotoxy(32,1);
		cout<<pts;
		Sleep(100);
		frame++;
	}	
	system("cls");
	cout<<"You Lose the game....";
	cout<<"\nYour points are : "<<pts;
	
}
