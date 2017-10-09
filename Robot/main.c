#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define l1 180.0
#define l2 130.0
#define PI 3.141592

void FK(float th1, float th2, float *xt, float *yt, float *x1, float *y1);
void IK(float x, float y, float *th1, float *th2);
float R2D (float rad);
float D2R (float deg);

int main()
{
    FILE *f;
    f=fopen("Forward.txt", "w");
    float x, y;
    float th1, th2;
    float x1, y1;

    th1=D2R(10.313);
    th2=D2R(25.783);

    FK(th1, th2, &x, &y, &x1, &y1);
    printf("\n Forward: th1=%f th2=%f xt=%f yt=%f\n", R2D(th1), R2D(th2), x, y);
    printf("\n Forward: x1=%f y1=%f\n",x1, y1);

    fprintf(f,"th1 = %f\n", R2D(th1));
    fprintf(f,"th2 = %f\n", R2D(th2));
    fprintf(f,"x1 = %f\n", x1);
    fprintf(f,"y1 = %f\n", y1);
    fprintf(f,"xt = %f\n", x);
    fprintf(f,"yt = %f\n", y);

    fclose(f);

    IK(x, y, &th1, &th2);
    printf("\n Inverse: x=%f y=%f th1=%f th2=%f\n", x, y, R2D(th1), R2D(th2));

    return 0;
}

void FK(float th1, float th2, float *xt, float *yt, float *x1, float *y1)
{
    *x1 = l1 * cos(th1);
    *y1 = l1 * sin(th1);

    *xt = *x1 + l2 * cos(th1+th2);
    *yt = *y1 + l2 * sin(th1+th2);
}

float R2D (float rad)
{
    return 180.0/PI*rad;
}

float D2R (float deg)
{
    return deg*PI/180.;
}

void IK(float x, float y, float *th1, float *th2)
{
    float s1, c1, s2, c2;

    c2 = (x*x+ y*y- l1*l1-l2*l2);
    c2/=(2*l1*l2) ;
    s2 = sqrt(1 - c2*c2);
    *th2 = atan2(s2, c2);
    c1 =  (x*(l2*cos(*th2)+l1) + l2*sin(*th2)*y);
    c1/=( (l1+l2*cos(*th2))*(l1+l2*cos(*th2)) + (l2*sin(*th2))*(l2*sin(*th2)) ) ;
    s1 = (-l2*sin(*th2)*x+(l2*cos(*th2)+l1)*y);
    s1/=((l1+l2*cos(*th2))*(l1+l2*cos(*th2))+(l2*sin(*th2))*(l2*sin(*th2)));
    *th1 = atan2(s1, c1);
}
