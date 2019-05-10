#include "mainwindow1.h"
const int dim=8;
const int cx=8;
const int cy=8;
const int dim_s=2;
const int choose=2;
MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent),h(0),w(0),h1(0),w1(0),n_w(0)
{
    this->test_main();
}

MainWindow1::~MainWindow1()
{
    
}
void MainWindow1::test_main()
{
    Mat src=imread("f:/num\\test.jpg");
    Mat src1(src.rows,src.cols,src.type());
    for(int m=0;m<src.rows;m++)
        for(int n=0;n<src.cols;n++)
            for(int i=0;i<3;i++)
                src1.at<Vec3b>(m,n)[i]=src.at<Vec3b>(m,n)[i];
//    this->study(src,src1,2);
    this->test(src,src1);
}

void MainWindow1::test(Mat src,Mat src1)
{
    this->weight_gray(src);
    int th=this->get_threshold_2(src);
    int color=this->binary(src,th,choose);
    Point l,r,l1,r1;
    this->getpostion(src,l,r,color);

    l1.x=l.x;l1.y=r.y;
    r1.x=r.x;r1.y=l.y;
    line(src1,l,l1,Scalar(200,200,0),1,8,0);
    line(src1,l1,r,Scalar(200,200,0),1,8,0);
    line(src1,r1,r,Scalar(200,200,0),1,8,0);
    line(src1,l,r1,Scalar(200,200,0),1,8,0);

    imshow("3",src);

    for(int m=l.y;m<=r.y;m++)
        for(int n=l.x;n<=r.x;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                n_w++;
        }
    n_w/=(dim*dim);
    h=(r.y-l.y)/dim,w=(r.x-l.x)/dim;
    cout <<n_w<<" "<<h<<" "<<w<<endl;

    if(n_w==0)
    {
        cout <<"problem:h:w"<<endl;
        return ;
    }
    double *temp=new double[dim*dim+1],*temp1=new double[4*cx+4*cy+1];
    this->setFeature(src,temp,color,l);

    h1=(r.y-l.y)/(cy),w1=(r.x-l.x)/(cx);

    for(int i=1;i<=cx;i++)
    {
        int n=l.x+i*w1;
        Point q,q1;
        q.x=n,q.y=l.y;
        q1.x=n,q1.y=r.y;
        line(src1,q,q1,Scalar(200,200,0),1,8,0);
    }
    for(int i=1;i<=cy;i++)
    {
        int m=l.y+i*h1;
        Point q,q1;
        q.x=l.x,q.y=m;
        q1.x=r.x,q1.y=m;
        line(src1,q,q1,Scalar(200,200,0),1,8,0);
    }
    imshow("1",src1);

    this->setFeature1(src,temp1,color,l,r);
    this->detect(temp,temp1);
    delete temp;
    delete temp1;
}

void MainWindow1::study(Mat src,Mat src1, int num)
{
    this->weight_gray(src);
    int th=this->get_threshold_2(src);
    int color=this->binary(src,th,choose);
    Point l,r,l1,r1;
    this->getpostion(src,l,r,color);

    l1.x=l.x;l1.y=r.y;
    r1.x=r.x;r1.y=l.y;
    line(src1,l,l1,Scalar(200,200,0),1,8,0);
    line(src1,l1,r,Scalar(200,200,0),1,8,0);
    line(src1,r1,r,Scalar(200,200,0),1,8,0);
    line(src1,l,r1,Scalar(200,200,0),1,8,0);

    imshow("3",src);

    for(int m=l.y;m<=r.y;m++)
        for(int n=l.x;n<=r.x;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                n_w++;
        }
    n_w/=(dim*dim);
    h=(r.y-l.y)/dim,w=(r.x-l.x)/dim;
    cout <<n_w<<" "<<h<<" "<<w<<endl;

    if(n_w==0)
    {
        cout <<"problem:h:w"<<endl;
        return ;
    }
    double *temp=new double[dim*dim+1],*temp1=new double[4*cx+4*cy+1];
    this->setFeature(src,temp,color,l);

    h1=(r.y-l.y)/(cy),w1=(r.x-l.x)/(cx);

    for(int i=1;i<=cx;i++)
    {
        int n=l.x+i*w1;
        Point q,q1;
        q.x=n,q.y=l.y;
        q1.x=n,q1.y=r.y;
        line(src1,q,q1,Scalar(200,200,0),1,8,0);
    }
    for(int i=1;i<=cy;i++)
    {
        int m=l.y+i*h1;
        Point q,q1;
        q.x=l.x,q.y=m;
        q1.x=r.x,q1.y=m;
        line(src1,q,q1,Scalar(200,200,0),1,8,0);
    }
    imshow("1",src1);

    this->setFeature1(src,temp1,color,l,r);
    this->write_file(num,temp,temp1);
    delete temp;
    delete temp1;
}





