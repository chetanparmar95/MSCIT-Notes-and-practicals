

/************************************************** Prac 2 A *********************************************************************/

#include <apop.h>
int main()
{
gsl_matrix *m=gsl_matrix_alloc(20,15);
gsl_matrix_set_all(m,1);

for(int i=0;i<m->size1;i++)
{
	Apop_matrix_row(m,i,one_row);
	gsl_vector_scale(one_row,i+1);
}
for(int i=0;i<m->size2;i++)
{
	Apop_matrix_col(m,i,one_col);
	gsl_vector_scale(one_col,i+1);
}
apop_matrix_show(m);
gsl_matrix_free(m);
}



/************************************************** Prac 2 B *********************************************************************/
#include <apop.h>

double calc_taxes(double income){
	double cutoffs[] = {0, 11200, 42650, 110100, 178350, 349700, INFINITY};
	double rates[]   = {0, 0.10, .15, .25, .28, .33, .35};
	double tax       = 0;
	int    bracket   = 1;
	income -= 7850;   //Head of household standard deduction
	income -= 3400*3; //exemption: self plus two dependents.
	while (income > 0){
		tax     += rates[bracket] * GSL_MIN(income, cutoffs[bracket]-cutoffs[bracket-1]);
		income  -= cutoffs[bracket];
		bracket ++;
	}

	return tax;
}

int main(){
	apop_db_open("data-census.db");
	strncpy(apop_opts.db_name_column, "geo_name", 100);
	apop_data *d = apop_query_to_data("select geo_name, Household_median_in as income from income where sumlevel = '040' order by household_median_in desc");
	Apop_col_t(d, "income", income_vector);
	d->vector   = apop_vector_map(income_vector, calc_taxes);
	apop_name_add(d->names, "tax owed", 'v');
	apop_data_show(d);
}

/******************************************************** Prac 3 A Plotting a vector ****************************************************************************/

#include <apop.h>
void plot_matrix_now(gsl_matrix *data)
{
	static FILE *gp = NULL;
	if (!gp)
	gp = popen("gnuplot -persist", "w");
	if (!gp)
	{
		printf("Couldn't open Gnuplot.\n");
		return;
	}
	fprintf(gp,"reset;set term dumb \n");
	fprintf(gp," plot '-' \n");
	apop_matrix_print(data,.output_pipe=gp);
	fflush(gp);
}

int main()
{
	apop_db_open("data-climate.db");
	plot_matrix_now(apop_query_to_matrix("select (year*12+month)/12., temp from temp"));
}


/******************************************************** Prac 3 B eigenbox ****************************************************************************/


#include "eigenbox.h"

apop_data *query_data(){
apop_db_open("data-census.db");
return apop_query_to_data(" select postcode as row_names, "
" m_per_100_f, population/1e6 as population, median_age "
" from geography, income,demos,postcodes "
" whereincome.sumlevel= '040' "
" andgeography.geo_id = demos.geo_id  "
" andincome.geo_name = postcodes.state "
" and geography.geo_id = income.geo_id ");
}

voids how_projection(gsl_matrix *pc_space, apop_data *data){
	fprintf(stderr,"The eigenvectors:\n");
	apop_matrix_print(pc_space, .output_pipe=stderr);
	apop_data *projected = apop_dot(data, apop_matrix_to_data(pc_space));
	printf("plot '-' using 2:3:1 with labels\n");
	apop_data_show(projected);
}

int main(){
apop_plot_lattice(query_data(), "out");
}





/******************************************************** Prac 3 C Erroebars ****************************************************************/


#include <apop.h>
void plot_matrix_now(gsl_matrix *data)
{
	static FILE *gp = NULL;
	if (!gp)
	gp = popen("gnuplot -persist", "w");
	if (!gp)
	{
		printf("Couldn't open Gnuplot.\n");
		return;
	}
	fprintf(gp,"reset;set term dumb \n");
	fprintf(gp," plot '-' with errorbars\n");
	apop_matrix_print(data,.output_pipe=gp);
	fflush(gp);
}

int main()
{
apop_db_open("data-climate.db");
plot_matrix_now(apop_query_to_matrix("select (year*12+month)/12., temp from temp"));
}


/******************************************************** Prac 4 A 1 ****************************************************************************/



#include <stdio.h>
#include <gsl/gsl_randist.h>

