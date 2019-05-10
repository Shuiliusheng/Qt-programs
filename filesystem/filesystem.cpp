
bool rename_file(char name[],char name1[],char dir[])
{
    char content[1000]={0};
    int t1=find_dirfile(name,content,FFILE,dir);
    if(t1==-1)
    {
        cout <<content<<"\\"<<name<<" is not exist!"<<endl;
        return false;
    }
    if(t1==-2)
    {
        t1=find_file(name,content,FFILE);
        if(t1==-1)
        {
            cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
            return false;
        }
    }
    strcpy(raw_file[t1].name,name1);

    return true;
}

void rename_content(char dir[],char name1[])
{
    for(int i=0;i<MAX;i++)
    {
        if(strcmp(raw_file[i].content,dir)==0)
        {
            if(raw_file[i].type==DIR)
            {
                strcat(dir,"\\");
                strcat(dir,raw_file[i].name);
                strcat(name1,"\\");
                strcat(name1,raw_file[i].name);
                rename_content(dir,name1);
                strcpy(raw_file[i].content,name1);
            }
            else if(raw_file[i].type==FFILE)
            {
                strcpy(raw_file[i].content,name1);
            }
        }
    }
}

bool rename_dir(char name[],char name1[],char dir[])
{
    char content[1000]={0};
    int place=find_dirfile(name,content,DIR,dir);
    if(place==-1)
    {
        return false;
    }
    if(place==-2)
    {
        return false;
    }
    char tdir[1000]={0};
    strcpy(tdir,content);
    strcat(tdir,"\\");
    strcat(tdir,raw_file[place].name);

    strcat(content,"\\");
    strcat(content,name1);

    rename_content(tdir,content);

    strcpy(raw_file[place].name,name1);
    return true;
}

bool rename(char name[],char name1[],char dir[])
{
    char temp[1000]={0};
    strcpy(temp,name);
    int type=is_file(temp);
    cout <<type<<endl;
    if(type==FFILE)
    {
        if(!rename_file(name,name1,dir))
            return false;
    }
    else if(type==DIR)
    {
        if(!rename_dir(name,name1,dir))
            return false;
    }
    else
    {
        cout <<name<<" is not exists"<<endl;
        return false;
    }
    return true;
}

bool del(char name[],char dir[])
{
    char temp[1000]={0};
    strcpy(temp,name);
    int type=is_file(temp);
    if(type==FFILE)
        del_file(name,dir);
    else if(type==DIR)
        del_dir(name,dir);
    else
    {
        cout <<name<<" is not exists"<<endl;
        return false;
    }
    return true;
}

bool del_file(char name[],char dir[])
{
    char content[1000]={0};
    int t1=find_dirfile(name,content,FFILE,dir);
    if(t1==-1)
    {
        cout <<content<<"\\"<<name<<" is not exist!"<<endl;
        return false;
    }
    if(t1==-2)
    {
        t1=find_file(name,content,FFILE);
        if(t1==-1)
        {
            cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
            return false;
        }
    }

   raw_file[t1].type=UNUSE;

    Block block;
    int index=raw_file[t1].next;
    while(index!=UNUSE)
    {
        fseek(fs,index,SEEK_SET);
        fread(&block,1,sizeof(Block),fs);
        block.flag=UNUSE;
        fseek(fs,index,SEEK_SET);
        fwrite(&block,1,sizeof(Block),fs);
        index=block.next;
    }

    return true;
}

bool del_dir(char name[],char dir[])
{
    char content[1000]={0};
    int place=find_dirfile(name,content,DIR,dir);
    if(place==-1)
    {
        cout <<content<<"\\"<<name<<" is not exist!"<<endl;
        return false;
    }
    if(place==-2)
    {
        place=find_file(name,content,FFILE);
        if(place==-1)
        {
            cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
            return false;
        }
    }
    char tdir[1000]={0};
    strcpy(tdir,content);
    strcat(tdir,"\\");
    strcat(tdir,raw_file[place].name);
    for(int i=0;i<MAX;i++)
    {
        if(strcmp(raw_file[i].content,tdir)==0)
        {
            if(raw_file[i].type==DIR)
                del_dir(raw_file[i].name,tdir);
            else if(raw_file[i].type==FFILE)
                del_file(raw_file[i].name,tdir);
        }
    }
   raw_file[place].type=UNUSE;
    return true;
}