//对图像进行二值化处理，th为阈值
int MainWindow1::binary(Mat &src,int th,int flag)
{
    int r=src.rows,c=src.cols;
    int color=254;
    for(int m=0;m<r;m++)
        for(int n=0;n<c;n++)
        {
            if(flag==1)
            {
                if(src.at<Vec3b>(m,n)[0]>th)
                    for(int i=0;i<3;i++)
                        src.at<Vec3b>(m,n)[i]=color;
                else
                    for(int i=0;i<3;i++)
                        src.at<Vec3b>(m,n)[i]=0;
            }
            else
            {
                if(src.at<Vec3b>(m,n)[0]<th)
                    for(int i=0;i<3;i++)
                        src.at<Vec3b>(m,n)[i]=color;
                else
                    for(int i=0;i<3;i++)
                        src.at<Vec3b>(m,n)[i]=0;
            }
        }
    cout <<"color:"<<color<<endl;
    return color;
}
void  MainWindow1::weight_gray(Mat &src)
{
    int t=0;
    int temp[3];
    int r=src.rows,c=src.cols;
    for(int m=0;m<r;m++)
        for(int n=0;n<c;n++)
        {
            for(int i=0;i<3;i++)
                temp[i]=src.at<Vec3b>(m,n)[i];
            t=(int)(0.114*temp[0]+0.587*temp[1]+0.299*temp[2]);
            src.at<Vec3b>(m,n)[0]=t;
            src.at<Vec3b>(m,n)[1]=t;
            src.at<Vec3b>(m,n)[2]=t;
        }
//    imshow("weight_gray",src);
}
//迭代法计算的迭代函数
int MainWindow1::cal_t(Mat src, int t)
{
    double a=0,a1=0;
    int n1=0,n2=0;
    for(int m=0;m<src.rows;m++)
        for(int n=0;n<src.cols;n++)
        {
            int t1=src.at<Vec3b>(m,n)[0];
            if(t1<t)
                a+=t1,n1++;
            if(t1>t)
                a1+=t1,n2++;
        }
    a/=n1;
    a1/=n2;
    if(fabs(((a+a1)/2)-t)<1)
        return t;
    t=(int)((a+a1)/2);
    return this->cal_t(src,t);
}
//使用迭代法计算获得阈值，初始值为整体的灰度均值
int MainWindow1::get_threshold_2(Mat src)
{
    int r=src.rows,c=src.cols;
    double a=0;
    for(int m=0;m<r;m++)
        for(int n=0;n<c;n++)
            a+=src.at<Vec3b>(m,n)[0];
    a/=(r*c);
    int t=this->cal_t(src,(int)a);
    return t;
}

void MainWindow1::getpostion(Mat src,Point &l,Point &r1,int color)
{
    int r=src.rows,c=src.cols;//r y,c x
    int m=0,n=0;
    for(m=0;m<r;m++)
    {
        for(n=0;n<c;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                break;
        }
        if(n!=c)
            break;
    }
    l.y=m;
    for(n=0;n<c;n++)
    {
        for(m=0;m<r;m++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                break;
        }
        if(m!=r)
            break;
    }
    l.x=n;
    for(m=r-1;m>=0;m--)
    {
        for(n=c-1;n>=0;n--)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                break;
        }
        if(n!=-1)
            break;
    }
    r1.y=m;
    for(n=c-1;n>=0;n--)
    {
        for(m=r-1;m>=0;m--)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                break;
        }
        if(m!=-1)
            break;
    }
    r1.x=n;
}
//
void MainWindow1::setFeature(Mat src,double temp[],int color,Point l)
{
    for(int i=0;i<dim;i++)//i y
    {
        for(int j=0;j<dim;j++)//j x
        {
            Point s,e;
            s.x=l.x+j*w;
            s.y=l.y+i*h;
            e.x=l.x+(j+1)*w;
            e.y=l.y+i*h+h;
            temp[dim*i+j]=this->cal(src,color,s,e);
        }
    }
}
///

