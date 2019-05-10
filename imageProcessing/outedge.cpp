#include"widget.h"
#include"outedge.h"

void Outedge::outedge(Mat &src,Mat &dst)
{
    Mat src_gray;
    Mat detected_edges;
    if(!src.data)
    {
        return ;
    }
    src_gray.create(src.size(),src.type());
    cvtColor(src,src_gray,CV_BGR2GRAY);
    dst.create(src.size(),src.type());
    blur(src_gray,detected_edges,Size(3,3));

    Canny(detected_edges,detected_edges,lowThreshold,ratio*lowThreshold,kernel_size);

    dst=Scalar::all(255);

    src.copyTo(dst,detected_edges);

}