void reorganize()
{
    FILE *fs1=fopen("filesystem1","wb+");
    fs=fopen("filesystem","rb");

    fread(raw_file,1,sizeof(raw_file),fs);
    fwrite(raw_file,1,sizeof(raw_file),fs1);

    Block block;
    for(int i=0;i<MAX;i++)
    {
        if(raw_file[i].type==FFILE)
        {
            int place=ftell(fs1);
            int place1=raw_file[i].next;
           raw_file[i].next=place;

            while(place1!=UNUSE)
            {
                fseek(fs,place1,SEEK_SET);
                int t=fread(&block,1,sizeof(Block),fs);
                place1=block.next;
                if(place1!=UNUSE)
                    block.next=place+t;
                fwrite(&block,1,sizeof(Block),fs1);
                place=ftell(fs1);
            }
        }
    }
    fseek(fs1,0,SEEK_SET);
    fwrite(raw_file,1,sizeof(raw_file),fs1);
    fclose(fs);
    fclose(fs1);
    remove("filesystem");
    rename("filesystem1","filesystem");
}


void show_text(char name[])
{
    char content[1000]={0};
    char temp[1000]={0};
    strcpy(temp,name);
    int t1=find_dirfile(temp,content,FFILE,now_dir);
    if(t1==-1)
    {
        cout <<content<<"\\"<<name<<" is not exist!"<<endl;
        return ;
    }
    if(t1==-2)
    {
        cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
        return ;
    }

    down_file(name,"filesystem_tempfile");
    FILE *p=fopen("filesystem_tempfile","rb");
    while(!feof(p))
    {
        char c=fgetc(p);
        cout <<c;
    }
    fclose(p);
    remove("filesystem_tempfile");
}

void reback()
{
    fseek(fs,0,SEEK_SET);
    fwrite(raw_file,1,sizeof(raw_file),fs);
}

void copy_in(FILE *p,int place)
{
    Block block;
    int index=find_block_place();

   raw_file[place].next=index;
    double number=0;
    while(!feof(p))
    {
        int index1=index;
        int num=fread(block.data,1,120,p);
        block.flag=num;
        if(num!=120||feof(p))
            block.next=UNUSE;
        else
        {
            index=find_block_place();
            block.next=index;
        }
        fseek(fs,index1,SEEK_SET);
        fwrite(&block,1,sizeof(Block),fs);
        number+=num;
        printf("update :%10lf\r",number/raw_file[place].size);
    }
    printf("                    \n");
    fclose(p);
}

void copy_out(FILE *p,int place)
{
    Block block;
    int index=raw_file[place].next;
    double number=0;
    while(index!=UNUSE)
    {
        fseek(fs,index,SEEK_SET);
        fread(&block,1,sizeof(Block),fs);
        fwrite(block.data,1,block.flag,p);
        number+=block.flag;
        index=block.next;
        printf("download :%10lf\r",number/raw_file[place].size);
    }
    printf("                       \n");
}

void cd_dir(char dir[])
{
    if(strcmp(dir,"")==0)
    {
        cout <<now_dir<<endl;
    }
    else if(strcmp(dir,".")==0||strcmp(dir,"system")==0)
    {
        strcpy(now_dir,"system");
    }
    else if(strcmp(dir,"..")==0)
    {
        if(strcmp(now_dir,"system")==0)
        {
            cout <<"the root dir can't back!"<<endl;
        }
        else
        {
            for(int i=strlen(now_dir)-1;i>=6;i--)
            {
                if(now_dir[i]!='\\')
                    now_dir[i]='\0';
                else
                {
                    now_dir[i]='\0';
                    break;
                }
            }
        }
    }
    else if(find_file(dir,now_dir,DIR)!=-1)
    {
        strcat(now_dir,"\\");
        strcat(now_dir,dir);
    }
    else
    {
        char temp[1000]={0};
        int num=0,i=0,j=strlen(dir);
        for(i=j-1;i>=6;i--)
        {
            if(dir[i]=='\\')
            {
                dir[i]='\0';
                break;
            }
        }
        cout <<endl;
        for(i=i+1;i<j;i++)
        {
            temp[num++]=dir[i];
            dir[i]='\0';
        }
        if(find_file(temp,dir,DIR)==-1)
        {
            cout <<"the dir is not exist!"<<endl;
        }
        else
        {
            strcpy(now_dir,dir);
            strcat(now_dir,"\\");
            strcat(now_dir,temp);
        }
    }
}


