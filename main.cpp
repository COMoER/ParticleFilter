#include "simple_pf.h"
typedef simple_particle_filter::VectorState VS;
typedef simple_particle_filter::VectorOb VO;
int char2int(const char* N)
{
    int i=0;
    int c = 0;
    char s=N[i];
    while(s!='\0')
    {
        c = c*10+(s-'0');
        s = N[++i];
    }
    return c;
}
void NormalNoise(VS &noise,const cv::Mat& S)
{
    cv::RNG r;
    cv::Mat out;
    cv::Mat mean = cv::Mat::zeros(6,1,CV_64F);
    r.fill(out,cv::RNG::NORMAL,mean,S);
    cv::cv2eigen(out,noise);
}
void generate_data(int i,double delta_t,int& x,int& y,VO& ob,double sigmar,default_random_engine& e)
{
    normal_distribution<double> g(0,sigmar);
    double r = 0.3*(delta_t*i);
    double x_ = r*cos(0.2*delta_t*i);
    double y_ = r*sin(0.2*delta_t*i);
    x = cvRound(x_);
    y = cvRound(y_);
    ob(0,0) = r+g(e);
    ob(1,0) = 0.2*delta_t*i+g(e);
}

int main(int argc,char** argv) {
    int Ns = 100;
    if(argc>1) Ns = char2int(argv[1]);
    double sigmar = 0.008;
    Matrix<double,6,6> Q = Matrix<double,6,6>::Zero();
    simple_particle_filter filter(Ns,Q,sigmar);
    int H = 600;
    int W = 600;
    double delta_t = 1;
    default_random_engine e;
    cv::Mat canvas = cv::Mat::zeros(H,W,CV_8UC3);
    for(int i=0;i<500;++i)
    {
        vector<VO> obs;
        VO ob;
        int x,y;
        generate_data(i,delta_t,x,y,ob,sigmar,e);
        obs.push_back(ob);
        filter.prediction_step(delta_t);
        VS result = filter.update_step(obs);
        int x_p = cvRound(result(0,0))+H/2;
        int y_p = cvRound(result(1,0))+W/2;
        x += H/2;
        y += W/2;
        cv::circle(canvas,cv::Point(x,y),1,cv::Scalar(0,255,0),-1);
        cv::circle(canvas,cv::Point(x_p,y_p),1,cv::Scalar(255,0,0),-1);
        printf("%d %d\n",x_p,y_p);
    }
    cv::imshow("out",canvas);
    cv::waitKey(0);

    return 0;
}
