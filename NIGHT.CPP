#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip.h>
#include<ctype.h>
#define orderfile"ff2.txt"
#define recsize 100
#define max 11
fstream file;
char buffer[80],c[20];
int count[11]={0,0,0,0,0,0,0,0,0,0,0};
class order
{
     public:
	      char o_no[5],name[15],location[15],phone[15];
	      char o_time[10],d_time[10],amount[5];
	      void unpack();
	      void disp();
	      void initial();
	      void read();
	      int retrieve(int addr,char k[]);

 };
 void compute(int t)
 {
	//int e=0;
	char dummy[75];
	int temp;
       //	for(i=0;i<5;i++)
	file.seekp(t*recsize*5,ios::beg);
		//count[addr]=count[addr]+1;
	       //	cout<<count[addr];
		file.getline(dummy,5,'||');
		if(strcmp(dummy,"####")!=0)
		{
			count[t]=count[t]+1;
			//cout<<count[t];
		}
	      //	else
	      //	count[t]=count[t]+1;

      //	else
	       //	{

			temp=(t*recsize*5);
			//file.seekp((addr*recsize*5)+50,ios::beg);
			temp=temp+100;
			while(temp<(t*recsize*5)+500)
			{
				file.seekp(temp,ios::beg);
				file.getline(dummy,5,'||');
				if(strcmp(dummy,"####")!=0)
				{
				       /*	file.seekp(temp,ios::beg);
					file<<buffer;
					flag=1;
					break;*/
					count[t]=count[t]+1;
					//cout<<t<<"\t"<<count[t];
				}
				temp=temp+100;
			}
	       cout<<"\nCount val of bucket:"<<t<<"\t"<<count[t];
		}



void order::initial()
{
  int i,j,k,m;
  //for(m=0;m<5;m++)
    //   compute(m);
  file.open(orderfile,ios::in);
  if(!file)
  {
     file.open(orderfile,ios::out);
     if(!file)
     {
      cout<<"unable to open the file";
      exit(1);
      }
    for(i=0;i<11;i++)
    {
     //file.seekp(i*recsize,ios::beg);
	//file<<0;
     for(k=0;k<5;k++)
     {
	for(j=0;j<recsize-2;j++)
		file<<"#";
	if(k!=4)
		file<<"||";
     //file<<endl;
     }
	file<<endl;
   }
   //file<<endl;
 cout<<"empty file created";
 }
 file.close();

 for(m=0;m<11;m++)
 {
 file.open(orderfile,ios::in);
  if(!file)
  {
     file.open(orderfile,ios::out);
     if(!file)
     {
      cout<<"unable to open the file";
      exit(1);
      }
    }   compute(m);
    file.close();
  }
 return;
 }
void order::read()
{ int q,c;

 label2:
 cout<<"enter the order number:";      gets(o_no);

if(isdigit(o_no[0])&&isdigit(o_no[1])&&isdigit(o_no[2]))
 {
   //cout<<strlen(o_no)<<endl<<endl;
 if(strlen(o_no)-1==2)
 {
 cout<<"enter the name:";           gets(name);
 cout<<"enter the location:";      gets(location);
 cout<<"enter the phone:";      gets(phone);
 cout<<"enter the order time:"; gets(o_time);
 cout<<"enter the delivery time:";  gets(d_time);
 cout<<"enter the amount:";  gets(amount);

 strcpy(buffer,o_no);             strcat(buffer,"|");
 strcat(buffer,name);             strcat(buffer,"|");
 strcat(buffer,location);               strcat(buffer,"|");

 strcat(buffer,phone);             strcat(buffer,"|");
 strcat(buffer,o_time);               strcat(buffer,"|");

 strcat(buffer,d_time);             strcat(buffer,"|");
 strcat(buffer,amount);               strcat(buffer,"|");
 return;
 }
 else
 {
    cout<<"INVALID ORDER NUMBER\n";
    goto label2;

 }
 }
  else
 {
    cout<<"INVALID ORDER NO\n";
    goto label2;

 }

}

int hash(char key[])
{
  int i=0,sum=0;
  while(key[i]!='\0')
  {
    sum=sum+(key[i]-48);
    i++;
    }
 return sum % max;
 }