int
main (void)
{
	int i;
	double p = 0.6;
	float sum=0;
	/* prints probability distibution table*/

	printf("random variable|||probability |||cumulative prob.\n");
	printf("Chetan Parmar.\n");

	for(i = 0; i <= 1; i++){

			float k = gsl_ran_bernoulli_pdf (i,p);
			sum=sum+k;
			printf("%d\t\t%f\t\t%f\n",i,k,sum);
	}

	printf("\n");
	return 0;
}

/**************************************************************** Prac 4 A 2 ******************************************************************/

#include <stdio.h>
#include <gsl/gsl_randist.h>

int
main (void)
{
	int i,n=5;
	double p = 0.6;
	float sum=0;
	/* prints probability distibution table*/

	printf("random variable|||probability |||cumulative prob.\n");
	printf("Chetan Parmar\n");
	for (i = 0; i<= n; i++){
		float k = gsl_ran_binomial_pdf (i,p,n);
		sum=sum+k;
		printf("%d\t\t%f\t\t%f\n",i,k,sum);
	}

	printf("\n");
	return 0;																								
}

/******************************************************************* Prac 4 A 3 ****************************************************************/

#include <stdio.h>
#include <gsl/gsl_randist.h>

int
main (void)
{
	int i, n = 10;
	double mu = 3.0;
	float sum=0;
	/* prints probability distibution table*/

	printf("random variable|||probability |||cumulative prob.\n");
	printf("Anju  Singh\n");
	for (i = 0; i<= n; i++){
		float k = gsl_ran_poisson_pdf (i,mu);
		sum=sum+k;
		printf("%d\t\t%f\t\t%f\n",i,k,sum);
	}

	printf("\n");
	return 0;
}


/************************************************************** Prac 4 A 4 *****************************************************************/





#include <stdio.h>
#include <gsl/gsl_randist.h>

int
main (void)
{

	double x;
	int a,b ;
	printf("enter vaue for x ,a,b \n");
	scanf("%f",&x);
	scanf("%d",&a);
	scanf("%d",&b);
	float sum=0;
	/* prints probability distibution table*/

	printf("random variable|||probability \n");
	printf("Anju  Singh\n");

	float k = (float)gsl_ran_flat_pdf (x,a,b);

	printf("%f\t\t%f\n",x,k);

	return 0;
}


/********************************************************** Prac 4 A 5 *******************************************************************/


#include <stdio.h>
#include <gsl/gsl_randist.h>
int main (void)
{
	int k=3;
	const double p[]={0.40,0.35,0.25};
	const unsigned int n[]={7,2,3};
	/* prints probability */
	printf("random variable|||probability \n");
	printf("-------------------------------------------------------\n");
	double pmf =gsl_ran_multinomial_pdf(k,p,n);
	printf("%3.9f\n",pmf);
	return 0;
}


/************************************************************** Prac 4 A 6 **********************************************************************/

#include <stdio.h>
#include <gsl/gsl_randist.h>
int main (void)
{
	int x,s,f,n;
	n=6,x=2,s=13;f=39;
	/* prints probability */
	printf("random variable|||probability \n");
	printf("-------------------------------------------------------\n");
	double pmf = gsl_ran_hypergeometric_pdf(x,f,s,n);
	printf("%d%3.9f\n",x,pmf);
	return 0;
}

/***************************************************************** Prac 4 B **********************************************************************/


#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

void normal();
void beta();
void gamma1();
void exponential();
void lognormal();

int main()
{
	int choice;
	printf("continous distributions\n");
	printf("-----------------------\n");
	printf("1:Normal distribution\n");
	printf("2:Gamma distribution\n");
	printf("3:Exponential distribution\n");
	printf("4:Beta distribution\n");
	printf("5:Lognormal distribution\n");
	printf("enter your choice\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
		normal();
		break;
		case 2:
		gamma1();
		break;
		case 3:
		exponential();
		break;
		case 4:
		beta();
		break;
		case 5:
		lognormal();
		break;
		default:
		printf("wrong choice\n");
	}
	
	return 0;
	
}


void normal()
{
	double P, Q;
	double x = 10;
	double sigma=5;
	double pdf;
	printf("Normal distribution :x=%f sigma=%f\n",x,sigma);
	pdf = gsl_ran_gaussian_pdf (x,sigma);
	printf ("prob(x = %f) = %f\n", x, pdf);
	P = gsl_cdf_gaussian_P (x,sigma);
	printf ("prob(x < %f) = %f\n", x, P);
	Q = gsl_cdf_gaussian_Q (x,sigma);
	printf ("prob(x > %f) = %f\n", x, Q);
	x = gsl_cdf_gaussian_Pinv (P,sigma);
	printf ("Pinv(%f) = %f\n", P, x);
	x = gsl_cdf_gaussian_Qinv (Q,sigma);
	printf ("Qinv(%f) = %f\n", Q, x);
}