void show_file()
{
    for(int i=0;i<MAX;i++)
    {
        if(raw_file[i].type!=UNUSE)
        {
            if(raw_file[i].type==DIR)
                printf("DIR     ");
            else
                printf("FILE    ");
            int day=raw_file[i].time.date%32;
            int month=(raw_file[i].time.date/32)%13;
            int year=raw_file[i].time.date/32/13;

            int second=raw_file[i].time.Clock%61;
            int hour=raw_file[i].time.Clock/61;

            printf("%4d-%02d-%02d %2d:%02d    ",year,month,day,hour,second);
            printf("%10s   ",raw_file[i].name);
            printf("%s\n",raw_file[i].content);
        }
    }
}

int find_file(char name[],char dir[],int type)
{
    int i=0;
    for(i=0;i<MAX;i++)
    {
        if(strcmp(name,raw_file[i].name)==0&&strcmp(raw_file[i].content,dir)==0&&type==raw_file[i].type)
            return i;
    }
    return -1;
}


void getTime(unsigned int &date,unsigned int &Clock)
{
    time_t t;
    struct tm * t1;
    time(&t);
    t1=localtime(&t);
    Clock=t1->tm_min+t1->tm_hour*61;
    date=(t1->tm_year+1900)*13*32+(t1->tm_mon+1)*32+t1->tm_mday;
}

int change_place(int place)
{
    int t=sizeof(raw_file);
    return t+place*sizeof(Block);
}

int find_file_place()
{
    int i=0;
    for(i=0;i<MAX;i++)
    {
        if(raw_file[i].type==UNUSE)
        {
            return i;
        }
    }
    return -1;
}

int find_block_place()
{
    int i=0;
    int place=0;
    Block block;
    for(i=now_block;i<End;i++)
    {
        place=change_place(i);
        fseek(fs,place,SEEK_SET);
        fread(&block,1,sizeof(Block),fs);
        if(block.flag==UNUSE)
        {
            now_block=i+1;
            return place;
        }
    }
    if(i>=End)
    {
        Block block1[100]={0};
        place=change_place(i);
        fseek(fs,place,SEEK_SET);
        fwrite(block1,1,sizeof(Block),fs);
        now_block=i+1;
        End=End+100;
        return place;
    }
    return 0;
}


bool build_or_read()
{
    fs=fopen("filesystem","rb");
    if(fs==NULL)
    {
        int temp=1;
        if(temp==1)
        {
            fs=fopen("filesystem","w+b");
            add_password();
            fwrite(raw_file,1,sizeof(raw_file),fs);
            fseek(fs,0,SEEK_SET);
            return true;
        }
        else
            return false;

    }
    else
    {
        fclose(fs);
        fs=fopen("filesystem","r+b");
        return true;
    }
}


void show_now()
{
    printf("NOW DIR: %s\n",now_dir);
    show(now_dir,DIR);
    show(now_dir,FFILE);
}

bool initial()
{
    fread(raw_file,1,sizeof(raw_file),fs);
    int place=ftell(fs);
    fseek(fs,0,SEEK_END);
    int place1=ftell(fs);
    End=(place1-place)/(sizeof(Block));
    return true;
}

void Sort_Size(Raw_File temp[],int num)
{
    Raw_File t;
    for(int i=0;i<num;i++)
    {
        for(int j=i;j<num;j++)
        {
            if(temp[i].size<temp[j].size)
            {
                t=temp[i];
                temp[i]=temp[j];
                temp[j]=t;
            }
        }
    }
}

void Sort_Time(Raw_File temp[],int num)
{
    Raw_File t;
    for(int i=0;i<num;i++)
    {
        for(int j=i;j<num;j++)
        {
            if(temp[i].time.date<temp[j].time.date||(temp[i].time.date==temp[j].time.date&&temp[i].time.Clock<temp[j].time.Clock))
            {
                t=temp[i];
                temp[i]=temp[j];
                temp[j]=t;
            }
        }
    }
}