void store(int addr)
{
	char dummy[10];
	int flag=0,i,temp,temp1;
	file.open(orderfile,ios::in|ios::out);
	//cout<<count[addr];
	if(count[addr]!=5)
	{
		file.seekp(addr*recsize*5,ios::beg);
		count[addr]=count[addr]+1;
		//cout<<count[addr];
		file.getline(dummy,5,'||');
		if(strcmp(dummy,"####")==0)
		{
			file.seekp(addr*recsize*5,ios::beg);
			file<<buffer;
			flag=1;
		}
		else
		{
			temp=(addr*recsize*5);
			//file.seekp((addr*recsize*5)+50,ios::beg);
			temp=temp+100;
			while(temp<(addr*recsize*5)+500)
			{
				file.seekp(temp,ios::beg);
				file.getline(dummy,5,'||');
				if(strcmp(dummy,"####")==0)
				{
					file.seekp(temp,ios::beg);
					file<<buffer;
					flag=1;
					break;
				}
				temp=temp+100;
			}
		}

	}
	else
	{
		for(i=addr+1;i!=addr;i++)
		{
			if(i%max==0)
				i=0;
			if(count[i]!=5)
			{
				file.seekp(i*recsize*5,ios::beg);
				count[i]=count[i]+1;
				cout<<count[i];
				file.getline(dummy,5,'||');
				if(strcmp(dummy,"####")==0)
				{
					cout<<"\n collision has occured\n";
					cout<<"home address is"<<addr<<"actual address is"<<i<<"\n";
					file.seekp(i*recsize*5,ios::beg);
					file<<buffer;
					flag=1;
					break;
				}
				else
				{
					temp1=(i*recsize*5);
					//file.seekp((i*recsize*5)+50,ios::beg);
					temp1=temp1+100;
					while(temp1<(i*recsize*5)+500)
					{
						file.seekp(temp1,ios::beg);
						file.getline(dummy,5,'||');
						if(strcmp(dummy,"####")==0)
						{
							file.seekp(temp1,ios::beg);
							file<<buffer;
							flag=1;
							break;
						}
						temp1=temp1+100;
					}
				 }


			}
		 }
	}
	if((i==addr) && (!flag))
		cout<<"hash file is full,record cannot be inserted\n";
	file.close();
	return;
}

int order::retrieve(int addr,char k[])
{
 int found=0,i,temp;
 char dummy[10];
 i=addr;
 temp=i*recsize*5;
 file.open(orderfile,ios::in|ios::out);
 do
 {
  while(temp<i*recsize*5+500)
  {
  file.seekp(temp,ios::beg);
  file.getline(dummy,5,'\n');
  if(strcmp(dummy,"####")==0)
  {
      temp=temp+100;

   }
   else
  {
  file.seekp(temp,ios::beg);
  file.getline(o_no,15,'|');
   if(strcmp(o_no,k)==0)
   {
	found=1;
	cout<<"\n RECORD FOUND\n"<<endl;

	file.getline(name,15,'|');
	file.getline(location,15,'|');
	file.getline(phone,15,'|');
	file.getline(o_time,10,'|');
	file.getline(d_time,10,'|');

	file.getline(amount,5,'|');

       cout<<"O_NO="<<o_no<<"\n________________________________\nNAME="<<name<<"\n________________________________\nLOCATION="<<location<<"\n________________________________\nPHONE="<<phone;
       cout<<"\n________________________________\nO_TIME="<<o_time<<"\n________________________________\nD_TIME="<<d_time<<"\n________________________________\nAMOUNT="<<amount<<"\n________________________________";
       gets(c);
    return temp;

  }
   temp=temp+100;
} }

   i++;
   if(i%max==0)
      i=0;

}while(i!=addr);
if(found==0)
 cout<<"\n RECORD DOES NOT EXISTS\n";
 gets(c);
 return -1;
 }
 void order::unpack()
 {
	//char ddummy[50];
	file.getline(o_no,5,'|');
	file.getline(name,15,'|');
	file.getline(location,15,'|');
	file.getline(phone,15,'|');
	file.getline(o_time,10,'|');
	file.getline(d_time,10,'|');
	file.getline(amount,5,'|');


	/*file.getline(daddress,15,'|');
	file.getline(dob,15,'|');
	file.getline(avail,5,'|');
	file.getline(ddummy,85,'\n');*/

}
 void order::disp()
 {
    int i,j,temp;
    char dummy[10];
    //char dum[75];
     file.open(orderfile,ios::in);
     cout<<setiosflags(ios::left);
     cout<<"_______________________________________________________________________________"<<endl;
     cout<<setw(10)<<"ORDER NO " <<setw(10)<<"NAME "<<setw(15)<<"LOCATION "<<setw(15)<<"PHONE "<<setw(10)<<"O_TIME "<<setw(10)<<"D_TIME "<<setw(10)<<"AMOUNT "<<endl;
     cout<<"________________________________________________________________________________"<<endl;
     for(i=0;i<11;i++)
     {
	 temp=(i*recsize*5);
	 for(j=1;j<=5;j++)
	 {
	     file.seekp(temp,ios::beg);
	     file.getline(dummy,5,'\n');
	     if(strcmp(dummy,"####")!=0)
		{
			file.seekp(temp,ios::beg);
			unpack();
		    cout<<setiosflags(ios::left);
		    cout<<setw(10)<<o_no<<setw(10)<<name<<setw(15)<<location<<setw(15)<<phone<<setw(10)<<o_time<<setw(10)<<d_time;
		    cout<<setw(10)<<amount<<endl;
		   // cout<<"*******************************************************************************************************************************************"<<endl;

		}
		temp=temp+100;
	 }

     }
     cout<<"_______________________________________________________________________________"<<endl;
     gets(c);


}




