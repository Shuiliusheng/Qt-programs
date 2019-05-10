#include "mainwindow2.h"
const int n_s=7;
const int n_e=3;
MainWindow2::MainWindow2(QWidget *parent)
    : QMainWindow(parent),el(0,0),er(0,0),
      el1(0,0),er1(0,0),ml(0,0),mr(0,0)
{
    this->test_main();
}

MainWindow2::~MainWindow2()
{
    
}
void MainWindow2::test_main()
{
    Mat src1=imread("f:/num\\p3.jpg");
    detect(src1);
//    this->study(src1,3);

}

int MainWindow2::detect(Mat src)
{
    double *temp=new double[n_s+1];
    this->get_postion(src);
    this->setFeature(temp);
    int no=this->charge(temp);
    return no;
}

int MainWindow2::charge(double temp[])
{
    double min=10000;
    int flag=0;
    double l=0;
    for(int n=0;n<n_s;n++)
        l+=(temp[n]*temp[n]);
    l=sqrt(l);
    for(int n=1;n<=n_e;n++)
    {
        double temp1=this->getmin(temp,n,l);
        cout <<"similar degree:"<<temp1<<endl;
        if(temp1<min)
            min=temp1,flag=n;
    }
    if(min<0.05)
    {
        cout <<"people is No:"<<flag<<endl;
        return flag;
    }
    else
        cout <<"No proper people to fit!"<<endl;
    return 0;
}

double MainWindow2::getmin(double temp[],int i,double l)
{
    char str[30];
    sprintf(str,"\src\\people%d.txt",i);
    FILE *p=NULL;
    p=fopen(str,"rb");
    if(p==NULL)
    {
        cout <<"problem\n";
        return 0;
    }
    double min=1000,m1=0;
    double *temp1=new double[n_s+1];
    while(!feof(p))
    {
        m1=0;
        for(int c=0;c<n_s;c++)
        {
            fscanf(p,"%lf,",&temp1[c]);
            m1+=(temp[c]-temp1[c])*(temp[c]-temp1[c]);
        }
        m1=sqrt(m1)/l;
        if(m1<min)
            min=m1;
    }
    fclose(p);
    delete temp1;
    return min;
}

void MainWindow2::study(Mat src, int i)
{
    double *temp=new double[n_s+1];
    this->get_postion(src);
    this->setFeature(temp);
    write_file(temp,i);
    delete temp;
}
void MainWindow2::write_file(double temp[],int i)
{
    char str[30];
    sprintf(str,"\src\\people%d.txt",i);
    FILE *p;
    p=fopen(str,"ab");
    for(int c=0;c<n_s;c++)
        fprintf(p,"%lf,",temp[c]);
    fprintf(p,"\n");
    fclose(p);
}

void MainWindow2::setFeature(double temp[])
{
    temp[0]=1.0*(er.y-el.y)/(1.0*(mr.y-el.y));//左眼高比
    temp[1]=1.0*(er.x-el.x)/(1.0*(er1.x-el.x));//左眼宽比
    temp[2]=1.0*(er1.y-el1.y)/(1.0*(mr.y-el1.y));//右眼高比
    temp[3]=1.0*(er1.x-el1.x)/(1.0*(er1.x-el.x));//右眼宽比
    temp[4]=1.0*(mr.y-ml.y)/(1.0*(mr.y-el.y));//嘴巴高比左眼
    temp[5]=1.0*(mr.y-ml.y)/(1.0*(mr.y-el1.y));//嘴巴高比右眼
    temp[6]=1.0*(mr.x-ml.x)/(1.0*(er1.x-el.x));//嘴巴宽比
}