double MainWindow1::cal(Mat src, int color, Point s, Point e)
{
    double c=0;
    for(int m=s.y;m<=e.y;m++)
        for(int n=s.x;n<=e.x;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                c++;
        }
    return (double)(c/(n_w));
}

void MainWindow1::write_file(int i,double temp[],double temp1[])
{
    char str[20];
    sprintf(str,"\src\\%d.txt",i);
    FILE *p;
    p=fopen(str,"ab");
    for(int c=0;c<dim*dim;c++)
    {
//        co/ut <<temp[c]<<" ";
        fprintf(p,"%lf,",temp[c]);
    }
//    cout <<endl;
    int t=4*cx+4*cy;
    for(int c=0;c<t;c++)
    {
//        cout <<temp1[c]<<" " ;
        fprintf(p,"%lf,",temp1[c]);
    }
//    cout <<endl;
    fprintf(p,"\n");
    fclose(p);
}

void MainWindow1::detect_t(int temp[],int n,double t[],int color)
{
    int flag=0,flag1=0,c=0;
    for(int i=0;i<n;i++)
    {
        if(flag1==0&&temp[i]==color)
        {
            flag1=1;
            t[c++]=(i-flag)/(n*1.0);//(i-flag)/(n*1.0)
            flag=i;
        }
        if(c==2)
            break;
        if(flag1==1&&temp[i]==0)
        {
            flag1=0;
            flag=i;
        }
    }
    c=2;
    flag=n-1,flag1=0;
    for(int i=n-1;i>=0;i--)
    {
        if(flag1==0&&temp[i]==color)
        {
            flag1=1;
            t[c++]=(flag-i)/(n*1.0);//
            flag=i;
        }
        if(c==4)
            break;
        if(flag1==1&&temp[i]==0)
        {
            flag1=0;
            flag=i;
        }
    }
}

void MainWindow1::setFeature1(Mat src,double temp[],int color,Point l,Point r)
{
    int *ty=new int[r.y-l.y+2],*tx=new int[r.x-l.x+2];
    int t=2*cx+2*cy;
    ///x
    int flag=0;
    for(int i=1;i<=cx;i++)
    {
        int n=l.x+i*w1;
        double t1[4]={0};
        for(int m=l.y;m<=r.y;m++)
            ty[m-l.y]=src.at<Vec3b>(m,n)[0];
        detect_t(ty,(r.y-l.y+1),t1,color);
        temp[flag]=t1[0],temp[flag+t]=t1[1],flag++;
        temp[flag]=t1[2],temp[flag+t]=t1[3],flag++;

    }
    for(int i=1;i<=cy;i++)
    {
        int m=l.y+i*h1;
        double t1[4]={0};
        for(int n=l.x;n<=r.x;n++)
            tx[n-l.x]=src.at<Vec3b>(m,n)[0];
        detect_t(ty,(r.x-l.x+1),t1,color);
        temp[flag]=t1[0],temp[flag+t]=t1[2],flag++;
        temp[flag]=t1[1],temp[flag+t]=t1[3],flag++;
    }
    delete tx,ty;
}




int MainWindow1::detect(double temp[],double temp2[])
{
    double min=10000;
    int flag=0;
    for(int n=0;n<dim_s;n++)
    {
        double temp1=this->getmin(temp,temp2,n);
        if(temp1<min)
            min=temp1,flag=n;
    }
    cout <<"flag:"<<flag<<endl;
    return flag;
}
double MainWindow1::getmin(double temp[],double temp2[],int i)
{
    char str[10];
    sprintf(str,"\src\\%d.txt",i+1);
    FILE *p=NULL;
    p=fopen(str,"rb");
    if(p==NULL)
    {
        cout <<"problem\n";
        return 0;
    }
    double min=1000,m1=0;
    int t=4*cx+4*cy;
    double *temp1=new double[dim*dim+1+t];
    while(!feof(p))
    {
        m1=0;
        for(int c=0;c<dim*dim;c++)
        {
            fscanf(p,"%lf,",&temp1[c]);
            m1+=(temp[c]-temp1[c])*(temp[c]-temp1[c]);
        }
        for(int c=0;c<t;c++)
        {
            fscanf(p,"%lf,",&temp1[c]);
            m1+=(temp2[c]-temp1[c])*(temp2[c]-temp1[c]);
        }
        if(m1<min)
            min=m1;
    }
    fclose(p);
    delete temp1;
    return min;

}