void main()
{
 int ch,addr,pos,i;

 char skey[15];//char b[60];
 order s;
 clrscr();
 s.initial();

 la:for(;;)

 { clrscr();
 cout<<"\n*****************************************\n";
  cout<<endl<<"1.READ\n2.DISPLAY\n3.SEARCH\n4.DELETE\n5.MODIFY \n6.EXIT\n\n";
  cout<<"******************************************\n";
  cout<<"ENTER YOUR CHOICE"<<endl;

  cin>>ch;

  switch(int(ch))
 {
  label1:
	  case 1:clrscr();
	  cout<<endl<<"ENTER YOUR ORDER DETAILS:"<<endl;

	  s.read();
	  addr=hash(s.o_no);
	  store(addr);
	  break;
  case 2:clrscr();
	 cout<<"DETAILS ARE:"<<endl;
	 s.disp();
	 break;
  case 3:clrscr();
	 cout<<"ENTER  ORDER NUMBER :"<<endl;
	 cin>>skey;
	 addr=hash(skey);
	 s.retrieve(addr,skey);
	 break;
  case 4:clrscr();
	 cout<<"DELETION BASED ON ORDER NUMBER\n" ;
	 cout<<"ENTER THE ORDER NUMBER\n";
	 cin>>skey;
	 addr=hash(skey);
	 cout<<"THE DELETED RECORD DETAILS ARE\n\n" ;
	 pos=s.retrieve(addr,skey);
	 cout<<pos;
	 if(pos!=-1)
	 {
	   count[addr]=count[addr]-1;
	   file.open(orderfile,ios::out);
	   file.seekp(pos,ios::beg);
	   for(i=1;i<99;i++)
	      //b[i]='#';
	   file.put('#');
	   file.close();
	 }
	 break;
  case 5:clrscr();
	 cout<<"MODIFICATION BASED ON THE ORDER NUMBER\n" ;
	 cout<<"ENTER THE ORDER NUMBER\n";
	 cin>>skey;
	 addr=hash(skey);
	 cout<<"RECORD TO BE MODIFIED IS:\n\n";
	 pos=s.retrieve(addr,skey);
	 //cout<<pos;
	 if(pos!=-1)
	 {
	   count[addr]=count[addr]-1;
	   file.open(orderfile,ios::out);
	   file.seekp(pos,ios::beg);
	   for(i=1;i<99;i++)
	      //b[i]='#';
	   file.put('#');
	  file.close();
	  goto label1;


	 }

	 break;

 case 6:exit(0);
 default:goto la;


 }
file.close();
}
}

