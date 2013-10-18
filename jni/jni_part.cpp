#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "levmar/levmar.h"

using namespace std;

#define  LOG_TAG    "levmarndk"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

/* Meyer's (reformulated) problem, minimum at (2.48, 6.18, 3.45) */
void meyer(double *p, double *x, int m, int n, void *data)
{
register int i;
double ui;

	for(i=0; i<n; ++i){
		ui=0.45+0.05*i;
		x[i]=p[0]*exp(10.0*p[1]/(ui+p[2]) - 13.0);
	}
}

void jacmeyer(double *p, double *jac, int m, int n, void *data)
{
register int i, j;
double ui, tmp;

  for(i=j=0; i<n; ++i){
	  ui=0.45+0.05*i;
	  tmp=exp(10.0*p[1]/(ui+p[2]) - 13.0);

	  jac[j++]=tmp;
	  jac[j++]=10.0*p[0]*tmp/(ui+p[2]);
	  jac[j++]=-10.0*p[0]*p[1]*tmp/((ui+p[2])*(ui+p[2]));
  }
}

extern "C" {
JNIEXPORT jint JNICALL Java_hvrl_levmar_levmarActivity_Driver(JNIEnv* env, jobject thiz)
{
	int problem, ret;
	double p[5], // 5 is max(2, 3, 5)
		   x[16]; // 16 is max(2, 3, 5, 6, 16)
	int m, n;
	double opts[LM_OPTS_SZ], info[LM_INFO_SZ];
	int i,j;

	m=3; n=16;
	p[0]=8.85; p[1]=4.0; p[2]=2.5;
	x[0]=34.780;	x[1]=28.610; x[2]=23.650; x[3]=19.630;
	x[4]=16.370;	x[5]=13.720; x[6]=11.540; x[7]=9.744;
	x[8]=8.261;	x[9]=7.030; x[10]=6.005; x[11]=5.147;
	x[12]=4.427;	x[13]=3.820; x[14]=3.307; x[15]=2.872;
	//ret=dlevmar_der(meyer, jacmeyer, p, x, m, n, 1000, opts, info, NULL, NULL, NULL); // with analytic Jacobian

    double *work, *covar;
	work=(double*)malloc((LM_DIF_WORKSZ(m, n)+m*m)*sizeof(double));
	if(!work){
		fprintf(stderr, "memory allocation request failed in main()\n");
	  exit(1);
	}
	covar=work+LM_DIF_WORKSZ(m, n);

	ret=dlevmar_dif(meyer, p, x, m, n, 1000, opts, info, work, covar, NULL); // no Jacobian, caller allocates work memory, covariance estimated

	LOGI("Covariance of the fit:\n");
	for(i=0; i<m; ++i){
	  for(j=0; j<m; ++j)
		  //printf("%g ", covar[i*m+j]);
		  LOGI("%g ", covar[i*m+j]);
	  //printf("\n");
	}

	free(work);

 	return 1;
}
}