void gamma1()
{
	double P, Q;
	double x = 1.5;
	double a=1;
	double b=2;
	double pdf;
	printf("Gamma distribution :x=%f a=%f b=%f\n",x,a,b);
	pdf = gsl_ran_gamma_pdf (x,a,b);
	printf ("prob(x = %f) = %f\n", x, pdf);
	P = gsl_cdf_gamma_P (x,a,b);
	printf ("prob(x < %f) = %f\n", x, P);
	Q = gsl_cdf_gamma_Q (x,a,b);
	printf ("prob(x > %f) = %f\n", x, Q);
	x = gsl_cdf_gamma_Pinv (P,a,b);
	printf ("Pinv(%f) = %f\n", P, x);
	x = gsl_cdf_gamma_Qinv (Q,a,b);
	printf ("Qinv(%f) = %f\n", Q, x);
}


void exponential()
{
	double P, Q;
	double x = 0.05;
	double lambda=2;
	double pdf;
	printf("Exponential distribution :x=%f lambda=%f\n",x,lambda);
	pdf = gsl_ran_exponential_pdf (x,lambda);
	printf ("prob(x = %f) = %f\n", x, pdf);
	P = gsl_cdf_exponential_P (x,lambda);
	printf ("prob(x < %f) = %f\n", x, P);
	Q = gsl_cdf_exponential_Q (x,lambda);
	printf ("prob(x > %f) = %f\n", x, Q);
	x = gsl_cdf_exponential_Pinv (P,lambda);
	printf ("Pinv(%f) = %f\n", P, x);
	x = gsl_cdf_exponential_Qinv (Q,lambda);
	printf ("Qinv(%f) = %f\n", Q, x);
}


void beta()
{
	double P, Q;
	double x = 0.8;
	double a=0.5;
	double b=0.5;
	double pdf;
	printf("Beta distribution :x=%f a=%f b=%f\n",x,a,b);
	pdf = gsl_ran_beta_pdf (x,a,b);
	printf ("prob(x = %f) = %f\n", x, pdf);
	P = gsl_cdf_beta_P (x,a,b);
	printf ("prob(x < %f) = %f\n", x, P);
	Q = gsl_cdf_beta_Q (x,a,b);
	printf ("prob(x > %f) = %f\n", x, Q);
	x = gsl_cdf_beta_Pinv (P,a,b);
	printf ("Pinv(%f) = %f\n", P, x);
	x = gsl_cdf_beta_Qinv (Q,a,b);
	printf ("Qinv(%f) = %f\n", Q, x);
}


void lognormal()
{
	double P, Q;
	double x = 4;
	double zeta=2;
	double sigma=1.5;
	double pdf;
	printf("Lognormal distribution :x=%f zeta=%f sigma=%f\n",x,zeta,sigma);
	pdf = gsl_ran_lognormal_pdf (x,zeta,sigma);
	printf ("prob(x = %f) = %f\n", x, pdf);
	P = gsl_cdf_lognormal_P (x,zeta,sigma);
	printf ("prob(x < %f) = %f\n", x, P);
	Q = gsl_cdf_lognormal_Q (x,zeta,sigma);
	printf ("prob(x > %f) = %f\n", x, Q);
	x = gsl_cdf_lognormal_Pinv (P,zeta,sigma);
	printf ("Pinv(%f) = %f\n", P, x);
	x = gsl_cdf_lognormal_Qinv (Q,zeta,sigma);
	printf ("Qinv(%f) = %f\n", Q, x);
}	


/********************************************************** Prac 5 A *******************************************************************************/



#include <stdio.h>
#include <gsl/gsl_fit.h>
int
main (void)
{
	int i, n = 4;
	double x[4] = { 1970, 1980, 1990, 2000 };
	double y[4] = { 12, 11, 14, 13 };
	double w[4] = { 0.1, 0.2, 0.3, 0.4 };
	double c0, c1, cov00, cov01, cov11, chisq;
	gsl_fit_wlinear (x, 1, w, 1, y, 1, n,&c0, &c1, &cov00, &cov01, &cov11,&chisq);
	printf ("# best fit: Y = %g + %g X\n", c0, c1);
	printf ("# covariance matrix:\n");
	printf ("# [ %g, %g\n# %g, %g]\n",cov00, cov01, cov01, cov11);
	printf ("# chisq = %g\n", chisq);
	
	for (i = 0; i < n; i++)
		printf ("data: %g %g %g\n", x[i], y[i], 1/sqrt(w[i]));
	
	printf ("\n");

	for (i = -30; i < 13; i++){
		double xf = x[0] + (i/100.0) * (x[n-1] - x[0]);
		double yf, yf_err;
		gsl_fit_linear_est (xf,c0, c1,cov00, cov01, cov11,&yf, &yf_err);
		printf ("fit: %g %g\n", xf, yf);
		printf ("hi : %g %g\n", xf, yf + yf_err);
		printf ("lo : %g %g\n", xf, yf - yf_err);
	}

	return 0;
}


