#include "mainwindow1.h"
const int b_c=2;//1 >
const int num=12;
MainWindow1::MainWindow1(QWidget *parent)
    : QMainWindow(parent),hs(0),he(0),fw(0)
{
    test_main();
}

MainWindow1::~MainWindow1()
{
    
}

void MainWindow1::draw_bar()
{
    //200 56225 51440
    int number[14]={0},se[100]={0};
    char str[15]="0005622551444";
    Mat src(250,360,16);
    for(int m=0;m<src.rows;m++)
        for(int n=0;n<src.cols;n++)
            for(int i=0;i<3;i++)
                src.at<Vec3b>(m,n)[i]=255;
    for(int i=0;i<13;i++)
        number[i]=(int)(str[i]-'0');

    check2(number);

    get_se(number,se);
    int m1=src.rows/6,n1=src.cols/8;
    int n2=0,n3;
    int w=3,h=src.rows*4/6;
    for(int i=0;i<95;i++)
    {
        int m2=h;
        if(i==0||i==2||i==46||i==48||i==94||i==92)
            m2=h+src.rows/12;
        if(se[i]==1)
        {
            n2=n1+i*w,n3=n2+w;
            for(int m=m1;m<=m2;m++)
                for(int n=n2;n<n3;n++)
                    for(int a=0;a<3;a++)
                        src.at<Vec3b>(m,n)[a]=0;
        }
    }
    imshow("2",src);
}

void MainWindow1::check2(int number[])
{
    int t[13],need=10-number[12];
    for(int i=0;i<13;i++)
        t[i]=number[12-i];
    int n1=0,n2=0;
    for(int i=1;i<=6;i++)
        n1+=3*t[2*i-1],n2+=t[2*i];
    n1=n1+n2;
    n1=n1%10;
    cout <<n1<<" "<<need<<endl;
    if(need>n1)
        number[0]=need-n1;
    else if(need<n1)
        number[0]=10+(need-n1);
    for(int i=0;i<13;i++)
        cout <<number[i];
    cout <<endl;

}

void MainWindow1::get_oe(int n,int temp[])
{
    int F[10]={31,20,18,17,12,6,3,10,9,5};
    int t=F[n];
    for(int i=5;i>=1;i--)
    {
        temp[i]=t%2;
        t/=2;
    }
    temp[0]=1;
}

void MainWindow1::get_se(int nu[],int se[])
{
    int A[20]={13,25,19,61,35,49,47,59,55,11,39,51,27,33,29,57,5,17,9,23};
    int B[10]={114,102,108,66,92,78,80,68,72,116};
    int dn=3,oe[6];
    get_oe(nu[0],oe);
    se[0]=1,se[2]=1;
    for(int i=1;i<7;i++)
    {
        int t=A[nu[i]];
        if(oe[i-1]==0)
            t=A[nu[i]+10];
        for(int a=6;a>=0;a--)
        {
            se[dn+7*(i-1)+a]=t%2;
            t/=2;
        }
    }
    se[46]=1,se[48]=1;
    dn=50;
    for(int i=7;i<13;i++)
    {
        int t=B[nu[i]];
        for(int a=6;a>=0;a--)
        {
            se[dn+7*(i-7)+a]=t%2;
            t/=2;
        }
    }
    se[92]=1,se[94]=1;
}

void MainWindow1::test_main()
{
    Mat src=imread("f:/num\\code3.jpg");
    imshow("1",src);
    Mat src1(src.rows/2,src.cols,src.type());
    this->cut(src,src1);
    imshow("2",src1);
    this->weight_gray(src1);
    int th=get_threshold_2(src1);
    int color=binary(src1,th,b_c);
    imshow("3",src1);
    Mat src2=check(src1,color);
    imshow("4",src2);
    get_num(src2,color);
}