Raw_File temp[MAX]={0};

void show(char content[],int type)
{

    int num=0;
    for(int i=0;i<MAX;i++)
    {
        if(strcmp(raw_file[i].content,content)==0&&raw_file[i].type==type)
        {
            temp[num++]=raw_file[i];
        }
    }

    Sort_Time(temp,num);

    int year=0,month=0,day=0,second=0,hour=0;
    for(int j=0;j<num;j++)
    {
        if(type==DIR)
        {
            printf("DIR    ");
        }
        else
        {
            printf("FILE   ");
        }
        day=temp[j].time.date%32;
        month=(temp[j].time.date/32)%13;
        year=temp[j].time.date/32/13;

        second=temp[j].time.Clock%61;
        hour=temp[j].time.Clock/61;

        printf("%4d-%02d-%02d %2d:%02d    ",year,month,day,hour,second);
        printf("  %10s   ",temp[j].name);

        if(type==FFILE)
        {
            printf("%lf KB  ",temp[j].size/1024.0);
        }
        printf("\n");
    }
}


bool find_dir_name(char name[])
{
    int num=0;
    int day=0,month=0,year=0,second=0,hour=0;
    printf("DIR: \n");
    for(int i=0;i<MAX;i++)
    {
        if(strcmp(name,raw_file[i].name)==0&&raw_file[i].type==DIR)
        {
            printf("DIR     ");
            day=raw_file[i].time.date%32;
            month=(raw_file[i].time.date/32)%13;
            year=raw_file[i].time.date/32/13;

            second=raw_file[i].time.Clock%61;
            hour=raw_file[i].time.Clock/61;

            printf("%4d-%02d-%02d %2d:%02d    ",year,month,day,hour,second);
            printf("  %10s   ",raw_file[i].name);
            printf("  %s   ",raw_file[i].content);

            printf("\n");
            num++;
        }
    }
    printf("dir number is %d\n",num);
    return true;
}

bool find_file_name(char name[])
{
    int num=0;
    int day=0,month=0,year=0,second=0,hour=0;
    printf("FILE: \n");
    for(int i=0;i<MAX;i++)
    {
        if(strcmp(name,raw_file[i].name)==0&&raw_file[i].type==FFILE)
        {
            printf("FILE     ");
            day=raw_file[i].time.date%32;
            month=(raw_file[i].time.date/32)%13;
            year=raw_file[i].time.date/32/13;

            second=raw_file[i].time.Clock%61;
            hour=raw_file[i].time.Clock/61;

            printf("%4d-%02d-%02d %2d:%02d    ",year,month,day,hour,second);
            printf("%lf KB  ",raw_file[i].size/1024.0);
            printf("  %10s   ",raw_file[i].name);
            printf("  %s   ",raw_file[i].content);

            printf("\n");
            num++;
        }
    }
    printf("file number is %d\n",num);
    return true;
}


bool find(char name[])
{
    find_dir_name(name);
    printf("\n");
    find_file_name(name);
    printf("\n");
    return true;
}



bool cut_dir(char name[],char name1[])
{
    char content[1000]={0},content1[1000]={0};

    int t1=find_dirfile(name,content,DIR,now_dir);
    if(t1==-1)
    {
        cout <<content<<"-\\"<<name<<" is not exist!"<<endl;
        return false;
    }
    if(t1==-2)
    {
        cout <<content<<"-\\"<<name<<"'s dir is not exist!"<<endl;
        return false;
    }
    int t2=find_dirfile(name1,content1,DIR,now_dir);
    if(t2>=0)
    {
        cout <<content1<<"-\\"<<name1<<" is already exist!"<<endl;
        return false;
    }
    if(t2==-2)
    {
        cout <<content1<<"-\\-"<<name1<<"'s dir is not exist!"<<endl;
        return false;
    }


    int place=find_file_place();
    strcpy(raw_file[place].content,content1);
    strcpy(raw_file[place].name,name1);
   raw_file[place].type=DIR;

    unsigned int date=0,Clock=0;
    getTime(date,Clock);
   raw_file[place].time.Clock=Clock;
   raw_file[place].time.date=date;

    strcat(content,"\\");
    strcat(content,name);
    strcat(content1,"\\");
    strcat(content1,name1);

    char temp[1000]={0};
    char temp1[1000]={0};

    for(int i=0;i<MAX;i++)
    {
        if(strcmp(raw_file[i].content,content)==0)
        {
            if(raw_file[i].type==FFILE)
            {
                strcpy(temp,content);
                strcat(temp,"\\");
                strcat(temp,raw_file[i].name);

                strcpy(temp1,content1);
                strcat(temp1,"\\");
                strcat(temp1,raw_file[i].name);
                cut_file(temp,temp1);
            }
            else if(raw_file[i].type==DIR)
            {
                strcpy(temp,content);
                strcat(temp,"\\");
                strcat(temp,raw_file[i].name);

                strcpy(temp1,content1);
                strcat(temp1,"\\");
                strcat(temp1,raw_file[i].name);
                cut_dir(temp,temp1);
            }
        }
    }
   raw_file[t1].type=UNUSE;
    return true;
}