void MainWindow2::get_postion(Mat src1)
{
    int t[3]={0};
    imshow("1",src1);
    this->delete_back(src1,t);
    Mat src;
    src=this->de_longly_nosing(src1);
    this->weight_gray(src);
    int th=this->get_threshold_2(src);
    th=(th+127)/2;
    int color=this->binary(src,th,1);////
    imshow("4",src);
    this->cut(src,color,4);
    this->cut(src,color,2);
    detect1(src,color);
    if(er.y-el.y<=5)
        er.y=er1.y;
    if(er.x-el.x<=5)
    {
        if(el.x<(3*el1.x-2*er1.x))
            er.x=el.x+(er1.x-el1.x);
        else
            el.x=er.x-(er1.x-el1.x);
    }
    if(er1.y-el1.y<=5)
        er1.y=er.y;
    if(er1.x-el1.x<=5)
    {
        if(el1.x>(3*er1.x-2*el1.x))
            er1.x=el1.x+(er.x-el.x);
        else
            el1.x=er1.x-(er.x-el.x);
    }
    cout <<el.x<<" "<<el.y<<endl;
    cout <<er.x<<" "<<er.y<<endl;
    cout <<el1.x<<" "<<el1.y<<endl;
    cout <<er1.x<<" "<<er1.y<<endl;
    imshow("3",src);
}


int MainWindow2::find_bottom(int temp[], int n, int num,int s)
{
    for(int i=num+s;i<n-num-1;i++)
    {
        int flag=0,c=0,e=0;
        for(c=i-num;c<i;c++)
        {
            if(temp[c]<temp[i])
                break;
        }
        if(c==i)flag=1;
        for(c=i+1;c<=i+num;c++)
        {
            if(temp[c]<temp[i])
                break;
        }
        if(c>(i+num)&&flag==1&&temp[i-num]-temp[i]>=3&&temp[i+num]-temp[i]>=3)
            return i;
    }
    return 0;
}

void MainWindow2::detect1(Mat src, int color)
{
    int r=src.rows,c=src.cols;
    Mat src1(r,c,16);
    int *h=new int[r+2];
    for(int m=0;m<r;m++)
    {
        h[m]=0;
        for(int n=0;n<c;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                h[m]++;
        }
        for(int n=0;n<c;n++)
        {
            if(n<h[m])
                for(int i=0;i<3;i++)
                    src1.at<Vec3b>(m,n)[i]=255;
            else
                for(int i=0;i<3;i++)
                    src1.at<Vec3b>(m,n)[i]=0;
        }
    }
    int i=0,first,first1;
    for(i=0;i<r;i++)
        if(h[i]!=0)break;
    if(r-i>10)
    {
        first=this->find_bottom(h,r,4,i);
        first1=this->find_bottom(h,r,4,first);
    }
    int first2=0,first3=0;
    for(int a=first;a<=first1;a++)
        if(h[a]-h[a+1]>=2)
        {
            first2=a+1;
            break;
        }
    for(int a=first1+1;a<r;a++)
        if(h[a]-h[a+1]>=1&&h[a+1]-h[a+2]>=1)
        {
            first3=a;
            break;
        }
    for(int a=first1;a>=first;a--)
        if(h[a]-h[a-1]>=2)
        {
            first=a-1;
            first1=first2;
            break;
        }


    this->detect_eye(src,first1,first3,color);
    int h1=er1.x-el.x,e=0;
    e=first1+h1;
    this->detect_mouth(src,first3,e,(er.x+el.x)/2,(er1.x+el1.x)/2);
    delete h;
}

void MainWindow2::detect_mouth(Mat src, int h1, int h2, int w1, int w2)
{
    int *w=new int[w2-w1+2],*h=new int[h2-h1+2];
    int m=0,n=0;
    for(n=w1;n<=w2;n++)
    {
        w[n-w1]=0;
        for(m=h1;m<=h2;m++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==0)
                w[n-w1]++;
        }
    }


    int flag=0;
    for(n=1;n<=w2-w1-1;n++)
    {
        if(flag==0&&w[n]==0)
            flag=1;
        if(flag==1&&w[n]>0&&w[n-1]==0&&w[n+1]>0)
            break;
    }
    if(n>(w2-w1)/2)
        n=0;
    int n1=0;
    flag=0;
    for(n1=w2-w1-1;n1>=1;n1--)
    {
        if(flag==0&&w[n1]==0)
            flag=1;
        if(flag==1&&w[n1]>0&&w[n1+1]==0&&w[n1-1]>0)
            break;
    }
    if(n1<(w2-w1)/2)
        n1=w2-w1;


    ml.x=n+w1,mr.x=n1+w1;

    for(m=h1;m<=h2;m++)
    {
        h[m-h1]=0;
        for(n=ml.x;n<=mr.x;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==0)
                h[m-h1]++;
        }
    }

    flag=0;
    for(m=h2-h1-1;m>=1;m--)
    {
        if(flag==0&&h[m]==0)
            flag=1;
        if(flag==1&&h[m]>0&&h[m+1]==0&&h[m-1]>0)
            break;
    }
    if(m<(h2-h1)/2)
        m=h2-h1;
    int m1=0;