/****************************************************prac 5 B ********************************************************************************/


#include <apop.h>
int main(){
	apop_db_open("climate-db.db");
	apop_data *precip = apop_query_to_data("select PCP from precip");
	apop_model *est = apop_estimate(precip, apop_normal);
	apop_data *precip_binned = apop_data_to_bins(precip/*,.bin_count=180*/);
	apop_model *datahist = apop_estimate(precip_binned, apop_pmf);
	apop_model *modelhist = apop_model_to_pmf(.model=est,.binspec=apop_data_get_page(precip_binned, "<binspec>"), .draws=1e5);
	double scaling = apop_sum(datahist->data->weights)/apop_sum(modelhist->data->weights);
	gsl_vector_scale(modelhist->data->weights, scaling);
	apop_data_show(apop_histograms_test_goodness_of_fit(datahist,modelhist));
}


/*******************************************************************practical 6*******************************************************************************/

//1. using seed square method

#include <stdio.h>
#include <gsl/gsl_rng.h>

gsl_rng * r;  /* global generator */

int
main (void)
{

const gsl_rng_type * T;

gsl_rng_env_setup();

  T = gsl_rng_default;
  r = gsl_rng_alloc (T);

printf ("Performed by Chetan Parmar");
printf ("generator type: %s\n", gsl_rng_name (r));
printf ("seed = %lu\n", gsl_rng_default_seed);
printf ("first value = %lu\n", gsl_rng_get (r));

gsl_rng_free (r);

return 0;
}                                                                       



//2. using exponential distribution


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
int main(int argc, char *argv[]){
	int i,n;
	float x,alpha;
	gsl_rng *r=gsl_rng_alloc(gsl_rng_mt19937); /* initialises GSL RNG */
  	n=atoi(argv[1]);
	alpha=atof(argv[2]);
  	x=0;
	
	for (i=0;i<n;i++){
      	x=alpha*x + gsl_ran_exponential(r,1);
		printf(" %2.4f \n",x);
   }

return(0);
}


//3. using uniform distribution

#include <stdio.h>
#include <gsl/gsl_rng.h>
int
main (void){
	const gsl_rng_type * T;
	gsl_rng * r;
	int i, n = 10;
	gsl_rng_env_setup();
  	T = gsl_rng_default;
  	r = gsl_rng_alloc (T);
	for (i = 0; i < n; i++){
		double u = gsl_rng_uniform (r);
		printf ("%.5f\n", u);
	}

	gsl_rng_free (r);
	return 0;

}

//4. Using binomial distribution


#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
int
main (void)
{
	const gsl_rng_type * T;
	gsl_rng * r;
	int i, n = 10;
	 /* create a generator chosen by the
	environment variable GSL_RNG_TYPE */
	gsl_rng_env_setup();
	T = gsl_rng_default;
	r = gsl_rng_alloc (T);
	float p=0.3;
  	/* print n random variates chosen from
		the binomial distribution with mean
		parameter mu */
	for (i = 0; i < n; i++)
	{
		unsigned int k = gsl_ran_binomial(r, p,n);
		printf (" %u", k);
	}
	printf ("\n");
	gsl_rng_free (r);

	return 0;
}







/*******************************************************************practical 7*******************************************************************************/








/*******************************************************************practical 8*******************************************************************************/


//KES college

#include <apop.h>
int main()
{
apop_db_open("company.db");

char joinedtab[] = "(select emp.id, emp.salary, dept.num from emp, dept where emp.id = dept.id)";

apop_data_show(apop_anova(joinedtab, "id", "salary", "num"));
}


//valia college

include<apop.h>

int main(){
	apop_db_open("data-metro.db");
	char joinedtab[] = "(select year, riders, line from riders, lines where riders.station = lines.station)";
 	printf("Performed by Chetan Parmar");
	apop_data_show(apop_anova(joinedtab, "riders", "line", "year"));


}