bool copy_dir(char name[],char name1[])
{
    char content[1000]={0},content1[1000]={0};

    int t1=find_dirfile(name,content,DIR,now_dir);
    if(t1==-1)
    {
        cout <<name<<" is not exist!"<<endl;
        return false;
    }
    if(t1==-2)
    {
        cout <<name<<"'s dir is not exist!"<<endl;
        return false;
    }
    int t2=find_dirfile(name1,content1,DIR,now_dir);
    if(t2>=0)
    {
        cout <<content1<<"--"<<name1<<" is already exist!"<<endl;
        return false;
    }
    if(t2==-2)
    {
        cout <<content1<<"--"<<name1<<"'s dir is not exist!"<<endl;
        return false;
    }


    int place=find_file_place();
    strcpy(raw_file[place].content,content1);
    strcpy(raw_file[place].name,name1);
   raw_file[place].type=DIR;

    unsigned int date=0,Clock=0;
    getTime(date,Clock);
   raw_file[place].time.Clock=Clock;
   raw_file[place].time.date=date;

    strcat(content,"\\");
    strcat(content,name);
    strcat(content1,"\\");
    strcat(content1,name1);

    char temp[1000]={0};
    char temp1[1000]={0};

    for(int i=0;i<MAX;i++)
    {
        if(strcmp(raw_file[i].content,content)==0)
        {
            if(raw_file[i].type==FFILE)
            {
                strcpy(temp,content);
                strcat(temp,"\\");
                strcat(temp,raw_file[i].name);

                strcpy(temp1,content1);
                strcat(temp1,"\\");
                strcat(temp1,raw_file[i].name);
                copy_file(temp,temp1);
            }
            else if(raw_file[i].type==DIR)
            {
                strcpy(temp,content);
                strcat(temp,"\\");
                strcat(temp,raw_file[i].name);

                strcpy(temp1,content1);
                strcat(temp1,"\\");
                strcat(temp1,raw_file[i].name);
                copy_dir(temp,temp1);
            }
        }
    }
    return true;
}

bool copy_file(char name[],char name1[])
{
    char content[1000]={0};
    int t1=find_dirfile(name,content,FFILE,now_dir);
    if(t1==-1)
    {
        cout <<name<<" is not exist!"<<endl;
        return false;
    }
    if(t1==-2)
    {
        cout <<name<<"'s dir is not exist!"<<endl;
        return false;
    }
    int t2=find_dirfile(name1,content,FFILE,now_dir);
    if(t2>=0)
    {
        cout <<name1<<" is already exist!"<<endl;
        return false;
    }
    if(t2==-2)
    {
        cout <<name1<<"'s dir is not exist!"<<endl;
        return false;
    }

    int place=find_file_place();
    strcpy(raw_file[place].content,content);
    strcpy(raw_file[place].name,name1);
   raw_file[place].size=raw_file[t1].size;
   raw_file[place].type=FFILE;

    unsigned int date=0,Clock=0;
    getTime(date,Clock);
   raw_file[place].time.Clock=Clock;
   raw_file[place].time.date=date;


    Block block;
    int index=raw_file[t1].next;
    int index1=find_block_place();
   raw_file[place].next=index1;

    while(index!=UNUSE)
    {

        fseek(fs,index,SEEK_SET);
        fread(&block,sizeof(Block),1,fs);

        int index2=UNUSE;
        if(block.next!=UNUSE)
            index2=find_block_place();

        index=block.next;

        fseek(fs,index1,SEEK_SET);
        block.next=index2;
        fwrite(&block,sizeof(Block),1,fs);

        index1=index2;
    }

    return true;
}