//    flag=0;

//    for(m1=0;m1<=h2-h1;m1++)
//        if(h[m1]>max)
//            max=h[m1],flag=m1;

    for(m1=h1;m1<=h2;m1++)
    {
        int temp1=src.at<Vec3b>(m1,ml.x)[0];
        int temp2=src.at<Vec3b>(m1,mr.x)[0];
        if(temp1==0||temp2==0)
            break;
    }
    m1=m1-h1;

    for(m1;m1>=2;m1--)
        if(h[m1]==0&&h[m1-1]==0&&h[m1-2]==0&&h[m1+1]>0)
            break;
    ml.y=m1+h1,mr.y=m+h1;

    for(n=w1;n<=w2;n++)
        for(int i=0;i<3;i++)
        {
            src.at<Vec3b>(h1,n)[i]=0;
            src.at<Vec3b>(h2,n)[i]=0;
        }
    for(n=ml.x;n<=mr.x;n++)
        for(int i=0;i<3;i++)
        {
            src.at<Vec3b>(ml.y,n)[i]=100;
            src.at<Vec3b>(mr.y,n)[i]=100;
        }
    for(m=h1;m<=h2;m++)
        for(int i=0;i<3;i++)
        {
            src.at<Vec3b>(m,w1)[i]=0;
            src.at<Vec3b>(m,w2)[i]=0;
        }
    for(m=ml.y;m<=mr.y;m++)
        for(int i=0;i<3;i++)
        {
            src.at<Vec3b>(m,ml.x)[i]=100;
            src.at<Vec3b>(m,mr.x)[i]=100;
        }
    delete w,h;
}



void MainWindow2::detect_eye(Mat src, int h1, int h2, int color)
{
    int *w=new int[src.cols+2];
    int c=src.cols,r=src.rows;
    Mat src1(r,c,16);
    int m=0,n=0;
    for(n=0;n<c;n++)
    {
        w[n]=0;
        for(m=h1;m<=h2;m++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==0)
                w[n]++;
        }
        for(m=0;m<r;m++)
        {
            if(m<w[n])
                for(int i=0;i<3;i++)
                    src1.at<Vec3b>(m,n)[i]=255;
            else
                for(int i=0;i<3;i++)
                    src1.at<Vec3b>(m,n)[i]=0;
        }
    }
    for(n=0;n<c;n++)
        if(w[n]!=(h2-h1+1))
            break;
    int mid=n;
    for(n=c-1;n>=mid;n--)
        if(w[n]!=(h2-h1+1))
            break;
    mid=(mid+n)/2;
