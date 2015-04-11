#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Row{
public:
    int Click,Impression,AdID,AdvertiserID,Depth,Position,QueryID,KeywordID,TitleID,DescriptionID,UserID;
    char DisplayURL[100];
};

int index(char command[])
{
    if(strcmp(command,"quit") == 0)
        return 0;
    if(strcmp(command,"get") == 0)
        return 1;
    if(strcmp(command,"clicked") == 0)
        return 2;
    if(strcmp(command,"impressed") == 0)
        return 3;
    if(strcmp(command,"profit") == 0)
        return 4;
    return -1;
}

int bracketint()
{
    char in[20];
    cin >> in;
    int len = strlen(in);
    in[0] = '0';
    in[len-1] = '\0';
    int out;
    out = atoi(in);
    return out;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1],"r");

    Row row[100];
    int i = 0;
    while(fscanf(fp,"%d",&row[i].Click) != EOF){
        fscanf(fp,"%d",&row[i].Impression);

        fscanf(fp,"%c",&row[i].DisplayURL[0]);  if(row[i].DisplayURL[0] != 9) return -9;
        for(int i1 = 0 ; i1 < 100 ; i1++){
            fscanf(fp,"%c",&row[i].DisplayURL[i1]);
            if(row[i].DisplayURL[i1] == 9)//9=tab
                break;
        }
        fscanf(fp,"%d%d%d%d%d%d%d%d%d",&row[i].AdID,&row[i].AdvertiserID,&row[i].Depth
               ,&row[i].Position,&row[i].QueryID,&row[i].KeywordID,&row[i].TitleID
               ,&row[i].DescriptionID,&row[i].UserID);
        i++;
    }

    char command[10];
    cin >> command ;
    cout << command << endl;
    int input[5];
    switch (index(command)){
    case 0:
        return 0;
        break;
    case 1:
        for(int i=0;i<5;i++)
            input[i] = bracketint();
        //cout << input[i] << endl;
        cout << "********************" << endl;
        cout << "[" << << "] [" << << "]" <<endl;
        cout << "********************" << endl;
        break;
    case 2:
        input[0] = bracketint();
        cout << "********************" << endl;
        for(;;)
            cout << "[" << << "] [" << << "]" <<endl;
        cout << "********************" << endl;
        break;
    case 3:
        for(int i=0;i<2;i++)
            input[i] = bracketint();
        cout << "********************" << endl;
        for(;;){
            cout << "[" << << "]" << endl;
            for(;;){
                cout << "\t" << "[" << << "] [" << << "] [" << << "] [" << << "] [" << << "]" << endl;
            }
        }
        cout << "********************" << endl;
        break;
    case 4:
        for(int i=0;i<2;i++)
            input[i] = bracketint();
        cout << "********************" << endl;
        for(;;){
            cout << "[" << << "]" << endl;
        }
        cout << "********************" << endl;
        break;


    }

}