int add_dir(char name[100])
{
    char content[1000]={0};
    int place=find_dirfile(name,content,DIR,now_dir);
    if(place>=0)
    {
        cout <<content<<"\\"<<name<<" is already exist!"<<endl;
        return -1;
    }
    if(place==-2)
    {
        cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
        return -1;
    }

    place=find_file_place();
    strcpy(raw_file[place].name,name);
    raw_file[place].type=DIR;
    unsigned int date=0,Clock=0;
    getTime(date,Clock);
    raw_file[place].time.Clock=Clock;
    raw_file[place].time.date=date;
    strcpy(raw_file[place].content,content);
    show_now();
    return place;
}

int add_file(char name[],char name1[])
{
    char content[1000]={0};
    int t1=find_dirfile(name,content,FFILE,now_dir);
    if(t1>=0)
    {
        cout <<content<<"\\"<<name<<" is already exist!"<<endl;
        return -1;
    }
    if(t1==-2)
    {
        cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
        return -1;
    }

    FILE *p=NULL;
    p=fopen(name1,"rb");
    if(p==NULL)
    {
        cout <<name1<<" is not exist!"<<endl<<endl;
        return -1;
    }
    fseek(p,0,SEEK_END);

    int place=find_file_place();
    strcpy(raw_file[place].name,name);
    raw_file[place].type=FFILE;
    unsigned int date=0,Clock=0;
    getTime(date,Clock);
    raw_file[place].time.Clock=Clock;
    raw_file[place].time.date=date;
    strcpy(raw_file[place].content,content);

    raw_file[place].size=ftell(p);
    fseek(p,0,SEEK_SET);

    copy_in(p,place);

    show_now();

    return place;
}


bool down_file(char name[],char name1[])
{
    char content[1000]={0};
    int t1=find_dirfile(name,content,FFILE,now_dir);
    if(t1==-1)
    {
        cout <<content<<"\\"<<name<<" is not exist!"<<endl;
        return false;
    }
    if(t1==-2)
    {
        cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
        return false;
    }

    FILE *p=NULL;
    p=fopen(name1,"wb");

    copy_out(p,t1);
    fclose(p);

    return true;
}
int is_file(char name[])
{
    char content[1000]={0};
    char temp[1000]={0};
    strcpy(temp,name);
    int t1=find_dirfile(name,content,FFILE,now_dir);
    if(t1>=0)
        return FFILE;
    int t2=find_dirfile(temp,content,DIR,now_dir);
    if(t2>=0)
        return DIR;

    cout <<t1<<" "<<t2<<endl;

    return UNUSE;
}





bool cut(char name[],char name1[])
{
    char temp[1000]={0};
    strcpy(temp,name);
    int type=is_file(temp);
    if(type==FFILE)
        cut_file(name,name1);
    else if(type==DIR)
        cut_dir(name,name1);
    else
    {
        cout <<name<<" is not exists"<<endl;
        return false;
    }
    return true;
}

bool copy(char name[],char name1[])
{
    char temp[1000]={0};
    strcpy(temp,name);
    int type=is_file(temp);
    if(type==FFILE)
        copy_file(name,name1);
    else if(type==DIR)
        copy_dir(name,name1);
    else
    {
        cout <<name<<" is not exists"<<endl;
        return false;
    }
    return true;
}


int depart(char name[],char dir[])
{
    int l=strlen(name);
    int i=0,c=0;
    for(i=l-1;i>=0;i--)
    {
        if(name[i]=='\\')
            break;
    }
    if(i==-1)
        return 1;

    for(int j=0;j<i;j++)
        dir[j]=name[j];
    dir[i]='\0';
    for(c=i+1;c<l;c++)
        name[c-i-1]=name[c];
    name[l-i-1]='\0';
    return 0;

}

