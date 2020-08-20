#include <stdio.h>
#include <stdlib.h>


const char id_s[] = "<a href=\"/song?id=";
#define id_s_len 18

const char name_s[] = "<b title=\"";
#define name_s_len 10

//const char quot="&quot;";
//const char nbsp="&nbsp;";

const char add[] = ".mp3 -O download/";//17

unsigned int num=17,a,b,flag=0;

const char nbsp[] = "&nbsp;";//6
const char quot[] = "&quot;";//6

char name[100]={0x00};
char id[100]={0x00};
char str[999999]={0x00};

unsigned char munum;

unsigned char listnum;

unsigned int addnum;

int main()
{
	printf("是否添加序号\n1:是\n2:否\n");
	scanf("%d",&addnum);

	FILE *fp;
	char ch;
	unsigned int all=0;
	fp = fopen("download.txt","r");
	ch=fgetc(fp);
	while(ch != EOF)
	{
		str[all]=ch;
		all++;
		ch = fgetc(fp);
	}
	fclose(fp);

	system("mkdir download");
	printf("%s",str);
	
	unsigned int list_all=0;
	while(str[num]!=0x00)
	{
		b=0;
		for(a=0;a<id_s_len;a++)
			if(str[num-a]==id_s[ id_s_len -1 -a])
				b++;
		if(b==id_s_len)
		{
			list_all++;
		}
		b=0;
		num++;
	}
	num=17;
	unsigned int list_all_bit = 10000;
	for(b=0;b<5;b++)
	{
		if(list_all/list_all_bit>0)
		{
			switch(list_all_bit)
			{
				case 10000:
					listnum=6;
					break;
				case 1000:
					listnum=5;
					break;
				case 100:
					listnum=4;
					break;
				case 10:
					listnum=3;
					break;
				case 1:
					listnum=2;
					break;
			}
			break;
		}
		list_all_bit = list_all_bit / 10;
	}

	while(str[num]!=0x00)
	{
		b=0;
		for(a=0;a<id_s_len;a++)
			if(str[num-a]==id_s[ id_s_len -1 -a ])
				b++;
		if(b==id_s_len)
		{
			num++;
			a=0;
			while(str[num]!='\"'||str[num+1]!='>')
			{
				id[a]=str[num];
				a++;
				num++;
			}
			id[a]=0x00;
			printf("%s		",id);
			flag++;
		}

		b=0;
		for(a=0;a<name_s_len;a++)
			if(str[num-a]==name_s[ name_s_len -1 -a ])
				b++;
		if(b==name_s_len)
		{
			if(addnum==1)
			{
			if(listnum>=6)
				name[listnum-6]=munum/10000%10+'0';
			if(listnum>=5)
				name[listnum-5]=munum/1000%10+'0';
			if(listnum>=4)
				name[listnum-4]=munum/100%10+'0';
			if(listnum>=3)
				name[listnum-3]=munum/10%10+'0';
			if(listnum>=2)
				name[listnum-2]=munum/1%10+'0';
			name[listnum-1]='.';
			}
			else
				listnum=0;
			munum++;
			num++;
			a=0;
			while(str[num]!='\"'||str[num+1]!='>')
			{
				b=0;
				unsigned char c=0,d=0;
				for(b=0;b<6;b++)
					if(str[num+b]==nbsp[b])
						c++;
				if(c==6)
				{
					name[a+listnum]=' ';
					num+=5;
					d++;
				}
				c=0;
				for(b=0;b<6;b++)
					if(str[num+b]==quot[b])
						c++;
				if(c==6)
				{
					name[a+listnum]='\'';
					num+=5;
					d++;
				}
				c=0;
				if(d==0)
					name[a+listnum]=str[num];
				a++;
				num++;
			}
			name[a+listnum]=0x00;
			printf("%s\n",name);
			flag++;
		}

		if(flag==2)
		{
			flag=0;
			char download[300]="wget http://music.163.com/song/media/outer/url?id=";
			a=0;
			while(id[a]!=0x00)
			{
				download[a+50]=id[a];
				a++;
			}
			unsigned int ad;
			for(ad=0;ad<17;ad++)
			{
				download[a+50+ad]=add[ad];
			}
			download[a+67]='\"';
			b=0;
			while(name[b]!=0x00)
			{
				download[a+68+b]=name[b];
				b++;
			}
			download[a+b+68] = '.';
			b++;
			download[a+b+68] = 'm';
			b++;
			download[a+b+68] = 'p';
			b++;
			download[a+b+68] = '3';
			b++;
			download[a+b+68] = '\"';
			b++;
			download[a+b+68] = 0x00;
			printf("%s\n",download);
			//download code
			system(download);
			for(b=0;b<100;b++)
			{
				name[b]=0x00;
				id[b]=0x00;
			}
		}
		num++;
	}
}
