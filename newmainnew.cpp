#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DATA 150000000
using namespace std;

class Row{
public:
    int Click,Impression,AdID,AdvertiserID,Depth,Position,QueryID,KeywordID,TitleID,DescriptionID,UserID;
    char DisplayURL[25];
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
    while(fscanf(fp,"%d",&row[i].Click) != EOF){
        fscanf(fp,"%d",&row[i].Impression);
        fscanf(fp,"%c",&row[i].DisplayURL[0]);  if(row[i].DisplayURL[0] != 9) return -9;
        for(int j = 0 ; j < 100 ; j++){
            fscanf(fp,"%c",&row[i].DisplayURL[j]);
            if(row[i].DisplayURL[j] == 9)//9=tab
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
    cout << "SORT:DONE" << endl;

    char command[10];
  while(true){
    cin >> command ;
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
        for(int i=0 ; i<DATA ; i++){
            if(row[i].UserID == input[0]){
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
            for(int j=newADID;j<i;j++){
                if(property[i].AdvertiserID == property[j].AdvertiserID
                && property[i].KeywordID == property[j].KeywordID
                && property[i].TitleID == property[j].TitleID
                && property[i].DescriptionID == property[j].DescriptionID
                && strcmp(property[i].DisplayURL,property[j].DisplayURL) == 0)
                    printflag=false;

            }
            if(printflag==true)
                cout << "\t" << property[i].DisplayURL << " " << property[i].AdvertiserID << " " <<
                property[i].KeywordID << " " << property[i].TitleID << " " << property[i].DescriptionID << endl;
        }
        cout << "********************" << endl;
        delete [] property;
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