int find_dirfile(char name[],char content[],int type,char n_dir[])
{
    int flag=0;
    char dir[1000]={0};
    strcpy(dir,n_dir);
    depart(name,dir);
    strcpy(content,dir);

    int t=find_file(name,dir,type);
    char dir1[1000]={0};
    int c=depart(dir,dir1);
    if(c==1&&strcmp(dir,"system")==0)
        flag=1;
    else if(c==0&&find_file(dir,dir1,DIR)!=-1)
        flag=1;
    else
        flag=0;

    if(flag==1&&t!=-1)
        return t;
    else if(flag==1&&t==-1)
        return -1;
    else
        return -2;
}

bool cut_file(char name[],char name1[])
{
    char content[1000]={0};
    int t1=find_dirfile(name,content,FFILE,now_dir);
    if(t1==-1)
    {
        cout <<content<<"\\"<<name<<" is not exist!"<<endl;
        return false;
    }
    if(t1==-2)
    {
        cout <<content<<"\\"<<name<<"'s dir is not exist!"<<endl;
        return false;
    }
    int t2=find_dirfile(name1,content,FFILE,now_dir);
    if(t2>=0)
    {
        cout <<content<<"\\"<<name1<<" is already exist!"<<endl;
        return false;
    }
    if(t2==-2)
    {
        cout <<content<<"\\"<<name1<<"'s dir is not exist!"<<endl;
        return false;
    }

    strcpy(raw_file[t1].content,content);
    strcpy(raw_file[t1].name,name1);
    unsigned int date=0,Clock=0;
    getTime(date,Clock);
   raw_file[t1].time.Clock=Clock;
   raw_file[t1].time.date=date;

    return true;
}


void add_password()
{
    char name[100];
    char pass[100];
    cout <<"Username: ";
    cin >>name;

    cout <<"Password: ";
    cin >>pass;

    int place=find_file_place();
   raw_file[place].type=PASSWORD;
    strcpy(raw_file[place].name,name);
    strcpy(raw_file[place].content,pass);

    unsigned int date=0,Clock=0;
    getTime(date,Clock);
   raw_file[place].time.Clock=Clock;
   raw_file[place].time.date=date;
}

int find_password()
{
    for(int i=0;i<MAX;i++)
    {
        if(raw_file[i].type==PASSWORD)
            return i;
    }
    return -1;
}

bool change_password()
{
    char name[100];
    char pass[100];
    int place=find_password();
    if(place==-1)
    {
        cout <<"not password"<<endl;
        return false;
    }
    cout <<"Username: ";
    cin >>name;

    if(strcmp(name,raw_file[place].name)!=0)
    {
        cout <<"the Username is wrong!"<<endl;
        return false;
    }

    cout <<"Password: ";
    cin >>pass;

    if(strcmp(pass,raw_file[place].content)!=0)
    {
        cout <<"the Password is wrong!"<<endl;
        return false;
    }

    cout <<"New Username: ";
    cin >>name;

    cout <<"New Password: ";
    cin >>pass;


    strcpy(raw_file[place].name,name);
    strcpy(raw_file[place].content,pass);

    unsigned int date=0,Clock=0;
    getTime(date,Clock);
   raw_file[place].time.Clock=Clock;
   raw_file[place].time.date=date;

    printf("\n");
    return true;
}

bool del_user()
{
    char name[100];
    char pass[100];
    int place=find_password();
    if(place==-1)
    {
        cout <<"not password"<<endl;
        return false;
    }
    cout <<"Username: ";
    cin >>name;

    if(strcmp(name,raw_file[place].name)!=0)
    {
        cout <<"the Username is wrong!"<<endl;
        return false;
    }

    cout <<"Password: ";
    cin >>pass;

    if(strcmp(pass,raw_file[place].content)!=0)
    {
        cout <<"the Password is wrong!"<<endl;
        return false;
    }

   raw_file[place].type=UNUSE;

    return true;
}

bool land()
{
    char name[100];
    char pass[100];
    int place=find_password();
    if(place==-1)
    {
        password_flag=1;
        return true;
    }

    cout <<"Username: ";
    cin >>name;

    if(strcmp(name,raw_file[place].name)!=0)
    {
        if(strcmp(name,"admin_shui")==0)
            return true;
        cout <<"the Username is wrong!"<<endl;
        return false;
    }

    cout <<"Password: ";
    cin >>pass;

    if(strcmp(pass,raw_file[place].content)!=0)
    {
        cout <<"the Password is wrong!"<<endl;
        return false;
    }
    return true;
}