//    for(m=0;m<r;m++)
//        for(int i=0;i<3;i++)
//        {
//            src.at<Vec3b>(m,mid)[i]=200;
//            src1.at<Vec3b>(m,mid)[i]=200;
//        }

    if(w[mid]==0)
    {
        for(m=mid;m<c;m++)
            if(w[m-1]==0&&w[m]==0&&w[m+1]-w[m]>=1)
                break;
        el1.x=m+1;
        int num=10;
        for(m=el1.x+num;m<c-num;m++)
        {
            if(w[m]==0)
            {
                er1.x=m;
                break;
            }
        }
        if(m==c-num)
        {
           int m1=0;
           for(m1=el1.x;m1<c;m1++)
               if(w[m1]>=h2-h1-2)
                   break;
           for(int m2=m1;m2>=el1.x;m2--)
               if(w[m2]-w[m2-1]<=0)
               {
                   er1.x=m2;
                   break;
               }
        }
//        cout <<"b:"<<er1.x<<endl;

        num=4;
        for(m=mid;m>=0;m--)
            if(w[m+1]==0&&w[m]==0&&w[m-1]-w[m]>=1)
                break;
        er.x=m-1;
        for(m=er.x-num;m>num;m--)
        {
            if(w[m]==0)
            {
                el.x=m;
                break;
            }
        }
        if(m==num)
        {
            int m1=0;
            for(m1=er.x;m1>=0;m1--)
            {
//                cout <<w[m1]<<" "<<h2-h1<<endl;
                if(w[m1]>=h2-h1-2)
                    break;
            }
            for(int m2=m1;m2<=el1.x;m2++)
                if(w[m2]-w[m2+1]<=0)
                {
//                    cout <<m2<<endl;
//                    cout <<w[m2]-w[m2+1]<<" "<<w[m2+1]-w[m2+2]<<endl;
                    el.x=m2;
                    break;
                }
        }

        int max=0;
        for(m=el.x;m<=er.x;m++)
            if(w[m]>max)
                max=w[m];
        el.y=h1;
        el.y=find_eye1(src,h1,h2,el.x,er.x);
        er.y=el.y+max;

        max=0;
        for(m=el1.x;m<=er1.x;m++)
            if(w[m]>max)
                max=w[m];
        el1.y=h1;
        el1.y=find_eye1(src,h1,h2,el1.x,er1.x);
        er1.y=el1.y+max;

        for(n=el.x;n<=er.x;n++)
            for(int i=0;i<3;i++)
            {
                src.at<Vec3b>(el.y,n)[i]=0;
                src.at<Vec3b>(er.y,n)[i]=0;
            }
        for(n=el1.x;n<=er1.x;n++)
            for(int i=0;i<3;i++)
            {
                src.at<Vec3b>(el1.y,n)[i]=50;
                src.at<Vec3b>(er1.y,n)[i]=50;
            }
        for(m=el.y;m<=er.y;m++)
            for(int i=0;i<3;i++)
            {
                src.at<Vec3b>(m,el.x)[i]=0;
                src.at<Vec3b>(m,er.x)[i]=0;
            }
        for(m=el1.y;m<=er1.y;m++)
            for(int i=0;i<3;i++)
            {
                src.at<Vec3b>(m,el1.x)[i]=0;
                src.at<Vec3b>(m,er1.x)[i]=0;
            }
    }
//    imshow("a",src1);
    delete w;
}

int MainWindow2::find_eye1(Mat src,int h1, int h2, int w1, int w2)
{
    int *h=new int[h2-h1+2];

    for(int m=h1;m<=h2;m++)
    {
        h[m-h1]=0;
        for(int n=w1;n<=w2;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==0)
                h[m-h1]++;
        }
//        cout <<h[m-h1]<<" ";
    }
//    cout <<endl;
    for(int m=0;m<=h2-h1;m++)
        if(h[m]!=0&&h[m-1]==0&&h[m+1]-h[m]>=0&&h[m+2]-h[m]>=0)
        {
//            cout <<" m:"<<m<<endl;
            return m+h1;
        }
    delete h;
    return h1;
}










void MainWindow2::cut(Mat src,int color,int num)
{
    int r=src.rows,c=src.cols;
    for(int m=0;m<r;m++)
    {
        for(int n=0;n<c;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
            {
                for(int n1=n;n1<n+num&&n1<c;n1++)
                    for(int i=0;i<3;i++)
                        src.at<Vec3b>(m,n1)[i]=0;
                break;
            }
        }
    }

    for(int m=0;m<r;m++)
    {
        for(int n=c-1;n>=0;n--)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
            {
                for(int n1=n;n1>n-num&&n1>=0;n1--)
                    for(int i=0;i<3;i++)
                        src.at<Vec3b>(m,n1)[i]=0;
                break;
            }
        }
    }

    for(int n=0;n<c;n++)
    {
        for(int m=0;m<r;m++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
            {
                for(int m1=m;m1<m+num&&m1<r;m1++)
                    for(int i=0;i<3;i++)
                        src.at<Vec3b>(m,n)[i]=0;
                break;
            }
        }
    }


}