void MainWindow1::get_num(Mat src,int color)
{
    int *w=new int[src.cols+1];
    int *d=new int[100+7*num],dn=0;
    int r=src.rows,c=src.cols;
    int ns=0,ne=0;
//////投影定位，得到w[]
    for(int n=0;n<c;n++)
    {
        w[n]=0;
        for(int m=0;m<r;m++)
        {
            int t=src.at<Vec3b>(m,n)[0];
            if(t==color)
                w[n]++;
        }
    }
/////确定条形码宽度,ns,ne,以及平均每格咱的长度
    for(int n=0;n<c;n++)
    {
        if(w[n]!=0)
        {
            ns=n;
            break;
        }
    }
    for(int n=c-1;n>=0;n--)
        if(w[n]!=0)
        {
            ne=n;
            break;
        }
    double t=1.0*(ne-ns+1)/(11.0+7*num);
/////////生成01序列
    for(int n=ns;n<=ne;n++)
    {
        double s=ns,e=0;
        if(fabs(w[n+1]-w[n])>0)
        {
            e=n+1;
            int m=(int)((e-s)/t+0.6);
//            cout <<e<<" "<<s<<":";
            if(w[n]==0)
            {
                int i=dn;
//                cout <<m<<":";
                for(;dn<m+i;dn++){
//                    cout <<0;
                    d[dn]=0;
                }
//                cout <<endl;
            }
            else
            {
                int i=dn;
//                cout <<m<<":";
                for(;dn<m+i;dn++){
//                    cout <<1;
                    d[dn]=1;
                }
//                cout <<endl;
            }
            ns=e;
        }
    }
    cout <<dn<<" "<<endl;

////////////dn为序列长度，对序列进行翻译
    int re[13],re1[7],r1=0;
    int A[20]={13,25,19,61,35,49,47,59,55,11,39,51,27,33,29,57,5,17,9,23};
    int B[10]={114,102,108,66,92,78,80,68,72,116};
    int F[10]={31,20,18,17,12,6,3,10,9,5};

    int d1=dn-95;
    cout <<"d1:"<<d1<<endl;
    for(int i=0;i<6;i++)
    {
        int t1=0;
        for(int c=6;c>=0;c--)
        {
            t1=t1+d[3+7*i+c]*pow(2,6-c);
        }
        int c1=0;
        for(c1=0;c1<20;c1++)
            if(t1==A[c1])
            {
                re[r1++]=c1%10;
                re1[r1-1]=c1;
                break;
            }
        if(c1==20&&d1!=0)//////防止错格的一个补救
        {
            for(int e=1;e<=d1;e++)
            {
                int t1=0;
                for(int c=6;c>=0;c--)
                {
                    t1=t1+d[3+7*i+c+e]*pow(2,6-c);
                }
                int c1=0;
                for(c1=0;c1<20;c1++)
                    if(t1==A[c1])
                    {
                        re[r1++]=c1%10;
                        re1[r1-1]=c1;
                        break;
                    }
                if(c1!=20)
                {
                    d1-=e;
                    break;
                }
            }
        }
    }
    for(int i=0;i<6;i++)
    {
        int t1=0;
        for(int c=6;c>=0;c--)
        {
            t1=t1+d[50+7*i+c]*pow(2,6-c);
        }
        int c1=0;
        for(c1=0;c1<10;c1++)
            if(t1==B[c1])
            {
                re[r1++]=c1;
                break;
            }
        if(c1==10&&d1!=0)
        {
            for(int e=1;e<=d1;e++)
            {
                int t1=0;
                for(int c=6;c>=0;c--)
                {
                    t1=t1+d[3+7*i+c+e]*pow(2,6-c);
                }
                int c1=0;
                for(c1=0;c1<10;c1++)
                    if(t1==B[c1])
                    {
                        re[r1++]=c1;
                        break;
                    }
                if(c1!=10)
                {
                    d1-=e;
                    break;
                }
            }
        }
    }
//////////获取前置符
    int f=0;
    if(r1>=6)
    {
        int t=0;
        for(int i=0;i<6;i++)
        {
            if(re1[i]<10)
                t=2*t+1;
            else
                t=2*t;
        }
        t-=32;
        for(int i=0;i<10;i++)
            if(t==F[i])
            {
                cout <<i;
                f=i;
                break;
            }
    }
    for(int i=0;i<r1;i++)
        cout <<re[i];
    cout <<endl;
    if(r1==12)
        check1(f,re);
    delete w,d;
}

void MainWindow1::check1(int n, int temp[])
{
    int t[13];
    for(int i=0;i<12;i++)
        t[i]=temp[11-i];
    t[12]=n;
    int n1=0,n2=0;
    for(int i=1;i<=6;i++)
        n1+=3*t[2*i-1],n2+=t[2*i];
    n1=n1+n2;
    n1=n1%10;
    n1=10-n1;
    if(n1==t[0])
        cout <<"Correct!"<<endl;
    else
        cout <<"Wrong!"<<endl;
}


