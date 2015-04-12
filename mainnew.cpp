#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATA 22023599
using namespace std;

class Row{
public:
    int Click,Impression,AdID,AdvertiserID,Depth,Position,QueryID,KeywordID,TitleID,DescriptionID,UserID;
    char DisplayURL[100];
};

int compareUID(const void *r1, const void *r2)
{
    if(((Row*)r1)->UserID - ((Row*)r2)->UserID > 0)
        return 1;
    else if(((Row*)r1)->UserID - ((Row*)r2)->UserID < 0)
        return -1;
    else{
        if(((Row*)r1)->AdID - ((Row*)r2)->AdID > 0)
            return 1;
        else if(((Row*)r1)->AdID - ((Row*)r2)->AdID < 0)
            return -1;
        else{
            if(((Row*)r1)->QueryID - ((Row*)r2)->QueryID > 0)
                return 1;
            else if(((Row*)r1)->QueryID - ((Row*)r2)->QueryID < 0)
                return -1;
            else
                return 0;
        }
    }

}

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

int main(int argc, char *argv[])
{
    FILE *fp;
    fp = fopen(argv[1],"r");

    Row *row = new Row[DATA];
    int i = 0;
    while(i<22023547){
        fscanf(fp,"%d",&row[i].Click);
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
    cout << "READ:DONE" << endl;
    /*sort userID*/
    qsort(row, i, sizeof(Row), compareUID);
    /*for(int j=0;j<i;j+=10000)
        cout << row[j].UserID << endl;*/
        cout << row[22023546].UserID << endl;
    char command[10];
  while(true){
    cin >> command ;
    //cout << command << endl;
    int input[5];
    switch (index(command)){
    case 0:
        return 0;
        break;
    case 1:{
        for(int i=0;i<5;i++){
            cin >> input[i];
        }
        int outputClick = 0, outputImpression = 0;
        for(int i=0 ; i<22023547 ; i++){
            if(row[i].UserID == input[0]){
                cout << "FoundUID:" << row[i].UserID << endl;
                cout << "AdID:" << row[i].AdID << "\tQueryID:" << row[i].QueryID << "\tPosition:" << row[i].Position << "\tDepth:" << row[i].Depth << endl;
                if(row[i].AdID == input[1] && row[i].QueryID == input[2] &&
                    row[i].Position == input[3] && row[i].Depth == input[4]){
                        outputClick += row[i].Click;
                        outputImpression += row[i].Impression;
                }
            }
        }
        cout << "********************" << endl;
        cout << outputClick << " " << outputImpression << endl;
        cout << "********************" << endl;
        }break;
    case 2:{
        cin >> input[0];
        cout << "********************" << endl;
        for(int i=0 ; row[i].UserID <= input[0] ; i++){
            if(row[i].UserID < input[0])
                continue;
            if(row[i].Click > 0)
                cout << row[i].AdID << " " << row[i].QueryID << endl;
        }
        cout << "********************" << endl;
        }break;
    case 3:{
        for(int i=0;i<2;i++)
            cin >> input[i];
        cout << "********************" << endl;
        int a0=-1,an;
        for(int i=0 ; row[i].UserID <= input[0] && row[i].UserID <= input[1] ; i++){
            if(row[i].UserID < input[0] && row[i].UserID < input[1] ){
                a0 = i;
                continue;
            }
            an = i;
        }
        a0++;
        int b0 = an,bn;
        for(int j=(an+1) ; row[j].UserID <= input[0] || row[j].UserID <= input[1] ; j++){
            if(row[j].UserID < input[0] || row[j].UserID < input[1] ){
                b0 = j;
                continue;
            }
            bn = j;
        }
        b0++;
        //cout<<a0<<endl<<an<<endl<<b0<<endl<<bn<<endl;
        Row *property = new Row[DATA];
        int itter=0;
        for(int i = a0 ; i <= an ; i++){
            for(int j = b0 ; j <= bn ; j++){
                if(row[i].Impression > 0 && row[j].Impression > 0 && row[i].AdID == row[j].AdID){
        //cout<<"foundID:"<<row[i].AdID<<endl;
                    bool dupli=false;
                    for(int k=0;k<itter;k++){
                        if(property[k].AdID==row[i].AdID)
                            dupli=true;
                    }
                    bool propdupli=false;
                    for(int k=0;k<itter;k++){
                        if(property[itter].AdvertiserID==row[i].AdvertiserID &&
                            property[itter].KeywordID==row[i].KeywordID &&
                            property[itter].TitleID==row[i].TitleID &&
                            property[itter].DescriptionID==row[i].DescriptionID &&
                            strcmp(property[itter].DisplayURL,row[i].DisplayURL) == 0)
                                propdupli=true;
                    }
                    if(dupli==false){
                        property[itter].AdID=row[i].AdID;
                        strcpy(property[itter].DisplayURL,row[i].DisplayURL);
                        property[itter].AdvertiserID=row[i].AdvertiserID;
                        property[itter].KeywordID=row[i].KeywordID;
                        property[itter].TitleID=row[i].TitleID;
                        property[itter].DescriptionID=row[i].DescriptionID;
                        itter++;
                    }else if(propdupli==false){
                        property[itter].AdID=row[i].AdID;
                        strcpy(property[itter].DisplayURL,row[i].DisplayURL);
                        property[itter].AdvertiserID=row[i].AdvertiserID;
                        property[itter].KeywordID=row[i].KeywordID;
                        property[itter].TitleID=row[i].TitleID;
                        property[itter].DescriptionID=row[i].DescriptionID;
                        itter++;
                        property[itter].AdID=row[j].AdID;
                        strcpy(property[itter].DisplayURL,row[j].DisplayURL);
                        property[itter].AdvertiserID=row[j].AdvertiserID;
                        property[itter].KeywordID=row[j].KeywordID;
                        property[itter].TitleID=row[j].TitleID;
                        property[itter].DescriptionID=row[j].DescriptionID;
                        itter++;

                    }
                }
            }
        }
        int newADID;
        bool printflag=true;
        for(int i=0;i<itter;i++){
            if(i == 0 || property[i].AdID != property[i-1].AdID){
                cout << property[i].AdID << endl;
                newADID = i;
            }
            printflag = true;
            for(int j=newADID;j<=i;j++){
                if(property[i].AdvertiserID == property[j-1].AdvertiserID
                && property[i].KeywordID == property[j-1].KeywordID
                && property[i].TitleID == property[j-1].TitleID
                && property[i].DescriptionID == property[j-1].DescriptionID
                && strcmp(property[i].DisplayURL,property[j-1].DisplayURL) == 0)
                    printflag=false;

            }
            if(printflag==true)
                cout << "\t" << property[i].DisplayURL << " " << property[i].AdvertiserID << " " <<
                property[i].KeywordID << " " << property[i].TitleID << " " << property[i].DescriptionID << endl;
        }
        cout << "********************" << endl;
        }break;
    case 4:{
        cin >> input[0];
        double theta;
        cin >> theta;
        cout << "********************" << endl;
        double rate;
        for(int j = 0; j < i ; j++){
            if(row[j].AdID == input[0]){
                if(row[j].Click == 0 && row[j].Impression == 0)
                    rate = 0;
                else
                    rate = ((double)row[j].Click) / ((double)row[j].Impression);
                if( rate >= theta)
                    cout << row[j].UserID << endl;
            }
        }
        cout << "********************" << endl;
        }break;


    }
  }
}