void MainWindow2::delete_back1(Mat src,int t[])
{
    int m1=1;
    t[0]=0,t[1]=0,t[2]=0;
    int m=0;
    for(m=0;m<src.rows;m++)
    {
        int n=0;
        for(n=0;n<src.cols;n++)
        {
            int temp=0;
            for(int i=0;i<3;i++)
                temp+=src.at<Vec3b>(m,n)[i];
            if(temp!=0)
                break;
        }
        if(n!=src.cols)
            break;
    }
    cout <<m<<endl;
    int flag=0;
    for(int m2=m;m2<m+m1;m2++)
    {
        for(int n=0;n<src.cols;n++)
        {
            int temp=0;
            for(int i=0;i<3;i++)
                temp+=src.at<Vec3b>(m2,n)[i];
            if(temp!=0)
            {
                flag++;
                for(int i=0;i<3;i++)
                    t[i]+=src.at<Vec3b>(m2,n)[i];
            }
        }
    }
    for(int i=0;i<3;i++)
        t[i]=t[i]/flag;
    cout <<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
    for(int m=0;m<src.rows;m++)
        for(int n=0;n<src.cols;n++)
        {
            int temp[3]={0};
            for(int i=0;i<3;i++)
                temp[i]=src.at<Vec3b>(m,n)[i];
            int a=0;
            for(a=0;a<3;a++)
                if(fabs(temp[a]-t[a])>=30)
                    break;
            if(a==3)
            {
                for(int i=0;i<3;i++)
                    src.at<Vec3b>(m,n)[i]=0;
            }

        }
}


void MainWindow2::delete_back(Mat src,int t[])
{
    int m1=3;
    int flag=0;
    t[0]=0,t[1]=0,t[2]=0;
    for(int m=0;m<m1;m++)
    {
        for(int n=3;n<src.cols-3;n++)
        {
            flag++;
            for(int i=0;i<3;i++)
                t[i]+=src.at<Vec3b>(m,n)[i];
        }
    }
    for(int i=0;i<3;i++)
        t[i]=t[i]/flag;
//    cout <<t[0]<<" "<<t[1]<<" "<<t[2]<<endl;
    for(int m=0;m<src.rows;m++)
        for(int n=0;n<src.cols;n++)
        {
            int temp[3]={0};
            for(int i=0;i<3;i++)
                temp[i]=src.at<Vec3b>(m,n)[i];
            int a=0;
            for(a=0;a<3;a++)
                if(fabs(temp[a]-t[a])>=30)
                    break;
            if(a==3)
            {
//                cout <<"aa"<<endl;
                for(int i=0;i<3;i++)
                    src.at<Vec3b>(m,n)[i]=0;
            }

        }
}

//对图像进行二值化处理，th为阈值
int MainWindow2::binary(Mat &src,int th,int flag)
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
void  MainWindow2::weight_gray(Mat &src)
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
int MainWindow2::cal_t(Mat src, int t)
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
int MainWindow2::get_threshold_2(Mat src)
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


//使用四点，判断该像素点是否为独立噪点
bool MainWindow2::find_nosing(Mat src,int r,int c)
{
//    int dir[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
    int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    int temp[3];
    int tt=8;
    int t=0;
    int t0=0;
    int num=0;
    for(int n=0;n<3;n++)
        temp[n]=src.at<Vec3b>(r,c)[n];
    t0=(int)(0.114*temp[0]+0.587*temp[1]+0.299*temp[2]);
    for(int i=0;i<tt;i++)
    {
        for(int n=0;n<3;n++)
            temp[n]=src.at<Vec3b>(r+dir[i][0],c+dir[i][1])[n];
        t=(int)(0.114*temp[0]+0.587*temp[1]+0.299*temp[2]);
        if(fabs(t0-t)>5)
        {
            num++;
        }
    }
    if(num>=tt)
        return true;
    return false;
}
//去除孤立的噪点，使用8连通区域
Mat MainWindow2::de_longly_nosing(Mat src)
{
    int r=src.rows,c=src.cols;
    Mat src1(r,c,src.type());
    for(int m=0;m<r;m++)
        for(int n=0;n<c;n++)
        {
            if(m==0||n==0||m==r-1||n==c-1)
                for(int i=0;i<3;i++)
                    src1.at<Vec3b>(m,n)[i]=src.at<Vec3b>(m,n)[i];
            else
            {
                if(this->find_nosing(src,m,n))
                    for(int i=0;i<3;i++)
                        src1.at<Vec3b>(m,n)[i]=src.at<Vec3b>(m-1,n)[i];
                else
                    for(int i=0;i<3;i++)
                        src1.at<Vec3b>(m,n)[i]=src.at<Vec3b>(m,n)[i];
            }
        }
    return src1;
    //    imshow("de_longly_nosing",src1);
}