Mat MainWindow1::check(Mat src,int color)
{
    int *h=new int[src.rows+1],*w=new int[src.cols+1];
    int r=src.rows,c=src.cols;
    int t=0,m=0,n=0;

    int th=4;
    ////////////确定条形码的上下位置////////////////
    for(m=0;m<r;m++)
    {
        h[m]=0;
        for(n=0;n<c;n++)
        {
            int temp=src.at<Vec3b>(m,n)[0];
            if(temp==color)
                h[m]++;
        }
    }
    int temp=0,n1=0;
    for(m=0;m<r;m++)
        if(fabs(h[m]-h[m-1])<=th&&h[m]!=0)
        {
            n1++;
            if(n1>r/2)
            {
                temp=h[m];
                break;
            }
        }
    for(m=0;m<r-1;m++)
    {
        int n2=0;
        if(fabs(h[m]-temp)<=th)
            for(int m1=m;m1<r-1;m1++)
            {
                if(fabs(h[m1]-temp)<=th)
                    n2++;
                else
                    break;
            }
        if(n2>r/4)
            break;
    }
    hs=m;
    for(m=r-1;m>=1;m--)
    {
        int n2=0;
        if(fabs(h[m]-temp)<=th)
            for(int m1=m;m1>=0;m1--)
            {
                if(fabs(h[m1]-temp)<=th)
                    n2++;
                else
                    break;
            }

        if(n2>r/4)
            break;
    }
    he=m;
    int tt=(he-hs)/10;
    hs+=tt,he-=tt;
//    cout <<temp<< " "<<n1<<endl;
//    cout <<hs<<" "<<he<<endl;
//    cout <<r<<" "<<c<<endl;
    if(hs>=he)
    {
        cout <<"wrong"<<endl;
        return src;
    }
    ////////////////根据位置生成新的图片，进行旋转修正//////////////////////////

    Mat src1(he-hs,src.cols,src.type());
    for(m=0;m<src1.rows;m++)
        for(n=0;n<src1.cols;n++)
            for(int i=0;i<3;i++)
                src1.at<Vec3b>(m,n)[i]=src.at<Vec3b>(m+hs,n)[i];
    imshow("x",src1);
    t=0,n1=0;
    int *ht=new int[src1.rows+1];
    for(m=0;m<src1.rows;m++)
    {
        for(n=0;n<src1.cols;n++)
        {
            int temp=src1.at<Vec3b>(m,n)[0];
            if(temp==color)break;
        }
        ht[m]=n;
        t+=n;
    }
    t/=src1.rows;
    for(m=0;m<src1.rows;m++)
        ht[m]=t-ht[m];
    Mat src2(src1.rows,src1.cols,src1.type());
    for(m=0;m<src1.rows;m++)
        for(n=0;n<src1.cols;n++)
        {
            int temp=src1.at<Vec3b>(m,n)[0];
            if(temp==0)
                for(int i=0;i<3;i++)
                    src2.at<Vec3b>(m,n)[i]=0;
            else
                for(int i=0;i<3;i++)
                    src2.at<Vec3b>(m,n+ht[m])[i]=color;
        }
    imshow("y",src2);

    ///////////////进行噪声处理////////////////////////
    for(n=0;n<src2.cols;n++)
    {
        w[n]=0;
        for(m=0;m<src2.rows;m++)
        {
            int temp=src2.at<Vec3b>(m,n)[0];
            if(temp==color)
                w[n]++;
        }
        if(w[n]>(src2.rows/4))
        {
            for(m=0;m<src2.rows;m++)
                for(int i=0;i<3;i++)
                    src2.at<Vec3b>(m,n)[i]=color;
        }
        else
        {
            for(m=0;m<src2.rows;m++)
                for(int i=0;i<3;i++)
                    src2.at<Vec3b>(m,n)[i]=0;
        }
    }
    delete h,w,ht;
    return src2;
}



void MainWindow1::cut(Mat src, Mat src1)
{
    for(int m=0;m<src1.rows;m++)
    {
        for(int n=0;n<src.cols;n++)
        {
            for(int i=0;i<3;i++)
                src1.at<Vec3b>(m,n)[i]=src.at<Vec3b>(m+src.rows/4,n)[i];
        }
    }
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
